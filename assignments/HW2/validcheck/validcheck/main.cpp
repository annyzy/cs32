//
//  main.cpp
//  validcheck
//
//  Created by Ziying Yu on 2/2/19.
//  Copyright © 2019 Ziying Yu. All rights reserved.
//

#include <iostream>
#include <stack>
#include <cctype>
#include <cassert>
#include <string>

#include "Set.h"

using namespace std;

int priority(char op)
{
    if(op=='!')
        return 3;
    else if(op=='&')
        return 2;
    else if(op=='|')
        return 1;
    else
        return 0;
}

int checkValid(string infix)
{
    string infix_cleaned = "";
    for (size_t i = 0; i < infix.size(); i++) {
        char ch = infix[i];
        if (ch != ' ')
            infix_cleaned += ch;
    }
    
    // check if it is an empty string
    if (infix_cleaned.size() == 0)
        return 2;
    
    // check if it contains invalid characters
    for(size_t i = 0; i < infix_cleaned.size(); i++) {
        char ch = infix_cleaned[i];
        if (! islower(ch) && ch != '|' && ch != '&' && ch != '!' && ch != '(' && ch != ')')
            return 3;
    }
    
    // check if it contains empty paratheses
    if (infix_cleaned.find("()") != string::npos)
        return 4;
    
    // check if patheses matches
    int parenthesesCounter = 0;
    for(size_t i = 0; i < infix_cleaned.size(); i++) {
        char ch = infix_cleaned[i];
        if (ch == '(')
            parenthesesCounter += 1;
        else if (ch == ')')
            parenthesesCounter -= 1;
        if (parenthesesCounter < 0)
            return 5;
    }
    if (parenthesesCounter != 0)
        return 6;
    
    // check if an operator is at the end of the infix_cleaned expression
    char last = infix_cleaned[infix_cleaned.size()];
    if (last == '!' || last == '&' || last == '|')
        return 7;
    
    // check if an operator is at the beginning of the infix_cleaned expression
    char first = infix_cleaned[0];
    if (first == '&' || first == '|')
        return 8;
    
    // check if ! is followed by an operand
    for(size_t i = 0; i < infix_cleaned.size(); i++) {
        char ch = infix_cleaned[i];
        char next = infix_cleaned[i+1];
        if (ch == '!') {
            if (! islower(next) && next != '(' && next != '!')
                return 9;
        }
    }
    
    // check if & and | are preceded and followed by an operand
    for(size_t i = 0; i < infix_cleaned.size(); i++) {
        char prev = infix_cleaned[i-1];
        char ch = infix_cleaned[i];
        char next = infix_cleaned[i+1];
        if (ch == '&' || ch == '|') {
            if (! (islower(prev) || prev == ')'))
                return 10;
            if (! (islower(next) || next == '(' || next == '!'))
                return 11;
        }
    }
    
    // check if an operand is followed by an operand
    for(size_t i = 0; i < infix_cleaned.size() - 1; i++) {
        char ch = infix_cleaned[i];
        char next = infix_cleaned[i+1];
        // if ch is an operand
        if (islower(ch) || ch == ')') {
            if (islower(next) || next == '(' || next == '!')
                return 12;
        }
    }
    
    return 0;
}

int evaluate(string infix, string &result)
{
   if(checkValid(infix) != 0)
      return 1;
    
    string postfix = "";
    stack <char> operatorStack;
    
    for(int i=0; i<infix.size();i++)
    {
        char ch=infix[i];
        switch (ch)
        {
            case 'a' ... 'z':
                postfix += ch;
                break;
            case '(':
                operatorStack.push(ch);
                break;
            case ')':
                while (operatorStack.top()!='(')
                {
                    postfix+=operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.pop();
                break;
            case '!':
            case '&':
            case '|':
                while(!operatorStack.empty() && operatorStack.top() !='(' && priority(ch) <= priority(operatorStack.top()))
                {
                    postfix+=operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.push(ch);
                break;
            default:
                break;
        }
    }
    
    while (!operatorStack.empty())
    {
        postfix+=operatorStack.top();
        operatorStack.pop();
    }
    
    result=postfix;
    return 0;

    stack<bool> operandStack;
    for(int j=0; j<postfix.size();j++)
    {
        char ch=postfix[j];
        if(islower(ch))
        {
            
            operandStack.push(ch);
        }
        else if(ch =='!')
        {
            bool operand3=operandStack.top();
            operandStack.pop();
            operandStack.push(!operand3);
        }
        else if(ch!='!')
        {
            bool operand2 = operandStack.top();
            operandStack.pop();
            bool operand1 = operandStack.top();
            operandStack.pop();
            if(ch=='&')
                operandStack.push(operand2 && operand1);
            else if(ch=='|')
                operandStack.push(operand2 || operand1);
        }
    }
    result=operandStack.top();
    return 0;
}

int main(){
    
    string pf="ff!tn&&|";
    
    assert(evaluate("f  |  !f & (t&n) ", pf)==0);
    cout << pf << endl;
    assert(pf=="ff!tn&&|");
    
    cout<<"passed"<<endl;
}
