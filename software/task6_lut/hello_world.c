#include <stdlib.h>
#include <sys/alt_stdio.h>
#include <sys/alt_alarm.h>
#include <sys/times.h>
#include <alt_types.h>
#include <system.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#define ALT_CI_FP_ADD_0(A,B) __builtin_custom_fnff(ALT_CI_FP_ADD_0_N,(A),(B))
#define ALT_CI_FP_ADD_0_N 0x1
#define ALT_CI_FP_MULT_0(A,B) __builtin_custom_fnff(ALT_CI_FP_MULT_0_N,(A),(B))
#define ALT_CI_FP_MULT_0_N 0x3
#define ALT_CI_FP_SUB_0(A,B) __builtin_custom_fnff(ALT_CI_FP_SUB_0_N,(A),(B))
#define ALT_CI_FP_SUB_0_N 0x2
#define ALT_CI_LPM_1_0(A,B) __builtin_custom_inff(ALT_CI_LPM_1_0_N,(A),(B))
#define ALT_CI_LPM_1_0_N 0x0
// Test case 1
//#define step 5
//#define N 52
// Test case 2
//#define step 1/8.0
//#define N 2041
//Test case 3
#define step 1/1024.0
#define N 261121
// Generates the vector x and stores it in the memory

#define PI 3.14159265358979323846
#define TWO_PI (2.0 * PI)
#define STEP 0.01
#define TABLE_SIZE (int)(TWO_PI / STEP + 1)

double cosLookupTable[TABLE_SIZE];

void generateCosLookupTable() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
    	cosLookupTable[i] = cos(i * STEP);
    }
}

int modulo(int dividend, int divisor) {
    // Handling divisor equals to zero case
    if (divisor == 0) {
        printf("Error: Division by zero\n");
        return -1; // Return an error code
    }

    // Ensure divisor is positive
    int positiveDivisor = divisor < 0 ? ALT_CI_FP_SUB_0(0, divisor) : divisor;

    // Using subtraction to find the modulo
    while (dividend >= positiveDivisor) {
        dividend = ALT_CI_FP_SUB_0(dividend, positiveDivisor);
    }

    // If original dividend was negative, adjust the result
    if (dividend < 0) {
        dividend = ALT_CI_FP_ADD_0(dividend, positiveDivisor);
    }

    return dividend;
}


float getCosFromTable(float radians) {
	if (radians < 0) radians = ALT_CI_FP_ADD_0(radians, TWO_PI);
	    //while (radians >= TWO_PI) radians =  ALT_CI_FP_SUB_0(radians, TWO_PI);

	    // Calculate the index, using modulo to ensure it cycles within the table bounds
	    int index = (int)(ALT_CI_FP_MULT_0(radians, 100));
	    return cosLookupTable[index];
}


void generateVector(float x[N])
{
int i;
x[0] = 0;
for (i=1; i<N; i++){
//x[i] = x[i-1] + step;
x[i]=ALT_CI_FP_ADD_0(x[i-1], step);
//printf("x[%d] = %f\n", i, x[i]); // Print the current value in each iteration
}
}


float sumVector(float x[], int M)
{
	float sum = 0;
		    for (int i = 0; i < M; i++) {
		        //sum += x[i] + x[i]*x[i]; // Add xi and xi^2 to sum
		    	float x_2 = ALT_CI_FP_MULT_0(x[i], x[i]);
		    	float x_sum = ALT_CI_FP_ADD_0(x[i], x_2);

		    }
		    return sum;
}

//double cosTaylorExpansion(double x) {
    // Using terms up to x^6 for the Taylor series expansion of cos(x)
    //return 1 - (x*x) / 2 + (x*x*x*x) / 24 - (x*x*x*x*x*x) / 720;
//}



float func(float x[], int M, float cosLookupTable[])
{
    float sum = 0;
    for (int i = 0; i < M; i++) {
    	//sum += 0.5 * x[i] + x[i] * x[i] * cosTaylorExpansion((x[i] - 128.0) / 128.0);
        float min = ALT_CI_FP_SUB_0(x[i],128);
        float div = ALT_CI_FP_MULT_0(min, 0.0078125);
        float xs = ALT_CI_FP_MULT_0(x[i],x[i]);
        float sum05=ALT_CI_FP_MULT_0(x[i], 0.5);

    	float sum_cos=ALT_CI_FP_MULT_0(xs, getCosFromTable(div));
    	float sumf=ALT_CI_FP_ADD_0(sum05, sum_cos);
    	sum = ALT_CI_FP_ADD_0(sum, sumf);
    }
    return sum;
}

int main()
{
printf("Task 4!\n");
// Define input vector
float x[N];
float cosLookupTable[TABLE_SIZE];
generateCosLookupTable(cosLookupTable);
// Returned result
float y;
generateVector(x);
printf("%f \n",getCosFromTable(2.8));
printf("%f \n",cos(2.8));


// The following is used for timing
//char buf[50];
clock_t exec_t1, exec_t2;
exec_t1 = times(NULL); // get system time before starting the process
// The code that you want to time goes here
y = func(x, N,cosLookupTable);
// till here
exec_t2 = times(NULL); // get system time after finishing the process


printf(" proc time = %d ticks \n", (unsigned int) (exec_t2-exec_t1));
printf("Result: %f \n",y);

//nios2-elf-objdump -d hello_world.elf > disassembly.txt
//nios2-elf-objdump -d hello_world.elf | grep -A20 "<main>:"
//nios2-elf-size hello_world.elf
}
