//
//  maze.cpp
//  HW3
//
//  Created by Ziying Yu on 2/7/19.
//  Copyright © 2019 Ziying Yu. All rights reserved.
//

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

 bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    if (sr==er && sc==ec)
        return true;
    maze[sr][sc]='o';
    
    Coord s=Coord(sr+1,sc);
    if(maze[s.r()][s.c()] == '.' && pathExists(maze, nRows, nCols, s.r(), s.c(), er, ec))
        return true;
    
    Coord w=Coord(sr,sc-1);
    if(maze[w.r()][w.c()] == '.' && pathExists(maze, nRows, nCols, w.r(), w.c(), er, ec))
        return true;
    
    Coord n=Coord(sr-1,sc);
    if(maze[n.r()][n.c()] == '.' && pathExists(maze, nRows, nCols, n.r(), n.c(), er, ec))
        return true;
    
    Coord e=Coord(sr,sc+1);
    if(maze[e.r()][e.c()] == '.' && pathExists(maze, nRows, nCols, e.r(), e.c(), er, ec))
        return true;
    
    return false;
}
