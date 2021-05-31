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

#include <vector>
#include "State.h"
#include "Cost.h"

class Graph
{
public:
    Cost CalcH(const State& x); 
    bool IsGoal(const State& x) const;

    size_t GetChildren(const State& x, std::vector<State>& child, std::vector<Cost>& cost, std::vector<Cost>& heur);

private:
    Cost Manhattan(const State& x) const;

    static char MovesNo( uint8_t idx );
    static char Move( uint8_t sp, uint8_t j );

public:
    // Maximal number of children for any state in graph (space state)
    inline static constexpr unsigned int MAX_CHILD_NO = 4;

private:

    // The GOAL state.
    // The algorithm works ONLY FOR THIS GOAL STATE.
    // If you want to modify the goal state, tables State::m_coorX, State::m_coorY must be modyfied as well!
    inline static const State m_goal{std::array< char, State::TILENO>{
                                  1,  2,  3,  4,  5,
                                  6,  7,  8,  9, 10,
                                 11, 12, 13, 14, 15,
                                 16, 17, 18, 19, 20,
                                 21, 22, 23, 24,  0}};


    // Allowed moves collected in tabular form.
    // The first element of each row determines number of allowed moves.
    inline static const char m_moves[State::TILENO][MAX_CHILD_NO + 1] = {
        {2, 1, 5},    // 0
        {3, 0, 2, 6}, // 1
        {3, 1, 3, 7}, // 2
        {3, 2, 4, 8}, // 3
        {2, 3, 9},    // 4
        {3, 0, 6, 10},    // 5
        {4, 1, 5, 7, 11}, // 6
        {4, 2, 6, 8, 12}, // 7
        {4, 3, 7, 9, 13}, // 8
        {3, 4, 8, 14},    // 9
        {3, 5, 11, 15},     // 10
        {4, 6, 10, 12, 16}, // 11
        {4, 7, 11, 13, 17}, // 12
        {4, 8, 12, 14, 18}, // 13
        {3,  9, 13, 19},    // 14
        {3, 10, 16, 20},     // 15
        {4, 11, 15, 17, 21}, // 16
        {4, 12, 16, 18, 22}, // 17
        {4, 13, 17, 19, 23}, // 18
        {3, 14, 18, 24},     // 19
        {2, 15, 21},     // 20
        {3, 16, 20, 22}, // 21
        {3, 17, 21, 23}, // 22
        {3, 18, 22, 24}, // 23
        {2, 19, 23}      // 24
    };


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
Cost Graph::CalcH(const State& x)
{
    return Manhattan(x);
}

#endif
