#include <iostream>
#include "map"

using namespace std;

int main() {
    int n;
    cin >> n;

    map<int, int> mp;
    int* mas = new int[n]; //Динамический массив

    //Цикл для ввода значений (вводятся и в массив и в словарь (map))
    int k;
    for (int i = 0; i < n; i++) {
        cin >> k;
        mas[i] = k;
        if (mp.find(k) != mp.end()) {
            mp[k] += 1;
        } else {
            mp[k] = 1;
        }
    }

    int max = 0;
    map<int, int> :: iterator it; // Создание итератора для словаря
    for(it = mp.begin(); it != mp.end(); it++){
        if (it->second > max) {
            max = it->second;
        }
    }

    int minim = INT_MAX; // Установка переменной minim в максимальное число для int
    for(it = mp.begin(); it != mp.end(); it++){
        if (it->second == max) {
            minim = min(minim, it->first);
        }
    }

    int seredina;
    if (n % 2 != 0) {
        seredina = mas[n/2];
    } else {
        seredina = min(mas[n/2], mas[(n+1)/2]); // Выбор минимального числа из двух серединных
    }
    cout << "Ответ: " << minim << " " << seredina;
    return 0;
}
