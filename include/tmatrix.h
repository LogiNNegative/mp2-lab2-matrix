// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
	size_t sz;
	T* pMem;
public:
	TDynamicVector(size_t size = 1) : sz(size)
	{
		if (sz > MAX_VECTOR_SIZE)
			throw out_of_range("Incorrect vector size");

		if (sz == 0)
			throw out_of_range("Incorrect vector size");

		pMem = new T[sz]();
	}

	TDynamicVector(T* arr, size_t s) : sz(s)
	{
		if (sz > MAX_VECTOR_SIZE)
			throw out_of_range("Incorrect vector size");

		assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");

		pMem = new T[sz];
		std::copy(arr, arr + sz, pMem);
	}

	TDynamicVector(const TDynamicVector& v)
	{
		sz = v.sz;
		pMem = new T[sz];
		std::copy(v.pMem, v.pMem + sz, pMem);
	}

	TDynamicVector(TDynamicVector&& v) noexcept
	{
		pMem = nullptr;
		swap(*this, v);
	}

	~TDynamicVector()
	{
		delete[] pMem;
	}

	TDynamicVector& operator=(const TDynamicVector& v)
	{
		if (this == &v)
			return *this;
		sz = std::max(v.sz, sz);
		TDynamicVector vector_2(v);
		swap(*this, vector_2);
		return *this;
	}

	TDynamicVector& operator=(TDynamicVector&& v) noexcept
	{
		if (pMem != nullptr)
		{
			delete[] pMem;
			pMem = nullptr;
		}
		swap(*this, v);
		return *this;
	}

	size_t size() const noexcept { return sz; }

	// индексация
	T& operator[](size_t ind)
	{
		return pMem[ind];
	}
	const T& operator[](size_t ind) const
	{
		return pMem[ind];
	}

	// индексация с контролем
	T& at(size_t ind)
	{
		if (ind >= sz || ind < 0)
			throw out_of_range("Incorrect index");
		return pMem[ind];
	}
	const T& at(size_t ind) const
	{
		if (ind >= sz || ind < 0)
			throw out_of_range("Incorrect index");
		return pMem[ind];
	}

	// сравнение
	bool operator==(const TDynamicVector& v) const noexcept
	{
		if (sz != v.size())
			return false;
		for (size_t i = 0; i < sz; i++)
			if (pMem[i] != v[i])
				return false;

		return true;
	}
	bool operator!=(const TDynamicVector& v) const noexcept
	{
		return !(*this == v);
	}

	// скалярные операции
	TDynamicVector operator+(T val)
	{
		TDynamicVector vector_2(sz);
		for (size_t i = 0; i < sz; i++)
			vector_2[i] = pMem[i] + val;

		return vector_2;
	}
	TDynamicVector operator-(double val)
	{
		TDynamicVector vector_2(sz);
		for (size_t i = 0; i < sz; i++)
			vector_2[i] = pMem[i] - val;

		return vector_2;
	}
	TDynamicVector operator*(double val)
	{
		TDynamicVector vector_2(sz);
		for (size_t i = 0; i < sz; i++)
			vector_2[i] = pMem[i] * val;

		return vector_2;
	}

	// векторные операции
	TDynamicVector operator+(const TDynamicVector& v)
	{
		if (sz != v.size())
			throw out_of_range("Incorrect vector sizes");

		TDynamicVector vector_2(sz);
		for (size_t i = 0; i < sz; i++)
			vector_2[i] = pMem[i] + v.pMem[i];

		return vector_2;
	}
	TDynamicVector operator-(const TDynamicVector& v)
	{
		if (sz != v.size())
			throw out_of_range("Icrorrect vector sizes");

		TDynamicVector vector_2(sz);
		for (size_t i = 0; i < sz; i++)
			vector_2[i] = pMem[i] - v.pMem[i];

		return vector_2;
	}
	T operator*(const TDynamicVector& v)
	{
		if (sz != v.size())
			throw out_of_range("Icrorrect vector sizes");
		T scalar = {};
		for (size_t i = 0; i < sz; i++)
			scalar += pMem[i] * v.pMem[i];

		return scalar;
	}

	friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
	{
		std::swap(lhs.sz, rhs.sz);
		std::swap(lhs.pMem, rhs.pMem);
	}

	// ввод/вывод
	friend istream& operator>>(istream& istr, TDynamicVector& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			istr >> v.pMem[i];
		return istr;
	}
	friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
		return ostr;
	}
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
	using TDynamicVector<TDynamicVector<T>>::pMem;
	using TDynamicVector<TDynamicVector<T>>::sz;
public:
	T& at(size_t index_1, size_t index_2)
	{
		if (index_1 >= sz || index_2 >= sz || index_1 < 0 || index_2 < 0)
			throw out_of_range("Incorrect index");
		return pMem[index_1][index_2];
	}
	const T& at(size_t ind1, size_t ind2) const
	{
		if (index_1 >= sz || index_2 >= sz || index_1 < 0 || index_2 < 0)
			throw out_of_range("Incorrect index");
		return pMem[index_1][index_2];
	}


	TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
	{
		if (sz > MAX_MATRIX_SIZE)
			throw out_of_range("Incorrect matrix size");
		for (size_t i = 0; i < sz; i++)
			pMem[i] = TDynamicVector<T>(sz);
	}
	size_t size() const noexcept { return sz; }
	using TDynamicVector<TDynamicVector<T>>::operator[];

	// сравнение
	bool operator==(const TDynamicMatrix& m) const noexcept
	{
		return TDynamicVector<TDynamicVector<T>>::operator==(m);
	}

	// матрично-скалярные операции
	TDynamicMatrix operator*(const T& val)
	{
		TDynamicMatrix matrix(sz);
		for (size_t i = 0; i < sz; i++)
		{
			matrix.pMem[i] = pMem[i] * val;
		}
		return matrix;
	}

	// матрично-векторные операции
	TDynamicVector<T> operator*(const TDynamicVector<T>& v)
	{
		TDynamicVector<T> vector(sz);
		for (size_t i = 0; i < sz; i++)
			vector[i] = pMem[i] * v;

		return vector;
	}

	// матрично-матричные операции
	TDynamicMatrix operator+(const TDynamicMatrix& m)
	{
		TDynamicMatrix matrix(sz);
		for (size_t i = 0; i < sz; i++)
			matrix.pMem[i] = pMem[i] + m.pMem[i];

		return matrix;
	}

	TDynamicMatrix operator-(const TDynamicMatrix& m)
	{
		TDynamicMatrix matrix(sz);
		for (size_t i = 0; i < sz; i++)
			matrix.pMem[i] = pMem[i] - m.pMem[i];

		return matrix;
	}

	TDynamicMatrix operator*(const TDynamicMatrix& m)
	{
		if (m.size() == size())
		{
			TDynamicMatrix matrix(sz);
			for (size_t i = 0; i < sz; i++)
				for (size_t j = 0; j < sz; j++)
					for (size_t k = 0; k < sz; k++)
						matrix[i][j] += pMem[i][k] * m[k][j];
			return matrix;
		}
		else
			throw exception("Incorrect size of the right argument");
	}

	// ввод/вывод
	friend istream& operator>>(istream& istr, TDynamicMatrix& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			for (size_t j = 0; j < v.sz; j++)
				istr >> v.pMem[i][j];

		return istr;
	}

	friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
	{
		for (size_t i = 0; i < v.sz; i++)
		{
			for (size_t j = 0; j < v.sz; j++)
				ostr << v.pMem[i][j] << " ";
			ostr << "\n";
		}

		return ostr;
	}

};

#endif
