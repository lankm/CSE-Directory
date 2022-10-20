/* This is a low level implementation of a uint32 array big int.
 * 
 * BigInt(const char*) is only a basic implemtation.
 * 
 * Author: Landon Moon
 * In progress.
 */

#include <iostream>
#include <algorithm>

using namespace std;

class BigInt
{
    private:
        uint32_t *i;
        uint32_t size;
    public:
        BigInt() {
            BigInt(1);
        }
        BigInt(int size) {
            i = (uint32_t*)calloc(size, sizeof(uint32_t));
        }
        BigInt(const char *str) {
            BigInt(1);
            *i = atoi(str);

            printf("%lld\n", *i);
        }
        ~ BigInt() {
            free(i);
        }
        void resize(int size) {
            
        }
        string toString() { //replace with << overload
            return "Not implemented";
        }
        BigInt operator +(const BigInt num) {
            BigInt temp = BigInt();
            
            //add

            return temp;
        }
        BigInt operator -(const BigInt num) {
            BigInt temp;
            
            //sub

            return temp;
        }
        BigInt operator *(const BigInt num)
        {
            BigInt temp;
            
            //mul

            return temp;
        }
};
