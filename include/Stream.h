#pragma once

#ifndef STREAM_HPP
#define STREAM_HPP

#include <cstddef>
#include <string>
#include <cinttypes>
#include "Print.h"


#define NO_IGNORE_CHAR  '\x01' // a char not found in a valid ASCII numeric field


// This enumeration provides the lookahead options for parseInt(), parseFloat()
// The rules set out here are used until either the first valid character is found
// or a time out occurs due to lack of input.
enum LookaheadMode{
    SKIP_ALL,       // All invalid characters are ignored.
    SKIP_NONE,      // Nothing is skipped, and the stream is not touched unless the first waiting character is valid.
    SKIP_WHITESPACE // Only tabs, spaces, line feeds & carriage returns are skipped.
};

class Stream : public Print {

    protected:
        long parseInt(char ignore) { return parseInt(SKIP_ALL, ignore); }
        float parseFloat(char ignore) { return parseFloat(SKIP_ALL, ignore); }
        struct MultiTarget {
            const char *str;
            std::size_t len;
            std::size_t index;
        };
        int findMulti(struct MultiTarget *targets, int tCount);
        unsigned long _timeout;      // number of milliseconds to wait for the next char before aborting timed read
        unsigned long _startMillis;  // used for timeout measurement
        int timedRead();    // read stream with timeout
        int timedPeek();    // peek stream with timeout
        int peekNextDigit(LookaheadMode lookahead, bool detectDecimal); // returns the next numeric digit in the stream or -1 if timeout

    public:
        Stream();
        ~Stream();
        virtual int available() = 0;
        virtual int o_read() = 0;
        virtual int peek() = 0;

        /*
         * Clearns buffer once all outgoing characters have been sent.
        */
        virtual void flush(void) = 0;

        void setTimeout(unsigned long timeout);  // sets maximum milliseconds to wait for stream data, default is 1 second
        unsigned long getTimeout(void) { return _timeout; }

        bool find(char *target);   // reads data from the stream until the target string is found
        bool find(uint8_t *target) { return find ((char *)target); }
        // returns true if target string is found, false if timed out (see setTimeout)

        bool find(char *target, std::size_t length);   // reads data from the stream until the target string of given length is found
        bool find(uint8_t *target, std::size_t length) { return find ((char *)target, length); }
        // returns true if target string is found, false if timed out

        bool find(char target) { return find (&target, 1); }

        bool findUntil(char *target, char *terminator);   // as find but search ends if the terminator string is found
        bool findUntil(uint8_t *target, char *terminator) { return findUntil((char *)target, terminator); }

        bool findUntil(char *target, std::size_t targetLen, char *terminate, std::size_t termLen);   // as above but search ends if the terminate string is found
        bool findUntil(uint8_t *target, std::size_t targetLen, char *terminate, std::size_t termLen) {return findUntil((char *)target, targetLen, terminate, termLen); }

        long parseInt(LookaheadMode lookahead = SKIP_ALL, char ignore = NO_IGNORE_CHAR);
        // returns the first valid (long) integer value from the current position.
        // lookahead determines how parseInt looks ahead in the stream.
        // See LookaheadMode enumeration at the top of the file.
        // Lookahead is terminated by the first character that is not a valid part of an integer.
        // Once parsing commences, 'ignore' will be skipped in the stream.

        float parseFloat(LookaheadMode lookahead = SKIP_ALL, char ignore = NO_IGNORE_CHAR);
        // float version of parseInt

        std::size_t readBytes( char *buffer, std::size_t length); // read chars from stream into buffer
        std::size_t readBytes( uint8_t *buffer, std::size_t length) { return readBytes((char *)buffer, length); }
        // terminates if length characters have been read or timeout (see setTimeout)
        // returns the number of characters placed in the buffer (0 means no valid data found)

        std::size_t readBytesUntil( char terminator, char *buffer, std::size_t length); // as readBytes with terminator character
        std::size_t readBytesUntil( char terminator, uint8_t *buffer, std::size_t length) { return readBytesUntil(terminator, (char *)buffer, length); }
        // terminates if length characters have been read, timeout, or if the terminator character  detected
        // returns the number of characters placed in the buffer (0 means no valid data found)

        // Arduino String functions to be added here
        std::string readString();
        std::string readStringUntil(char terminator);
};

#endif