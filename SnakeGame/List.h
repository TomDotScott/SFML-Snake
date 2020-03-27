#pragma once
#include <SFML/System/Vector2.hpp>

//Doubly linked list, so we need reference to previous and next node
struct Node
{
	friend class List;
	Node(sf::Vector2f _position, Node* _previousNode, Node* _nextNode) : m_position(_position), m_previousNode(_previousNode), m_nextNode(_nextNode){}
	sf::Vector2f m_position;
	Node* m_previousNode;
	Node* m_nextNode;
};

class List
{
public:
	List();
	List(const sf::Vector2f _position);
	~List();
	void PushFront(const sf::Vector2f _segmentPosition);
	void PushBack(const sf::Vector2f _segmentPosition);
	void PopBack();
	sf::Vector2f Front() const;
	bool IsEmpty() const;
	int Size() const;
private:
	Node* m_head;
	Node* m_tail;
};

