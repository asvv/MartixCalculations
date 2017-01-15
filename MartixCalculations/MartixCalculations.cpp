// MartixCalculations.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "Matrix.h"

int main()
{

	
	
	Matrix<int> test;
    std::cin >> test;
	
	//test << 5;


	std::cout << test.GetDataAt(0,0);

	

	
    
	system("PAUSE");
    return 0;
}

