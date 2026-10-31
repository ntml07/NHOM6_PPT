#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

double f1(double x) {
    return 1.0 / (1.0 + x * x);
}

double f2(double x) {
    return 1.0 / (1.0 + x);
}

double f3(double x) {
    if (x == 0) return 1.0;
    return sin(x) / x;
}

double saiSoHinhThang(double a, double b, int soDoan, double M2) {
    double h = (b - a) / soDoan;
    return (b - a) * h * h * M2 / 12.0;
}

double saiSoSimpson(double a, double b, int n, double M4) {
    double h = (b - a) / (2.0 * n);
    return (b - a) * pow(h, 4) * M4 / 180.0;
}

double hinhThang(double y[], double h, int soDoan) {
    double sum = 0;
    for (int i = 1; i < soDoan; i++) {
        sum += y[i];
    }
    return h * ((y[0] + y[soDoan]) / 2.0 + sum);
}

double simpson(double y[], double h, int n) {
    int soDoan = 2 * n;
    double sumLe = 0, sumChan = 0;
    for (int i = 1; i < soDoan; i++) {
        if (i % 2 == 1) sumLe += y[i];
        else sumChan += y[i];
    }
    return h / 3.0 * (y[0] + y[soDoan] + 4 * sumLe + 2 * sumChan);
}

void bai1() {
    cout << "\nBAI 1\n";

    double a = 0, b = 1;
    int n = 5;
    double h = (b - a) / (2 * n);

    double y[11];
    for (int i = 0; i <= 2 * n; i++) {
        y[i] = f1(a + i * h);
    }

    double IT = hinhThang(y, h, 2 * n);
    double IS = simpson(y, h, n);
    double I = atan(1.0);

    cout << "n = " << n << ", so doan = " << 2 * n << endl;
    cout << "Buoc chia h = " << h << endl;
    cout << "Ket qua hinh thang: " << IT << endl;
    cout << "Ket qua Simpson: " << IS << endl;
    cout << "Gia tri chinh xac: " << I << endl;
}

void bai2() {
    cout << "\nBAI 2\n";

    double a = 0, b = 1;
    int n = 5;
    double h = (b - a) / (2 * n);

    double y[11];
    for (int i = 0; i <= 2 * n; i++) {
        y[i] = f2(a + i * h);
    }

    double IT = hinhThang(y, h, 2 * n);
    double IS = simpson(y, h, n);

    double M2 = 2, M4 = 24;
    double ET = saiSoHinhThang(a, b, 2 * n, M2);
    double ES = saiSoSimpson(a, b, n, M4);
    double I = log(2.0);

    cout << "n = " << n << ", so doan = " << 2 * n << endl;
    cout << "Buoc chia h = " << h << endl;
    cout << "Ket qua hinh thang: " << IT << endl;
    cout << "Sai so hinh thang: " << ET << endl;
    cout << "Ket qua Simpson: " << IS << endl;
    cout << "Sai so Simpson: " << ES << endl;
    cout << "Gia tri chinh xac: " << I << endl;
}

void bai3() {
    cout << "\nBAI 3\n";

    double a = 0, b = 1;
    double M2 = 1.0 / 3.0, M4 = 1.0 / 5.0;
    double saiSoYeuCau = 3e-4;

    int soDoan = 1;
    while (saiSoHinhThang(a, b, soDoan, M2) >= saiSoYeuCau) {
        soDoan++;
    }
    if (soDoan % 2 != 0) soDoan++;

    int n = soDoan / 2;
    double h = (b - a) / (2 * n);

    double y[11];
    for (int i = 0; i <= 2 * n; i++) {
        y[i] = f3(a + i * h);
    }

    double IT = hinhThang(y, h, 2 * n);
    double IS = simpson(y, h, n);
    double ET = saiSoHinhThang(a, b, 2 * n, M2);
    double ES = saiSoSimpson(a, b, n, M4);

    cout << "n = " << n << ", so doan = " << 2 * n << endl;
    cout << "Buoc chia h = " << h << endl;
    cout << "Sai so uoc luong hinh thang: " << ET << endl;
    cout << "Sai so uoc luong Simpson: " << ES << endl;
    cout << "Ket qua hinh thang: " << IT << endl;
    cout << "Ket qua Simpson: " << IS << endl;

    cout << "\nKet qua lam tron 6 chu so thap phan:\n";
    cout << setprecision(6);
    cout << "Hinh thang: " << IT << endl;
    cout << "Simpson: " << IS << endl;
    cout << setprecision(12);
}

int main() {
    cout << fixed << setprecision(12);
    cout << "THUC HANH CHUONG 4 - TINH GAN DUNG TICH PHAN\n";
    bai1();
    bai2();
    bai3();
    cout << "\nHoan thanh ca 3 bai tap!\n";
    return 0;
}
