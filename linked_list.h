#pragma once
#include <iostream>

struct NodeLL
{
    int value;
    NodeLL* next;
};

class LinkedList
{
public:
    LinkedList() :
        start(nullptr)
    {

    }
    void insertToEnd(int value)
    {
        if (!start)
        {
            start = new NodeLL;
            start->value = value;
            start->next = nullptr;
            return;
        }

        if (!start->next)
        {
            start->next = new NodeLL;
            start->next->value = value;
            start->next->next = nullptr;
            return;
        }

        NodeLL* current = start;
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
        if (!start)
            return;


        if (start->value == value)
        {
            NodeLL* deleteNode = start;
            start = start->next;

            delete deleteNode;
            deleteNode = nullptr;

            return;
       }

        NodeLL* current = start;
        NodeLL* prev = start;
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

    void reverse()
    {
        if (!start)
            return;

        NodeLL* prevNode = nullptr;
        NodeLL* nextNode = start;
        while (nextNode)
        {
            nextNode = start->next;
            start->next = prevNode;
            prevNode = start;
            start = nextNode;
        }

        start = prevNode;
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
        if (!start)
            return;

        if (!start->next)
        {
            std::cout << "Middle is - " << start->value << std::endl;
            return;
        }

        NodeLL* slowPtr = start;
        NodeLL* fastPtr = start;
        while (fastPtr && fastPtr->next)
        {
            slowPtr = slowPtr->next;
            fastPtr = fastPtr->next->next;
        }
        std::cout << "Middle is - " << slowPtr->value << std::endl;

    }

    bool detectAndRemoveLoop()
    {
        return true;
    }

    void printLL()
    {
        if (!start)
            return;

        NodeLL* current = start;
        while (current)
        {
            std::cout << current->value << " ";
            current = current->next;
        }
        std::cout << "\n";
    }
//private:
    NodeLL* start;
};

