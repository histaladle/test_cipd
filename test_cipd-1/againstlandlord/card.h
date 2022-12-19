#ifndef CARD_H
#define CARD_H
#include <vector>
#include <map>
namespace fal
{



class Card
{
public:
    enum Suit
    {
        ErrorSuit=-1,
        UnknownSuit=0,
        Spade=1,
        Heart,
        Club,
        Diamond,
    };
    enum Color
    {
        ErrorColor=-1,
        UnknownColor=0,
        Black,
        Red,
    };

    int suit=0;
    int point=0;

    bool operator==(const Card card)
    {
        bool ok;
        ok = card.point==this->point&&card.suit==this->suit;
        return ok;
    }

    std::string getText()
    {
        std::string s;
        if(textMap.find(point)!=textMap.end()) {
            s=textMap[point];
        }

        return s;
    }

    int getColor()
    {
        int color=-1;
        if(suit==Spade||suit==Club) {
            color=Black;
        }
        else if(suit==Heart||suit==Diamond) {
            color=Red;
        }
        else {
            color=ErrorColor;
            if(point==VICE_JOKER_POINT) {
                color=Black;
            }
            else if(point==JOKER_POINT){
                color=Red;
            }
        }
        return color;
    }
    std::string getSuitText()
    {
        std::string s;
        if(suitTextMap.find(suit)!=suitTextMap.end()) {
            s=suitTextMap[suit];
        }

        return s;
    }
    static const int JOKER_POINT;
    static const int VICE_JOKER_POINT;
    static std::map<int,std::string> textMap;
    static std::map<int,std::string> suitTextMap;
};
extern void sort(std::vector<Card> &cards);

}
#endif // CARD_H
