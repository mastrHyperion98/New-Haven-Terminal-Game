//
// Created by Muher on 2020-02-18.
//
#include <iostream>
#include <boost/graph/graph_utility.hpp>
#include "../src/GBMap.h"
#include "../src/Resources.h"
#include "../src/Calculations.h"

using namespace std;

int main() {
    int configuration = 0;
    GBMap* map = nullptr;
    input_configuration:
    //executes loop if the input fails (e.g., no characters were read)
    while (cout << "Enter the board configuration (0 = 2 players, 1 = 3 players, 2 = 4 players): " && !(cin >> configuration)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    try {
        map = new GBMap(configuration);
    }catch(int e){
        cout << "ERROR: " << configuration << " is not a correct option: Please select 0, 1 or 2\n";
        // if incorrect input jump to input_config;
        goto input_configuration;
    }
    cout << "\n***PRINT GRAPH***\n" << endl;
    map->printGraph();
    cout << "\n***Print Connected Components***\n" << endl;
    map->printConnectedGraph();

    // loop and create a trail of 5 resources that the user can place
    HarvestTile* tile = {new HarvestTile[5]};
    cout << "TESTING HARVEST TRAILS AND PLAYER OWNED RESOURCES FOR A TURN: ALL SQUARES ARE CURRENTLY EMPTY\n";
    map->printIndexConfiguration();

    ResourcesCollected *resourceCalculator = new ResourcesCollected();

    for(int i = 0; i < 5; i++) {
        int position;
        while (cout << "PLAY A HARVEST TILE AT SQUARE #: " && !( cin >>  position)) {
            std::cin.clear(); //clear bad input flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
            std::cout << "Invalid input; please re-enter.\n";
        }
        // to keep track of current tile position
        resourceCalculator->position = position;
        try{
            if(position >= *map->SIZE || position < 0) {
                throw 2;
            }
            // loop through the entire resource trail and show the Square position and
            // show the out going edges
            (*map).getSquare(position).setTile(&tile[i]);

            // Returns the tile content to calculate the resources
            //resourceCalculator->resourceType = tile[i].getTileContent();

            resourceCalculator->tiles[resourceCalculator->position] = tile[i].getTileContent();
            resourceCalculator->mapSize = *map->SIZE;

            ResourceTrails trail = map->getConnectedGraph(position);
            ResourceTrails::vertex_iterator vertexIt, vertexEnd;
            ResourceTrails::adjacency_iterator neighbourIt, neighbourEnd;

            vector<int> connectedNodes;

            tie(vertexIt, vertexEnd) = vertices(trail);
            for (; vertexIt != vertexEnd; ++vertexIt) {
                cout << trail[*vertexIt].getPosition() << " is connected with ";
                // array of connected tiles
                connectedNodes.push_back(trail[*vertexIt].getPosition());

                tie(neighbourIt, neighbourEnd) = adjacent_vertices(*vertexIt, trail);
                for (; neighbourIt != neighbourEnd; ++neighbourIt)
                    cout << trail[*neighbourIt].getPosition() << " ";
                cout << "\n";
            }
            resourceCalculator->connectedNodes = connectedNodes;
            resourceCalculator->calculateResourcesCollected();
        }catch(int e){
            if(e==1)
                cout << "\nERROR: Tile " << position << " already contains a tile!" << endl;
            if(e==2)
                cout<< "\nERROR INVALID POSITION INDEX\n";
            i--;
        }
    }

    delete map;
    delete[] tile;

    return 0;
}