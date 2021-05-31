#ifndef ASTAR_OPENSET_H
#define ASTAR_OPENSET_H

//
// AUTHOR: Zbigniew Romanowski
//         romz@wp.pl
// ***  PART OF A-STAR ALGORITHM  *** 
//
//
// ---------------------------------------------------------------------------------
//      D E S C R I P T I O N
// ---------------------------------------------------------------------------------
//  1. This is OPEN SET for A* algorithm.
//
//  2. Open set is represented as priority queue.
//
//  3. It is template class, where template parameter "S" represents GRAPH STATE.
//
//  4. This implementation is based on priority queue from STL library.
//
//  5. The open set holds the pointers to class "PathNode<S>".
//
//  6. Priority queue requires comparison function.
//     Functor GreaterN<S> is used as the comparison function.
//
//  7. The container std::map from STL library is used to search for states of graph state.
//
//  8. Container std::map requires comparison function.
//     Class LessS<S> is used as the comparison function.
//
//  9. Class "S" (i.e. graph state) must define comparison operator:
//       bool S::operator<(const S& a, const S& b) const
//
// 10. Memory for objects of class "PathNode<S>" stored in OPEN SET are allocated in Astar.
//
// 11. Allocated memory by Astar for objects stored in OPEN SET are deleted by open set.


// ---------------------------------------------------------------------------------
//     T H E R E   A R E   F O L L O W I N G   M E M B E R   F U N C T I O N S
// ---------------------------------------------------------------------------------
//  1. void Add(PathNode<S>* t)
//    It adds pointer "p" to OPEN SET. Memory for object pointed by "p" 
//    must be allocated by "new" operator by calling function.
//
//  2. void RemoveBest(void)
//     It removes the best element (i.e. with the lowest PathNode<S>::F() value).
//
//  3. PathNode<S>* Best(void) const
//     It return pointer to the best node (i.e. with the lowest PathNode<S>::F() value).
//
//  4. PathNode<S>* Search(const S& state) const
//     It returns pointer to node, if "state" is present in OPEN SET.
//     Otherwise it returns NULL.
//
//  5. void Update(PathNode<S>* t)
//     It updats priority queue when element "t" already located in the queue was modyfied.
//
//  6. bool IsEmpty(void) const
//     It returns "true" if OPEN SET is empty. Otherwise it returns "false".
//
//  7. size_t Size(void) const
//     It returns the number of elements in OPEN SET
//
//  8. void Erase(void)
//    It deletes all objects pointed by pointers stored in OPEN SET and clears all pointers stored in OPEN SET.
//    After calling this function, the OPEN SET is empty.
//    This function is called by destructor as well.
//
//  9. void PrintStats(FILE* out) const
//     It prints calling statistic to file "out". The statistic is only available,
//     when preprocessor macro "ASTAR_STATISTICS" is defined.


#include "pathnode.h"
#include <cassert>
#include <set>
#include <map>
#include <cstdio>
#include <iostream>

// ---------------------------------------------------------------------------------
//   F U N C T O R S
// ---------------------------------------------------------------------------------
//
// Functor used by priority queue. 
// It compares two objects represented by class PathNode<T>.
// The comaprison is based on value returned by function:
//       Real PathNode<S>::F(void) const.
// Objects of class PathNode<S> are represented by pointers.
//
template <typename S>
class LessF
{
public:
    bool operator() (const PathNode<S>* const a, const PathNode<S>* const b) const
    {
        assert(a && b);
        // assert(a != b);

        // If "F" functions are equal, heuristics are compared
        if(a->F() == b->F())
        {
            // If heuristics are equal, STATES are compared
            if(a->m_h == b->m_h)
                return a->m_state < b->m_state;
                // return a < b; // This is not deterministic
            else
                return a->m_h < b->m_h;
        }

        return a->F() < b->F();     
    }
};


//
// Functor. 
// It compares two graph states "S".
// Objects of class "S" are represented by pointers.
//
template <typename S>
class LessS
{
public:
    bool operator() (const S* const a, const S* const b) const
    {
        assert(a && b);
        return (*a) < (*b);
    }
};


// ---------------------------------------------------------------------------------
//   O P E N   S E T
// ---------------------------------------------------------------------------------
template<typename S>
class OpenSet
{
    typedef typename S::Cost Cost;
public:
    OpenSet(void);
    ~OpenSet(void);

    void Add(PathNode<S>* t);
    void RemoveBest(void);
    void Update(PathNode<S>* p, PathNode<S>* newParent, Cost newG);


    PathNode<S>* Best(void) const;
    PathNode<S>* Search(const S& state) const;

    bool IsEmpty(void) const;
    size_t Size(void) const;

    void Erase(void);

    void PrintStats() const;

private:
    // Array storing data, needed by priority queue
    // std::vector< PathNode<S>* > m_pq;
    std::set< PathNode<S>*, LessF<S> > m_set;

    // Auxiliary data to speed up searching for state.
    std::map< S*, PathNode<S>*, LessS<S> > m_aux;

    // Comparing function object used by priority queue for ordering
    // const GreaterN<S> m_cmp;

#ifdef ASTAR_STATISTICS
    mutable size_t m_stats_add;
    mutable size_t m_stats_best;
    mutable size_t m_stats_removeBest;
    mutable size_t m_stats_search;
    mutable size_t m_stats_erase;
    mutable size_t m_stats_isEmpty;
    mutable size_t m_stats_update;
    mutable size_t m_stats_size;
#endif
};

//
// Default constructor
//
template<typename S>
inline
OpenSet<S>::OpenSet(void)
{
#ifdef ASTAR_STATISTICS
    m_stats_add = 0;
    m_stats_best = 0;
    m_stats_removeBest = 0;
    m_stats_search = 0;
    m_stats_erase = 0;
    m_stats_isEmpty = 0;
    m_stats_update = 0;
    m_stats_size = 0;
#endif
}

//
// Destructor
//
template<typename S>
inline
OpenSet<S>::~OpenSet(void)
{
    Erase();
}

//
// Erase all elements from set
//
template<typename S>
void OpenSet<S>::Erase(void)
{
#ifdef ASTAR_STATISTICS
    m_stats_erase++;
#endif

// std::set< PathNode<S>*, LessF<S> >::iterator it = m_set.begin();
//
//  for(; it != m_set.end(); ++it)
//      delete (*it);
    m_set.clear();

    // Calling the delete operator is not needed.
    m_aux.clear();
}

//
// Returns "true" if OPEN SET os empty
//
template<typename S>
inline
bool OpenSet<S>::IsEmpty(void) const
{
#ifdef ASTAR_STATISTICS
    m_stats_isEmpty++;
#endif

    return m_set.empty();
}

//
// Adds new element represented by pointer to OPEN SET
//
template<typename S>
inline
void OpenSet<S>::Add(PathNode<S>* p)
{
#ifdef ASTAR_STATISTICS
    m_stats_add++;
#endif

    assert(p);
    // Duplications are not allowed. Pointer "p" must not be in OPEN SET
    assert(m_set.count(p) == 0); 

    m_set.insert(p);
    m_aux.insert(std::pair< S*, PathNode<S>* >(&(p->m_state), p));

    // Check the synchronization after operation
    assert(m_aux.size() == m_set.size());
}

//
// Returns element with the smallest value "F" in OPEN SET
//
template<typename S>
inline
PathNode<S>* OpenSet<S>::Best(void) const
{
#ifdef ASTAR_STATISTICS
    m_stats_best++;
#endif

    // Return the pointer to "the best" node
    return *(m_set.begin());
}

//
// Removes the best element from OPEN SET
//
template<typename S>
inline
void OpenSet<S>::RemoveBest(void)
{
#ifdef ASTAR_STATISTICS
    m_stats_removeBest++;
#endif

    // OPEN SET must not be empty
    assert(!m_set.empty());

    // Get the iterator to "the best" node
    typename std::set< PathNode<S>*, LessF<S> >::const_iterator it = m_set.begin();

    // FIRST. Remove "the best" node from auxiliary set
    PathNode<S>* p = *it;
    m_aux.erase(&(p->m_state));

    // SECOND. Remove "the best" node from OPEN SET
    m_set.erase(it);
    
    // Check the synchronization after operation
    assert(m_aux.size() == m_set.size());
}


//
// If state is in OPEN SET, returns pointer to "PathNode" defined by "state".
// Otherwise returns NULL
//
template<typename S>
inline
PathNode<S>* OpenSet<S>::Search(const S& state) const
{
#ifdef ASTAR_STATISTICS
    m_stats_search++;
#endif

    S* p = const_cast<S*>(&state);
    typename std::map< S*, PathNode<S>*, LessS<S> >::const_iterator it = m_aux.find(p);
    if(it != m_aux.end())
        return it->second;
    return NULL;
}


//
// Update OPEN SET, since object pointed by "t" was changed
//
template<typename S>
inline
void OpenSet<S>::Update(PathNode<S>* p, PathNode<S>* newParent, Cost newG)
{
#ifdef ASTAR_STATISTICS
    m_stats_update++;
#endif

    // Erase pointer "p" from OPEN SET
    m_set.erase(m_set.find(p));

    // Update value of object pointed by pointer "p"
    p->m_g = newG;
    p->m_parent = newParent;

    // Insert pointer "p" to OPEN SET
    m_set.insert(p);

    // Auxiliary set "m_aux" need not be modyfied

    // Check the synchronization after operation
    assert(m_aux.size() == m_set.size());
}


//
// Returns number of elements in OPEN SET
//
template<typename S>
inline
size_t OpenSet<S>::Size(void) const
{
#ifdef ASTAR_STATISTICS
    m_stats_size++;
#endif

    return m_set.size();
}


template<typename S>
void OpenSet<S>::PrintStats() const
{
#ifdef ASTAR_STATISTICS
    std::cout << "  OpenSet::Search.... = " << m_stats_search << "\n";
    std::cout << "  OpenSet::Add....... = " << m_stats_add << "\n";
    std::cout << "  OpenSet::Best...... = " << m_stats_best << "\n";
    std::cout << "  OpenSet::RemoveBest = " << m_stats_removeBest << "\n";
    std::cout << "  OpenSet::IsEmpty... = " << m_stats_isEmpty << "\n";
    std::cout << "  OpenSet::Update.... = " << m_stats_update << "\n";
    std::cout << "  OpenSet::Erase..... = " << m_stats_erase << "\n";
    std::cout << "  OpenSet::Size...... = " << m_stats_size << "\n";
#else
    // fprintf(out, "OpenSet. No statistics available!\n");
#endif

}

#endif
