#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include <vector>
#include <mutex>
namespace fal {

class Player
{
public:
    Player();
    ~Player()
    {
        countMutex.lock();
        --count;
        countMutex.unlock();
    }
    std::vector<fal::Card> cards;
    const int id;
    static int count;
    static std::mutex countMutex;
private:
};

}
#endif // PLAYER_H
