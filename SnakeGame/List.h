#pragma once
#include <iostream>
#include <SFML/System/Vector2.hpp>

//Holds the directions that the snake can travel in
enum class EDirection {
	eNone, eLeft, eRight, eUp, eDown
};

//Doubly linked list, so we need reference to previous and next node
struct Node {
	friend class List;
	Node(sf::Vector2f _position, EDirection _direction, Node* _previousNode, Node* _nextNode) : m_position(_position), m_direction(_direction), m_previousNode(_previousNode), m_nextNode(_nextNode) {}

	bool IsNextNodeAvailable() const { return m_nextNode; }

	sf::Vector2f m_position;
	EDirection m_direction;

	Node* m_previousNode;
	Node* m_nextNode;
};

class List {
public:
	List();
	List(const sf::Vector2f _position, EDirection _direction);
	~List();
	void PopFront();
	void PushFront(const sf::Vector2f _segmentPosition, const EDirection _direction);
	void PushBack(const sf::Vector2f _segmentPosition, const EDirection _direction);
	void PopBack();
	void Clear() const;
	sf::Vector2f Front() const;
	sf::Vector2f Back() const;
	bool IsEmpty() const;
	int Size() const;

	//Returns the front node
	Node* GetHead() const { return m_head; }
	//Returns the back node
	Node* GetTail() const { return m_tail; }

private:
	Node* m_head{ nullptr };
	Node* m_tail{ nullptr };
	int m_size{ 0 };
};
