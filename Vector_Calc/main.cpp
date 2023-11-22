#include <iostream>
#include <header.hpp>
#include <locale.h>


int main()
{
	setlocale(LC_ALL, "Russian");
	
	int i;
	Vector v1;
	Vector v2;
	Vector v3;

	i = Privet();

	if (i < 8 && i > 0)
	{
		Create_Vector(v1);
		Create_Vector(v2);
		Operation(v1, v2, v3, i);
	}
	if (i == 8 || i == 9)
	{
		Create_Vector(v1);
		Create_Vector(v2);
		Create_Vector(v3);
		Operation(v1, v2, v3, i);
	}
	if (i==10 || i ==11)
	{
		Create_Vector(v1);
		Operation(v1, v2, v3, i);
	}
	if (i < 0 || i > 11)
	{
		std::cout << "Вы ввели несуществующую команду" << std::endl;
	}

	return 0;
}