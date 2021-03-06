// dm_1115.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "vector.h"

using VECTOR::Vector;

int main()
{
	using namespace std;
	ofstream myFile;
	cout << "Please enter the address to store the datas:";
	string fileFpath;
	cin >> fileFpath;
	string fileName("RandomWalk.txt");
	string filePath = fileFpath + fileName;
	myFile.open(filePath);
	if (!myFile.is_open())
	{
		cout << "\nFailed to open the file !" << endl;
		exit(EXIT_FAILURE);
	}
	srand(time(0));
	double direction;
	Vector step;
	Vector result(0.0, 0.0);
	unsigned long steps = 0;
	double target;
	double dstep;
	cout << "Enter target distance (q to quit):";
	while (cin >> target)
	{
		
		cout << "Enter step length:";
		if (!(cin >> dstep))
			break;
		myFile << "Target Distance : " << target;
		myFile << ", Step Size: " << dstep << endl;
		cout << "Times to simulation:";
		unsigned int times;
		if (!(cin >> times) || times <= 0)
			break;
		double maxStep, minStep;
		double totalStep = 0.0;
		for (unsigned int i = 0; i < times; i++)
		{
			myFile << "\n*************" << i + 1 << "*************"<<endl;

			while (result.magval() < target)
			{
				direction = rand() % 360;
				step.reset(dstep, direction, Vector::POL);
				result = result + step;
				steps++;
				myFile << steps << ": (x,y) = " << result;
			}
			if (i == 0)
			{
				maxStep = steps;
				minStep = steps;
				//totalStep = steps;
			}
			myFile << "\nAfter " << steps << " steps, the subject "
				"has the following locatioin:\n(x,y) = "<< result;
			maxStep = maxStep > steps ? maxStep : steps;
			minStep = minStep < steps ? minStep : steps;
			totalStep += steps;
			steps = 0;
			result.reset(0.0, 0.0);
		}
		double aveStep = totalStep / times;
		myFile << "--After " << times << " times simulation--"<<endl;
		myFile << "Max steps: " << maxStep<<endl;
		myFile << "Min steps: " << minStep << endl;
		myFile << "Average steps: " << aveStep;
		/*
		myFile << "\nAfter " << steps << " steps, the subject "
			"has the following locatioin:\n(x,y) = ";
		myFile << result ;
		result.polar_mode();
		myFile << "or\n" << result << endl;
		
		myFile << "Average outward distance per step="
			<< result.magval() / steps << endl;
			*/
		
		cout << "Enter target distance (q to quit):";
	}
	cout << "Bye!\n";
	myFile.close();
	cin.clear();
	while (cin.get() != '\n')
		continue;
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
