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
        uint64_t *i;
        uint32_t size;
    public:
        BigInt() {
            BigInt(1);
        }
        BigInt(int size) {
            i = (uint64_t*)calloc(size, sizeof(uint64_t));
        }
        BigInt(const char *str) {
            BigInt(1);
            *i = atoll(str);

            printf("%lld\n", *i);
        }
        ~ BigInt() {
            free(i);
        }
        void resize(int size) {
            this->size = size;
            realloc(i, size * sizeof(uint64_t));
        }
        string operator <<(const BigInt num) {
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
