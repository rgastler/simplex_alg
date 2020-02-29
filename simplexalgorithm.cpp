#include <iostream>

using std::cout;
using std::cin;
using std::endl;

#include <iomanip>

using std::setw;
using std::setiosflags;

	// Example 1: 2D
	// Maximize: P = 2x + 3y
	// Subject to the constraints:
	//		2x + y <= 18
	//		6x + 5y <= 60
	//		2x + 5y <= 40
	//		x, y >= 0

	// The linear programming problem written in matrix form.
// const int n = 2, m = 3;		// n = # of variables, m = # of constraints

/* double N[4][7] = { {1,-2,-3, 0, 0, 0,  0},
				   {0, 2, 1, 1, 0, 0, 18},
				   {0, 6, 5, 0, 1, 0, 60},
				   {0, 2, 5, 0, 0, 1, 40} }; */


	// Example 2: 3D
	// Maximize: P = 20x + 10y + 15z
	// Subject to the constraints:
	//		3x + 2y + 5z <= 55
	//		2x + y  + z  <= 26
	//		x  + y  + 3z <= 30
	//		5x + 2y + 4z <= 57
	//		x, y, z >= 0

	// The linear programming problem written in matrix form.
const int n = 3, m = 4;		// n = # of variables, m = # of constraints

double N[5][9] = { {1, -20, -10, -15, 0, 0, 0, 0,  0},
				   {0,   3,   2,   5, 1, 0, 0, 0, 55},
				   {0,   2,   1,   1, 0, 1, 0, 0, 26},
				   {0,   1,   1,   3, 0, 0, 1, 0, 30},
				   {0,   5,   2,   4, 0, 0, 0, 1, 57} };


bool optimal = false;		// Stops the main loop when changed to true.
int r, k;					// r = pivot row, k = pivot column.

void printarray(double[m + 1][n + m + 2]);
void findpivotcolumn(double[m + 1][n + m + 2], int&);
void findpivotrow(double[m + 1][n + m + 2], const int, int&);
void checkoptimal(double[m + 1][n + m + 2], bool&);
void rowreduce(double[m + 1][n + m + 2], const int, const int);
void showproblem(double[m + 1][n + m + 2]);


int main()
{

	showproblem(N);

	/* double sol[n+m] = {0};		// First feasible solution.
		for ( int i = n; i < n+m; i++ )
		{
			sol[i] = N[i-n+1][n+m+1];
		}
		for ( int i = 0; i < n+m; i++ )		// Show feasible solution just to check.
		{
			cout << sol[i] << endl;
		} */

	while (optimal == false)			// Main loop.
	{
		r = 1;
		k = 1;
		findpivotcolumn(N, k);
		findpivotrow(N, k, r);
		rowreduce(N, r, k);
		printarray(N);
		checkoptimal(N, optimal);
	}

	return 0;
}



// Displays matrix.
void printarray(double A[m + 1][n + m + 2])
{
	cout << endl;
	for (int i = 0; i < m + 1; i++)
	{
		for (int j = 0; j < n + m + 2; j++)
			cout << setw(5) << A[i][j] << ' ';

		cout << endl << endl;
	}
}



// Finds column corresponding to largest coeff. of obj. func.
void findpivotcolumn(double A[m + 1][n + m + 2], int& q)
{
	double min = 0;
	for (int j = 1; j < n + 1; j++)
	{
		if (A[0][j] <= min)
		{
			min = A[0][j];
			q = j;
		}
	}
}



// Finds row corresponding to smallest change given the column from above.
void findpivotrow(double A[m + 1][n + m + 2], const int q, int& p)
{
	bool killwhile = false;
	double min = 0;
	int l = 1;

	while (killwhile == false && l < m + 1)
	{
		if (A[l][q] > 0)
		{
			min = A[l][n + m + 1] / A[l][q];
			p = l;
			killwhile = true;
		}
		l++;
	}

	for (int i = p + 1; i < m + 1; i++)
	{
		if (A[i][q] > 0)
		{
			if (A[i][n + m + 1] / A[i][q] < min)
			{
				min = A[i][n + m + 1] / A[i][q];
				p = i;
			}
		}
	}
}



// Checks to see if we have the optimal solution.
void checkoptimal(double A[m + 1][n + m + 2], bool& opt)
{
	double min = 0;
	for (int j = 1; j < n + 1; j++)
	{
		if (A[0][j] <= min)
		{
			min = A[0][j];
		}
	}
	if (min == 0)
	{
		opt = true;
		cout << "The optimal solution has been found." << endl;
	}
	else
	{
		cout << "The optimal solution has NOT been found, more iterations are required." << endl;
	}
}



// Row reduced the input column to unit vector of input row.
void rowreduce(double A[m + 1][n + m + 2], const int p, const int q)
{
	double D = A[p][q];
	double E;
	for (int j = 0; j < n + m + 2; j++)
	{
		A[p][j] = A[p][j] / D;
	}

	for (int i = 0; i < p; i++)
	{
		E = A[i][q];
		for (int j = 0; j < n + m + 2; j++)
		{
			A[i][j] = A[i][j] - E * A[p][j];
		}
	}
	for (int i = p + 1; i < m + 1; i++)
	{
		E = A[i][q];
		for (int j = 0; j < n + m + 2; j++)
		{
			A[i][j] = A[i][j] - E * A[p][j];
		}
	}
}



// Displays the linear programming problem nicely.
void showproblem(double A[m + 1][n + m + 2])
{
	cout << endl;
	cout << "Maximize: P = ";
	for (int j = 1; j < n; j++)
	{
		cout << -A[0][j] << "*X[" << j << "] + ";
	}
	cout << -A[0][n] << "*X[" << n << "]";

	cout << endl << "Subject to: " << endl;
	for (int i = 1; i < m + 1; i++)
	{
		cout << setw(5);
		for (int j = 1; j < n; j++)
		{
			cout << A[i][j] << "*X[" << j << "] + ";
		}
		cout << A[i][n] << "*X[" << n << "] ";
		cout << "<= " << A[i][n + m + 1] << endl;
	}
}