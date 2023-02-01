// колво студентов получающих степуху.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct student
{
	string name, surname, gender;
	int age, grades[3];
};

const int N = 14;

string file_path = "D:/students/";
string file_name_in = "F1.txt";
string file_name_out = "F2.txt";

void output_file(string file_name) // Вывод файла
{
	ifstream fin(file_path + file_name);

	if (!fin)
		cout << "\nОшибка при открытии! Файл не существует!\n\n";
	else
	{
		cout << "\nСодержимое файла " << file_name << ":\n\n";

		string s;
		while (!fin.eof())
		{
			getline(fin, s);
			cout << s << endl;
		}
	}
	fin.close();
}

void filling_array(student* a, string file_name) // Заполнения массива структур
{
	ifstream fin(file_path + file_name);

	student s;
	int i = 0;

	while (!fin.eof())
	{
		fin >> s.surname >> s.name >> s.gender >> s.age
			>> s.grades[0] >> s.grades[1] >> s.grades[2];

		a[i++] = s;
	}

	fin.close();
}

void check_students(student* a, string file_name) // Проверка условий
{
	ofstream ff(file_path + file_name);

	for (int i = 0; i < N; i++)
	{
		student s = a[i];

		if (s.grades[0] ==2 || s.grades[1] ==2 || s.grades[2] == 2)
		{
			ff << s.surname << " " << s.name << " " << s.gender << " " << s.age << " "
				<< s.grades[0] << " " << s.grades[1] << " " << s.grades[2] << "\n";
		}
	}
	ff.close();
}

int main()
{
	setlocale(LC_ALL, "Rus");

	output_file(file_name_in);

	student group16[N];

	filling_array(group16, file_name_in);
	check_students(group16, file_name_out);

	output_file(file_name_out);
}