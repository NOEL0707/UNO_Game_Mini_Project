#include <bits/stdc++.h>
#include <random>

#include "Player.h"
using namespace std;
Player::Player(){

}
Player::Player(int ID){
    id=ID;
}
Card* Player::putCardAutomatically(Card* topCard){
    cout<<"Player "<<id<<"'s turn"<<endl;
    cout<<"Top Card : ";
    topCard->show();cout<<endl;
    Card* selectedCard= getCardChoiceAutomatic( topCard);
    cards.erase(selectedCard);
    return selectedCard;
}
Card* Player::putCardManual(Card* topCard){
    cout<<"Player "<<id<<"'s turn"<<endl;
    cout<<"Top Card : ";
    topCard->show();cout<<endl;
    Card* selectedCard=getCardChoice(topCard);
    cards.erase(selectedCard);
    return selectedCard;
}
vector<Card*> Player::filter(Card* topCard){
    vector<Card*> filteredCards;
    int numberOfColorCards=0;
    for(auto card:cards){
        if(card->isWild()){
                filteredCards.push_back(card);
        }
        else if(topCard->isReverse()&& card->isReverse()){
                filteredCards.push_back(card);
        }

        else if(topCard->isSkip()&& card->isSkip()){
            filteredCards.push_back(card);
        }
        else if(topCard->isPlus2()&& card->isPlus2()){
            filteredCards.push_back(card);
        }
        else if(topCard->getNumber()==card->getNumber() && topCard->getNumber()!=-1 ){
            filteredCards.push_back(card);
        }
        else if((topCard->getColor()==card->getColor() ) && topCard->getColor()!="NULL" ){
                filteredCards.push_back(card);
                numberOfColorCards++;
        }

    }
    if(numberOfColorCards==0){
        for(auto card:cards){
            if(card->isPlus4()){
                filteredCards.push_back(card);
            }
        }
    }
    return filteredCards;
}
void Player::takeCard(Card* inputCard){
    cards.insert(inputCard);
}
bool Player::didWin(){
    return cards.size()==0;
}
int Player::getId(){
    return id;
}
int Player::getNoOfCardsRemaining(){
    return cards.size();
}
 
Card* Player::getCardChoice(Card* topCard){
    vector<Card*> filteredCards=filter(topCard);
    if(filteredCards.size()==0){
        return NULL;
    }
    for(int i=0;i<filteredCards.size();i++){
        cout<<"choice "<<i+1<<" : ";
        filteredCards[i]->show();
        cout<<endl;
    }
    int choice;
    cout<<"Select Card Choice: ";
    cin>>choice;
    while(choice-1>=filteredCards.size()||choice-1<0){
        cout<<"Wrong Choice"<<endl;
        cout<<"Select Correct Card Choice:";
        cin>>choice;
    }
    return filteredCards[choice-1];
}
Card* Player::getCardChoiceAutomatic(Card* topCard){
    vector<Card*> filteredCards=filter(topCard);
    if(filteredCards.size()==0){
        return NULL;
    }
    for(int i=0;i<filteredCards.size();i++){
        cout<<"choice "<<i+1<<" : ";
        filteredCards[i]->show();
        cout<<endl;
    }
    //random choice generatoe
    random_device rd;
    uniform_int_distribution<int> distribution(1,filteredCards.size());
    int choice=distribution(rd);
    cout<<"Select Card Choice: ";
    cout<<choice<<endl;
    return filteredCards[choice-1];
}

Player::~Player(){
    for(auto card:cards){
        delete card;
    }
}