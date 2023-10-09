/**
 * @file Onion.h
 *
 * Arduino-like functions and other definitions for the Linux
 *
 * @author  Eyitope Adelowo (email:<adeyitope.io@gmail.com>)
 * @date    9/OCT/2023
 * 
 */
#ifndef ONION_H
#define ONION_H

#include <unistd.h>
#include <cstdlib>
#include <cstddef>
#include <cinttypes>
#include <sys/types.h>
#include <cstdint>
#include <string>
#include <iostream>

/*
 * "NEVER include <bits/termios-baud.h> directly; use <termios.h> instead."
*/

#define __MAX_BAUD B4000000

// #define dbSerialPrintln(a)  do{(void)(a);}while(0)
// #define dbSerialPrint(a)  do{(void)(a);}while(0)

#define OMEGA_2S_UART_BUFFER_SIZE 16

#ifndef DISPLAY_UART_PORT
#define DISPLAY_UART_PORT "/dev/ttyS0"
#endif

#ifndef DISPLAY_UART_BAUD
#define DISPLAY_UART_BAUD 9600
#endif

#define dbSerialPrintln(a)  pprint(a)
#define dbSerialPrint(a)  pprint(a)

void yield(void);
void delay(unsigned int seconds);
unsigned long millis();
void delayMicroseconds(unsigned int seconds);
// ssize_t min(ssize_t a, ssize_t b);
// ssize_t max(ssize_t a, ssize_t b);

void instant_shutdown(int signum);

void reverse(char s[]);
char * utoa(unsigned int value, char * str, int radix);
char *itoa(int value, char *str, int base);

void pprint(std::string stuff);
void pprint(uint32_t& stuff);
void pprint(int stuff);
void pprint(double stuff);

#endif