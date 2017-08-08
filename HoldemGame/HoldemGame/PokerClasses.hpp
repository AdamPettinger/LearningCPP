//
//  PokerClasses.hpp
//  HoldemGame
//
//  Created by Adam on 7/14/17.
//  Copyright © 2017 Adam. All rights reserved.
//

#ifndef PokerClasses_hpp
#define PokerClasses_hpp

#include <stdio.h>
#include <string>
#include <vector>

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASSES DEFS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~CARD CLASS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Card
{
public:
    Card();
    Card(short num, char suit);
    ~Card();
    short val() const {return itsNum;};
    char suit() const {return itsSuit;};
    std::string str() const;
    void setNum(short val);
    void setSuit(char suit);
    
    
private:
    short itsNum;
    char itsSuit;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~DECK CLASS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Deck
{
public:
    Deck();
    ~Deck();
    void shuffle();
    void reset();
    Card& pop();
    
    // Change the deck to private eventually
    std::vector<Card> itsDeck;
    
private:
    
    short loc = 0;
    
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~PLAYER CLASS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Player
{
public:
    Player(short num, long starting);
    Player();
    ~Player();
    void add(long wins);
    long sub(long loss);
    void giveCard(Card &c, short num);
    void resetHand();
    void setInHand(bool in){inHand = in;};
    bool allIn(){return all;};
    void setAllIn(bool in){all = in;};
    
    bool in(){return inHand;};
    long mon(){return money;};
    std::string str(bool showHand);
    std::string getName(){return name;};
    Card * hand = new Card[2];
    long betAmount = 0;
    
private:
    long money;

    std::string name;
    bool inHand = true;
    bool all = false;
    
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~TABLE CLASS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Table
{
public:
    Table();
    ~Table();
    
    void setPlayers(short num);
    void potAdd(long num);
    void cycle();
    void addCard(Card& c);
    
    long stack(){return pot;};
    short BB(){return BBpos;};
    short SB(){return SBpos;};
    std::vector<Card> cards(){return board;};
    std::string roundHist(){return roundLog;};
    std::string handHist(){return handLog;};
    void addRoundLog(std::string toAdd){roundLog += toAdd;};
    void addHandLog(std::string toAdd){handLog += toAdd;};
    void clearRoundLog(){roundLog = "";};
    void clearHandLog(){handLog = "";};
    
private:
    long pot = 0;
    short BBpos = 1;
    short SBpos = 0;
    short numPlayers = 0;
    std::vector<Card> board;
    std::string roundLog;
    std::string handLog;

};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~GAME CLASS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Game
{
public:
    Game(short num, long startingStack, long SBamount);
    ~Game();
    
    void removePlayer();
    void playRound();
    int playHand();
    void playGame();
    void clear();

    void pickWinner();                          // TO TEST
    std::vector< std::vector<short> > mScores;
    std::vector<Card> sortCards(std::vector<Card> cards);
    std::vector<Card> removeCards(std::vector<Card> cards, short value);
    std::vector<Card> removeSuits(std::vector<Card> cards, char rSuit);
    std::vector<short> getScore(std::vector<Card> cards);
    short checkS(std::vector<Card> cards);
    char checkF(std::vector<Card> cards);
    short checkXK(std::vector<Card> cards, short x);
    std::vector<short> checkHC(std::vector<short> rScore, std::vector<Card> rCards, short num);
    
    void display(Player& P, bool hand, bool sP);
    int getOption();
    long getBet();
    bool checkAllIn();
    
    void bet(Player &better, long betSize);
    void call(Player &caller);
    
    std::string gameHist(){return gameLog;};
    void addGameLog(std::string toAdd){gameLog += toAdd;};
    
    void dealPlayers();
    void dealTable(short num);
    
    std::vector<Player> players;
    Deck * deck = new Deck;
    std::vector<Player*> order;
    std::vector<Player*> moved;
    Table * table = new Table;

private:
    int numPlayers;
    
    int handNum = 0;
    bool firstBet = true;
    long minBet;
    long toCall = 0;
    bool wentAllIn = false;
    std::string gameLog;
    
};

#endif /* PokerClasses_hpp */
