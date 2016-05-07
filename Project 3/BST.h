#pragma once
#include "MyConsole.h"

template <typename Type>
class BST
{
	struct Node{
		
		Type data; 
		Node * left, *right;
		Node(const Type& _data, Node * _left = NULL, Node * _right = NULL);
	};

	Node * m_root;

	//HELPER FUNCTIONS
	void PrintHelper(Node * root, Type& highlight) const;
	void InsertHelper(Node * _parent, Node * temp);
	void clearHelper(Node* Xnode);
	bool findHelper(Node * Xnode, const Type& v) const;
	bool RemoveHelper(Node ** parent, Node** current, const Type& v);
	void RemoveCase1(Node ** parent, Node ** current);
	void RemoveCase2(Node ** parent, Node ** current);
	void RemoveCase3(Node ** parent, Node ** current);
	void copyHelper(const Node* Xnode);

public:
	BST();
	~BST();
	BST& operator=(const BST& that);
	BST(const BST& that);
	void insert(const Type& v);
	bool findAndRemove(const Type& v);
	bool find(const Type& v) const;
	void clear();
	void printInOrder(Type * highlight = NULL) const;
};
//////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
BST<Type>::Node::Node(const Type& _data, Node* _left, Node* _right)
{
	left = _left;
	right = _right;
	data = _data;
}

/////////////////////////////Constuctor
template <typename Type>
BST<Type>::BST()
{
	m_root = nullptr;
}

////////////////// Function : Destructor
template <typename Type>
BST<Type>::~BST()
{
	clear();
	delete m_root;
}

///////////////////Assignment operator
template <typename Type>
BST<Type>& BST<Type>::operator=(const BST& that)
{
	if (this != &that)
	{
		copyHelper(that.m_root);
	}
	return *this;
}

////////////////////// Copy Constructor
template <typename Type>
BST<Type>::BST(const BST& that)
{
	m_root = NULL;
	copyHelper(that.m_root);
}

////////////////////Pre Order Traverse//Recursion
template <typename Type>
void BST<Type>::copyHelper(const Node* Xnode)
{
	if (Xnode == NULL)
		return;
	insert(Xnode->data);
	copyHelper(Xnode->left);
	copyHelper(Xnode->right);	
}

//////////////////////////Function : Insert
template <typename Type>
void BST<Type>::insert(const Type& v)
{
	Node * temp = new Node(v);
	if (m_root == NULL)
	{
		m_root = temp;
		return;
	}
	else
		InsertHelper(m_root, temp);

}
//////////////////////////////InsertHelper//Recursion
template <typename Type>
void BST<Type>::InsertHelper(Node * parent, Node *temp)
{
	if (temp->data < parent->data)
	{
		if (parent->left == NULL)
		{
			parent->left = temp;
			return;
		}
		else
			InsertHelper(parent->left, temp);
	}
	else if (temp->data > parent->data)
	{
		if (parent->right == NULL)
		{
			parent->right = temp;
			return;
		}
		else
			InsertHelper(parent->right, temp);
	}
}

////////////////////////////// Find And Remove
template <typename Type>
bool BST<Type>::findAndRemove(const Type& v)
{
	if (m_root == NULL)
		return false;
	return RemoveHelper(&m_root, &m_root, v);

}

///////////////////////////////RemoveHelper//Recursion
template <typename Type>
bool BST<Type>::RemoveHelper(Node ** parent, Node** current, const Type& v)
{
	if (*current == NULL)
		return false;

	if (v < (*current)->data) //If value is Less than, send the parent and the parents LEFT
	{
		return RemoveHelper(current, &(*current)->left, v);
	}
	else if (v >(*current)->data)  //If value is Greater than, send the parent and the parents RIGHT
	{
		return RemoveHelper(current, &(*current)->right, v);
	}
	else if (v == (*current)->data)
	{
		if ((*current)->left == NULL && (*current)->right == NULL)		//no child
			RemoveCase1(parent, current);

		else if ((*current)->left != NULL && (*current)->right != NULL)	//2 children
			RemoveCase3(parent, current);

		else
			RemoveCase2(parent, current);							    //1 child

		return true; 
	}
	return false;
}

/////////Case 1 ----------No Children
template <typename Type>
void BST<Type>::RemoveCase1(Node ** parent, Node** current)
{
	if (*current == m_root)    
	{
		delete m_root;
		m_root = NULL;
	}
	else
	{
		if ((*parent)->left == *current)  
		{
			delete (*parent)->left;      //deleting current. setting to Null
			(*parent)->left = NULL;
		}
		else if ((*parent)->right == *current)
		{
			delete (*parent)->right;    //deleting current......
			(*parent)->right = NULL;
		}
	}
}
///////Case2 ----------1 Child
template <typename Type>
void BST<Type>::RemoveCase2(Node ** parent, Node** current)
{
	Node * temp = *current;
	if (*current == m_root)					//If Root..
	{
		if ((*current)->right == NULL)		//delete left
		{
			m_root = (*current)->left;
			delete temp;
		}
		else if ((*current)->left == NULL)	// delete right
		{
			m_root = (*current)->right;
			delete temp;
		}
	}
	else
	{
		if ((*parent)->left == *current)		//To the Left of parent
		{
			if ((*current)->right == NULL)		
			{
				(*parent)->left = (*current)->left;
					delete temp;
			}
			else if ((*current)->left == NULL)	
			{
				(*parent)->left = (*current)->right;
				delete temp;
			}
		}
		else if ((*parent)->right == *current)	//To The Right of Parent
		{
			if ((*current)->right == NULL)		
			{
				(*parent)->right = (*current)->left;
				delete temp;
			}
			else if ((*current)->left == NULL)	
			{
				(*parent)->right = (*current)->right;
				delete temp;
			}
		}
	}
}
///////////Case3 -------2 Children
template <typename Type>
void BST<Type>::RemoveCase3(Node ** parent, Node** current)
{
	Node * temp = *parent;
	Node * min = (*current)->right;
	while (!(min->left == NULL || min->right == NULL))
	{
		temp = min;
		min = min->left;
	}
	(*current)->data = min->data;			

	if (min->left == NULL &&  min->right == NULL)		
		RemoveCase1(&temp, &min);
	else
		RemoveCase2(&temp, &min);
}

////////////////////////FIND
template <typename Type>
bool BST<Type>::find(const Type& v) const
{
	bool found = findHelper(m_root, v);
	return found;
}
///////////////////FindHelper//Recursion
template <typename Type>
bool BST<Type>::findHelper(Node * Xnode, const Type& v) const
{
	if (Xnode == NULL)
		return false;
	if (v == Xnode->data)
		return true;
	if (v < Xnode->data)
	{
		return findHelper(Xnode->left, v);
	}
	else if (v > Xnode->data)
	{
		return findHelper(Xnode->right, v);
	}
	return false;
}

template <typename Type>
void BST<Type>::clear()
{
	clearHelper(m_root);
	m_root = nullptr;
}
/////////////////Post Order Traverse//Recursion
template <typename Type>
void BST<Type>::clearHelper(Node* Xnode)
{
	if (Xnode == NULL)
		return;
	clearHelper(Xnode->left);
	clearHelper(Xnode->right);
	delete Xnode;
}

////////////////PRINT
template <typename Type>
void BST<Type>::printInOrder(Type * highlight) const
{
	Console::SetCursorPosition(2, 10);
	PrintHelper(m_root, *highlight);
	cout << '\n';
}
/////////////In Order Traverse//Recursion
template <typename Type>
void BST<Type>::PrintHelper(Node * Xnode, Type& highlight) const
{
	if (Xnode == NULL)
		return;
	PrintHelper(Xnode->left, highlight);
	Console::SetCursorPosition(Console::CursorLeft(), Console::CursorTop() + 1);
	if (Xnode->data == highlight)
		Console::ForegroundColor(Yellow);
	else
		Console::ForegroundColor(DarkCyan);
	if (Console::CursorTop() == Console::WindowHeight() - 4)
		Console::SetCursorPosition(15, 11);
	else if (Console::CursorLeft() == Console::WindowWidth() - 2)
		Console::SetCursorPosition(30, 11);
	cout << Xnode->data;
	PrintHelper(Xnode->right, highlight);
}