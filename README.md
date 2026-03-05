# CS3339 - Homework 2

## Name
Sarbocha Pandey

## Description
This program takes two positive floating-point numbers, a loop bound and a loop counter and checks whether repeatedly adding the counter to a variable will eventually have no effect due to floating-point precision limits. It prints the IEEE 754 binary representation of both inputs, and if overflow is possible, it prints the threshold value where the overflow begins.

## Files
- `fp_overflow_checker.cpp` - main implementation
- `README.md` - this file

## How to Compile
Open a terminal in the project directory and run:
```
g++ -o fp_overflow_checker fp_overflow_checker.cpp
```

## How to Run
```
./fp_overflow_checker <loop_bound> <loop_counter>
```

## Examples
```
./fp_overflow_checker 1e+08 1.0
./fp_overflow_checker 1e+05 2.0
./fp_overflow_checker 1.4567 3.14
```
