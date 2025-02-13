/**
 * @file NexTimer.cpp
 *
 * The implementation of class NexTimer. 
 *
 * @author  huang xianming (email:<xianming.huang@itead.cc>)
 * @date    2015/8/26
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

#include "NexTimer.h"
#include "NexHardware.h"

NexTimer::NexTimer(Nextion *nextion, uint8_t pid, uint8_t cid, const char *name, const NexObject* page)
    :NexTouch(nextion, pid, cid, name, page)
{
}

void NexTimer::attachTimer(NexTouchEventCb timer, void *ptr)
{
    NexTouch::attachPop(timer, ptr);
}

void NexTimer::detachTimer(void)
{
    NexTouch::detachPop();
}

bool NexTimer::getCycle(uint32_t *number)
{
    std::string cmd = std::string("get ");
    getObjGlobalPageName(cmd);
    cmd += ".tim";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexTimer::setCycle(uint32_t number)
{
    char buf[10] = {0};
    std::string cmd;
    if (number < 50)
    {
        number = 50;
    }
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".tim=";
    cmd += buf;
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}


bool NexTimer::enable(void)
{
    char buf[10] = {0};
    std::string cmd;
    utoa(1, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".en=";
    cmd += buf;
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

bool NexTimer::disable(void)
{
    char buf[10] = {0};
    std::string cmd;
    utoa(0, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".en=";
    cmd += buf;
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

bool NexTimer::Get_cycle_tim(uint32_t *number)
{
    std::string cmd = std::string("get ");
    getObjGlobalPageName(cmd);
    cmd += ".tim";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexTimer::Set_cycle_tim(uint32_t number)
{
    char buf[10] = {0};
    std::string cmd;
    if (number < 8)
    {
        number = 8;
    }
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".tim=";
    cmd += buf;
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

