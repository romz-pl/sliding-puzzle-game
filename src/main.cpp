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
#include "graphp25.h"
#include <iostream>


void Intro();
void RunAstar( const StateP25& beg );

StateP25 Example01()
{
    std::array< char, StateP25::TILENO > tab{
     2,  8,  3,  5,  9,
     1,  6,  7,  4,  0, 
    11, 12, 13, 14, 10,
    16, 17, 18, 19, 15,
    21, 22, 23, 24, 20,
    };

    return StateP25{ tab };
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


    StateP25 beg = Example01();
    //beg.Read( argv[ 1 ] );

    RunAstar( beg );
	
    return 0;
}


void RunAstar( const StateP25& beg )
{
    Astar<GraphP25> as;
    GraphP25 graph;
    StateP25::Cost cost;
    std::vector<StateP25> path;
    bool pathFound;


    std::cout << "SELECTED-BEGIN-STATE:\n";
	beg.Print(stdout);
    std::cout << "\n\nComputing...";

	pathFound = as.Find(graph, beg, path, cost);
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

    std::cout << "FOUND-MOVES:\n";
	for(size_t i = 0; i < stateNo; i++)
	{
		if(i < stateNo - 1)
			path[i + 1].PrintDiff(path[i]);

		if((i+1) % 10 == 0)
            std::cout << "\n";
	}

	
    // printf("\n\nCALCULATION-TIME = %d second(s)\n\n", as.FindTime());
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
    std::cout << " Open set and closed set of A* are implemented as STL containers.\n";
    std::cout << "===============================================================================\n\n";
}

