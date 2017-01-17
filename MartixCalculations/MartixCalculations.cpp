// MartixCalculations.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "Matrix.h"
#include <fstream>
int main()
{

	
	
	Matrix<int> test(3,3);
   
	std::fstream file;
	file.open("data.txt");
	if (file.good())
	{
		file >> test;

	}
	else
	{
	std::cerr << "B³¹d otwarcia pliku";
	}
	//std::cin >> test;
	
	//test << 5;


	
	auto o = test.Inverse();
	std::cout << o;

	
    
	system("PAUSE");
    return 0;
}

