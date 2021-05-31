//
// AUTHOR: Zbigniew Romanowski
//         romz@wp.pl
//
//
// ---------------------------------------------------------------------------------
//      D E S C R I P T I O N
// ---------------------------------------------------------------------------------
// 1. Demonstration program of A-STAR algorithm.
//
// 2. It finds the solution for 25-Puzzle game for selected initial positions.
//
// 3. Selected positions are sorted according to lenth of searched state space.
//
// 4. Two GiB of memory is required for 0,1,2,3,4,6 configurations.
//
// 5. Sixteen GiB of memory is required for 6-th configuration.
//


// This must be defined befor including "astar.h"
#define ASTAR_STATISTICS

#include "astar.h"
#include "graphp25.h"
#include <iostream>


void Intro();
void RunAstar( const StateP25& beg );

int main(int argc, char* argv[])
{
    Intro( );

    if( argc != 2 )
    {
        std::cout << "Invalid number of parameters.\n";
        std::cout << "Provide file name for the initial state\n";
        return 1;
    }


    StateP25 beg;
    beg.Read( argv[ 1 ] );

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

