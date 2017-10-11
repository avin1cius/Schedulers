#include "main.hpp"

int main( int argc, char *argv[ ] )
{
    std::string filename;

    Process process;
    std::vector<Process> vecProcess;
    vecProcess.reserve( 10 );
    
    if ( argc == 1 )
    {
        filename = "input.txt";
    }
    else
    {
        filename = argv[1];
    }

    std::ifstream file( filename );

    if ( file.is_open() )
    {
        int i, j;
        while ( file >> i >> j )
        {
            process.arrive_time_ = i;
            process.duration_ = j;
                
            vecProcess.push_back( process );
        }
        file.close();
    }
    else
    {
        std::cout << filename << " não encontrado" << std::endl;
        return 0;
    }

    std::sort( vecProcess.begin(), vecProcess.end(), CompareProcesses ); //Sorting by arrive time
    
    for ( int i = 0; i < (int)vecProcess.size(); i++ )
    {
        vecProcess[i].id_ = i;
    }

    PrintMetrics( "FCFS", FCFS( vecProcess ) );

    PrintMetrics( "SJF", SJF( vecProcess ) );

    PrintMetrics( "RR", RR( vecProcess, 2 ) );

    return 0;
}
