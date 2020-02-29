The Simplex Algorithm with C++

(Click 'raw' to see this in a better view.)
This code is designed to use the simplex algorithm to solve linear programming problems like the following:
Maximize: P = 2x + 3y (or P - 2x - 3y = 0 for reference later)
Subject to constraints:
2x + y <= 18
6x + 5y <= 60
2x + 5y <= 40
x, y >= 0

In this problem, n = 2 (# of variables) and m = 3 (# of constraints).  The simplex algorithm applies a sequence of row operations and column/row pivots on a matrix to find the optimal solution to the system.  The matrix looks like the following.

P   x   y            #
1  -2  -3  0  0  0   0
0   2   1  1  0  0  18
0   6   5  0  1  0  60
0   2   5  0  0  1  40

In order to solve another system, 
1. Copy the code.
2. Set the values of n and m in the statement:     const int n = 3, m = 4;		// n = # of variables, m = # of constraints
3. Create the matrix using the coefficients of the function to maximize and the constraints.  Note:  Constraints must be of the form Ax + By <= C
For example: double N[4][7] = { {1,-2,-3, 0, 0, 0,  0},
				                        {0, 2, 1, 1, 0, 0, 18},
				                        {0, 6, 5, 0, 1, 0, 60},
				                        {0, 2, 5, 0, 0, 1, 40} };
                                
Note:  I have not explored situations where the feasible region (bounded by the constraints) is infinite and there is no optimal solution.  At some point, I will construct one and try that out.  
