#ifndef ASTAR_MEMMGR_H
#define ASTAR_MEMMGR_H

//
// AUTHOR: Zbigniew Romanowski
//         romz@wp.pl
// ***  PART OF A-STAR ALGORITHM  *** 
//
//
// ---------------------------------------------------------------------------------
//      D E S C R I P T I O N
// ---------------------------------------------------------------------------------
// 1. Memory Manager used by A* algorithm
//
// 2. Allocates memory in large chunks avoiding memeory defragmentation.
// 
// 3. Open-set and Closed-set in A-Star algorithms uses pointers only.
//    Memory manager simplyfies realizing the memory.
//
// 4. Allocated memory is stores as the vector of chunks.
//
// 5. The size of the chunk is a parameter of memory menager constructor.
//
// 6. Initially there are 100 chunks.
//

#include <cassert>

template<typename T>
class MemMgr
{
public:
    explicit MemMgr(unsigned int chunkSize);
    ~MemMgr(void);

    T* New(void);
    void Erase(void);

private:
    // Size of the m_chunkSize, i.e. size of the array pointed by element of m_tab
    const unsigned int m_chunkSize;

    // Id of chunk with the first free object
    unsigned int m_chunk;

    // Id of row with the first free object
    unsigned int m_row;

    // Vector of pointers. Each element of vector points to an array.
    std::vector<T*> m_tab;
};


//
// Constructor
// eltNo - initial size of array
//
template<typename T>
MemMgr<T>::MemMgr( unsigned int chunkSize )
    : m_chunkSize( chunkSize )
    , m_chunk( 0 )
    , m_row( 0 )
    , m_tab( 100 )
{
    m_tab[ 0 ] = new T[ chunkSize ];
}

//
// Destructor
//
template<typename T>
MemMgr<T>::~MemMgr(void)
{
    for(unsigned int i = 0; i < m_tab.size(); i++)
        delete [] m_tab[i];
}

//
// Increase the size of array. New element is added to the end of array.
//
template<typename T>
T* MemMgr<T>::New(void)
{
    m_row++; // Take next free row

    if(m_row == m_chunkSize)
    {
        // Create new m_chunkSize
        T* p = new T[m_chunkSize];
        assert(p);
        m_tab.push_back(p);

        // Jump to begin of the next chunk
        m_chunk++;
        m_row = 0;
    }

    return &(m_tab[m_chunk][m_row]);
}

//
// Deletes all objects. Afer calling this function there is not allocated memory.
//
template<typename T>
void MemMgr<T>::Erase(void)
{
    // Index "i" starts from (1) ONE!!!
    for(unsigned int i = 1; i < m_tab.size(); i++)
        delete [] m_tab[i];

    m_tab.resize(1);
    m_chunk = 0;
    m_row = 0;
}

#endif
