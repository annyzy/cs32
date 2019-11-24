//
//  testSSNSet.cpp
//  HW1
//
//  Created by Ziying Yu on 1/19/19.
//  Copyright © 2019 Ziying Yu. All rights reserved.
//

#include "SSNSet.h"
#include <iostream>
#include <cassert>

using namespace std;

void test()
{
    SSNSet y;
    assert(y.size() == 0);
    cout<<"Test 1:SSNSet::SSNSet()"<<endl;
    cout<< endl;
    
    y.add(123456789);
    y.add(123456789);
    y.add(987654321);
    assert(! (y.size() == 3));
    cout<<"Test 2:bool SSNSet:: add(unsigned long ssn)"<<endl;
    cout<< endl;
    
    assert(y.size()==2);
    cout<<"Test 3:int SSNSet:: size() const"<<endl;
    cout<<endl;
    
    y.print();
    cout<<endl;
    y.add(132456789);
    y.print();
    cout<<"Test 3:bool SSNSet:: add(unsigned long ssn)"<<endl;
    cout<<endl;
}

int main()
{
    test();
    cout << "All tests passed." << endl;
}


