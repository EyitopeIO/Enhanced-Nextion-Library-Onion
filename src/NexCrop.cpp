/**
 * @file NexCrop.cpp
 *
 * The implementation of class NexCrop. 
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

#include "NexCrop.h"
#include "NexHardware.h"

NexCrop::NexCrop(Nextion *nextion, uint8_t pid, uint8_t cid, const char *name, const NexObject* page)
    :NexTouch(nextion, pid, cid, name, page)
{
}

bool NexCrop::Get_background_crop_picc(uint32_t *number)
{
    std::string cmd = std::string("get ");
    getObjGlobalPageName(cmd);
    cmd += ".picc";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexCrop::Set_background_crop_picc(uint32_t number)
{
    char buf[10] = {0};
    std::string cmd;
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".picc=";
    cmd += buf;
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

bool NexCrop::getPic(uint32_t *number)
{
    std::string cmd = std::string("get ");
    getObjGlobalPageName(cmd);
    cmd += ".picc";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexCrop::setPic(uint32_t number)
{
    char buf[10] = {0};
    std::string cmd;
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".picc=";
    cmd += buf;
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

