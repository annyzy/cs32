//
//  SSNSet.cpp
//  HW1
//
//  Created by Ziying Yu on 1/19/19.
//  Copyright © 2019 Ziying Yu. All rights reserved.
//

#include "Set.h"
#include "SSNSet.h"
#include <iostream>

SSNSet::SSNSet()
{
}

bool SSNSet:: add(unsigned long ssn)
{
    if(m_ssnarray.insert(ssn))
        return true;
    return false;
}

int SSNSet:: size() const
{
    return m_ssnarray.size();
}

void SSNSet::print()const
{
    for(int index=0; index<m_ssnarray.size(); index++)
    {
        unsigned long SSN;
        m_ssnarray.get(index, SSN);
        std::cout<<SSN<<std::endl;
    }
}

