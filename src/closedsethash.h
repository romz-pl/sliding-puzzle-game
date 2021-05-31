#ifndef ASTAR_CLOSEDSETHASH_H
#define ASTAR_CLOSEDSETHASH_H


//
// AUTHOR: Zbigniew Romanowski
//         romz@wp.pl
// ***  PART OF A-STAR ALGORITHM  *** 
//
//
// ---------------------------------------------------------------------------------
//      D E S C R I P T I O N
// ---------------------------------------------------------------------------------
// 1. This is CLOSED SET for A* algorithm.
//
// 2. It is template class, where template parameter "S" represents GRAPH STATE.
//
// 3. The closed set holds the pointers to class "PathNode<S>".
//
// 4. Implementation is based on template class HashSet.
//
// 5. OPEN SET holds only pointers to GRAPH STATE.
//

#include "hashset.h"
#include <cstdio>
#include <iostream>

template<typename S>
class ClosedSetHash
{
public:
	ClosedSetHash(void);

	void Add(PathNode<S>* p);
	bool Search(const S& state) const;

	void Erase(void);
	size_t Size() const;

    void PrintStats() const;

private:
	// Container storing pointers to "PathNode<S>"
	HashSet<S> m_set;

#ifdef ASTAR_STATISTICS
	mutable size_t m_stats_erase;     // Number of calls for function Erase
	mutable size_t m_stats_add;       // Number of calls for function Add
	mutable size_t m_stats_search;    // Number of calls for function Search
	mutable size_t m_stats_size;      // Number of calls for function Size
	mutable size_t m_stats_collision; // Number of collisions in hash table
#endif

};

//
// Default constructor
//
template<typename S>
inline
ClosedSetHash<S>::ClosedSetHash(void) : m_set(10000000)
{
#ifdef ASTAR_STATISTICS
	m_stats_erase = 0;
	m_stats_add = 0;
	m_stats_search = 0;
	m_stats_size = 0;
	m_stats_collision = 0;
#endif
}

//
// Erase all elements from set.
// Objects pointed by pointers stored in the set are deleted.
//
template<typename S>
void ClosedSetHash<S>::Erase(void)
{
#ifdef ASTAR_STATISTICS
	m_stats_erase++;
#endif

	m_set.Clear();
}

//
// Adds new element represented by pointer "p"
//
template<typename S>
inline
void ClosedSetHash<S>::Add(PathNode<S>* p)
{
#ifdef ASTAR_STATISTICS
	m_stats_add++;
#endif

	assert(p);

#ifdef ASTAR_STATISTICS
	m_stats_collision += m_set.Insert(p);
#else
	m_set.Insert(p);
#endif
	
}

//
// Returns "true" if "state" is in CLOSED SET
//
template<typename S>
inline
bool ClosedSetHash<S>::Search(const S& state) const
{
#ifdef ASTAR_STATISTICS
	m_stats_search++;
#endif

	return (m_set.Find(state) != NULL);
}

//
// Returns number of elements in CLOSED SET
//
template<typename S>
inline
size_t ClosedSetHash<S>::Size() const
{
#ifdef ASTAR_STATISTICS
	m_stats_size++;
#endif

	return m_set.Count();
}

//
// Prints statistics to file "out"
//
template<typename S>
void ClosedSetHash<S>::PrintStats() const
{
#ifdef ASTAR_STATISTICS
    std::cout << "  ClosedSetHash::Search....... = " << m_stats_search << "\n";
    std::cout << "  ClosedSetHash::Add.......... = " << m_stats_add << "\n";
    std::cout << "  ClosedSetHash::Erase........ = " << m_stats_erase << "\n";
    std::cout << "  ClosedSetHash::Size......... = " << m_stats_size << "\n";
    std::cout << "  ClosedSetHash::Collisions... = " << m_stats_collision << "\n";
#else
	// fprintf(out, "ClosedSetSTL. No statistics available!\n");
#endif
}


#endif
