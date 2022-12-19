#ifndef COMBINATION_H
#define COMBINATION_H

#include "card.h"
#include <vector>
namespace fal {

class Combination
{
public:
    enum CombinationType {
        ErrorCombination=-1,
        UnknownCombination=0,
        Single,
        Pair,
        Three,
        Straight,
        PairStraight,
        Airplane,
        FourWithTwo,
        Bomb,
        JokerBomb,
    };
    enum ComparedResult {
        ErrorComparison=-1,
        Equal,
        Less,
        Greater,
    };

    Combination(std::vector<fal::Card> cards);
    ~Combination();
    static int compare(Combination comb1,Combination comb2);
    static void sort(std::vector<fal::Card> &cards);
    static void sortInPlay(std::vector<fal::Card> &cards);
    static std::map<int,int> statistics(std::vector<fal::Card> cards);
    int getCombinationType(std::vector<fal::Card> &primeCards);
    int getCombinationType();

//    void probe(std::vector<fal::Card> &cards,std::vector<std::vector<fal::Combination> > &combs,int combtype);
    std::vector<fal::Card> cards;
};

}
#endif // COMBINATION_H
