/* Purpose: Modular Exponentiation with brute-force recursion and with memoization
 * Author: Arib Amin
 * Date: 2023-10-14
 * Persons discussed w/: TA's on Discord
 * References:
 */
#include "ex6q1.h"

#define LEN 200000000

// Array to store values of previous calls to exp_mod_2 and use for later calculations
uint32_t stored_values[LEN] = {0}; 

// This function should be pure recursion - no dynamic programming allowed
uint32_t exp_mod_1(uint32_t base, uint32_t exp, uint32_t modulo) {
  // Incrementing each time exp_mod_1 is called
  EXP_MOD_1_CALL_COUNT++;

  // Base case when exponent equals 0
  if (exp == 0){
    return 1;
  }

  // Base case when exponent equals 1
  if (exp == 1){
    return base % modulo;
  }

  // Recursively call exp_mod_1 by breaking the expoent down into smaller problems
  // Using these formulas: "7**7 == 7**(4+3) == 7**4 * 7**3" and "a == b * c we have a % d == ((b % d) * (c % d)) % d"
  return (exp_mod_1(base, exp / 2, modulo) * exp_mod_1(base, exp - exp / 2, modulo)) % modulo;

}

// This function should store the values of previous calls to exp_mod_2 in an
// array and use them for later calculations.
uint32_t exp_mod_2(uint32_t base, uint32_t exp, uint32_t modulo) {
    // Incrementing each time exp_mod_2 is called
    EXP_MOD_2_CALL_COUNT++;
  
    // Base case when exponent equals 0
    if (exp == 0){
      return 1;
    }

    // Base case when exponent equals 1
    if (exp == 1){
      return base % modulo;
    }

    // Checking if modulo for that exponent has already been calculated and returning value if it has
    if (stored_values[exp] != 0){
      return stored_values[exp];
    }

    // Storing value for modulo of each exponent when unwiding recursion stack
    stored_values[exp] = (exp_mod_2(base, exp / 2, modulo) * exp_mod_2(base, exp - exp / 2, modulo)) % modulo;
    
    // Returning value for modulo of original exponent
    return stored_values[exp];
}


int main(void) {
    uint32_t base, exp, modulo;

    if (scanf("%d %d %d", &base, &exp, &modulo) != 3) {
        return 1;
    }
    
    uint32_t mod_1 = exp_mod_1(base, exp, modulo);
    uint32_t mod_2 = exp_mod_2(base, exp, modulo);

    fprintf(stdout, "exp_mod_1 calls: %d\n", EXP_MOD_1_CALL_COUNT);
    fprintf(stdout, "exp_mod_2 calls: %d\n", EXP_MOD_2_CALL_COUNT);
    fprintf(stdout, "%d == %d\n", mod_1, mod_2);
}