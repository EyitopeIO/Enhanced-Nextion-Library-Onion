/*
* Eyitope Adelowo (adeyitope.io@gmail.com)
*/

#pragma once

#ifndef SOFTWARESERIAL_HPP
#define SOFTWARESERIAL_HPP

#include "Stream.h"
#include "Onion.h"
#include <termios.h>
#include <mutex>
#include <memory>

#define ONION_UART_SIZE 16


/*
* Implementation gotten from Embedded Artistry
* https://embeddedartistry.com/blog/2017/05/17/creating-a-circular-buffer-in-c-and-c/
*
*/
template <class T>
class SoftUART_Q
{
    private:
        std::mutex mutex_;      // For thread safety
        std::unique_ptr<T[]> buf_;
        size_t head_ = 0;
        size_t tail_ = 0;
        const size_t max_size_;
        bool full_ = 0;

    public:
        SoftUART_Q(size_t size);
        ~SoftUART_Q();
        void push(T item);
        T pop(void);
        T head(void);
        T tail(void);
        void reset(void);
        bool empty(void) const;
        bool full(void) const;
        size_t capacity(void) const;
        size_t size(void) const; 
};

/*
* This class is supposed to be used with the uint8_t data type even thought its a template class.
* It won't be tested with other data types.
* 
* The class attempts to replicate Arduino's SoftwareSerial library. See that libraries interface
* to understand how this one works. 
* nxread() and o_read() is what differs. See the comments for these.
*/
class SoftwareSerial: public Stream {

    public:

        explicit SoftwareSerial(const char* port);
        ~SoftwareSerial();

        /*
        * Instantiate the serial port
        * @param speed: The baudrate in the form "B<baudrate>"
        */
        void begin(unsigned int speed);

        virtual int available(void);    // This and next two override from Steam.
        virtual int peek(void);
        virtual void flush(void);

        /*
        * Equivalent to Arduino's read. Overrides from the Steam class
        * @return: data from the serial port.
        */
        virtual int o_read(void) override;

    private:

        SoftUART_Q<uint8_t> *ouart;     // Points to the circular buffer used for incoming serial data.
        
        /*
        * Serial port stuff here
        */
        unsigned int baudrate;    
        const char *serial_port;
        int o_fd;
        struct termios tty; 

        /*
        * Calls the Linux read() method to get data from the serial port (UART)
        * and keep in a temporary buffer. Onion's buffer is 16 bytes.
        */
        void nxread(void);

        std::size_t o_write(const uint8_t *buffer, std::size_t size) override;      // Overrides from Print.
        std::size_t o_write(uint8_t chr);

};



#endif