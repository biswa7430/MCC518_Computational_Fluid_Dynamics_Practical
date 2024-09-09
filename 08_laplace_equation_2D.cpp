#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const int SIZE = 4; // Fixed grid size for 4x4 matrix

// Function to perform the Jacobi iteration for 2D Laplace equation
void jacobi(float u[SIZE][SIZE], int iterations) {
    float u_new[SIZE][SIZE];
    
    for (int iter = 0; iter < iterations; ++iter) {
        // Copy the current values of u to u_new
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                u_new[i][j] = u[i][j];
            }
        }

        // Initial case: Apply diagonal formula for u[1][1]
        if (iter == 0) {
            u_new[1][1] = 0.25 * (u[0][0] + u[0][2] + u[2][0] + u[2][2]);
            u[1][1] = 0.25 * (u[0][0] + u[0][2] + u[2][0] + u[2][2]);
        }

        // Update values using Jacobi iteration for all points
        for (int i = 1; i < SIZE - 1; ++i) {
            for (int j = 1; j < SIZE - 1; ++j) {
                // Use the standard Jacobi formula for all points
                if(iter == 0 && i ==1 && j==1){
                    //cout<<"Pass "<<u_new[i][j]<<"\n";
                    continue;
                } 
                if(iter == 0){
                u_new[i][j] = 0.25 * (u_new[i + 1][j] + u_new[i - 1][j] + u_new[i][j + 1] + u_new[i][j - 1]);
                } else {
                    u_new[i][j] = 0.25 * (u[i + 1][j] + u[i - 1][j] + u[i][j + 1] + u[i][j - 1]);
                }
            }
        }

        // Copy the new values back to u
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                u[i][j] = u_new[i][j];
            }
        }

        // Print the matrix after each iteration
        cout << "Iteration " << iter + 1 << ":\n";
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                cout << fixed << setprecision(2) << setw(7) << u[i][j] << "\t";
            }
            cout << "\n";
        }
        cout << "\n";
    }
}

int main() {
    int iterations;
    float u[SIZE][SIZE];

    cout << "Enter the number of iterations: ";
    cin >> iterations;

    // Input boundary conditions
    cout << "Enter the boundary conditions:\n";
    cout << "top boundary (4 values): ";
    for (int j = 0; j < SIZE; ++j) {
        cin >> u[0][j]; // Bottom row
    }

    cout << "Bottom boundary (4 values): ";
    for (int j = 0; j < SIZE; ++j) {
        cin >> u[SIZE - 1][j]; // Top row
    }

    cout << "Left middle boundary (2 values): ";
    for (int i = 1; i < SIZE - 1; ++i) {
        cin >> u[i][0]; // Left column
    }

    cout << "Right middle boundary (2 values): ";
    for (int i = 1; i < SIZE - 1; ++i) {
        cin >> u[i][SIZE - 1]; // Right column
    }

    // Initialize interior points to zero or another initial guess
    for (int i = 1; i < SIZE - 1; ++i) {
        for (int j = 1; j < SIZE - 1; ++j) {
            u[i][j] = 0.0; // Initial guess
        }
    }

    // Solve using Jacobi iteration
    jacobi(u, iterations);

    return 0;
}