#include "numerical_solution.h"
#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <stdio.h> 
#include <time.h>
#include <chrono>
#include <thread>

using namespace std;

#define RefRate 40000 
#define randomness 5 // high means less random 

// Clear the shell 
void clrscr()
{
	system("@cls||clear");
}

// Print a random character giving preference  
// to * 
void printRandLeaf()
{
	char leaftypes[5] = { '.', '*', '+', 'o', 'O' };
	int temp = rand() % randomness;

	// Giving preference to * 
	if (temp == 1)
		printf("%c ", leaftypes[rand() % 5]);
	else
		printf("%c ", leaftypes[1]);
}

void triangle(int f, int n, int toth)
{
	int i, j, k = 2 * toth - 2;

	for (i = 0; i < f - 1; i++)
		k--;

	// number of rows 
	for (i = f - 1; i < n; i++) {

		// space handler 
		for (j = 0; j < k; j++)
			printf(" ");

		// decrementing k after each loop 
		k = k - 1;

		// number of columns, printing stars 
		for (j = 0; j <= i; j++)
			printRandLeaf();

		printf("\n");
	}
}

// Prints multiple triangles 
void printTree(int h)
{
	int start = 1, stop = 0, diff = 3;
	while (stop < h + 1) {
		stop = start + diff;
		triangle(start, stop, h);
		diff++;
		start = stop - 2;
	}
}

// Prints bottom part. 
void printLog(int n)
{
	int i, j, k = 2 * n - 4;

	for (i = 1; i <= 6; i++) {

		// space handler 
		for (j = 0; j < k; j++)
			printf(" ");

		for (j = 1; j <= 6; j++)
			printf("#");

		printf("\n");
	}
}


// U"xx + U"yy = -f(x, y)
// a <= x <= b, c <= y <= d
// U(a, y) = M1(y), U(b, y) = M2(y)
// U(x, c) = M3(x), U(x, d) = M3(x)

int main(void)
{
	setlocale(LC_ALL, "rus");
	system("title Смирнов Руслан: задача Дирихле для уравнения Пуассона");

	srand(time(NULL));
	int ht = 6;

	//printf("\n*********С наступающим новым годом!*********\n\n");
	printTree(ht);
	printLog(ht);

	std::cout << std::endl << std::endl;

	int		Nmax = 10000;		//Максимальное число итераций
	int		S = 0;				//Счетчик итераций
	double	eps = 0.0000001;	//Параметр требуемой точности
	double	epsMax = 0;			//Достигнутая точность
	int		n = 4, m = 4;		//Размерность сетки
	double** V = NULL;			//Искомый вектор 
	double** F = NULL;			//f(x, y) из дифференециального уравнения в узлах сетки
	double	a, b, c, d;			//Границы области определния уравнения
	int Exit = 1, Show = 0;

	//Границы по x и y
	a = 0;
	b = 2;
	c = 0;
	d = 1;

	V = MemoryAllocator(n + 1, m + 1);
	FillStartSolution(V, n, m, a, b, c, d);
	ZeidelsMethod(V, n, m, a, b, c, d, eps, Nmax, epsMax, S);
	cout << "Итоговое численное решение " << endl;
	ShowSolution(V, n, m);

	//Справка
	cout << endl << endl;
	//cout << endl << "---------------------------------------------" << endl;
	cout << "Размерность сетки: " << n << "x" << m << endl;
	/*cout << "Область определения X: [" << a << "; " << b << "]" << endl;
	cout << "Область определения Y: [" << c << "; " << d << "]" << endl;
	cout << "Шаг сетки по оси Ox: h = " << (b - a) / n << endl;
	cout << "Шаг сетки по оси Oy: k = " << (d - c) / m << endl;*/
	cout.precision(15);
	cout << "Проведено итераций: " << S << endl;
	cout << "Заданная точность: " << eps << endl;
	cout << "Достигнутая точность: " << epsMax << endl;
	cout << "Общая погрешность: " << CheckNumSolution(V, n, m, a, b, c, d) << endl;
	cout << "Невязка решения: " << DiscrepancyOfSolution(V, n, m, a, b, c, d) << endl;
	//cout << "---------------------------------------------" << endl << endl;

	MemoryCleaner(V, n);

	cout << endl;
	cin >> Nmax;

	return 0;
}