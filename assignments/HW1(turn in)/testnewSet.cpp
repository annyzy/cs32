//
//  testnewSet.cpp
//  HW 1.1
//
//  Created by Ziying Yu on 1/20/19.
//  Copyright © 2019 Ziying Yu. All rights reserved.
//

#include "newSet.h"
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

void test()
{
    
    Set a(250);
    assert(a.empty());
    cout<<"Test 1: Set::Set(const int capacity)" << endl;
    cout<<endl;
    
    Set b;
    assert(b.size()==0);
    cout<<"Test 2: bool Set::empty() const" << endl;
    cout<<endl;
    cout<<"Test 3: int Set::size() const" << endl;
    cout<<endl;
    
    Set c(5);
    ItemType v[6] = { "32","33","1","543","7","70"};
    for (int k = 0; k < 5; k++)
        assert(c.insert(v[k]));
    assert(!c.insert(v[5]));
    cout<<"Test 4:bool Set::insert(const ItemType& value) of part 1: no failures to insert 5 different items into b"<<endl;
    cout<<"Test 4:bool Set::insert(const ItemType& value) of part 2: cannot insert a sixth item into b"<<endl;
    
    Set d(1);
    ItemType x[6] = { "1","1" };
    for (int k = 0; k < 1; k++)
        assert(d.insert(x[k]));
    assert(d.size()==1);
    cout<<"Test 4:bool Set::insert(const ItemType& value) of part 3: cannot insert a item twice into d"<<endl;
    cout<<endl;
    
    assert(!c.erase("30"));
    assert(c.size()==5);
    cout<<"Test 5: bool Set::erase(const ItemType& value) of part 1: !contains(value)"<<endl;
    assert(c.erase("1"));
    assert(c.size()==4);
    cout<<"Test 5: bool Set::erase(const ItemType& value) completely "<<endl;
    cout<<endl;
    
    assert(!c.contains("1"));
    assert(c.contains("7"));
    assert(c.contains("32"));
    assert(c.contains("33"));
    assert(!c.contains("70")); // value 70 is the sixth item in set c which is not inserted;
    assert(c.contains("543"));
    cout<<"Test 6: bool Set::contains(const ItemType& value) const completely "<<endl;
    cout<<endl;
    
    Set e(4);
    string y="21";
    assert( !e.get(0, y));
    assert(e.insert("21"));
    assert(e.insert("12"));
    assert(e.size()==2);
    assert(e.get(1,y));
    
    Set f;
    assert(f.insert(""));
    string z;
    assert(f.get(0,z) && z =="");
    cout<<"Test 7: bool Set::get(int i, ItemType& value) const including empty string"<<endl;
    cout<<endl;
    
    

    d.swap(e);
    assert(e.contains("1"));
    assert(e.size()==1);
    assert(d.size()==2);
    cout<<"Test 8: void Set::swap(Set& other) of part 1: size swap "<<endl;
    
    assert(d.insert("2"));
    assert(d.insert("3"));
    assert(d.contains("2") && d.contains("3") && d.contains("21") && d.contains("12") );
    cout<<"Test 8: void Set::swap(Set& other) of part 2: size swap "<<endl;
    
    assert(e.contains("1"));
    cout<<"Test 8: void Set::swap(Set& other) of part 3: contents swap "<<endl;
    cout<<endl;
    
}

int main()
{
    test();
    cout << "Passed all tests"<< endl;
}
