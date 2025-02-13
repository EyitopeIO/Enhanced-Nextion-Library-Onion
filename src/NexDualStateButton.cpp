/**
 * @file NexDualStateButton.cpp
 *
 * The implementation of class NexDSButton. 
 *
 * @author  huang xianming (email:<xianming.huang@itead.cc>)
 * @date    2015/11/11
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

#include "NexDualStateButton.h"
#include "NexHardware.h"

NexDSButton::NexDSButton(Nextion *nextion, uint8_t pid, uint8_t cid, const char *name, const NexObject* page)
    :NexTouch(nextion, pid, cid, name, page)
{
}

bool NexDSButton::getValue(uint32_t *number)
{
    std::string cmd = std::string("get ");
    getObjGlobalPageName(cmd);
    cmd += ".val";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexDSButton::setValue(uint32_t number)
{
    char buf[10] = {0};
    std::string cmd;
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".val=";
    cmd += buf;
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

bool NexDSButton::getText(std::string &str)
{
    std::string cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".txt";
    sendCommand(cmd.c_str());
    return recvRetString(str);
}


bool NexDSButton::getText(char *buffer, uint16_t &len)
{
    std::string cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".txt";
    sendCommand(cmd.c_str());
    return recvRetString(buffer,len);
}

bool NexDSButton::setText(const char *buffer)
{
    std::string cmd;
    getObjGlobalPageName(cmd);
    cmd += ".txt=\"";
    cmd += buffer;
    cmd += "\"";
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();    
}

bool NexDSButton::Get_state0_color_bco0(uint32_t *number)
{
    std::string cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".bco0";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexDSButton::Set_state0_color_bco0(uint32_t number)
{
    char buf[10] = {0};
    std::string cmd;
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".bco0=";
    cmd += buf;
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

bool NexDSButton::Get_state1_color_bco1(uint32_t *number)
{
    std::string cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".bco1";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexDSButton::Set_state1_color_bco1(uint32_t number)
{
    char buf[10] = {0};
    std::string cmd;
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".bco1=";
    cmd += buf;
    sendCommand(cmd.c_str());

    return recvRetCommandFinished();
}

bool NexDSButton::Get_font_color_pco(uint32_t *number)
{
    std::string cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".pco";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexDSButton::Set_font_color_pco(uint32_t number)
{
    char buf[10] = {0};
    std::string cmd;
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".pco=";
    cmd += buf;
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

bool NexDSButton::Get_place_xcen(uint32_t *number)
{
    std::string cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".xcen";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexDSButton::Set_place_xcen(uint32_t number)
{
    char buf[10] = {0};
    std::string cmd;
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".xcen=";
    cmd += buf;
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

bool NexDSButton::Get_place_ycen(uint32_t *number)
{
    std::string cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".ycen";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexDSButton::Set_place_ycen(uint32_t number)
{
    char buf[10] = {0};
    std::string cmd;
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".ycen=";
    cmd += buf;
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

bool NexDSButton::getFont(uint32_t *number)
{
    std::string cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".font";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexDSButton::setFont(uint32_t number)
{
    char buf[10] = {0};
    std::string cmd;
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".font=";
    cmd += buf;
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

bool NexDSButton::Get_state0_crop_picc0(uint32_t *number)
{
    std::string cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".picc0";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexDSButton::Set_state0_crop_picc0(uint32_t number)
{
    char buf[10] = {0};
    std::string cmd;
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".picc0=";
    cmd += buf;
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

bool NexDSButton::Get_state1_crop_picc1(uint32_t *number)
{
    std::string cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".picc1";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexDSButton::Set_state1_crop_picc1(uint32_t number)
{
    char buf[10] = {0};
    std::string cmd;
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".picc1=";
    cmd += buf;
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

bool NexDSButton::Get_state0_image_pic0(uint32_t *number)
{
    std::string cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".pic0";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexDSButton::Set_state0_image_pic0(uint32_t number)
{
    char buf[10] = {0};
    std::string cmd;
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".pic0=";
    cmd += buf;
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

bool NexDSButton::Get_state1_image_pic1(uint32_t *number)
{
    std::string cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".pic1";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexDSButton::Set_state1_image_pic1(uint32_t number)
{
    char buf[10] = {0};
    std::string cmd;
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".pic1=";
    cmd += buf;
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}


