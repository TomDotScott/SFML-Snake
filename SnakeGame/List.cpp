#include "List.h"

List::List()
{
	std::pair<sf::Vector2f, EDirection> null{ sf::Vector2f(0, 0), EDirection::eRight };
	m_head = new Node(null, nullptr, nullptr);
	m_tail = new Node(null, m_head, nullptr);
	m_head->m_nextNode = m_tail;
};

List::List(std::pair<sf::Vector2f, EDirection>& _data)
{
	//Initialise the 'Head' of the linked list to the position
	m_head = new Node(_data, nullptr, nullptr);
	m_size = 1;
	m_tail = m_head;
}


List::~List() {
	Clear();
}

void List::PopFront() {
	Node* newHead = m_head->m_nextNode;
	delete m_head;
	m_head = newHead;
	m_size -= 1;
}

//Pushes an element to the front of the List
void List::PushFront(std::pair<sf::Vector2f, EDirection> _data) {
	//Allocate a new node
	auto* newNode = new Node(_data, nullptr, m_head);
	m_head->m_previousNode = newNode;
	//make the new node the head of the list
	m_head = newNode;
	m_size += 1;
}

//Pushes an element to the back of the list
void List::PushBack(std::pair<sf::Vector2f, EDirection> _data) {
	//Allocate a new node
	auto* newNode = new Node(_data, m_tail, nullptr);
	//make the current tail point to the newly allocated node
	m_tail->m_nextNode = newNode;

	//make the new node the tail of the list
	m_tail = newNode;
	m_size += 1;
}

void List::PopBack() {
	if (m_tail->m_previousNode != nullptr) {
		Node* newTail = m_tail->m_previousNode;
		delete m_tail;
		m_tail = newTail;
		m_size -= 1;
	}
}

//Empty the list
void List::Clear() const {
	//Iterate through and delete each node
	auto* currentNode = m_head;
	for (int i = 0; i < m_size; ++i) {
		auto* nextNode = currentNode->m_nextNode;
		currentNode = nullptr;
		currentNode = nextNode;
		nextNode = nullptr;
	}
}

bool List::IsEmpty() const {
	return m_size == 0 ? true : false;
}

int List::Size() const {
	return m_size;
}