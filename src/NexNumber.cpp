/**
 * @file NexNumber.cpp
 *
 * The implementation of class NexNumber. 
 *
 * @author  huang xianming (email:<xianming.huang@itead.cc>)
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
#include "NexNumber.h"
#include "NexHardware.h"

NexNumber::NexNumber(Nextion *nextion, uint8_t pid, uint8_t cid, const char *name, const NexObject* page)
    :NexTouch(nextion, pid, cid, name, page)
{
}

bool NexNumber::getValue(uint32_t *number)
{
    std::string cmd = std::string("get ");
    getObjGlobalPageName(cmd);
    cmd += ".val";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexNumber::setValue(uint32_t number)
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

bool NexNumber::Get_background_color_bco(uint32_t *number)
{
    std::string cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".bco";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexNumber::Set_background_color_bco(uint32_t number)
{
    char buf[10] = {0};
    std::string cmd;
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".bco=";
    cmd += buf;
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

bool NexNumber::Get_font_color_pco(uint32_t *number)
{
    std::string cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".pco";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexNumber::Set_font_color_pco(uint32_t number)
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

bool NexNumber::Get_place_xcen(uint32_t *number)
{
    std::string cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".xcen";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexNumber::Set_place_xcen(uint32_t number)
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

bool NexNumber::Get_place_ycen(uint32_t *number)
{
    std::string cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".ycen";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexNumber::Set_place_ycen(uint32_t number)
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

bool NexNumber::getFont(uint32_t *number)
{
    std::string cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".font";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexNumber::setFont(uint32_t number)
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

bool NexNumber::Get_number_lenth(uint32_t *number)
{
    std::string cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".lenth";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexNumber::Set_number_lenth(uint32_t number)
{
    char buf[10] = {0};
    std::string cmd;
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".lenth=";
    cmd += buf;
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

bool NexNumber::Get_background_crop_picc(uint32_t *number)
{
    std::string cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".picc";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexNumber::Set_background_crop_picc(uint32_t number)
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

bool NexNumber::Get_background_image_pic(uint32_t *number)
{
    std::string cmd = std::string("get ");
    getObjGlobalPageName(cmd);
    cmd += ".pic";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexNumber::Set_background_image_pic(uint32_t number)
{
    char buf[10] = {0};
    std::string cmd;
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".pic=";
    cmd += buf;
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}