#ifndef ASTAR_OPENSETHASH_H
#define ASTAR_OPENSETHASH_H

//
// AUTHOR: Zbigniew Romanowski
//         romz@wp.pl
// DATE: 07 September 2010
// ***  PART OF A-STAR ALGORITHM  *** 
//
//
// ---------------------------------------------------------------------------------
//      D E S C R I P T I O N
// ---------------------------------------------------------------------------------
// 1. This is OPEN SET for A* algorithm.
//
// 2. It is template class, where template parameter "S" represents GRAPH STATE.
//
// 3. This implementation of "prioryty queue" is based on std::set container from STL library.
//
// 4. The closed set holds the pointers to class "PathNode<S>".
//
// 5. In order to seep-up searching auxiliary structure based on class HashSet is created.
//
// 6. OPEN SET holds only pointers to GRAPH STATE.
//

#include "Cost.h"
#include "pathnode.h"
#include "hashset.h"
#include <set>


template<typename S>
class OpenSetHash
{
public:
    OpenSetHash(void);

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
    std::set< PathNode<S>*, LessF<S> > m_set;

    // Auxiliary data to speed up searching for state.
    HashSet<S> m_aux;

#ifdef ASTAR_STATISTICS
    mutable size_t m_stats_add;
    mutable size_t m_stats_best;
    mutable size_t m_stats_removeBest;
    mutable size_t m_stats_search;
    mutable size_t m_stats_erase;
    mutable size_t m_stats_isEmpty;
    mutable size_t m_stats_update;
    mutable size_t m_stats_size;
    mutable size_t m_stats_collision; // Number of collisions in hash table
#endif
};


//
// Default constructor
//
template<typename S>
inline
OpenSetHash<S>::OpenSetHash(void) : m_aux(10000000)
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
    m_stats_collision = 0;
#endif
}

//
// Erase all elements from set
//
template<typename S>
void OpenSetHash<S>::Erase(void)
{
#ifdef ASTAR_STATISTICS
    m_stats_erase++;
#endif

    m_set.clear();
    m_aux.Clear();
}

//
// Returns "true" if OPEN SET os empty
//
template<typename S>
inline
bool OpenSetHash<S>::IsEmpty(void) const
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
void OpenSetHash<S>::Add(PathNode<S>* p)
{
#ifdef ASTAR_STATISTICS
    m_stats_add++;
#endif

    assert(p);
    // Duplications are not allowed. Pointer "p" must not be in OPEN SET
    assert(m_set.count(p) == 0); 

    m_set.insert(p);

#ifdef ASTAR_STATISTICS
    m_stats_collision += m_aux.Insert(p);
#else
    m_aux.Insert(p);
#endif

    // Check the synchronization after operation
    assert(m_aux.Count() == m_set.size());
}

//
// Returns element with the smallest value "F" in OPEN SET
//
template<typename S>
inline
PathNode<S>* OpenSetHash<S>::Best(void) const
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
void OpenSetHash<S>::RemoveBest(void)
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
    m_aux.Erase(p->m_state);

    // SECOND. Remove "the best" node from OPEN SET
    m_set.erase(it);
    
    // Check the synchronization after operation
    assert(m_aux.Count() == m_set.size());
}

//
// If state is in OPEN SET, returns pointer to "PathNode" defined by "state".
// Otherwise returns NULL
//
template<typename S>
inline
PathNode<S>* OpenSetHash<S>::Search(const S& state) const
{
#ifdef ASTAR_STATISTICS
    m_stats_search++;
#endif

    return m_aux.Find(state);
}

//
// Update OPEN SET, since object pointed by "t" was changed
//
template<typename S>
inline
void OpenSetHash<S>::Update(PathNode<S>* p, PathNode<S>* newParent, Cost newG)
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
    assert(m_aux.Count() == m_set.size());
}

//
// Returns number of elements in OPEN SET
//
template<typename S>
inline
size_t OpenSetHash<S>::Size(void) const
{
#ifdef ASTAR_STATISTICS
    m_stats_size++;
#endif

    return m_set.size();
}


template<typename S>
void OpenSetHash<S>::PrintStats() const
{
#ifdef ASTAR_STATISTICS
    std::cout << "  OpenSetHash::Search.... = " << m_stats_search << "\n";
    std::cout << "  OpenSetHash::Add....... = " << m_stats_add << "\n";
    std::cout << "  OpenSetHash::Best...... = " << m_stats_best << "\n";
    std::cout << "  OpenSetHash::RemoveBest = " << m_stats_removeBest << "\n";
    std::cout << "  OpenSetHash::IsEmpty... = " << m_stats_isEmpty << "\n";
    std::cout << "  OpenSetHash::Update.... = " << m_stats_update << "\n";
    std::cout << "  OpenSetHash::Erase..... = " << m_stats_erase << "\n";
    std::cout << "  OpenSetHash::Size...... = " << m_stats_size << "\n";
    std::cout << "  OpenSetHash::Collision. = " << m_stats_collision << "\n";
#else
    // fprintf(out, "OpenSetSTL. No statistics available!\n");
#endif

}


#endif
