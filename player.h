#ifndef PLAYER_H_
#define PLAYER_H_

#include "card.h"

class Player{
    public:
        Player();
        vector<int> calculateHand();
        virtual bool isPlayer(){return false;}
        int getHandSize();
        void giveCard(card thisCard, int currHand);
        void printCards();
        void resetHand();
        vector<vector<card>*>* getHand();
        void setCurrVal(int n){currVal = n;}
        int getHandValue();
        
    private:
        vector<vector<card>*> *thisHand;
        int currVal;
};

class bettingMan : public Player{
    public:
        bool isPlayer() override{
            return true;
        };
    void hit(card thisCard);
};

class Dealer : public Player{
    public:
        bool isPlayer() override{
            return false;
        }
        void hit(card thisCard);
};

#endif