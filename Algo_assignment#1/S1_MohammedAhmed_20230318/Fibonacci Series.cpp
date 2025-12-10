#include "bits/stdc++.h"
using namespace std;

// Fibonacci series using recursion
int Fibonacci_Recursion(int n) {
    if(n <= 1) return n;
    return Fibonacci_Recursion(n-1) + Fibonacci_Recursion(n-2);
}

///////////////////////////////////////////////////////////////////////

// Fibonacci series using divide and conquer (matrix multiplication)
struct Matrix
{
    long long M[2][2]; // transformation matrix

    Matrix()
    {
        M[0][0] = 1;
        M[0][1] = 1;
        M[1][0] = 1;
        M[1][1] = 0;
    }

    Matrix operator*(const Matrix &other) const
    {
        Matrix result;
        result.M[0][0] = M[0][0] * other.M[0][0] + M[0][1] * other.M[1][0];
        result.M[0][1] = M[0][0] * other.M[0][1] + M[0][1] * other.M[1][1];
        result.M[1][0] = M[1][0] * other.M[0][0] + M[1][1] * other.M[1][0];
        result.M[1][1] = M[1][0] * other.M[0][1] + M[1][1] * other.M[1][1];
        return result;
    }
};

Matrix Rec_matrix(Matrix base, long long n) {
    if (n == 1)
        return base;

    Matrix half = Rec_matrix(base, n / 2);
    Matrix result;

    if (n % 2 == 1) { // odd
        result = half * half;
        result = result * base;
    } else { // even
        result = half * half;
    }
    return result;
}

long long Fibonacci_Matrix(long long n) {
    if (n < 0)
        return -1;
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;

    --n;
    Matrix base;
    Matrix result = Rec_matrix(base, n);
    return result.M[0][0];
}

///////////////////////////////////////////////////////////////////////

// Fibonacci series using dynamic programming
long long fib_dp(long long n) {
    if (n < 0) return -1; // invalid
    if (n == 0) return 0;
    if (n == 1) return 1;
    long long a = 0, b = 1;
    for (long long i = 2; i <= n; ++i) {
        long long c = a + b;
        a = b;
        b = c;
    }
    return b;
}


///////////////////////////////////////////////////////////////////////

int main() {
    int choice;
    long long n;

    cout << "==============================\n";
    cout << " Fibonacci Series Calculator\n";
    cout << "==============================\n";
    cout << "1. Recursion Method\n";
    cout << "2. Divide & Conquer (Matrix Multiplication)\n";
    cout << "3. Dynamic Programming\n";
    cout << "------------------------------\n";
    cout << "Enter your choice (1-3): ";
    cin >> choice;

    cout << "Enter n: ";
    cin >> n;

    long long result;

    switch (choice) {
        case 1:
            result = Fibonacci_Recursion(n);
            cout << "Fibonacci(" << n << ") = " << result << " [Recursion]" << endl;
            break;
        case 2:
            result = Fibonacci_Matrix(n);
            cout << "Fibonacci(" << n << ") = " << result << " [Matrix Method]" << endl;
            break;
        case 3:
            result = fib_dp(n);
            cout << "Fibonacci(" << n << ") = " << result << " [Dynamic Programming]" << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
            break;
    }
}
