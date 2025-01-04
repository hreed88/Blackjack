#ifndef CARD_H
#define CARD_H


using namespace std;
#include <string>
#include <iostream>
#include <vector>

enum value {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
enum suite {CLUB, DIAMOND, HEARTS, SPADE};

struct card{
    value v;
    suite s;
};

string getCardValueString(card thisCard){

    switch(thisCard.v){
        case 0:
            return "ACE";
        case 1:
            return "TWO";
        case 2:
            return "THREE";
        case 3:
            return "FOUR";
        case 4:
            return "FIVE";
        case 5:
            return "SIX";
        case 6:
            return "SEVEN";
        case 7:
            return "EIGHT";
        case 8:
            return "NINE";
        case 9:
            return "TEN";
        case 10:
            return "JACK";
        case 11:
            return "QUEEN";
        case 12:
            return "KING";
        default:
            break;
    }


    return "";

}

int getCardValueInt(card thisCard, int sum){

    switch(thisCard.v){
        case 0:
            if(sum + 11 > 21){
                return 1;
            }
            else{
                return 11;
            }
        case 1:
            return 2;
        case 2:
            return 3;
        case 3:
            return 4;
        case 4:
            return 5;
        case 5:
            return 6;
        case 6:
            return 7;
        case 7:
            return 8;
        case 8:
            return 9;
        case 9:
            return 10;
        case 10:
            return 10;
        case 11:
            return 10;
        case 12:
            return 10;
        default:
            break;
    }


    return -1;

}

string getCardSuite(card thisCard){
    switch(thisCard.s){
        case 0:
            return "CLUBS";
        case 1:
            return "DIAMOND";
        case 2:
            return "HEART";
        case 3:
            return "SPADE";
        default:
            break;
    }

    return "";
}

void printCard(card thisCard){
    cout << "{" << getCardValueString(thisCard) << "," << getCardSuite(thisCard) << "}"; 
}

#endif