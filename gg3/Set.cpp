#pragma once
#include <ostream>
#include <iostream>
#include "Vector.cpp"
#include <algorithm>
using namespace std;

class IteratorS
{
	friend class Set; // ������������� �����
public:
	IteratorS() { elem = 0; } // ����������� ��� ����������
	IteratorS(const IteratorS& it) { elem = it.elem; } // ����������� �����������
	// ������������� �������� ���������
	bool operator==(const IteratorS& it) { return elem == it.elem; }
	bool operator!=(const IteratorS& it) { return elem != it.elem; }
	/* ������� � ���������� �������� (� ������� ������-���������) */
	void operator++() { ++elem; }
	// ���������
	void operator--() { --elem; }
	// ���������������
	int& operator*()const { return *elem; }

	int* elem; // ��������� �� ������� ���� int
};

class Set {
public:
	// ����������� � �����������
	Set(int s, int k = 0)
	{
		size = s;
		data = new int[size];
		for (int i = 0; i < size; i++)
			data[i] = k++;

		beg.elem = &data[0];
		end.elem = &data[size];
	}

	/*
	// ����������� ������ � ���������
	Set(Vector& a)
	{
		if (a.size != 0)
			sort(a.beg, a.end);
		int setsize = 0;

		for (int i = 1; i < a.size; ++i)
			if (a[i - 1] != a[i])
				setsize++;

		Set set(setsize);
		set[0] = a[0];
		int index = 0;
		for (int i = 1; i < a.size; ++i)
			if (a[i - 1] != a[i]) {
				set[++index] = a[i];
			}
		// ������ size � data
	}*/

	// ����������� �����������
	Set(const Set& a)
	{
		size = a.size;
		data = new int[size];
		for (int i = 0; i < size; i++)
			data[i] = a.data[i];

		beg = a.beg;
		end = a.end;
	}

	// ����������
	~Set()
	{
		delete[]data;
		data = 0;
	}

	// �������� ������������
	Set& operator=(const Set& a)
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

	// �������� ��� ���������� ���������
	Set operator+(const int k) // +k
	{
		Set temp(size);
		for (int i = 0; i < size; ++i)
			temp.data[i] += data[i] + k;
		return temp;
	}

	/* ����������� �������� */
	Set operator+(const Set& a)
	{
		int nsize = size;
		Set temp(size);
		for (int i = 0; i < a.size; ++i) {
			bool flag = false;
			for (int j = 0; j < size; ++j) {
				if (a.data[i] == data[j]) {
					flag = true;
					break;
				}
			}
			if (!flag) {
				nsize++;
				Set temp1(nsize - 1);
				temp1 = temp;
				temp = Set(nsize);
				//Set temp1(nsize);
				for (int k = 0; k < nsize - 1; ++k)
					temp.data[k] = temp1.data[k];
				temp.data[nsize - 1] = a.data[i];
				//temp = temp1;
			}
		}

		//Set temp(size);
		/*for (int i = 0; i < size; ++i)
			temp.data[i] += data[i] + k;*/
		return temp;
	}

	/* ����������� ������� ��������� */
	int operator()()
	{
		return size;
	}

	// �������� ��� �����-������
	friend ostream& operator<<(ostream& out, const Set& a)
	{
		for (int i = 0; i < a.size; ++i)
			out << a.data[i] << " ";
		return out;
	}

	friend istream& operator>>(istream& in, Set& a)
	{
		for (int i = 0; i < a.size; ++i)
			in >> a.data[i];
		return in;
	}

	// ������ ��� ������ � ����������
	IteratorS first() { return beg; } // ���������� ��������� �� ������ �������
	IteratorS last() { return end; } // ���������� ��������� �� �������, ��������� �� ���������
private:
	int size; // ������ �������
	int* data; // ��������� �� ������������ ������ �������� �������
	IteratorS beg; // ��������� �� ������ ������� �������
	IteratorS end; // ��������� �� �������, ��������� �� ���������
};