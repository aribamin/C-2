/* Purpose: Creating a NewFloat data type which has 1 sign bit, 5 exponent bits, and 26 mantissa bits
 * Author: Arib Amin
 * Date: 2023-11-29
 * Persons discussed w/: TAs on Discord & Professor Lin Office Hours
 * References: Binary addition: https://www.youtube.com/watch?v=aH11flclJDI&t=386s
 *             Binary subtraction (adding negatives): https://www.youtube.com/watch?v=JnorFLL86DE&t=121s
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

typedef uint32_t NewFloat;

NewFloat bits_string_to_nfloat(char s1[32]){
    NewFloat n1 = 0.0;
  
    for (int i = 0; i < 32; i++){
        n1 = (n1 << 1) | (s1[i] - '0');
    }
    
    return n1;
}

void nfloat_debug(NewFloat f){
    for (int i = 31; i >= 0; i--){
        printf("%d", (f >> i) & 1);
        
        if (i == 31 || i == 26){
            printf(" ");
        }
    }
    printf("\n");
}

NewFloat float_to_nfloat(float f){
    NewFloat n2 = 0.0;

    uint32_t float_bits = *(uint32_t*)&f;

    n2 = ((float_bits >> 31) << 31);

    int new_exponent = ((float_bits << 1) >> 24);
    new_exponent -= 127;
    new_exponent += 15;

    if (new_exponent < 0) {
        new_exponent = 0;
    } else if (new_exponent > 31) {
        new_exponent = 31;
    }

    n2 = n2 | (new_exponent << 26);
    n2 = n2 | ((float_bits << 9) >> 6);

    return n2;
}

void nfloat_print(NewFloat f){
    double result = 0.0;
    double two_pow_26 = 67108864.0;

    int sign = (f >> 31);
    int exponent = ((f << 1) >> 27) - 15;
    int mantissa = ((f << 6) >> 6);

    // Consider the implicit leading 0 in normalized representation
    if (exponent == -15){
        result = (0.0 + mantissa / two_pow_26);  
    
    } else if (exponent != -15){
        result = 1.0 + (mantissa / two_pow_26);
    }

    if (exponent > 0){
            result *= (1 << exponent);

        } else if (exponent < 0){
            result /= (1 << (-exponent));
    }

    if (sign == 1) {
        result *= -1.0;
    }

    printf("%.7lf\n", result);
}

// void nfloat_print(NewFloat f) {
//     double result = 0.0;

//     int sign = (f >> 31);
//     int exponent = ((f << 1) >> 27) - 15;
//     int mantissa = ((f << 6) >> 6);

//     uint64_t combinedValue = ((uint64_t)sign << 63) | ((uint64_t)exponent << 52) | ((uint64_t)mantissa << 26);

//     // Copy the combined value into the result
//     memcpy(&result, &combinedValue, sizeof(double));

//     printf("%.7f\n", result);
// }

NewFloat nfloat_double(NewFloat f){
    int exponent = ((f << 1) >> 27);
    exponent += 1;

    if (exponent > 31){
        exponent = 31;
    }

    NewFloat n4 = 0.0;

    n4 = ((f >> 31) << 31) | (exponent << 26);
    n4 = n4 | ((f << 6) >> 6);

    return n4;
}

NewFloat nfloat_add(NewFloat a, NewFloat b) {
    NewFloat n4 = 0.0;
    double two_pow_26 = 67108864.0;

    int sign_a = (a >> 31);
    int sign_b = (b >> 31);

    int exponent_a = ((a << 1) >> 27) - 15;
    int exponent_b = ((b << 1) >> 27) - 15;

    int mantissa_a = ((a << 6) >> 6);
    double float_mantissa_a = 1.0 + (mantissa_a / two_pow_26);
    int mantissa_b = ((b << 6) >> 6);
    double float_mantissa_b = 1.0 + (mantissa_b / two_pow_26);

    if (mantissa_a == 0 && exponent_a == -15 && mantissa_b == 0 && exponent_b == -15) {
        return 0.0;
    } else if (mantissa_a == 0 && exponent_a == -15) {
        return b;
    } else if (mantissa_b == 0 && exponent_b == -15) {
        return a;
    }

    // Align the exponents to the larger exponent btween a and b
    int exponent_diff = exponent_a - exponent_b;
    if (exponent_diff > 0) {
        float_mantissa_b /= (1 << exponent_diff);
        exponent_b = exponent_a;
    } else if (exponent_diff < 0) {
        float_mantissa_a /= (1 << (-exponent_diff));
        exponent_a = exponent_b;
    }

    // Adding up or subtracting the mantisas depending on signs
    double new_mantissa;
    if ((sign_a == 0) && (sign_b == 0)) {
        new_mantissa = float_mantissa_a + float_mantissa_b;

    } else if ((sign_a == 0) && (sign_b == 1)) {
        if (float_mantissa_a >= float_mantissa_b) {
            new_mantissa = float_mantissa_a - float_mantissa_b;
            sign_a = 0;
        } else {
            new_mantissa = float_mantissa_b - float_mantissa_a;
            sign_a = 1;
        }

    } else if ((sign_a == 1) && (sign_b == 0)) {
        if (float_mantissa_a >= float_mantissa_b) {
            new_mantissa = float_mantissa_a - float_mantissa_b;
            sign_a = 1;
        } else {
            new_mantissa = float_mantissa_b - float_mantissa_a;
            sign_a = 0;
        }

    } else if ((sign_a == 1) && (sign_b == 1)){
        new_mantissa = float_mantissa_a + float_mantissa_b;
    }

    // Case for mantissa overflow
    if (new_mantissa >= 2.0) {
        new_mantissa /= 2.0;
        exponent_a++;
    }

    // Case for mantissa underflow
    while ((new_mantissa < 1.0) && (exponent_a > -15)) {
        new_mantissa *= 2.0;
        exponent_a--;
    }

    n4 = (sign_a << 31) | ((exponent_a + 15) << 26);
    n4 = n4 | ((int)(new_mantissa * two_pow_26) & 0x3FFFFFF);

    return n4;
}

int main(void) {
    int part_num;
    char s1[40];
    float f1, f2;
    NewFloat n1, n2;

    // This will scan the input for you! Uncomment pieces once you implement
    // the functions for that part
    while (1) {
        int res = scanf(" p%d", &part_num);

        if (res != 1) {
            break;
        } else if (part_num == 1) {
            scanf("%s", s1);
            n1 = bits_string_to_nfloat(s1);
            nfloat_debug(n1);
        } else if (part_num == 2) {
            scanf("%f", &f1);
            n1 = float_to_nfloat(f1);
            nfloat_debug(n1);
        } else if (part_num == 3) {
            scanf("%s", s1);
            n1 = bits_string_to_nfloat(s1);
            nfloat_print(n1);
        } else {
            scanf("%s ", s1);

            if (s1[0] == 'd') {
                scanf("%f", &f1);
                n1 = float_to_nfloat(f1);
                n1 = nfloat_double(n1);
            } else {
                scanf("%f %f", &f1, &f2);
                n1 = float_to_nfloat(f1);
                n2 = float_to_nfloat(f2);
                n1 = nfloat_add(n1, n2);
            }

            nfloat_print(n1);
        }
    }
}
