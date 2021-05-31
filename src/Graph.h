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
// 3. Each state of graph is represented by object of class State.
//
// 4. Distance between states is defined by Manhattan metric.
//
// 5. There are pre-defined (hard-coded) interesting targed configurations.
//

#include "State.h"
#include <vector>

class Graph
{
public:
    // Declaration of type "State" is required by template class "Astar"
    using State = ::State;

    // Declaration of type "Cost" is required by template class "Astar"
    using Cost = State::Cost;

public:
    Cost CalcH(const State& x); 
    bool IsGoal(const State& x) const;

    size_t GetChildren(const State& x, std::vector<State>& child, std::vector<Cost>& cost, std::vector<Cost>& heur);

private:
    State::Cost Manhattan(const State& x) const;

    static char MovesNo( uint8_t idx );
    static char Move( uint8_t sp, uint8_t j );

public:
    // Maximal number of children for any state in graph (space state)
    inline static constexpr unsigned int MAX_CHILD_NO = 4;

private:

    // The GOAL state.
    // The algorithm works ONLY FOR THIS GOAL STATE.
    // If you want to modify the goal state, tables State::m_coorX, State::m_coorY
    // must be modyfied as well!
    inline static const State m_goal{std::array< char, State::TILENO>{
                                  1,  2,  3,  4,  5,
                                  6,  7,  8,  9, 10,
                                 11, 12, 13, 14, 15,
                                 16, 17, 18, 19, 20,
                                 21, 22, 23, 24,  0}};


    // Allowed moves. The first element of each row determines number of allowed moves.
    static const char m_moves[State::TILENO][MAX_CHILD_NO + 1];


    // Number of pre-defined samples (exemplary begin states). 
    inline static constexpr unsigned int SAMPLENO = 9;

    // Pre-defined exemplary states
    static const char m_sample[SAMPLENO][State::TILENO];
};

//
// Returns "true" if "x" is the GOAL state
//
inline
bool Graph::IsGoal(const State& x) const
{
    return (x == m_goal);
}

//
// Return number of moves, when space is on i-th position 
//
inline
char Graph::MovesNo( uint8_t idx )
{
    assert( idx < State::TILENO );
    return m_moves[ idx ][ 0 ];
}

//
// Returns j-th allowed position, when space is on "sp" position
//
inline
char Graph::Move( uint8_t sp, uint8_t j )
{
    assert( sp < State::TILENO );
    assert( j < MAX_CHILD_NO );
    return m_moves[ sp ][ j + 1 ];
}

//
// Returns value of heuristic from "x" to GOAL state
//
inline
State::Cost Graph::CalcH(const State& x)
{
    return Manhattan(x);
}

#endif
