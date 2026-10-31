#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <stdexcept>

using namespace std;

using So = long double;
using Day = vector<So>;
using Bang = vector<Day>;

Day nhanNhanTu(const Day& p, So a) {
    Day q(p.size() + 1, 0);
    for (size_t i = 0; i < p.size(); ++i) {
        q[i] -= a * p[i];
        q[i+1] += p[i];
    }
    return q;
}

So giaTri(const Day& p, So x) {
    So y = 0;
    for (int i = static_cast<int>(p.size()) - 1; i >= 0; --i) y = y * x + p[i];
    return y;
}

void inDaThuc(const char* ten, const Day& heSo) {
    int n = static_cast<int>(heSo.size()) - 1;
    cout << ten << "(x) = ";
    bool dau = true;
    for(int k = n; k >= 0; --k) {
        So v = heSo[k];
        if(abs(v) < 1e-12L) continue;
        if(!dau) cout << (v < 0 ? " - " : " + ");
        else if(v < 0) cout << "-";
        cout << abs(v);
        if(k > 0) cout << "*x";
        if(k > 1) cout << "^" << k;
        dau = false;
    }
    if(dau) cout << "0";
    cout << '\n';
}

Day lagrange(const Day& x, const Day& y) {
    int n = static_cast<int>(x.size()) - 1;
    Day p_n(n + 1, 0);
    for(int i = 0; i <= n; ++i) {
        Day l_i{1};
        So mauSo = 1;
        for(int j = 0; j <= n; ++j) {
            if(j != i) {
                l_i = nhanNhanTu(l_i, x[j]);
                mauSo *= x[i] - x[j];
            }
        }
        if(mauSo == 0) throw runtime_error("Cac moc noi suy phai khac nhau");
        for(int k = 0; k <= n; ++k) p_n[k] += y[i] * l_i[k] / mauSo;
    }
    return p_n;
}

Day newton(const Day& x, const Day& y) {
    int n = static_cast<int>(x.size()) - 1;
    Bang T(n + 1, Day(n + 1, 0));
    for (int i = 0; i <= n; ++i) T[i][0] = y[i];
    for (int k = 1; k <= n; ++k)
        for (int i = 0; i <= n - k; ++i)
            T[i][k] = (T[i + 1][k - 1] - T[i][k - 1]) / (x[i + k] - x[i]);

    cout << "Bang ty sai phan (cac cot tu cap 0 den cap n):\n";
    for (int i = 0; i <= n; ++i) {
        for (int k = 0; k <= n - i; ++k) cout << T[i][k] << "  ";
        cout << '\n';
    }

    Day L_n{T[0][n]};
    for (int k = n - 1; k >= 0; --k) {
        L_n = nhanNhanTu(L_n, x[k]);
        L_n[0] += T[0][k];
    }
    return L_n;
}

void bai1() {
    cout << "\nBAI 1 - LAGRANGE\n";
    Day p = lagrange({0, 1, 3, 5}, {1, 2, 1, 4});
    inDaThuc("p_3", p);
    cout << "Gia tri tai x = 2: p_3(2) = " << giaTri(p, 2) << "\n";
}

void bai2() {
    cout << "\nBAI 2 - LAGRANGE VA PHAN THUC\n";
    Day x{-4, -3, -1, 0}, y;
    for(So t : x) y.push_back(t*t*t + t*t - 10);

    Day p = lagrange(x, y);
    inDaThuc("P_3", p);

    Day r;
    for(int i = 0; i < 4; ++i) {
        So mauSo = 1;
        for(int j = 0; j < 4; ++j) if(i != j) mauSo *= x[i] - x[j];
        r.push_back(y[i] / mauSo);
    }
    cout << "Cac he so phan thuc tinh duoc:\n";
    cout << "A = " << r[3] << "\n";
    cout << "B = " << r[2] << "\n";
    cout << "C = " << r[1] << "\n";
    cout << "D = " << r[0] << "\n";
}

void bai3() {
    cout << "\nBAI 3 - TONG LAP PHUONG\n";
    Day p = lagrange({0, 1, 2, 3, 4}, {0, 1, 9, 36, 100});
    cout << "Cong thuc noi suy tong lap phuong sinh ra la:\n";
    inDaThuc("S_n", p);

    cout << "\nAp dung cong thuc tinh cho cac gia tri n:\n";
    for(int n : {1, 5, 10, 20}) {
        cout << "- Voi n = " << n << " -> S(" << n << ") = " << giaTri(p, n) << "\n";
    }
}

void bai4() {
    cout << "\nBAI 4 - NOI SUY NEWTON\n";
    Day p = newton({-1, 0, 3, 6, 7}, {3, -6, 39, 822, 1611});
    inDaThuc("L_4", p);
    cout << "Gia tri tai x = 0.25: L_4(0.25) = " << giaTri(p, 0.25L) << "\n";
}

void bai7() {
    cout << "\nBAI 7 - ĐANH GIA SAI SO NOI SUY LAGRANGE CUA SIN(X)\n";
    So pi = acos(-1.0L);
    Day x_do = {0, 5, 10, 15, 20, 25};
    Day x_radian, y;

    for (So do_ : x_do) {
        So radian = do_ * pi / 180.0L;
        x_radian.push_back(radian);
        y.push_back(sin(radian));
    }

    Day p = lagrange(x_radian, y);

    So x_canTinh_do = 12.5L;
    So x_canTinh_radian = x_canTinh_do * pi / 180.0L;
    So giaTriMay = giaTri(p, x_canTinh_radian);
    So giaTriThuc = sin(x_canTinh_radian);

    cout << "Gia tri noi suy P_5(12.5 do) = " << giaTriMay << "\n";
    cout << "Gia tri that cua sin(12.5 do) = " << giaTriThuc << "\n";
    cout << "=> Sai so thuc te la: " << scientific << abs(giaTriMay - giaTriThuc) << fixed << "\n\n";
}

int main() {
    cout << fixed << setprecision(6);
    cout << "BAI 9 SEMINAR 2 - CHUONG 2\n";
    try {
        bai1(); bai2(); bai3(); bai4(); bai7();
    } catch(const exception& e) {
        cerr << "Loi: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
