#include "player.h"

Player::Player(){
    //initalize *decks
    thisHand = new vector<vector<card>*>();
    //initalize inital deck
    vector<card> *initalHand = new vector<card>();
    thisHand->push_back(initalHand);
}

vector<int> Player::calculateHand(){
    vector<card> aces;
    vector<int> result;

    //check each hand(i.e. when a split occurs/dealers vect should always be of size 1)
    for(auto hand : *thisHand){
        //check cards except for aces
        int sum = 0;
        for(auto c : *hand){
                sum += getCardValueInt(c, sum);
            }

        result.push_back(sum);
    }
    return result;
}

void Player::giveCard(card thisCard, int currHand){
    thisHand->at(currHand)->push_back(thisCard);
    currVal = calculateHand().at(0);
}

int Player::getHandSize(){
    return thisHand->size();
}

void Player::printCards(){
    for(auto h : *thisHand){
        for(auto c: *h){
            printCard(c);
        }
    }
}

void Player::resetHand(){
    for(auto h: *thisHand){
        h->clear();
    }
}

int Player::getHandValue(){
    return currVal;
}

vector<vector<card>*>* Player::getHand(){
    return thisHand;
}

void bettingMan::hit(card thisCard){
    giveCard(thisCard, 0);
    setCurrVal(calculateHand().at(0));
}

void Dealer::hit(card thisCard){
    giveCard(thisCard, 0);
    setCurrVal(calculateHand().at(0));
}
