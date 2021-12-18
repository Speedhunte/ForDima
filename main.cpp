#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

struct Matrix{

    int n = 0; //размерность матрицы
    float field[17][17] = {{0}}; //матрица значений матрицы

    void filling(){ //функция заполнения матрицы числами от 1 до n*n

        //тут нужно указать путь к своему файлу ввода

        ifstream input("D:\\Practicum\\LAB2\\input.txt");
        //если файл не открылся по каким-то причинам - вывод сообщения об ошибке
        if (!input){
            cout << "File not found" << endl;
            return;
        }

        input >> n;
        //проверка ввода
        if (!((n >= 4) && (n <= 16))){
            cout << "Wrong input" << endl;
            return;
        }


        int dir = -1, counter = 1;
        //первая часть - заполнение вертикальными линиями с изменением направления движения
        //dir это направление, dir = 1 - вверх, dir = -1 - вниз
        //мы идём то вверх, то вниз, смещаясь вправо и заполняя каждую ячейку следующим числом
        for (int j = 0; j < n; j++){
            if (dir == -1){
                for (int i = j + 1; i < n; i++) {
                    field[i][j] = counter;
                    counter++;
                }
            }
            else{
                for (int i = n - 1; i > j; i--) {
                    field[i][j] = counter;
                    counter++;
                }
            }
            dir *= -1;
        }
        //вторая часть - заполнение части над диагональю косыми линиями с изменением направления движения
        //принцип работы точно такой же - проходы то в одну сторону, то в другую с изменением направления и смещением после каждой итерации
        //dir = 1 - проход вправо вниз, dir = -1 - проход влево вверх
        dir = -1;
        for (int k = n - 1; k >= 0; k--){
            if (dir == -1){
               int i = k, j = n - 1;
               while (i >= 0){
                   field[i][j] = counter;
                   counter++;
                   i--;
                   j--;
               }

            }
            else{
                int i = 0, j = n - 1 - k;
                while (i <= k) {
                    field[i][j] = counter;
                    counter++;
                    i++;
                    j++;
                }
            }
            dir *= -1;
        }
    }

    void input(){ //функция ввода матрицы из файла
        ifstream input("D:\\Practicum\\LAB2\\input.txt");

        if (!input){
            cout << "File not found" << endl;
            return;
        }
        //ввод размерности матрицы
        input >> n;
        //проверка на корректность данных
        if (!((n >= 4) && (n <= 16))){
            cout << "Wrong input" << endl;
            return;
        }
        //ввод значений матрицы
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                input >> field[i][j];
    }

    void output(){ //функция вывода матрицы в файл
        ofstream output("D:\\Practicum\\LAB2\\output.txt");

        if (!output){
            cout << "Can't open this file" << endl;
            return;
        }
        //вывод матрицы
        output << n << endl;

        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++)
                output << field[i][j] << " ";
            output << endl;
        }
    }
};

Matrix erase(Matrix A, int x, int y){ //удаление из матрицы А строки Х и столбца У (нужно для нахождения обратной матрицы)
    Matrix ans;
    ans.n = A.n - 1;
    for (int i = 0; i < ans.n; i++)
        for (int j = 0; j < ans.n; j++)
            ans.field[i][j] = A.field[i + (i >= x)][j + (j >= y)]; //пока мы не дошли до строки или столбца, мы присваиваем те же значения из матрицы А, после того, как перешли границу, смещаемся на 1 вправо или вниз

    return ans;
}

float det(Matrix M){ // функция нахождения определителя. рекурсивная. взята непосредственно из определения линейной алгебры
    float ans = 0;

    if (M.n == 1){
        ans = M.field[0][0];
    }
    else
    if (M.n == 2){
        ans = ((M.field[0][0] * M.field[1][1]) - (M.field[0][1] * M.field[1][0]));
    }
    else{
        for (int j = 0; j < M.n; j++){
            if (j % 2 == 0)
                ans += (M.field[0][j] * det(erase(M, 0, j)));
            else
                ans -= (M.field[0][j] * det(erase(M, 0, j)));
        }
    }

    return ans;
}

Matrix transpose(Matrix M){ //транспонирование матрицы
    for (int i = 0; i < M.n; i++)
        for (int j = i + 1; j < M.n; j++)
            swap(M.field[i][j], M.field[j][i]); //грубо говоря, мы меняем каждый элемент из верхней правой диагональной половины с соответствующим элементом из левой нижней

    return M;
}

Matrix inverse(Matrix M){ //нахождение обратной матрицы методом алгебраических дополнений
    Matrix Tr = transpose(M), tmp = M;


    //находим матрицу алгебраических дополнений
    for (int i = 0; i < M.n; i++)
        for (int j = 0; j < M.n; j++){
            float deter = det(erase(Tr, i, j));
            if ((i + j) % 2 == 0)
                tmp.field[i][j] = deter;
            else{
                deter *= -1;
                tmp.field[i][j] = deter;
            }
        }

    float deter = det(Tr);
    //считаем обратную матрицу
    for (int i = 0; i < M.n; i++)
        for (int j = 0; j < M.n; j++)
            tmp.field[i][j] = (tmp.field[i][j] / deter);

    return tmp;
}

Matrix multiply(Matrix A, Matrix B){ //умножение двух матриц, просто как в алгебре
    Matrix ans;
    //проверка на корректность данных
    if (A.n != B.n){
        cout << "Different size" << endl;
        return ans;
    }

    ans.n = A.n;
    //обычное умножение матриц
    for (int i = 0; i < A.n; i++)
        for (int j = 0; j < A.n; j++){
            ans.field[i][j] = 0;

            for (int k = 0; k < A.n; k++)
                ans.field[i][j] += (A.field[i][k] * B.field[k][j]);
        }

    return ans;
}

int main() {
    Matrix A, B; //создаём две матрицы

    A.filling(); //одну заполняем как на картинке
    B.input();   //другую читаем из файла

    Matrix C = multiply(A, inverse(B)); //находим произведение матрицы А и обратной к матрице В

    C.output(); //выводим матрицу в файл

    return 0;
}


