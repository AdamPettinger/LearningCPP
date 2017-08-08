//
//  Poker.hpp
//  LearningCPP
//
//  Created by Adam on 6/29/17.
//  Copyright © 2017 Adam. All rights reserved.
//

#include <algorithm>

class Poker
{
public:
    //Card();
    Poker(int num, int suit);
    ~Poker();
    /*
    char str() const;
    char getSuit() const;
    int getNum() const;
    void setNum(int val);
    void setSuit(char suit);
     */
private:
    int itsNum;
    int itsSuit;
};


/*
class Player
{
public:
    Player(long money);
    ~Player();
    long getStack() const;
    void changeStack(long delta);
    void giveHand(Card &c1, Card &c2);
private:
    long itsStack;
    Card * hand = new Card[2];
};


class Deck
{
public:
    Deck();
    ~Deck();
    Card pop();
    void shuffle();
    
private:
    Card * deck = new Card[52];
    short loc = -1;
};
*/