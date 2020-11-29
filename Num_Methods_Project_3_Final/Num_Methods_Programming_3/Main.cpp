/*
	Ong, Johnny

	October 21, 2020

	CS 3010.01 Numerical Methods
	Programming Project 3
*/

#include "Functions.h"
#include <iostream>
#include <cctype>

using namespace std;

int main()
{
	cout << "Which function would you like to test? " << endl;
	cout << "a) f(x) = 2x^3 - 11.7x^2 + 17.7x - 5" << endl;
	cout << "b) f(x) = x + 10 - xcosh(50/x)" << endl;
	char choice = 0;
	cin >> choice;

	while (!(choice == 'a' || choice == 'b'))
	{
		cout << "Invalid answer. Try again";
		cin >> choice;
	}

	bool aChoosen = choice == 'a';

	cout << "----------Bisection Method---------" << endl;
	cout << "Initial a (Will be used for the rest of the methods): ";
	double a = 0;
	cin >> a;
	cout << "Initial b (Will be used for the rest of the methods): ";
	double b = 0;
	cin >> b;
	bisection(aChoosen, a, b);
	system("Pause");

	cout << "-------False-Postion Method--------" << endl;
	fposition(aChoosen, a, b);
	system("Pause");

	cout << "------------Newton Method----------" << endl;
	newton(aChoosen, a);
	system("Pause");

	cout << "------------Secant Method----------" << endl;
	secant(aChoosen, a, b);
	system("Pause");

	cout << "----------Mod Secant Method--------" << endl;
	modSecant(aChoosen, a);

	system("Pause");
	return 0;
}