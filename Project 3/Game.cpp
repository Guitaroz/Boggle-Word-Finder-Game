#include "Game.h"
#include <fstream>
#include "HTable.h"
#include <algorithm>
#include <string>
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctype.h>
#include "Graph.h"
//#include "SLList.h"
#include "BST.h"
#include "MyConsole.h"
using namespace std;



unsigned int factorial(int x_);
unsigned int brownies(const string& str)
{
	//Hashing Function
	{
		//Made this by taking one hash function and adding a little extra " + (seed << 4)"
		unsigned int hash = 0;								//0-16  68 empty
		unsigned int seed = 65599;

		for (size_t i = 0; i < str.length(); i++)
		{
			hash = hash * seed + str[i] + (seed << 4);
		}

		return hash % buckets;

	}

}
Game::Game()
{
	LookNice();
	DrawFrame();
	Console::SetCursorPosition(25, 10);
	cout << "Loading Dictionary Words...";
	srand(static_cast<unsigned int>(time(nullptr)));
	m_score = 0;
	m_hash = new HTable<string>(buckets, brownies);
	ifstream ReadIn;
	ReadIn.open("engldict.txt");

	if (ReadIn.is_open())
	{
		while (!ReadIn.eof())
		{
			string temp;
			ReadIn >> temp;
			/*if (ReadIn.eof())
				break;*/
			if (strchr(temp.c_str(), '\''))
				continue;
			if (temp.length() < 3 || temp.length() > 16)
				continue;
			m_hash->insert(temp);
		}
		m_hash->PrintHashStats();
		ReadIn.close();
	}
	system("cls");
}

Game::~Game()
{
}

void Game::LinkGraph()
{
	int intArray[8] = { -5, -4, -3, -1, 1, 3, 4, 5 };
	unsigned int i = 0;
	while (i < 4)
	{
		switch (i)
		{
		case 0:
			for (size_t E = 4; E < 8; E++)
			{
				if (E == 5)
					continue;
				m_graph[i].addEdge(i + intArray[E]);
				m_graph[15 - i].addEdge(15 - intArray[E]);
				m_graph[i + 3].addEdge((i + 3) + intArray[E - 1]);
				m_graph[15 - (i + 3)].addEdge(15 - (i + 3) - intArray[E - 1]);
			}	i++; break;
		case 1:
			for (size_t index = 1; index < 3; index++)	{
				for (size_t j = 3; j < 8; j++){
					m_graph[index].addEdge(index + intArray[j]);
					m_graph[15 - index].addEdge((15 - index) - intArray[j]);
				}
			}	i++; break;
		case 2:
			for (size_t E = 1; E < 8; E++)
			{
				int index = i + 2; //4
				if (E == 3 || E == 5)
					continue;
				m_graph[index].addEdge(index + intArray[E]);
				m_graph[15 - index].addEdge(15 - index - intArray[E]);
				m_graph[index + 3].addEdge(index + 3 + intArray[E - 1]);
				m_graph[15 - (index + 3)].addEdge((15 - (index + 3)) - intArray[E - 1]);
			}	i++; break;
		case 3:
			for (size_t case3 = i + 2; case3 < 7; case3++){
				for (size_t j = 0; j < 8; j++)	{
					m_graph[case3].addEdge(case3 - intArray[j]);
					m_graph[15 - case3].addEdge((15 - case3) - intArray[j]);
				}
			}	i++; break;
		}
	}
}

void Game::AnimateIntro()
{
	/*
		   W M   L  C  O  E e            		B  o  g  g  l  e
		   29 30 31 32 33 34 35            		40 41 42 43 44 45
		   */
	int y = 6;
	Console::SetCursorPosition(29, y);
	cout << "Wmlcoee To Bglgoe!";
	Sleep(500);
	ConsoleColor colorArr[2] = { Yellow, White };
	for (size_t i = 0; i < 5; i++)
	{
		Console::SetCursorPosition(29, y);
		Console::ForegroundColor(Red);
		cout << "Wmlcoee To Bglgoe";
		Sleep(100);
		Console::SetCursorPosition(29, y);
		Console::ForegroundColor(White);
		cout << "Wmlcoee To Bglgoe";
		Sleep(100);
	}
	Sleep(500);

	Sleep(105);
	Console::SetCursorPosition(34, y);
	cout << " ";
	Console::SetCursorPosition(34, y + 1);
	Console::ForegroundColor(Red);
	cout << "e";
	Console::SetCursorPosition(42, y);
	cout << " ";
	Console::SetCursorPosition(42, y + 1);
	Console::ForegroundColor(Red);
	cout << "l";
	Sleep(105);
	Console::SetCursorPosition(30, y);
	cout << " ";
	Console::SetCursorPosition(31, y - 1);
	Console::ForegroundColor(Red);
	cout << "m";
	Console::SetCursorPosition(34, y + 1);
	cout << " ";
	Console::SetCursorPosition(33, y + 1);
	Console::ForegroundColor(Red);
	cout << "e";
	Sleep(105);
	Console::SetCursorPosition(44, y);
	cout << " ";
	Console::SetCursorPosition(31, y - 1);
	cout << " ";
	Console::SetCursorPosition(32, y - 1);
	cout << "m";
	Console::SetCursorPosition(33, y + 1);
	cout << " ";
	Console::SetCursorPosition(32, y + 1);
	Console::ForegroundColor(Red);
	cout << "e";
	Console::SetCursorPosition(32, y - 1);
	cout << " ";
	Console::SetCursorPosition(33, y - 1);
	Console::ForegroundColor(Red);
	cout << "m";

	Console::SetCursorPosition(44, y - 1);
	cout << " ";
	Console::SetCursorPosition(43, y - 1);
	Console::ForegroundColor(Red);
	cout << "o";
	Sleep(105);
	Console::SetCursorPosition(33, y - 1);
	cout << " ";
	Console::SetCursorPosition(34, y - 1);
	Console::ForegroundColor(Red);
	cout << "m";
	Console::SetCursorPosition(32, y + 1);
	cout << " ";
	Console::SetCursorPosition(31, y + 1);
	Console::ForegroundColor(Red);
	cout << "e";
	Console::SetCursorPosition(41, y);
	cout << " ";
	Console::SetCursorPosition(42, y);
	Console::ForegroundColor(White);
	cout << "g";
	Sleep(105);///----
	Console::SetCursorPosition(33, y - 1);
	cout << " ";
	Console::SetCursorPosition(34, y - 1);
	Console::ForegroundColor(Red);
	cout << "m";
	Console::SetCursorPosition(31, y + 1);
	cout << " ";
	Console::SetCursorPosition(30, y + 1);
	Console::ForegroundColor(Red);
	cout << "e";
	Console::SetCursorPosition(42, y + 1);
	cout << " ";
	Console::SetCursorPosition(43, y + 1);
	Console::ForegroundColor(Red);
	cout << "l";
	Sleep(105);
	Console::SetCursorPosition(34, y - 1);
	cout << " ";
	Console::SetCursorPosition(34, y);
	Console::ForegroundColor(Red);
	cout << "m";
	Console::SetCursorPosition(43, y - 1);
	cout << " ";
	Console::SetCursorPosition(42, y - 1);
	Console::ForegroundColor(Red);
	cout << "o";
	Sleep(105);
	Console::SetCursorPosition(43, y + 1);
	cout << " ";
	Console::SetCursorPosition(44, y + 1);
	Console::ForegroundColor(Red);
	cout << "l";
	Sleep(105);
	Console::SetCursorPosition(30, y + 1);
	cout << " ";
	Console::SetCursorPosition(30, y);
	Console::ForegroundColor(Red);
	cout << "e";
	Console::SetCursorPosition(42, y - 1);
	cout << " ";
	Console::SetCursorPosition(41, y - 1);
	Console::ForegroundColor(Red);
	cout << "o";
	Sleep(105);
	Console::SetCursorPosition(44, y + 1);
	cout << " ";
	Console::SetCursorPosition(44, y);
	Console::ForegroundColor(Red);
	cout << "l";
	Sleep(105);
	Console::SetCursorPosition(41, y - 1);
	cout << " ";
	Console::SetCursorPosition(41, y);
	Console::ForegroundColor(Red);
	cout << "o";
	for (size_t i = 0; i < 5; i++)
	{
		Console::SetCursorPosition(46, y);
		Console::ForegroundColor(Red);
		cout << '!';
		Sleep(80);
		Console::SetCursorPosition(46, y);
		Console::ForegroundColor(White);
		cout << '!';
		Sleep(80);
	}
}

void Game::Run()
{
	DrawFrame();
	AnimateIntro();
	AskUserWhatTable();
	m_time.reset();
	Show();
	while (b_Run)
	{
		FlushConsoleInputBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
		while (m_time.getElapsedTime() < 60000)
		{
			Console::SetCursorPosition(Console::WindowWidth() / 2 - 1, 1);
			int time = 60 - m_time.getElapsedTime() / 1000;

			if (time > 30)
				Console::ForegroundColor(Green);
			else if (time > 10)
				Console::ForegroundColor(Yellow);
			else
				Console::ForegroundColor(Red);
			cout << time;
			// 1 - get user input
			if (_kbhit())
			{
				char ch = _getch();
				// did the user press a-z?

				if (-32 == ch)
					_getch();
				else if (isalpha(ch))
				{
					if (CheckForLetter(ch, true)) //the bool value is used to color them red/default
					{
						userInput += tolower(ch);
						unsigned int startVertex;
						for (size_t i = 0; i < m_graph.size(); i++)
						{
							if (userInput[0] == m_graph[i].element.character)
							{
								startVertex = i;
								break;
							}
						}
						TraverseAndFind(startVertex, userInput);
						Show();
					}
				}
			}
			if (userInput.size() > 0)
			{
				if (GetAsyncKeyState(VK_BACK))
				{
					CheckForLetter(userInput[userInput.size() - 1], false);
					
					if (userInput.size() > 0)
					{
						userInput.pop_back();
						unsigned int startVertex;
						for (size_t i = 0; i < m_graph.size(); i++)
						{
							if (userInput[0] == m_graph[i].element.character)
							{
								startVertex = i;
								break;
							}
						}
						TraverseAndFind(startVertex, userInput);
						Show();
					}
					Sleep(99);
				}
			}
			// 2 - act on it
			
			if (GetAsyncKeyState(VK_RETURN) & 0x8000 && userInput.size() > 2)
			{
				unsigned int startVertex;
				for (size_t i = 0; i < m_graph.size(); i++)
				{
					if (userInput[0] == m_graph[i].element.character)
					{
						startVertex = i;
						break;
					}
				}
				if (TraverseAndFind(startVertex, userInput))
				{
					if (m_hash->find(userInput) != -1)
					{
						if (!m_tree.find(userInput))
						{
							m_score += factorial(userInput.size());
							m_tree.insert(userInput);
							lastWordScored = userInput;
						}
						userInput.clear();
					}
				}
				else
					userInput.clear();
				ResetCharBools();
				Show();
			}
			if (GetAsyncKeyState(VK_RETURN) & 0x8000)
			{
				ResetCharBools();
				userInput.clear();
				Show();
			}
			if (GetAsyncKeyState(VK_ESCAPE))
				break;
			// 3 - draw the screen
		}
		SaveScores();
		system("cls");
		DrawFrame();
			if (AskToPlayAgain())
			{
				m_tree.clear();
				m_graph.clear();
				m_score = 0;
				AskUserWhatTable();
				m_time.reset();
				userInput.clear();
				FlushConsoleInputBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
				Show();
				continue;
			}
			else 
			{
				b_Run = false;
			}
		
	}
}
bool Game::AskToPlayAgain() const
{
	bool temp = true;
	int width = Console::WindowWidth() / 2 - 10;
	//char[3][4] = { '' }
	Console::SetCursorPosition(width - 5, 3);
	Console::ForegroundColor(DarkCyan);
	cout << "Would you like to play again? ";
	Console::SetCursorPosition(width + 3, 5);
	cout << "Yes";
	Console::SetCursorPosition(width + 14, 5);
	cout << "No";
	Console::SetCursorPosition(width + 3, 6);
	cout << "---";
	while (true)
	{
		Console::SetCursorPosition(width - 3, 9);

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || GetAsyncKeyState('D') & 0x8000)
		{
			Console::SetCursorPosition(width + 3, 6);
			cout << "   ";
			Console::SetCursorPosition(width + 14, 6);
			cout << "--";
			temp = false;

		}
		else if (GetAsyncKeyState(VK_LEFT) & 0x8000 || GetAsyncKeyState('A'))
		{
			Console::SetCursorPosition(width + 14, 6);
			cout << "  ";
			Console::SetCursorPosition(width + 3, 6);
			cout << "---";
			temp = true;
		}

		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
			break;
	}
	return temp;
	Console::ResetForegroundColor();
}

void Game::SaveScores()
{
	system("cls");
	DrawFrame();
	struct Score  //Declare Struct to Sort using function
	{
		string name;
		int score;
		bool operator<(const Score& _otherScore) { return this->score > _otherScore.score; }
	};

	vector<Score> scores;
	fstream ios_;
	ios_.open("HighScores.txt", ios_base::in);

	if (ios_.is_open())
	{
		Score temp;
		while (!ios_.eof()) //Read All the file
		{
			ios_ >> temp.name;
			if (ios_.eof())
				break;
			ios_ >> temp.score;
			scores.push_back(temp);
		}

		ios_.close();
	}
	Score CurrentPlayer;
	CurrentPlayer.name = "You Scored..";
	CurrentPlayer.score = m_score;
	sort(scores.begin(), scores.end()); //Sort
	scores.resize(11);
	scores.push_back(CurrentPlayer);
	sort(scores.begin(), scores.end()); //Sort Again with current player included

	int howlong, y = 8;
	scores.size() < 12 ? howlong = scores.size() : howlong = 12;
	Console::SetCursorPosition(32, 4);
	Console::ForegroundColor(Magenta);
	cout << "Top Scores";
	for (int i = 0; i < howlong; i++) //Print scores, 10 Max
	{
		Console::SetCursorPosition(28, y);
		if (scores[i].name == CurrentPlayer.name)
			Console::ForegroundColor(DarkYellow);
		else
			Console::ForegroundColor(DarkCyan);
		cout << scores[i].name;
		Console::SetCursorPosition(40, y++);
		cout << scores[i].score;
	}

	Console::SetCursorPosition(18, 26);
	cout << "Would you like to save your score? y/n";
	while (true)
	{
		if (GetAsyncKeyState('Y') & 0x8000)
		{
			break;
		}
		else if (GetAsyncKeyState('N') & 0x8000)
		{
			return;
		}
	}
	Console::SetCursorPosition(28, 27);

	cout << "Enter your name: ";
	FlushConsoleInputBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
	string temp;
	do
	{
		cin >> temp;
	} while (temp.size() <= 0);


	ios_.open("HighScores.txt", ios_base::out | ios_base::app);
	if (ios_.is_open())
	{
		ios_ << temp << '\t' << m_score << '\n';
	}
	ios_.close();
}
void Game::AskUserWhatTable()
{
	CharItem CharArr[16];
	string table;
	InitializeTable(table);
	for (size_t i = 0; i < 16; i++)
	{
		CharArr[i] = CharItem(table[i]);
		m_graph.addVertex(CharArr[i]);
	}
	LinkGraph();
}
bool Game::TraverseAndFind(unsigned int& startVertex, string& stringX)
{
	queue<int> indexes;
	vector<int> UsedVertices;
	queue<char> Word;
	queue<int> duplicateIndexes;
	string duplicateString;
	queue<int> DuplicateEdges;
	/*push String parameter into Word Cue*/
	for (size_t i = 0; i < stringX.size(); i++)
	{
		Word.push(stringX[i]);
	}
	/* Checking for Duplicate Starting Points And storing them into A "duplicate" Cue.*/
	for (size_t i = 0; i < m_graph.size(); i++)
	{
		if (stringX[0] == m_graph[i].element.character)
		{
			duplicateIndexes.push(i);
		}
	}
	if (!duplicateIndexes.empty()){duplicateIndexes.pop();} /// --> pop one because that's the one we're starting with
	int * IndexesVisited = new int[m_graph.size()];
	memset(IndexesVisited, -1, m_graph.size() * 4);
	IndexesVisited[startVertex] = 0;
	indexes.push(startVertex);

	do //This Loop is checking for duplicate Edges/Starting Points
	{
		do//This Loop is the main Traverse Loop
		{
			if (indexes.empty())
				break;
			if (Word.empty())
				break;
			int index = indexes.front();
			indexes.pop();
			if (IndexesVisited[index] != -2)
			{
				char compare = Word.front();  
				if (m_graph[index].element.character == compare)
				{  ///<----ending bracket at bottom of function.
					UsedVertices.push_back(index);
					IndexesVisited[index] = -2;
					/*NEED TO DO ALL THIS PROCESS TO CHECK FOR DUPLICATE EDGES AND CREATE ALTERNATE PATHS*/
					/*Loop for the amount of edges this Vertex has, and check if our Character is our Edge's character as well*/
					for (size_t i = 1; i < m_graph[index].edges.size(); i++)
					{
						char a = m_graph[index].element.character;
						char b = m_graph[m_graph[index].edges[i].toVertex].element.character;
						if (a == b) //If Duplicate vertices: Push edge onto duplicate Cue & Reset&Update DuplicateString 
						{
							duplicateString.clear();
							DuplicateEdges.push(m_graph[index].edges[i].toVertex);
							while (!Word.empty()){			        //Really inneficient way of
								duplicateString += Word.front();    //initializing the duplicatestring
								Word.pop();
							}
							for (size_t i = 0; i < duplicateString.size(); i++) // because then i had rePush onto the cue, 
							{
								Word.push(duplicateString[i]);					//from the string.
							}
						}
					}
					Word.pop();
					/*Clear indexes to store new Edges*/
					while (!indexes.empty()) { indexes.pop(); }
					if (m_graph[index].edges.size() > 0)
					{
						for (unsigned int i = 0; i < m_graph[index].edges.size(); i++)
						{
							indexes.push(m_graph[index].edges[i].toVertex);
						}
					}
				}
			}
		} while (true); ///End of our Main Traverse Loop
		/* IF We have duplicate edges, Reset some variables and start Main Traverse Loop again.*/
		if (!DuplicateEdges.empty() && !Word.empty())
		{
			while (!indexes.empty()) { indexes.pop(); } //clear Indexes,
			while (!Word.empty()) { Word.pop(); }      //clear Word cue,
			int temp = UsedVertices[0];
			UsedVertices.clear();
			UsedVertices.push_back(temp);
			indexes.push(DuplicateEdges.front());
			DuplicateEdges.pop();
			for (size_t i = 0; i < duplicateString.size(); i++)
			{
				Word.push(duplicateString[i]);
			}
			continue;
		}
		/*Break Out If We have No duplicates OR if we found the string*/
		if ((duplicateIndexes.empty() || Word.empty()))
			break;
		/* OtherWise Reset some Variables and start Main Traverse Loop again. */
		else
			indexes.push(duplicateIndexes.front());
		duplicateIndexes.pop();
		memset(IndexesVisited, -1, m_graph.size() * 4);
		IndexesVisited[indexes.front()] = 0;
		while (!Word.empty()) { Word.pop(); } //Reinitialize Word To start Main Traverse again
		for (size_t i = 0; i < stringX.size(); i++){ Word.push(stringX[i]); }
		UsedVertices.clear();

	} while (true);
	ResetCharBools();

	for (size_t i = 0; i < UsedVertices.size(); i++)
	{
		m_graph[UsedVertices[i]].element.activated = true;
	}
	delete[] IndexesVisited;
	if (Word.empty() && stringX.size() > 2)
		return true;
	else
		return false;
}

bool Game::CheckForLetter(char L, bool on)
{
	bool toreturn = false;
	for (size_t i = 0; i < m_graph.size(); i++)
	{
		if (m_graph[i].element.character == L)
		{
			if (m_graph[i].element.activated == !on)
			{
				//m_graph[i].element.activated = on;

			}
			toreturn = true;
		}
	}
	return toreturn;
}

void Game::DrawTable() const
{
	int x = 32, y = 3;
	Console::SetCursorPosition(x, y);

	for (int i = 0; i < 16; i++)
	{
		if (m_graph[i].element.activated)
		{
			Console::ForegroundColor(Red);
		}
		else
			Console::ForegroundColor(White);
		cout << (char)toupper(m_graph[i].element.character) << "  ";
		if (i == 3 || i == 7 || i == 11)
			Console::SetCursorPosition(x, ++y);
	}
}

void Game::Show()
{
	int x = Console::WindowWidth(), y = Console::WindowHeight();

	system("cls");

	LockWindowUpdate(GetConsoleWindow());
	Console::CursorVisible(false);
	DrawFrame();
	//Console::SetCursorPosition(x / 2 - 9, 4);
	//cout << "                                            ";
	DrawTable();

	Console::SetCursorPosition(x / 2 - userInput.length() / 2, 8);
	Console::ForegroundColor(White);
	cout << userInput;
	Console::SetCursorPosition(1, 9);
	cout << "Score: " << m_score;
	Console::SetCursorPosition(2, 10);
	m_tree.printInOrder(&lastWordScored);

	LockWindowUpdate(NULL);
}
unsigned int factorial(int x)
{
	if (x == 1)
		return x;
	return x * factorial(x - 1);

}
void Game::LookNice() const
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFOEX info;
	info.cbSize = sizeof(info);
	GetConsoleScreenBufferInfoEx(consoleHandle, &info);
	COORD winSize;
	winSize.X = 75;
	winSize.Y = 30;
	info.dwSize.X = info.dwMaximumWindowSize.X = info.srWindow.Right = winSize.X;
	info.dwSize.Y = info.dwMaximumWindowSize.Y = info.srWindow.Bottom = winSize.Y;
	SetConsoleScreenBufferInfoEx(consoleHandle, &info);
	SetConsoleScreenBufferSize(consoleHandle, winSize);
	SetConsoleTitle(L"Word Finder Game"); // Unicode string
}
void Game::DrawFrame() const
{
	Console::Wrap(false);
	int width = Console::WindowWidth();
	int height = Console::WindowHeight();
	Console::SetCursorPosition(0, 0);
	Console::ForegroundColor(Red);
	for (int i = 0; i < width - 1; i++)
	{
		cout << '\xCD';
	}
	Console::SetCursorPosition(0, height - 1);
	for (int i = 0; i < width - 1; i++)
	{
		cout << '\xCD';
	}
	for (int i = 0; i <= height - 1; i++)
	{
		Console::SetCursorPosition(0, i);
		if (i == 0)
			cout << '\xC9';
		else if (i == height - 1)
			cout << '\xC8';
		else
			cout << '\xBA';
		Console::SetCursorPosition(width - 1, i);
		if (i == 0)
			cout << '\xBB';
		else if (i == height - 1)
			cout << '\xBC' << '\b';
		else
			cout << '\xBA';
	}
	Console::SetCursorPosition(2, 1);
	Console::ResetForegroundColor();
}
void Game::ResetCharBools()
{
	for (size_t i = 0; i < m_graph.size(); i++)
	{
		m_graph[i].element.activated = false;
	}
}

bool Game::CheckForVowels(string& table)
{
	int counter = 0;
	for (size_t i = 0; table[i] != '\0'; i++)
	{
		if (table[i] == 'a' || table[i] == 'e' || table[i] == 'i' ||
			table[i] == 'o' || table[i] == 'u')
		{
			counter++;
		}
	}
	if (counter > 3)
		return true;
	else
		return false;
}
void Game::InitializeTable(string& table)
{
	Console::SetCursorPosition(20, 15);
	Console::ResetForegroundColor();
	cout << "Which Grid would you like to use?";
	Console::SetCursorPosition(19, 16);
	Console::ForegroundColor(DarkCyan);
	cout << "(1) Random Grid";
	Console::ResetForegroundColor();
	cout << " or ";
	Console::ForegroundColor(DarkGreen);
	cout << "(2) Hardcoded Grid";
	Console::CursorVisible(false);

	while (true)
	{
		if (GetAsyncKeyState('2') & 0x8000)
		{
			//table = "arlwitosenstwpkj";
			table = "neoneasdoijelant";
			break;
		}
		else if (GetAsyncKeyState('1') & 0x8000)
		{
			string randomizedTable;;
			do {
				randomizedTable.clear();
				for (size_t i = 0; i < 16; i++)
				{
					randomizedTable += (char)(rand() % 26 + 97);
				}

			} while (!CheckForVowels(randomizedTable));
			table = randomizedTable;
			break;
		}
	}
}
