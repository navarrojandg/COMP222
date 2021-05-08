#include <stdio.h>
#include <math.h>

//----------------------------
// Part 1:  IEEE to Float
//----------------------------
double getFraction(unsigned x) {
    return 0.0;
};

int getExponent(unsigned x) {
    return 0;
};

double getFloat(unsigned x) {
    return 0.0;
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
    return 0x0;
};

unsigned getBinexp(double x) {
    return 0x0;
};

unsigned getIEEE(double x) {
    return 0x0;
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

