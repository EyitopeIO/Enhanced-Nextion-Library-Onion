#include "SoftwareSerial.h"
#include "helpers.h"
#include "Nextion.h"
#include <csignal>
#include <thread>
#include <chrono>
#include "Onion.h"
#include <string>


// Logging variable to be defined here

unsigned long long GLOBAL_program_start_time;

#ifndef DISPLAY_UART_PORT
#define DISPLAY_UART_PORT "/dev/ttyS0"
#endif

SoftwareSerial mySerial(DISPLAY_UART_PORT);

Nextion *next = Nextion::GetInstance(mySerial); // software serial

NexPage splash_screen(next, 0, "canvas");

NexTouch *nex_listen_list[] = { &splash_screen, nullptr };

int count = 0;

void splash_screen_callback(void *ptr)
{
    DEBUG_PRINT("splash_screen_callback(): ");
    next->sendCommand("page 3");
}

void nextion_events(void)
{
    DEBUG_PRINT("nextion_events(): Starting nextion_events thread");
    while(1) next->nexLoop(nex_listen_list);
}


int main() {

    std::thread nextion_thread(nextion_events);

    DEBUG_PRINT("main(): Starting program");
    GLOBAL_program_start_time = millis();
    delay(500); // arbitrary number for display to startup
    std::signal(SIGINT, instant_shutdown);
    next->nexInit(static_cast<unsigned int>(115200));
    next->sendCommand("page 0");
    next->sendCommand("vis 255,1");     // Show component on current page
    next->sendCommand("thsp=3");        // Sets internal No-touch-then-sleep timer to 3s
    next->sendCommand("thup=1");        // Sets if Nextion should auto-wake from sleep when touch press occurs to 30s
    next->sendCommand("ussp=30");       // Sets internal No-serial-then-sleep timer to 30s
    next->sendCommand("dims=10");       // Sets internal No-serial-then-sleep timer to 30s

    splash_screen.attachPush(splash_screen_callback);
    splash_screen.attachPop(splash_screen_callback);

    // TODO: Replace with ubus loop
    while(1)
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    return 0;

}