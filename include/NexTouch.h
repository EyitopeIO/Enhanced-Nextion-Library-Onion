/**
 * @file NexTouch.h
 *
 * The definition of class NexTouch. 
 *
 * @author Wu Pengfei (email:<pengfei.wu@itead.cc>)
 * @date 2015/8/13
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

#pragma once

#include "NexObject.h"
#include <string>

class Nextion;

/**
 * @addtogroup TouchEvent 
 * @{ 
 */

/**
 * Push touch event occuring when your finger or pen coming to Nextion touch pannel. 
 */
#define NEX_EVENT_PUSH  (0x01)
/**
 * Pop touch event occuring when your finger or pen leaving from Nextion touch pannel. 
 */
#define NEX_EVENT_POP   (0x00)  

/**
 * Type of callback funciton when an touch event occurs. 
 * 
 * @param ptr - user pointer for any purpose. Commonly, it is a pointer to a object. 
 * @return none. 
 */
typedef void (*NexTouchEventCb)(void *ptr);

/**
 * Father class of the components with touch events.  
 *
 * Derives from NexObject and provides methods allowing user to attach
 * (or detach) a callback function called when push(or pop) touch event occurs.
 */
class NexTouch: public NexObject
{

    NexTouch()=delete;

public: /* static methods */    
    static void iterate(NexTouch **list, uint8_t pid, uint8_t cid, uint8_t event);

public: /* methods */

    /**
     * @copydoc NexObject::NexObject(Nextion*, uint8_t, uint8_t, const char*, const NexObject*)
     */
    NexTouch(Nextion *nextion, uint8_t pid, uint8_t cid, const char *name, const NexObject* page=nullptr);

    /**
     * Attach an callback function of push touch event. 
     *
     * @param push - callback called with ptr when a push touch event occurs. 
     * @param ptr - parameter passed into push[default:nullptr]. 
     * @return none. 
     *
     * @note If calling this method multiply, the last call is valid. 
     */
    virtual void attachPush(NexTouchEventCb push, void *ptr = nullptr);

    /**
     * Detach an callback function. 
     * 
     * @return none. 
     */
    void detachPush(void);

    /**
     * Attach an callback function of pop touch event. 
     *
     * @param pop - callback called with ptr when a pop touch event occurs. 
     * @param ptr - parameter passed into pop[default:nullptr]. 
     * @return none. 
     *
     * @note If calling this method multiply, the last call is valid. 
     */
    void attachPop(NexTouchEventCb pop, void *ptr = nullptr);

    /**
     * Detach an callback function. 
     * 
     * @return none. 
     */
    void detachPop(void);
    
private: /* methods */ 
    void push(void);
    void pop(void);
    
private: /* data */ 
    NexTouchEventCb __cb_push;
    void *__cbpush_ptr;
    NexTouchEventCb __cb_pop;
    void *__cbpop_ptr;
};

/**
 * @}
 */
