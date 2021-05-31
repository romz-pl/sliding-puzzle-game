#ifndef ASTAR_CLOSEDSET_H
#define ASTAR_CLOSEDSET_H

//
// AUTHOR: Zbigniew Romanowski
//         romz@wp.pl
// DATE: 07 September 2010
// ***  PART OF A-STAR ALGORITHM  *** 
//
// ---------------------------------------------------------------------------------
//      D E S C R I P T I O N
// ---------------------------------------------------------------------------------
// 1. This is CLOSED SET for A* algorithm.
//
// 2. It is template class, where template parameter "S" represents GRAPH STATE.
//
// 3. This implementation is based on std::set container from STL library.
//
// 4. The closed set holds the pointers to class "PathNode<S>".
//
// 5. Container std::set requires comparison function.
//    Class LessN<S> is used as the comparison function.
//
// 6. Class "S" (i.e. graph state) must define comparison operator:
//       bool S::operator<(const S& a, const S& b) const
//
// 7. Memory for objects of class "PathNode<S>" stored in CLOSED SET are allocated in Astar.
//
// 8. Allocated memory by Astar for objects stored in OPEN SET are deleted by open set.
//
//
//
//
// ---------------------------------------------------------------------------------
//     T H E R E   A R E   F O L L O W I N G   M E M B E R   F U N C T I O N S
// ---------------------------------------------------------------------------------
// 1. void Add(PathNode<S>* p)
//    It adds pointer "p" to CLOSED SET. Memory for object pointed by "p" 
//    must be allocated by "new" operator by calling function.
//
// 2. bool Search(const S& state) const
//    It returns "true", if "state" is in CLOSED SET. Otherwise it returns "false".
//
// 3. void Erase(void)
//    It deletes all objects pointed by pointers stored in CLOSED SET and clears all pointers stored in CLOSED SET.
//    After calling this function, the CLOSED SET is empty.
//    This function is called by destructor as well.
//
// 4. size_t Size() const
//    It returns the number of elements in CLOSED SET.
//
// 5. void PrintStats(FILE* out) const
//    It prints calling statistic to file "out". The statistic is only available,
//    when preprocessor macro "ASTAR_STATISTICS" is defined.
//


#include "pathnode.h"
#include <cassert>
#include <set>
#include <cstddef>
#include <cstdio>
#include <iostream>

//
// ---------------------------------------------------------------------------------
//   F U N C T O R
// ---------------------------------------------------------------------------------
//
// It compares two graph states "S" stored in objects of class PathNode<S>.
// Objects of class PathNode<S> are represented by pointers.
//
template <typename S>
class LessN
{
public:
	bool operator() (const PathNode<S>* const a, const PathNode<S>* const b) const
	{
		assert(a && b);
		return (a->m_state < b->m_state);
	}
};

//
// ---------------------------------------------------------------------------------
//   C L O S E D   S E T
// ---------------------------------------------------------------------------------
//
// Template parameter "S" represents graph state.
//
template<typename S>
class ClosedSet
{
public:
    ClosedSet(void);
    ~ClosedSet(void);

	void Add(PathNode<S>* p);
	bool Search(const S& state) const;

	void Erase(void);
	size_t Size() const;

    void PrintStats() const;

private:
	// Container storing pointers to "PathNode<S>"
	std::set< PathNode<S>*, LessN<S> > m_set;

#ifdef ASTAR_STATISTICS
	mutable size_t m_stats_erase;  // Number of calls for function Erase
	mutable size_t m_stats_add;    // Number of calls for function Add
	mutable size_t m_stats_search; // Number of calls for function Search
	mutable size_t m_stats_size;   // Number of calls for function Size
#endif
};

//
// Default constructor
//
template<typename S>
inline
ClosedSet<S>::ClosedSet(void)
{
#ifdef ASTAR_STATISTICS
	m_stats_erase = 0;
	m_stats_add = 0;
	m_stats_search = 0;
	m_stats_size = 0;
#endif
}

//
// Destructor
//
template<typename S>
inline
ClosedSet<S>::~ClosedSet(void)
{
	Erase();
}


//
// Erase all elements from set.
// Objects pointed by pointers stored in the set are deleted.
//
template<typename S>
void ClosedSet<S>::Erase(void)
{
#ifdef ASTAR_STATISTICS
	m_stats_erase++;
#endif

// std::set< PathNode<S>*, LessN<S> >::iterator it = m_set.begin();
//
//	for(; it != m_set.end(); ++it)
//		delete (*it);
	m_set.clear();
}


//
// Adds new element represented by pointer "p"
//
template<typename S>
inline
void ClosedSet<S>::Add(PathNode<S>* p)
{
#ifdef ASTAR_STATISTICS
	m_stats_add++;
#endif

	assert(p);
	m_set.insert(p);
}

//
// Returns "true" if "state" is in CLOSED SET
//
template<typename S>
inline
bool ClosedSet<S>::Search(const S& state) const
{
#ifdef ASTAR_STATISTICS
	m_stats_search++;
#endif

// This is a temporary object required for comparison.
// This object is only used by funtion:
//     bool LessN<S>::operator(const PathNode<S>* const, const PathNode<S>* const) const
//
// This object can be treated as a wrapper for "state" object.
PathNode<S> tmp(state, NULL, 0, 0);

	return (m_set.count(&tmp) > 0);
}

//
// Returns number of elements in CLOSED SET
//
template<typename S>
inline
size_t ClosedSet<S>::Size() const
{
#ifdef ASTAR_STATISTICS
	m_stats_size++;
#endif

	return m_set.size();
}

//
// Prints statistics to file "out"
//
template<typename S>
void ClosedSet<S>::PrintStats() const
{
#ifdef ASTAR_STATISTICS
    std::cout << "  ClosedSet::Search.... = " << m_stats_search << "\n";
    std::cout << "  ClosedSet::Add....... = " << m_stats_add << "\n";
    std::cout << "  ClosedSet::Erase..... = " << m_stats_erase << "\n";
    std::cout << "  ClosedSet::Size...... = " << m_stats_size << "\n";
#else
    // fprintf(out, "ClosedSet. No statistics available!\n");
#endif
}


#endif
