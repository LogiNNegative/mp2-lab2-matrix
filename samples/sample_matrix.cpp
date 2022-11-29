// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"
//---------------------------------------------------------------------------

TDynamicMatrix<double> CreateRandomMatrix(int MatrixSize)
{
	TDynamicMatrix<double> matrix(MatrixSize);
	for (size_t i = 0; i < MatrixSize; i++)
		for (size_t j = 0; j < MatrixSize; j++)
			matrix[i][j] = rand() % 10 + (rand() % 10) * 1. / 10;
	return matrix;
}

TDynamicVector<double> CreateRandomVector(int VectorSize)
{
	TDynamicVector<double> vector(VectorSize);
	for (size_t i = 0; i < VectorSize; i++)
		vector[i] = rand() % 10 + (rand() % 10) * 1. / 10;
	return vector;
}

int ChooseFilling()
{
	int choose;
	cout << "Выбирете способ заполнения:\n"
		<< "0 - вручную\n"
		<< "1 - случайная\n";
	cin >> choose;
	if (choose == 0)
	{
		cout << "Введите матрицу:\n";
		return choose;
	}
	else if (choose == 1)
	{
		cout << "Случайная матрица:\n";
		return choose;
	}
	else
	{
		cout << "Некорректный выбор!\n";
		return -1;
	}
}

int ChooseOperation()
{
	int choose;
	cout << "Выбирете операцию:\n"
		<< "0 - умножить матрицу на число (matrix * number)\n"
		<< "1 - умножить матрицу на вектор (matrix * vector)\n"
		<< "2 - умножить матрицу на матрицу (matrix * matrix)\n"
		<< "3 - прибавить к матрице матрицу (matrix + matrix)\n"
		<< "4 - вычесть из матрицы матрицу (matrix - matrix)\n";
	cin >> choose;
	if (choose >= 0 && choose <= 4)
		return choose;
	else
		return -1;
}

void main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Тестирование класс работы с матрицами" << endl;

	int size;
	cout << "Введите размер матрицы: ";
	cin >> size;

	if (size <= 0 || size > MAX_MATRIX_SIZE)
		cout << "Некорректный размер матрицы!";
	else
	{
		int choose = ChooseFilling();
		if (choose != -1)
		{
			TDynamicMatrix<double> matrix_1(size);
			TDynamicMatrix<double> matrix_2(size);
			TDynamicVector<double> vector(size);
			if (choose)
			{
				matrix_1 = CreateRandomMatrix(size);
				matrix_2 = CreateRandomMatrix(size);
				vector = CreateRandomVector(size);
			}
			else
				cin >> matrix_1;
			cout << endl << matrix_1;

			int op_choose = ChooseOperation();

			if (op_choose == -1)
				cout << "\nНекорректный выбор операции!";
			if (op_choose == 0)
			{
				double num;
				cout << "Введите число:\n";
				cin >> num;
				cout << "\nРезультат умножения матрицы на число:\n" << matrix_1 * num;
			}
			if (op_choose == 1)
			{
				if (choose)
				{
					cout << "Случайный вектор:\n";
					cout << vector;
				}
				else
				{
					cout << "Введите вектор:\n";
					cin >> vector;
				}
				cout << "\nРезультат умножения матрицы на вектор:\n" << matrix_1 * vector;
			}
			if (op_choose == 2)
			{
				if (choose)
				{
					cout << "Случайная вторая матрица:\n";
					cout << matrix_2;
				}
				else
				{
					cout << "Введите вторую матрицу:\n";
					cin >> matrix_2;
				}
				cout << "\nРезультат умножения матриц:\n" << matrix_1 * matrix_2;
			}
			if (op_choose == 3)
			{
				if (choose)
				{
					cout << "Случайная вторая матрица:\n";
					cout << matrix_2;
				}
				else
				{
					cout << "Введите вторую матрицу:\n";
					cin >> matrix_2;
				}
				cout << "\nРезультат сложения матриц:\n" << matrix_1 + matrix_2;
			}
			if (op_choose == 4)
			{
				if (choose)
				{
					cout << "Случайная вторая матрица:\n";
					cout << matrix_2;
				}
				else
				{
					cout << "Введите вторую матрицу:\n";
					cin >> matrix_2;
				}
				cout << "\nРезультат разности матриц:\n" << matrix_1 - matrix_2;
			}
		}
	}

}
//---------------------------------------------------------------------------