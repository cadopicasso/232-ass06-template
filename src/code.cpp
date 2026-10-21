// ============================================================
// CSCI 232 Assignment 06 – Doubly Linked List vs. std::list
// Student Implementation
// ============================================================

#include "code.hpp"
#include <algorithm>
#include <iostream>

// Uncomment the author block below and fill in your name:

std::string AUTHOR_NAME       = "Caden Johns";
std::string AUTHOR_AUTHORSHIP = "I acknowledge that I have worked on this "
"assignment independently, except where explicitly noted and referenced. "
"Any collaboration or use of external resources has been properly cited. "
"I am fully aware of the consequences of academic dishonesty and agree "
"to abide by the university's academic integrity policy.";

// ============================================================
// PART 1: Class DoubleNode
// ============================================================

/// Constructor: initialize ALL THREE fields with a member initializer list.
/// value <- newValue, prevPtr <- nullptr, nextPtr <- nullptr.
DoubleNode::DoubleNode(NodeValue newValue)
{
    this->value=newValue;
    this->prevPtr=nullptr;
    this->nextPtr=nullptr;
}

/// Const getter: return the stored value.
NodeValue DoubleNode::getValue() const
{
    return NodeValue{value};
}

/// Const getter: return the previous node (or nullptr).
DoubleNode *DoubleNode::getPrev() const
{
    return this->prevPtr;
}

/// Const getter: return the next node (or nullptr).
DoubleNode *DoubleNode::getNext() const
{
    return this->nextPtr;
}

/// Setter: store newPrevPtr in prevPtr.
void DoubleNode::setPrev(DoubleNode *newPrevPtr)
{
    this->prevPtr=newPrevPtr;
}

/// Setter: store newNextPtr in nextPtr.
void DoubleNode::setNext(DoubleNode *newNextPtr)
{
    this->nextPtr=newNextPtr;
}

// ============================================================
// PART 2: Class DoublyLinkedList
// ============================================================

/// Empty list: headPtr = nullptr, tailPtr = nullptr, count = 0.
DoublyLinkedList::DoublyLinkedList()
{
    this->headPtr = nullptr;
    this->tailPtr = nullptr;
    this->count = 0;
}

/// RAII: delete ALL nodes. Save the next pointer BEFORE delete.
DoublyLinkedList::~DoublyLinkedList()
{
    DoubleNode* currentPtr=headPtr;
    DoubleNode* nextPtr;

    //assumes list is constructed correctly, keep an eye on this
    for (size_t i = 0; i < count; i++)
    {
        if (currentPtr==nullptr){
            std::cerr<<"Deconstructor failed"<<std::endl;
        }

        nextPtr=currentPtr->getNext();
        delete currentPtr;
        currentPtr=nextPtr;

        
    }
    
    this->count=0;
    
}

/// Unlink the first node and RETURN it (do not delete it).
/// Fix headPtr, tailPtr, count. Clear the node's own prevPtr and nextPtr.
/// Return nullptr if the list is empty.
DoubleNode *DoublyLinkedList::detachFirst()
{
    DoubleNode* detachedNodePtr=nullptr;
    if (headPtr!=nullptr){
        detachedNodePtr=headPtr;

        headPtr=detachedNodePtr->getNext();

        if (headPtr==nullptr){
            tailPtr==nullptr;
        }

        detachedNodePtr->setNext(nullptr);
        //prev should already be null, is first

        this->count-=1;
    }
    return detachedNodePtr;
}

/// Unlink the last node and RETURN it (do not delete it).
/// Use the tail's prev link. Return nullptr if the list is empty.
DoubleNode *DoublyLinkedList::detachLast()
{
    DoubleNode* detachedNodePtr=nullptr;
    if (headPtr!=nullptr){
        if (headPtr->getNext()==nullptr){
            detachedNodePtr=detachFirst();
        }
        else{
            detachedNodePtr=tailPtr;

            tailPtr=tailPtr->getPrev();

            detachedNodePtr->setPrev(nullptr);

            this->count-=1;
        }
    }
    return detachedNodePtr;
}

/// Find the FIRST node equal to value and unlink it (head, tail, only node
/// or middle node). Return nullptr if not found. Reuse detachFirst/detachLast.
DoubleNode *DoublyLinkedList::detachValue(NodeValue value)
{
    DoubleNode* detachedNodePtr=nullptr;
    DoubleNode* currentCheck=headPtr;
    while(currentCheck!=nullptr && currentCheck->getValue()!=value){
        currentCheck=currentCheck->getNext();
    }

    if (currentCheck!=nullptr){
        

        if (currentCheck==headPtr){
            detachedNodePtr=detachFirst();
        }else if(currentCheck==tailPtr){
            detachedNodePtr=detachLast();
        }else{
            detachedNodePtr=currentCheck;

            detachedNodePtr->getPrev()->setNext(detachedNodePtr->getNext()); //get previous, set its next to detached's next :)

            detachedNodePtr->getNext()->setPrev(detachedNodePtr->getPrev()); //get next, set its next to detached's previous :)

            detachedNodePtr->setPrev(nullptr);

            detachedNodePtr->setNext(nullptr);

            this->count-=1;
        }
    }
    return detachedNodePtr;
}

/// Create a node with new and link it in front. Handle the empty list.
void DoublyLinkedList::pushFrontValue(NodeValue value)
{
    DoubleNode* newNode= new DoubleNode(value);

    if (headPtr!=nullptr){
        headPtr->setPrev(newNode);
        newNode->setNext(headPtr);
    }

    

    headPtr=newNode;
    if (tailPtr==nullptr){
        tailPtr=headPtr;
    }

    count+=1;
}

/// Create a node with new and link it at the end. Handle the empty list.
void DoublyLinkedList::pushBackValue(NodeValue value)
{
    DoubleNode* newNode= new DoubleNode(value);


    if (tailPtr!=nullptr){
        tailPtr->setNext(newNode);
        newNode->setPrev(tailPtr);
    }
    

    tailPtr=newNode;
    if (headPtr==nullptr){
        headPtr=tailPtr;
    }

    count+=1;
}

/// Detach the first node, read its value, delete the node, return the value.
/// Empty list -> std::nullopt.
std::optional<NodeValue> DoublyLinkedList::popFrontValue()
{
    if (headPtr==nullptr){
        std::cerr<<"Empty List"<<std::endl;
        return std::nullopt;
    }else{
        

        DoubleNode* detachedPtr=detachFirst();

        NodeValue returnValue=detachedPtr->getValue();

        delete detachedPtr;

        return returnValue;
    }
    
}

/// Detach the last node, read its value, delete the node, return the value.
/// Empty list -> std::nullopt.
std::optional<NodeValue> DoublyLinkedList::popBackValue()
{
    if (headPtr==nullptr){
        std::cerr<<"Empty List"<<std::endl;
        return std::nullopt;
    }else{
        DoubleNode* detachedPtr=detachLast(); //may need error handling, could be nullptr

        NodeValue returnValue=detachedPtr->getValue();

        delete detachedPtr;

        return returnValue;
    }
}

/// Remove the FIRST node equal to value and free it.
/// Return true if something was removed.
bool DoublyLinkedList::deleteValue(NodeValue value)
{
    bool success=false;

    if (headPtr!=nullptr){
        DoubleNode * detachedNode=detachValue(value);

        if (detachedNode!=nullptr){
            delete detachedNode;
            success=true;
        }
    }
    return success;
}

/// Return true if any node holds value.
bool DoublyLinkedList::containsValue(NodeValue value) const
{
    DoubleNode* currentCheck=headPtr;
    while(currentCheck!=nullptr && currentCheck->getValue()!=value){
        currentCheck=currentCheck->getNext();
    }

    return (currentCheck!=nullptr); //if not iterated through (no value found), currentCheck should be null
}

/// Print values head -> tail with std::visit (each followed by a space,
/// then a newline). Return the number of printed values.
int DoublyLinkedList::printForward() const
{
    DoubleNode* currentNode=headPtr;
    for (int i = 0; i < count; i++)
    {
        std::visit([](auto x) { std::cout << x << " "; },currentNode->getValue());
        currentNode=currentNode->getNext();
    }
    
    return 0;
}

/// Print values tail -> head using prevPtr. Return the number of printed values.
int DoublyLinkedList::printBackward() const
{
    DoubleNode* currentNode=tailPtr;
    for (size_t i = 0; i < count; i++)
    {
        std::visit([](auto x) { std::cout << x << " "; },currentNode->getValue());
        currentNode=currentNode->getPrev();
    }
    return 0;
}

/// Return count.
int DoublyLinkedList::length() const
{
    return count;
}

// ===== BEGIN PART 3 (do not remove this marker) =====
// ============================================================
// PART 3: Class StdDoublyLinkedList
// ============================================================
// Only std::list methods, <algorithm>, iterators and std::visit.
// A loop is allowed ONLY for printing.

/// Which std::list method inserts at the front?
void StdDoublyLinkedList::pushFrontValue(NodeValue value)
{
    data.push_front(value);
}

/// Which std::list method inserts at the back?
void StdDoublyLinkedList::pushBackValue(NodeValue value)
{
    data.push_back(value);
}

/// Read the front element, remove it, return it. Empty -> std::nullopt.
std::optional<NodeValue> StdDoublyLinkedList::popFrontValue()
{
    
    if (data.size()==0){
        return std::nullopt;
    }
    
    NodeValue front=data.front();
    data.pop_front();

    return front;

}

/// Read the back element, remove it, return it. Empty -> std::nullopt.
std::optional<NodeValue> StdDoublyLinkedList::popBackValue()
{
    if (data.size()==0){
        return std::nullopt;
    }
    
    NodeValue front=data.back();
    data.pop_back();

    return front;
}

/// Remove only the FIRST element equal to value. Return true if removed.
bool StdDoublyLinkedList::deleteValue(NodeValue value)
{
    // TODO: implement
    return false;
}

/// Search without writing your own loop.
bool StdDoublyLinkedList::containsValue(NodeValue value) const
{
    // TODO: implement
    return false;
}

/// Print head -> tail (same format as Part 2). Return the number of values.
int StdDoublyLinkedList::printForward() const
{
    // TODO: implement
    return 0;
}

/// Print tail -> head (same format as Part 2). Return the number of values.
int StdDoublyLinkedList::printBackward() const
{
    // TODO: implement
    return 0;
}

/// size() returns size_t, length() returns int.
int StdDoublyLinkedList::length() const
{
    // TODO: implement
    return 0;
}
// ===== END PART 3 (do not remove this marker) =====
