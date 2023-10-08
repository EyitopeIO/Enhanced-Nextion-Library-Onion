#include "helpers.h"
#include "Nextion.h"
#include "Onion.h"
#include "KnemesisAssets.h"
#include <csignal>
#include <thread>
#include <chrono>
#include <cstdint>
#include <cstdlib>


// Logging variable to be defined here

std::uint64_t program_start_time = 0;
extern Nextion *next;

void instant_shutdown(int signum)
{
	exit(EXIT_SUCCESS);
}



int main(int argc, char *argv[])
{
    DEBUG_PRINT("main(): Starting program");
    program_start_time = millis();
    std::signal(SIGINT, instant_shutdown);

    initialize_nextion();
    std::thread nextion_thread_var(nextion_thread_func);

    // TODO: Replace with ubus loop
    
    while(1) std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    return 0;
}