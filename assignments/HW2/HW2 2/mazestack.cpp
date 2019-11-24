//
//  mazestack.cpp
//  HW2
//
//  Created by Ziying Yu on 1/31/19.
//  Copyright © 2019 Ziying Yu. All rights reserved.
//

#include <iostream>
#include <stack>

using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    stack<Coord> coordStack;
    Coord start(sr,sc);
    Coord end(er,ec);
    
    coordStack.push(start);
    maze[sr][sc]='o';
    
    while (!coordStack.empty())
    {
        Coord curr=coordStack.top();
        //cout<<"current location is ( "<<curr.r()<<" , "<<curr.c()<<" )"<<endl;
        coordStack.pop();
        //cout<<"current location is ( "<<curr.r()<<" , "<<curr.c()<<" )"<<endl;
        
        if(curr.r()==end.r() && curr.c()==end.c())
        {
            return true;
        }
        
        //south is available
        if(maze[curr.r()+1][curr.c()] == '.')
        {
            maze[curr.r()+1][curr.c()] = 'o';
            coordStack.push(Coord(curr.r()+1,curr.c()));
        }

        //west is available
        if(maze[curr.r()][curr.c()-1] == '.')
        {
            maze[curr.r()][curr.c()-1] = 'o';
            coordStack.push(Coord(curr.r(),curr.c()-1));
        }
        
        //north is available
        if(maze[curr.r()-1][curr.c()] == '.')
        {
            maze[curr.r()-1][curr.c()] = 'o';
            coordStack.push(Coord(curr.r()-1,curr.c()));
        }
        
        //east is available
        if(maze[curr.r()][curr.c()+1] == '.')
        {
            maze[curr.r()][curr.c()+1] = 'o';
            coordStack.push(Coord(curr.r(),curr.c()+1));
        }
    }
    
    return false;
}

