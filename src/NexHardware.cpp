/**
 * @file NexHardware.cpp
 *
 * The implementation of base API for using Nextion. 
 *
 * @author  Wu Pengfei (email:<pengfei.wu@itead.cc>)
 * @date    2015/8/11
 * @author Jyrki Berg 2/17/2019 (https://github.com/jyberg)
 * 
 * @copyright 
 * Copyright (C) 2014-2015 ITEAD Intelligent Systems Co., Ltd. \n
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 * 
 * @copyright 2020 Jyrki Berg
 **/

#include "Onion.h"
#include "NexHardware.h"
#include "NexTouch.h"
#include "SoftwareSerial.h"
#include "helpers.h"
#include <algorithm>

#define NEX_RET_EVENT_NEXTION_STARTUP       (0x00)
#define NEX_RET_EVENT_TOUCH_HEAD            (0x65)
#define NEX_RET_CURRENT_PAGE_ID_HEAD        (0x66)
#define NEX_RET_EVENT_POSITION_HEAD         (0x67)
#define NEX_RET_EVENT_SLEEP_POSITION_HEAD   (0x68)
#define NEX_RET_STRING_HEAD                 (0x70)
#define NEX_RET_NUMBER_HEAD                 (0x71)
#define NEX_RET_AUTOMATIC_SLEEP             (0x86)
#define NEX_RET_AUTOMATIC_WAKE_UP           (0x87)
#define NEX_RET_EVENT_NEXTION_READY         (0x88)
#define NEX_RET_START_SD_UPGRADE            (0x89)
#define Nex_RET_TRANSPARENT_DATA_FINISHED   (0xFD)
#define Nex_RET_TRANSPARENT_DATA_READY      (0xFE)

#define NEX_RET_INVALID_CMD             (0x00)
#define NEX_RET_CMD_FINISHED_OK         (0x01)
#define NEX_RET_INVALID_COMPONENT_ID    (0x02)
#define NEX_RET_INVALID_PAGE_ID         (0x03)
#define NEX_RET_INVALID_PICTURE_ID      (0x04)
#define NEX_RET_INVALID_FONT_ID         (0x05)
#define NEX_RET_INVALID_FILE_OPERATION  (0x06)
#define NEX_RET_INVALID_CRC             (0x09)
#define NEX_RET_INVALID_BAUD            (0x11)
#define NEX_RET_INVALID_WAVEFORM_ID_OR_CHANNEL_NRO  (0x12)
#define NEX_RET_INVALID_VARIABLE_OR_ATTRIBUTE       (0x1A)
#define NEX_RET_INVALID_VARIABLE_OPERATION          (0x1B)
#define NEX_RET_ASSIGNMENT_FAILED_TO_ASSIGN         (0x1C)
#define NEX_RET_EEPROM_OPERATION_FAILED             (0x1D)
#define NEX_RET_INVALID_QUANTITY_OF_PARAMETERS      (0x1E)
#define NEX_RET_IO_OPERATION_FAILED                 (0x1F)
#define NEX_RET_ESCAPE_CHARACTER_INVALID            (0x20)
#define NEX_RET_VARIABLE_NAME_TOO_LONG              (0x23)
#define NEX_RET_SERIAL_BUFFER_OVERFLOW              (0x24)

class SoftwareSerial;
class Stream;

const uint32_t Nextion::baudRates[]{2400, 4800, 9600, 19200, 31250, 38400, 57600, 115200, 230400, 250000, 256000, 512000, 921600};

// queued events and size
static uint8_t _nextion_queued_events[][2] =
{
    {NEX_RET_EVENT_NEXTION_STARTUP,     6},
    {NEX_RET_EVENT_TOUCH_HEAD,          7},
    {NEX_RET_CURRENT_PAGE_ID_HEAD,      5},
    {NEX_RET_EVENT_POSITION_HEAD,       9},
    {NEX_RET_EVENT_SLEEP_POSITION_HEAD, 9},
    {NEX_RET_AUTOMATIC_SLEEP,           4},
    {NEX_RET_AUTOMATIC_WAKE_UP,         4},
    {NEX_RET_EVENT_NEXTION_READY,       1},
    {NEX_RET_START_SD_UPGRADE,          1},
    {0xFF,                              0}  // end of list
};

void Nextion::ReadQueuedEvents()
{
    // std::cout<<"ReadQueuedEvents"<<std::endl;
    for(int c=m_nexSerial->peek(); c!=-1; c=m_nexSerial->peek())
    {
        int i{0};
        for(; _nextion_queued_events[i][1]; ++i)
        {
            if(c==_nextion_queued_events[i][0])
            {
                nexQueuedEvent *event = new nexQueuedEvent();
                if(readBytes(&event->event_data[0],_nextion_queued_events[i][1],20)!= _nextion_queued_events[i][1])
                {
                    delete event;
                    return;
                }
                if(!m_queuedEvents)
                {
                    m_queuedEvents = event;
                }
                else
                {
                    nexQueuedEvent *last = m_queuedEvents->m_next;
                    while( last->m_next)
                    {
                        last = last->m_next;
                    }
                    last->m_next=event;
                }
                yield();
            }
        }
        if(!_nextion_queued_events[i][1])
        {
            return;
        }
    }
    return;
}

nexQueuedEvent* Nextion::GetQueuedEvent()
{
    nexQueuedEvent *tmp{m_queuedEvents};
    if(tmp)
    {
        m_queuedEvents = m_queuedEvents->m_next;
        tmp->m_next=0;
    }
    return tmp;
}

Nextion::Nextion(SoftwareSerial &nexSerial):  m_nexSerialType(SW), s_nexSerial(nexSerial)
{
    m_nexSerial = &nexSerial;
    s_nexSerial = nexSerial;
    nextionStartupCallback = nullptr;
    currentPageIdCallback = nullptr;
    touchCoordinateCallback = nullptr;
    touchEventInSleepModeCallback = nullptr;
    automaticSleepCallback = nullptr;
    automaticWakeUpCallback = nullptr;
    nextionReadyCallback = nullptr;
    startSdUpgradeCallback = nullptr;
}

Nextion* Nextion::GetInstance(SoftwareSerial &nexSerial)
{
    return new Nextion(nexSerial);
}

Nextion::~Nextion()
{}


bool Nextion::connect()
{
    sendCommand("");
    sendCommand("connect");
    std::string resp;
    recvRetString(resp, NEX_TIMEOUT_RETURN, false);
    if(resp.find("comok",0) != -std::string::npos)
    {
        DEBUG_PRINT("Nextion::connect(): Device details: " << resp);
        return true;
    }
    return false;
}

bool Nextion::findBaud(uint32_t &baud)
{
    for(uint8_t i = 0; i < (sizeof(baudRates)/sizeof(baudRates[0])); i++)
    {
        //((SoftwareSerial*)m_nexSerial)->begin( static_cast<unsigned int>(baudRates[i]) );
        dynamic_cast<SoftwareSerial*>(m_nexSerial)->begin( static_cast<unsigned int>(baudRates[i]) );

        delay(100);
        if(connect())
        {
            baud = baudRates[i];
            DEBUG_PRINT("Nextion::findBaud(): baud: " << baud);
            return true;
        }
    }
    return false; 
}

/*
 * Receive unt32_t data. 
 * 
 * @param number - save uint32_t data. 
 * @param timeout - set timeout time. 
 *
 * @retval true - success. 
 * @retval false - failed.
 *
 */
bool Nextion::recvRetNumber(uint32_t *number, size_t timeout)
{
    bool ret = false;
    uint8_t temp[8] = {0};

    if (!number)
    {
        goto __return;
    }

    ReadQueuedEvents();
    if (sizeof(temp) != readBytes(temp, sizeof(temp),timeout))
    {
        goto __return;
    }

    if (temp[0] == NEX_RET_NUMBER_HEAD
        && temp[5] == 0xFF
        && temp[6] == 0xFF
        && temp[7] == 0xFF
        )
    {
        *number = ((uint32_t)temp[4] << 24) | ((uint32_t)temp[3] << 16) | ((uint32_t)temp[2] << 8) | (temp[1]);
        ret = true;
    }

__return:

    if (ret) 
    {
        DEBUG_PRINT("Nextion::recvRetNumber():" << *number);
    }
    else
    {
        DEBUG_PRINT("Nextion::recvRetNumber(): err" << false);
    }
    
    return ret;
}

/*
 * Receive int32_t data. 
 * 
 * @param number - save int32_t data. 
 * @param timeout - set timeout time. 
 *
 * @retval true - success. 
 * @retval false - failed.
 *
 */
bool Nextion::recvRetNumber(int32_t *number, size_t timeout)
{
    bool ret = false;
    uint8_t temp[8] = {0};

    if (!number)
    {
        goto __return;
    }

    ReadQueuedEvents();
    if (sizeof(temp) != readBytes(temp, sizeof(temp), timeout))
    {
        goto __return;
    }

    if (temp[0] == NEX_RET_NUMBER_HEAD
        && temp[5] == 0xFF
        && temp[6] == 0xFF
        && temp[7] == 0xFF
        )
    {
        *number = ((int32_t)temp[4] << 24) | ((int32_t)temp[3] << 16) | ((int32_t)temp[2] << 8) | (temp[1]);
        ret = true;
    }

__return:

    if (ret) 
    {
        DEBUG_PRINT("Nextion::recvRetNumber():" << *number);
    }
    else
    {
        DEBUG_PRINT("Nextion::recvRetNumber(): err" << false);
    }
    
    return ret;
}

/*
 * Receive string data. 
 * 
 * @param str - save string data. 
 * @param timeout - set timeout time. 
 * @param start_flag - is str start flag (0x70) expected, default falue true
 *
 * @retval true - success. 
 * @retval false - failed.
 *
 */
bool Nextion::recvRetString(std::string &str, size_t timeout, bool start_flag)
{
    str = "";
    bool ret{false};
    bool str_start_flag {!start_flag};
    uint8_t cnt_0xff = 0;
    uint8_t c = 0;
    ReadQueuedEvents();
    unsigned long start{millis()};
    DEBUG_PRINT("Nextion::recvRetString(): start:" << start);
//    size_t avail{(size_t)m_nexSerial->available()};
    while(ret == false && (millis()-start)<timeout)
    {
        while (m_nexSerial->available())
        {
            c = m_nexSerial->o_read();
            if (str_start_flag)
            {
                if (0xFF == c)
                {
                    cnt_0xff++;                    
                    if (cnt_0xff >= 3)
                    {
                        ret = true;
                        break;
                    }
                }
                else
                {
                    str += (char)c;
                }
            }
            else if (NEX_RET_STRING_HEAD == c)
            {
                str_start_flag = true;
            }
            yield();
        }
        // delayMicroseconds(20); delay specified in serial port setup i.e. VMIN and VTIME
        yield();
    }
    DEBUG_PRINT("Nextion::recvRetString()" << str.length() << "," << str);
    return ret;
}

/*
 * Receive string data. 
 * 
 * @param buffer - save string data. 
 * @param len - in buffer len / out saved string len excluding null char. 
 * @param timeout - set timeout time. 
 * @param start_flag - is str start flag (0x70) expected, default falue true
 *
 *
 * @retval true - success. 
 * @retval false - failed.  
 *
 */
bool Nextion::recvRetString(char *buffer, uint16_t &len, size_t timeout, bool start_flag)
{
    std::string temp;
    bool ret = recvRetString(temp,timeout, start_flag);

    if(ret && len)
    {
        len=temp.length()>len?len:temp.length();
        strncpy(buffer,temp.c_str(), len);
    }
    return ret;
}

/*
 * Send command to Nextion.
 *
 * @param cmd - the string of command.
 */
void Nextion::sendCommand(const char* cmd) {
    DEBUG_PRINT("Nextion::sendCommand():" << cmd);

    ReadQueuedEvents();
    // empty in buffer for clean responce
    while (m_nexSerial->available())
    {
        m_nexSerial->o_read();
    }
    m_nexSerial->print(cmd);
    m_nexSerial->o_write(0xFF);
    m_nexSerial->o_write(0xFF);
    m_nexSerial->o_write(0xFF);
    // std::cout<<"SendCommand...DONE"<<std::endl;
}

void Nextion::sendRawData(const uint8_t *buf, uint16_t len)
{
    m_nexSerial->o_write(buf, len);
}

void Nextion::sendRawByte(const uint8_t byte)
{
    m_nexSerial->o_write(&byte, 1);
}

size_t Nextion::readBytes(uint8_t* buffer, size_t size, size_t timeout)
{
    unsigned long start{millis()};
    size_t avail{(size_t)m_nexSerial->available()};
    while(size>avail && (millis()-start)<timeout)
    {
        delayMicroseconds(10);
        yield();
        avail=m_nexSerial->available();
    }
    
    size_t read=std::min(size,avail);
    for(size_t i{read}; i;--i)
    {
        *buffer=m_nexSerial->o_read();
        ++buffer;
    }
    return read;
}

bool Nextion::recvCommand(const uint8_t command, size_t timeout)
{
    bool ret = false;
    uint8_t temp[4] = {0};
    ReadQueuedEvents();
    size_t bytesRead = readBytes((uint8_t *)temp, sizeof(temp), timeout);
    if (sizeof(temp) != bytesRead)
    {
        DEBUG_PRINT("Nextion::recvCommand(): recv command timeout");
        ret = false;
    }
    else
    {
        if (temp[0] == command
            && temp[1] == 0xFF
            && temp[2] == 0xFF
            && temp[3] == 0xFF
            )
        {
            ret = true;
        }
        else
        {
            DEBUG_PRINT("Nextion::recvCommand(): recv command err");
        }
    }
    return ret;
}

bool Nextion::recvRetCommandFinished(size_t timeout)
{
    bool ret = recvCommand(NEX_RET_CMD_FINISHED_OK, timeout);
    if (ret) 
    {
        DEBUG_PRINT("Nextion::recvRetCommandFinished(): ok");
    }
    else
    {
        DEBUG_PRINT("Nextion::recvRetCommandFinished(): err");
    }
    return ret;
}

bool Nextion::RecvTransparendDataModeReady(size_t timeout)
{
    DEBUG_PRINT("Nextion::RecvTransparendDataModeReady() requested");

    bool ret = recvCommand(Nex_RET_TRANSPARENT_DATA_READY, timeout);
    if (ret) 
    {
        DEBUG_PRINT("Nextion::RecvTransparendDataModeReady(): ok");
    }
    else
    {
        DEBUG_PRINT("Nextion::RecvTransparendDataModeReady(): err");
    }
    return ret;
}

bool Nextion::RecvTransparendDataModeFinished(size_t timeout)
{
    bool ret = recvCommand(Nex_RET_TRANSPARENT_DATA_FINISHED, timeout);
    if (ret) 
    {
        DEBUG_PRINT("Nextion::RecvTransparendDataModeFinished(): ok");
    }
    else
    {
        DEBUG_PRINT("Nextion::RecvTransparendDataModeFinished(): err");
    }
    return ret;
}

bool Nextion::nexInit(const uint32_t baud)
{
    m_baud=baud;
    DEBUG_PRINT("Nextion::nexInit(): START");
    //((SoftwareSerial*)m_nexSerial)->begin(m_baud); // default baud, it is recommended that do not change defaul baud on Nextion, because it can forgot it on re-start
    dynamic_cast<SoftwareSerial*>(m_nexSerial)->begin(m_baud); // default baud, it is recommended that do not change defaul baud on Nextion, because it can forgot it on re-start
    
    if(!connect())
    {
        if(!findBaud(m_baud))
        {
            ((SoftwareSerial*)m_nexSerial)->begin(NEX_SERIAL_DEFAULT_BAUD);
            return false;
        }
    }
    if(baud!=NEX_SERIAL_DEFAULT_BAUD || baud!=m_baud)
    {
        // change baud to wanted
        char cmd[14];
        sprintf(cmd,"baud=%lu",(unsigned long)baud);
        sendCommand(cmd);
        delay(100);
        ((SoftwareSerial*)m_nexSerial)->begin(baud);
        if(!connect())
        {
            return false;
        }
        m_baud=baud;
    }
    sendCommand("bkcmd=3");
    recvRetCommandFinished();
    sendCommand("page 0");
    bool ret = recvRetCommandFinished();
    return ret;
}

uint32_t Nextion::GetCurrentBaud()
{
    return m_baud;
}

void Nextion::nexLoop(NexTouch *nex_listen_list[])
{
    s_nexSerial.flush();   

    ReadQueuedEvents();
    for(nexQueuedEvent* queued = GetQueuedEvent(); queued; queued = GetQueuedEvent())
    {
        uint8_t *__buffer{queued->event_data};

        switch(__buffer[0])
        {
            case NEX_RET_EVENT_NEXTION_STARTUP:
            {
                if (0x00 == __buffer[1] && 0x00 == __buffer[2] && 0xFF == __buffer[3] && 0xFF == __buffer[4] && 0xFF == __buffer[5])
                {
                    if(nextionStartupCallback!=nullptr)
                    {
                        nextionStartupCallback();
                    }
                }
                break;
            }
            case NEX_RET_EVENT_TOUCH_HEAD:
            {
                if (0xFF == __buffer[4] && 0xFF == __buffer[5] && 0xFF == __buffer[6])
                {
                    NexTouch::iterate(nex_listen_list, __buffer[1], __buffer[2], __buffer[3]);
                }
                break;
            }
            case NEX_RET_CURRENT_PAGE_ID_HEAD:
            {
                if (0xFF == __buffer[2] && 0xFF == __buffer[3] && 0xFF == __buffer[4])
                {
                    if(currentPageIdCallback!=nullptr)
                    {
                        currentPageIdCallback(__buffer[1]);
                    }
                }
                break;
            }
            case NEX_RET_EVENT_POSITION_HEAD:
            case NEX_RET_EVENT_SLEEP_POSITION_HEAD:
            {
                if (0xFF == __buffer[6] && 0xFF == __buffer[7] && 0xFF == __buffer[8])
                {
                    if(__buffer[0] == NEX_RET_EVENT_POSITION_HEAD && touchCoordinateCallback!=nullptr)
                    {
                            
                        touchCoordinateCallback(((int16_t)__buffer[2] << 8) | (__buffer[1]), ((int16_t)__buffer[4] << 8) | (__buffer[3]),__buffer[5]);
                    }
                    else if(__buffer[0] == NEX_RET_EVENT_SLEEP_POSITION_HEAD && touchCoordinateCallback!=nullptr)
                    {
                            
                        touchEventInSleepModeCallback(((int16_t)__buffer[2] << 8) | (__buffer[1]), ((int16_t)__buffer[4] << 8) | (__buffer[3]),__buffer[5]);
                    }
                }
                break;
            }
            case NEX_RET_AUTOMATIC_SLEEP:
            case NEX_RET_AUTOMATIC_WAKE_UP:
            {
                if (0xFF == __buffer[1] && 0xFF == __buffer[2] && 0xFF == __buffer[3])
                {
                    if(__buffer[0]==NEX_RET_AUTOMATIC_SLEEP && automaticSleepCallback!=nullptr)
                    {
                        automaticSleepCallback();
                    }
                    else if(__buffer[0]==NEX_RET_AUTOMATIC_WAKE_UP && automaticWakeUpCallback!=nullptr)
                    {
                        automaticWakeUpCallback();
                    }
                }
                break;
            }
            case NEX_RET_EVENT_NEXTION_READY:
            {
                if(nextionReadyCallback!=nullptr)
                {
                    nextionReadyCallback();
                }
                break;
            }
            case NEX_RET_START_SD_UPGRADE:
            {
                if(startSdUpgradeCallback!=nullptr)
                {
                    startSdUpgradeCallback();
                }
                break;
            }
            default:
            {
                break;              
            }
        }; 
        delete queued;
        ReadQueuedEvents();    
    }

    if(m_nexSerial->available())
    {
        ReadQueuedEvents();
        if(!m_queuedEvents)
        {
            // unnoun data clean buffer.
            uint8_t c = m_nexSerial->o_read();
            while (m_nexSerial->available())
            {
                c=m_nexSerial->o_read();
                yield();
            }
        }
    } 
}