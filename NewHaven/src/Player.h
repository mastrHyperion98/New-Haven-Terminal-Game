#include "VGMap.h"
#include "Resources.h"
#include "ScoreCalculator.h"
#include "ResourceTracker.h"
#include <string>
struct Player
{
public:
    Player(string id);
    Player(const Player &player);
    ~Player();
    Player &operator = (const Player &player);
    // cannot implement yet. Requires the game_controller / main-loop / logic controller to be a singleton with references to the game_board
    int placeHarvestTile();
    // Used for shipment tile
    int placeShipmentTile();

    // cannot implement yet. Requires the game_controller / main-loop / logic controller to be a singleton with references to the building deck
    void drawBuilding(Building* building);
    // cannot implement yet. Requires the game_controller / main-loop / logic controller to be a singleton with references to the harvest tile
    void drawHarvestTile(HarvestTile* tile);
    void drawBuildingPool(Building*);
    // Returns the ResourceTracker object held by the player
    ResourceTracker* resourceTracker();
    bool buildVillage();
    void calculateResources(ResourceTrails);
    void setVillage(VGMap);
    // Used to set the shipment tile in Player's hand
    void setShipmentTile(HarvestTile* shipmentTile);
    void setShipmentContent(ResourceTypes *type);
    // Getter for shipment tile
    HarvestTile* getShipmentTile();
    string getID();
    void setShipmentPlayed();
    bool isShipmentPlayed();
private:
    VGMap *village;
    ResourceTracker *resource_score;
    ScoreCalculator *vb_score;
    Hand *my_hand;
    string *id;
};
