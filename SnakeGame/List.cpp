#include "List.h"

List::List()
{
	m_head = new Node(sf::Vector2f(0,0), NULL, NULL);
	m_tail = new Node(sf::Vector2f(0, 0), m_head, NULL);
	m_head->m_nextNode = m_tail;
}

List::List(const sf::Vector2f _position)
{
	//Initialise the 'Head' of the linked list to the position
	m_head = new Node(_position, NULL, NULL);
	//create an empty 'tail'
	m_tail = new Node(sf::Vector2f(0, 0), m_head, NULL);
}

List::~List()
{
	//Iterate through and delete each node
}

void List::PushFront(const sf::Vector2f _segmentPosition)
{
	//Allocate a new node
	auto* newNode = new Node(_segmentPosition, NULL, m_head);
	m_head->m_previousNode = newNode;
	//make the new node the head of the list
	m_head = newNode;
}

void List::PushBack(const sf::Vector2f _segmentPosition)
{
}

void List::PopBack()
{
}

sf::Vector2f List::Front() const
{
	return m_head->m_position;
}

bool List::IsEmpty() const
{
	return false;
}

int List::Size() const
{
	return 0;
}


std::ostream& operator<<(std::ostream& os, const List list)
{
	Node* currentNode = list.GetHead();
	os << "TEST:";
	do 
	{
		os << currentNode->m_position.x << " " << currentNode->m_position.y << std::endl;
		currentNode = currentNode->m_nextNode;
	} while (currentNode);
	return os;
}