/****************************File Description*********************************
*	Author: Samuel Huxtable		Last Revision: 25/3/20						 *
*	Description: Contains all functions used by the class Complex.			 *
*																			 *
*							Funtions Included:								 *
*																			 *
*	finished-Function to check if the user is finshed what they are doing	 *
*	setType- Set the Type of Class Complex								     *
*	setIn1- Set In1 of a object Complex										 *
*	setIn2- Set In2 of a object Complex										 *
*	returnType - Return the Type of a complex object						 *
*	returnIn1Polar - Returns In1 in polar									 *
*	returnIn2Polar - Returns In2 in polar									 *
*	returnIn1Rec - Returns In1 in rectangular								 *
*	returnIn2Rec - Returns In2 in rectangular								 *
*	modifyElements - Allows the modification of complex numbers				 *
*	viewComplex - Outputs complex number in both forms						 *
*	GetComplexListFromFile - Gets numbers from a file and stores in a vector *
*	SaveComplexListToFile - Saves complex numbers back to a file			 *
******************************************************************************/

#include "Complex.h"

#include <iostream>
#include <string.h>
#include <vector>
#include <cmath>
#include <math.h>

using namespace std;
//Declare functions 
int finished();

//SetType(string containing either r or p) - Sets Type to the input value
inline void Complex::setType(string T) {
	Type = T;
}

//SetIn1(double containing the value to alter) - Sets In1 to the input value 
inline void Complex::setIn1(double R) {
	In1 = R;
}

//SetIn2(double containing the value to alter) - Sets In2 to the input value 
inline void Complex::setIn2(double I) {
	In2 = I;
}

//returnType() - Return the Type of a complex object	 
inline const string Complex::returnType() {
	return Type;
}

//returnIn1Polar() - Returns In1 in polar			
inline const double Complex::returnIn1Polar() {
	Complex temp;

	if (Type == "r") {
		temp.In1 = In1 * cos(In2);
		return temp.In1;
	} else {
		temp.In1 = In1;
		return temp.In1;
	}
}

//returnIn2Polar() - Returns In2 in polar		
inline const double Complex::returnIn2Polar() {
	Complex temp;

	if (Type == "r") {
		temp.hold = In2 / In1;
		temp.In2 = std::atan(hold);
		return temp.In2;
	}
	else {
		temp.In2 = In2;
		return temp.In2;
	}
}

//returnIn1Rec() - Returns In1 in rectangular	
inline const double Complex::returnIn1Rec() {
	Complex temp;

	if (Type == "p") {
		temp.In1 = In1 * cos(In2);
		return temp.In1;
	}
	else {
		temp.In1 = In1;
		return temp.In1;
	}
}

//returnIn2Rec() - Returns In2 in rectangular	
inline const double Complex::returnIn2Rec() {
	Complex temp;

	if (Type == "p") {
		temp.In2 = In1 * sin(In2);
		return temp.In2;
	}
	else {
		temp.In2 = In2;
		return temp.In2;
	}
}

//modifyElements() - Displays complex number in either p or r and allows the user to modify In1 or In2
void Complex::modifyElements() {
	cout << "Which form would you wish to modify this number in? (p/r)" << endl;	//Ask user what form to view the number in
	cin >> formChoice;
	if (formChoice == "r") {
		if (Type == "p") {				//If user wants "r" but the number is stored in "p", convert and then output
			out1 = In1 * cos(In2);
			out2 = In1 * sin(In2);
		}
		else {
			out1 = In1;
			out2 = In2;
		} //else output the number without conversion
	}
	if (formChoice == "p") {
		if (Type == "r") {			//If user wants "p" but the number is stored in "r", convert and then output
			out1 = sqrt(pow(In1, 2) + pow(In2, 2));
			out2 = std::atan2(In2, In1);
		}
		else {
			out1 = In1;
			out2 = In2; 		//else output the number without conversion
		}
	}
	check = 1;
	while (check) {
		cout << "Number to be modifed:" << formChoice << " " << out1 << " " << out2 << endl;		//Print the number in the requested form
		cout << "Which element do you wish to modify?(1/2)" << endl;							//Ask which element to modify
		cin >> k;
		cout << "Which is your new value?" << endl;												//Ask for the new value
		cin >> hold;
		if (k == 1) {																			//Depending on the user response change In1 or In2 
			out1 = hold;
			In1 = hold;
		}
		else if (k == 2) {
			out2 = hold;
			In2 = hold;
		}
		else {
			cout << "Please choose either 1 or 2" << endl;
		}
		cout << "The new number is:" << formChoice << " " << out1 << " " << out2 << endl;	//Output new number
		check = finished();			//Ask if the user wishes to modify more elements 
	}
}

//viewComplex() - Oututs complex number in both polar and rectangular
void Complex::viewComplex() {		 

	if (Type == "r") {			//If the number is rectangular
		real = sqrt(pow(In1, 2) + pow(In2, 2));
		hold = In2 / In1;
		img = std::atan(hold);
		cout << "In rectangular form: Real:" << In1 << " Imaginary:" << In2 << endl;
		cout << "In Polar form: Magnitude:" << real << " Angle:" << img << endl;
	}
	if (Type == "p") {		//If the number is polar 
		real = In1 * cos(In2);
		img = In1 * sin(In2);
		cout << "In rectangular form: Real:" << real << " Imaginary:" << img << endl;
		cout << "In Polar form: Magnitude:" << In1 << " Angle:" << In2 << endl;
	}
}

//GetComplexListFromFile() - Gets numbers from a file and stores in a vector
vector<Complex>  Complex::GetComplexListFromFile() {
	vector<Complex> ComplexList;

	int k;
	int i = 0;
	readfile.open("C:/Users/SHuxt/Documents/Cardiff_stuff/Object/Coursework1/complex_numbers.txt");		//Change this depending on where you stored your numbers
	
	while (std::getline(readfile, linestr)) {			//Get each line of the file by looping through it 
		k = 0;
		ComplexList.resize(i + 1);					//Resize the vector to be big enough to take the next input
		std::stringstream ss(linestr);					//Convert the line into a string
		while (ss.good() && k < 3) {					//Loop through each value seperated by a space and save that value into List
			ss >> line;
			if (k == 0) {
				ComplexList[i].setType(line);			//Set the type of ComplexList[i] from the file
			}
			else if (k == 1) {
				ComplexList[i].setIn1(std::stoi(line));		//Set In1 of ComplexList[i] from the file
			}
			else if (k == 2) {
				ComplexList[i].setIn2(std::stoi(line));		//Set In2 of ComplexList[i] from the file
			}
			k++;			//Increment k to indicate which value of the line is being read
		}
		i++;		//Increment i to increase the size of ComplexList and show where to store the new information
	}
	readfile.close();	//Close the file
	return ComplexList;		//Return the vector ComplexList to the call location
}

//SaveComplexListToFile(Pointer to the Complex vector containing all store complex numbers)
void Complex::SaveComplexListToFile(vector<Complex>& ComplexList) {

	remove("C:/Users/SHuxt/Documents/Cardiff_stuff/Object/Coursework1/complex_numbers.txt");			//Empty the file complex_numbers.txt

	writefile.open("C:/Users/SHuxt/Documents/Cardiff_stuff/Object/Coursework1/complex_numbers.txt");	//Open a new Complex_numbers.txt for writing
	for (k = 0; k < ComplexList.size(); k++) {				//Loop through List, in increments of 3, upto the list size
		if (ComplexList[k].Type == "r" || ComplexList[k].Type == "p") {				//Accounts for cases the user didn't choose a proper type
			writefile << ComplexList[k].Type << " " << ComplexList[k].In2 << " " << ComplexList[k].In2 << endl;							//Write to the file
		}
	}
	writefile.close();				//close the file
}

int finished() {		//Function to check if the user is finshed what they are doing

	string fin = "n";
	string yn = "";
	while (fin == "n") {
		cout << "Have you finished? (y/n)";
		cin >> yn;
		if (yn == "y") { return 0; }
		if (yn == "n") { return 1; }
		else { fin = "n"; }
	}
	return 0;
}

