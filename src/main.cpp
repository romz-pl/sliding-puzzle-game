//
// AUTHOR: Zbigniew Romanowski
//         romz@wp.pl
//
//
// This program solves Sliding puzzle for the board of size 5x5, i.e. puzzle 24 game.
//
    

// This macro must be defined before including "astar.h"
// #define ASTAR_STATISTICS

#include "astar.h"
#include "Graph.h"
#include "Examples.h"
#include <iostream>


void Intro();
void RunAstar( const State& beg );

int main(int /*argc*/, char** /*argv*/)
{
    Intro( );

    Examples examples;

    for(const State& s : examples)
    {
        RunAstar( s );
    }
    
    return 0;
}


void RunAstar( const State& beg )
{
    Astar as;
    Graph graph;
    bool pathFound;


    std::cout << "SELECTED-BEGIN-STATE:\n";
    beg.Print(stdout);
    std::cout << "\nComputing..." << std::flush;

    const std::optional<std::vector<State>> path = as.Find(graph, beg);
    if(!path.has_value())
    {
        std::cout << "Path NOT found for START state:\n";
        return;
    }
    std::cout << "Ok\n";

#ifdef ASTAR_STATISTICS
    as.PrintStats();
    std::cout << "\nFINAL-NUMBER-OF-STATES:\n";
    std::cout << "   Closed-set... = " << as.ClosedNo() << "\n";
    std::cout << "   Open-set..... = " << as.OpenNo() << "\n\n";

    std::cout << "NUMBER-OF-STATES-IN-FOUND-PATH = " << ( path.value().size() - 1 ) << "\n\n";
#endif

    const size_t stateNo = path.value().size();
    std::cout << "SOLUTION (" << stateNo - 1 << "): ";
    for(size_t i = 0; i < stateNo - 1; i++)
    {
        path.value()[i + 1].PrintDiff(path.value()[i]);
    }

    std::cout << "\n";

    constexpr bool show_states{ false };
    if constexpr(show_states)
    {
        for(size_t i = 0; i < path.value().size(); i++)
        {
            path.value()[i].Print(stdout);
            std::cout << "\n\n";
        }
    }

}


void Intro()
{
    std::cout << "===============================================================================\n";
    std::cout << " AAAAA  SSSSS TTTTT AAAAA  RRRRR   Zbigniew ROMANOWSKI  \n";
    std::cout << " A   A  S       T   A   A  R   R                        \n";
    std::cout << " AAAAA  SSSSS   T   AAAAA  RRRRR                        \n";
    std::cout << " A   A      S   T   A   A  R  R    romz@wp.pl           \n";
    std::cout << " A   A  SSSSS   T   A   A  R   R                        \n";
    std::cout << "===============================================================================\n\n";
    std::cout << " This program solves 24-puzzle problem.\n";
    std::cout << " It uses A* (A-star) with Manhattan metric to find the solution.\n";
    std::cout << " Open set and closed set of A* are implemented as exensible hash arrays.\n";
    std::cout << "===============================================================================\n\n";
}

