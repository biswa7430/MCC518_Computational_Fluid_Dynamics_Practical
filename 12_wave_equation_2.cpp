#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

#define X 5
#define T 5

float fun(float x) {
    return x * (1 - x);
}

int main() {
    float u[X + 1][T + 1], c, h, k;
    int i, j;

    cout << "\nEnter the valu of c: ";
    cin >> c;
    cout<< "\nEnter the value of h : ";
    cin>> h;
    k = h/c;
    cout<<"\nThe value of k is : "<<k;

    // Initialize boundary values for all time steps
    for (j = 0; j <= T; j++) {
        u[0][j] = 0;
        u[X][j] = 0;
    }

    // Initialize values for i = 1 to X - 1 at t = 0 and t = 1
    for (i = 1; i <= X - 1; i++) {
        u[i][0] = fun(i*h);
        u[i][1] = k + u[i][0]; // u_t(x,0) = 1
    }
    

    // Compute values for t = 1 to T - 1
    for (j = 1; j <= T - 1; j++) {
        for (i = 1; i <= X - 1; i++) {
            u[i][j + 1] = u[i - 1][j] + u[i + 1][j] - u[i][j - 1];
        }
    }


    // Display the results
    cout << "\nThe values of u[i][j] are:\n";
    for (j = 0; j <= T; j++) {
        for (i = 0; i <= X; i++) {
            cout << setw(6) << fixed << setprecision(2) << u[i][j];
        }
        cout << "\n";
    }

    return 0;
}
