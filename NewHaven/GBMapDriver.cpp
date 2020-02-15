#include <iostream>
#include <boost/graph/graph_utility.hpp>
#include "src/GBMap.h"
#include "src/Resources.h"

using namespace std;

int main() {
    GBMap *map = new GBMap();
    int configuration = 0;
    cout << "Enter the board configuration (0 = 2 players, 1 = 3 players, 2 = 4 players): ";
    cin >> configuration;
    map->setBoardConfig(configuration);
    cout << "\n***Generate Graph***\n" << endl;
    map->generateGraph();
    cout << "\n***PRINT GRAPH***\n" << endl;
    map->printGraph();
    cout << "\n***Print Connected Components***\n" << endl;
    map->printConnectedGraph();

    // loop and create a trail of 5 resources that the user can place
    HarvestTile* tile = {new HarvestTile[5]};
    cout << "TESTING HARVEST TRAILS AND PLAYER OWNED RESOURCES FOR A TURN: ALL SQUARES ARE CURRENTLY EMPTY\n";
    cout << "\n4 player board layout:\n -  25 26 27 28 29 --\n35 00 01 02 03 04 40\n36 05 06 07 08 09 41\n37 10 11 12 13 14 42\n"<<
            "38 15 16 17 18 19 43\n39 20 21 22 23 24 44\n-  30 31 32 33 34 -" << endl;
    for(int i = 0; i < 5; i++) {
        int position;
        cout << "PLAY A HARVEST TILE AT SQUARE #: ";
        cin >>  position;
        try{
        if(position >= *map->SIZE || position < 0) {
            throw 2;
        }
            (*map).getSquare(position)->setTile(&tile[i]);
            ResourceTrails trail = map->getConnectedGraph(position);
            ResourceTrails::vertex_iterator vertexIt, vertexEnd;
            ResourceTrails::adjacency_iterator neighbourIt, neighbourEnd;
            tie(vertexIt, vertexEnd) = vertices(trail);
            for (; vertexIt != vertexEnd; ++vertexIt) {
                cout << trail[*vertexIt].getPosition() << " is connected with ";
                tie(neighbourIt, neighbourEnd) = adjacent_vertices(*vertexIt, trail);
                for (; neighbourIt != neighbourEnd; ++neighbourIt)
                    cout << trail[*neighbourIt].getPosition() << " ";
                cout << "\n";
            }
        }catch(int e){
            if(e==1)
                cout << "\nERROR: Tile " << position << " already contains a tile!" << endl;
            if(e==2)
                cout<< "\nERROR INVALID POSITION INDEX\n";
            i--;
        }
    }
    // clear up memory
    delete map;
    delete[] tile;

    return 0;
}
