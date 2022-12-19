#ifndef GAME_H
#define GAME_H
#include "card.h"
#include "combination.h"
#include "vector"
#include "player.h"
#include "enviroment.h"
namespace fal {

class Game
{
public:
    Game();
    ~Game()
    {
        for(int i=0;i<PLAYER_NUM;i++) {
            delete players[i];
        }
    }
    std::vector<fal::Card> takeCard(int num=1);
    Player *players[PLAYER_NUM]={nullptr};
private:
    std::vector<fal::Card> initializedCards;
};

}


#endif // GAME_H
