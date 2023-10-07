/*
* Eyitope Adelowo (adeyitope.io@gmail.com)
*/

#include "Onion.h"
#include <cstdlib>
#include <bits/stdc++.h>
#include <unistd.h>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <sys/time.h>
#include "helpers.h"

// ÿ

extern unsigned long long GLOBAL_program_start_time;

void delay(unsigned int milliseconds)
{
    DEBUG_PRINT("delay(): " << milliseconds << " seconds...");
	usleep(milliseconds * 1000);
}

void delayMicroseconds(unsigned int seconds)
{
    DEBUG_PRINT("delayMicroseconds():" << seconds << " micro seconds...");
    usleep(seconds);
}

unsigned long millis()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (static_cast<unsigned long long>(tv.tv_sec)*1000 + static_cast<unsigned long long>(tv.tv_usec)/1000) - GLOBAL_program_start_time;
}

void yield(void)
{
	return;
}

char * utoa(unsigned int value, char * str, int radix)
{
	const char * format = nullptr;

	switch(radix)
	{
		case 8:
			format = "%o";
			break;
		case 10:
			format = "%u";
			break;
		case 16:
			format = "%x";
			break;
	}

	if(format == nullptr)
		return str;

	int size = std::sprintf(str, format, value);
	return &str[size];
}

 /* reverse:  reverse string s in place */
 void reverse(char s[])
 {
     int i, j;
     char c;

     for (i = 0, j = std::strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
}

char* itoa(int value, char* str, int radix) {
    static char dig[] =
        "0123456789"
        "abcdefghijklmnopqrstuvwxyz";
    int n = 0, neg = 0;
    unsigned int v;
    char* p, *q;
    char c;

    if (radix == 10 && value < 0) {
        value = -value;
        neg = 1;
    }
    v = value;
    do {
        str[n++] = dig[v%radix];
        v /= radix;
    } while (v);
    if (neg)
        str[n++] = '-';
    str[n] = '\0';

    for (p = str, q = p + (n-1); p < q; ++p, --q)
        c = *p, *p = *q, *q = c;
    return str;
}

void pprint(std::string stuff) { std::cout<<"Debug: "<< stuff << std::endl; }
//void pprint(uint32_t stuff) { std::cout<<"Debug: "<< stuff << std::endl; }
void pprint(uint32_t& stuff) { std::cout<<"pprint: Data type n/a"<< std::endl; }
void pprint(char *stuff) { std::printf("Debug: %s\n", stuff); }
void pprint(int stuff) { std::cout<<"pprint: Data type n/a"<< std::endl; }
void pprint(float stuff) { std::cout<<"pprint: Data type n/a"<< std::endl; }
void pprint(double stuff) { std::cout<<"pprint: Data type n/a"<< std::endl; }
void pprint(std::__cxx11::basic_string<char>::size_type) { std::cout<<"pprint: Data type n/a"<< std::endl; }

/* Signal handler for SIGINT */
void instant_shutdown(int signum)
{
	exit(EXIT_SUCCESS);
}

