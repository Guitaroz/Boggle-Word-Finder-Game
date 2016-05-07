#pragma once

template<typename Type>
class DynArray
{
	Type * m_pointer;
	unsigned int m_size;
	unsigned int m_capacity;

public:
	DynArray();
	DynArray(const DynArray<Type>& that);
	~DynArray();
	DynArray<Type>& operator=(const DynArray<Type>& that);
	Type& operator[](const unsigned int index);
	const Type& operator[](const unsigned int index) const;
	unsigned int size() const { return m_size; }
	void DecreaseSize(); // TEMPORARY while i make the Remove function.
	unsigned int capacity() const { return m_capacity; }
	void clear();
	void append(const Type& item);
	void reserve(const unsigned int & newCap = 0);


};


// Function :	Constructor
template<typename Type>
DynArray<Type>::DynArray()
{
	m_size = 0;
	m_capacity = 0;
	m_pointer = new Type[m_capacity];
}

// Function :	Destructor
// Notes : cleans up any dynamic memory
template<typename Type>
DynArray<Type>::~DynArray()
{
	delete[] m_pointer;
}

template<typename Type>
void DynArray<Type>::DecreaseSize()
{
	m_size--;
}

// Function :	Copy Constructor
template<typename Type>
DynArray<Type>::DynArray(const DynArray<Type>& that)
{
	m_size = that.m_size;
	m_capacity = that.m_capacity;
	m_pointer = new Type[m_capacity];
	for (size_t i = 0; i < m_size; i++)
	{
		m_pointer[i] = that.m_pointer[i];
	}
}

// Function :	Assignment Operator
template<typename Type>
DynArray<Type>& DynArray<Type>::operator=(const DynArray<Type>& that)
{
	if (this != &that)
	{
		m_size = that.m_size;
		m_capacity = that.m_capacity;
		delete[] m_pointer;
		m_pointer = new Type[m_capacity];
		for (size_t i = 0; i < m_size; i++)
		{
			m_pointer[i] = that.m_pointer[i];
		}
	}
	return *this;
}

template<typename Type>
Type& DynArray<Type>::operator[](const unsigned int index)
{
	return m_pointer[index];
}

template<typename Type>
const Type& DynArray<Type>::operator[](const unsigned int index) const
{
	return m_pointer[index];
}


template<typename Type>
void DynArray<Type>::clear()
{
	m_size = 0;
	m_capacity = 0;
	delete[] m_pointer;
	m_pointer = new Type[m_capacity];
}

template<typename Type>
void DynArray<Type>::append(const Type& item)
{
	if (m_size == m_capacity)
		reserve();
	
	m_pointer[m_size] = item;
	m_size++;
}


template<typename Type>
void DynArray<Type>::reserve(const unsigned int & newCap = 0)
{
	if (newCap == 0)
	{
		if (m_capacity == 0)
		{
			m_capacity = 1;
		}
		else
		{
			m_capacity = m_capacity * 2;
		}
		Type * temp = new Type[m_capacity];
		for (size_t i = 0; i < m_size; i++)
		{
			temp[i] = m_pointer[i];
		}
		delete[] m_pointer;
		m_pointer = temp;
		return;
	}
	else
	{
		if (newCap <= m_capacity)
			return;

		m_capacity = newCap;
		Type * temp = new Type[m_capacity];
		for (size_t i = 0; i < m_size; i++)
		{
			temp[i] = m_pointer[i];
		}
		delete[] m_pointer;
		m_pointer = temp;
		return;
	}
}