#include <iostream>
#include <iomanip>
using namespace std;

float x[10];

float* tridiagonal(float r, float d[], int n) {
    int i;
    float a = -r*0.5, b = (1 + r), c = -r*0.5;
    float alpha[10], beta[10];
    alpha[1] = b;
    beta[1] = d[1] / b;
    for (i = 2; i < n; i++) {
        alpha[i] = b - (a * c / alpha[i - 1]);
        beta[i] = (d[i] - a * beta[i - 1]) / alpha[i];
    }
    x[n - 1] = beta[n - 1];
    for (i = n - 2; i >= 1; i--) {
        x[i] = beta[i] - (c * x[i + 1]) / alpha[i];
    }
    return x;
}

int main() {
    int i, j, m, n;
    float u[20][20], h, k, c, r;

    cout << "Enter the value of c: ";
    cin >> c;
    cout << "Enter the value of dx: ";
    cin >> h;
    cout << "Enter the value of dy: ";
    cin >> k;
    cout << "Enter the value of m and n:\n";
    cin >> m >> n;

    r = (k * c * c) / (h * h);
    cout<<"The value of r is "<<r<<"\n";

    // Boundary Conditions
    for (j = 0; j <= m; j++) {
        u[0][j] = 0;
        u[n][j] = 0;
    }

    //Initial Conditions
    for (i = 1; i < n; i++) {
        float x = i*h;
        if (x <= 0.5)
        {
            u[i][0] = 2*x;
        } else {
            u[i][0] = 2*(1-x);
        }
    }

    float d[n];
    for (j = 0; j < m; j++) {
        for (i = 1; i < n; i++) {
            d[i] = r*0.5 * (u[i + 1][j] + u[i - 1][j]) +  (1 - r) * u[i][j];
        }
        float* y = tridiagonal(r, d, n);
        for (i = 1; i < n; i++) {
            u[i][j + 1] = y[i];
        }
    }

    cout << "The value of all u(i,j):\n";
    for (j = m; j >= 0; j--) {
        for (i = 0; i <= n; i++) {
            cout << fixed << setprecision(2) << setw(7) << u[i][j] << "\t";
        }
        cout << "\n";
    }

    return 0;
}