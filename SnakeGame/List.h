#pragma once
#include <utility>

#include "SFML/System/Vector2.hpp"

/**
 * \brief The directions that the snake can travel in. None, Left, Right, Up, and Down
 */
enum class EDirection {
	eNone, eLeft, eRight, eUp, eDown
};


/**
 * \brief The structure of each element of the Linked List
 */
struct Node {
	friend class List;
	/**
	 * \brief Constructs a Node
	 * \param _data The data to store in the node
	 * \param _previousNode A pointer to the previous node in the Linked List
	 * \param _nextNode A pointer to the next node in the Linked List
	 */
	Node(std::pair<sf::Vector2f, EDirection>& _data, Node* _previousNode, Node* _nextNode) : m_data(_data),
		m_previousNode(_previousNode),
		m_nextNode(_nextNode) {
	}


	/**
	 * \return false if at the end of the Linked List
	 */
	bool IsNextNodeAvailable() const { return m_nextNode; }

	std::pair<sf::Vector2f, EDirection> m_data;

	Node* m_previousNode;
	Node* m_nextNode;
};

/**
 * \brief The List class is a custom doubly-linked list. TODO - make it a template class!
 */
class List {
public:
	/**
	 * \brief Constructs a Linked List object with an empty node
	 */
	List();

	/**
	 * \brief Constructs a Linked List object with parameters
	 * \param _data The data to store in the first node
	 */
	List(std::pair<sf::Vector2f, EDirection>& _data);

	/**
	 * \brief Destroys the Linked List
	 */
	~List();

	/**
	 * \brief Pops the front of the list. TODO - when making a template, make it return the data stored
	 */
	void PopFront();

	/**
	 * \brief Adds data to the front of the list
	 * \param _data The data to store in the front node
	 */
	void PushFront(std::pair<sf::Vector2f, EDirection> _data);

	/**
	 * \brief Adds data to the back of the list
	 * \param _data The data to store in the back node
	 */
	void PushBack(std::pair<sf::Vector2f, EDirection> _data);

	/**
	 * \brief Pops the front of the list. TODO - when making a template, make it return the data stored
	 */
	void PopBack();

	/**
	 * \brief Clears the list by deleting each node
	 */
	void Clear() const;

	/**
	 * \return The front node of the Linked List without popping it
	 */
	Node* Front() const { return m_head; }

	/**
	* \return The back node of the Linked List without popping it
	*/
	Node* Back() const { return m_tail; }
	
	/**
	 * \return true if no nodes are in the Linked List
	 */
	bool IsEmpty() const;
	
	/**
	 * \return the amount of nodes in the Linked List
	 */
	int Size() const;

private:
	/**
	 * \brief The head - or front - of the Linked List
	 */
	Node* m_head{ nullptr };

	/**
	 * \brief The tail - or back - of the Linked List 
	 */
	Node* m_tail{ nullptr };

	/**
	 * \brief The size of the Linked List
	 */
	int m_size{ 0 };
};
