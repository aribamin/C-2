#ifndef LAB6_H
#define LAB6_H
#include <stdio.h>
#include <stdint.h>

int EXP_MOD_1_CALL_COUNT = 0;
int EXP_MOD_2_CALL_COUNT = 0;

uint32_t exp_mod_1(uint32_t base, uint32_t exp, uint32_t modulo);

uint32_t exp_mod_2(uint32_t base, uint32_t exp, uint32_t modulo);

#endif
