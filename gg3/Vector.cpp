#pragma once
#include <ostream>
#include <iostream>
using namespace std;

class IteratorV
{
	friend class Vector; // дружественный класс
public:
	IteratorV() { elem = 0; } // конструктор без параметров
	IteratorV(const IteratorV& it) { elem = it.elem; } // конструктор копирования
	// перегруженные операции сравнения
	bool operator==(const IteratorV& it) { return elem == it.elem; }
	bool operator!=(const IteratorV& it) { return elem != it.elem; }
	// перегруженная операция инкремент
	void operator++() { ++elem; }
	/* ПЕРЕХОД К ПРЕДЫДУЩЕМУ ЭЛЕМЕНТУ (С ПОМОЩЬЮ КЛАССА-ИТЕРАТОРА) */
	void operator--() { --elem; }
	// разыменовывание
	int& operator*()const { return *elem; }

	int* elem; // указатель на элемент типа int
};

class Vector {
public:
	// конструктор с параметрами
	Vector(int s, int k = 0)
	{
		size = s;
		data = new int[size];
		for (int i = 0; i < size; i++)
			data[i] = k;

		beg.elem = &data[0];
		end.elem = &data[size];
	}

	// конструктор копирования
	Vector(const Vector& a)
	{
		size = a.size;
		data = new int[size];
		for (int i = 0; i < size; i++)
			data[i] = a.data[i];

		beg = a.beg;
		end = a.end;
	}

	// деструктор
	~Vector()
	{
		delete[]data;
		data = 0;
	}

	// операция присваивания
	Vector& operator=(const Vector& a)
	{
		if (this == &a) return *this;
		size = a.size;
		if (data != 0) delete[] data;
		data = new int[size];
		for (int i = 0; i < size; i++)
			data[i] = a.data[i];

		beg = a.beg;
		end = a.end;
		return *this;
	}

	/* ДОСТУП ПО ИНДЕКСУ */
	int& operator[](int index)
	{
		if (index < size) return data[index];
		else cout << "\nError! Index>size";
	}

	/* СЛОЖЕНИЕ ЭЛЕМЕНТОВ ВЕКТОРОВ */
	Vector operator+(const Vector& a)
	{
		Vector temp(size);
		for (int i = 0; i < size; ++i)
			temp.data[i] = data[i] + a.data[i];
		return temp;
	}

	/* ДОБАВЛЯЕТ КОНСТАНТУ КО ВСЕМ ЭЛЕМЕНТАМ ВЕКТОРА */
	Vector operator+(const int k) // +k
	{
		Vector temp(size);
		for (int i = 0; i < size; ++i)
			temp.data[i] += data[i] + k;
		return temp;
	}

	// операция для получения длины вектора
	int operator()()
	{
		return size;
	}

	// операции для ввода-вывода
	friend ostream& operator<<(ostream& out, const Vector& a)
	{
		for (int i = 0; i < a.size; ++i)
			out << a.data[i] << " ";
		return out;
	}

	friend istream& operator>>(istream& in, Vector& a)
	{
		for (int i = 0; i < a.size; ++i)
			in >> a.data[i];
		return in;
	}

	// методы для работы с итератором
	IteratorV first() { return beg; } // возвращает указатель на первый элемент
	IteratorV last() { return end; } // возвращает указатель на элемент, следующий за последним

	int size; // размер вектора
	int* data; // указатель на динамический массив значений вектора
	IteratorV beg; // указатель на первый элемент вектора
	IteratorV end; // указатель на элемент, следующий за последним
};