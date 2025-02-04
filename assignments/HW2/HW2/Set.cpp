//
//  Set.cpp
//  HW2
//
//  Created by Ziying Yu on 2/1/19.
//  Copyright © 2019 Ziying Yu. All rights reserved.
//

#include "Set.h"

Set::Set()
{
    createEmpty();
}

bool Set::insert(const ItemType& value)
{
    // Fail if value already present
    
    Node* p = findFirstAtLeast(value);
    if (p != m_head  &&  p->m_value == value)
        return false;
    
    // Insert new Node preserving ascending order and incrementing m_size
    
    insertBefore(p, value);
    return true;
}

bool Set::erase(const ItemType& value)
{
    // Find the Node with the value, failing if there is none.
    
    Node* p = findFirstAtLeast(value);
    if (p == m_head  ||  p->m_value != value)
        return false;
    
    // Erase the Node, decrementing m_size
    doErase(p);
    return true;
}

bool Set::get(int i, ItemType& value) const
{
    if (i < 0  ||  i >= m_size)
        return false;
    
    // Return the value at position i.  Since the values are stored in
    // ascending, the value at position i will be greater than exactly i
    // items in the set, meeting get's specification.
    
    // If i is closer to the head of the list, go forward to reach that
    // position; otherwise, start from tail and go backward.
    
    Node* p;
    if (i < m_size / 2)  // closer to head
    {
        p = m_head->m_next;
        for (int k = 0; k != i; k++)
            p = p->m_next;
    }
    else  // closer to tail
    {
        p = m_head->m_prev;
        for (int k = m_size-1; k != i; k--)
            p = p->m_prev;
    }
    
    value = p->m_value;
    return true;
}

void Set::swap(Set& other)
{
    // Swap head pointers
    
    Node* p = other.m_head;
    other.m_head = m_head;
    m_head = p;
    
    // Swap sizes
    
    int s = other.m_size;
    other.m_size = m_size;
    m_size = s;
}

Set::~Set()
{
    // Delete all Nodes from first non-dummy up to but not including
    // the dummy
    
    while (m_head->m_next != m_head)
        doErase(m_head->m_next);
    
    // delete the dummy
    
    delete m_head;
}

Set::Set(const Set& other)
{
    createEmpty();
    
    // Copy all non-dummy other Nodes.  (This will set m_size.)
    // Inserting each new node before the dummy node that m_head points to
    // puts the new node at the end of the list.
    
    for (Node* p = other.m_head->m_next; p != other.m_head; p = p->m_next)
        insertBefore(m_head, p->m_value);
}

Set& Set::operator=(const Set& rhs)
{
    if (this != &rhs)
    {
        // Copy and swap idiom
        
        Set temp(rhs);
        swap(temp);
    }
    return *this;
}

void Set::createEmpty()
{
    m_size = 0;
    
    // Create dummy node
    
    m_head = new Node;
    m_head->m_next = m_head;
    m_head->m_prev = m_head;
}

void Set::insertBefore(Node* p, const ItemType& value)
{
    // Create a new node
    
    Node* newp = new Node;
    newp->m_value = value;
    
    // Insert new item before p
    
    newp->m_prev = p->m_prev;
    newp->m_next = p;
    newp->m_prev->m_next = newp;
    newp->m_next->m_prev = newp;
    
    m_size++;
}

void Set::doErase(Node* p)
{
    // Unlink p from the list and destroy it
    
    p->m_prev->m_next = p->m_next;
    p->m_next->m_prev = p->m_prev;
    delete p;
    
    m_size--;
}

Set::Node* Set::findFirstAtLeast(const ItemType& value) const
{
    // Walk through the list looking for a match
    
    Node* p = m_head->m_next;
    for ( ; p != m_head  &&  p->m_value < value; p = p->m_next)
        ;
    return p;
}

