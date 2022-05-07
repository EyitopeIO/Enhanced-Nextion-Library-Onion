#include "SoftwareSerial.h"
#include "Nextion.h"
// #include <iostream>
// #include <bits/stdc++.h>
#include <csignal>
#include "Onion.h"
#include <string>

// Logging variable to be defined here

unsigned long long GLOBAL_program_start_time;

SoftwareSerial mySerial("/dev/ttyS0");

Nextion *next = Nextion::GetInstance(mySerial); // software serial

NexPage splash_screen(next, 0, "canvas");

NexTouch *nex_listen_list[] = { &splash_screen, nullptr };

int count = 0;

void splash_screen_callback(void *ptr)
{
    next->sendCommand("page notice");
    std::cout<<"splash screen callback"<<std::endl;
}


int main() {

    std::cout << "BOOT." << std::endl;

    GLOBAL_program_start_time = millis();

    std::signal(SIGINT, instant_shutdown);
    
    next->nexInit(static_cast<unsigned int>(115200));
    // next->sendCommand("page alert");
    next->sendCommand("vis 255,1");     // Show component on current page
    next->sendCommand("thsp=3");        // Sets internal No-touch-then-sleep timer to 3s
    next->sendCommand("thup=1");        // Sets if Nextion should auto-wake from sleep when touch press occurs to 30s
    next->sendCommand("ussp=30");       // Sets internal No-serial-then-sleep timer to 30s
    next->sendCommand("dims=10");       // Sets internal No-serial-then-sleep timer to 30s 

    delay(3000);

    splash_screen.attachPush(splash_screen_callback);
    splash_screen.attachPop(splash_screen_callback);

    while(1)
    {
        next->nexLoop(nex_listen_list);
    }
    
    return 0;

}