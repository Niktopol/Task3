#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
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
void prost(double S, double n, double arr[],double point, double step){
    arr[0] = zaem(S, point + step, n);
    arr[1] = zaem(S, point - step, n);
}
double binfind(double S, double m, double n, double step, double point, double arr[]) {
    if (step <= 100){
        return point;
    }
    if ((arr[0] < m) and (arr[1] < m)){
        point += step;
        prost(S,n,arr,point,step/2);

    } else {
        point -= step;
        prost(S,n,arr,point,step/2);
    }
    return binfind(S,m,n,step/2,point,arr);
}
double ssuda(double S, double m, double n) {
    if (S < 0 or m < 0 or n < 0 or (S == 0 and m > 0)){
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
            double point = (std::numeric_limits<float>::max())/2;
            double step = (std::numeric_limits<float>::max())/4;
            double arr[2] = {zaem(S, point + step,n), zaem(S, point - step, n)};
            double perc = binfind(S,m,n,step,point, arr);
            double p = ((perc-1000)<0) ? 0 : perc-1000;
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
int main() {
    setlocale(LC_ALL, "");
    double S, p, n, m;

    std::wcout << L"Введите сумму, процент и число лет" << std::endl;
    std::wcin >> S; std::wcin >> p; std::wcin >> n;
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
        std::wcout << L"p = " << h << std::endl;
    }
    copy();
    filtr();

    std::wstring d;
    std::wcin >> d;
    std::sort(d.begin(),d.end(), c);
    std::wcout << d;
    return 0;
}