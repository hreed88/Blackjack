#include "deck.h"

deck::deck(){
    thisDeck = new vector<card>();
    currentCard = 0;
    for(int i = 0; i < 4; i++){
            for(int j = 0 ; j < 13; j++){
                card temp;
                temp.v = value(j);
                temp.s = suite(i);
                thisDeck->push_back(temp);
            }
    }
}

deck::deck(int deckNum){
    thisDeck = new vector<card>();
    currentCard = 0;
    //loop through default contructer deckNumTimes
    for(int k = 0; k < deckNum; k++){
        for(int i = 0; i < 4; i++){
            for(int j = 0 ; j < 13; j++){
                card temp;
                temp.v = value(j);
                temp.s = suite(i);
                thisDeck->push_back(temp);
            }
        }
    }
}

deck::~deck(){
    //free decks memory
    thisDeck->clear();
    thisDeck->shrink_to_fit();
    delete(thisDeck);
}

card deck::getTop(){
    card myTop;
    try{
        myTop = thisDeck->at(currentCard++);
    }
    catch(exception &e){
        cerr << "Tried to get the top of an empty deck" << "\nError: " << &e;
        myTop.s = suite(-1);
        myTop.v = value(-1);
    }
    return myTop;
}

void deck::shuffle(int n){
    cout << "\nReshuffling";
    currentCard = 0;
    int rand1, rand2;
    //set random seed
    srand(time(NULL));
    //shuffle n times
    while(n > 0){
        //swap cards 52 times
        for(int i = 0; i < 52; i++){
            rand1 = rand() % thisDeck->size();
            rand2 = rand() % thisDeck->size();
            //cout << "\nSwapping "<< rand1 << "," << rand2 << "(";
            // printCard(thisDeck->at(rand1));
            // printCard(thisDeck->at(rand2));
            // cout << ")\n";

            swap(thisDeck->at(rand1), thisDeck->at(rand2));

            // cout << "\nResult : (";
            // printCard(thisDeck->at(rand1));
            // printCard(thisDeck->at(rand2));
            // cout << ")\n"; 
        }
    n--;
    }
    
}

void deck::printDeck(){
    for(auto c : *thisDeck){
        printCard(c);
        cout << "\n";
    }
}

int deck::deckSize(){
    return thisDeck->size();
}

int deck::currentCardNum(){
    return currentCard;
}

bool deck::checkIfReshuffle(){
    if(currentCard == ceil(thisDeck->size() * 0.85)){
        return true;
    }
    
    return false;
}

// int main(){
//     deck myDeck = deck();
//     myDeck.printDeck();
//     myDeck.shuffle(20);
//     cout << "\nSHUFFELED DECK\n";
//     myDeck.printDeck();
//     return 0;
// }