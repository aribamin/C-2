if (mantissa_a == 0 && exponent_a == -15 && mantissa_b == 0 && exponent_b == -15) {
        return 0.0;
    } else if (mantissa_a == 0 && exponent_a == -15) {
        return b;
    } else if (mantissa_b == 0 && exponent_b == -15) {
        return a;
    }