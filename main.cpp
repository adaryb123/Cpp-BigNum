#include <iostream>
#include "bignum.h"

int main()
{
	std::string number1 = "", number2 ="";
	std::cout << "Enter first number:\n";
	std::getline(std::cin,number1);
	std::cout << "Enter second number:\n";
	std::getline(std::cin, number2);
	try {
		BigNum first{ number1};
		BigNum second{ number2 };
		BigNum temp{ first };

		std::cout << "first number : " << first << '\n';
		std::cout << "second number : " << second << '\n';
		
		std::cout << "+ first : " << (+first) << '\n';
		std::cout << "- first : " << (-first) << '\n';
		std::cout << "first += second : " << (first += second) << '\n';
		first = temp;
		std::cout << "first -= second : " << (first -= second) << '\n';
		first = temp;
		std::cout << "first *= second : " << (first *= second) << '\n';
		first = temp;

		std::cout << "first + second : " << (first + second) << '\n';
		std::cout << "first - second : " << (first - second) << '\n';
		std::cout << "first * second : " << (first * second) << '\n';

		std::cout << "first < second : " << (first < second) << '\n';
		std::cout << "first <= second : " << (first <= second) << '\n';
		std::cout << "first == second : " << (first == second) << '\n';
		std::cout << "first >= second : " << (first >= second) << '\n';
		std::cout << "first > second : " << (first > second) << '\n';
		std::cout << "first != second : " << (first != second) << '\n';
	}
	catch (std::invalid_argument) 
	{
		std::cout << "Invalid input\n";
	}
	catch (...)
	{
		std::cout << "Something strange happened\n";
	}
	return 0;
}
