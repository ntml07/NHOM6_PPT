#ifndef NUMERICAL_METHODS_H
#define NUMERICAL_METHODS_H

#include <functional>

// 1. Phương pháp Chia đôi
double chiaDoi(std::function<double(double)> f, double a, double b, double tol, int max_iter, bool show_steps = true);

// 2. Phương pháp Lặp đơn
double lapDon(std::function<double(double)> phi, double x0, double tol, int max_iter, bool show_steps = true);

// 3. Phương pháp Tiếp tuyến Newton
double tiepTuyenNewton(std::function<double(double)> f, std::function<double(double)> df, double x0, double tol, int max_iter, bool show_steps = true);

// 4. Phương pháp Dây cung
double dayCung(std::function<double(double)> f, double x0, double x1, double tol, int max_iter, bool show_steps = true);

#endif