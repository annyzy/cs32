//
//  newSet.cpp
//  HW 1.1
//
//  Created by Ziying Yu on 1/20/19.
//  Copyright © 2019 Ziying Yu. All rights reserved.
//

#include "newSet.h"
#include <iostream>

using namespace std;

Set::Set(const int capacity)
{
    if (capacity <0)
    {
        cout<<" The capcity of the set in invalid" <<endl;
        exit(1);
    }
    m_capacity=capacity;
    m_size=0;
    m_array = new ItemType[m_capacity];
}

Set::Set (const Set &copy)
{
    m_capacity=copy.m_capacity;
    m_size=copy.m_size;
    m_array = new ItemType[m_capacity];
    
    for(int index=0;index<m_size;index++)
    {
        m_array[index] = copy.m_array[index];
    }
}

Set::~Set()
{
    delete [] m_array;
}

Set&Set::operator = (const Set &src)
{
    if( &src == this )
    {
        return *this;
    }
    
    delete [] m_array;
    m_capacity = src.m_capacity;
    m_size = src.m_size;
    m_array = new ItemType[m_capacity];
    for(int index=0;index<m_size;index++)
    {
        m_array[index] = src.m_array[index];
    }
    return *this;
}

bool Set::empty() const
{
    return m_size==0;
}

int Set:: size() const
{
    return m_size;
}

bool Set::insert(const ItemType& value)
{
    if(contains(value))
        return false;
    if(m_size>=m_capacity)
        return false;
    if(m_size==0)
    {
        m_array[size()]=value;
        m_size++;
        return true;
    }
    
    int index;
    for(index=0; index<size();index++)
    {
        if(value<m_array[index])
            break;
    }
    
    for(int index1=size();index1>index;index1--)
    {
        m_array[index1]=m_array[index1-1];
    }
    
    m_array[index]=value;
    m_size++;
    return true;
    
}

bool Set::erase(const ItemType& value)
{
    if (!contains(value))
        return false;
    int index;
    for (index = 0; index < size(); index ++) {
        if (m_array[index] == value) {
            break;
        }
    }
    m_size --;
    for (; index < size(); index ++) {
        m_array[index] = m_array[index+1];
    }
    return true;
}

bool Set::contains(const ItemType& value) const
{
    for(int index=0;index<size();index++)
    {
        if(m_array[index]==value)
            return true;
    }
    
    return false;
}

bool Set::get(int i, ItemType& value) const
{
    if (i < 0  ||  i >= size())
    {
        return false;
    }
    
    value = m_array[i];
    return true;
    
}

void Set::swap(Set& other)
{
    Set temp = *this;
    *this = other;
    other = temp;
}
