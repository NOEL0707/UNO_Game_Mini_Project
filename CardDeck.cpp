#include <bits/stdc++.h>
#include<random>
#include "CardDeck.h"

using namespace std;
CardDeck::CardDeck(/* args */)
{
    colors={"Blue","Green","Red","Yellow","Orange","Violet","Indigo"};
}
CardDeck::CardDeck(int inoOfNumbers,int inoOfColors)
{
    // cout<<"Inside Card Deck"<<endl;
    noOfColors=inoOfColors;
    noOfNumbers=inoOfNumbers;
    colors={"Blue","Green","Red","Yellow","Orange","Violet","Indigo"};
    for(int i=0;i<noOfColors;i++){
        string color=colors[i];
        // cout<<color<<endl;
        for(int j=1;j<=noOfNumbers;j++){
            // cout<<"x"<<endl;
            drawPile.push(new Card(colors[i],j,false,false,false,false,false));
            drawPile.push(new Card(colors[i],j,false,false,false,false,false));
        }
        //zero card
        drawPile.push(new Card(colors[i],0,false,false,false,false,false));
        //+2 cards
        drawPile.push(new Card(colors[i],-1,true,false,false,false,false));
        drawPile.push(new Card(colors[i],-1,true,false,false,false,false));
        //reverse cards
        drawPile.push(new Card(colors[i],-1,false,false,false,true,false));
        drawPile.push(new Card(colors[i],-1,false,false,false,true,false));
        //skip cards
        drawPile.push(new Card(colors[i],-1,false,false,false,false,true));
        drawPile.push(new Card(colors[i],-1,false,false,false,false,true));
        //wild card
        drawPile.push(new Card("NULL",-1,false,false,true,false,false));
        //+4 card
        drawPile.push(new Card("NULL",-1,false,true,false,false,false));
    }
    cout<<"Card Deck Initialised"<<endl;
}
void CardDeck::shuffle(int numberOfTimes){
    // cout<<"Inside Shuffle"<<endl;
    Card* topCard=NULL;
    // cout<<"Inside Shuffle"<<endl;
    if(!discardPile.empty()){
        topCard=discardPile.top();
        discardPile.pop();
    }
    //adding cards to vector
    vector<Card*> cards;
    while(!discardPile.empty()){
        cards.push_back(discardPile.top());
        discardPile.pop();
    }
    while(!drawPile.empty()){
        // cout<<"x"<<endl;
        cards.push_back(drawPile.top());
        drawPile.pop();
    }
    //shuffling cards
    std::random_device rd;
    std::shuffle(cards.begin(),cards.end(),rd);
    //adding cards to pile
    if(topCard){
        discardPile.push(topCard);
    }
    for(auto card:cards){
        drawPile.push(card);
    }
    cout<<"Cards Shuffled 🔀"<<endl;
}
Card* CardDeck::getCard(){
    if(drawPile.empty()){
        shuffle(10000);
    }
    Card* topCard= drawPile.top();
    drawPile.pop();
    return topCard;
}
Card* CardDeck::getTopCard(){
    if(discardPile.empty()){
        return NULL;
    }
    
    return discardPile.top();
}
void CardDeck::putCardInDrawPile(Card* card){
    drawPile.push(card);

}
void CardDeck::putCardInDiscardPile(Card* card){
    discardPile.push(card);
}
vector<string> CardDeck::getColors(){
    vector<string> ans;
    for(int i=0;i<noOfColors;i++){
        ans.push_back(colors[i]);
    }
    return ans;
} 
CardDeck::~CardDeck()
{
    while(!drawPile.empty()){
        Card* t=drawPile.top();
        drawPile.pop();
        delete t;
    }
    while(!discardPile.empty()){
        Card* t=discardPile.top();
        discardPile.pop();
        delete t;
    }
}
