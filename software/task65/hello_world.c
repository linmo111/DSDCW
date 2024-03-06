#include <system.h>
#include <stdio.h>

#include <stdlib.h>
#include <sys/alt_stdio.h>
#include <sys/alt_alarm.h>
#include <sys/times.h>
#include <alt_types.h>
#include <unistd.h>
#include <math.h>
//#define ALT_CI_CUSTOM_MUL_0_N 0x0
//#define ALT_CI_CUSTOM_MUL_0(A,B)
//__builtin_custom_inii(ALT_CI_CUSTOM_MUL_0_N,(A),(B))#
#define ALT_CI_FP_ADD_0_N 0x1
#define ALT_CI_FP_ADD_0(A,B) __builtin_custom_fnff(ALT_CI_FP_ADD_0_N,(A),(B))
#define ALT_CI_FP_MULT_0_N 0x3
#define ALT_CI_FP_MULT_0(A,B) __builtin_custom_fnff(ALT_CI_FP_MULT_0_N,(A),(B))
#define ALT_CI_FP_SUB_0_N 0x2
#define ALT_CI_FP_SUB_0(A,B) __builtin_custom_fnff(ALT_CI_FP_SUB_0_N,(A),(B))
#define ALT_CI_LPM_1_0_N 0x0
#define ALT_CI_LPM_1_0(A,B) __builtin_custom_fnff(ALT_CI_LPM_1_0_N,(A),(B))
#define TABLE_SIZE 360


// Test case 1
#define step 5
#define N 52
// Test case 2
//#define step 1/8.0
//#define N 2041
//Test case 3
//#define step 1/1024.0
//#define N 261121
// Generates the vector x and stores it in the memory
// Test Case 4
//#define N 2323
//#define RANDSEED 334

float cosTable[TABLE_SIZE];
float degree= 1.0/360.0f;

//float taylorEthan(float x){
//	float x2, cosApprox_1,sum
////	x2_1 = ((x[i] - 128) / 128) * ((x[i] - 128) / 128);
//	x2=ALT_CI_FP_MULT_0(x,x);
//	cosApprox_1 = 1 - x2 / 2 + x2_1 * x2_1 / 24 - x2_1*x2_1*x2_1/720 + x2_1*x2_1*x2_1*x2_1/40320;
////	sum += 0.5 * x[i] + x[i] * x[i] * cosApprox_1;
//}

//float sumVector(float x[], int M) {
//    float sum = 0.0;
//    float x2_1, x2_2, x2_3, x2_4, x2_5;
//    float cosApprox_1, cosApprox_2, cosApprox_3, cosApprox_4, cosApprox_5;
//    // Process in chunks of 5
//    int i = 0;
//    for (; i <= M - 5; i += 5) {
//        // Manually unroll computations for each of the five elements
//        x2_1 = ((x[i] - 128) / 128) * ((x[i] - 128) / 128);
//        cosApprox_1 = 1 - x2_1 / 2 + x2_1 * x2_1 / 24 - x2_1*x2_1*x2_1/720 + x2_1*x2_1*x2_1*x2_1/40320;
//        sum += 0.5 * x[i] + x[i] * x[i] * cosApprox_1;
//
//        x2_2 = ((x[i + 1] - 128) / 128) * ((x[i + 1] - 128) / 128);
//        cosApprox_2 = 1 - x2_2 / 2 + x2_2 * x2_2 / 24 - x2_2*x2_2*x2_2/720 + x2_2*x2_2*x2_2*x2_2/40320;
//        sum += 0.5 * x[i + 1] + x[i + 1] * x[i + 1] * cosApprox_2;
//
//        x2_3 = ((x[i + 2] - 128) / 128) * ((x[i + 2] - 128) / 128);
//        cosApprox_3 = 1 - x2_3 / 2 + x2_3 * x2_3 / 24 - x2_3*x2_3*x2_3/720 + x2_3*x2_3*x2_3*x2_3/40320;
//        sum += 0.5 * x[i + 2] + x[i + 2] * x[i + 2] * cosApprox_3;
//
//        x2_4 = ((x[i + 3] - 128) / 128) * ((x[i + 3] - 128) / 128);
//        cosApprox_4 = 1 - x2_4 / 2 + x2_4 * x2_4 / 24 - x2_4*x2_4*x2_4/720 + x2_4*x2_4*x2_4*x2_4/40320;
//        sum += 0.5 * x[i + 3] + x[i + 3] * x[i + 3] * cosApprox_4;
//
//        x2_5 = ((x[i + 4] - 128) / 128) * ((x[i + 4] - 128) / 128);
//        cosApprox_5 = 1 - x2_5 / 2 + x2_5 * x2_5 / 24 - x2_5*x2_5*x2_5/720 + x2_5*x2_5*x2_5*x2_5/40320;
//        sum += 0.5 * x[i + 4] + x[i + 4] * x[i + 4] * cosApprox_5;
//    }
//    // Handle the remaining elements
//    for (; i < M; i++) {
//        float x2 = ((x[i] - 128) / 128) * ((x[i] - 128) / 128);
//        float cosApprox = 1 - x2 / 2 + x2 * x2 / 24 - x2*x2*x2/720 + x2*x2*x2*x2/40320;
//        sum += 0.5 * x[i] + x[i] * x[i] * cosApprox;
//    }
//    return sum;
//}







void buildCosTable() {
  for(int i=0; i < TABLE_SIZE; i++) {
    cosTable[i] = cos(i * M_PI / 180.0);
  }
}
float radToDeg(float rad) {

  // Input rad is in range -1 to 1
  float angle;

  // Shift and scale to 0 to 2*PI
  angle = (rad + 1.0f) * M_PI;

  // Convert to degrees
  angle = angle * 180.0f / M_PI;

  // Wrap into 0 to 360 range
  if(angle < 0) {
    angle += 360.0f;
  }
  else if (angle >= 360) {
    angle -= 360.0f;
  }

  return angle;
}
float lookupCos(float x) {
	float y=radToDeg(x);
	 int index = y * (TABLE_SIZE-1) / 360.0f;
	  float frac = (y * (TABLE_SIZE-1) / 360.0f) - index;

	  float y1 = cosTable[index];
	  float y2 = cosTable[index+1];

	  return y1 + frac * (y2 - y1);
}
float customLookupCos(float x) {

//  int index = x * (TABLE_SIZE-1) / 360.0f;
	float tmp=ALT_CI_FP_MULT_0(x, ALT_CI_FP_MULT_0((TABLE_SIZE-1) , degree));
	int index= (int) tmp;
	float frac= ALT_CI_FP_SUB_0(tmp,(float)index);
//	printf( " index is %d, frac is %f", index, frac);
//	float frac=tmp-index;
//  int index=ALT_CI_FP_MULT_0(x, ALT_CI_FP_MULT_0((TABLE_SIZE-1) , degree));
//  float frac = (x * (TABLE_SIZE-1) / 360.0f) - index;
//  ALT_CI_FP_MULT_0(x, ALT_CI_FP_MULT_0((TABLE_SIZE-1) , degree));
  float y1 = cosTable[index];
  float y2 = cosTable[index+1];

  float res=ALT_CI_FP_ADD_0(y1, ALT_CI_FP_MULT_0(frac, ALT_CI_FP_SUB_0(y2,y1)));
//  return y1 + frac * (y2 - y1);
  return res;
}

float cos_horner(float x) {
  float result;
  float term;

  term = 1.0f;
  result = term;

  term *= x*x/2.0f;
  result += -term;

  term *= x*x/3.0f*4.0f;
  result += term;

  term *= x*x/5.0f*6.0f;
  result += -term;

  term *= x*x/7.0f*8.0f;
  result += term;

  term *= x*x/9.0f*10.0f;
  result += -term;

  return result;
}


float custom_cos_horner(float x) {
  float result;
  float term;

  term = 1.0f;
  result = term;

  term = ALT_CI_FP_MULT_0(term, ALT_CI_FP_MULT_0(x, ALT_CI_FP_MULT_0(x,1/2.0f)));
  result = ALT_CI_FP_ADD_0(result,-term);

  term = ALT_CI_FP_MULT_0(term,ALT_CI_FP_MULT_0(x,ALT_CI_FP_MULT_0(x, 1.0/(12.0f))));
  result = ALT_CI_FP_ADD_0(result,term);

  term = ALT_CI_FP_MULT_0(term,ALT_CI_FP_MULT_0(x,ALT_CI_FP_MULT_0(x, 1.0/(30.0f))));
  result = ALT_CI_FP_ADD_0(result,-term);

  term = ALT_CI_FP_MULT_0(term,ALT_CI_FP_MULT_0(x,ALT_CI_FP_MULT_0(x, 1.0/(56.0f))));
  result = ALT_CI_FP_ADD_0(result,term);

  term = ALT_CI_FP_MULT_0(term,ALT_CI_FP_MULT_0(x,ALT_CI_FP_MULT_0(x, 1.0/(90.0f))));
  result = ALT_CI_FP_ADD_0(result,-term);

  return result;
}
float factorial(int n) {
  float result = 1.0f;
  int i;

  for(i=2; i<=n; i++)
    result *= i;

  return (float)result;
}
float custom_factorial(int n) {
  float result = 1.0f;
  int i;

  for(i=2; i<=n; i++)
    result = ALT_CI_FP_MULT_0(result,i);

  return (float)result;
}
float custom_powf(float x, int n){
	float result = 1.0f;
	for (int i=0; i<n; i++){
		result=ALT_CI_FP_MULT_0(result, x);
	}
	return (float)result;
}


float cos_taylor(float x, int n) {
  float result = 0.0f;
  float term = 1.0f;
  int i;

  for(i=0; i<n; i++) {
    result += term * powf(-1, i) / factorial(2*i);
    term *= x * x;
  }

  return result;
}
float custom_cos_taylor(float x, int n) {
  float result = 0.0f;
  float term = 1.0f;
  int i;

  for(i=0; i<n; i++) {
    result = ALT_CI_FP_ADD_0(result, ALT_CI_FP_MULT_0(term , custom_powf(-1, i)) / custom_factorial(2*i));
    term = ALT_CI_FP_MULT_0(term,ALT_CI_FP_MULT_0(x , x));
  }

  return result;
}



void generateVector(float x[N])
{
	int i;
	x[0] = 0;
	for (i=1; i<N; i++)
	x[i] = x[i-1] + step;
}
float sumVector(float x[], int M)
{
	float sum=0;

	for (int i=0;i<M;i++){
		sum+= 0.5*x[i]+x[i]*x[i]*(cos_horner((x[i]-128)/128));
	}
//		printf("the current sum is %f, current xi is %f \n", sum,x[i]);}
	return sum;
// YOUR CODE GOES HERE
}
float CustomSumVector(float x[], int M)
{
	float sum=0;
	float ff=1.0/128;
//	printf("ff= %f", ff);
	for (int i=0;i<M;i++){
//		float a=ALT_CI_FP_SUB_0(x[i], 128);
//		float b=cos(ALT_CI_FP_MULT_0(a ,1/128));
//		float c=ALT_CI_FP_MULT_0(x[i],b );
//		float d=ALT_CI_FP_MULT_0(x[i],c);
//		sum+= 0.5*x[i]+x[i]*x[i]*(cos((x[i]-128)/128));
		//ALT_CI_FP_MULT_0(x[i], ALT_CI_FP_MULT_0(x[i], cos(ALT_CI_FP_MULT_0(ALT_CI_FP_SUB_0(x[i], 128),1/128)))) cos(ALT_CI_FP_MULT_0(ALT_CI_FP_SUB_0(x[i], 128) ,1/128)) ))
//		sum= ALT_CI_FP_ADD_0(sum,  ALT_CI_FP_ADD_0(ALT_CI_FP_MULT_0(0.5,x[i]),ALT_CI_FP_MULT_0(x[i],ALT_CI_FP_MULT_0(x[i],custom_cos_taylor(ALT_CI_FP_MULT_0((ALT_CI_FP_SUB_0(x[i], 128)),1/128),3) )) ));
		sum= ALT_CI_FP_ADD_0(sum,  ALT_CI_FP_ADD_0(ALT_CI_FP_MULT_0(0.5,x[i]),ALT_CI_FP_MULT_0(x[i],ALT_CI_FP_MULT_0(x[i],cos(ALT_CI_FP_MULT_0((ALT_CI_FP_SUB_0(x[i], 128)),ff)) )) ));


	}
//		printf("the current sum is %f, current xi is %f \n", sum,x[i]);}
	return sum;
// YOUR CODE GOES HERE
}
float TaylorCustomSumVector(float x[], int M)
{
	float sum=0;
	float ff=1.0/128;
	int i=0;
//	printf("ff= %f", ff);
	for (;i<M-4;i+=4){
//		float a=ALT_CI_FP_SUB_0(x[i], 128);
//		float b=cos(ALT_CI_FP_MULT_0(a ,1/128));
//		float c=ALT_CI_FP_MULT_0(x[i],b );
//		float d=ALT_CI_FP_MULT_0(x[i],c);
//		sum+= 0.5*x[i]+x[i]*x[i]*(cos((x[i]-128)/128));
		//ALT_CI_FP_MULT_0(x[i], ALT_CI_FP_MULT_0(x[i], cos(ALT_CI_FP_MULT_0(ALT_CI_FP_SUB_0(x[i], 128),1/128)))) cos(ALT_CI_FP_MULT_0(ALT_CI_FP_SUB_0(x[i], 128) ,1/128)) ))
//		sum= ALT_CI_FP_ADD_0(sum,  ALT_CI_FP_ADD_0(ALT_CI_FP_MULT_0(0.5,x[i]),ALT_CI_FP_MULT_0(x[i],ALT_CI_FP_MULT_0(x[i],custom_cos_taylor(ALT_CI_FP_MULT_0((ALT_CI_FP_SUB_0(x[i], 128)),ff),3) )) ));
		sum= ALT_CI_FP_ADD_0(sum,  ALT_CI_FP_ADD_0(ALT_CI_FP_MULT_0(0.5,x[i]),ALT_CI_FP_MULT_0(x[i],ALT_CI_FP_MULT_0(x[i],custom_cos_horner(ALT_CI_FP_MULT_0((ALT_CI_FP_SUB_0(x[i], 128)),ff)) )) ));
		sum= ALT_CI_FP_ADD_0(sum,  ALT_CI_FP_ADD_0(ALT_CI_FP_MULT_0(0.5,x[i+1]),ALT_CI_FP_MULT_0(x[i+1],ALT_CI_FP_MULT_0(x[i+1],custom_cos_horner(ALT_CI_FP_MULT_0((ALT_CI_FP_SUB_0(x[i+1], 128)),ff)) )) ));
		sum= ALT_CI_FP_ADD_0(sum,  ALT_CI_FP_ADD_0(ALT_CI_FP_MULT_0(0.5,x[i+2]),ALT_CI_FP_MULT_0(x[i+2],ALT_CI_FP_MULT_0(x[i+2],custom_cos_horner(ALT_CI_FP_MULT_0((ALT_CI_FP_SUB_0(x[i+2], 128)),ff)) )) ));
		sum= ALT_CI_FP_ADD_0(sum,  ALT_CI_FP_ADD_0(ALT_CI_FP_MULT_0(0.5,x[i+3]),ALT_CI_FP_MULT_0(x[i+3],ALT_CI_FP_MULT_0(x[i+3],custom_cos_horner(ALT_CI_FP_MULT_0((ALT_CI_FP_SUB_0(x[i+3], 128)),ff)) )) ));
//		sum= ALT_CI_FP_ADD_0(sum,  ALT_CI_FP_ADD_0(ALT_CI_FP_MULT_0(0.5,x[i+4]),ALT_CI_FP_MULT_0(x[i+4],ALT_CI_FP_MULT_0(x[i+4],custom_cos_horner(ALT_CI_FP_MULT_0((ALT_CI_FP_SUB_0(x[i+4], 128)),ff)) )) ));
//		sum= ALT_CI_FP_ADD_0(sum,  ALT_CI_FP_ADD_0(ALT_CI_FP_MULT_0(0.5,x[i+5]),ALT_CI_FP_MULT_0(x[i+5],ALT_CI_FP_MULT_0(x[i+5],custom_cos_horner(ALT_CI_FP_MULT_0((ALT_CI_FP_SUB_0(x[i+5], 128)),ff)) )) ));
//		sum= ALT_CI_FP_ADD_0(sum,  ALT_CI_FP_ADD_0(ALT_CI_FP_MULT_0(0.5,x[i+6]),ALT_CI_FP_MULT_0(x[i+4],ALT_CI_FP_MULT_0(x[i+6],custom_cos_horner(ALT_CI_FP_MULT_0((ALT_CI_FP_SUB_0(x[i+6], 128)),ff)) )) ));
//		sum= ALT_CI_FP_ADD_0(sum,  ALT_CI_FP_ADD_0(ALT_CI_FP_MULT_0(0.5,x[i+7]),ALT_CI_FP_MULT_0(x[i+4],ALT_CI_FP_MULT_0(x[i+7],custom_cos_horner(ALT_CI_FP_MULT_0((ALT_CI_FP_SUB_0(x[i+7], 128)),ff)) )) ));
		//		sum= ALT_CI_FP_ADD_0(sum,  ALT_CI_FP_ADD_0(ALT_CI_FP_MULT_0(0.5,x[i]),ALT_CI_FP_MULT_0(x[i],ALT_CI_FP_MULT_0(x[i],cos(ALT_CI_FP_MULT_0((ALT_CI_FP_SUB_0(x[i], 128)),ff)) )) ));
	}
	for (; i < M; i++){
		sum= ALT_CI_FP_ADD_0(sum,  ALT_CI_FP_ADD_0(ALT_CI_FP_MULT_0(0.5,x[i]),ALT_CI_FP_MULT_0(x[i],ALT_CI_FP_MULT_0(x[i],custom_cos_horner(ALT_CI_FP_MULT_0((ALT_CI_FP_SUB_0(x[i], 128)),ff)) )) ));
	}

//		printf("the current sum is %f, current xi is %f \n", sum,x[i]);}
	return sum;
// YOUR CODE GOES HERE
}
float OneCustomSumVector(float x[], int M)
{
	float sum=0;

	for (int i=0;i<M;i++){
//		float a=ALT_CI_FP_SUB_0(x[i], 128);
//		float b=cos(ALT_CI_FP_MULT_0(a ,1/128));
//		float c=ALT_CI_FP_MULT_0(x[i],b );
//		float d=ALT_CI_FP_MULT_0(x[i],c);

		sum+=  0.5*x[i]+ALT_CI_FP_MULT_0(x[i], x[i]*(cos_horner((x[i]-128)/128)));
		//ALT_CI_FP_MULT_0(x[i], ALT_CI_FP_MULT_0(x[i], cos(ALT_CI_FP_MULT_0(ALT_CI_FP_SUB_0(x[i], 128),1/128))))
//		sum= ALT_CI_FP_ADD_0(sum,  ALT_CI_FP_ADD_0(ALT_CI_FP_MULT_0(0.5,x[i]),ALT_CI_FP_MULT_0(x[i],ALT_CI_FP_MULT_0(x[i],cos(ALT_CI_FP_MULT_0(ALT_CI_FP_ADD_0(x[i], -128) ,1/128)) )) ));
	}
//		printf("the current sum is %f, current xi is %f \n", sum,x[i]);}
	return sum;
// YOUR CODE GOES HERE
}
float LUTCustomSumVector(float x[], int M)
{
	float sum=0;
	float ff=1.0/128.0f;
//	printf("ff= %f", ff);
	for (int i=0;i<M;i++){
//		float a=ALT_CI_FP_SUB_0(x[i], 128);
//		float b=cos(ALT_CI_FP_MULT_0(a ,1/128));
//		float c=ALT_CI_FP_MULT_0(x[i],b );
//		float d=ALT_CI_FP_MULT_0(x[i],c);
//		sum+= 0.5*x[i]+x[i]*x[i]*(cos((x[i]-128)/128));
		//ALT_CI_FP_MULT_0(x[i], ALT_CI_FP_MULT_0(x[i], cos(ALT_CI_FP_MULT_0(ALT_CI_FP_SUB_0(x[i], 128),1/128)))) cos(ALT_CI_FP_MULT_0(ALT_CI_FP_SUB_0(x[i], 128) ,1/128)) ))
//		sum= ALT_CI_FP_ADD_0(sum,  ALT_CI_FP_ADD_0(ALT_CI_FP_MULT_0(0.5,x[i]),ALT_CI_FP_MULT_0(x[i],ALT_CI_FP_MULT_0(x[i],custom_cos_taylor(ALT_CI_FP_MULT_0((ALT_CI_FP_SUB_0(x[i], 128)),ff),3) )) ));
		sum= ALT_CI_FP_ADD_0(sum,  ALT_CI_FP_ADD_0(ALT_CI_FP_MULT_0(0.5,x[i]),ALT_CI_FP_MULT_0(x[i],ALT_CI_FP_MULT_0(x[i],lookupCos(ALT_CI_FP_MULT_0((ALT_CI_FP_SUB_0(x[i], 128.0)),ff)) )) ));
//		sum= ALT_CI_FP_ADD_0(sum,  ALT_CI_FP_ADD_0(ALT_CI_FP_MULT_0(0.5,x[i]),ALT_CI_FP_MULT_0(x[i],ALT_CI_FP_MULT_0(x[i],cos(ALT_CI_FP_MULT_0((ALT_CI_FP_SUB_0(x[i], 128)),ff)) )) ));


	}
//		printf("the current sum is %f, current xi is %f \n", sum,x[i]);}
	return sum;
// YOUR CODE GOES HERE
}


int main()
{
//	buildCosTable();
//	for(int i=0; i<90; i+=10) {
//	    printf("cos(%d) = %lf\n", i, lookupCos(i));
//	  }
	alt_putstr("hello");
	printf("Task 4!\n");
//	Define input vector
	float x[N];
 // Returned result
	float y;

	generateVector(x);

	clock_t exec_t1, exec_t2;
// 	 exec_t1 = times(NULL); // get system time before starting the process
// 	 y = sumVector(x, N);
//
// // till here
// 	 exec_t2 = times(NULL); // get system time after finishing the process
// 	 printf(" proc time = %d ticks \n", (unsigned int) (exec_t2-exec_t1));
// 	 int i;
// 	 for (i=0; i<10; i++){
// 		 y = y/2.0;}
// 	 printf("Result: %f \n", (float) y);
//

 	 exec_t1 = times(NULL); // get system time before starting the process
	 y = TaylorCustomSumVector(x, N);
 // till here
	 exec_t2 = times(NULL); // get system time after finishing the process
	 printf(" custom proc time = %d ticks \n", (unsigned int) (exec_t2-exec_t1));
	 int j;
	 for (j=0; j<10; j++){
		 y = y/2.0;}
	 printf("Custom Result: %f \n", (float) y);
//	 exec_t1 = times(NULL); // get system time before starting the process
//	 y = OneCustomSumVector(x, N);
//  // till here
//	 exec_t2 = times(NULL); // get system time after finishing the process
//	 printf(" taylor custom proc time = %d ticks \n", (unsigned int) (exec_t2-exec_t1));
////	 	 int j;
//	 for (j=0; j<10; j++){
//		 y = y/2.0;}
//	 printf("one taylor Custom Result: %f \n", (float) y);

//	 int j;
	 //	 for (j=0; j<10; j++){
	 //		 y = y/2.0;}
	 //	 printf("Custom Result: %f \n", (float) y);
//	 exec_t1 = times(NULL); // get system time before starting the process
//	 y = LUTCustomSumVector(x, N);
//   // till here
//	 exec_t2 = times(NULL); // get system time after finishing the process
//	 printf(" LUT custom proc time = %d ticks \n", (unsigned int) (exec_t2-exec_t1));
// //	 	 int j;
//	 for (j=0; j<10; j++){
//		 y = y/2.0;}
//	 printf("LUT Custom Result: %f \n", (float) y);

 	 return 0;
}
