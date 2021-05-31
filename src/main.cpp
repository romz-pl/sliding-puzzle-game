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
#include <iostream>


void Intro();
void RunAstar( const State& beg );

State Example(int id)
{
    if(id == 1)
    {
        const std::array< char, State::TILENO > tab{
         2,  8,  3,  5,  9,
         1,  6,  7,  4,  0, 
        11, 12, 13, 14, 10,
        16, 17, 18, 19, 15,
        21, 22, 23, 24, 20,
        };

        return State{ tab };
    }
    else if(id == 2)
    {
        const std::array< char, State::TILENO > tab{
         1,  7,  2,  8,  4,
         6,  9, 13,  3,  5,
        11, 17, 12, 14, 10,
        16, 18, 23, 22, 15,
        21, 24, 19, 20,  0,
        };

        return State{ tab };
    }
    else if(id == 3)
    {
        const std::array< char, State::TILENO > tab{
         1,  4,  3,  5, 10,
         6,  7,  8,  2,  9,
        23, 11, 13, 14, 15,
        12,  0, 18, 24, 19,
        17, 16, 21, 22, 20,
        };

        return State{ tab };
    }
    else if(id == 4)
    {
        const std::array< char, State::TILENO > tab{
         0,  6,  2,  9,  4,
        17,  1,  3, 10, 14,
        22,  8,  7, 12,  5,
        21, 11, 18, 13, 24,
        16, 23, 15, 20, 19,
        };

        return State{ tab };
    }
    else if(id == 5)
    {
        const std::array< char, State::TILENO > tab{
         2,  3,  7,  9,  4,
        11,  1, 14,  5, 10,
        12, 17, 15, 19,  8,
        22,  6, 13,  0, 23,
        16, 21, 18, 24, 20,
        };

        return State{ tab };
    }

    

    throw "Example not available";
}


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


    State beg = Example( 5 );
    //beg.Read( argv[ 1 ] );

    RunAstar( beg );
    
    return 0;
}


void RunAstar( const State& beg )
{
    Astar as;
    Graph graph;
    std::vector<State> path;
    bool pathFound;


    std::cout << "SELECTED-BEGIN-STATE:\n";
    beg.Print(stdout);
    std::cout << "\n\nComputing...";

    pathFound = as.Find(graph, beg, path);
    if(!pathFound)
    {
        std::cout << "Path NOT found for START state:\n";
        beg.Print(stdout);
        return;
    }
    std::cout << "...Ok\n";
    const size_t stateNo = path.size();
    as.PrintStats();

    std::cout << "\nFINAL-NUMBER-OF-STATES:\n";
    std::cout << "   Closed-set... = " << as.ClosedNo() << "\n";
    std::cout << "   Open-set..... = " << as.OpenNo() << "\n\n";

    std::cout << "NUMBER-OF-STATES-IN-FOUND-PATH = " << ( stateNo - 1 ) << "\n\n";

    std::cout << "FOUND-MOVES: ";
    for(size_t i = 0; i < stateNo; i++)
    {
        if(i < stateNo - 1)
            path[i + 1].PrintDiff(path[i]);
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

