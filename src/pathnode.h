#ifndef ASTAR_PATHNODE_H
#define ASTAR_PATHNODE_H
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
// 1. Represents the wrapper to graph state S.
// 
// 2. Template parameter "S" is a graph state.
//
// 3. Object of class PathNode is an element of found path in A-star algorithm.
//

template<typename S>
class PathNode
{
	typedef typename S::Cost Cost;
public:
    PathNode(void) : m_parent(nullptr), m_g(0), m_h(0) {}
	PathNode(const S& state, PathNode* parent, Cost g, Cost h)
		: m_state(state), m_parent(parent), m_g(g), m_h(h) {}

	void Set(const S& state, PathNode* parent, Cost g, Cost h)
	{
		m_state = state;
		m_parent = parent;
		m_g = g;
		m_h = h;
	}

	// Sum "f=g+h" is calculated in order to decrease memory consumption
	Cost F(void) const { return m_g + m_h; }

public:
	// State of state space (node of the graph)
	S m_state;

	// Parent of the "m_state", i.e. how the "m_state" is reached
	PathNode<S>* m_parent;

	// Cost from START state to "m_state"
	Cost m_g;

	// Estimated cost (heuristic) from "m_state" to GOAL (target) state
	Cost m_h;
};

#endif

