#include "combination.h"
#include <map>
#include <QDebug>
using namespace fal;
Combination::Combination(std::vector<fal::Card> cards)
{
    this->cards=cards;
}

int Combination::getCombinationType(std::vector<fal::Card> &primeCards)
{
    if(cards.size()==0){
        return -1;
    }
    int res=0;
    std::map<fal::Card,int> cardcounts;
    std::map<int,int> pointcounts;
    pointcounts=statistics(cards);
    if(cards.size()==1) {
        res=Single;
        primeCards=cards;
        fal::sort(primeCards);
    }
    else if(cards.size()==2) {
        if(pointcounts.size()==1)
        {
            res=Pair;
            primeCards=cards;
            fal::sort(primeCards);
        }
        else if(pointcounts.find(Card::JOKER_POINT)!=pointcounts.end()
                && pointcounts.find(Card::VICE_JOKER_POINT)!=pointcounts.end()) {
            res=JokerBomb;
            primeCards=cards;
            fal::sort(primeCards);
        }
        else
        {
            res=ErrorCombination;
            primeCards.clear();
        }
    }
    else if(cards.size()==3)
    {
        if(pointcounts.size()==1) {
            res=Three;
            primeCards=cards;
            fal::sort(primeCards);
        }
        else {
            res=ErrorCombination;
            primeCards.clear();
        }
    }
    else if(cards.size()==4) {
        if(pointcounts.size()==1) {
            res=Bomb;
            primeCards=cards;
            fal::sort(primeCards);
        }
        else if(pointcounts.size()==2){
            int maxcount=0;
            for (auto it=pointcounts.begin();it!=pointcounts.end();it++) {
                if(maxcount<it->second)
                {
                    maxcount=it->second;
                }
            }
            if(maxcount==3)
            {
                res=Three;
                primeCards.clear();
                for(size_t i=0;i<cards.size();i++) {
                    if(pointcounts[cards[i].point]==3) {
                        primeCards.push_back(cards[i]);
                    }
                }
                fal::sort(primeCards);
            }
            else {
                res=ErrorCombination;
                primeCards.clear();
            }
        }
        else {
            res=ErrorCombination;
            primeCards.clear();
        }
    }
    else if(cards.size()==5)
    {
        if(pointcounts.size()==2) {
            res=Three;
            int maxcount=0;
            for (auto it=pointcounts.begin();it!=pointcounts.end();it++) {
                if(maxcount<it->second)
                {
                    maxcount=it->second;
                }
            }
            if(maxcount==3) {
                res=Three;
                primeCards.clear();
                for(size_t i=0;i<cards.size();i++) {
                    if(pointcounts[cards[i].point]==3) {
                        primeCards.push_back(cards[i]);
                    }
                }
                fal::sort(primeCards);
            }
            if(maxcount==4) {
                res=FourWithTwo;
                primeCards.clear();
                for(size_t i=0;i<cards.size();i++) {
                    if(pointcounts[cards[i].point]==4) {
                        primeCards.push_back(cards[i]);
                    }
                }
                fal::sort(primeCards);
            }
        }
        else if(pointcounts.size()==5) {
            std::vector<fal::Card> cs=cards;
            fal::sort(cs);
            res=Straight;
            primeCards.clear();
            primeCards=cards;
            fal::sort(primeCards);
            for(size_t i=0;i<cs.size()-1;i++) {
                if(cs[i].point+1!=cs[i+1].point) {
                    res=ErrorCombination;
                    primeCards.clear();
                    break;
                }
            }
//            if(pointcounts.find(2)!=pointcounts.end()) {
//                res=-1;
//            }
        }
        else {
            res=ErrorCombination;
            primeCards.clear();
        }
    }
    else {
        int maxcount=0;
        int mincount=INT_MAX;
        for (auto it=pointcounts.begin();it!=pointcounts.end();it++) {
            if(maxcount<it->second) {
                maxcount=it->second;
            }
            if(mincount>it->second) {
                mincount=it->second;
            }
        }
        if(maxcount==1) {
            std::vector<fal::Card> cs=cards;
            fal::sort(cs);
            res=Straight;
            primeCards=cards;
            fal::sort(primeCards);
            for(size_t i=0;i<cs.size()-1;i++) {
                if(cs[i].point+1!=cs[i+1].point) {
                    res=ErrorCombination;
                    primeCards.clear();
                    break;
                }
            }
//            if(pointcounts.find(2)!=pointcounts.end()) {
//                res=-1;
//            }
        }
        else if(maxcount==2) {
            res=PairStraight;
            std::vector<int> pairnums;
            for(auto it=pointcounts.begin();it!=pointcounts.end();it++) {
                if(it->second==2) {
                    pairnums.push_back(it->first);
                }
                else {
                    res=ErrorCombination;
                    pairnums.clear();
                    primeCards.clear();
                    break;
                }
            }
            for(size_t i=0;i<pairnums.size();i++) {
                if(pairnums[i]+1!=pairnums[i+1]) {
                    res=ErrorCombination;
                    primeCards.clear();
                    break;
                }
            }
        }
        else {
            res=ErrorCombination;
            primeCards.clear();

            // "airplane" with "wings"
            std::vector<int> threenums;
            // all numbers of can be "airplane"
            for(auto it=pointcounts.begin();it!=pointcounts.end();it++) {
                if(it->second>=3) {
                    threenums.push_back(it->first);
                }
            }
            // max continuous numbers(repeat>=3)
            do {
                std::sort(threenums.begin(),threenums.end());
                std::vector<std::vector<int> > contlists;
                std::vector<int> contlist;
                std::vector<int> maxcontlist;
                size_t left=0,right=1;
                if(threenums.size()<2) {
                    break;
                }
                while(left<threenums.size()&&right<threenums.size()) {
                    if(threenums[right]-1==threenums[right-1]) {
                    }
                    else {
                        contlist.insert(contlist.end(),threenums.begin()+int(left),threenums.begin()+int(right));
                        contlists.push_back(contlist);
                        contlist.clear();
                        left=right;
                    }
                    right++;
                    if(right>=threenums.size()) {
                        contlist.insert(contlist.end(),threenums.begin()+int(left),threenums.begin()+int(right));
                        contlists.push_back(contlist);
                        contlist.clear();
                        left=right;
                    }
                }
                size_t maxcontnum=0,maxcontindex=0;
                for(size_t i=0;i<contlists.size();i++) {
                    if(maxcontnum<=contlists[i].size()) {
                        maxcontnum=contlists[i].size();
                        maxcontindex=i;
                    }
                }
                if(contlists.empty()) {
                    break;
                }
                // max continuous cards(repeat>=3)
                std::vector<Card> cards1,threecards;
                if(maxcontnum) {
                    maxcontlist=contlists[maxcontindex];
                    cards1=cards;
                    int t=0;
                    for(size_t i=0;i<maxcontlist.size();i++) {
                        t=0;
                        for(size_t j=0;j<cards1.size();j++) {
                            if(cards1[j].point==maxcontlist[i]) {
                                if(t<3) {
                                    threecards.push_back(cards1[j]);
                                    cards1.erase(cards1.begin()+int(j));
                                    j--;
                                    t++;
                                }
                                else {
                                    break;
                                }
                            }
                        }
                    }
                    std::map<int,int> pointcounts1;
                    pointcounts1=statistics(cards1);
                    int attachnum=0;
                    int mincount1=INT_MAX,maxcount1=0;
                    for(auto it=pointcounts1.begin();it!=pointcounts1.end();it++) {
                        if(it->second>maxcount1) {
                            maxcount1=it->second;
                        }
                        if(it->second<mincount1) {
                            mincount1=it->second;
                        }
                    }
                    if(mincount1%2!=maxcount1%2) {
                        break;
                    }
                    if(mincount1%2) {
                        for(auto it=pointcounts1.begin();it!=pointcounts1.end();it++) {
                            attachnum+=it->second;
                        }
                    }
                    else {
                        for(auto it=pointcounts1.begin();it!=pointcounts1.end();it++) {
                            attachnum+=it->second/2;
                        }
                    }
                    if(size_t(attachnum)<=maxcontnum) {
                        res=Three;
                        primeCards=threecards;
                        fal::sort(primeCards);
                    }
                }
            }while(false);

            // "four with two"
            std::vector<int> fournums;
            // all numbers of can be "four"
            for(auto it=pointcounts.begin();it!=pointcounts.end();it++) {
                if(it->second>=4) {
                    fournums.push_back(it->first);
                }
            }
            // max continuous numbers(repeat>=4)
            do {
                std::sort(fournums.begin(),fournums.end());
                std::vector<std::vector<int> > contlists;
                std::vector<int> contlist;
                std::vector<int> maxcontlist;
                size_t left=0,right=1;
                if(fournums.size()<1) {
                    break;
                }
                if(fournums.size()<2) {
                    contlist.push_back(*(fournums.begin()));
                    contlists.push_back(contlist);
                }
                while(left<fournums.size()&&right<fournums.size()) {
                    if(fournums[right]-1==fournums[right-1]) {
                    }
                    else {
                        contlist.insert(contlist.end(),fournums.begin()+int(left),fournums.begin()+int(right));
                        contlists.push_back(contlist);
                        contlist.clear();
                        left=right;
                    }
                    right++;
                    if(right>=fournums.size()) {
                        contlist.insert(contlist.end(),fournums.begin()+int(left),fournums.begin()+int(right));
                        contlists.push_back(contlist);
                        contlist.clear();
                        left=right;
                    }
                }
                size_t maxcontnum=0,maxcontindex=0;
                for(size_t i=0;i<contlists.size();i++) {
                    if(maxcontnum<=contlists[i].size()) {
                        maxcontnum=contlists[i].size();
                        maxcontindex=i;
                    }
                }
                if(contlists.empty()) {
                    break;
                }
                // max continuous cards(repeat>=4)
                std::vector<Card> cards1,fourcards;
                if(maxcontnum) {
                    maxcontlist=contlists[maxcontindex];
                    cards1=cards;
                    int t=0;
                    for(size_t i=0;i<maxcontlist.size();i++) {
                        t=0;
                        for(size_t j=0;j<cards1.size();j++) {
                            if(cards1[j].point==maxcontlist[i]) {
                                if(t<4) {
                                    fourcards.push_back(cards1[j]);
                                    cards1.erase(cards1.begin()+int(j));
                                    j--;
                                    t++;
                                }
                                else {
                                    break;
                                }
                            }
                        }
                    }
                    std::map<int,int> pointcounts1;
                    pointcounts1=statistics(cards1);
                    int attachnum=0;
                    int mincount1=INT_MAX,maxcount1=0;
                    for(auto it=pointcounts1.begin();it!=pointcounts1.end();it++) {
                        if(it->second>maxcount1) {
                            maxcount1=it->second;
                        }
                        if(it->second<mincount1) {
                            mincount1=it->second;
                        }
                    }
                    if(mincount1%2!=maxcount1%2) {
                        break;
                    }
                    if(mincount1%2) {
                        for(auto it=pointcounts1.begin();it!=pointcounts1.end();it++) {
                            attachnum+=it->second;
                        }
                    }
                    else {
                        for(auto it=pointcounts1.begin();it!=pointcounts1.end();it++) {
                            attachnum+=it->second/2;
                        }
                    }
                    if(size_t(attachnum)<=maxcontnum*2) {
                        res=FourWithTwo;
                        primeCards=fourcards;
                        fal::sort(primeCards);
                    }
                }
            }while(false);
        }
    }
    return res;
}

void Combination::sortInPlay(std::vector<fal::Card> &cards)
{
    if(cards.size()==0) {
        return;
    }
    std::map<int,int> pointcounts;
    pointcounts=statistics(cards);
    int maxcount=0;
    for(auto it=pointcounts.begin();it!=pointcounts.end();it++) {
        if(maxcount<it->second) {
            maxcount=it->second;
        }
    }

    std::vector<fal::Card> cards1,cards2;
    for(size_t i=0;i<cards.size();i++) {
        if(pointcounts[cards[i].point]==maxcount) {
            cards1.push_back(cards[i]);
        }
        else {
            cards2.push_back(cards[i]);
        }
    }
    sort(cards1);
    sort(cards2);
    cards1.insert(cards1.end(),cards2.begin(),cards2.end());
    cards=cards1;
}

void Combination::sort(std::vector<fal::Card> &cards)
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

int Combination::compare(Combination comb1, Combination comb2)
{
    int res=ErrorComparison;
    int comb1type,comb2type;
    std::vector<Card> primeCards1,primeCards2;
    comb1type=comb1.getCombinationType(primeCards1);
    comb2type=comb2.getCombinationType(primeCards2);
    if(comb1type==ErrorCombination||comb2type==UnknownCombination) {
        return ErrorComparison;
    }
    if(comb1type==ErrorCombination||comb2type==UnknownCombination) {
        return ErrorComparison;
    }
    if(comb1type==JokerBomb) {
        return Greater;
    }
    if(comb2type==JokerBomb) {
        return Less;
    }
    if(comb1type==Bomb && comb2type!=Bomb) {
        return Greater;
    }
    if(comb1type==Bomb && comb2type!=Bomb) {
        return Less;
    }
    if(comb1type!=comb2type) {
        return ErrorComparison;
    }
    if(comb1.cards.size()!=comb2.cards.size()) {
        return ErrorComparison;
    }
    std::map<int,int> comb1pointcounts,comb2pointcounts;
    int maxcount1=0,maxcount2=0;
    comb1pointcounts=statistics(comb1.cards);
    for(auto it=comb1pointcounts.begin();it!=comb1pointcounts.end();it++) {
        if(maxcount1<it->second) {
            maxcount1=it->second;
        }
    }
    comb2pointcounts=statistics(comb2.cards);
    for(auto it=comb2pointcounts.begin();it!=comb2pointcounts.end();it++) {
        if(maxcount2<it->second) {
            maxcount2=it->second;
        }
    }

    switch (comb1type) {
    case Single:
    case Pair:
    case Straight:
    case PairStraight:
    case Three:
    case Airplane:
    case FourWithTwo:
    case Bomb:
        if(primeCards1.begin()->point<primeCards2.begin()->point) {
            res=Less;
        }
        else if(primeCards1.begin()->point==primeCards2.begin()->point) {
            res=Equal;
        }
        else {
            res=Greater;
        }
        break;
    }
    return res;
}

std::map<int,int> Combination::statistics(std::vector<fal::Card> cards)
{
    int point;
    std::map<int,int> pointcounts;
    for(size_t i=0;i<cards.size();i++) {
        point=cards[i].point;
        if(pointcounts.count(point)) {
            pointcounts[point]+=1;
        }
        else {
            pointcounts[point]=1;
        }
    }
    return pointcounts;
}

int Combination::getCombinationType()
{
    std::vector<Card> primeCards;
    return getCombinationType(primeCards);
}
Combination::~Combination()
{
}
