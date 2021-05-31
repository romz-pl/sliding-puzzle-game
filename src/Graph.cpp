#include "Graph.h"
#include <cstdlib>

// Exemplary begin states
const char Graph::m_sample[SAMPLENO][State::TILENO] = {
    {2,8,3,5,9,1,6,7,4,0,11,12,13,14,10,16,17,18,19,15,21,22,23,24,20}, // 15 moves (VERY EASY)
    {1,7,2,8,4,6,9,13,3,5,11,17,12,14,10,16,18,23,22,15,21,24,19,20,0}, // 30 moves (EASY)
    {1,4,3,5,10,6,7,8,2,9,23,11,13,14,15,12,0,18,24,19,17,16,21,22,20}, // 42 moves
    {0,6,2,9,4,17,1,3,10,14,22,8,7,12,5,21,11,18,13,24,16,23,15,20,19},
    {2,3,7,9,4,11,1,14,5,10,12,17,15,19,8,22,6,13,0,23,16,21,18,24,20}, // 48 moves (HARD)
    // {1,7,2,8,3,11,6,9,5,4,12,13,18,10,0,16,22,15,24,20,21,23,17,19,14},
    {6,1,8,3,4,11,15,2,5,10,7,19,0,20,9,16,18,12,23,14,21,13,17,22,24}, // ?? moves (VERY HARD)
    {7,1,4,9,5,13,3,24,10,19,6,8,12,18,2,17,0,22,15,20,16,11,23,21,14}, // ?? moves (VERY HARD)
    

    // {1,3,4,14,5,6,7,2,0,9,11,8,12,20,10,21,18,16,19,15,17,22,13,23,24}, // 40 moves (HARD)
    { 9, 0, 7, 3, 4,   6, 2, 1,13, 5,  11,12, 8,15,10,  16,17,18,14,24,  21,22,23,20,19},
    { 1, 2, 3, 4, 5,   6, 7, 8, 0,10,  16,11,14, 9,15,  21,12,18,23,19,  17,22,20,13,24}
//  { 1, 7, 2, 5, 3,   6, 8, 9, 0, 4,  12,13,14,15,10,  11,17,18,19,20,  16,21,22,23,24},
//  { 1, 2, 9, 3, 5,   6, 7, 8, 4,10,  11,12,13,14,15,  16, 0,18,19,20,  21,17,22,23,24}
};


//
// Generates children for state "x". Generated states (children) are stored
// in "child", "cost", "heur" arrays.
//
size_t Graph::GetChildren(const State& x, std::vector<State>& child,
    std::vector<Cost>& cost, std::vector<Cost>& heur)
{
const char idx = x.SpaceIdx();
const char movesNo = MovesNo(idx);

    assert(child.size() >= static_cast<size_t>(movesNo));
    assert(child.size() == cost.size());
    assert(child.size() == heur.size());

    for(char i = 0;  i < movesNo; i++)
    {
        child[i] = x;
        child[i].Swap(idx, Move(idx, i));
        cost[i] = 1;
        heur[i] = CalcH(child[i]);
    }
    
    return movesNo;
}

//
// Calculates heurictic for state "s" as Manhatten distance 
//
Cost Graph::Manhattan(const State& s) const
{
char cx, cy, gx, gy;
Cost h = 0;

    for(char i = 0; i < State::TILENO; i++)
    {
        // do not count the blank 
        if(s.IsSpace(i))
            continue;

        // Current (X,Y) coordinates
        cx = s.X(i);
        cy = s.Y(i);

        // Goal state (X,Y) coordinates
        gx = m_goal.X(i);
        gy = m_goal.Y(i);

        // add manhatten distance to h
        h += abs(cx - gx) + abs(cy - gy);
    }
    return h;
}

