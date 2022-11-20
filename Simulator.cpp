#include <bits/stdc++.h>
#include "Simulator.h"
using namespace std;

Simulator::Simulator(/* args */)
{
}

Simulator::Simulator(int noOfPlayers, int noOfColors, int noOfNumbers)
{
    for (int i = 0; i < noOfPlayers; i++)
    {
        players.push_back(new Player(i));
    }
    cardDeck = new CardDeck(noOfNumbers, noOfColors);
}
int Simulator::reversePlayers(int idx)
{
    // std::cout << std::setfill('-') << std::setw(38) << '\n';
    cout << " direction is reversed 🔁" << endl;
    std::cout << std::setfill('-') << std::setw(38) << '\n';
    if(players.size()==2){
        return idx;
    }
    reverse(players.begin(), players.end());
    if (idx == 0)
    {
        return 0;
    }

    return players.size() - idx;
}
void Simulator::giveCards(Player *player, int noofCards)
{
    int n = noofCards;
    while (n--)
    {
        player->takeCard(cardDeck->getCard());
    }
    // std::cout << std::setfill('-') << std::setw(38) << '\n';
    if (noofCards == 1)
    {
        cout << "player With ID: " << player->getId() << " took " << noofCards << " card 😂😂" << endl;
    }
    else
    {
        cout << "player With ID: " << player->getId() << " took " << noofCards << " cards 😂😂" << endl;
    }
    std::cout << std::setfill('-') << std::setw(38) << '\n';
}
void Simulator::simulateManually()
{
    int noOfPlayers = players.size();
    cardDeck->shuffle(10000);
    distributeCards(7);
    Card *topCard = cardDeck->getCard();
    while (topCard != NULL && topCard->isPlus4())
    {
        topCard = cardDeck->getCard();
    }
    cardDeck->putCardInDiscardPile(topCard);
    int i = findStartingPlayerIndex(cardDeck->getTopCard(), "Manual");
    while (true)
    {
        topCard = cardDeck->getTopCard();
        Card *playedCard = players[i]->putCardManual(topCard);
        cout << "Played Card : ";
        if (playedCard)
        {
            playedCard->show();
        }
        else
            cout << "No Card Played";
        cout << endl;
        if (playedCard == NULL)
        {
            giveCards(players[i], 1);
            cout << "player with id : " << players[i]->getId() << " continuing turn " << endl;
            playedCard = players[i]->putCardManual(topCard);
            cout << "Played Card : ";
            if (playedCard)
                playedCard->show();
            else
                cout << "No Card Played";
            cout << endl;
        }
        if (playedCard != NULL && playedCard->isPlus4())
        {
            string chosenColor = players[i]->getColorChoice(cardDeck->getColors());
            playedCard->setColor(chosenColor);
            if (players[(i + 1) % noOfPlayers]->doYouWantToChallengeManual())
            {
                cout << players[(i + 1) % noOfPlayers]->getId() << " challenged " << players[i]->getId() << " for use of +4 " << endl;
                if (players[i]->getNoOfColorCards(topCard) > 0)
                {
                    cout << players[(i + 1) % noOfPlayers]->getId() << " Won Challenge" << endl;
                    giveCards(players[i], 4);
                    i = (i + 1) % noOfPlayers;
                }
                else
                {
                    cout << players[(i + 1) % noOfPlayers]->getId()  << " lost challenge " << endl;
                    giveCards(players[(i + 1) % noOfPlayers], 6);
                    i = (i + 2) % noOfPlayers;
                }
            }
            else
            {
                if (CheckPlayerWon(players[i],"Manual"))
                    break;
                i = (i + 1) % noOfPlayers;
                giveCards(players[i], 4);
                i = (i + 1) % noOfPlayers;
            }
        }
        if (playedCard != NULL && playedCard->isPlus2())
        {
            if (CheckPlayerWon(players[i],"Manual"))
                break;
            i = (i + 1) % noOfPlayers;
            giveCards(players[i], 2);
            i = (i + 1) % noOfPlayers;
        }
        if (playedCard != NULL && playedCard->isWild())
        {
            string chosenColor = players[i]->getColorChoice(cardDeck->getColors());
            playedCard->setColor(chosenColor);
            if (CheckPlayerWon(players[i],"Manual"))
                break;
            i = (i + 1) % noOfPlayers;
        }
        if (playedCard != NULL && playedCard->isSkip())
        {
            if (CheckPlayerWon(players[i],"Manual"))
                break;
            cout << "Player " << players[(i + 1) % noOfPlayers]->getId() << "'s turn Skipped 🚫" << endl;
            std::cout << std::setfill('-') << std::setw(38) << '\n';
            i = (i + 2) % noOfPlayers;
        }
        if (playedCard != NULL && playedCard->isReverse())
        {
            if (CheckPlayerWon(players[i],"Manual"))
                break;
            i = reversePlayers(i);
        }
        if (playedCard != NULL && !playedCard->isPowerCard())
        {
            if (CheckPlayerWon(players[i],"Manual"))
                break;
            i = (i + 1) % noOfPlayers;
        }
        if (playedCard == NULL)
        {
            i = (i + 1) % noOfPlayers;
            std::cout << std::setfill('-') << std::setw(38) << '\n';
        }
        if (playedCard != NULL)
        {
            if (cardDeck->getTopCard()->isPlus4() || cardDeck->getTopCard()->isWild())
            {
                cardDeck->getTopCard()->setColor("NULL");
            }
            cardDeck->putCardInDiscardPile(playedCard);
        }
    }
}
void Simulator::simulateAutomatically()
{
    int noOfPlayers = players.size();
    cardDeck->shuffle(10000);
    distributeCards(7);
    Card *topCard = cardDeck->getCard();
    while (topCard != NULL && topCard->isPlus4())
    {
        topCard = cardDeck->getCard();
    }
    cardDeck->putCardInDiscardPile(topCard);
    int i = findStartingPlayerIndex(cardDeck->getTopCard(), "Automatic");
    while (true)
    {
        topCard = cardDeck->getTopCard();
        Card *playedCard = players[i]->putCardAutomatically(topCard);
        cout << "Played Card : ";
        if (playedCard)
        {
            playedCard->show();
        }
        else
            cout << "No Card Played";
        cout << endl;
        if (playedCard == NULL)
        {
            giveCards(players[i], 1);
            cout << "player with id : " << players[i]->getId() << " continuing turn " << endl;
            playedCard = players[i]->putCardAutomatically(topCard);
            cout << "Played Card : ";
            if (playedCard)
                playedCard->show();
            else
                cout << "No Card Played";
            cout << endl;
        }
        if (playedCard != NULL && playedCard->isPlus4())
        {
            cout << players[i % noOfPlayers]->getId() << "  Played +4️⃣" << endl;
            string chosenColor = players[i]->getColorChoiceAutomatic(cardDeck->getColors());
            playedCard->setColor(chosenColor);
            if (players[(i + 1) % noOfPlayers]->doYouWantToChallenge())
            {
                cout << players[(i + 1) % noOfPlayers]->getId() << " challenged " << players[i]->getId() << " for use of +4 " << endl;
                if (players[i]->getNoOfColorCards(topCard) > 0)
                {
                    cout << players[i]->getId() << " lost challenge and picked 4 cards " << endl;
                    giveCards(players[i], 4);
                    i = (i + 1) % noOfPlayers;
                }
                else
                {
                    cout << players[(i + 1) % noOfPlayers] << " lost challenge and picked 6 cards " << endl;
                    giveCards(players[(i + 1) % noOfPlayers], 6);
                    i = (i + 2) % noOfPlayers;
                }
            }
            else
            {
                if (CheckPlayerWon(players[i],"Automatic"))
                    break;
                i = (i + 1) % noOfPlayers;
                giveCards(players[i], 4);
                i = (i + 1) % noOfPlayers;
            }
        }
        if (playedCard != NULL && playedCard->isPlus2())
        {
            cout << players[i % noOfPlayers]->getId() << "  Played  +2️⃣" << endl;
            if (CheckPlayerWon(players[i],"Automatic"))
                break;
            i = (i + 1) % noOfPlayers;
            giveCards(players[i], 2);
            i = (i + 1) % noOfPlayers;
        }
        if (playedCard != NULL && playedCard->isWild())
        {
            cout << players[i % noOfPlayers]->getId() << " Played wild card 🔴🔵🟢🟡" << endl;
            string chosenColor = players[i]->getColorChoiceAutomatic(cardDeck->getColors());
            playedCard->setColor(chosenColor);
            if (CheckPlayerWon(players[i],"Automatic"))
                break;
            i = (i + 1) % noOfPlayers;
        }
        if (playedCard != NULL && playedCard->isSkip())
        {
            if (CheckPlayerWon(players[i],"Automatic"))
                break;
            cout << "Player " << players[(i + 1) % noOfPlayers]->getId() << "'s turn Skipped 🚫" << endl;
            std::cout << std::setfill('-') << std::setw(38) << '\n';
            i = (i + 2) % noOfPlayers;
        }
        if (playedCard != NULL && playedCard->isReverse())
        {
            if (CheckPlayerWon(players[i],"Automatic"))
                break;
            i = reversePlayers(i);
        }
        if (playedCard != NULL && !playedCard->isPowerCard())
        {
            if (CheckPlayerWon(players[i],"Automatic"))
                break;
            i = (i + 1) % noOfPlayers;
            // std::cout << std::setfill('-') << std::setw(38) << '\n';
        }
        if (playedCard == NULL)
        {
            i = (i + 1) % noOfPlayers;
            std::cout << std::setfill('-') << std::setw(38) << '\n';
        }
        if (playedCard != NULL)
        {
            if (cardDeck->getTopCard()->isPlus4() || cardDeck->getTopCard()->isWild())
            {
                cardDeck->getTopCard()->setColor("NULL");
            }
            cardDeck->putCardInDiscardPile(playedCard);
        }
        // std::cout << std::setfill('-') << std::setw(38) << '\n';
    }
}
bool Simulator::CheckPlayerWon(Player *player,string s)
{
    if (player->didWin())
    {
        cout << "Player with ID " << player->getId() << " Won the match 🔥🔥🔥" << endl;
        return true;
    }
    if(player->getNoOfCardsRemaining()==1){
        bool uno;
        if(s=="Manual"){
            uno=player->isUNO();
        }
        else{
            uno=player->isUNOAutomatic();
        }
        if(uno){
            cout << "Player " << player->getId() << " Played UNO 👍👍"<<endl;
        }
        if(!uno){
            cout << "Player " << player->getId() << " did NOT Play UNO 👎👎👎"<<endl;
            giveCards(player,2);
        }
    }
    cout << "Player " << player->getId() << "'s Remaining cards are " << player->getNoOfCardsRemaining() << endl;
    cout << "Player " << player->getId() << "'s turn over" << endl;
    std::cout << std::setfill('-') << std::setw(38) << '\n';
    return false;
}
void Simulator::distributeCards(int noOfCards)
{
    for (auto player : players)
    {
        for (int i = 0; i < noOfCards; i++)
        {
            player->takeCard(cardDeck->getCard());
        }
    }
}
int Simulator::findStartingPlayerIndex(Card *topCard, string typeOfSimulation)
{
    int i = 0;
    int noOfPlayers = players.size();
    if (topCard->isPlus2())
    {

        giveCards(players[i], 2);
        i = (i + 1) % noOfPlayers;
    }
    else if (topCard->isWild())
    {
        string chosenColor = typeOfSimulation == "Manual" ? players[i]->getColorChoice(cardDeck->getColors()) : players[i]->getColorChoiceAutomatic(cardDeck->getColors());
        topCard->setColor(chosenColor);
        i = (i + 1) % noOfPlayers;
    }
    else if (topCard->isSkip())
    {
        cout << "Player " << players[(i) % noOfPlayers]->getId() << "'s first turn Skipped 🚫" << endl;
        std::cout << std::setfill('-') << std::setw(38) << '\n';
        i = (i + 1) % noOfPlayers;
    }
    else if (topCard->isReverse())
    {
        if(players.size()==2){
            i=1;
        }
        else{
            i = reversePlayers(i);
        }
        
    }
    if (!topCard->isPowerCard())
    {

        i = (i) % noOfPlayers;
    }
    return i;
}
Simulator::~Simulator()
{
    for (auto player : players)
    {
        delete player;
    }
    delete cardDeck;
}
