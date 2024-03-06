#include <stdlib.h>
#include <sys/alt_stdio.h>
#include <sys/alt_alarm.h>
#include <sys/times.h>
#include <alt_types.h>
#include <system.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
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
void generateVector(float x[N])
{
int i;
x[0] = 0;
for (i=1; i<N; i++)
x[i] = x[i-1] + step;
}
float sumVector(float x[], int M)
{
	float sum = 0;
		    for (int i = 0; i < M; i++) {
		        sum += x[i] + x[i]*x[i]; // Add xi and xi^2 to sum
		    }
		    return sum;
}

float func(float x[], int M)
{
	float sum = 0;
		    for (int i = 0; i < M; i++) {
		    	sum += 0.5 * x[i] + x[i] * x[i] * cos((x[i] - 128.0) / 128.0);
		    }
		    return sum;
}

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
//nios2-elf-size task5.elf
}
