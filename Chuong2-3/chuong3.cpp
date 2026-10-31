#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <algorithm>

using namespace std;

using So = long double;
using Day = vector<So>;
using Bang = vector<Day>;

Day giaiHe(Bang A, Day B) {
    int n = A.size();
    for (int i = 0; i < n; ++i) {
        int dongTroi = i;
        for (int j = i + 1; j < n; ++j) {
            if (abs(A[j][i]) > abs(A[dongTroi][i])) dongTroi = j;
        }
        if (abs(A[dongTroi][i]) < 1e-12L) throw runtime_error("Ma tran he phuong trinh suy bien");

        swap(A[i], A[dongTroi]);
        swap(B[i], B[dongTroi]);

        for (int j = i + 1; j < n; ++j) {
            So heSoKhu = A[j][i] / A[i][i];
            for (int k = i; k < n; ++k) A[j][k] -= heSoKhu * A[i][k];
            B[j] -= heSoKhu * B[i];
        }
    }

    Day X(n, 0);
    for (int i = n - 1; i >= 0; --i) {
        X[i] = B[i];
        for (int j = i + 1; j < n; ++j) X[i] -= A[i][j] * X[j];
        X[i] /= A[i][i];
    }
    return X;
}

Day hoiQuyDaThuc(const Day& X, const Day& Y, int m) {
    int n = X.size();
    Bang A(m + 1, Day(m + 1, 0));
    Day B(m + 1, 0);
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= m; ++j) {
            So tong = 0;
            for (int k = 0; k < n; ++k) tong += pow(X[k], i + j);
            A[i][j] = tong;
        }
        So tongY = 0;
        for (int k = 0; k < n; ++k) tongY += Y[k] * pow(X[k], i);
        B[i] = tongY;
    }
    return giaiHe(A, B);
}

void bai5() {
    cout << "\nBAI 5 - BINH PHUONG BE NHAT (TOI THIEU)\n";
    Day x = {0, 1, 2, 3, 4, 5, 6, 7};
    Day y = {1.4, 1.3, 1.4, 1.1, 1.3, 1.8, 1.6, 2.3};

    Day c1 = hoiQuyDaThuc(x, y, 1);
    cout << "(a) Da thuc bac 1: y = " << c1[1] << "*x + " << c1[0] << "\n";

    Day c2 = hoiQuyDaThuc(x, y, 2);
    cout << "(b) Da thuc bac 2: y = " << c2[2] << "*x^2 + " << c2[1] << "*x + " << c2[0] << "\n";

    Day lny(y.size());
    for (size_t i = 0; i < y.size(); ++i) lny[i] = log(y[i]);
    Day c3 = hoiQuyDaThuc(x, lny, 1);
    So a3 = exp(c3[0]), b3 = c3[1];
    cout << "(c) Ham mu: y = " << a3 << " * e^(" << b3 << " * x)\n";

    Day ey(y.size());
    for (size_t i = 0; i < y.size(); ++i) ey[i] = exp(y[i]);
    Day c4 = hoiQuyDaThuc(x, ey, 1);
    So b4 = c4[0], a4 = c4[1];
    cout << "(d) Ham logarit: y = ln(" << a4 << "*x + " << b4 << ")\n";
}

void bai6() {
    cout << "\nBAI 6 - HOI QUY DA THUC BAC 2\n";
    Day x = {0.78, 1.56, 2.34, 3.12, 3.81};
    Day y = {2.50, 1.20, 1.12, 4.28, 7.50};
    Day c = hoiQuyDaThuc(x, y, 2);
    cout << "y = " << c[2] << "*x^2 + " << c[1] << "*x + " << c[0] << "\n";
}

void bai8() {
    cout << "\nBAI 8 - SO SANH KET QUA CAC DANG HOI QUY\n";
    Day x = {2, 4, 6, 8, 10, 12};
    Day y = {7.32, 8.24, 9.20, 10.19, 11.01, 12.05};

    Day c1 = hoiQuyDaThuc(x, y, 1);
    So S1 = 0;
    for (size_t i = 0; i < x.size(); ++i) {
        So y_xapXi = c1[0] + c1[1] * x[i];
        S1 += pow(y[i] - y_xapXi, 2);
    }
    cout << "Dang 1: y = " << c1[0] << " + " << c1[1] << "*x\n";
    cout << "   -> Tong binh phuong sai so (S1): " << S1 << "\n";

    Day c2 = hoiQuyDaThuc(x, y, 2);
    So S2 = 0;
    for (size_t i = 0; i < x.size(); ++i) {
        So y_xapXi = c2[0] + c2[1] * x[i] + c2[2] * x[i] * x[i];
        S2 += pow(y[i] - y_xapXi, 2);
    }
    cout << "Dang 2: y = " << c2[0] << " + " << c2[1] << "*x + " << c2[2] << "*x^2\n";
    cout << "   -> Tong binh phuong sai so (S2): " << S2 << "\n";

    Day lg_x(x.size()), lg_y(y.size());
    for (size_t i = 0; i < x.size(); ++i) {
        lg_x[i] = log10(x[i]);
        lg_y[i] = log10(y[i]);
    }
    Day c3 = hoiQuyDaThuc(lg_x, lg_y, 1);
    So a3 = pow(10, c3[0]), b3 = c3[1], S3 = 0;
    for (size_t i = 0; i < x.size(); ++i) {
        So y_xapXi = a3 * pow(x[i], b3);
        S3 += pow(y[i] - y_xapXi, 2);
    }
    cout << "Dang 3: y = " << a3 << " * x^" << b3 << "\n";
    cout << "   -> Tong binh phuong sai so (S3): " << S3 << "\n";

    So min_S = min({S1, S2, S3});
    cout << "=> KET LUAN: ";
    if (min_S == S2) cout << "Dang y = a + bx + cx^2 co tong binh phuong sai so (S) nho nhat -> Phu hop nhat.\n";
    else if (min_S == S1) cout << "Dang y = a + bx co tong binh phuong sai so (S) nho nhat -> Phu hop nhat.\n";
    else cout << "Dang y = ax^b co tong binh phuong sai so (S) nho nhat -> Phu hop nhat.\n";
}

int main() {
    cout << fixed << setprecision(6);
    cout << "BAI 9 SEMINAR 2 - CHUONG 3\n";
    try {
        bai5(); bai6(); bai8();
    } catch(const exception& e) {
        cerr << "Loi: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
