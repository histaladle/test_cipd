#ifndef ROUND_H
#define ROUND_H

#include "card.h"
#include "enviroment.h"
#include <map>
namespace fal {

class Round
{
public:
    Round();
    std::pair<int,std::vector<fal::Card> > records[PLAYER_NUM];
};

}

#endif // ROUND_H
