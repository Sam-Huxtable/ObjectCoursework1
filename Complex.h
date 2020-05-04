/****************************File Description*********************************
*			Author: Samuel Huxtable		Last Revision: 25/3/20				 *
*							File Name: Complex.h							 *
*	Description: Defines the Class Complex and creates all varibles and		 *
*				 Functions used by the class. Also overloads the following	 *
*				 operators "+", "-", "/", "*", "+="							 *
*																			 *
******************************************************************************/
#ifndef Complex_H
#define Complex_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "Complex.h"
using namespace std;

class Complex {
	//Initilize varibles
	string linestr, line, Type, formChoice;
	int k = 0;
	ifstream readfile;
	ofstream writefile;
	int check = 1;
	double real = 0; 
	double img = 0;
	double out1, out2, hold, hold2 ,In1, In2;	

public:
	//Declare Functions that are part of class Complex
	const string returnType();
	void setType(string T);
	void setIn1(double);
	void setIn2(double);
	const double returnIn1Polar();
	const double returnIn2Polar();
	const double returnIn1Rec();
	const double returnIn2Rec();
	void modifyElements();
	void viewComplex();
	vector<Complex>  GetComplexListFromFile();
	void SaveComplexListToFile(vector<Complex>& ComplexList);

	//Create object of type complex (No arguments)
	Complex() {};
	Complex(const string t) {
		cout << "Please also input values" << endl;
		cout << "Input 1: ";
		cin >> In1;
		cout << "Input 2: ";
		cin >> In2;
		Type = t;
	};
	//Create object of type complex (3 arguments)
	Complex(const string t, const double r, const double i) {
		In1 = r;
		In2 = i;
		Type = t;
	};
	//Overlaod the unary - operator to change the sign of objects complex
	Complex operator-() {
		Complex temp;
		if (Type == "p") {
			Type = "r";
			real = In1 * cos(In2);
			img = In1 * sin(In2);
			temp.In1 = - real;
			temp.In2 = - img;
			temp.Type = "r";
		} else {
			temp.In1 = -In1;
			temp.In2 = -In2;
			temp.Type = "r";
		}

		return temp; //Return complex object temp and all its values E.g. In1, In2, Type
	}
	//Overlaod the + operator to add objects of type Complex
	Complex operator+(Complex& c) {
		Complex temp;
		real = In1;
		img = In2;
		c.real = c.In1;
		c.img = c.In2;
		if (Type == "p") {
			Type = "r";
			real = In1 * cos(In2);
			img = In1 * sin(In2);
		}
		if (c.Type == "p") {
			c.Type = "r";
			c.real = c.In1 * cos(c.In2);
			c.img = c.In1 * sin(c.In2);
		}

		temp.In1 = real + c.real;
		temp.In2 = img + c.img;
		temp.Type = "r";
		return temp;	//Return complex object temp and all its values E.g. In1, In2, Type
	}
	//Overlaod the - operator to subtrack objects of type Complex
	Complex operator-(Complex& c) {
		Complex temp;		//create a complex object Temp

		real = In1;			//set up buffers for conversion
		img = In2;
		c.real = c.In1;
		c.img = c.In2;
		//Convert both incoming complex numbers to retanglur
		if (Type == "p") {
			Type = "r";
			real = In1 * cos(In2);
			img = In1 * sin(In2);
		}
		if (c.Type == "p") {
			c.Type = "r";
			c.real = c.In1 * cos(c.In2);
			c.img = c.In1 * sin(c.In2);
		}
		temp.Type = "r";
		temp.In1 = real -c.real;
		temp.In2 = img - c.img;
		return temp;	//Return complex object temp and all its values E.g. In1, In2, Type
	}

	//Overload the / operator to divide objects of type Complex
	Complex operator/(Complex& c) {
		Complex temp;
		real = In1;
		img = In2;
		c.real = c.In1;
		c.img = c.In2;

		if (Type == "r") {									//Convert both incoming complex numbers to retanglur
			real = sqrt(pow(In1, 2) + pow(In2, 2));
			hold = In2 / In1;
			img = std::atan(hold);
			Type = "p";
		}
		if (c.Type == "r") {
			c.real = sqrt(pow(c.In1, 2) + pow(c.In2, 2));
			c.hold = c.In2 / c.In1;
			c.img = std::atan(c.hold);
			c.Type = "p";
		}
		temp.Type = "p";
		temp.In1 = real / c.real;
		temp.In2 = img - c.img;
		return temp;	//Return complex object temp and all its values E.g. In1, In2, Type
	}
	//Overload the * operator to divide objects of type Complex
	Complex operator*(Complex& c) {
		Complex temp;

		real = In1;
		img = In2;
		c.real = c.In1;
		c.img = c.In2;

		if (Type == "r") {													//Convert both incoming complex numbers to retanglur
			real = sqrt(pow(In1, 2) + pow(In2, 2));
			hold = In2 / In1;
			img = std::atan(hold);
			Type = "p";
		}
		if (c.Type == "r") {
			c.real = sqrt(pow(c.In1, 2) + pow(c.In2, 2));
			c.hold = c.In2 / c.In1;
			c.img = std::atan(c.hold);
			c.Type = "p";
		}

		temp.Type = "p";
		temp.In1 = real * c.real;
		temp.In2 = img + c.img;
		return temp;	//Return complex object temp and all its values E.g. In1, In2, Type
	}

	const Complex* operator+=(const vector<Complex>& rv) {
		real = 0;
		img = 0;
		for (k = 0; k < rv.size(); k++) {
			if (rv[k].Type == "p") {									//Convert both incoming complex numbers to retanglur
				out1 = rv[k].In1 * cos(rv[k].In2);
				out2 = rv[k].In1 * sin(rv[k].In2);
				real = real + out1;
				img = img + out2;

			}
			if (rv[k].Type == "r") {
				real = real + rv[k].In1;
				img = img + rv[k].In2;
			}
		}
		cout << "In rectangular sum of all complex numbers is:" << "Real: " << real << " Imgainary: " << img << endl;
		return this;		//return
	};
};
#endif