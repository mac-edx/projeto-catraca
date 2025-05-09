#ifndef MATRIZ_H
#define MATRIZ_H
#include <stdint.h>
#include <stdlib.h>


typedef struct {
  uint8_t G, R, B; // Três valores de 8-bits compõem um pixel na ordem GRB.
} npLED_t;

void neopixel_init(uint pin, uint amount);

void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b);

void npInit(uint pin);

void npClear();

void npWrite();
#endif