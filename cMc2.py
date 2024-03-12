import numpy as np
import math
import scipy.stats as stats

# Define the initial parameters and the CORDIC gain, using Q1.29 representation
NUM_FRACTIONAL_BITS = 24
INITIAL_X = int(0.607252935 * (2**NUM_FRACTIONAL_BITS))  # Convert 1/K to Q1.29
ITERATIONS = 20

# Define the fixed CORDIC angles in Q1.29 representation
angles = [
    int(math.atan(2**-i) * (2**NUM_FRACTIONAL_BITS)) for i in range(ITERATIONS)
]

def cordic_cosine(angle_float):
    # NUM_FRACTIONAL_BITS = 24
    # Convert the floating-point angle to Q1.29 representation
    z = int(angle_float * (2**NUM_FRACTIONAL_BITS))

    x = INITIAL_X
    y = 0
    count = 0

    # Perform CORDIC iterations
    for iter in range(ITERATIONS):
        if z >= 0:
            x_next = x - (y >> iter)
            y_next = y + (x >> iter)
            z_next = z - angles[iter]
        else:
            x_next = x + (y >> iter)
            y_next = y - (x >> iter)
            z_next = z + angles[iter]
        if x_next >= 2**NUM_FRACTIONAL_BITS or y_next >= 2**NUM_FRACTIONAL_BITS or z_next >= 2**NUM_FRACTIONAL_BITS:
            count+=1
        # print(y_next)
        x, y, z = x_next, y_next, z_next
    
    # Convert the result back to floating-point from Q1.29
    # print(count)
    cosine = x / (2**NUM_FRACTIONAL_BITS)
    return cosine

def monte_carlo_mean_error_and_confidence(num_samples=100000):
    errors = []

    for _ in range(num_samples):
        # Generate a random angle in the range [-1, 1], convert to radians
        angle = np.float32(np.random.uniform(-1, 1))
        # Calculate the cosine using the CORDIC algorithm
        cos_cordic = cordic_cosine(angle)
        # Calculate the cosine using Python's math library
        cos_ref = math.cos(angle)
        # Compute the error
        error = abs(cos_ref - cos_cordic)
        errors.append(error)

    # Calculate the mean error and the 95% confidence interval
    mean_error = np.mean(errors)
    sem = stats.sem(errors)  # Standard error of the mean
    confidence_interval = stats.t.interval(0.95, len(errors)-1, loc=mean_error, scale=sem)

    return mean_error, confidence_interval

# Run the Monte Carlo simulation to estimate the mean error and 95% confidence interval
mean_error, confidence_interval = monte_carlo_mean_error_and_confidence()
print(f"Mean error: {mean_error}")
print(f"95% Confidence Interval: {confidence_interval}")