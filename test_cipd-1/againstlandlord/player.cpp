#include "player.h"
using namespace fal;
int Player::count=0;
std::mutex Player::countMutex;
Player::Player() : id(count)
{
    countMutex.lock();
    ++count;
    countMutex.unlock();
}
