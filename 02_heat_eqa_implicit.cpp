#include <iostream>
using namespace std;

const int N = 6;        // Number of spatial points (L/dx + 1)
const int M = 1;       // Number of time steps (T/dt)
const double r = 0.020875;   // Given ratio r = 0.5
const double dx = 2.0;
const double dt = 0.01;

// Function to set up the initial condition u(x, 0)
void initialCondition(double u[N]) {
    for (int j = 1; j < N-1; ++j) {
        double x = j * dx; // dx = 1
        //u[j] = 0.5 * x * (8 - x);
        u[j] = 0;
    }
}

// Function to solve the tridiagonal system using the Thomas algorithm
void thomasAlgorithm(double a[N-1], double b[N], double c[N-1], double d[N], double u_new[N]) {
    double c_prime[N];
    double d_prime[N];

    // Forward sweep
    c_prime[0] = c[0] / b[0];
    d_prime[0] = d[0] / b[0];

    for (int i = 1; i < N; ++i) {
        double denom = b[i] - a[i-1] * c_prime[i-1];
        if (i < N-1) c_prime[i] = c[i] / denom;
        d_prime[i] = (d[i] - a[i-1] * d_prime[i-1]) / denom;
    }

    // Back substitution
    u_new[N-1] = d_prime[N-1];
    for (int i = N-2; i >= 0; --i) {
        u_new[i] = d_prime[i] - c_prime[i] * u_new[i+1];
    }
}

int main() {
    // Arrays to store the current and next time step solutions
    double u[N] = {0.0};       // Solution array at current time step
    double u_new[N] = {0.0};   // Solution array at next time step

    // Initialize the solution with the initial condition
    initialCondition(u);


    // Coefficients for the tridiagonal matrix
    double a[N-1]; // sub-diagonal
    double b[N];   // main diagonal
    double c[N-1]; // super-diagonal
    for (int i = 0; i < N-1; ++i) {
        a[i] = -r;
        c[i] = -r;
    }
    for (int i = 0; i < N; ++i) {
        b[i] = 1 + 2 * r;
    }

    // Time-stepping loop
    for (int n = 0; n <= M; ++n) {
        // Apply boundary conditions
        u[0] = 100.0;      // Boundary condition at x = 0
        u[N-1] = 50.0;    // Boundary condition at x = 8

        // Print the current time step as a matrix
        cout << "Time step " << n << ":\n";
        for (int j = 0; j < N; ++j) {
            cout << u[j] << " ";
        }
        cout << "\n\n";

        if (n < M) {
            // Set up the right-hand side vector d
            double d[N];
            d[0] = 0.0;   // Boundary condition at x = 0
            d[N-1] = 0.0; // Boundary condition at x = L

            for (int j = 1; j < N-1; ++j) {
                d[j] = r * u[j-1] + (1 - 2 * r) * u[j] + r * u[j+1];
            }

            // Solve the tridiagonal system
            thomasAlgorithm(a, b, c, d, u_new);

            // Update the solution for the next time step
            for (int j = 0; j < N; ++j) {
                u[j] = u_new[j];
            }
        }
    }

    return 0;
}