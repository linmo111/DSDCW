/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include <stdio.h>

#define ALT_CI_CORDICMULTI_0(A) __builtin_custom_fnf(ALT_CI_CORDICMULTI_0_N,(A))
#define ALT_CI_CORDICMULTI_0_N 0x0
#define ALT_CI_FX_0(A,B) __builtin_custom_fnff(ALT_CI_FX_0_N,(A),(B))
#define ALT_CI_FX_0_N 0x1

//#define step 5
//#define N 52
// Test case 2
//#define step 1/8.0
//#define N 2041
//Test case 3
#define step 1/1024.0
#define N 261121
void generateVector(float x[N])
{
	int i;
	x[0] = 0;
	for (i=1; i<N; i++)
	x[i] = x[i-1] + step;
}
float sumVectorC(float x[], int M)
{
	float sum=0;

	for (int i=0;i<M;i++){
		sum=ALT_CI_FX_0(x[i],sum);
//		printf("Custom Result: %f \n", (float) sum);
	}
//		printf("the current sum is %f, current xi is %f \n", sum,x[i]);}
	return sum;
// YOUR CODE GOES HERE
}
float sumVector(float x[], int M)
{
	float sum=0;

	for (int i=0;i<M;i++){
		sum+= 0.5*x[i]+x[i]*x[i]*(ALT_CI_CORDICMULTI_0((x[i]-128)/128));
//		printf("Custom Result: %f \n", (float) sum);
	}
//		printf("the current sum is %f, current xi is %f \n", sum,x[i]);}
	return sum;
// YOUR CODE GOES HERE
}
int main()
{
//  float x=128.0;
//  float oldsum=2.0;
//  float customRes= ALT_CI_FX_0(x,oldsum);
//  float originalRes=oldsum+0.5*x+x*x*(cos((x-128)/128));
//  printf("Resultnew: %f \n",customRes);
//
//  printf("Resultold: %f \n",originalRes);
//
//  printf("Result: %f \n",originalRes-customRes);
//

  	alt_putstr("hello");
  	printf("Task 8!\n");
  //	Define input vector
  	float x[N];
   // Returned result
  	float y;

  	generateVector(x);

  	clock_t exec_t1, exec_t2;


   	 exec_t1 = times(NULL); // get system time before starting the process
  	 y = sumVector(x, N);
   // till here
  	 exec_t2 = times(NULL); // get system time after finishing the process
  	 printf(" custom proc time = %d ticks \n", (unsigned int) (exec_t2-exec_t1));

  	 printf("Custom Result: %f \n", (float) y);
   	 exec_t1 = times(NULL); // get system time before starting the process
  	 y = sumVectorC(x, N);
   // till here
  	 exec_t2 = times(NULL); // get system time after finishing the process
  	 printf(" custom proc time = %d ticks \n", (unsigned int) (exec_t2-exec_t1));

  	 printf("Custom Result: %f \n", (float) y);


}
