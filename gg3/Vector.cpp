#pragma once
#include <ostream>
#include <iostream>
using namespace std;

class IteratorV
{
	friend class Vector; // ������������� �����
public:
	IteratorV() { elem = 0; } // ����������� ��� ����������
	IteratorV(const IteratorV& it) { elem = it.elem; } // ����������� �����������
	// ������������� �������� ���������
	bool operator==(const IteratorV& it) { return elem == it.elem; }
	bool operator!=(const IteratorV& it) { return elem != it.elem; }
	// ������������� �������� ���������
	void operator++() { ++elem; }
	/* ������� � ����������� �������� (� ������� ������-���������) */
	void operator--() { --elem; }
	// ���������������
	int& operator*()const { return *elem; }

	int* elem; // ��������� �� ������� ���� int
};

class Vector {
public:
	// ����������� � �����������
	Vector(int s, int k = 0)
	{
		size = s;
		data = new int[size];
		for (int i = 0; i < size; i++)
			data[i] = k;

		beg.elem = &data[0];
		end.elem = &data[size];
	}

	// ����������� �����������
	Vector(const Vector& a)
	{
		size = a.size;
		data = new int[size];
		for (int i = 0; i < size; i++)
			data[i] = a.data[i];

		beg = a.beg;
		end = a.end;
	}

	// ����������
	~Vector()
	{
		delete[]data;
		data = 0;
	}

	// �������� ������������
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

	/* ������ �� ������� */
	int& operator[](int index)
	{
		if (index < size) return data[index];
		else cout << "\nError! Index>size";
	}

	/* �������� ��������� �������� */
	Vector operator+(const Vector& a)
	{
		Vector temp(size);
		for (int i = 0; i < size; ++i)
			temp.data[i] = data[i] + a.data[i];
		return temp;
	}

	/* ��������� ��������� �� ���� ��������� ������� */
	Vector operator+(const int k) // +k
	{
		Vector temp(size);
		for (int i = 0; i < size; ++i)
			temp.data[i] += data[i] + k;
		return temp;
	}

	// �������� ��� ��������� ����� �������
	int operator()()
	{
		return size;
	}

	// �������� ��� �����-������
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

	// ������ ��� ������ � ����������
	IteratorV first() { return beg; } // ���������� ��������� �� ������ �������
	IteratorV last() { return end; } // ���������� ��������� �� �������, ��������� �� ���������

	int size; // ������ �������
	int* data; // ��������� �� ������������ ������ �������� �������
	IteratorV beg; // ��������� �� ������ ������� �������
	IteratorV end; // ��������� �� �������, ��������� �� ���������
};