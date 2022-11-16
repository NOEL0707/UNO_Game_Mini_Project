#include <bits/stdc++.h>
#ifndef SIMULATOR_H
#define SIMULATOR_H
#include"CardDeck.h"
#include"Player.h"
using namespace std;
class Simulator
{
private:
    vector<Player*> players;
    CardDeck* cardDeck;
public:
    Simulator();
    Simulator(int,int,int);
    void simulateManually();
    void simulateAutomatically();

    void distributeCards(int);
    int reversePlayers(int);
    string getColorChoice();
    void giveCards(Player*,int);
    string getColorChoiceAutomatically();
    bool CheckPlayerWon(Player*);
    int findStartingPlayerIndex(Card*,string);
    ~Simulator();
};
#endif
