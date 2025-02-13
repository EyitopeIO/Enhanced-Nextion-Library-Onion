/**
 * @file NexRtc.cpp
 *
 * The implementation of class NexRtc. 
 *
 * @author  Wu Pengfei (email:<pengfei.wu@itead.cc>)
 * @date    2015/8/13
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
#include "NexRtc.h"
#include "NexHardware.h"

NexRtc::NexRtc(Nextion *nextion):NextionIf(nextion)
{}

NexRtc::~NexRtc()
{}

bool NexRtc::write_rtc_time(char *time)
{
    char year[5],mon[3],day[3],hour[3],min[3],sec[3];
    std::string cmd = std::string("rtc");
    
    if(strlen(time) >= 19)
    {
        year[0]=time[0];year[1]=time[1];year[2]=time[2];year[3]=time[3];year[4]='\0';
        mon[0]=time[5];mon[1]=time[6];mon[2]='\0';
        day[0]=time[8];day[1]=time[9];day[2]='\0';
        hour[0]=time[11];hour[1]=time[12];hour[2]='\0';
        min[0]=time[14];min[1]=time[15];min[2]='\0';
        sec[0]=time[17];sec[1]=time[18];sec[2]='\0';
        
        cmd += "0=";
        cmd += year;
        sendCommand(cmd.c_str()); 
        if(!recvRetCommandFinished())
        {
            return false;
        }
        
        cmd = "";
        cmd += "rtc1=";
        cmd += mon;
        sendCommand(cmd.c_str());
        if(!recvRetCommandFinished())
        {
            return false;
        }
        
        cmd = "";
        cmd += "rtc2=";
        cmd += day;
        sendCommand(cmd.c_str());
        if(!recvRetCommandFinished())
        {
            return false;
        }
        
        cmd = "";
        cmd += "rtc3=";
        cmd += hour;
        sendCommand(cmd.c_str());
        if(!recvRetCommandFinished())
        {
            return false;
        }
        
        cmd = "";
        cmd += "rtc4=";
        cmd += min;
        sendCommand(cmd.c_str());
        if(!recvRetCommandFinished())
        {
            return false;
        }
        
        cmd = "";
        cmd += "rtc5=";
        cmd += sec;
        sendCommand(cmd.c_str());
        if(!recvRetCommandFinished())
        {
            return false;
        }
        
    }
    else
    {
        return false;
    }
    return true;
}

bool NexRtc::write_rtc_time(uint32_t *time)
{
    char year[5],mon[3],day[3],hour[3],min[3],sec[3];
    std::string cmd = std::string("rtc");
    
     utoa(time[0],year,10);
     utoa(time[1],mon, 10);
     utoa(time[2],day, 10);
     utoa(time[3],hour,10);
     utoa(time[4],min, 10);
     utoa(time[5],sec, 10);
        
        
     cmd += "0=";
     cmd += year;
     sendCommand(cmd.c_str()); 
     if(!recvRetCommandFinished())
     {
         return false;
     }
        
     cmd = "";
     cmd += "rtc1=";
     cmd += mon;
     sendCommand(cmd.c_str());
     if(!recvRetCommandFinished())
     {
         return false;
     }
        
     cmd = "";
     cmd += "rtc2=";
     cmd += day;
     sendCommand(cmd.c_str());
     if(!recvRetCommandFinished())
     {
         return false;
     }
        
     cmd = "";
     cmd += "rtc3=";
     cmd += hour;
     sendCommand(cmd.c_str());
     if(!recvRetCommandFinished())
     {
         return false;
     }
        
     cmd = "";
     cmd += "rtc4=";
     cmd += min;
     sendCommand(cmd.c_str());
     if(!recvRetCommandFinished())
     {
         return false;
     }
        
     cmd = "";
     cmd += "rtc5=";
     cmd += sec;
     sendCommand(cmd.c_str());
     if(!recvRetCommandFinished())
     {
         return false;
     }
     return true;
}

bool NexRtc::write_rtc_time(char *time_type,uint32_t number)
{
    std::string cmd = std::string("rtc");
    char buf[10] = {0};
    
    utoa(number, buf, 10);
    if(strstr(time_type,"year"))
    {
        cmd += "0=";
        cmd += buf;
    }
    if(strstr(time_type,"mon"))
    {
        cmd += "1=";
        cmd += buf;
    }
    if(strstr(time_type,"day"))
    {
        cmd += "2=";
        cmd += buf;
    }
    if(strstr(time_type,"hour"))
    {
        cmd += "3=";
        cmd += buf;
    }
    if(strstr(time_type,"min"))
    {
        cmd += "4=";
        cmd += buf;
    }
    if(strstr(time_type,"sec"))
    {
        cmd += "5=";
        cmd += buf;
    }
    
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

bool NexRtc::read_rtc_time(char *time,uint32_t len)
{
    char time_buf[22] = {"0000/00/00 00:00:00 0"};
    uint32_t year,mon,day,hour,min,sec,week;
    std::string cmd;
    
    cmd = "get rtc0";
    sendCommand(cmd.c_str());
    if(!recvRetNumber(&year))
    {
        return false;
    }
    
    cmd = "";
    cmd = "get rtc1";
    sendCommand(cmd.c_str());
    if(!recvRetNumber(&mon))
    {
        return false;
    }    
    
    cmd = "";
    cmd = "get rtc2";
    sendCommand(cmd.c_str());
    if(!recvRetNumber(&day))
    {
        return false;
    }   
    
    cmd = "";
    cmd = "get rtc3";
    sendCommand(cmd.c_str());
    if(!recvRetNumber(&hour))
    {
        return false;
    } 

    cmd = "";
    cmd = "get rtc4";
    sendCommand(cmd.c_str());
    if(!recvRetNumber(&min))
    {
        return false;
    } 
    
    cmd = "";
    cmd = "get rtc5";
    sendCommand(cmd.c_str());
    if(!recvRetNumber(&sec))
    {
        return false;
    }    
    
    cmd = "";
    cmd = "get rtc6";
    sendCommand(cmd.c_str());
    if(!recvRetNumber(&week))
    {
        return false;
    }    
    
    time_buf[0] = year/1000 + '0';
    time_buf[1] = (year/100)%10 + '0';
    time_buf[2] = (year/10)%10 + '0';
    time_buf[3] = year%10 + '0';
    time_buf[5] = mon/10 + '0';
    time_buf[6] = mon%10 + '0';
    time_buf[8] = day/10 + '0';
    time_buf[9] = day%10 + '0';
    time_buf[11] = hour/10 + '0';
    time_buf[12] = hour%10 + '0';
    time_buf[14] = min/10 + '0';
    time_buf[15] = min%10 + '0';
    time_buf[17] = sec/10 + '0';
    time_buf[18] = sec%10 + '0';
    time_buf[20] = week + '0';
    time_buf[21] = '\0';
    
    if(len >= 22)
    {
        for(int i=0;i<22;i++)
        {
            time[i] = time_buf[i];
        }
    }
    else{
        for(uint32_t i=0;i<len;i++)
        {
            time[i] = time_buf[i];
        }
    }   
  return true;
}

bool NexRtc::read_rtc_time(uint32_t *time,uint32_t len)
{
    uint32_t time_buf[7] = {0};
    std::string cmd;
    
    cmd = "get rtc0";
    sendCommand(cmd.c_str());
    if(!recvRetNumber(&time_buf[0]))
    {
        return false;
    }
    
    cmd = "";
    cmd = "get rtc1";
    sendCommand(cmd.c_str());
    if(!recvRetNumber(&time_buf[1]))
    {
        return false;
    }
    
    cmd = "";
    cmd = "get rtc2";
    sendCommand(cmd.c_str());
    if(!recvRetNumber(&time_buf[2]))
    {
        return false;
    }
    
    cmd = "";
    cmd = "get rtc3";
    sendCommand(cmd.c_str());
    if(!recvRetNumber(&time_buf[3]))
    {
        return false;
    }
    
    cmd = "";
    cmd = "get rtc4";
    sendCommand(cmd.c_str());
    if(!recvRetNumber(&time_buf[4]))
    {
        return false;
    }
    
    cmd = "";
    cmd = "get rtc5";
    sendCommand(cmd.c_str());
    if(!recvRetNumber(&time_buf[5]))
    {
        return false;
    }

    cmd = "";
    cmd = "get rtc6";
    sendCommand(cmd.c_str());
    if(!recvRetNumber(&time_buf[6]))
    {
        return false;
    }    

    for(uint32_t i=0;i<len;i++)
    {
       time[i] = time_buf[i];
    }
    return true;
}


bool NexRtc::read_rtc_time(char *time_type,uint32_t *number)
{
    std::string cmd = std::string("get rtc");
    
    if(strstr(time_type,"year"))
    {
        cmd += '0';
    }
    else if(strstr(time_type,"mon"))
    {
        cmd += '1';
    }
    else if(strstr(time_type,"day"))
    {
        cmd += '2';
    }
    else if(strstr(time_type,"hour"))
    {
        cmd += '3';
    }
    else if(strstr(time_type,"min"))
    {
        cmd += '4';       
    }
    else if(strstr(time_type,"sec"))
    {
        cmd += '5';
    }
    else if(strstr(time_type,"week"))
    {
        cmd += '6';
    }
    else{
        return false;
    }
    
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}