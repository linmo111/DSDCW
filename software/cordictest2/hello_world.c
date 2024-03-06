#include <stdio.h>
#include <math.h>
#define ALT_CI_CORDIC_0(A) __builtin_custom_fnf(ALT_CI_CORDIC_0_N,(A))
#define ALT_CI_CORDIC_0_N 0x0

int main()
{
 float cos1 = cos(-0.52359878);

 float cos2 = ALT_CI_CORDIC_0(-0.52359878);

 printf("Result: %f \n",cos1);

 printf("Result: %f \n",cos2);

 printf("Result: %f \n",cos1-cos2);

 return 0;
}
