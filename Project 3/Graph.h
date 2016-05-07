#pragma once
#include "SLList.h"
#include "DynArray.h"
#include <queue>
using namespace std;

template<typename Type>
class Graph
{
public:

	struct Edge
	{
		Edge();
		unsigned int toVertex; //represent the index connects to to form an edge
	};

	struct Vertex
	{
		Type element;  //data
		SLList<Edge> edges;
		Vertex();
		Vertex(const Type& x);
		void addEdge(const unsigned int& toVertex);
	};

	unsigned int addVertex(const Type& value);
	Vertex& operator[](const unsigned int& index);
	const Vertex& operator[](const unsigned int& index) const;
	unsigned int size() const;
	void clear();
	bool CompareBreadthFirst(unsigned int& startVertex, string& str);
	void printBreadthFirst(const unsigned int& startVertex);

private:
	DynArray<Vertex> m_Vertices;
	void CompareHelper(queue<int>& cue, int * VisitedIndexes, queue<char>& str);
	void PrintHelper(queue<int>& indexes, int * VisitedIndexes);

};

template<typename Type>
unsigned int Graph<Type>::addVertex(const Type& value)
{
	Vertex temp(value);
	m_Vertices.append(temp);
	return m_Vertices.size() - 1;
}

template <typename Type>
Graph<Type>::Edge::Edge()
{}

template <typename Type>
Graph<Type>::Vertex::Vertex()
{}

template <typename Type>
Graph<Type>::Vertex::Vertex(const Type& x)
{
	element = x;
}

template <typename Type>
void Graph<Type>::Vertex::addEdge(const unsigned int& setVertex)
{
	Edge temp; temp.toVertex = setVertex;
	edges.addHead(temp);
}

template<typename Type>
typename Graph<Type>::Vertex& Graph<Type>::operator[](const unsigned int& index)
{
	return m_Vertices.operator[](index);
}
template<typename Type>
const typename Graph<Type>::Vertex& Graph<Type>::operator[](const unsigned int& index) const
{
	return m_Vertices.operator[](index);
}


template<typename Type>
unsigned int Graph<Type>::size() const
{
	return m_Vertices.size();
}

template<typename Type>
void Graph<Type>::clear()
{
	m_Vertices.clear();
}

template <typename Type>
void Graph<Type>::CompareHelper(queue<int>& indexes, int * VisitedIndexes, queue<char>& str)
{
	if (indexes.empty())		//EXIT CONDITION
		return;
	if (str.empty())
		return;
	int index = indexes.front();// + 1;
	indexes.pop();					//Dequeue
	if (VisitedIndexes[index] != -2)
	{
		//////////////DO FUNCTIONS...STUFF...ETC HERE../////////////////////////
		//cout << m_Vertices[index].element << " : " << VisitedIndexes[index] << '\n'; //PRINT
		char compare = str.front();

		if (m_Vertices[index].element.character == compare)
		{  //ending bracket at bottom of function.
			str.pop();
			VisitedIndexes[index] = -2;
			for (size_t erase = 0; erase < indexes.size(); erase++) {indexes.pop();}

			////////////////////////////////////////////////////////////////////////
			if (m_Vertices[index].edges.size() > 0)
			{
				SLLIter<Edge> iter(m_Vertices[index].edges);
				iter.begin();
				for (; !iter.end(); ++iter)
				{
					//if (VisitedIndexes[iter.current().toVertex] == -1) //if we have not visited this index yet

					indexes.push(iter.current().toVertex);
					//VisitedIndexes[iter.current().toVertex] = VisitedIndexes[index] + 1;

				}
			}
		}
	}
	CompareHelper(indexes, VisitedIndexes, str);

}

template<typename Type>
bool Graph<Type>::CompareBreadthFirst(unsigned int& startVertex, string& str)
{
	queue<int> indexes;
	//////////ADD WHATEVER ELSE HERE////////////
	queue<char> Word;
	for (size_t i = 0; i < str.size(); i++)
	{
		Word.push(str[i]);
	}

	//////////////////////////////////////////
	int * IndexesVisited = new int[m_Vertices.size()];
	memset(IndexesVisited, -1, m_Vertices.size() * 4);
	IndexesVisited[startVertex] = 0;
	indexes.push(startVertex);
	CompareHelper(indexes, IndexesVisited, Word);
	delete[] IndexesVisited;
	if (Word.empty())
		return true;
	else
		return false;
}
template <typename Type>
void Graph<Type>::PrintHelper(queue<int>& indexes, int * VisitedIndexes)
{
	if (indexes.empty())		//EXIT CONDITION
		return;
	int index = indexes.front();// + 1;
	cout << m_Vertices[index].element.character << " : " << VisitedIndexes[index] << '\n'; //PRINT
	indexes.pop();					//Dequeue
	if (m_Vertices[index].edges.size() > 0)
	{
		SLLIter<Edge> iter(m_Vertices[index].edges);
		iter.begin();
		for (; !iter.end(); ++iter)
		{
			if (VisitedIndexes[iter.current().toVertex] == -1) //if we have not visited this index yet
			{
				indexes.push(iter.current().toVertex);
				VisitedIndexes[iter.current().toVertex] = VisitedIndexes[index] + 1;
			}
		}
	}
	PrintHelper(indexes, VisitedIndexes);
}

template<typename Type>
void Graph<Type>::printBreadthFirst(const unsigned int& startVertex)
{
	queue<int> indexes;
	int * IndexesVisited = new int[m_Vertices.size()];
	memset(IndexesVisited, -1, m_Vertices.size() * 4);
	IndexesVisited[startVertex] = 0;
	indexes.push(startVertex);
	PrintHelper(indexes, IndexesVisited);
	delete[] IndexesVisited;
}