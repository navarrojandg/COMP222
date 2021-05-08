#include <stdio.h>
#include <math.h>

// helper function to help visualize IEEE Bits
void printBits(unsigned x) {
    for (signed i = 31; i > -1; i--) {
        if (i == 30 || i == 22) { printf(" "); };
        (x & (1 << i)) ? printf("1") : printf("0");
    };
    printf("\n");
};

//----------------------------
// Part 1:  IEEE to Float
//----------------------------
double getFraction(unsigned x) {
    // 0 00000000 00000000000000000000000
    // 0 00000000 11111111111111111111111
    // 0x007FFFFF
    // mask to extract bits 0-22

    unsigned mantissa = x & 0x7FFFFF; // isolate the mantissa bits
    double acc = 1.0;
    double j = 0.5;
    for (signed i = 22; i > -1; i--, j /= 2) {
        if ((mantissa & (1 << i))) { acc += j; }; // if bit is 1 then we add j to the accumulator;
    };

    return acc;
};

int getExponent(unsigned x) {
    // 0 00000000 00000000000000000000000
    // 0 11111111 00000000000000000000000
    // 0x7F800000
    // mask to extract bits 23-30

    unsigned exponent = x & 0x7F800000; // isolate the exponent bits;
    int acc = 0;
    int j = 1;
    for (signed i = 23; i < 31; i++, j *= 2) {
        if ((exponent & (1 << i))) { acc += j; }; // if bit is 1 then we add j to the accumulator;
    };

    return acc - 127;
};

double getFloat(unsigned x) {
    double acc = getFraction(x) * (pow(2, getExponent(x))); 
    return (x & (1 << 31)) ? (acc * -1) : acc; // handle the sign before returning acc
};

//----------------------------------
// Part 2:  Float to IEEE
//----------------------------------

int getNormexp(double x) {
    return (int)(floor(log(x)/log(2)));
};

double getNormfrac(double x) {
    return x / pow(2,getNormexp(x));
};

unsigned getBinfrac(double x) {
    double normFrac = getNormfrac(x) - 1; // get normalized fraction and remove the leading 1;
    unsigned acc = 0x0;
    for (int i = 0; i < 22; i++, acc = acc << 1) {// add 1 to the acc if needed and shift the bits each increment;
        normFrac *= 2;
        if (floor(normFrac) == 1) {
            acc += 0x1;
            normFrac -= 1;
        };
    };
    return acc;
};

unsigned getBinexp(double x) {
    unsigned normExp = getNormexp(x) + 127;
    return normExp << 23;
};

unsigned getIEEE(double x) {
    unsigned acc = 0x0;
    if (x < 0) { acc += (1 << 31); }; // sign bit;
    x = fabs(x); // we use fabs because we already dealt with the sign bit;
    acc += getBinexp(x); 
    acc += getBinfrac(x);
    return acc;
};

//-------------------------------
// Part 3: test cases and driver
//-------------------------------

void testPart1() {
    printf("%f\n",getFloat(0x43580000)); // answer = 216.0
    printf("%f\n",getFloat(0x44FA0000)); // answer = 2000.0
    printf("%f\n",getFloat(0x45002000)); // answer = 2050.0
    printf("%f\n",getFloat(0x47A60400)); // answer = 85000.0
};

void testPart2() {
    printf("%x\n",getIEEE(216.0)); // answer = 0x43580000
    printf("%x\n",getIEEE(440.0)); // answer = 0x43dc0000
    printf("%x\n",getIEEE(53.0));  // answer = 0x42540000
    printf("%x\n",getIEEE(30.5));  // answer = 0x41f40000
};

int main(void) {
    testPart1();
    testPart2();
    
    return 0;
};

