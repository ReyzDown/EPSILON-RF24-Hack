#ifndef GAUSSIANNOISE_H
#define GAUSSIANNOISE_H

#define CE_PIN  16
#define CSN_PIN 17

#define X       1
#define PIPE    0xF0

#include <RF24.h>

class Gaussian{
public:
    void setUp();
    void sendNoise();
    void randomGaussian();
}


#endif