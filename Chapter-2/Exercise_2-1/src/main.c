#include <stdio.h>
#include <limits.h>
#include <float.h>

int main()
{
    printf("char[%d, %d]\n", CHAR_MIN, CHAR_MAX);
    printf("signed char[%d, %d]\n", SCHAR_MIN, SCHAR_MAX);
    printf("unsigned char[%d, %d]\n", 0, UCHAR_MAX);
    printf("\n----\n");
    printf("short[%d, %d]\n", SHRT_MIN, SHRT_MAX);
    printf("unsigned short[%d, %d]\n", 0, USHRT_MAX);
    printf("\n----\n");
    printf("int[%d, %d]\n", INT_MIN, INT_MAX);
    printf("unsigned int[%d, %u]\n", 0, UINT_MAX);
    printf("\n----\n");
    printf("long[%ld, %ld]\n", LONG_MIN, LONG_MAX);
    printf("unsigned long[%d, %lu]\n", 0, ULONG_MAX);
    printf("\n----\n");
    printf("float[%f, %f]\n", FLT_MIN, FLT_MAX);
    printf("float10EXP[%d, %d]\n", FLT_MIN_10_EXP, FLT_MAX_10_EXP);
    printf("float_epsilon: %f\n", FLT_EPSILON);
    printf("float_eval_method: %d\n", FLT_EVAL_METHOD);
    printf("float_dig: %d\n", FLT_DIG);
    printf("float_mant_dig: %d\n", FLT_MANT_DIG);
    return 0;
}
