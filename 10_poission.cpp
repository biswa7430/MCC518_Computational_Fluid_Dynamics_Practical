#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const int SIZE = 4; // Grid size for a 4x4 matrix
double h = 1.0;     // Grid spacing (assuming uniform grid)

double f(double x, double y)
{
    return -10 * (x * x + y * y + 10); // Function representing the source term
}

// Function to solve the 2D Poisson equation using Jacobi iteration with a specific update order
void solvePoisson(double u[SIZE][SIZE], int iterations)
{
    double u_new[SIZE][SIZE]; // Temporary storage for updated values
    
    for (int iter = 0; iter < iterations; ++iter)
    {
        // Copy the current values of u to u_new before starting the iteration
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                u_new[i][j] = u[i][j];
            }
        }

        // 1. First update values where i != j
        for (int i = 1; i < SIZE - 1; ++i)
        {
            for (int j = 1; j < SIZE - 1; ++j)
            {
                if (i != j)
                {
                    u_new[i][j] = 0.25 * (u[i - 1][j] + u[i + 1][j] + u[i][j - 1] + u[i][j + 1] - h * h * f(i * h, j * h));
                }
            }
        }

        // 2. Use the updated values to calculate positions where i == j
        for (int i = 1; i < SIZE - 1; ++i)
        {
            for (int j = 1; j < SIZE - 1; ++j)
            {
                if (i == j)
                {
                    u_new[i][j] = 0.25 * (u_new[i - 1][j] + u_new[i + 1][j] + u_new[i][j - 1] + u_new[i][j + 1] - h * h * f(i * h, j * h));
                }
            }
        }

        // Copy the new values back to u for the next iteration
        for (int i = 1; i < SIZE - 1; ++i)
        {
            for (int j = 1; j < SIZE - 1; ++j)
            {
                u[i][j] = u_new[i][j];
            }
        }

        // Print the matrix after each iteration
        cout << "Iteration " << iter + 1 << ":\n";
        for (int i = SIZE - 1; i >= 0; --i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                cout << fixed << setprecision(3) << setw(7) << u[i][j] << "\t";
            }
            cout << "\n";
        }
        cout << "\n";
    }
}

int main()
{
    int iterations;
    double u[SIZE][SIZE];

    cout << "Enter the number of iterations: ";
    cin >> iterations;

    // Initialize grid with zero values (initial guess)
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            u[i][j] = 0.0;
        }
    }


    // Solve using Jacobi iteration
    solvePoisson(u, iterations);

    return 0;
}
