/*
 Print.cpp - Base class that provides print() and println()
 Copyright (c) 2008 David A. Mellis.  All right reserved.
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, o_write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 
 Modified 23 November 2006 by David A. Mellis
 Modified 03 August 2015 by Chuck Todd
 */

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <string>
#include "Onion.h"

#include "Print.h"

// Public Methods //////////////////////////////////////////////////////////////


Print::Print()
{
  write_error = 0;
}

Print::~Print()
{
  std::cout<<"Destroying Print...OK"<<std::endl;
}

/* default implementation: may be overridden */
/* to be called by all other o_write functions */
std::size_t Print::o_write(const uint8_t *buffer, std::size_t size)
{
  std::size_t n = 0;
  while (size--) {
    if (o_write(*buffer++)) n++;
    else break;
  }
  return n;
}

std::size_t Print::o_write(const char *str)
{
  if (str == NULL) return 0;
  return o_write((const uint8_t *)str, std::strlen(str));
}

std::size_t Print::o_write(const char *buffer, std::size_t size)
{
  return o_write((const uint8_t *)buffer, size);
}


std::size_t Print::print(const std::string &s)
{
  return o_write(s.c_str(), s.length());
}

std::size_t Print::print(const char str[])
{
  return o_write(str);
}

std::size_t Print::print(char c)
{
  return o_write(c);
}

std::size_t Print::print(unsigned char b, int base)
{
  return print((unsigned long) b, base);
}

std::size_t Print::print(int n, int base)
{
  return print((long) n, base);
}

std::size_t Print::print(unsigned int n, int base)
{
  return print((unsigned long) n, base);
}

std::size_t Print::print(long n, int base)
{
  if (base == 0) {
    return o_write(n);
  } else if (base == 10) {
    if (n < 0) {
      int t = print('-');
      n = -n;
      return printNumber(n, 10) + t;
    }
    return printNumber(n, 10);
  } else {
    return printNumber(n, base);
  }
}

std::size_t Print::print(unsigned long n, int base)
{
  if (base == 0) return o_write(n);
  else return printNumber(n, base);
}

std::size_t Print::print(double n, int digits)
{
  return printFloat(n, digits);
}

std::size_t Print::print(const Printable& x)
{
  return x.printTo(*this);
}

std::size_t Print::println(void)
{
  return o_write("\r\n");
}

std::size_t Print::println(const std::string &s)
{
  std::size_t n = print(s);
  n += println();
  return n;
}

std::size_t Print::println(const char c[])
{
  std::size_t n = print(c);
  n += println();
  return n;
}

std::size_t Print::println(char c)
{
  std::size_t n = print(c);
  n += println();
  return n;
}

std::size_t Print::println(unsigned char b, int base)
{
  std::size_t n = print(b, base);
  n += println();
  return n;
}

std::size_t Print::println(int num, int base)
{
  std::size_t n = print(num, base);
  n += println();
  return n;
}

std::size_t Print::println(unsigned int num, int base)
{
  std::size_t n = print(num, base);
  n += println();
  return n;
}

std::size_t Print::println(long num, int base)
{
  std::size_t n = print(num, base);
  n += println();
  return n;
}

std::size_t Print::println(unsigned long num, int base)
{
  std::size_t n = print(num, base);
  n += println();
  return n;
}

std::size_t Print::println(double num, int digits)
{
  std::size_t n = print(num, digits);
  n += println();
  return n;
}

std::size_t Print::println(const Printable& x)
{
  std::size_t n = print(x);
  n += println();
  return n;
}

// Private Methods /////////////////////////////////////////////////////////////

std::size_t Print::printNumber(unsigned long n, uint8_t base)
{
  char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
  char *str = &buf[sizeof(buf) - 1];

  *str = '\0';

  // prevent crash if called with base == 1
  if (base < 2) base = 10;

  do {
    char c = n % base;
    n /= base;

    *--str = c < 10 ? c + '0' : c + 'A' - 10;
  } while(n);

  return o_write(str);
}

std::size_t Print::printFloat(double number, uint8_t digits) 
{ 
  std::size_t n = 0;
  
  if (std::isnan(number)) return print("nan");
  if (std::isinf(number)) return print("inf");
  if (number > 4294967040.0) return print ("ovf");  // constant determined empirically
  if (number <-4294967040.0) return print ("ovf");  // constant determined empirically
  
  // Handle negative numbers
  if (number < 0.0)
  {
     n += print('-');
     number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;
  
  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  n += print(int_part);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0) {
    n += print('.'); 
  }

  // Extract digits from the remainder one at a time
  while (digits-- > 0)
  {
    remainder *= 10.0;
    unsigned int toPrint = (unsigned int)(remainder);
    n += print(toPrint);
    remainder -= toPrint; 
  } 
  
  return n;
}
