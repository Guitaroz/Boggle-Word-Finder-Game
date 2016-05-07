#pragma once

template<typename Type> class SLLIter;


template<typename Type> class SLList
{

	friend class SLLIter<Type>;

	struct Node
	{
		Type data;
		Node * next;
	};

	Node * m_head;
	unsigned int m_size;



public:

	SLList();
	~SLList();
	SLList<Type>& operator=(const SLList<Type>& that);
	Type& operator[](const unsigned int& index);
	SLList(const SLList<Type>& that);
	void addHead(const Type& v);
	void clear();
	void insert(SLLIter<Type>& index, const Type& v);
	void remove(SLLIter<Type>& index);
	unsigned int size();
	void RecursiveCopy(Node * c);

};

template<typename Type>
Type& SLList<Type>::operator[](const unsigned int &index)
{
	SLLIter<Type> iter(*this);
	iter.begin();
	for (size_t i = 0; i < index; ++iter, ++i);
	return iter.current();
}

/////////////////////////////////////////////////////////////////////////////
// Function : Constructor
// Notes : constructs an empty list
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
SLList<Type>::SLList()
{
	m_head = nullptr;
	m_size = 0;
}

/////////////////////////////////////////////////////////////////////////////
// Function : Destructor
// Notes : Destroys the list
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
SLList<Type>::~SLList()
{
	clear();
}

/////////////////////////////////////////////////////////////////////////////
// Function : Assignment Operator
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
SLList<Type>& SLList<Type>::operator=(const SLList<Type>& that)
{
	
	if (this != &that)
	{
		clear();
		RecursiveCopy(that.m_head);

	}
	return *this;
}
template<typename Type>

void SLList<Type>::RecursiveCopy(Node * c)
{
	if (c == nullptr)
		return;

	RecursiveCopy(c->next);
	addHead(c->data);
}

/////////////////////////////////////////////////////////////////////////////
// Function : Copy Constructor
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
SLList<Type>::SLList(const SLList<Type>& that)
{
	m_head = nullptr;
	m_size = 0;
	RecursiveCopy(that.m_head);
}

/////////////////////////////////////////////////////////////////////////////
// Function : addHead
// Parameters :	v - the item to add to the list
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
void SLList<Type>::addHead(const Type& v)
{
	Node * temp = new Node;
	temp->data = v;
	temp->next = m_head;
	m_head = temp;
	SLList<Type>::m_size++;
}

/////////////////////////////////////////////////////////////////////////////
// Function : clear
// Notes : clears the list, freeing any dynamic memory
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
void SLList<Type>::clear()
{
	Node * temp;

	while (m_head != nullptr)
	{
		temp = m_head;
		m_head = m_head->next;
		delete temp;
	}
	m_size = 0;
}
/////////////////////////////////////////////////////////////////////////////
// Function : insert
// Parameters :	index - an iterator to the location to insert at
//				v - the item to insert
// Notes : do nothing on a bad iterator
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
void SLList<Type>::insert(SLLIter<Type>& index, const Type& v)
{
	if (index.curr == nullptr)
		return;

	Node * temp = new Node;
	temp->data = v;
	temp->next = index.curr;

	if (index.curr == m_head)
	{
		m_head = temp;
		index.prev = m_head;
	}
	else
		index.prev->next = temp;
	index.curr = temp;

	SLList<Type>::m_size++;
}

/////////////////////////////////////////////////////////////////////////////
// Function : remove
// Parameters :	index - an iterator to the location to remove from
// Notes : do nothing on a bad iterator
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
void SLList<Type>::remove(SLLIter<Type>& index)
{
	if (index.curr == nullptr)
		return;

	Node * temp = index.curr->next;
	delete index.curr;	

	if (index.curr == m_head)
	{
		m_head = temp;
		index.prev = m_head;
	}
	else
	 index.prev->next = temp;

	index.curr = temp;
	SLList<Type>::m_size--;
}

/////////////////////////////////////////////////////////////////////////////
// Function : size
// Return : the number of items stored in the linked list.
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
unsigned int SLList<Type>::size()
{
	return m_size;
}


// class SLLIter
template<typename Type> class SLLIter
{
	// the list is the iterator’s friend
	friend class SLList<Type>;

	SLList<Type> * list;
	typename SLList<Type>::Node* prev;
	typename SLList<Type>::Node* curr;

public:
	//Methods
	SLLIter(SLList<Type>& listToIterate);
	void begin();
	bool end();
	SLLIter<Type>& operator++();
	Type& current() const;
};
/////////////////////////////////////////////////////////////////////////////
// Function : Constructor
// Parameters :	listToIterate - the list to iterate
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
SLLIter<Type>::SLLIter(SLList<Type>& listToIterate)
{
	list = &listToIterate;
}

/////////////////////////////////////////////////////////////////////////////
// Function : begin
// Notes : moves the iterator to the head of the list
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
void SLLIter<Type>::begin()
{
	curr = list->m_head;
	prev = list->m_head;
}

/////////////////////////////////////////////////////////////////////////////
// Function : end
// Notes : returns true if we are at the end of the list, false otherwise
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
bool SLLIter<Type>::end()
{
	if (curr == nullptr)
		return true;
	else
		return false;
}

/////////////////////////////////////////////////////////////////////////////
// Function : operator++
// Notes : move the iterator forward one node
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
SLLIter<Type>& SLLIter<Type>::operator++()
{
	if (curr != nullptr)
	{
		prev = curr;
		curr = curr->next;
	}
	return *this;
}

/////////////////////////////////////////////////////////////////////////////
// Function : current
// Notes : returns the item at the current iterator location
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
Type& SLLIter<Type>::current() const
{
	return curr->data;
}


