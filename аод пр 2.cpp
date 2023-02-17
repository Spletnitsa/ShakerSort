#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <chrono>
#include <ctime>
using namespace std;

void PrintInfo(long long int C, long long int M, long long int e, double dur) {
	cout << "сравнения: " << C << "\tперемещения: " << M << endl;
	if (e > 10) {
		long long int fэ_n, fа_n;
		fэ_n = C + M;
		if (M != 0) {
			fа_n = e * e;
		}
		else {
			fа_n = e;
		}
		double fэ_fа = (double)fэ_n / (double)fа_n;
		cout << "T(n): " << left << setw(10) << dur / 1000000;
		cout << "fэ(n): " << left << setw(13) << fэ_n;
		cout << "fэ(n)/fа(n): " << left << setw(13) << fэ_fа << endl;
	}
}

void ShakerSort(int* arr, int e)
{
	long long int C = 0, M = 0;
	bool k = true;
	int leftMark = 1;
	int rightMark = e - 1;
	auto start_time = chrono::high_resolution_clock::now();
	while (leftMark <= rightMark)
	{
		for (int i = rightMark; i >= leftMark; i--) {
			C++;
			if (arr[i - 1] > arr[i]) {
				swap(arr[i - 1], arr[i]);
				M++;
				k = false;
			}
		}
		leftMark++;
		if (k) break;
		for (int i = leftMark; i <= rightMark; i++) {
			C++;
			if (arr[i - 1] > arr[i]) {
				swap(arr[i - 1], arr[i]);
				M++;
			}
		}
		rightMark--;
	}
	auto stop_time = chrono::high_resolution_clock::now();
	chrono::duration<double, nano> dur = stop_time - start_time;

	PrintInfo(C, M, e, dur.count());
}

void WorstSort(int* arr, int e)
{
	int sv;
	for (int i = 0; i < e - 1; i++) {
		for (int j = i + 1; j < e; j++) {
			if (arr[i] < arr[j]) {
				sv = arr[i];
				arr[i] = arr[j];
				arr[j] = sv;
			}
		}
	}
}

int main()
{
	setlocale(LC_ALL, "ru");
	int question;
	int Myarr[10];
	srand(time(0));
	cout << "+-----------------------------------------------------------------------------+" << endl;
	cout << "|Мещеряков Андрей ИКБО-15-19                                                  |" << endl;
	cout << "|Практическая работа №2 Нетривиальные алгоритмы внутренней сортировки массивов|" << endl;
	cout << "+-----------------------------------------------------------------------------+" << endl;
	cout << "ввод массива вручную (1)/автоматический ввод массива (2): ";
	cin >> question;
	if (question == 1) {
		cout << "введите массив:";
		for (int i = 0; i < 10; i++)
		{
			cout << "[" << i << "]= ";
			cin >> Myarr[i];
		}
		cout << "шейкерная сортировка: ";
		ShakerSort(Myarr, 10);
		
	}
	else if (question == 2) {
		long long int e;
		for (e = 30000; e <= 70000; e += 10000) {
			int* Autoarr = new int[e];
			for (int i = 0; i < e; i++) {
				Autoarr[i] = rand();
			}
			cout << "_______________________________________________________________________________\n";
			cout << "шейкерная сортировка n= " << e << endl;
			cout << "*--------------------------------средний случай-------------------------------*\n";
			ShakerSort(Autoarr, e);
			cout << "*-------------------------------наилучший случай------------------------------*\n";
			ShakerSort(Autoarr, e);
			cout << "--------------------------------наихудший случай------------------------------*\n";
			WorstSort(Autoarr, e);
			ShakerSort(Autoarr, e);
		}
	}
}