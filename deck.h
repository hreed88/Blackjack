#ifndef DECK_H_
#define DECK_H_
#include <vector>
#include <tuple>
#include <random>
#include "card.h"
using namespace std;
class deck{
    public:
        deck(); //initalize a deck of size 1
        deck(int deckNum); //intialize deck of size deckNum
        ~deck();
        card getTop();
        void printDeck();
        void shuffle(int n); //shuffles the deck n times
        int deckSize();
        int currentCardNum();
        bool checkIfReshuffle();
    private:
        //maybe in future make the vector a have pointers to cards
        //maybe not since theyll sit next to each other in memory when returning cards for the game
        vector<card> *thisDeck;
        int currentCard;

};

#endif