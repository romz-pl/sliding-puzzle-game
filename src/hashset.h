#ifndef ASTAR_HASHSET_H
#define ASTAR_HASHSET_H

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
// 1. This is a template hash table.
//
// 2. Table keeps the pointers to the objects only.
//
// 3. This is linear hash-table with dynamic expansion.
//

#include "pathnode.h"
#include <vector>
#include <cassert>

template <typename S>
class HashSet
{
public:
	HashSet(unsigned int initSize);

	unsigned int Insert(PathNode<S>* p);

	bool Find(PathNode<S>* p) const;
	PathNode<S>* Find(const S& s) const;

	void Erase(PathNode<S>* p);
	void Erase(const S& s);

	void Clear(void);

	unsigned int Count(void) const;

private:
	void Next(unsigned int& idx) const;

	void Malloc(unsigned int size);
	void Expand(void);

	unsigned int Hash(const S& s) const;
	static unsigned int Prime(unsigned int limit);
	static unsigned int jenkins_one_at_a_time_hash(unsigned char *key, unsigned int key_len);

private:
	// Array for storing pointers
	std::vector< PathNode<S>* > m_tab;

	// Number of elements in array
	unsigned int m_cnt;
};


//
// Constructor
// initSize - initialize size of array
//
template <typename S>
HashSet<S>::HashSet(unsigned int initSize) : m_cnt(0)
{
	Malloc(initSize);
}

//
// Returns number of elements in hash array
//
template <typename S>
unsigned int HashSet<S>::Count(void) const
{
	return m_cnt;
}

//
// Inserts object pointed by "p" into the set.
// It is allowed to insert one object pointed by "p" only.
//
template <typename S>
unsigned int HashSet<S>::Insert(PathNode<S>* p)
{
unsigned int i, coll = 0;

	assert(p != NULL);
	assert(!Find(p)); // Duplications are not allowed!

	i = Hash(p->m_state);
	// Is there a colision in hash table
	while(m_tab[i] != NULL)
	{
		coll++;
		Next(i);
	}

	// Insert element into hash table
	m_tab[i] = p;
	m_cnt++;

	// Is the size of hash table sufficiently large
	if(m_cnt >= m_tab.size() / 2)
		Expand();
	
	return coll;
}

//
// Returns "true" if a state contained in object pointed by "p" is in the set.
// Otherwise it returns "false".
//
template <typename S>
bool HashSet<S>::Find(PathNode<S>* p) const
{
	assert(p != NULL);
	return (Find(p->m_state) != NULL);
}

//
// Returns pointer to object holding state "s", if state "s" is in the set. 
// Otherwise it returns NULL.
//
template <typename S>
PathNode<S>* HashSet<S>::Find(const S& s) const
{
unsigned int i;

	i = Hash(s);
	// Check possible colisions
	while(m_tab[i] != NULL)
	{
		if(s == m_tab[i]->m_state)
			return m_tab[i];
		Next(i);
	}
	return NULL;
}

//
// Erases element from hash table corespoinding to stated contained in object "p".
//
template <typename S>
void HashSet<S>::Erase(PathNode<S>* p)
{
unsigned int i, j, d;

	assert(p != NULL);
	assert(Find(p)); // Object "p" must be in hash table

	i = Hash(p->m_state);
	// Find the proper entry counting the possible pollisions 
	while(m_tab[i] != NULL)
	{
		if(p->m_state == m_tab[i]->m_state)
			break;
		Next(i);
	}
	m_tab[i] = NULL;
	m_cnt--;
		

	// Clean up 
	j = i;
	while(true)
	{
		// i = (i + 1) % m_tab.size();
		Next(i);
		if(m_tab[i] == NULL) // dzialka m_tab[i] jest pusta, koniec zgrupowanych elementow
			return;
		d = Hash(m_tab[i]->m_state);

		const bool b1 = (j <  d && d <= i);
		const bool b2 = (d <= i && i <  j);
		const bool b3 = (i <  j && j <  d);
		if(b1 || b2 || b3) // "d" lezy cyklicznie pomiedzy "j" oraz "i"
			continue;

		m_tab[j] = m_tab[i]; // Przesuniecie zapisu
		m_tab[i] = NULL; // Dzialka m_tab[i] staje sie dzialka pusta
		j = i;
	}
}

//
// Erases element from hash table with state "s".
//
template <typename S>
void HashSet<S>::Erase(const S& s)
{
PathNode<S> *p = Find(s);

	Erase(p);
}

template <typename S>
void HashSet<S>::Clear(void)
{
	for(size_t i = 0; i < m_tab.size(); i++)
		m_tab[i] = NULL;
}


//
// Allocates the proper size for hash table. "size" is suggested array size.
//
template <typename S>
void HashSet<S>::Malloc(unsigned int size)
{
	// Prawdziwy rozmiat tablicy jest liczba pierwsza wieksza od "size"
	size = Prime(size);
	assert(size > 0);
		
	m_tab.resize(size);
	for(size_t i = 0; i < m_tab.size(); i++)
		m_tab[i] = NULL;
}

//
// Dwukrotne zwiekszenie rozmiaru tablicy.
//
template <typename S>
void HashSet<S>::Expand(void)
{
std::vector< PathNode<S>* > tmp = m_tab;
const unsigned int oldSize = m_tab.size();

	printf("\n***EXPANDING-BEGIN (size=%d)***\n", oldSize); fflush(stdout);

	m_cnt = 0;
	Malloc(oldSize + 1);
	for(unsigned int i = 0; i < tmp.size(); i++)
	{
		if(tmp[i] != NULL)
			Insert(tmp[i]);
	}
	printf("\n***EXPANDING-END***\n"); fflush(stdout);
}

//
// Funkcja haszujaca. 
//
template <typename S>
unsigned int HashSet<S>::Hash(const S& s) const
{
const unsigned int wordNo = sizeof(S) / sizeof(unsigned char);

	// Tutaj klucz "key" traktowany jest jako tablica charow
	const unsigned int idx = jenkins_one_at_a_time_hash((unsigned char*)(&s), wordNo);
	return idx % m_tab.size();
}

//
// Zwraca najmniesza liczbe pierwsza (postaci 2^k - w) wieksza od limit
//
template <typename S>
unsigned int HashSet<S>::Prime(unsigned int limit)
{
// Wybrane liczby piersze
const unsigned int  prime[24] = {
			251, // 2^8  - 5
			509, // 2^9  - 3
			1021, // 2^10 - 3
			2039, // 2^11 - 9
			4093, // 2^12 - 3
			8191, // 2^13 - 1
			16381, // 2^14 - 3
			32749, // 2^15 - 19
			65521, // 2^16 - 15
		131071, // 2^17 - 1
		262139, // 2^18 - 5
		524287, // 2^19 - 1
		1048573, // 2^20 - 3
		2097143, // 2^21 - 9
		4194301, // 2^22 - 3
		8388593, // 2^23 - 15
		16777213, // 2^24 - 3
		33554393, // 2^25 - 39
		67108859, // 2^26 - 5
		134217689, // 2^27 - 39
		268435399, // 2^28 - 57
		536870909, // 2^29 - 3
	1073741789, // 2^30 - 35
	2147483647  // 2^31 - 1
	};

		
//		// Aby zawsze korzystac z pamieci virtualnej!
//		if(limit < P_BIG_ALLOC_MIN_REQUEST)
//			limit = P_BIG_ALLOC_MIN_REQUEST;

	if(limit < prime[0])
		return prime[0];

    for(size_t i = 0; i < sizeof(prime) / sizeof(unsigned int); i++)
	{
		if(prime[i] > limit)
			return prime[i];
	}
	assert(0); // Za duzy rozmiar tablicy!
	return 0;
}


//
// Wybitnie dobra funkcja haszujaca. Patrz WIKIPEDIA (haslo: Hash Table)
//
template <typename S>
unsigned int HashSet<S>::jenkins_one_at_a_time_hash(unsigned char *key, unsigned int key_len)
{
unsigned int i, hash = 0;
 
	for (i = 0; i < key_len; i++)
	{
		hash += key[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash;
}

template <typename S>
inline
void HashSet<S>::Next(unsigned int& idx) const
{
	idx = (idx + 1) % m_tab.size();

/*
	idx++;
	const unsigned int size = m_tab.size();
	const unsigned int mul = (idx == size);
	assert(mul == 0 || mul == 1);
	idx = idx - size * mul; // Even more Faster?
*/
}


#endif
