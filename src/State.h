#ifndef ASTAR_STATE_H
#define ASTAR_STATE_H

//
// AUTHOR: Zbigniew Romanowski
//         romz@wp.pl
// ***  PART OF A-STAR ALGORITHM  *** 
//
//
// ---------------------------------------------------------------------------------
//      D E S C R I P T I O N
// ---------------------------------------------------------------------------------
// 1. Represents state in Puzzle-25 game.
//
// 2. This class is directly related to GraphP25.
//
// 3. State is represented as an array of characters.
//
// 4. TILE numbering:
//    1  2  3  4  5
//    6  7  8  8 10
//   11 12 13 14 15
//   16 17 18 19 20
//   21 22 23 24 25
//

#include <cstring>
#include <cstdio>
#include <cassert>
#include <string>
#include <array>
#include <cstdint>

class State
{
public:
    // Width of the squared board
    inline static constexpr unsigned int WIDTH = 5;

    // Number of tiles on the board
    inline static constexpr unsigned int TILENO = WIDTH * WIDTH;


public:
    State( );
    explicit State( const std::array< char, TILENO> tab );

    bool operator==(const State& s) const;
    bool operator< (const State& s) const;

    char SpaceIdx( ) const;
    bool IsSpace( uint8_t idx ) const;
    
    void Swap(char oldPos, char newPos);

    char X( uint8_t idx ) const;
    char Y( uint8_t idx ) const;

    void Print(FILE* out) const;
    void PrintDiff(const State& next) const;

    void Read( const std::string& file );

private:
    const char* Lab( uint8_t idx ) const;
    
private:
    // Tiles on the board
    // char m_tab[TILENO];
    std::array< char, TILENO> m_tab;

private:
    // X-coordinates of the GOAL state
    static const char m_coorX[State::TILENO];

    // Y-coordinates of the GOAL state
    static const char m_coorY[State::TILENO];

    // Names of tiles on the board
    static const char* const m_label[TILENO];
};

//
// Returns "true", if on position "idx" is SPACE
//
inline
bool State::IsSpace( uint8_t idx ) const
{
    assert( idx < TILENO );
    return ( m_tab[ idx ] == 0 );
}

//
// Changes the positions of two tiles
//
inline
void State::Swap(char oldPos, char newPos)
{
    const char tmp = m_tab[newPos];

    m_tab[newPos] = m_tab[oldPos];
    m_tab[oldPos] = tmp;
}


//
// Returns label of i-th tile.
//
inline
const char* State::Lab( uint8_t idx ) const
{
    return m_label[ static_cast<uint>( m_tab[ idx ] ) ];
}

//
// Returns X-coordinate of i-th tile
//
inline
char State::X( uint8_t idx ) const
{
    return m_coorX[ static_cast<uint>( m_tab[ idx ] ) ];
}

//
// Returns Y-coordinate of i-th tile
//
inline
char State::Y( uint8_t idx ) const
{
    return m_coorY[ static_cast<uint>( m_tab[ idx ] ) ];
}


//
// Equality operator
//
inline
bool State::operator==( const State& s ) const
{
    for( uint8_t i = 0; i < TILENO; i++ )
    {
        if( m_tab[ i]  != s.m_tab[ i ])
            return false;
    }
    return true;
}

#endif

