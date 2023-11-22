#pragma once
#include <iostream>


class Point
{
public:
	Point(double x, double y, double z); // конструктор
		
	~Point(); //деструктор

	// гетеры
	double GetX();
	double GetY();
	double GetZ();

	// сетеры
	void SetX(double newX);
	void SetY(double newY);
	void SetZ(double newZ);

private:
	double x;
	double y;
	double z;
};

class Vector
{
public:
	Vector(Point p1, Point p2); //конструктор по двум точкам
	Vector(double x, double y, double z); // конструктор по координатам
	Vector(); // конструктор пустого вектора (нулевого)

	~Vector(); //деструктор

	//гетеры
	double GetV_X();
	double GetV_Y();
	double GetV_Z();

private:
	double v_x;
	double v_y;
	double v_z;
};

double Length_Vector(Vector v1); //длина вектора
Vector Add_Vector(Vector v1, Vector v2); //сложение векторов
Vector Diff_Vector(Vector v1, Vector v2); // разность векторов
Vector Reverse_Vector(Vector v1); // обратный вектор
Vector Unit_Vector(Vector v1); // единичный вектор
Vector Double_Prod_Vector(Vector v1, double a); // умножение вектора на число
Vector Prod_Vector(Vector v1, Vector v2); // произведение векторов
double Mixed_Prod_Vector(Vector v1, Vector v2, Vector v3); // смешанное произведение векторов
bool Is_Collinearity_Vector(Vector v1, Vector v2); // коллинеарны ли векторы
bool Is_Complanarity_Vector(Vector v1, Vector v2, Vector v3); // компланарны ли векторы
double Distance_Between_Vector(Vector v1, Vector v2); // расстояние между двумя векторами
double Angle_Between_Vector(Vector v1, Vector v2); // угол между двумя векторами

int Privet(); // приветствие и вывод меню
void Create_Vector(Vector &v1); // создание вектора с консоли
void Operation(Vector v1, Vector v2, Vector v3, int i); // операции с векторами в зависимости от выбранного действия
void Out_vector(Vector v_final); // вывод вектора
void Out_Double(double double_x); // вывод числа
void Out_Bool(bool bool_x); // вывод да/нет