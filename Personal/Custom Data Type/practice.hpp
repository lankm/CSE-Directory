/* This is a simple implementation of a 32.32 bit fixed point number.
 * The goal of this project of mine is to be able to make a low level
 * implementation of bigDecimal that runs as fast as possible.
 * 
 * Because decimal values exist, signed integers should not be used.
 * They don't inform decimal values about their negativity.
 * 
 * Some methods might be implemented with assembally.
 *
 * Author: Landon Moon
 * In progress
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <string>
#include <iostream>
#include <format>

using namespace std;

class Number
{
    private:
        uint32_t f;
        uint32_t i;
        uint8_t  n : 1;
    public:
        Number()
        {
            f=0;
            i=0;
            n=0;
        }
        Number(const char *str)
        {
            // retrieving decimal bits
            char* point = strchr(str, '.');
            double dec = atof(point);
            f = (uint32_t)(dec*(1<<16)*(1<<16));    // err: small rounding mistake

            // if negative
            if(str[0] == '-')
            {
                // retrieving integer bits. skip '-'
                i = atoll(++str);

                // negative handling
                n = 1;
            }
            else
            {
                // retrieving integer bits
                i = atoll(str);
            }

            printf("adr: %p i: %p\n", &f, &i); // print address values
            printf("num: %d %08lx.%08x\n", n, i, f); // print bit values
        }
        string toString()
        {

            // if negative
            char c = '+';
            if(n)
            {
                c = '-';
            }

            // retrieving decimal value
            double dec = ((double)(f))/(1<<16)/(1<<16);
    
            return format("%c%ld.%9lf\n", c, i, dec);
        }
        Number operator +(const Number num)
        {
            Number temp;
            
            //add

            return temp;
        }
        Number operator -(const Number num)
        {
            Number temp;
            
            //sub

            return temp;
        }
        Number operator *(const Number num)
        {
            Number temp;
            
            //mul

            return temp;
        }
        Number operator /(const Number num)
        {
            Number temp;
            
            //div

            return temp;
        }
};
