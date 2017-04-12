// File name: BoggleDriver.cpp
// Author: Edward Goode
// userid: goodees
// Email: edward.s.goode@gmail.com
// Class: CS2201 @ Vanderbilt U.
// Assignment Number: project10
// Description:  Main driver for solving Boggle game
// Honor statement: Honor Above All
// Last Changed: 12/07/2015

#include<iostream>
#include "Boggle.h"
using namespace std;

//file string constants
const string dictionary = "ospd.txt";
const string board = "boggle-in.txt";

int main()
{
	//create new Boggle given files
	Boggle newBoggle(dictionary, board);

	//solve
	newBoggle.solve();

	//exit
	cout << "Press enter to exit." << endl;
	cin.get();
	return 0;
}