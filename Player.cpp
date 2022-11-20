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
        if(card->isWild()||card->isPlus4()){
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
    
    return filteredCards;
}
void Player::takeCard(Card* inputCard){
    cards.insert(inputCard);
}
bool Player::didWin(){
    return cards.size()==0;
}
int Player::getNoOfColorCards(Card* topCard){
    int noofcoloredcards=0;
    for(auto c:cards){
        if(topCard->getColor()==c->getColor() && topCard->getColor()!="NULL"){
            noofcoloredcards++;
        }
    }
    return noofcoloredcards;
}
bool Player::doYouWantToChallenge(){
    random_device rd;
    uniform_int_distribution<int> distribution(1,100);
    int challengers_num =distribution(rd);
    return challengers_num>=70;
}
bool Player::doYouWantToChallengeManual(){
    char a;
    cout<<"Player with id "<<id<<" Wants to Challenge"<<endl;
    cout<<"Player with id  "<<id<<" Do you want to challenge for the use of +4 [Y/N] : ";
    cin >> a;
    while(a!='Y'&&a!='y'&&a!='N'&&a!='n'){
        cout<<"Wrong choice"<<endl;
        cout<<"Input correct choice : ";
        // cin.clear();
        cin>>a;
    }
    return (a=='Y'||a=='y')?1:0;

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
    //random choice generator
    random_device rd;
    uniform_int_distribution<int> distribution(1,filteredCards.size());
    int choice=distribution(rd);
    cout<<"Select Card Choice: ";
    cout<<choice<<endl;
    return filteredCards[choice-1];
}
string Player::getColorChoice(vector<string> colors){
    cout << "Color Choices: " << endl;
    for (int i = 0; i < colors.size(); i++)
    {
        cout << "choice " << i + 1 << " :";
        cout << colors[i] << endl;
    }
    int choice;
    cout << "Select Color Choices: ";
    cin >> choice;
    while (choice - 1 > colors.size() || choice - 1 < 0)
    {
        cout << "Wrong Choice" << endl;
        cout << "Select Correct colors Choice:";
        cin >> choice;
    }
    cout << endl;
    return colors[choice - 1];
}

string Player::getColorChoiceAutomatic(vector<string> colors){
    cout << "Color Choices: " << endl;
    for (int i = 0; i < colors.size(); i++)
    {
        cout << "choice " << i + 1 << " :";
        cout << colors[i] << endl;
    }
    cout << "Select Color Choices: ";
    random_device rd;
    uniform_int_distribution<int> distribution(1, colors.size());
    int choice = distribution(rd);
    cout << choice << endl;
    return colors[choice - 1];
}
bool Player::isUNO(){
    char a;
    cout<<"Do you want to say UNO [Y/N]:";
    cin >> a;
    return (a=='Y'||a=='y')?1:0;
}
bool Player::isUNOAutomatic(){
    random_device rd;
    uniform_int_distribution<int> distribution(0,1);
    int choice = distribution(rd);
    return choice<=0.9;
}  
Player::~Player(){
    for(auto card:cards){
        delete card;
    }
}