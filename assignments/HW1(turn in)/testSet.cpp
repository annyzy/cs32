//
//  testSet.cpp
//  HW1
//
//  Created by Ziying Yu on 1/17/19.
//  Copyright © 2019 Ziying Yu. All rights reserved.
//

#include "Set.h"
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

void test()
{
    Set s;
    
    assert(s.size()==0);
    cout << "Pass test 1: bool Set::empty() const " << endl;
    cout<<endl;
    
    assert(s.empty());
    cout << "Pass test 2: bool Set::empty() const " << endl;
    cout<<endl;
    
    s.insert("1");
    s.insert("1");
    assert(! (s.size() == 2));
    cout << "Pass test 3: bool Set::empty() const of part 1:contains(value) " << endl;
    
    assert(! (s.size() == DEFAULT_MAX_ITEMS) );
    cout << "Pass test 3: bool Set::empty() const of part 2:size()==DEFAULT_MAX_ITEMS " << endl;
    assert(s.size() == 1);
    cout << "Pass test 3: bool Set::empty() const of part 3:size()==0 " << endl;
    
    s.insert("2");
    s.insert("4");
    s.insert("3");
    assert(s.size() ==4);
    cout << "Pass test 3: bool Set::empty() const completely" << endl;
    cout<<endl;
    
    s.erase("5");
    assert(s.size()==4);
    cout << "Pass test 4: bool Set::erase(const ItemType& value) of part 1:! contains(value) " << endl;
    
    s.erase("4");
    assert(s.size()==3);
    cout << "Pass test 4: bool Set::erase(const ItemType& value) completely" << endl;
    cout<<endl;
    
    assert(s.contains("1") && s.contains("2") && s.contains("3"));
    assert(! (s.contains("4") && s.contains("5")));
    cout << "Pass test 5: bool Set::contains(const ItemType& value) const" << endl;
    cout<<endl;

    ItemType x = "1";
    assert(s.get(0,x) && x=="1");
    ItemType y = "3";
    assert(s.get(2,y) && y=="3");
    
    string v;
    assert(s.get(1, v) && v == "2");
    s.insert("");
    assert(s.get(0, v) && v == "");
    cout << "Pass test 6: bool Set::get(int i, ItemType& value) const including empty string" << endl;
    cout<<endl;
    
    Set ss;
    ss.insert("2");
    ss.insert("1");
    ss.insert("3");
    s.swap(ss);
    assert(s.size()==3 && s.contains("1") && s.contains("2") && s.contains("2"));
    ItemType z;
    assert(s.get(0, z) && z=="1" );
    cout << "Pass test 7: void Set::swap(Set& other)" << endl;
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}

