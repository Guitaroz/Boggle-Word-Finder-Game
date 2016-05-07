#pragma once
#include "HTable.h"
#include <string>
#include <ctime>
#include "Graph.h"
using namespace std;
#define buckets 20000

#include "BST.h"

class DTSTimer
{
	unsigned int startTime;

public:
	DTSTimer()
	{
		reset();
	}

	void reset()
	{
		startTime = clock();
	}

	unsigned int getElapsedTime() const
	{
		return (clock() - startTime);
	}

	static void delay(const unsigned int milli)
	{
		unsigned int st = clock();
		while (clock() - st < milli){}
	}
};
struct CharItem
{
	char character;
	bool activated;
	CharItem(char l = '0', bool on = false)
	{
		character = l; activated = on;
	}
};
class Game 
{
	HTable<string> * m_hash;
	BST<string> m_tree;
	Graph<CharItem> m_graph;
	unsigned int m_score;
	bool b_Run = true;
	string lastWordScored;
	DTSTimer m_time;
	string userInput;
	void LookNice() const;
	void DrawFrame() const;

	//unsigned int brownies(const string& S);

public:

	Game();
	~Game();
	void AnimateIntro();
	void Run();
	void Show();
	void SaveScores();
	bool AskToPlayAgain()const;
	void DrawTable() const;
	bool CheckForLetter(char L, bool on);
	void LinkGraph();
	void ResetCharBools();
	bool CheckForVowels(string& table);
	void InitializeTable(string& table);
	void AskUserWhatTable();
	bool TraverseAndFind(unsigned int& startVertex, string& str);
	//typedef unsigned int (Game::*hashfunc)(const string& S);
	//hashfunc p
};

