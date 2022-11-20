#include<bits/stdc++.h>

#ifndef CARD_H
#define CARD_H
using namespace  std;
/*
    Class Card Declarations.
*/
class Card
{
private:
    string color;//to store color
    int number;//to store number of card
    bool plus2;//to store if a card is +2
    bool plus4;//if a card is +4
    bool wild;//if a card is wild
    bool reverse;//if a card is reverse
    bool skip;//if a card is skip

public:
    Card();
    Card(string,int,bool,bool,bool,bool,bool);
    string getColor();
    int getNumber();
    bool isPlus2();
    bool isPlus4();
    bool isWild();
    bool isReverse();
    bool isSkip();
    bool isPowerCard();
    void show();
    void setColor(string);
    ~Card();
};
#endif
