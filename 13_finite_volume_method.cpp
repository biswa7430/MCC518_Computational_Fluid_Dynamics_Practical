#include <iostream>
#include <iomanip>

using namespace std;

// Function to display the symmetric tridiagonal matrix
void displayMatrix(double a[], double b[], double c[], double d[]) {
    cout << "\nThe symmetric tridiagonal matrix is:\n";
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (i == j) {
                cout << setw(10) << b[i]; // Main diagonal
            } else if (j == i + 1) {
                cout << setw(10) << c[i]; // Upper diagonal
            } else if (j == i - 1) {
                cout << setw(10) << a[i]; // Lower diagonal
            } else {
                cout << setw(10) << 0; // Zero entries
            }
        }
        cout << "\n";
    }
    cout << "\nThe right-hand side vector d is:\n";
    for (int i = 0; i < 5; ++i) {
        cout << "d[" << (i + 1) << "] = " << d[i] << "\n"; // Display d[i]
    }
}

// Function to solve the tridiagonal system
void solveTridiagonal(double K_A_deltaX, double T_A, double T_B, double T[]) {
    double a[5] = {0.0}; // Lower diagonal
    double b[5] = {0.0}; // Main diagonal
    double c[5] = {0.0}; // Upper diagonal
    double d[5] = {0.0}; // Right-hand side

    // Set up the tridiagonal matrix
    b[0] = K_A_deltaX + 2 * K_A_deltaX; // Main diagonal coefficient for T1
    c[0] = -K_A_deltaX; // Upper diagonal coefficient for T1
    d[0] = 2 * K_A_deltaX * T_A; // Right-hand side

    // For T2, T3, T4
    for (int i = 1; i < 4; ++i) {
        a[i] = -K_A_deltaX; // Lower diagonal coefficient
        b[i] = 2 * K_A_deltaX; // Main diagonal coefficient
        c[i] = -K_A_deltaX; // Upper diagonal coefficient
        d[i] = 0.0; // Right-hand side
    }

    // For T5
    a[4] = -K_A_deltaX; // Lower diagonal coefficient for T5
    b[4] = K_A_deltaX + 2 * K_A_deltaX; // Main diagonal coefficient for T5
    d[4] = 2*K_A_deltaX * T_B; // Right-hand side

    // Display the tridiagonal matrix
    displayMatrix(a, b, c, d);

    // Thomas algorithm to solve the system
    for (int i = 1; i < 5; ++i) {
        double m = a[i] / b[i - 1];
        b[i] -= m * c[i - 1];
        d[i] -= m * d[i - 1];
    }

    // Back substitution
    T[4] = d[4] / b[4]; // T5
    for (int i = 3; i >= 0; --i) {
        T[i] = (d[i] - c[i] * T[i + 1]) / b[i];
    }
}

int main() {
    double K, A, deltaX, T_A, T_B;

    // Input parameters
    cout << "Enter the thermal conductivity (K): ";
    cin >> K;
    cout << "Enter the cross-sectional area (A): ";
    cin >> A;
    cout << "Enter the distance between nodal points (deltaX): ";
    cin >> deltaX;
    cout << "Enter temperature at boundary point A (T_A): ";
    cin >> T_A;
    cout << "Enter temperature at boundary point B (T_B): ";
    cin >> T_B;

    // Calculate KA/del(x)
    double K_A_deltaX = K * A / deltaX;
    cout << "The value of KA/del(x) is: " << K_A_deltaX << "\n";

    // Temperature array for the 5 intermediate points
    double T[5];


    // Solve the tridiagonal system to find T1, T2, T3, T4
    solveTridiagonal(K_A_deltaX, T_A, T_B, T);

    // Output the results
    cout << fixed << setprecision(2);
    cout << "Calculated temperatures at the intermediate nodal points:\n";
    for (int i = 0; i < 5; ++i) {
        cout << "T[" << (i + 1) << "] = " << T[i] << " °C\n";
    }

    return 0;
}