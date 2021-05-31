#ifndef ASTAR_STATEP25_H
#define ASTAR_STATEP25_H

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

class StateP25
{
public:
	// Type used to evaluate the heuristic and to evaluate the cost between two connected states.
	typedef int Cost;

public:
	// WIDTH: Width of the squared board
	// TILENO: Number of tiles on the board
	enum{WIDTH = 5, TILENO = WIDTH * WIDTH};


public:
    StateP25( );
    explicit StateP25( const std::array< char, TILENO> tab );

	bool operator==(const StateP25& s) const;
	bool operator< (const StateP25& s) const;

    char SpaceIdx( ) const;
    bool IsSpace( uint8_t idx ) const;
	
	void Swap(char oldPos, char newPos);

    char X( uint8_t idx ) const;
    char Y( uint8_t idx ) const;

	void Print(FILE* out) const;
	void PrintDiff(const StateP25& next) const;

    void Read( const std::string& file );

private:
    const char* Lab( uint8_t idx ) const;
	
private:
	// Tiles on the board
    // char m_tab[TILENO];
    std::array< char, TILENO> m_tab;

private:
	// X-coordinates of the GOAL state
	static const char m_coorX[StateP25::TILENO];

	// Y-coordinates of the GOAL state
	static const char m_coorY[StateP25::TILENO];

	// Names of tiles on the board
	static const char* const m_label[TILENO];
};

//
// Returns "true", if on position "idx" is SPACE
//
inline
bool StateP25::IsSpace( uint8_t idx ) const
{
    assert( idx < TILENO );
    return ( m_tab[ idx ] == 0 );
}

//
// Changes the positions of two tiles
//
inline
void StateP25::Swap(char oldPos, char newPos)
{
    const char tmp = m_tab[newPos];

	m_tab[newPos] = m_tab[oldPos];
	m_tab[oldPos] = tmp;
}


//
// Returns label of i-th tile.
//
inline
const char* StateP25::Lab( uint8_t idx ) const
{
    return m_label[ static_cast<uint>( m_tab[ idx ] ) ];
}

//
// Returns X-coordinate of i-th tile
//
inline
char StateP25::X( uint8_t idx ) const
{
    return m_coorX[ static_cast<uint>( m_tab[ idx ] ) ];
}

//
// Returns Y-coordinate of i-th tile
//
inline
char StateP25::Y( uint8_t idx ) const
{
    return m_coorY[ static_cast<uint>( m_tab[ idx ] ) ];
}


//
// Equality operator
//
inline
bool StateP25::operator==( const StateP25& s ) const
{
    for( uint8_t i = 0; i < TILENO; i++ )
    {
        if( m_tab[ i]  != s.m_tab[ i ])
            return false;
    }
    return true;
}

#endif

