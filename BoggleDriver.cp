// File name: BoggleDriver.cpp
// Author: Edward Goode
// userid: goodees
// Email: edward.s.goode@gmail.com
// Description:  Main driver for solving Boggle game


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
