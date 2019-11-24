//
//  Trie.h
//  project4
//
//  Created by Ziying Yu on 3/8/19.
//  Copyright © 2019 Ziying Yu. All rights reserved.
//

#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#include <vector>

using namespace std;

template<typename ValueType>
class Trie
{
public:
    Trie();
    ~Trie();
    void reset();
    void insert(const string& key, const ValueType& value);
    vector<ValueType> find(const string& key, bool exactMatchOnly) const;
    
    // C++11 syntax for preventing copying and assignment
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;
private:
    //struct/class
    //store multiple values in a trie node (ex.each tree node point to a linked list of values, simply store a vector in each Node)
    struct Node
    {
        char label; // the element of children
        vector<ValueType> values; //constructe with no values automatically
        vector<Node*> children;
        
    public:
        void insert(const string& key, const ValueType& value)
        {
            //base case
            if(key.empty())
            {
                values.push_back(value);
                return;
            }
            
            //resursive case
            for (typename vector<Node*>::iterator it = children.begin(); it!=children.end(); it++)
            {
                //found!
                if( (*it)->label == key[0] )
                {
                    //only the node in the bottom level has value
                    (*it)->insert( key.substr(1), value);
                    return;
                }
                
            }
            
            //not find!
            Node *tmp = new Node;
            tmp->label=key[0];
            
            children.push_back(tmp);
            tmp->insert(key.substr(1), value);
        }
        
        vector<ValueType> find(const string& key, bool exactMatchOnly) const
        {
            // if exactMatchOnly is true, then return a vector containing all of the values associated with the exact key string specified
            if(key.empty())
                return values;
            
            for (typename vector<Node*>::const_iterator it = children.begin(); it!=children.end(); it++)
            {
                
                if ( (*it)->label == key[0])
                {
                    // exactMatchOnly = true;
                    return (*it)->helperFind(key.substr(1), exactMatchOnly);
                }
            }
            
            //not find at all
            return vector<ValueType>();
        }
        
        
        //deal with the rest
        vector<ValueType> helperFind(const string& key, bool exactMatchOnly)
        {
            if(key.empty())
                return values;
            
            vector<ValueType> foundResult;
            for (typename vector<Node*>::iterator it = children.begin(); it!=children.end(); it++)
            {
                
                vector<ValueType> found;
                
                
                if ( (*it)->label == key[0])
                {
                    // exactMatchOnly = true;
                    found =(*it)->helperFind(key.substr(1), exactMatchOnly);
                }
                
                else
                {
                    if (exactMatchOnly)
                        found = vector<ValueType>(); // do not record it value;
                    else
                        found =(*it)->helperFind(key.substr(1), true);
                }
                
                foundResult.insert(foundResult.end(), found.begin(), found.end());
            }
            
            return foundResult;
            
        }
            
            //
        
        ~Node()
        {
            for (typename vector<Node*>::iterator it = children.begin(); it!=children.end(); it++)
            {
                if((*it)!=nullptr)
                    delete (*it);
            }
        }
    };
    
    Node* root = nullptr;
};


template<typename ValueType>
Trie<ValueType>::Trie()
{
    root = new Node;
}

template<typename ValueType>
Trie<ValueType>::~Trie()
{
    delete root;
}

template<typename ValueType>
void Trie<ValueType>::reset()
{
    delete root;
    root = new Node;
}

//key: "GATTACA"; value: "42"
template<typename ValueType>
void Trie<ValueType>::insert(const string& key, const ValueType& value)
{
    root->insert(key, value);
}

template<typename ValueType>
//user need it to be true or false, in other worlds, exactMachOnly or not
//return type:vector<ValueType>, which is values in my case
vector<ValueType> Trie<ValueType>::find(const string& key, bool exactMatchOnly) const
{
    return root->find(key, exactMatchOnly);
}








//using Trie class template to define a variable:
//                 Trie<int> trie

#endif // TRIE_INCLUDED
