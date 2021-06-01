#include "Graph.h"
#include <cstdlib>

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

    for(uint i = 0; i < State::TILENO; i++)
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

