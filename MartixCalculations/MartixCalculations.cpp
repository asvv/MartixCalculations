// MartixCalculations.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "Matrix.h"
#include <fstream>
int main()
{

	
	
	Matrix<int> test(5,3);
	Matrix<int> res(5, 1);
   
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
	file.close();

	file.open("results.txt");
	if (file.good())
	{
		file >> res;

	}
	else
	{
		std::cerr << "B³¹d otwarcia pliku";
	}
	file.close();
	//std::cin >> test;
	
	//test << 5;


	
	
	std::cout << test.Solve(res);

	
    
	system("PAUSE");
    return 0;
}

