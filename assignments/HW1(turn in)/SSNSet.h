//
//  SSNSet.hpp
//  HW1
//
//  Created by Ziying Yu on 1/19/19.
//  Copyright © 2019 Ziying Yu. All rights reserved.
//

#ifndef SSNSet_h
#define SSNSet_h

#include "Set.h"

class SSNSet
{
public:
    SSNSet();          // Create an empty SSN set.
    
    bool add(unsigned long ssn);
    // Add an SSN to the SSNSet.  Return true if and only if the SSN
    // was actually added.
    
    int size() const;  // Return the number of SSNs in the SSNSet.
    
    void print() const;
    // Write every SSN in the SSNSet to cout exactly once, one per
    // line.  Write no other text.
    
private:
    Set m_ssnarray;
};

#endif /* SSNSet_h */

