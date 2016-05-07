#pragma once

#include "SLList.h"

template <typename Type>
class HTable
{
	SLList<Type> * m_list;
	unsigned int(*m_func) (const Type &v);
	unsigned int m_size;
	

public:
	HTable(unsigned int numOfBuckets, unsigned int(*hFunction) (const Type &v));
	~HTable();
	HTable<Type>& operator=(const HTable<Type>& that);
	HTable(const HTable<Type>& that);
	void insert(const Type& v);
	bool findAndRemove(const Type& v);
	void clear();
	int find(const Type& v) const;
	unsigned int GetSize() const { return m_size; };
	unsigned int Listsize(unsigned int i);
	SLList<Type>& operator [](unsigned int index);
	void PrintHashStats(const char* filePath = "hashdata.txt");
};

template <typename Type>
SLList<Type>& HTable<Type>::operator [](unsigned int index)
{
	return m_list[index];
}

template <typename Type>
HTable<Type>::HTable(unsigned int numOfBuckets, unsigned int(*hFunction) (const Type &v))
{
	m_size = numOfBuckets;
	m_list = new SLList<Type>[m_size];
	m_func = hFunction;
}

template <typename Type>
HTable<Type>::~HTable()
{
	delete[] m_list;
}


template <typename Type>
HTable<Type>& HTable<Type>::operator=(const HTable<Type>& that)
{
	if (this != &that)
	{
		clear();
		delete[] m_list;
		m_size = that.m_size;
		m_list = new SLList<Type>[m_size];
		m_func = that.m_func;

		for (size_t i = 0;i < that.GetSize(); i++)
		{
			m_list[i] = that.m_list[i];
		}
	}
	return *this;
}


template <typename Type>
unsigned int HTable<Type>::Listsize(unsigned int i)
{
	return m_list[i].size();
}

template <typename Type>
HTable<Type>::HTable(const HTable<Type>& that)
{
	m_size = that.GetSize();
	m_list = new SLList<Type>[m_size];
	m_func = that.m_func;
	
	for (size_t i = 0; i < that.GetSize(); i++)
	{
		m_list[i] = that.m_list[i]
	}
}

/////////////////////////////////////////////////////////////////////////////
// Function : insert
// Parameters : v - the item to insert into the hash table
/////////////////////////////////////////////////////////////////////////////
template <typename Type>
void HTable<Type>::insert(const Type& v)
{
	size_t i = m_func(v);
	m_list[i].addHead(v);
}

/////////////////////////////////////////////////////////////////////////////
// Function : findAndRemove
// Parameters : v - the item to remove(if it is found)
/////////////////////////////////////////////////////////////////////////////
template <typename Type>
bool HTable<Type>::findAndRemove(const Type& v)
{
	int i = m_func(v);
	SLLIter<Type> iter(m_list[i]);
	iter.begin();
	for (; !iter.end(); ++iter)
	{
		if (iter.current() == v)
		{
			m_list[i].remove(iter);
			return true;
		}
	}
	return false;
	
}
/////////////////////////////////////////////////////////////////////////////
// Function : clear
// Notes : clears the hash table
/////////////////////////////////////////////////////////////////////////////
template <typename Type>
void HTable<Type>::clear()
{
	for (size_t i = 0; i < m_size; i++)
	{
		m_list[i].clear();
	}
}

/////////////////////////////////////////////////////////////////////////////
// Function : find
// Parameters : v - the item to look for
// Return : the bucket we found the item in or -1 if we didn’t find the item.
/////////////////////////////////////////////////////////////////////////////
template <typename Type>
int HTable<Type>::find(const Type& v) const
{
	int i = m_func(v);
	SLLIter<Type> iter(m_list[i]);
	iter.begin();
	for (; !iter.end(); ++iter)
	{
		if (iter.current() == v)
			return i;
	}
	return -1;
}
// the following variable names are used below, match them to your variable names 
//	theTable - this is the array of lists
//	buck - the number of buckets

template <typename Type>
void HTable<Type>::PrintHashStats(const char* filePath = "hashdata.txt")
{
	ofstream outFile(filePath);

	if (outFile.is_open())
	{
		unsigned int empty = 0;
		unsigned int totalCount = 0;
		unsigned int loIndex = 0;
		unsigned int hiIndex = 0;

		for (unsigned int i = 0; i < m_size; ++i)
		{
			totalCount += m_list[i].size();
			outFile << i << " : " << m_list[i].size() << '\n';
			if (m_list[i].size() == 0)
				++empty;

			if (m_list[i].size() < m_list[loIndex].size())
				loIndex = i;
			else if (m_list[i].size() > m_list[hiIndex].size())
				hiIndex = i;
		}

		outFile << '\n' << totalCount << " Total items stored in " << m_size << " m_sizeets\n";
		outFile << '\n' << empty << " m_sizeets are empty\n\n";

		unsigned int Low = m_list[loIndex].size();
		unsigned int range = m_list[hiIndex].size() - Low + 1;

		outFile << "each m_sizeet contains between " << Low << " and " << Low + range - 1 << " items.\n\n";

		unsigned int* arr = new unsigned int[range];
		for (unsigned int j = 0; j < range; ++j)
			arr[j] = 0;

		for (unsigned int k = 0; k < m_size; ++k)
			++arr[m_list[k].size() - Low];

		for (unsigned int p = 0; p < range; ++p)
			outFile << arr[p] << " m_sizeets have " << p + Low << " items\n";

		delete[] arr;
	}
}
