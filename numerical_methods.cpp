#include "numerical_methods.h"
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// 1. Phuong phap Chia doi (Bisection)
double chiaDoi(function<double(double)> f, double a, double b, double tol, int max_iter, bool show_steps) {
    if (f(a) * f(b) >= 0) {
        cout << "Loi: Ham so khong doi dau tai 2 dau mut a va b!\n";
        return NAN;
    }
    double c = a;
    if (show_steps) {
        cout << "\n--- PHUONG PHAP CHIA DOI ---\n";
        cout << setw(6) << "Buoc" << setw(12) << "a" << setw(12) << "b" << setw(12) << "c" << setw(15) << "f(c)" << endl;
    }
    for (int i = 1; i <= max_iter; i++) {
        c = (a + b) / 2.0;
        if (show_steps) {
            cout << setw(6) << i << setw(12) << fixed << setprecision(6) << a 
                 << setw(12) << b << setw(12) << c << setw(15) << f(c) << endl;
        }
        if (abs(f(c)) < 1e-12 || (b - a) / 2.0 < tol) {
            return c;
        }
        if (f(a) * f(c) < 0) {
            b = c;
        } else {
            a = c;
        }
    }
    return c;
}

// 2. Phuong phap Lap don (Fixed-point iteration)
double lapDon(function<double(double)> phi, double x0, double tol, int max_iter, bool show_steps) {
    double x_prev = x0;
    double x_curr = 0;
    if (show_steps) {
        cout << "\n--- PHUONG PHAP LAP DON ---\n";
        cout << setw(6) << "Buoc" << setw(15) << "x_k" << setw(15) << "|x_k - x_{k-1}|" << endl;
    }
    for (int i = 1; i <= max_iter; i++) {
        x_curr = phi(x_prev);
        double diff = abs(x_curr - x_prev);
        if (show_steps) {
            cout << setw(6) << i << setw(15) << fixed << setprecision(6) << x_curr << setw(15) << diff << endl;
        }
        if (diff < tol) {
            return x_curr;
        }
        x_prev = x_curr;
    }
    return x_curr;
}

// 3. Phuong phap Tiep tuyen Newton (Newton-Raphson)
double tiepTuyenNewton(function<double(double)> f, function<double(double)> df, double x0, double tol, int max_iter, bool show_steps) {
    double x_prev = x0;
    double x_curr = 0;
    if (show_steps) {
        cout << "\n--- PHUONG PHAP TIEP TUYEN NEWTON ---\n";
        cout << setw(6) << "Buoc" << setw(15) << "x_k" << setw(15) << "f(x_k)" << endl;
    }
    for (int i = 1; i <= max_iter; i++) {
        double df_val = df(x_prev);
        if (abs(df_val) < 1e-12) {
            cout << "Dao ham qua nho, dung thuat toan.\n";
            return x_prev;
        }
        x_curr = x_prev - f(x_prev) / df_val;
        if (show_steps) {
            cout << setw(6) << i << setw(15) << fixed << setprecision(6) << x_curr << setw(15) << f(x_curr) << endl;
        }
        if (abs(x_curr - x_prev) < tol || abs(f(x_curr)) < tol) {
            return x_curr;
        }
        x_prev = x_curr;
    }
    return x_curr;
}

// 4. Phuong phap Day cung (Secant)
double dayCung(function<double(double)> f, double x0, double x1, double tol, int max_iter, bool show_steps) {
    double x_prev2 = x0;
    double x_prev1 = x1;
    double x_curr = 0;
    if (show_steps) {
        cout << "\n--- PHUONG PHAP DAY CUNG ---\n";
        cout << setw(6) << "Buoc" << setw(15) << "x_k" << setw(15) << "f(x_k)" << endl;
    }
    for (int i = 1; i <= max_iter; i++) {
        double f1 = f(x_prev1);
        double f2 = f(x_prev2);
        if (abs(f1 - f2) < 1e-12) {
            cout << "Mau so qua nho, dung thuat toan.\n";
            return x_prev1;
        }
        x_curr = x_prev1 - f1 * (x_prev1 - x_prev2) / (f1 - f2);
        if (show_steps) {
            cout << setw(6) << i << setw(15) << fixed << setprecision(6) << x_curr << setw(15) << f(x_curr) << endl;
        }
        if (abs(x_curr - x_prev1) < tol || abs(f(x_curr)) < tol) {
            return x_curr;
        }
        x_prev2 = x_prev1;
        x_prev1 = x_curr;
    }
    return x_curr;
}