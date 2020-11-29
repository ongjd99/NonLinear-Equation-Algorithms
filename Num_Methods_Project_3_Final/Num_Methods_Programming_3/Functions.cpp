/*
	Ong, Johnny

	October 21, 2020

	CS 3010.01 Numerical Methods
	Programming Project 3
*/

#include "Functions.h"
#include <string>
#include <iostream>
#include <cctype>
#include <stack>

using namespace std;

double solveFunction(bool aChoosen, double x)
{
	if (aChoosen)
	{
		return (2 * pow(x, 3)) - (11.7 * pow(x, 2)) + (17.7 * x) - 5;
	}
	else
	{
		return x + 10 - x * cosh(50 / x);
	}
}

double solveDerivative(bool aChoosen, double x)
{
	if (aChoosen)
	{
		return (6 * pow(x, 2)) - (23.4 * x) + 17.7;
	}
	else
	{
		return ((50 * sinh(50 / x)) / x) - cosh(50 / x) + 1;
	}
}

double solveMod(bool aChoosen, double x, double mod)
{
	double modNum = x + (x * mod);
	if (modNum == 0)
	{
		return 0;
	}
	double function = solveFunction(aChoosen, x);
 	return x - function * ( (x*mod) / (solveFunction(aChoosen, modNum) - function));
}

void bisection(bool aChoosen,double a, double b)
{
	double c = 0;
	double cPrev = 0;
	double fa = solveFunction(aChoosen, a);
	double fb = solveFunction(aChoosen, b);
	if (fa * fb > 0)
	{
		cout << "Function has same signs at a and b" << endl;
		return;
	}
	for (int n = 0; n < 100; n++)
	{
		c = (a+b)/2;
		double approxError = abs((c - cPrev) / c);
		double fc = solveFunction(aChoosen, c);
		cout << "Iteration: " << n << endl;
		cout << "a: " << a << endl;
		cout << "b: " << b << endl;
		cout << "c: " << c << endl;
		cout << "f(n+1): " << fc << endl;
		if (n)
		{
			cout << "approxError: " << approxError << endl;
		}
		if (abs(approxError) < 0.01)
		{
			cout << "Convergence at x = " << c << endl;
			return;
		}
		if (fa * fc > 0)
		{
			a = c;
			fa = fc;
		}
		else
		{
			b = c;
			fb = fc;
		}
		cPrev = c;
		cout << endl;
	}
}

void newton(bool aChoosen, double x)
{
	double fx = solveFunction(aChoosen, x);
	cout << "Iteration: 0" << endl;
	cout << "x: " << x << endl;
	cout << "fx: " << fx << endl;
	for (int n = 1; n < 100; n++)
	{
		double fp = solveDerivative(aChoosen, x);
		if (fp == 0)
		{
			cout << "Slope is 0. Ending method." << endl;
			return;
		}
		double d = fx / fp;
		x -= d;
		fx = solveFunction(aChoosen, x);
		cout << endl;
		cout << "Iteration: " << n << endl;
		cout << "x: " << x << endl;
		cout << "fx: " << fx << endl;
		cout << "approxError: " << d << endl;
		if (abs(d) < 0.01)
		{
			cout << "Convergence at x = " << x << endl;
			return;
		}
		else if ((n > 50 && d >= 1) || (abs(x) > pow(10, 10)))
		{
			cout << "Function is most likely converging slowly" << endl;
			cout << "or function has shot off into a direction. Ending Method." << endl;
			return;
		}
	}
}

void secant(bool aChoosen, double a, double b)
{
	double fa = solveFunction(aChoosen, a);
	double fb = solveFunction(aChoosen, b);
	if (abs(fa) > abs(fb))
	{
		swap(a, b);
		swap(fa, fb);
	}
	cout << "Iteration: 0" << endl;
	cout << "a: " << a << endl;
	cout << "fa: " << fa << endl;
	cout << "b: " << b << endl;
	cout << "fb: " << fb << endl;

	for (int n = 1; n < 100; n++)
	{
		if (abs(fa) > abs(fb))
		{
			swap(a, b);
			swap(fa, fb);
		}
		double d = (b - a) / (fb - fa);
		b = a;
		fb = fa;
		d *= fa;
		a -= d;
		fa = solveFunction(aChoosen, a);
		cout << "approxError: " << d << endl;
		if (abs(d) < 0.01)
		{
			cout << "Convergence at x = " << a << endl;
			return;
		}
		else if ((n > 50 && d >= 1) || (abs(a) > pow(10, 10)))
		{
			cout << "Function is most likely converging slowly" << endl;
			cout << "or function has shot off into a direction. Ending Method." << endl;
			return;
		}
		cout << endl;
		cout << "Iteration: " << n << endl;
		cout << "a: " << a << endl;
		cout << "fa: " << fa << endl;
		cout << "b: " << b << endl;
		cout << "fb: " << fb << endl;
	}
}

void fposition(bool aChoosen, double a, double b)
{
	double fa = solveFunction(aChoosen, a);
	double fb = solveFunction(aChoosen, b);
	if (abs(fa) > abs(fb))
	{
		swap(a, b);
		swap(fa, fb);
	}

	if (fa * fb > 0)
	{
		cout << "Function has same signs at a and b" << endl;
		return;
	}
	cout << "Iteration: 0" << endl;
	cout << "a: " << a << endl;
	cout << "fa: " << fa << endl;
	cout << "b: " << b << endl;
	cout << "fb: " << fb << endl;

	for (int n = 1; n < 100; n++)
	{
		if (abs(fa) > abs(fb))
		{
			swap(a, b);
			swap(fa, fb);
		}
		double d = (b - a) / (fb - fa);
		b = a;
		fb = fa;
		d *= fa;
		a -= d;
		fa = solveFunction(aChoosen, a);
		cout << "approxError: " << d << endl;
		if (abs(d) < 0.01)
		{
			cout << "Convergence at x = " << a << endl;
			return;
		}
		cout << endl;
		cout << "Iteration: " << n << endl;
		cout << "a: " << a << endl;
		cout << "fa: " << fa << endl;
		cout << "b: " << b << endl;
		cout << "fb: " << fb << endl;
	}
}

void modSecant(bool aChoosen, double x)
{
	double prevX = x;
	double fx = solveFunction(aChoosen, x);
	cout << "Iteration: 0" << endl;
	cout << "x: " << x << endl;
	cout << "fx: " << fx << endl;
	for (int n = 1; n < 100; n++)
	{
		x = solveMod(aChoosen, x, 0.01);
		if (x == 0)
		{
			cout << "x = 0. Function is acting weirdly. Ending Method" << endl;
			return;
		}
		double approxError = abs((x - prevX) / x);
		fx = solveFunction(aChoosen, x);
		cout << endl;
		cout << "Iteration: " << n << endl;
		cout << "x: " << x << endl;
		cout << "fx: " << fx << endl;
		cout << "approxError: " << approxError << endl;
		if (approxError < 0.01)
		{
			cout << "Convergence at x = " << x << endl;
			return;
		}
 		else if ((n > 50 && approxError >= 1) || (abs(x) > pow(10,10)))
		{
			cout << "Function is most likely converging slowly" << endl;
			cout << "or function has shot off into a direction. Ending Method." << endl;
			return;
		}
		prevX = x;
	}
}
