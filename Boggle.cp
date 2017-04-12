// File name: Boggle.cpp
// Author: Edward Goode
// userid: goodees
// Email: edward.s.goode@gmail.com
// Description:  .cpp file for Boggle which defines a
//				class that provides support for solving
//				the boggle game.

#include <cstddef>
#include <fstream>
#include <string>
#include <iostream>
#include "Boggle.h"

//Class constructor
//pre: Boggle does not exist
//constructs a trie and opens files
Boggle::Boggle(const string& words, const string& board)
	:boggleWords(), foundWords()
{
	cout << "Loading valid words. Please wait..." << endl;

	//set all values of Visited to false
	clearBoard();

	//fill array with characters
	fillBoard(board);

	//upload accepptable boggle words to trie
	boggleWords.loadFromFile(words);
}

//solve
//pre: boggle exists
//post: boggle is solved and words printed out
void Boggle::solve()
{
	//show board
	displayBoard();

	//receive input from user and validate
	getUserWords();

	//find all words stemming from each index
	for (int row = 0; row < BOARD_SIZE; row++) {
		for (int col = 0; col < BOARD_SIZE; col++) {
			findWords(string(1, value[row][col]), row, col);
			clearBoard();
		}
	}

	//print out computer found words
	print();

}

//findWords(string str, int row, int col)
//Pre: boggle board is set up
//Post: all words of square are found
void Boggle::findWords(string str, int row, int col)
{
	//set visited to true
	visited[row][col] = true;

	//if valid insert into trie
	if (str.length() >= 4 && boggleWords.isWord(str) && !userWords.isWord(str))
	{
		foundWords.insert(str);
	}

	//call for each sorrounding index
	for (int nRow = row - 1; nRow <= row + 1; nRow++) {
		for (int nCol = col - 1; nCol <= col + 1; nCol++) {
			if (!(nRow == row && nCol == col))
				possibleWord(str, nRow, nCol);
		}
	}
}

//possibleWOrds(string str, int row, int col)
//recursively finds words in boggle with findWords
//pre: boggle set up and findWords called
//post: findWords is called recursively if potential spot
void Boggle::possibleWord(string str, int row, int col)
{
	//if it is not visited and on the board
	if (onBoard(row, col) && !hasVisited(row, col))
	{
		//add to string
		string s = str;
		s.append(1, value[row][col]);

		//if it is a prefix continue recursive call
		if (boggleWords.isPrefix(s)) {
			findWords(s, row, col);

			//if no success finding word set visit to false
			unVisit(row, col);
		}
	}
}

//clear board
//Pre: boggle and visited exists
//Post: all visited values are set to false
void Boggle::clearBoard()
{
	//for each index set to false
	for (int row = 0; row < BOARD_SIZE; row++)
		for (int col = 0; col < BOARD_SIZE; col++)
			visited[row][col] = false;
}

//hasVisited(int row, int col)
//pre: visted array initialized and boggle created
//post: returns true if part of board has been visited
bool Boggle::hasVisited(int row, int col) const
{
	//if has been visited return true
	return visited[row][col];
}

//unVisit(int row, int col)
//pre: visited array initialized and boggle created
//post: sets visited[row][col] to false
void Boggle::unVisit(int row, int col)
{
	//set visited[][] to false
	visited[row][col] = false;
}

//onBoard(int row, in col)
//pre: boggle exists
//post: returns true if on board
bool Boggle::onBoard(int row, int col) const
{
	//if it is on the board return true
	return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
}

//getUserWords
//puts all of user inputs words that >= 4 into trie and a word
//pre: lexicon for potential words full
//post: user words lexicon full
void Boggle::getUserWords()
{
	//declare string
	string str;

	//while values are being input and they are not q
	while (cin >> str && str != "q" && str != "Q")
	{
		//if less than 4 not acceptable
		if (str.length() < 4)
		{
			cout << "Sorry, your words must be";
			cout << "at least 4 characters long." << endl;
		}
		else if (boggleWords.isWord(str))
		{
			//insert and output word
			userWords.insert(str);
			cout << "Okay, you found the word " << str << "." << endl;
		}
		else
		{
			//output word
			cout << "Don't try to cheat! " << str;
			cout << " is not a valid word" << endl;
		}
	}

	//print user found words
	printUser();

}

//displayBoard()
//displays boggle board
//pre: boggle bored is full and declared
//post: outputs in console boggle board
void Boggle::displayBoard() const
{
	//output board
	cout << "Here is the Boggle board: \n" << endl;
	for (int row = 0; row < BOARD_SIZE; row++) {
		for (int col = 0; col < BOARD_SIZE; col++) {
			cout << " " << value[row][col] << " ";
		}
		cout << endl;
	}

	//instructions for boggle
	cout << "\nEnter as many words as you can find";
	cout << ", on word per line." << endl;
	cout << "Signal the end of your list";
	cout << "by entering the letter Q or q." << endl;
	cout << "You can take as long as you want." << endl;
}

//print()
//prints out all words found by computer and not user
//pre: user has been prompted to enter word and entered q
//post: values that user did not enter are printed
void Boggle::print() const
{
	//output computer words
	cout << "The computer found the following words: " << endl;
	cout << "==========" << endl;

	//call trie print
	foundWords.print();

	cout << "==========" << endl;

	//use wordcount to find total found
	cout << "The computer found " << foundWords.wordCount();
	cout << " words." << endl;
	cin.get();
}

//fillBoard(string& str)
//fills Boggle board with characters from file
//pre: str is passed
//post: Boggle board is filled
void Boggle::fillBoard(const string& board)
{
	//open file
	string str;
	ifstream file(board.c_str());

	//if not open throw exception
	if (!file) {
		throw std::invalid_argument("File Cannot Be Open");
	}

	//set value from file
	for (size_t row = 0; file >> str; row++)
	{
		for (size_t col = 0; col < BOARD_SIZE; col++)
			value[row][col] = str[col];
	}
}

//printUser()
//prints out all words found by  user
//pre: user has been prompted to enter word and entered q
//post: values that user did not enter are printed
void Boggle::printUser() const
{
	cout << "You found the following words: " << endl;
	cout << "==========" << endl;

	//call trie print to output user inputted words
	userWords.print();

	cout << "==========" << endl;
	cout << "You found " << userWords.wordCount() << " words." << endl;
}

