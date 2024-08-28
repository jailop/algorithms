# Polynomial curve fitting
# An linear regression model implementation and testing
# (2020) Jaime Lopez <jailop AT gmail DOT com>

# In this script a linear regression experiment is run. It consist in finding
# polynomial curves to fit a generated sample data. Sample data correspond to
# the function sin(2*PI*x) plus random gaussian noise. Sample data is generated
# for the interval [0,1].

# Importing and setting libraries
# The model is used avoiding the usage of high level machine learning libraries.
# Only numpy and matplotlib are used.

import numpy as np
import matplotlib.pyplot as plt
np.random.seed(0)  # To repeat the experiment and get the same outputs

# Global parameters

N = 10000           # Size of sample dataset
MEAN = 0.0         # Mean of the noise gaussian distribution
STDEV = 0.8        # Standard deviation of the noise gaussian distribution
TRAIN_PROP = 0.1   # Proportion used for training from the sample dataset
TRIALS = 16     # Number of trials
NABLA = 0.9 
MAX_ITER = 1e4

# To generate the sample data. Three arrays are produced. The first one contains
# the x values, corresponding to N points in [0,1]. The second one is the sine
# of 2*PI*x. The third one is the previous plus a values from a gaussian
# distribution to simulate the presence of noise in the sample data. Results are
# stored in a matrix of N rows by 3 columns.

def generate_data():
    x = np.linspace(0, 1, N)
    y = np.sin(2 * np.pi * x)
    noise = np.random.normal(MEAN, STDEV, size=N)
    y_noised = y + noise
    data = np.array([x, y, y_noised]).transpose()
    return data

# A function is defined to extract from the sample dataset training and test
# datasets for X and y.

def train_test(X, y, split=0.8):
    n = X.shape[0]  # Number of observations
    # Getting indexes for datasets
    global_index = np.arange(n)
    train_size = round(n * split)
    train_index = np.random.choice(global_index, size=train_size, replace=False)
    test_index = np.setdiff1d(global_index, train_index)
    # Getting train and test datasets
    X_train = X[train_index, :]
    y_train = y[train_index]
    X_test = X[test_index, :]
    y_test = y[test_index]
    return X_train, y_train, X_test, y_test

# To get the model parameters, i.e. the coefficiente of the polynomial,
# represented by w, the gradient descent algorithm is implemented using the
# derivative of the cost function C = (1 / 2) \sum (y_hat - y)^2

def gradient_descent(X, y, nabla=0.01, max_iterations=1e4, step_error=1e-5):
    # Random initial values for w
    w = np.random.random(X.shape[1])
    optimized = False
    i = 0
    while i < max_iterations:
        y_hat = X.dot(w)
        dC = (y_hat - y).dot(X) # Derivative of the cost function
        # Parameters' updating
        aux = w - nabla * dC / len(y)
        diff = aux - w
        w = aux
        # Step error check
        if diff.dot(diff) < step_error:
            optimized = True
            break
        i += 1
    if not optimized:
        print('%d: Maximum number of iterations reached without optimization' % X.shape[1])    
    else:
        print('%d: Optimized at %d iteration' % (X.shape[1], i))
    return w

# A mean cost error function is defined to evaluate the model.

def rms(X, w, y):
    y_hat = X.dot(w)
    diff = y_hat - y
    cost = np.sqrt(diff.dot(diff) / len(X))
    return cost, y_hat

# A function is defined to compute the dataset as a polynomial. It's done adding
# new columns for the i-power, given i = 1, 2, ..., polynomial-grade.

def transform_x(X, grade=1):
    if grade == 1:
        return X
    aux = np.zeros((X.shape[0], grade + 1))
    aux[:, 0:2] = X
    for i in range(2, grade + 1):
        aux[:, i] = np.power(aux[:, 1], i)
    return aux

if __name__ == "__main__":
    # Preparing the datasets
    data = generate_data()
    X = np.ones((data.shape[0], 2))
    X[:, 1] = data[:, 0]
    y = data[:, 2]
    X_train, y_train, X_test, y_test = train_test(X, y, split=TRAIN_PROP)

    # Setting for trials
    errors = np.empty((3, TRIALS))
    fig, ax = plt.subplots(4, 4, figsize=(16, 16))

    x_full = np.ones((300, 2))
    x_full[:, 1] = np.linspace(0, 1, 300)
    y_real = np.sin(2 * np.pi * x_full[:, 1])
    for i in range(1, TRIALS + 1):
        errors[0, i - 1] = i

        X_train_transf = transform_x(X_train, i)
        X_test_transf = transform_x(X_test, i)

        w = gradient_descent(X_train_transf, y_train, nabla=NABLA, max_iterations=MAX_ITER)
        c, _ = rms(X_train_transf, w, y_train)
        errors[1, i - 1] = c
        c, _ = rms(X_test_transf, w, y_test)
        errors[2, i - 1] = c

        y_full = transform_x(x_full, i).dot(w)

        if i <= 16:
            # Plotting
            row = (i - 1) // 4
            col = i - 4 * row - 1
            ax[row, col].set_ylim((-2.5, 2.5))
            ax[row, col].plot(x_full[:, 1], y_full, label='Grade %s' % i)
            ax[row, col].plot(x_full[:, 1], y_real)
            ax[row, col].scatter(X_train[:, 1], y_train, s=0.5, c='grey', alpha=0.1)
            ax[row, col].scatter(X_test[:, 1], y_test, s=0.5, c='orange', alpha=0.1)
            ax[row, col].legend()

    plt.suptitle('Polynomial fitting for sin(2 \pi x) + noise N(0, 1)', fontsize=16)
    fig.savefig('trials.png')

    plt.figure(figsize=(16, 16))
    plt.plot(errors[0], errors[1], label='Training error')
    plt.plot(errors[0], errors[2], label='Generalization error')
    plt.xlabel('Polynomial grade')
    plt.ylabel('Root mean square error')
    plt.legend()
    plt.savefig('errors.png')
