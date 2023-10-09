/**
 * @file KnemesisAssets.h
 *
 * Definitions for KnemesisAssets.cpp 
 *
 * @author  Eyitope Adelowo (email:<adeyitope.io@gmail.com>)
 * @date    9/OCT/2023
 * 
 */

#ifndef KNESEMIS_ASSETS_H
#define KNESEMIS_ASSETS_H

enum KnemesisPages {
    SPLASH_SCREEN,
    SCRATCH_PAD,
    NOTIFICATION_PAGE,
    KNEMESIS_HOME
};

void nextion_thread_func(void);
void initialize_nextion(void);


#endif