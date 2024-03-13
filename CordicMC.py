import numpy as np
import math
import scipy.stats as stats

def conversion(num,width):
    
    res=""
    if num>=0: 
        res+="0"
    else:
        res+="1"
        num=abs(num)
    # num=num-int(num)    # print (num)
    for i in range (0,width-1):
        # print(2**(-i))
        # print(res)
        v=2**(-i)
        if num >= v:
            num-=v
            res+="1"
        else:
            res+="0"
    return res
def backconversion(numstr):
    res=0
    # if numstr[1]=="1":
    #     res+=1
    for i in range (1,len(numstr)):
        if numstr[i]=="1":
            res+=2**(-(i)+1)
    if numstr[0]=="1":
        res=-res
    return res
def changeNumToWidth(num,width):
    return backconversion(conversion(num,width))

x=[None]*22
y=[None]*22
z=[None]*22
e = [
    "001100100100001111110110100",
    "000111011010110001100111000",
    "000011111010110110111010110",
    "000001111111010101101110100",
    "000000111111111010101011010",
    "000000011111111111010101010",
    "000000001111111111111010100",
    "000000000111111111111111010",
    "000000000011111111111111110",
    "000000000001111111111111110",
    "000000000000111111111111111",
    # "00000000000011100100110000",
    # "00000000000001110010011000",
    # "00000000000000111001001100",
    # "00000000000000011100100110",
    # "00000000000000001110010011",
    # "00000000000000000111001001",
    # "00000000000000000011100100",
    # "00000000000000000001110010",
    # "00000000000000000000111001",
    # "00000000000000000000011100",
    # "00000000000000000000001110",


    "000000000000011111111111111",
    "000000000000001111111111111",
    "000000000000000111111111111",
    "000000000000000011111111111",
    "000000000000000001111111111",
    "000000000000000000111111111",
    "000000000000000000011111111",
    "000000000000000000001111111",
    "000000000000000000000111111",
    "000000000000000000000011111",
    "000000000000000000000001111"
]
FB=25
IT=22


angles = [
    conversion(math.atan(2**-i),27)  for i in range(22)
]






def cordic_cos(angle):
    iterations=15
    w=28
    x[0]=backconversion("00100110110111010011101101")
    y[0]=0
    z[0]=changeNumToWidth(angle,w)
    for i in range(0,iterations-1):
        # print(i)
        if z[i]>=0:
            x[i+1]=changeNumToWidth(x[i]-y[i]*(2**-i),w)
            y[i+1]=changeNumToWidth(y[i]+x[i]*(2**-i),w)
            z[i+1]=changeNumToWidth(z[i]-backconversion(e[i]),w)
        else:
            x[i+1]=changeNumToWidth(x[i]+y[i]*(2**-i),w)
            y[i+1]=changeNumToWidth(y[i]-x[i]*(2**-i),w)
            z[i+1]=changeNumToWidth(z[i]+backconversion(e[i]),w)
    # CORDIC block implementation (replace with your own code)
    # This is a placeholder function that returns the cosine of the angle
    return changeNumToWidth(x[iterations-1],w)

def monte_carlo_error_test(num_iterations, num_angles):
    accumulated_squared_error_cordic = 0
    errors = []

    # accumulated_squared_error_double = 0

    for _ in range(num_iterations):
        for _ in range(num_angles):
            # Generate a random angle between 0 and 2π
            random_angle =np.float32( np.random.uniform(-1, 1))

            # Calculate the expected cosine value using the math library (double precision)
            expected_cos_double = np.cos(random_angle)

            # Calculate the cosine value using the CORDIC block
            cordic_cos_val = cordic_cos(random_angle)

            # Calculate the squared error for CORDIC
            error_cordic = (expected_cos_double - cordic_cos_val)
            errors.append(error_cordic)
            # accumulated_squared_error_cordic += squared_error_cordic
            
            # Calculate the expected cosine value using double precision
            # expected_cos_val = np.cos(random_angle)

            # # Calculate the squared error for double precision
            # squared_error_double = (expected_cos_double - expected_cos_val) ** 2
            # accumulated_squared_error_double += squared_error_double

    # Calculate the mean squared error (MSE) for CORDIC and double precision
    mean_error = np.mean(errors)
    sem = stats.sem(errors)  # Standard error of the mean
    confidence_interval = stats.t.interval(0.95, len(errors)-1, loc=mean_error, scale=sem)
    mse_cordic = accumulated_squared_error_cordic / (num_iterations * num_angles)
    # mse_double = accumulated_squared_error_double / (num_iterations * num_angles)

    # return mse_cordic
    return mean_error, confidence_interval
# Configuration
num_iterations = 1000
num_angles = 100

# Run the Monte Carlo error test
# print("running")
# # mse_cordic= monte_carlo_error_test(num_iterations, num_angles)
# mean_error, confidence_interval = monte_carlo_error_test(num_iterations, num_angles)
# print(f"Mean error: {mean_error}")
# print(f"95% Confidence Interval: {confidence_interval}")
print(conversion(0.607252935,28))
print(backconversion("10000110000010101001001000"))
# print(f"Mean Squared Error (MSE) - CORDIC: {mse_cordic}")
# print(conversion(0.001953123,27))
# print(f"Mean Squared Error (MSE) - Double Precision: {mse_double}")