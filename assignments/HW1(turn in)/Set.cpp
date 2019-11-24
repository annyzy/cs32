//
//  Set.cpp
//  HW1
//
//  Created by Ziying Yu on 1/17/19.
//  Copyright © 2019 Ziying Yu. All rights reserved.
//

#include "Set.h"

Set::Set():m_size(0)
{
    
}

bool Set::empty() const
{
    if(m_size==0)
        return true;
    else
        return false;
}

int Set::size() const
{
    return m_size;
}

bool Set::insert(const ItemType& value)
{
    if(contains(value))
        return false;
    if(size()==DEFAULT_MAX_ITEMS)
        return false;
  
    if(size()==0)
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
    if (! contains(value))
        return false;
    int index;
    for (index = 0; index < size(); index ++)
    {
        if (m_array[index] == value)
        {
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
    int temp_size;
    ItemType temp;
    
    //swap contents
    for (int index = 0; index < DEFAULT_MAX_ITEMS; index++)
    {
        temp = m_array[index];
        m_array[index] = other.m_array[index];
        other.m_array[index] = temp;
    }
    
    //swap size;
    temp_size = m_size;
    m_size = other.m_size;
    other.m_size = temp_size;
    
}


