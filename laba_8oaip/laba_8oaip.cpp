/*Шидловский К.Д. гр.378101 лаб. 8 вар. 13
Напишите программу, которая находит кратчайший путь между двумя заданными вершинами во взвешенном графе, используя алгоритм Дейкстры*/


#include <stdio.h>
#include <limits.h>
#include <locale.h>
#include <windows.h>

#define SIZE 4

int main() {
    setlocale(LC_ALL, "Russian");

    int a[SIZE][SIZE]; // матрица связей
    int d[SIZE]; // минимальное расстояние
    int v[SIZE]; // посещенные вершины
    int temp, minindex, min;
    int begin_index, end_index;

    // Инициализация матрицы связей
    for (int i = 0; i < SIZE; i++) {
        a[i][i] = 0;
        for (int j = i + 1; j < SIZE; j++) {
            printf("Введите расстояние %d - %d: ", i + 1, j + 1);
            scanf_s("%d", &temp);
            a[i][j] = temp;
            a[j][i] = temp;
        }
    }

    // Ввод начальной и конечной вершины
    printf("Введите начальную вершину (от 1 до %d): ", SIZE);
    scanf_s("%d", &begin_index);
    printf("Введите конечную вершину (от 1 до %d): ", SIZE);
    scanf_s("%d", &end_index);
    begin_index--;
    end_index--;

    // Инициализация вершин и расстояний
    for (int i = 0; i < SIZE; i++) {
        d[i] = INT_MAX;
        v[i] = 1;
    }
    d[begin_index] = 0;

    // Шаг алгоритма
    do {
        minindex = INT_MAX;
        min = INT_MAX;
        for (int i = 0; i < SIZE; i++) {
            if ((v[i] == 1) && (d[i] < min)) {
                min = d[i];
                minindex = i;
            }
        }

        // Добавляем найденный минимальный вес
        // к текущему весу вершины
        // и сравниваем с текущим минимальным весом вершины
        if (minindex != INT_MAX) {
            for (int i = 0; i < SIZE; i++) {
                if (a[minindex][i] > 0) {
                    temp = min + a[minindex][i];
                    if (temp < d[i]) {
                        d[i] = temp;
                    }
                }
            }
            v[minindex] = 0;
        }
    } while (minindex < INT_MAX);

    // Вывод кратчайших расстояний до вершин
    printf("\nКратчайшие расстояния до вершин: \n");
    for (int i = 0; i < SIZE; i++)
        printf("%5d ", d[i]);

    // Восстановление пути
    int ver[SIZE]; // массив посещенных вершин
    int end = end_index; // индекс конечной вершины
    ver[0] = end + 1; // начальный элемент - конечная вершина
    int k = 1; // индекс предыдущей вершины
    int weight = d[end]; // вес конечной вершины

    while (end != begin_index) { // пока не дошли до начальной вершины
        for (int i = 0; i < SIZE; i++) { // просматриваем все вершины
            if (a[i][end] != 0) { // если связь есть
                int temp = weight - a[i][end]; // определяем вес пути из предыдущей вершины
                if (temp == d[i]) { // если вес совпал с рассчитанным
                    weight = temp; // сохраняем новый вес
                    end = i; // сохраняем предыдущую вершину
                    ver[k] = i + 1; // и записываем ее в массив
                    k++;
                }
            }
        }
    }

    // Вывод пути (начальная вершина оказалась в конце массива из k элементов)
    printf("\nКратчайший путь от вершины %d до вершины %d:\n", begin_index + 1, end_index + 1);
    for (int i = k - 1; i >= 0; i--)
        printf("%3d ", ver[i]);

    getchar(); getchar();
    return 0;
}
