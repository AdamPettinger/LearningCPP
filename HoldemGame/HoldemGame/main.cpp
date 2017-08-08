//
//  main.cpp
//  HoldemGame
//
//  Created by Adam on 7/14/17.
//  Copyright © 2017 Adam. All rights reserved.
//

#include <iostream>
#include <string>
#include <algorithm>

#include "PokerClasses.hpp"


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MAIN~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main(int argc, const char * argv[]) {
    
    
 //Main for testing
    //std::cout << "Creating Card";

    /*
    Card deck[2];
    Card * test = new Card(4, 'D');
    
    deck[0] = *test;
    
    std::cout << (deck[0]).str();
    
    Deck testDeck;
    testDeck.shuffle();
    

    std::cout << "1:  " << (testDeck.itsDeck[0]).str() << "\n";
    std::cout << "2:  " << (testDeck.itsDeck[1]).str() << "\n";
    
    Table testTable;
    testTable.setPlayers(4);
    testTable.potAdd(4000);
    
    testTable.addCard(testDeck.pop());
    testTable.addCard(testDeck.pop());
    
    std::vector<Card> testCards = testTable.cards();
    std::cout << "Cards on table: ";
    for (int i=0; i < testCards.size(); ++i)
    {
        std::cout << testCards[i].str() << ", ";
    }
    
    testTable.cycle();
    std::cout << "\nCards on table: " << testTable.cards().size();
    */
     
    Game testGame(3, 50000, 1000);
    //testGame.players[1].add(50000);
    //testGame.order[0]->add(25000);
    
    //testGame.bet(testGame.players[0], 15000);
    //testGame.bet(testGame.players[1], 25000);
    
    //testGame.dealTable(3);
    
    //testGame.table->cycle();
    
    testGame.playHand();
    std::cout << testGame.table->handHist();
    
    /*
    std::vector<Card> tCards;
    tCards.push_back(Card(2, 'S'));
    tCards.push_back(Card(10, 'S'));
    tCards.push_back(Card(4, 'S'));
    tCards.push_back(Card(3, 'H'));
    tCards.push_back(Card(13, 'S'));
    tCards.push_back(Card(8, 'S'));
    tCards.push_back(Card(14, 'D'));
    
    tCards = testGame.sortCards(tCards);
    
    std::vector<short> output = testGame.getScore(tCards);
    
    for(int i=0; i<output.size(); i++)
    {
        std::cout << output[i] << ", ";
    }
    std::cout << "\n";
    
    
    
    std::vector<short> arr, res;
    arr.assign(13, 0);
    
    int num = 2;
    
    res = testGame.checkHC(arr, tCards, num);
    
    std::cout << "High Cards (" << num << "):";
    for (int i=0; i<res.size(); i++)
    {
        std::cout << res[i] << ", ";
    }
    
    
    
    testGame.players[0].add(25000);
    testGame.playGame();
    
    std::cout << testGame.gameHist();
    
    

    
    testGame.display(testGame.players[0], false);
    testGame.bet(testGame.players[0], 15000);
    
    testGame.display(testGame.players[1], true);
    int test = testGame.getOption();

    long bet;
    if (test == 5)
    {
        bet = testGame.getBet();
    }
    
    std::cout << "You've chosen to bet $" << bet << ".\n";
    
    
    //testGame.deal();
    
    for (int i=0; i<3; i++)
    {
        std::cout << "Player " << i << ": " << testGame.players[i].hand[1].str();
        std::cout << ", " << testGame.players[i].hand[2].str() << "\n";
    }
    */
    
    
    /*
    int i;
    for (i=0; i<52; i++)
    {
        std::cout << i << "  " << (testDeck.itsDeck[i]).str() << "\n";
    }
    */
    
    
    return 0;
    
}





