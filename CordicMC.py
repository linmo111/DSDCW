import numpy as np
import math

def conversion(num):
    
    res=""
    num=num-int(num)    # print (num)
    for i in range (1,25):
        # print(2**(-i))
        # print(res)
        if num >= 2**(-i):
            num-=2**(-i)
            res+="1"
        else:
            res+="0"
    return "00"+res
def backconversion(numstr):
    res=0
    if numstr[1]=="1":
        res+=1;
    for i in range (2,len(numstr)):
        if numstr[i]=="1":
            res+=2**(-(i)+1)
    if numstr[0]=="1":
        res=-res
    return res


x=[None]*22
y=[None]*22
z=[None]*22
e = [
    "00110010010000111111011010",
    "00011101101011000110011100",
    "00001111101011011011101011",
    "00000111111101010110111010",
    "00000011111111101010101101",
    "00000001111111111101010101",
    "00000000111111111111101010",
    "00000000011111111111111101",
    "00000000001111111111111111",
    "00000000000111111111111111",
    "00000000000011111111111111",
    "00000000000001111111111111",
    "00000000000000111111111111",
    "00000000000000011111111111",
    "00000000000000001111111111",
    "00000000000000000111111111",
    "00000000000000000011111111",
    "00000000000000000001111111",
    "00000000000000000000111111",
    "00000000000000000000011111",
    "00000000000000000000001111",
    "00000000000000000000000111"
]









def cordic_cos(angle):
    x[0]=backconversion("00100110110111010011101101")
    y[0]=0
    z[0]=backconversion(conversion(angle))
    for i in range(0,21):
        # print(i)
        if z[i]>0:
            x[i+1]=x[i]-y[i]*(2**-i)
            y[i+1]=y[i]+x[i]*(2**-i)
            z[i+1]=z[i]-backconversion(e[i])
        else:
            x[i+1]=x[i]+y[i]*(2**-i)
            y[i+1]=y[i]-x[i]*(2**-i)
            z[i+1]=z[i]+backconversion(e[i])
    # CORDIC block implementation (replace with your own code)
    # This is a placeholder function that returns the cosine of the angle
    return backconversion(conversion(x[21]))

def monte_carlo_error_test(num_iterations, num_angles):
    accumulated_squared_error_cordic = 0
    # accumulated_squared_error_double = 0

    for _ in range(num_iterations):
        for _ in range(num_angles):
            # Generate a random angle between 0 and 2π
            random_angle = np.random.uniform(-1, 1)

            # Calculate the expected cosine value using the math library (double precision)
            expected_cos_double = math.cos(random_angle)

            # Calculate the cosine value using the CORDIC block
            cordic_cos_val = cordic_cos(random_angle)

            # Calculate the squared error for CORDIC
            squared_error_cordic = (expected_cos_double - cordic_cos_val) ** 2
            accumulated_squared_error_cordic += squared_error_cordic

            # Calculate the expected cosine value using double precision
            # expected_cos_val = np.cos(random_angle)

            # # Calculate the squared error for double precision
            # squared_error_double = (expected_cos_double - expected_cos_val) ** 2
            # accumulated_squared_error_double += squared_error_double

    # Calculate the mean squared error (MSE) for CORDIC and double precision
    mse_cordic = accumulated_squared_error_cordic / (num_iterations * num_angles)
    # mse_double = accumulated_squared_error_double / (num_iterations * num_angles)

    return mse_cordic
# Configuration
num_iterations = 1000
num_angles = 1000

# Run the Monte Carlo error test
mse_cordic= monte_carlo_error_test(num_iterations, num_angles)

print(f"Mean Squared Error (MSE) - CORDIC: {mse_cordic}")
# print(f"Mean Squared Error (MSE) - Double Precision: {mse_double}")