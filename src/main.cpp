//
// AUTHOR: Zbigniew Romanowski
//         romz@wp.pl
//
//
// This program solves Sliding puzzle for the board of size 5x5, i.e. puzzle 24 game.
//
    

// This must be defined befor including "astar.h"
#define ASTAR_STATISTICS

#include "astar.h"
#include "Graph.h"
#include "Examples.h"
#include <iostream>


void Intro();
void RunAstar( const State& beg );

int main(int argc, char* argv[])
{
    Intro( );

    /*if( argc != 2 )
    {
        std::cout << "Invalid number of parameters.\n";
        std::cout << "Provide file name for the initial state\n";
        return 1;
    }
    */

    Examples examples;

    RunAstar( examples.Get(2) );
    
    return 0;
}


void RunAstar( const State& beg )
{
    Astar as;
    Graph graph;
    bool pathFound;


    std::cout << "SELECTED-BEGIN-STATE:\n";
    beg.Print(stdout);
    std::cout << "\n\nComputing...";

    const std::optional<std::vector<State>> path = as.Find(graph, beg);
    if(!path.has_value())
    {
        std::cout << "Path NOT found for START state:\n";
        beg.Print(stdout);
        return;
    }
    std::cout << "...Ok\n";
    const size_t stateNo = path.value().size();
    as.PrintStats();

    std::cout << "\nFINAL-NUMBER-OF-STATES:\n";
    std::cout << "   Closed-set... = " << as.ClosedNo() << "\n";
    std::cout << "   Open-set..... = " << as.OpenNo() << "\n\n";

    std::cout << "NUMBER-OF-STATES-IN-FOUND-PATH = " << ( stateNo - 1 ) << "\n\n";

    std::cout << "FOUND-MOVES: ";
    for(size_t i = 0; i < stateNo; i++)
    {
        if(i < stateNo - 1)
            path.value()[i + 1].PrintDiff(path.value()[i]);
    }
    std::cout << "\n";


    /*for(size_t i = 0; i < path.size(); i++)
    {
        path[i].Print(stdout);
        std::cout << "\n\n";
    }*/ 

    
    // printf("\n***** Calculations completed successfully! *****\n\n");
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

