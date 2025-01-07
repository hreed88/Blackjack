#include "deck.cpp"
#include "player.cpp"
#include "SDLManager.cpp"
#include "game.h"

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
bool *gameState = new bool(true);
//checks for reshuffle
bool reshuffle = false;
//dealer check
bool dealerWin = false;
//push check
bool push = false;
//blackjack check
bool blackjack = false;
//create SDLManager
SDLManager *thisSDL = new SDLManager();

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


void events(){
    SDL_Event thisEvent;
    //cout << "In Thread(event loop) " <<  this_thread::get_id();
    //while(*gameState){}
    while(SDL_PollEvent(&thisEvent) != 0){
        //thisEvent = thisSDL->pollEvent();
        switch(thisEvent.type){
            case SDL_QUIT:
                cout << "\nSDL quit occured";
                *gameState = false;
                break;
            case SDL_KEYDOWN:
                if(thisEvent.key.keysym.sym == SDLK_f){
                cout << "\nF key pressed!\n";
                thisSDL->update();
                }
            default:
                break;
        }
    }
}

// void SDLUpdate(){
    
//     while(*gameState){
//         cout << "\nUpdate thread created";
//         thisSDL->update();
//     }
// }

void gameLogic(){
    while(*gameState){
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
            thisSDL->drawCard(thisPlayer.getHand()->at(0)->at(0), 0);
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
}

void preDraw(){
    thisSDL->pDraw();
}

void draw(){
    thisSDL->draw();
}

int main(){

    //shuffle cards before start
    //should be changed if difficulties are added
    thisDeck.shuffle(20);
    //game runs until player decides to quit
    //init vertex spec
    thisSDL->VertexSpecification();
    //create graphics pipeline
    thisSDL->createGraphicsPipeline();
    

    //events thread
    thread gameL(gameLogic);
    while(*gameState){
        //main loop
        events();
        //thread sdlWindow(SDLUpdate);
        preDraw();
        //cout << "\nIn Thread(Game loop) " <<  this_thread::get_id();
        draw();
    }
    gameL.join();
    // sdlWindow.join();
    delete(thisSDL);
    // }
    return 0;
}