/*****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#include <iostream>
#include "Exception.h"

template <typename Type>
class Double_sentinel_list {
	public:
		class Double_node {
			public:
				Double_node( Type const & = Type(), Double_node * = nullptr, Double_node * = nullptr );

				Type value() const;
				Double_node *previous() const;
				Double_node *next() const;

				Type         node_value;
				Double_node *previous_node;
				Double_node *next_node;
				Type GetVariableType() const;
		};

		Double_sentinel_list();
		Double_sentinel_list( Double_sentinel_list const & );
		Double_sentinel_list( Double_sentinel_list && );
		~Double_sentinel_list();

		// Accessors

		int size() const;
		bool empty() const;

		Type front() const;
		Type back() const;

		Double_node *begin() const;
		Double_node *end() const;
		Double_node *rbegin() const;
		Double_node *rend() const;

		Double_node *find( Type const & ) const;
		int count( Type const & ) const;

		// Mutators

		void swap( Double_sentinel_list & );
		Double_sentinel_list &operator=( Double_sentinel_list );
		Double_sentinel_list &operator=( Double_sentinel_list && );

		void push_front( Type const & );
		void push_back( Type const & );

		void pop_front();
		void pop_back();

		int erase( Type const & );

	private:
		Double_node *list_head;
		Double_node *list_tail;
		int list_size;

		// List any additional private member functions you author here
	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Double_sentinel_list<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list() :
	// This is the constructor for the sentinals

	list_head( new Double_node() ),
	list_tail( new Double_node() ),

list_size( 0 )
{
	list_head->next_node = list_tail;
	list_head->previous_node = nullptr;
	list_head->node_value = 0;

	list_tail->previous_node = list_head;
	list_tail->next_node = nullptr;
	list_tail->node_value = 0;

	// Enter your implementation hereType value() const;
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ):
// Updated the initialization list here
list_head(new Double_node()),
list_tail(new Double_node()),
list_size( 0 )
{
	// Initialize Sentinal
	list_head->next_node = list_tail;
	list_head->previous_node = nullptr;
	list_head->node_value = 0;
	list_tail->previous_node = list_head;
	list_tail->next_node = nullptr;
	list_tail->node_value = 0;

	// Create a new pointer for the Original list
	Double_node *tempnode = new Double_node();
	tempnode = list.list_tail;

	this->list_size = list.size();
	for (int i = list_size; i > 0; i--)
	{
		// Get the last node in the original list (First in, last out) 
		tempnode = tempnode->previous_node;

		// Create a new node for the new List
		Double_node *newnode = new Double_node();

		// Assign the new node the correct value
		newnode->node_value = tempnode->node_value;

		newnode->previous_node = list_head;
		newnode->next_node = list_head->next_node;
		list_head->next_node = newnode;
		newnode->next_node->previous_node = newnode;
	}
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> &&list ):
// Updated the initialization list here
list_head( list.list_head),
list_tail( list.list_tail),
list_size( list.list_size)
{
	list.list_head = nullptr;
	list.list_tail = nullptr;

	// Enter your implementation here
}

template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
	// This is the Deconstrutor
	for (; list_size != 0;)
	{
		pop_front();
	}
	delete list_head;
	delete list_tail;
}

template <typename Type>
int Double_sentinel_list<Type>::size() const {
	// Return the list of the list
	return list_size;
}

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
	// Return true if there is something in the list, otherwise return false

	if (list_size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <typename Type>
Type Double_sentinel_list<Type>::front() const {
	// Return the value of the next node
	// If the next node has no value (Sentinals)
	// Then throw underflow()

	//list_head->next_node == nullptr
	if (list_size == 0)
	{
		throw underflow();
	}
	else
	{
		return list_head->next_node->node_value;
	}
}

template <typename Type>
Type Double_sentinel_list<Type>::back() const {
	// Return the value of the previous node
	// If the previous node has no value (Sentinals)
	// Then throw underflow()

	//list_tail->previous_node == NULL
	if (list_size == 0)
	{
		throw underflow();
	}
	else
	{
		return list_tail->previous_node->value();
	}
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::begin() const {
	// Return the First Node in the List
	return list_head->next_node;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::end() const {
	// Return the list_tail
	return list_tail;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rbegin() const {
	// Return the last Node in the List
	return list_tail->previous_node;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rend() const {
	// Return the List_head
	return list_head;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::find( Type const &obj ) const {
	// Create a pointer and have it pointing to the beginning of the linked list
	Double_node *tempnode;
	tempnode = list_head;

	// Creates a while loop to search through all nodes
	while(tempnode != list_tail)
	{
		// If correct Value is found
		if (tempnode->node_value == obj)
		{
			return tempnode;
		}
		else
		{
			// Continue to next node
			tempnode = tempnode->next_node;
		}
	}
	return end();
}

template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {
	// Create a pointer and have it pointing to the beginning of the linked list
	Double_node *tempnode = list_head->next_node;
	int counter = 0;

	// Creates a while loop to search through all nodes
	while (tempnode != list_tail)
	{
		// If correct Value is found
		if ((tempnode->node_value) == obj)
		{
			counter = counter +1;
		}
		// Continue to next node
		tempnode = tempnode->next_node;	
	}
	
	return counter;
}

template <typename Type>
void Double_sentinel_list<Type>::swap( Double_sentinel_list<Type> &list ) {
	// This is done for you
	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}

template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> &&rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}

template <typename Type>
void Double_sentinel_list<Type>::push_front( Type const &obj ) {
	// Enter your implementation here

	Double_node *newnode = new Double_node();

	newnode->node_value = obj;
	newnode->previous_node = list_head;
	newnode->next_node = list_head->next_node;

	list_head->next_node = newnode;
	newnode->next_node->previous_node = newnode;

	list_size++;
}

template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {
	// Enter your implementation here

	Double_node *newnode = new Double_node();

	newnode->node_value = obj;
	newnode->next_node = list_tail;
	newnode->previous_node = list_tail->previous_node;

	list_tail->previous_node->next_node = newnode;
	list_tail->previous_node = newnode;

	list_size++;
}

template <typename Type>
void Double_sentinel_list<Type>::pop_front() {
	// If there are 2 or more nodes
	if (list_size >= 2)
	{
		Double_node *temp = nullptr;
		temp = list_head->next_node;
		list_head->next_node = temp->next_node;
		delete temp;
		list_head->next_node->previous_node = list_head;
		list_size--;
	}
	//If there is only one node left, you have to connect the sentinals which requires special/unique algorithm
	else if (list_size == 1)
	{
		Double_node *temp = nullptr;
		temp = list_head->next_node;
		delete temp;
		list_tail->previous_node = list_head;
		list_head->next_node = list_tail;
		list_size--;
	}
	else if (list_size == 0)
	{
		throw underflow();
	}
	// If list_size = 0 then do nothing (this is not suppose to delete sentinals)
	
}

template <typename Type>
void Double_sentinel_list<Type>::pop_back() {
	// If there are 2 or more nodes
	if (list_size >= 2)
	{
		Double_node *temp = nullptr;
		temp = list_tail->previous_node;
		list_tail->previous_node = temp->previous_node;
		delete temp;
		list_tail->previous_node->next_node = list_tail;
		list_size--;
	}
	//If there is only one node left, you have to connect the sentinals which requires special/unique algorithm
	else if (list_size == 1)
	{
		Double_node *temp = nullptr;
		temp = list_tail->previous_node;
		delete temp;
		list_tail->previous_node = list_head;
		list_head->next_node = list_tail;
		list_size--;
	}
	else if (list_size == 0)
	{
		throw underflow();
	}
	// If list_size = 0 then do nothing (this is not suppose to delete sentinals)
}


template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {
	// Enter your implementation here
	
	Double_node *temp = nullptr;
	temp = list_head->next_node;
	Double_node *temp2 = nullptr;
	Type Obj = obj;
	int i;
	int counter = 0;

	// Only look at the nodes with values (not the sentinals)
	for(i = list_size; i >= 1; i--)
	{
		
			// If value is the same
			if (temp->node_value == Obj)
			{
				// Redirect pointers 1away from temp
				temp->next_node->previous_node = temp->previous_node;
				temp->previous_node->next_node = temp->next_node;
				// Move forward to the next node and then delete temp
				temp2 = temp->next_node;
				delete temp;
				temp = temp2;
				list_size--;
				counter++;
			}
			else
			{
				// Move forward to next node
				temp2 = temp->next_node;
				temp = temp2;
			}
		
	}
	return counter;
}

template <typename Type>
Double_sentinel_list<Type>::Double_node::Double_node(
	Type const &nv,
	typename Double_sentinel_list<Type>::Double_node *pn,
	typename Double_sentinel_list<Type>::Double_node *nn ):
// Updated the initialization list here
node_value( Type() ), // This assigns 'node_value' the default value of Type
previous_node( nullptr ),
next_node( nullptr )
{
	// Enter your implementation here
}

template <typename Type>
Type Double_sentinel_list<Type>::Double_node::value() const {
	// This returns the Value of the Node
	return node_value; 
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::previous() const {
	// Enter your implementation here
	return previous_node;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::next() const {
	// Enter your implementation here
	return next_node;
}

/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// If you author any additional private member functions, include them here

/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Double_sentinel_list<T> const &list ) {
	out << "head";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.rend(); ptr != nullptr; ptr = ptr->next() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0" << std::endl << "tail";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.end(); ptr != nullptr; ptr = ptr->previous() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0";

	return out;
}

#endif
