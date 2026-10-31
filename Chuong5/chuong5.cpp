#include <iostream>
#include <cmath>
#include <iomanip>
#include <functional>

using namespace std;

// 1. Phuong phap Chia doi (Bisection)
double chiaDoi(function<double(double)> f, double a, double b,
               double tol, int max_iter, bool show_steps = true) {

    if (f(a) * f(b) >= 0) {
        cout << "Loi: Ham so khong doi dau tai 2 dau mut a va b!\n";
        return NAN;
    }

    double c = a;

    if (show_steps) {
        cout << "\n--- PHUONG PHAP CHIA DOI ---\n";
        cout << setw(6) << "Buoc" << setw(12) << "a"
             << setw(12) << "b" << setw(12) << "c"
             << setw(15) << "f(c)" << endl;
    }

    for (int i = 1; i <= max_iter; i++) {
        c = (a + b) / 2.0;

        if (show_steps) {
            cout << setw(6) << i
                 << setw(12) << fixed << setprecision(8) << a
                 << setw(12) << b << setw(12) << c
                 << setw(15) << f(c) << endl;
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
double lapDon(function<double(double)> phi, double x0,
              double tol, int max_iter, bool show_steps = true) {

    double x_prev = x0;
    double x_curr = 0;

    if (show_steps) {
        cout << "\n--- PHUONG PHAP LAP DON ---\n";
        cout << setw(6) << "Buoc" << setw(15) << "x_k"
             << setw(20) << "|x_k - x_(k-1)|" << endl;
    }

    for (int i = 1; i <= max_iter; i++) {
        x_curr = phi(x_prev);
        double diff = abs(x_curr - x_prev);

        if (show_steps) {
            cout << setw(6) << i
                 << setw(15) << fixed << setprecision(8) << x_curr
                 << setw(20) << diff << endl;
        }

        if (diff < tol) {
            return x_curr;
        }

        x_prev = x_curr;
    }

    return x_curr;
}


// 3. Phuong phap Tiep tuyen Newton (Newton-Raphson)
double tiepTuyenNewton(function<double(double)> f,
                       function<double(double)> df,
                       double x0, double tol, int max_iter,
                       bool show_steps = true) {

    double x_prev = x0;
    double x_curr = 0;

    if (show_steps) {
        cout << "\n--- PHUONG PHAP TIEP TUYEN NEWTON ---\n";
        cout << setw(6) << "Buoc" << setw(15) << "x_k"
             << setw(15) << "f(x_k)" << endl;
    }

    for (int i = 1; i <= max_iter; i++) {
        double df_val = df(x_prev);

        if (abs(df_val) < 1e-12) {
            cout << "Dao ham qua nho, dung thuat toan.\n";
            return x_prev;
        }

        x_curr = x_prev - f(x_prev) / df_val;

        if (show_steps) {
            cout << setw(6) << i
                 << setw(15) << fixed << setprecision(8) << x_curr
                 << setw(15) << f(x_curr) << endl;
        }

        if (abs(x_curr - x_prev) < tol || abs(f(x_curr)) < tol) {
            return x_curr;
        }

        x_prev = x_curr;
    }

    return x_curr;
}

// 4. Phuong phap Day cung theo slide
double dayCung(function<double(double)> f, double a, double b,
               double tol, int max_iter, bool show_steps = true) {

    if (f(a) * f(b) >= 0) {
        cout << "Loi: Ham so khong doi dau tai 2 dau mut a va b!\n";
        return NAN;
    }

    double x = 0;

    if (show_steps) {
        cout << "\n--- PHUONG PHAP DAY CUNG ---\n";
        cout << setw(6) << "Buoc" << setw(12) << "a"
             << setw(12) << "b" << setw(15) << "x"
             << setw(15) << "f(x)" << endl;
    }

    for (int i = 1; i <= max_iter; i++) {
        double fa = f(a);
        double fb = f(b);

        if (abs(fb - fa) < 1e-12) {
            cout << "Mau so qua nho, dung thuat toan.\n";
            return x;
        }

        x = (a * fb - b * fa) / (fb - fa);

        if (show_steps) {
            cout << setw(6) << i
                 << setw(12) << fixed << setprecision(8) << a
                 << setw(12) << b << setw(15) << x
                 << setw(15) << f(x) << endl;
        }

        if (abs(f(x)) < 1e-12) {
            return x;
        }

        // Cap nhat mot dau mut, giu dau mut con lai co dinh
        if (fa * f(x) < 0) {
            b = x;
        } else {
            a = x;
        }

        if (abs(b - a) < tol) {
            return x;
        }
    }

    if (show_steps) {
        cout << "Khoang sau " << max_iter
             << " lan lap: [" << a << ", " << b << "]\n";
    }

    return x;
}

int main() {

    cout << "=== KIEM TRA CAC PHUONG PHAP GIAI PHUONG TRINH ===\n";

    // Bai 1: Lap don cho x - 0.5*sin(x) = 0.25
    // Chuyen ve: x = 0.5*sin(x) + 0.25

    auto phi1 = [](double x) {
        return 0.5 * sin(x) + 0.25;
    };

    cout << "\n[Bai 1] Phuong phap lap don (4 buoc lap):";

    double ketQua1 = lapDon(phi1, 0.5, 1e-6, 4);

    cout << "Nghiem gan dung sau 4 buoc: "
         << setprecision(10) << ketQua1 << endl;


    // Bai 2: Chia doi cho x^3 - x - 1 = 0 tren [1, 2]

    auto f2 = [](double x) {
        return x * x * x - x - 1;
    };

    auto df2 = [](double x) {
        return 3.0 * x * x - 1.0;
    };
    double alpha2 = tiepTuyenNewton(f2, df2, 2.0, 1e-14, 50, false);

    cout << "\n[Bai 2] Phuong phap chia doi (4 buoc lap):";

    double ketQua2 = chiaDoi(f2, 1.0, 2.0, 1e-6, 4);

    cout << "Nghiem gan dung x4: "
         << setprecision(10) << ketQua2 << endl;

    cout << "Sai so ly thuyet |x4 - alpha| <= "
         << (2.0 - 1.0) / pow(2.0, 4) << endl;
    cout << "Sai so thuc |x4 - alpha| = "
         << scientific << abs(ketQua2 - alpha2) << fixed << endl;


    // Bai 3: Day cung cho x^3 - x - 1 = 0 tren [1, 2]

    cout << "\n[Bai 3] Phuong phap day cung (4 buoc lap):";

    double ketQua3 = dayCung(f2, 1.0, 2.0, 1e-6, 4);

    cout << "Nghiem gan dung sau 4 buoc: "
         << setprecision(10) << ketQua3 << endl;
    cout << "Sai so thuc |x4 - alpha| = "
         << scientific << abs(ketQua3 - alpha2) << fixed << endl;


    // Bai 4: Chia doi cho x^2 - 5 = 0 tren [2, 3]

    auto f4 = [](double x) {
        return x * x - 5.0;
    };
    double alpha4 = sqrt(5.0);

    cout << "\n[Bai 4] Phuong phap chia doi tinh can bac 2 cua 5 (4 buoc lap):";

    double ketQua4 = chiaDoi(f4, 2.0, 3.0, 1e-6, 4);

    cout << "Nghiem gan dung x4: "
         << setprecision(10) << ketQua4 << endl;

    cout << "Sai so ly thuyet |x4 - alpha| <= "
         << (3.0 - 2.0) / pow(2.0, 4) << endl;
    cout << "Sai so thuc |x4 - sqrt(5)| = "
         << scientific << abs(ketQua4 - alpha4) << fixed << endl;


    // Bai 5: Lap don cho x^3 - x - 1000 = 0
    // Chuyen ve: x = cubert(x + 1000)

    auto phi5 = [](double x) {
        return pow(x + 1000, 1.0 / 3.0);
    };

    cout << "\n[Bai 5] Phuong phap lap don (sai so tuyet doi <= 1e-5):";

    double ketQua5 = lapDon(phi5, 10.0, 1e-5, 100);

    cout << "Nghiem gan dung: "
         << setprecision(10) << ketQua5 << endl;

    // q = 0.004, sai so uoc luong theo cong thuc tren slide
    double q = 0.004;

    cout << "Sai so uoc luong < "
         << setprecision(12) << q / (1.0 - q) * 1e-5 << endl;

    return 0;
}