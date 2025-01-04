#include "deck.cpp"
#include "player.cpp"
#include <SDL2/SDL.h>
//generate deck
//update to allow for different difficulties(i.e. different sized decks)
deck thisDeck;
//generate player
//update if multiplayer is implemented
bettingMan thisPlayer = bettingMan();
//generate dealer
//no need for update
Dealer thisDealer = Dealer();
//gameState
bool gameState = true;
//checks for reshuffle
bool reshuffle = false;
//dealer check
bool dealerWin = false;
//push check
bool push = false;
//blackjack check
bool blackjack = false;
//initalize renderer
static SDL_Renderer* renderer;
SDL_Window *window;

void deal(){
    int dealCount = 0;
    bool playerGotCard = false;

    //deal only 4 for now since we only have dealer and one player
    while(dealCount < 4){
        card currCard = thisDeck.getTop();
        if(!playerGotCard){
            thisPlayer.giveCard(currCard,0);
            playerGotCard = true;
        }
        else{
            thisDealer.giveCard(currCard,0);
            playerGotCard = false;
        }
        dealCount++;
    }
    //
}

int main(){
    if (SDL_Init(SDL_INIT_EVERYTHING)== 0) {
		cout << "Subsystems Initialized!.." << endl;

		window = SDL_CreateWindow("FUCK", 0, 0, 1920, 1080, SDL_WINDOW_FULLSCREEN);

		if (window != nullptr) {
			cout << "Window Created" << endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer != nullptr) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			cout << "Renderer created!" << endl;
		}
    }
    //shuffle cards before start
    //should be changed if difficulties are added
    thisDeck.shuffle(20);
    //game runs until player decides to quit
    
    while(gameState){
        //reshuffle is necessary
        if(reshuffle){
            thisDeck.shuffle(20);
            reshuffle = false;
        }

        deal();

        reshuffle = thisDeck.checkIfReshuffle();
        cout << "\nReshuffle thing" << ceil(thisDeck.deckSize() * 0.92);


        if(thisDeck.currentCardNum() == thisDeck.deckSize() - 1)
            cout << "\nCurrent Card = " << thisDeck.currentCardNum();

        //set inital deal for player
        thisPlayer.setCurrVal(thisPlayer.calculateHand().at(0));
        //set intial deal for dealer
        thisDealer.setCurrVal(thisDealer.calculateHand().at(0));
        bool playerBust = false;
        bool playerStay = false;
        while(thisPlayer.calculateHand().at(0) < 21){
            blackjack = false;
            cout << "\nYou have ";
            thisPlayer.printCards();
            cout << "\n1.) Hit\n2.) Stand\n";
            int playerDecision;
            cin >> playerDecision;

            switch (playerDecision)
            {
                //hit
                case 1:
                    thisPlayer.hit(thisDeck.getTop());
                    break;
                //stand
                case 2:
                    playerStay = true;
                    break;
                default:
                    break;
            }
            //exit loop if the player stays
           
            if(playerStay){
                playerStay = false;
                break;
            }

        }
        if(thisPlayer.getHandValue() > 21){
                cout << "\nYou Busted! With";
                thisPlayer.printCards();
                playerBust = true;
                
        }

        if(thisPlayer.getHandValue() == 21){
            cout << "\nBlackjack baby!";
            blackjack = true;
        }
        //dealers turn!
        if(!playerBust && !blackjack){
            while(thisDealer.getHandValue() < 17){
                card thisCard = thisDeck.getTop();
                thisDealer.hit(thisCard);
            }
                cout << "\nYou had: " << thisPlayer.getHandValue() << "\nDealer had: " << thisDealer.getHandValue();
                cout << "\nYou : ";
                thisPlayer.printCards();
                cout << "\nDealer: ";
                thisDealer.printCards();
                if(thisDealer.getHandValue() > 21){
                    cout << "\nPlayer win, Dealer busted";
                    dealerWin = false;
                }
                //dealer win
                else if(thisPlayer.getHandValue() < thisDealer.getHandValue()){
                    cout << "\nDealer Win";
                    dealerWin = true;
                }
                //player win
                else if(thisPlayer.getHandValue() > thisDealer.getHandValue()){
                    cout << "\nPlayer win";
                    dealerWin = false;
                }
                //push
                else{
                    cout << "\nPush";
                    push = true;
                }
            }
            thisPlayer.resetHand();
            thisDealer.resetHand();

        }


    // }
    return 0;
}