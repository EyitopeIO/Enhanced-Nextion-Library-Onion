/**
 * @file NexButton.cpp
 *
 * The implementation of class NexButton. 
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
 * 
*/

#include "NexButton.h"
//#include "NexHardware.h"



NexButton::NexButton(Nextion *nextion, uint8_t pid, uint8_t cid, const char *name, const NexObject* page)
    :NexTouch(nextion, pid, cid, name, page)
{
}

bool NexButton::getText(std::string &str)
{
    std::string cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".txt";
    sendCommand(cmd.c_str());
    return recvRetString(str);
}


bool NexButton::getText(char *buffer, uint16_t &len)
{
    std::string cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".txt";
    sendCommand(cmd.c_str());
    return recvRetString(buffer,len);
}

bool NexButton::setText(const char *buffer)
{
    std::string cmd;
    getObjGlobalPageName(cmd);
    cmd += ".txt=\"";
    cmd += buffer;
    cmd += "\"";
    sendCommand(cmd.c_str());
    return recvRetCommandFinished(500);
}


bool NexButton::Get_background_color_bco(uint32_t *number)
{
    std::string cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".bco";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexButton::Set_background_color_bco(uint32_t number)
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

bool NexButton::Get_press_background_color_bco2(uint32_t *number)
{
    std::string cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".bco2";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexButton::Set_press_background_color_bco2(uint32_t number)
{
    char buf[10] = {0};
    std::string cmd;
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".bco2=";
    cmd += buf;
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

bool NexButton::Get_font_color_pco(uint32_t *number)
{
    std::string cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".pco";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexButton::Set_font_color_pco(uint32_t number)
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

bool NexButton::Get_press_font_color_pco2(uint32_t *number)
{
    std::string cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".pco2";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexButton::Set_press_font_color_pco2(uint32_t number)
{
    char buf[10] = {0};
    std::string cmd;
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".pco2=";
    cmd += buf;
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

bool NexButton::Get_place_xcen(uint32_t *number)
{
    std::string cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".xcen";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexButton::Set_place_xcen(uint32_t number)
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

bool NexButton::Get_place_ycen(uint32_t *number)
{
    std::string cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".ycen";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexButton::Set_place_ycen(uint32_t number)
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

bool NexButton::getFont(uint32_t *number)
{
    std::string cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".font";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexButton::setFont(uint32_t number)
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

bool NexButton::Get_background_cropi_picc(uint32_t *number)
{
    std::string cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".picc";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexButton::Set_background_crop_picc(uint32_t number)
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

bool NexButton::Get_press_background_crop_picc2(uint32_t *number)
{
    std::string cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".picc2";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexButton::Set_press_background_crop_picc2(uint32_t number)
{
	char buf[10] = {0};
    std::string cmd;
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".picc2=";
    cmd += buf;
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

bool NexButton::Get_background_image_pic(uint32_t *number)
{
    std::string cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".pic";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexButton::Set_background_image_pic(uint32_t number)
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

bool NexButton::Get_press_background_image_pic2(uint32_t *number)
{
    std::string cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".pic2";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexButton::Set_press_background_image_pic2(uint32_t number)
{
    char buf[10] = {0};
    std::string cmd;
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".pic2=";
    cmd += buf;
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}
