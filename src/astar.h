#ifndef ASTAR_ASTAR_H
#define ASTAR_ASTAR_H
//
// AUTHOR: Zbigniew Romanowski
//         romz@wp.pl
// ***  PART OF A-STAR ALGORITHM  *** 
//
//
// ---------------------------------------------------------------------------------
//      D E S C R I P T I O N
// ---------------------------------------------------------------------------------
// 1. Represents A-STAR algorithm as a template class.
//
// 2. Template class take three typenames:
//     Graph - represents weighted graph of states
//     CS    - represents Closed-set
//     OS    - represents Open-set
//
// 3. Function Astat::Find finds the shortest path between the start state
//    and the end (target) state of weighted graph.
//

#include "pathnode.h"
#include "closedset.h"
#include "openset.h"

#include "closedsethash.h"
#include "opensethash.h"

#include "memmgr.h"
#include "Cost.h"
#include "Graph.h"
#include <list>
#include <iostream>
#include <optional>

template<
    template <typename S> class CS = ClosedSetHash,
    template <typename S> class OS = OpenSetHash> 
class Astar
{
public:
    explicit Astar(unsigned int chunkSize = 10000);

    std::optional<std::vector<State>> Find(Graph& graph, const State& beg);

    size_t ClosedNo(void) const { return m_cs.Size(); }
    size_t OpenNo  (void) const { return m_os.Size(); }

    void PrintStats() const;

private:
    void ChildLoop(Graph& graph, PathNode<State>* x);
    std::vector<State> CreatePath(const PathNode<State>* target);

private:
    // Closed set
    CS<State> m_cs;

    // Open set
    OS<State> m_os;

    // Generated children for analyzed node. Auxiliary buffer.
    std::vector<State> m_child;

    // Cost from analyzed node to generated children. Auxiliary buffer.
    std::vector<Cost> m_cost;

    // Heuristic from analyzed node to generated children. Auxiliary buffer.
    std::vector<Cost> m_heur;

    // Memory menager
    MemMgr< PathNode<State> > m_mem;

#ifdef ASTAR_STATISTICS
    size_t m_stats_loopNo;
#endif
};

//
// Constructor
// "chunkSize" - number of elements allocated when increased, in memory allocator
//
template<template <typename S> class CS, template <typename S> class OS>
Astar<CS, OS>::Astar(unsigned int chunkSize) : m_mem(chunkSize)
{
}

//
// Finds the solution.
// Returns "true" if solution is found, otherwise returns "false".
// graph [IN]  - graph of states representing the states
// beg   [IN]  - start state, member of the graph
// path  [OUT] - found solution, vector of states in graph
//
template<template <typename S> class CS, template <typename S> class OS>
std::optional<std::vector<State>> Astar<CS, OS>::Find(Graph& graph, const State& beg)
{
PathNode<State>* p;

#ifdef ASTAR_STATISTICS
    m_stats_loopNo = 0;
#endif

    m_cs.Erase();
    m_os.Erase();
    m_mem.Erase();

    m_child.resize(Graph::MAX_CHILD_NO);
    m_cost.resize(Graph::MAX_CHILD_NO);
    m_heur.resize(Graph::MAX_CHILD_NO);

    const Cost h = graph.CalcH(beg);
    p = m_mem.New();
    p->Set(beg, NULL, 0, h);
    m_os.Add(p);

    while(!m_os.IsEmpty())
    {
#ifdef ASTAR_STATISTICS
        m_stats_loopNo++;
#endif

        // the node in openset having the lowest f_score value
        p = m_os.Best();
        if(graph.IsGoal(p->m_state))
        {
            return CreatePath(p);
        }
        m_os.RemoveBest();
        m_cs.Add(p);

        ChildLoop(graph, p);
    }

    return {};
}

//
// Loop over all children of "node"
//
template<template <typename S> class CS, template <typename S> class OS>
void Astar<CS, OS>::ChildLoop(Graph& graph, PathNode<State>* node)
{
PathNode<State> *p;

    assert(node);

    const size_t childNo = graph.GetChildren(node->m_state, m_child, m_cost, m_heur);

    for(size_t i = 0; i < childNo; i++)
    {
        const State &y = m_child[i];
        if(m_cs.Search(y))
            continue;

        const Cost g = node->m_g + m_cost[i];

        p = m_os.Search(y);

        if(p == NULL)
        {
            p = m_mem.New();
            p->Set(y, node, g, m_heur[i]);
            m_os.Add(p);
        }
        else if(g < p->m_g)
        {
            // Object pointed by "p" was changed, hence OPEN SET must be updated
            m_os.Update(p, node, g);
        }

    }
}

//
// Creates the path being the result of A-Star algorithm
//
template<template <typename S> class CS, template <typename S> class OS>
std::vector<State> Astar<CS, OS>::CreatePath(const PathNode<State>* node)
{
std::list<State> tmp; // Temporary list for storing states in proper order

    while(node)
    {
        tmp.push_front(node->m_state);
        node = node->m_parent;
    }

    // Copying states from list to array
    typename std::list<State>::const_iterator it;
    size_t i = 0;
    
    std::vector<State> path;
    path.resize(tmp.size()); // 
    for(it = tmp.begin(); it != tmp.end(); ++it, ++i)
    {
        path[i] = *it;
    }

    return path;
}

//
// Writes statistics to log file
//
template<template <typename S> class CS, template <typename S> class OS>
void Astar<CS, OS>::PrintStats() const
{
#ifdef ASTAR_STATISTICS
    std::cout << "\nSTATISTICS:\n";
    
    std::cout << "  Astar::LoopNo = " << m_stats_loopNo << "\n\n";

    m_os.PrintStats();
    std::cout << "\n";

    m_cs.PrintStats();
    std::cout << "\n";
#else
    // fprintf(out, "Astar. No statistics available!\n");
#endif
}

#endif
