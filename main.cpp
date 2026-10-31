#include <iostream>
#include <cmath>
#include "numerical_methods.h"

using namespace std;

int main() {
    cout << "=== KIEM TRA CAC BAI TOAN SO HOC (DA TACH FILE) ===\n";

    // Bai 1: Lap don cho x - 0.5*sin(x) = 0.25 => phi(x) = 0.5*sin(x) + 0.25
    auto phi1 = [](double x) { return 0.5 * sin(x) + 0.25; };
    cout << "\n[Bai 1] Phuong phap lap don (4 buoc lap):";
    lapDon(phi1, 0.5, 1e-6, 4);

    // Bai 2: Chia doi cho x^3 - x - 1 = 0 tren [1, 2]
    auto f2 = [](double x) { return x * x * x - x - 1; };
    cout << "\n[Bai 2] Phuong phap chia doi (4 buoc lap):";
    chiaDoi(f2, 1.0, 2.0, 1e-6, 4);

    // Bai 3: Day cung cho x^3 - x - 1 = 0 tren [1, 2]
    cout << "\n[Bai 3] Phuong phap day cung (4 buoc lap):";
    dayCung(f2, 1.0, 2.0, 1e-6, 4);

    // Bai 4: Chia doi tinh can bac 2 cua 5 tu x^2 - 5 = 0 tren [2, 3]
    auto f4 = [](double x) { return x * x - 5.0; };
    cout << "\n[Bai 4] Phuong phap chia doi tinh can bac 2 cua 5 (4 buoc lap):";
    chiaDoi(f4, 2.0, 3.0, 1e-6, 4);

    // Bo sung: Tiep tuyen Newton cho x^3 - x - 1 = 0
    auto df2 = [](double x) { return 3.0 * x * x - 1.0; };
    cout << "\n[Bo sung] Phuong phap Newton (4 buoc lap):";
    tiepTuyenNewton(f2, df2, 1.5, 1e-6, 4);

    return 0;
}