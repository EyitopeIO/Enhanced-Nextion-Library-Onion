/*
* Eyitope Adelowo (adeyitope.io@gmail.com)
*/


#include "SoftwareSerial.h"
#include <fcntl.h> // Contains file controls like O_RDWR
#include <termios.h> // Contains POSIX terminal control definitions
#include <iostream>


SoftwareSerial::SoftwareSerial(const char* port) : serial_port(port) {
    ouart = new SoftUART_Q<uint8_t>(ONION_UART_SIZE);
}

SoftwareSerial::~SoftwareSerial() {
    if (close(o_fd) == 0) {
        std::cout<<"Destroying SoftwareSerial...OK"<<std::endl;
    }
    else {
        std::cout<<"Destroying SoftwareSerial FAILED"<<std::endl;
    }
}

void SoftwareSerial::begin(unsigned int speed) 
{
    unsigned int speedCode = 0;
    int fd = -1;
    
    switch(speed)
    {
        case 9600:
            speedCode=B9600;
            break;
        case 115200:
            speedCode=B115200;
            break;
    }
    if (speedCode == 0)
    {
        std::exit(EXIT_FAILURE);
    }
    std::cout<<"Nextion port: "<<serial_port<<std::endl;
    std::cout<<"Nextion speed: "<<speed<<std::endl;
    if ((fd = open(serial_port, O_RDWR | O_NOCTTY)) == -1)
    {
        std::cout<< "begin():Serial port did not open" << std::endl;
        std::exit(EXIT_FAILURE);  
    }
    if (tcgetattr(fd, &tty) >= 0) {
        /* Set the terminal to be "raw" */
        tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
        tty.c_oflag &= ~OPOST;
        tty.c_lflag &= ~(ECHO | ECHONL | ISIG | IEXTEN);
        tty.c_lflag &= ~ICANON;
        tty.c_cflag &= ~(CSIZE | PARENB);
        tty.c_cflag |= CS8;
        tty.c_cc[VTIME] = 0;    // i.e. 1 == 100ms, 2 == 200ms,...10 == 1000ms
        tty.c_cc[VMIN] = 1;     // smallest number of characters that can be read
        cfsetspeed(&tty, speedCode);
        if (tcsetattr(fd, TCSAFLUSH, &tty) == -1) {
            std::cout<<"begin(): serial attributes not set."<<std::endl;
            std::exit(EXIT_FAILURE);
        }        
        this->o_fd = fd;
        std::cout<<"begin...OK "<<o_fd<<std::endl;
        return;  
    }
    else exit(EXIT_FAILURE);
}

std::size_t SoftwareSerial::o_write(const uint8_t *buffer, std::size_t size)
{
    return write(o_fd, buffer, size);
}

std::size_t SoftwareSerial::o_write(uint8_t chr)
{
    return write(o_fd, &chr, sizeof(chr));
}

void SoftwareSerial::nxread(void)
{
    // Onion Serial port is 16 bytes
    static char in[16];
    static ssize_t br;

    br = read(o_fd, in, sizeof(in));
    if (br > 0)
    {
        std::cout<< br << " bytes. in: " << in <<std::endl;
        for (int i = 0; i < br; i++) ouart->push(static_cast<uint8_t>(in[i]));
    }
}

int SoftwareSerial::o_read(void)
{
    int k = ouart->pop();
    std::cout << "o_read: "<< k << std::endl;
    return k;
}

void SoftwareSerial::flush(void)
{
    // static int i = 0;
    // std::cout << "flush called " << i++ << std::endl;
    this->nxread();
}

int SoftwareSerial::available(void)
{
    // size_t n = ouart->size();
    // {
    //     std::cout << n << " bytes available for reading." << std::endl;
    // }
    return ouart->size();
}

int SoftwareSerial::peek(void) 
{
   return ouart->tail();
}


/* ****************************************************************************** */

template <class T>
SoftUART_Q<T>::SoftUART_Q(size_t size) : buf_(new T[size]), max_size_(size) {};

template <class T>
void SoftUART_Q<T>::reset() {
	std::lock_guard<std::mutex> lock(mutex_);
	head_ = tail_;
	full_ = false;
}

template <class T>
bool SoftUART_Q<T>::empty() const {
    return (!full_ && (head_ == tail_));
}

template <class T>
bool SoftUART_Q<T>::full() const {
    return full_;
}

template <class T>
size_t SoftUART_Q<T>::capacity() const {
    return max_size_;
}

template <class T>
size_t SoftUART_Q<T>::size() const {
	size_t size = max_size_;

	if(!full_)
	{
		if(head_ >= tail_)
		{
			size = head_ - tail_;
		}
		else
		{
			size = max_size_ + head_ - tail_;
		}
	}

	return size;
}

template <class T>
void SoftUART_Q<T>::push(T item) {
	std::lock_guard<std::mutex> lock(mutex_);

	buf_[head_] = item;

	if(full_)
	{
		tail_ = (tail_ + 1) % max_size_;
	}

	head_ = (head_ + 1) % max_size_;

	full_ = head_ == tail_;
}

template <class T>
T SoftUART_Q<T>::pop(void) {

	std::lock_guard<std::mutex> lock(mutex_);
	if(empty())
	{
		return char();
	}

	//Read data and advance the tail (we now have a free space)
	auto val = buf_[tail_];
	full_ = false;
	tail_ = (tail_ + 1) % max_size_;

	return val;
}

template <class T>
T SoftUART_Q<T>::head(void) {
    return buf_[head_];
}

template <class T>
T SoftUART_Q<T>::tail(void) {
    return buf_[tail_];
}
