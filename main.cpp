#include <iostream>
#include<cmath>

using namespace std;
const double pi = 3.1415926535897932384626433832795;

double f1(double x){
    double up, down;

    /*  up - числитель, down - знаменатель
     *  pow(X, Y) - возводит число X в степень Y
     *  sqrt(X) - возвращает корень числа X
     *  exp(X) - возвращает число e (2.7...) в степени X
     *  (* pi / 180) - перевод в радианы, т.к. sin/cos/tan.. вычисляют по ним
     */
    up = (pow(x, 2)) + sin(sqrt(pi + 2*x) * pi / 180);
    down = 12 * sqrt(x + exp(1) * pow(x,2));
    return up / down;
}

double f2(double x, double y){
    double answer;
    if (y > 0) {
        double temp = sqrt(pow(x, 2) + tan(2 * y + pi));
        answer = f2(f1(temp), -1 * sin(y * pi / 180));

    } else if (y == 0) {
        answer = f1(pow(x,5));

    } else {
        double temp = pow(x,3) - pow(y, 2) + cos(15 * sqrt(x * (-1) * y) * pi / 180);
        answer = f1(temp);
    }
    return answer;
}

double f3(double x, double y, double z){
    //abs(X) - возвращает модуль числа Х
    int absZ = abs(z);
    /*
     * Организация суммы ряда.
     */
    double sum = 0;
    for (int k = 0; k <= absZ; k++){
        double up = f1(pow(x, k) / pow(y, k)) * f2(pow(z, k), x * y);
        double down = exp(3 * k);
        sum += sqrt(up / down);
    }

    return sum;
}

void menu() {
    cout << "1) Решать выражение 1\n"
         << "2) Решать выражение 2\n"
         << "3) Решать выражение 3\n"
         << "4) Выход\n";
}

bool work(){

    double x, y, z;

    int key;
    menu();
    cin >> key;
    switch(key){
        case 1:
            cout << "Введите значени Х: ";
            cin >> x;
            cout << f1(x) << "\n\n";
            work();
            break;
        case 2:
            cout << "Введите значени Х и Y: ";
            cin >> x >> y;
            cout << f2(x, y) << "\n\n";
            work();
            break;
        case 3:
            cout << "Введите значени Х, Y, Z: ";
            cin >> x >> y >> z;
            cout << f3(x, y, z) << "\n\n";
            work();
            break;
        case 4:
            return true;
        default:
            cout << "Запрос не ясен, повторите ввод\n";
            work();
    }
}

int main() {
    work();
    cout << "Завершение работы\n";

    return 0;
}
