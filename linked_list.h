#pragma once
#include <iostream>
#include <unordered_set>

struct NodeLL
{
    int value;
    NodeLL* next;
};

class LinkedList
{
public:
    LinkedList() :
        m_start(nullptr)
    {

    }
    void insertToEnd(int value)
    {
        if (!m_start)
        {
            m_start = new NodeLL;
            m_start->value = value;
            m_start->next = nullptr;
            return;
        }

        if (!m_start->next)
        {
            m_start->next = new NodeLL;
            m_start->next->value = value;
            m_start->next->next = nullptr;
            return;
        }

        NodeLL* current = m_start;
        while (current->next)
        {
            current = current->next;
        }
        current->next = new NodeLL;
        current->next->value = value;
        current->next->next = nullptr;

    }

    void deleteNode(int value)
    {
        if (!m_start)
            return;

        if (m_start->value == value)
        {
            NodeLL* deleteNode = m_start;
            m_start = m_start->next;

            delete deleteNode;
            deleteNode = nullptr;

            return;
       }

        NodeLL* current = m_start;
        NodeLL* prev = m_start;
        while (current)
        {
            if (current->value == value)
            {
                prev->next = current->next;

                delete current;
                current = nullptr;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

	void createLoop()
	{
		NodeLL* iterator = m_start;
		while (iterator->next)
		{
			iterator = iterator->next;
		}
		iterator->next = m_start;
	}

	bool detectAndRemoveLoop()
	{
		std::unordered_set<NodeLL*> visitedNodes;
		NodeLL* iterator = m_start;
		NodeLL* prevIt = m_start;
		while (iterator)
		{
			auto isExist = !visitedNodes.insert(iterator).second;
			if (isExist)
			{
				prevIt->next = nullptr;
				return true;
			}
			prevIt = iterator;
			iterator = iterator->next;

		}
		return false;
	}

    void reverse()
    {
        if (!m_start)
            return;

        NodeLL* prevNode = nullptr;
        NodeLL* nextNode = m_start;
        while (nextNode)
        {
            nextNode = m_start->next;
            m_start->next = prevNode;
            prevNode = m_start;
            m_start = nextNode;
        }

        m_start = prevNode;
    }

    void reverseRecursive(NodeLL** start)
    {
        if (*start == nullptr)
            return;
        
        NodeLL* first = *start;
        NodeLL* rest = first->next;

        if (rest == nullptr)
            return;

        reverseRecursive(&rest);
        first->next->next = first;

        first->next = nullptr;
        *start = rest;
    }


    void findMiddle()
    {
        if (!m_start)
            return;

        if (!m_start->next)
        {
            std::cout << "Middle is - " << m_start->value << std::endl;
            return;
        }

        NodeLL* slowPtr = m_start;
        NodeLL* fastPtr = m_start;
        while (fastPtr && fastPtr->next)
        {
            slowPtr = slowPtr->next;
            fastPtr = fastPtr->next->next;
        }
        std::cout << "Middle is - " << slowPtr->value << std::endl;

    }

    void printLL()
    {
        if (!m_start)
            return;

        NodeLL* current = m_start;
        while (current)
        {
            std::cout << current->value << " ";
            current = current->next;
        }
        std::cout << "\n";
    }
//private:
    NodeLL* m_start;
};

