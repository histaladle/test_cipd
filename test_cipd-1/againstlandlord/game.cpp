#include "game.h"
#include <cstdlib>
#include <ctime>
#include <QDebug>
using namespace fal;
Game::Game()
{
    long long seed;
    seed=time(nullptr);
    srand(uint32_t(seed));

    int suit;
    fal::Card card;

    for(int i=3;i<=14;i++) {
        for(int j=Card::Spade;j<=Card::Diamond;j++) {
            card.suit=j;
            card.point=i;
            initializedCards.push_back(card);
        }
    }
    card.point=20;
    for(int j=Card::Spade;j<=Card::Diamond;j++) {
        card.suit=j;
        initializedCards.push_back(card);
    }
//    suit=Card::Spade;
//    for(int i=3;i<=13;i++) {
//        card.suit=suit;
//        card.point=i;
//        initializedCards.push_back(card);
//    }
//    card.point=14;
//    initializedCards.push_back(card);
//    card.point=20;
//    initializedCards.push_back(card);

//    suit=Card::Heart;
//    for(int i=3;i<=13;i++) {
//        card.suit=suit;
//        card.point=i;
//        initializedCards.push_back(card);
//    }
//    card.point=14;
//    initializedCards.push_back(card);
//    card.point=20;
//    initializedCards.push_back(card);

//    suit=Card::Club;
//    for(int i=3;i<=13;i++) {
//        card.suit=suit;
//        card.point=i;
//        initializedCards.push_back(card);
//    }
//    card.point=14;
//    initializedCards.push_back(card);
//    card.point=20;
//    initializedCards.push_back(card);

//    suit=Card::Diamond;
//    for(int i=3;i<=13;i++) {
//        card.suit=suit;
//        card.point=i;
//        initializedCards.push_back(card);
//    }
//    card.point=14;
//    initializedCards.push_back(card);
//    card.point=20;
//    initializedCards.push_back(card);

    card.point=fal::Card::VICE_JOKER_POINT;
    card.suit=Card::UnknownSuit;
    initializedCards.push_back(card);
    card.point=fal::Card::JOKER_POINT;
    card.suit=Card::UnknownSuit;
    initializedCards.push_back(card);

    int cardsum=int(initializedCards.size());
    for(int i=0;i<PLAYER_NUM;i++) {
        players[i]=new Player();
        players[i]->cards=takeCard((cardsum-COVER_CARD_NUM)/PLAYER_NUM);
    }
    int lucky=rand()%PLAYER_NUM;
    players[lucky]->cards.insert(players[lucky]->cards.end(),initializedCards.begin(),initializedCards.end());
}

std::vector<fal::Card> Game::takeCard(int num)
{
    size_t cardnum;
    int rem;
    Card card;
    std::vector<Card> cards;
//    for(int i=0;i<num;i++) {
//        if(initializedCards.size()==0) {
//            break;
//        }
//        cardnum=initializedCards.size();
//        rem=rand()%int(cardnum);
//        card=initializedCards[size_t(rem)];
//        initializedCards.erase(initializedCards.begin()+rem);
//        cards.push_back(card);
//    }

    for(int i=0;i<num;i++) {
        if(initializedCards.size()==0) {
            break;
        }
        card=*(initializedCards.begin());
        initializedCards.erase(initializedCards.begin());
        cards.push_back(card);
    }
    return cards;
}

