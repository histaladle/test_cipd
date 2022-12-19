#include "card.h"
namespace fal {
const int Card::VICE_JOKER_POINT=99;
const int Card::JOKER_POINT=100;
void sort(std::vector<Card> &cards)
{
    if(cards.size()==0) {
        return;
    }
    for(size_t i=cards.size()-1;i>0;i--) {
        for(size_t j=0;j<i;j++) {
            if(cards[j].point>cards[i].point) {
                std::swap(cards[j],cards[i]);
            }
            else if(cards[j].point==cards[i].point) {
                if(cards[j].suit>cards[i].suit) {
                    std::swap(cards[j],cards[i]);
                }
            }
        }
    }
}

std::map<int,std::string> Card::textMap={
    { 3, "3"},
    { 4, "4"},
    { 5, "5"},
    { 6, "6"},
    { 7, "7"},
    { 8, "8"},
    { 9, "9"},
    {10,"10"},
    {11, "J"},
    {12, "Q"},
    {13, "K"},
    {14, "A"},
    {20, "2"},

    {VICE_JOKER_POINT,"JOKE"},
    {JOKER_POINT,"JOKER"},
};

std::map<int,std::string> Card::suitTextMap={
    {  Spade,"♠"},
    {  Heart,"♥"},
    {   Club,"♣"},
    {Diamond,"♦"},
};
}

