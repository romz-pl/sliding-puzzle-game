#ifndef ASTAR_GRAPHP25_H
#define ASTAR_GRAPHP25_H


//
// AUTHOR: Zbigniew Romanowski
//         romz@wp.pl
// ***  PART OF A-STAR ALGORITHM  *** 
//
//
// ---------------------------------------------------------------------------------
//      D E S C R I P T I O N
// ---------------------------------------------------------------------------------
// 1. Represents graph of 25-Puzzle game
//
// 2. This is weighted graph of states.
// 
// 3. Each state of graph is represented by object of class StateP25.
//
// 4. Distance between states is defined by Manhattan metric.
//
// 5. There are pre-defined (hard-coded) interesting targed configurations.
//

#include "statep25.h"
#include <vector>

class GraphP25
{
public:
    // Declaration of type "State" is required by template class "Astar"
    typedef StateP25 State;

    // Declaration of type "Cost" is required by template class "Astar"
    typedef StateP25::Cost Cost;

public:
    Cost CalcH(const State& x); 
    bool IsGoal(const State& x) const;

    size_t MaxChildNo(void) const;
    size_t GetChildren(const State& x, std::vector<State>& child, std::vector<Cost>& cost, std::vector<Cost>& heur);

private:
    StateP25::Cost Manhattan(const StateP25& x) const;

    static char MovesNo( uint8_t idx );
    static char Move( uint8_t sp, uint8_t j );

private:
    // The GOAL state
    static const StateP25 m_goal;

    // Maximal number of children for any state in graph (space state)
    enum{MAXCHILDNO = 4};

    // Allowed moves. The first element of each row determines number of allowed moves.
    static const char m_moves[StateP25::TILENO][MAXCHILDNO + 1];


    // Number of pre-defined samples (exemplary begin states). 
    enum{SAMPLENO = 9};

    // Pre-defined exemplary states
    static const char m_sample[SAMPLENO][StateP25::TILENO];
};

//
// Returns maximum number of children for any state in graph (space state)
//
inline
size_t GraphP25::MaxChildNo(void) const
{
    return MAXCHILDNO;
}

//
// Returns "true" if "x" is the GOAL state
//
inline
bool GraphP25::IsGoal(const StateP25& x) const
{
    return (x == m_goal);
}

//
// Return number of moves, when space is on i-th position 
//
inline
char GraphP25::MovesNo( uint8_t idx )
{
    assert( idx < StateP25::TILENO );
    return m_moves[ idx ][ 0 ];
}

//
// Returns j-th allowed position, when space is on "sp" position
//
inline
char GraphP25::Move( uint8_t sp, uint8_t j )
{
    assert( sp < StateP25::TILENO );
    assert( j < MAXCHILDNO );
    return m_moves[ sp ][ j + 1 ];
}

//
// Returns value of heuristic from "x" to GOAL state
//
inline
StateP25::Cost GraphP25::CalcH(const StateP25& x)
{
    return Manhattan(x);
}

#endif
