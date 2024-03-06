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
#define step 1/8.0
#define N 2041
//Test case 3
//#define step 1/1024.0
//#define N 261121
// Generates the vector x and stores it in the memory

#define TABLE_SIZE 360 // 1 degree resolution
#define PI 3.14159265358979323846

float cosLookupTable[TABLE_SIZE];

void generateCosLookupTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        // Convert angle from degrees to radians
        float rad = i * (PI / 180.0);
        cosLookupTable[i] = cos(rad);
    }
}

float lookupCos(int angle) {
    // Normalize angle to [0, 359]
    angle = angle % 360;
    if (angle < 0) angle += 360; // Ensure positive angle for negative inputs

    return cosLookupTable[angle];
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




//double cosTaylorExpansion(double x) {
    // Using terms up to x^6 for the Taylor series expansion of cos(x)
    //return 1 - (x*x) / 2 + (x*x*x*x) / 24 - (x*x*x*x*x*x) / 720;
//}

//float func(float x[], int M)
//{
//    float sum = 0;
//    for (int i = 0; i < M; i++) {
//    	//sum += 0.5 * x[i] + x[i] * x[i] * cosTaylorExpansion((x[i] - 128.0) / 128.0);
//        float min = ALT_CI_FP_SUB_0(x[i],128);
//        float div = ALT_CI_FP_MULT_0(min, 0.0078125);
//    	float xs = ALT_CI_FP_MULT_0(x[i],x[i]);
//    	float x_2 = ALT_CI_FP_MULT_0(div, div);
//        float x_4 = ALT_CI_FP_MULT_0(x_2, x_2);
//        float x_6 = ALT_CI_FP_MULT_0(x_2, x_4);
//        float x_8 = ALT_CI_FP_MULT_0(x_4, x_4);
//        float temp1 = ALT_CI_FP_MULT_0(x_2, 0.5);
//        float temp2 = ALT_CI_FP_MULT_0(x_4, 0.041666666666667);
//        float temp3 = ALT_CI_FP_MULT_0(x_6, 0.001388888888889);
//        float temp4 = ALT_CI_FP_MULT_0(x_8, 0.000024801587302);
//        float sum1=ALT_CI_FP_SUB_0(1,temp1);
//        float sum2=ALT_CI_FP_ADD_0(sum1, temp2);
//        float sum3=ALT_CI_FP_SUB_0(sum2, temp3);
//        float sum4=ALT_CI_FP_ADD_0(sum3, temp4);
//        float sum_cos=ALT_CI_FP_MULT_0(xs, sum4);
//        float sum05=ALT_CI_FP_MULT_0(x[i], 0.5);
//        float sumf=ALT_CI_FP_ADD_0(sum05, sum_cos);
//        sum = ALT_CI_FP_ADD_0(sum, sumf);
//
//    }
//    return sum;
//}

float func(float x[], int M)
{
    float sum = 0;
    for (int i = 0; i < M; i++) {
    	//sum += 0.5 * x[i] + x[i] * x[i] * cosTaylorExpansion((x[i] - 128.0) / 128.0);
        float min = ALT_CI_FP_SUB_0(x[i],128);
        float div = ALT_CI_FP_MULT_0(min, 0.0078125);
        float xs = ALT_CI_FP_MULT_0(x[i],x[i]);
        float sum05=ALT_CI_FP_MULT_0(x[i], 0.5);
    	int a = (int)ALT_CI_FP_MULT_0(div, 360);
    	if (a>360){
    		a=ALT_CI_FP_SUB_0(a,360);
    	}
    	float sum_cos=ALT_CI_FP_MULT_0(xs, cosLookupTable[a]);
    	float sumf=ALT_CI_FP_ADD_0(sum05, sum_cos);
    	sum = ALT_CI_FP_ADD_0(sum, sumf);
    }
    return sum;
}



// Function to approximate cos(x) using the first four terms of its Taylor expansion
//double cosTaylorExpansion(double x) {
//    // Using terms up to x^6 for the Taylor series expansion of cos(x)
//    return 1 - (x*x) / 2 + (x*x*x*x) / 24 - (x*x*x*x*x*x) / 720;
//}
//
//// Your original function modified to use the above cosTaylorExpansion function
//float func(float x[], int M) {
//    float sum = 0;
//    for (int i = 0; i < M; i++) {
//        // Use the Taylor expansion up to x^6 for the cosine calculation
//        sum += 0.5 * x[i] + x[i] * x[i] * cosTaylorExpansion((x[i] - 128.0) / 128.0);
//        printf("%f \n",sum);
//    }
//    return sum;
//}

int main()
{
printf("Task 4!\n");
// Define input vector
float x[N];
// Returned result
float y;
generateVector(x);
// The following is used for timing
//char buf[50];
clock_t exec_t1, exec_t2;
exec_t1 = times(NULL); // get system time before starting the process
// The code that you want to time goes here
y = func(x, N);
// till here
exec_t2 = times(NULL); // get system time after finishing the process



printf(" proc time = %d ticks \n", (unsigned int) (exec_t2-exec_t1));
printf("Result: %f \n",y);

//nios2-elf-objdump -d hello_world.elf > disassembly.txt
//nios2-elf-objdump -d hello_world.elf | grep -A20 "<main>:"
//nios2-elf-size hello_world.elf
}
