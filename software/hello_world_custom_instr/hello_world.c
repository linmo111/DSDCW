#include <system.h>
#include <stdio.h>
#define ALT_CI_FP_ADD_0(A,B) __builtin_custom_fnff(ALT_CI_FP_ADD_0_N,(A),(B))
#define ALT_CI_FP_ADD_0_N 0x1
#define ALT_CI_FP_MULT_0(A,B) __builtin_custom_fnff(ALT_CI_FP_MULT_0_N,(A),(B))
#define ALT_CI_FP_MULT_0_N 0x3
#define ALT_CI_FP_SUB_0(A,B) __builtin_custom_fnff(ALT_CI_FP_SUB_0_N,(A),(B))
#define ALT_CI_FP_SUB_0_N 0x2
#define ALT_CI_LPM_1_0(A,B) __builtin_custom_inff(ALT_CI_LPM_1_0_N,(A),(B))
#define ALT_CI_LPM_1_0_N 0x0
int main()
{
printf("Hello from Nios II!\n");
float a, b, c, d;
a = 2.2;
b = 2.2;
c = a*b;
printf("Multiplication result: %f\n", c);
a = ALT_CI_FP_MULT_0(a,b);
printf("Multiplication result from custom instr: %f", a);
return 0;
}
