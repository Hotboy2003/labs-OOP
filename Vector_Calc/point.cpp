#include <header.hpp>
#include <cmath>

Point::Point(double x, double y, double z) // конструктор
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Point::~Point() //деструктор
{

}

double Point::GetX() { return x; }
double Point::GetY() { return y; }
double Point::GetZ() { return z; }

void Point::SetX(double m_x) { x = m_x; }
void Point::SetY(double m_y) { y = m_y; }
void Point::SetZ(double m_z) { z = m_z; }



Vector::Vector(Point p1, Point p2) //конструктор
{
	v_x = p2.GetX() - p1.GetX();
	v_y = p2.GetY() - p1.GetY();
	v_z = p2.GetZ() - p1.GetZ();
}

Vector::Vector(double x, double y, double z)
{
	this->v_x = x;
	this->v_y = y;
	this->v_z = z;
}

Vector::Vector()
{
	v_x = 0;
	v_y = 0;
	v_z = 0;
}

Vector Add_Vector(Vector v1, Vector v2)
{
	return Vector(v1.GetV_X() + v2.GetV_X(), v1.GetV_Y() + v2.GetV_Y(), v1.GetV_Z() + v2.GetV_Z());
}

Vector Diff_Vector(Vector v1, Vector v2)
{
	return Vector(v1.GetV_X() - v2.GetV_X(), v1.GetV_Y() - v2.GetV_Y(), v1.GetV_Z() - v2.GetV_Z());
}

Vector Reverse_Vector(Vector v1)
{
	return Vector(v1.Vector::GetV_X() * (-1), v1.GetV_Y() * (-1), v1.GetV_Z() * (-1));
}

Vector Unit_Vector(Vector v1)
{
	if (Length_Vector(v1) == 0)
	{
		return Vector(0, 0, 0);
	}

	return Vector(v1.GetV_X() / Length_Vector(v1), v1.GetV_Y() / Length_Vector(v1), v1.GetV_Z() / Length_Vector(v1));
}

Vector Double_Prod_Vector(Vector v1, double a)
{
	return Vector(a * v1.GetV_X(), a * v1.GetV_Y(), a * v1.GetV_Z());
}

double Scalar_Prod_Vector(Vector v1, Vector v2)
{
	return v1.GetV_X() * v2.GetV_X() + v1.GetV_Y() * v2.GetV_Y() + v1.GetV_Z() * v2.GetV_Z();
}

Vector Prod_Vector(Vector v1, Vector v2)
{
	double prod_x = v1.GetV_Y() * v2.GetV_Z() - v1.GetV_Z() * v2.GetV_Y();
	double prod_y = v1.GetV_Z() * v2.GetV_X() - v1.GetV_X() * v2.GetV_Z();
	double prod_z = v1.GetV_X() * v2.GetV_Y() - v1.GetV_Y() * v2.GetV_X();
	return Vector(prod_x, prod_y, prod_z);
}

double Mixed_Prod_Vector(Vector v1, Vector v2, Vector v3)
{
	double a = v1.GetV_X() * v2.GetV_Y() * v3.GetV_Z();
	double b = v1.GetV_Z() * v2.GetV_X() * v3.GetV_Y();
	double c = v1.GetV_Y() * v2.GetV_Z() * v3.GetV_X();
	double d = v1.GetV_Z() * v2.GetV_Y() * v3.GetV_X();
	double e = v1.GetV_X() * v2.GetV_Z() * v3.GetV_Y();
	double f = v1.GetV_Y() * v2.GetV_X() * v3.GetV_Z();
	return a + b + c - d - e - f;
}

bool Is_Collinearity_Vector(Vector v1, Vector v2)
{
	Vector v3 = Prod_Vector(v1, v2);
	if (v3.GetV_X() == 0 && v3.GetV_Y() == 0 && v3.GetV_Z() == 0)
	{
		return true;
	}
	return false;
}

bool Is_Complanarity_Vector(Vector v1, Vector v2, Vector v3)
{
	double a =  Mixed_Prod_Vector(v1, v2, v3);
	if (a == 0)
	{
		return true;
	}
	return false;
}

double Distance_Between_Vector(Vector v1, Vector v2)
{
	return sqrt(pow((v1.GetV_X() - v2.GetV_X()), 2) + pow((v1.GetV_Y() - v2.GetV_Y()), 2) + pow((v1.GetV_Z() - v2.GetV_Z()), 2));
}

double Angle_Between_Vector(Vector v1, Vector v2)
{
	return acos(Scalar_Prod_Vector(v1, v2) / (Length_Vector(v1) * Length_Vector(v2)))*180 / acos(-1);
}

double Length_Vector(Vector v1)
{
	return sqrt(pow(v1.GetV_X(), 2) + pow(v1.GetV_Y(), 2) + pow(v1.GetV_Z(), 2));
}

int Privet()
{
	std::cout << "Привет, пользователь! Это калькулятор векторов. Выбери что хочешь сделать (выбери цифру). Вот твое меню:" << std::endl;
	std::cout << "1 - сложение векторов" << std::endl;
	std::cout << "2 - вычитание векторов" << std::endl;
	std::cout << "3 - скалярное произведение векторов" << std::endl;
	std::cout << "4 - векторное произведение векторов" << std::endl;
	std::cout << "5 - определить коллинеарность векторов" << std::endl;
	std::cout << "6 - найти угол между векторами" << std::endl;
	std::cout << "7 - найти расстояние между векторами" << std::endl;
	std::cout << "8 - определить компланарность трех векторов" << std::endl;
	std::cout << "9 - cмешанное произведение трех векторов" << std::endl;
	std::cout << "10 - получить обратный вектор" << std::endl;
	std::cout << "11 - получить единичный вектор" << std::endl;

	int i;
	std::cin >> i;

	return i;
}

void Create_Vector(Vector &v1)
{
	std::cout << "Как вы хотите ввести вектор" << std::endl << "1 - через точки" << std::endl << "2 - ввести координаты вектора" << std::endl;
	int j;
	std::cin >> j;

	int x_1, y_1, z_1;
	int x_2, y_2, z_2;

	if (j == 1)
	{
		std::cout << "Введите координаты первой точки: " << std::endl;
		std::cin >> x_1 >> y_1 >> z_1;
		std::cout << "Введите координаты второй точки: " << std::endl;
		std::cin >> x_2 >> y_2 >> z_2;
		
		Point p1(x_1, y_1, z_1);
		Point p2(x_2, y_2, z_2);
		
		v1 =Vector(p1, p2);
	}
	else if (j == 2)
	{
		std::cout << "Введите координаты вектора: " << std::endl;
		std::cin >> x_1 >> y_1 >> z_1;
		
		v1 = Vector(x_1, y_1, z_1);
	}
	else
	{
		std::cout << "Вы ввели несуществующую команду. Выставлен нулевой вектор по умолчанию." << std::endl;
	}
}

void Operation(Vector v1, Vector v2, Vector v3, int i)
{
	Vector v_final;
	double double_x; 
	bool bool_x;

	if (i == 1) { v_final = Add_Vector(v1, v2); }
	else if (i == 2) { v_final = Diff_Vector(v1, v2); }
	else if (i == 3) { double_x = Scalar_Prod_Vector(v1, v2); }
	else if (i == 4) { v_final = Prod_Vector(v1, v2); }
	else if (i == 5) { bool_x = Is_Collinearity_Vector(v1, v2); }
	else if (i == 6) { double_x = Angle_Between_Vector(v1, v2); }
	else if (i == 7) { double_x = Distance_Between_Vector(v1, v2); }
	else if (i == 8) { bool_x = Is_Complanarity_Vector(v1, v2, v3); }
	else if (i == 9) { double_x = Mixed_Prod_Vector(v1, v2, v3); }
	else if (i == 10) { v_final = Reverse_Vector(v1); }
	else if (i == 11) { v_final = Unit_Vector(v1); }

	if (i == 5 || i == 8) { Out_Bool(bool_x); }
	else if (i == 3 || i == 6 || i == 7 || i == 9) { Out_Double(double_x); }
	else { Out_vector(v_final); }
}

void Out_vector(Vector v_final)
{
	std::cout << "Вот результат: " << v_final.GetV_X() << " " << v_final.GetV_Y() << " " << v_final.GetV_Z() << std::endl;
}

void Out_Double(double x)
{
	std::cout << "Вот результат: " << x << std::endl;
}

void Out_Bool(bool bool_x)
{
	if (bool_x == true) { std::cout << "Вот ваш результат: да" << std::endl; }
	else { std::cout << "Вот ваш результат: нет" << std::endl; }
}

Vector::~Vector()
{

}

double Vector::GetV_X() { return v_x; }
double Vector::GetV_Y() { return v_y; }
double Vector::GetV_Z() { return v_z; }