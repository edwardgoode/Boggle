// File name: Boggle.h
// Author: Edward Goode
// userid: goodees
// Email: edward.s.goode@gmail.com
// Class: CS2201 @ Vanderbilt U.
// Assignment Number: project10
// Description:  .h file for Boggle class which declares a
//				class that provides support for 
//				solving the boggle game.
// Honor statement: Honor Above All
// Last Changed: 12/07/2015

#ifndef BOGGLE_H
#define BOGGLE_H

#include<string>
#include"Trie.h"
using namespace std;

//const size of board
const int BOARD_SIZE = 4;

class Boggle
{
public:

	//Class constructor
	//pre: Boggle does not exist
	//constructs a trie and opens files
	Boggle(const string& words, const string& board);

	//solve
	//pre: boggle exists
	//post: boggle is solved and words printed out
	void solve();

private:

	Trie boggleWords;						//trie of acceptable words
	Trie foundWords;						//trie of found words
	Trie userWords;							//trie of words found by user
	bool visited[BOARD_SIZE][BOARD_SIZE];	//if spot has been visited
	char value[BOARD_SIZE][BOARD_SIZE];		//char value in board

	//findWords(string str, int row, int col)
	//Pre: boggle board is set up
	//Post: all words of square are found
	void findWords(string str, int row, int col);

	//possibleWOrds(string str, int row, int col)
	//pre: boggle set up and findWords called
	//post: findWords is called recursively if potential spot
	void possibleWord(string str, int row, int col);

	//clear board
	//Pre: boggle and visited exists
	//Post: all visited values are set to false
	void clearBoard();

	//hasVisited(int row, int col)
	//pre: visted array initialized and boggle created
	//post: returns true if part of board has been visited
	bool hasVisited(int row, int col) const;

	//unVisit(int row, int col)
	//pre: visited array initialized and boggle created
	//post: sets visited[row][col] to false
	void unVisit(int row, int col);

	//onBoard(int row, in col)
	//pre: boggle exists
	//post: returns true if on board
	bool onBoard(int row, int col) const;

	//getUserWords()
	//puts all of user inputs words that >= 4 into trie and a word
	//pre: lexicon for potential words full
	//post: user words lexicon full
	void getUserWords();

	//displayBoard()
	//displays boggle board
	//pre: boggle bored is full and declared
	//post: outputs in console boggle board
	void displayBoard() const;

	//print()
	//prints out all words found by computer and not user
	//pre: user has been prompted to enter word and entered q
	//post: values that user did not enter are printed
	void print() const;

	//fillBoard(string& str)
	//fills Boggle board with characters from file
	//pre: str is passed
	//post: Boggle board is filled
	void fillBoard(const string& board);

	//printUser()
	//prints out all words found by  user
	//pre: user has been prompted to enter word and entered q
	//post: values that user did not enter are printed
	void printUser() const;
};

#endif
