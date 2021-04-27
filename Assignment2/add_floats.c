#include <stdio.h>
#include <stdlib.h>
#define TRUE  1
#define FALSE 0

/** 32 bit float union data **/
union float_32 {
    float num_as_float;
    struct sign_exponent_mantissa {
        unsigned mantissa : 23;
        unsigned exponent : 8;
        unsigned     sign : 1;
    } f_bits;
    struct single_bits {
        unsigned b0 : 1;
        unsigned b1 : 1;
        unsigned b2 : 1;
        unsigned b3 : 1;
        unsigned b4 : 1;
        unsigned b5 : 1;
        unsigned b6 : 1;
        unsigned b7 : 1;
        unsigned b8 : 1;
        unsigned b9 : 1;
        unsigned b10 : 1;
        unsigned b11 : 1;
        unsigned b12 : 1;
        unsigned b13 : 1;
        unsigned b14 : 1;
        unsigned b15 : 1;
        unsigned b16 : 1;
        unsigned b17 : 1;
        unsigned b18 : 1;
        unsigned b19 : 1;
        unsigned b20 : 1;
        unsigned b21 : 1;
        unsigned b22 : 1;
        unsigned b23 : 1;
        unsigned b24 : 1;
        unsigned b25 : 1;
        unsigned b26 : 1;
        unsigned b27 : 1;
        unsigned b28 : 1;
        unsigned b29 : 1;
        unsigned b30 : 1;
        unsigned b31 : 1;
    } bits;
};

union float_32 addFloats(union float_32 f1, union float_32 f2);
char* getBitString(union float_32 floatData, char* bitString);

int main(int argc, char* argv[]) {
    union float_32 float1, float2, sum;         //floats to be added through emulation
    float hardware_result;                      //result of floats added by hardware
    char bitString[41];                         //used to create bit strings
    FILE* output = fopen("output.txt", "a");    //output file

    printf("************************************************************************\n");
    fprintf(output, "************************************************************************\n");
    printf("This program will emulate the addition of two IEEE 754 floating point numbers\n");
    fprintf(output, "This program will emulate the addition of two IEEE 754 floating point numbers\n");

    printf("Please enter two positive floating point values each with:\n");
    fprintf(output, "Please enter two positive floating point values each with:\n");
    printf("    - no more than 6 significant digits\n");
    fprintf(output, "    - no more than 6 significant digits\n");
    printf("    - a value between + 10**37 and 10**-37\n\n");
    fprintf(output, "    - a value between + 10**37 and 10**-37\n\n");

    printf("Enter Float 1: ");
    fprintf(output, "Enter Float 1: ");
    scanf("%f", &float1.num_as_float);
    fprintf(output, "%g\n", float1.num_as_float);

    printf("Enter Float 2: ");
    fprintf(output, "Enter Float 2: ");
    scanf("%f", &float2.num_as_float);
    fprintf(output, "%g\n", float2.num_as_float);

    hardware_result = float1.num_as_float + float2.num_as_float;

    char* float_bitString = getBitString(float1, bitString);
    printf("\nOriginal pattern of Float 1: %s\n", float_bitString);
    fprintf(output, "\nOriginal pattern of Float 1: %s\n", float_bitString);

    float_bitString = getBitString(float2, bitString);
    printf("Original pattern of Float 2: %s\n", float_bitString);
    fprintf(output, "Original pattern of Float 2: %s\n", float_bitString);

    sum = addFloats(float1, float2);

    float_bitString = getBitString(sum, bitString);
    printf("Bit pattern of result      : %s\n\n", float_bitString);
    fprintf(output, "Bit pattern of result      : %s\n\n", float_bitString);

    printf("EMULATED FLOATING RESULT FROM PRINTF ==>>> %g\n", sum.num_as_float);
    fprintf(output, "EMULATED FLOATING RESULT FROM PRINTF ==>>> %g\n", sum.num_as_float);
    printf("HARDWARE FLOATING RESULT FROM PRINTF ==>>> %g\n", hardware_result);
    fprintf(output, "HARDWARE FLOATING RESULT FROM PRINTF ==>>> %g\n", hardware_result);
    printf("************************************************************************\n");
    fprintf(output, "************************************************************************\n");

    fclose(output);

    return 0;
}

union float_32 addFloats(union float_32 f1, union float_32 f2) {
    union float_32 result;
    int f1_exponent = f1.f_bits.exponent, f2_exponent = f2.f_bits.exponent;
    int f1_mantissa = f1.f_bits.mantissa, f2_mantissa = f2.f_bits.mantissa;
    int f1_denorm   = TRUE,               f2_denorm   = TRUE;
    int shiftNum    = 0;
    int result_mantissa;
    
    //if exponents are normalized insert the hidden bit
    if (f1_exponent) {
        f1_mantissa |= (1 << 23);
        f1_denorm = FALSE;
    }
    if (f2_exponent) {
        f2_mantissa |= (1 << 23);
        f2_denorm = FALSE;
    }

    //check which exponent is larger and shift mantissa of smaller number by their difference
    if (f1_exponent > f2_exponent) {
        shiftNum = f1_exponent - f2_exponent;
        if (shiftNum > 24) { shiftNum = 24; }
        if (shiftNum >= 1 && f2_denorm) {       //if f2 is denormalized shift right w/o hidden bit
            f2_mantissa >>= shiftNum - 1;
        }
        else { f2_mantissa >>= shiftNum; }
        result.f_bits.exponent = f1_exponent;
    }
    else {
        shiftNum = f2_exponent - f1_exponent;
        if (shiftNum > 24) { shiftNum = 24; }
        if (shiftNum >= 1 && f1_denorm) {       //if f1 is denormalized shift right w/o hidden bit
            f1_mantissa >>= shiftNum - 1;
        }
        else { f1_mantissa >>= shiftNum; }
        result.f_bits.exponent = f2_exponent;
    }

    //add both mantissas and remove hidden bit
    result_mantissa = f1_mantissa + f2_mantissa;

    //check for overflow of hidden bits
    if (result_mantissa & (1 << 24)) {
        result_mantissa >>= 1;
        if (result.f_bits.exponent != 0xFF) {   //if exponent is not inf increment it
            result.f_bits.exponent++;
        }
        result.f_bits.mantissa = (result_mantissa & ~(1 << 23));
    }
    else { result.f_bits.mantissa = (result_mantissa & ~(1 << 23)); }

    //if exponent is inf set mantissa bits to zero
    if (result.f_bits.exponent == 0xFF) {
        result.f_bits.mantissa = 0;
    }

    return result;
}

/** getBitString takes a float_32 union and a char array of length 41 then returns
 * the char array with the bit fields from the union so that they may be displayed **/
char* getBitString(union float_32 floatData, char* bitString) {
    bitString[0] = floatData.bits.b31 ? '1' : '0';
    bitString[1] = ' ';
    bitString[2] = floatData.bits.b30 ? '1' : '0';
    bitString[3] = floatData.bits.b29 ? '1' : '0';
    bitString[4] = floatData.bits.b28 ? '1' : '0';
    bitString[5] = floatData.bits.b27 ? '1' : '0';
    bitString[6] = ' ';
    bitString[7] = floatData.bits.b26 ? '1' : '0';
    bitString[8] = floatData.bits.b25 ? '1' : '0';
    bitString[9] = floatData.bits.b24 ? '1' : '0';
    bitString[10] = floatData.bits.b23 ? '1' : '0';
    bitString[11] = ' '; 
    bitString[12] = floatData.bits.b22 ? '1' : '0';
    bitString[13] = floatData.bits.b21 ? '1' : '0';
    bitString[14] = floatData.bits.b20 ? '1' : '0';
    bitString[15] = ' ';
    bitString[16] = floatData.bits.b19 ? '1' : '0';
    bitString[17] = floatData.bits.b18 ? '1' : '0';
    bitString[18] = floatData.bits.b17 ? '1' : '0';
    bitString[19] = floatData.bits.b16 ? '1' : '0';
    bitString[20] = ' ';
    bitString[21] = floatData.bits.b15 ? '1' : '0';
    bitString[22] = floatData.bits.b14 ? '1' : '0';
    bitString[23] = floatData.bits.b13 ? '1' : '0';
    bitString[24] = floatData.bits.b12 ? '1' : '0';
    bitString[25] = ' ';
    bitString[26] = floatData.bits.b11 ? '1' : '0';
    bitString[27] = floatData.bits.b10 ? '1' : '0';
    bitString[28] = floatData.bits.b9 ? '1' : '0';
    bitString[29] = floatData.bits.b8 ? '1' : '0';
    bitString[30] = ' ';
    bitString[31] = floatData.bits.b7 ? '1' : '0';
    bitString[32] = floatData.bits.b6 ? '1' : '0';
    bitString[33] = floatData.bits.b5 ? '1' : '0';
    bitString[34] = floatData.bits.b4 ? '1' : '0';
    bitString[35] = ' ';
    bitString[36] = floatData.bits.b3 ? '1' : '0';
    bitString[37] = floatData.bits.b2 ? '1' : '0';
    bitString[38] = floatData.bits.b1 ? '1' : '0';
    bitString[39] = floatData.bits.b0 ? '1' : '0';
    bitString[40] = '\0';

    return bitString;
}