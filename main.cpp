#include <iostream>
#include <fstream>
#include <string>
#define _USE_MATH_DEFINES
#include <cmath>
#include <limits>

bool find(char s) {
    char a[] = { '0','1','2','3','4','5','6','7','8','9' };
    for (char i : a) {
        if (s == i) {
            return true;
        }
    }
    return false;
}
double zaem(double S, double p, double n) {
    p = p / 100;
    if (S < 0 or p < 0 or n < 0){
        return -1;
    }
    if (n == 0) {
        return S;
    }
    else {
        if (p == 0) {
            return S / (n * 12);
        }
        else {
            double m = (S * p * std::pow((1 + p), n)) / (12 * (std::pow((1 + p), n) - 1));
            return m;
        }
    }
}
double binfind(double S, double m, double n, double start, double end) {
    double step = (end - start) / 2;
    double point = start + step;
    double ch = zaem(S, point, n);
    if (step <= 100) {
        return start;
    }
    if (m > ch) {
        start += step;
    }
    else if (ch == m) {
        return point;
    }
    else {
        end -= step;
    }
    return binfind(S, m, n, start, end);
}
double ssuda(double S, double m, double n) {
    if (S < 0 or m < 0 or n < 0 or (S == 0 and m > 0)) {
        return -1;
    }
    if (n == 0) {
        if (S == m) {
            return 0;
        }
        else {
            return -1;
        }
    }
    else {
        if (m == 0) {
            if (S != 0) {
                return -1;
            }
            else {
                return -2;
            }
        }
        else {
            double perc = binfind(S, m, n, 0, (std::numeric_limits<double>::max()));
            double p = ((perc - 1000) < 0) ? 0 : perc - 1000;
            while (zaem(S, p, n) < m) {
                p += 0.01;
            }
            return p;
        }
    }
}

void copy() {
    std::wifstream in;
    std::wofstream out;
    std::wstring str;
    std::wstring all;
    in.open("test.txt");
    if (!in.is_open()){
        std::wcout << L"Файла test.txt не существует" << std::endl;
    }
    else{
        while (getline(in, str)) {
            all += str+L"\n";
        }
        in.close();
        out.open("test_copy.txt");
        out << all;
        out.close();
    }
}
void filtr() {
    std::wifstream in;
    std::wofstream out;
    std::wstring str;
    std::wstring all;
    in.open("test.txt");
    if (!in.is_open()) {
        std::wcout << L"Файла test.txt не существует" << std::endl;
    } else {
        while (getline(in, str)) {
            all += str + L"\n";
        }
        std::wstring temp;
        for (int i = 0; i < all.length(); i++) {
            if (find(all[i])) {
                temp += (all[i]);
            } else if ((!find(all[i]) or i + 1 == all.length()) and temp != L"") {
                std::wcout << temp + L"\n";
                temp = L"";
            }
        }
    }
}
bool c(wchar_t a, wchar_t b){
    if (towlower(a) == towlower(b) && a != b){
        return towlower(a) != a;
    }
    return towlower(a) < towlower(b);
}
std::wstring my_sort(std::wstring s) {
    wchar_t t;
    for (int i = 0; i < s.length(); i++) {
        for (int j = 0; j < s.length()-1; j++) {
            if (c(s[j], s[j + 1])) {
                t = s[j];
                s[j] = s[j + 1];
                s[j + 1] = t;
            }
        }
    }
    return s;
}
int main() {
    setlocale(LC_ALL, "");
    double S, p, n, m;

    std::wcout << L"Введите сумму, процент и число лет" << std::endl;
    std::wcin >> S; std::wcin >> p; std::wcin >> n;
    std::wcout.precision(10);
    std::wcout << L"m = " << zaem(S, p, n) << std::endl;

    std::wcout << L"Введите сумму, размер выплат и число лет" << std::endl;
    std::wcin >> S; std::wcin >> m; std::wcin >> n;
    double h = ssuda(S,m,n);
    if (h == -1){
        std::wcout << L"Неверные данные" << std::endl;
    }
    else if (h == -2) {
        std::wcout << L"p = Любое число" << std::endl;
    }else{
        std::wcout.precision(10);
        std::wcout << L"p = " << h << std::endl;
    }
    copy();
    filtr();

    std::wstring d;
    std::wcin >> d;
    d = my_sort(d);
    std::wcout << d;
    return 0;
}