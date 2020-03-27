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
	m_size = 1;
	m_tail = m_head;
}

List::~List()
{
	Clear();
}

void List::PopFront()
{
	Node* newHead = m_head->m_nextNode;
	delete m_head;
	m_head = newHead;
	m_size -= 1;
}

//Pushes an element to the front of the List
void List::PushFront(const sf::Vector2f _segmentPosition)
{
	//Allocate a new node
	auto* newNode = new Node(_segmentPosition, NULL, m_head);
	m_head->m_previousNode = newNode;
	//make the new node the head of the list
	m_head = newNode;
	m_size += 1;
}

//Pushes an element to the back of the list
void List::PushBack(const sf::Vector2f _segmentPosition)
{
	//Allocate a new node
	auto* newNode = new Node(_segmentPosition, m_tail, NULL);
	//make the current tail point to the newly allocated node
	m_tail->m_nextNode = newNode;

	//make the new node the tail of the list
	m_tail = newNode;
	m_size += 1;
}

void List::PopBack()
{
	Node* newTail = m_tail->m_previousNode;
	delete m_tail;
	m_tail = newTail;
	m_size -= 1;
}

//Empty the list
void List::Clear() const
{
	//Iterate through and delete each node
	auto* currentNode = m_head;
	for(int i = 0; i < m_size; ++i)
	{
		auto* nextNode = currentNode->m_nextNode;
		currentNode = nullptr;
		currentNode = nextNode;
		nextNode = nullptr;
	}
}

sf::Vector2f List::Front() const
{
	return m_head->m_position;
}

sf::Vector2f List::Back() const
{
	return m_tail->m_position;
}

bool List::IsEmpty() const
{
	return m_size == 0 ? true : false;
}

int List::Size() const
{
	return m_size;
}


std::ostream& operator<<(std::ostream& _os, const List _list)
{
	Node* currentNode = _list.GetHead();
	while (currentNode)
	{
		if (currentNode->m_previousNode) {
			_os << "THE PREVIOUS NODE: " << currentNode->m_previousNode->m_position.x << " " << currentNode->m_previousNode->m_position.y << std::endl;
		}
		_os << "THIS NODE: " << currentNode->m_position.x << " " << currentNode->m_position.y << std::endl;
		if (currentNode->m_nextNode) {
			_os << "THE NEXT NODE: " << currentNode->m_nextNode->m_position.x << " " << currentNode->m_nextNode->m_position.y << std::endl;
		}
		currentNode = currentNode->m_nextNode;
		_os << std::endl << std::endl << std::endl;
	}
	return _os;
}