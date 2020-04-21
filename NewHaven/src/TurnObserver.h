//
// Created by hyperion on 2020-04-21.
//

#ifndef NEWHAVEN_TURNOBSERVER_H
#define NEWHAVEN_TURNOBSERVER_H

#include "GameObservers.h"
#include <string>
#include <map>
#include "Player.h"

class TurnObserver: public Observer {
public:
    TurnObserver();
    ~TurnObserver();
    // update function override
    virtual void update();
private:
    Player *current;
    std::map<ResourceTypes, std::uint_least16_t> *scores;
    void printTurnStart();
    void printPlayingHarvestTile();
    void printPlayedHT();
    void printBV();
};


#endif //NEWHAVEN_TURNOBSERVER_H
