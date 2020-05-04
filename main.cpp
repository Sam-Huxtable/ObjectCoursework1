/****************************File Description*********************************
*			Author: Samuel Huxtable		Last Revision: 25/3/20				 *
*							File Name: Main.cpp								 *
*	Description: Main function as described in course work, also contains    *
*				 a demo of overlaod functions								 *
*																			 *
******************************************************************************/
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "Complex.h"

using namespace std;

int main() {

	//Initilize varibles
	int check = 1;
	int check2 = 1;
	int choice, k;
	double C2, C3;
	vector<Complex> ComplexList;
	Complex Test;
	string C1, choice2;

	while (check) {
		cout << "What action do you wish to undertake?" << endl;		//Question which part of the coursework to run
		cout << "1: Run main as described in coursework" << endl;
		cout << "2: Overload Demostration" << endl;
		cin >> choice;
		if (choice == 1) {
			ComplexList = Test.GetComplexListFromFile();
			for (k = 0; k < ComplexList.size(); k++) {					//Loop through List, in increments of 3, upto the list size
				ComplexList[k].viewComplex();							//Call function viewComplex for each number in the vector
			}
			Test += ComplexList;
			
			while (check2) {
				cout << "Would you like to add more complex numbers?(y/n)" << endl;
				cin >> choice2;
				if (choice2 == "y") {
					k++;
					ComplexList.resize(k + 1);				//Resize the vector to the current size + 1
					cout << "Type of complex number: ";
					cin >> C1;							
					ComplexList[k].setType(C1);				//Set the type of Complex
					cout << "Input 1: ";
					cin >> C2;								
					ComplexList[k].setIn1(C2);				//Set the first number of Complex
					cout << "Input 2: ";
					cin >> C3;
					ComplexList[k].setIn2(C3);				//Set the second number of Complex
				}
				else if (choice2 == "n") {
					check2 = 0;
				}
				else { cout << "Please answer either y or n" << endl; }
			}
			Test += ComplexList;						//Output the sum of ComplexList
			Test.SaveComplexListToFile(ComplexList);			//Save the final complex vector to a file
			check2 = 1;
		}

		if (choice == 2) {             //Demo of overload functions as described in question 5
			Complex B("p", 10, 0.5);	//Create the complex numbers as shown in file
			Complex C("r", 12, 14);
			Complex D("p", 25, 1);
			Complex E("p", 100, 0.8);
			Complex A;						//Create a Complex to store the answer
			A =(C - D) ;				//subtract D from C
			A = A/E;					//Divide A by E
			A = B * A;					//Times B and A
			A = -A;						//Change the sign of A
			A.viewComplex();			//View the answer
		}
	}
	system("pause");
	return 0;
}

