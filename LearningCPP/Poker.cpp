//
//  Poker.cpp
//  LearningCPP
//
//  Created by Adam on 6/29/17.
//  Copyright © 2017 Adam. All rights reserved.
//

#include "Poker.hpp"


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CLASS DEFS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ~~~~~~~~~~~~~~~~~~~~~~~ Card Class ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
Card::Card()
{
    itsNum = 0;
    itsSuit = 'N';
}
*/
Poker::Poker(int num, int suit)
{
    itsNum = num;
    itsSuit = suit;
}

Poker::~Poker()
{
}

/*
int Card::getNum() const
{
    return itsNum;
}

char Card::getSuit() const
{
    return itsSuit;
}

void Card::setNum(int val)
{
    itsNum = val;
}

void Card::setSuit(char suit)
{
    itsSuit = suit;
}
*/
// ~~~~~~~~~~~~~~~~~~~~~~~ Player Class ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
Player::Player(long startingMoney)
{
    itsStack = startingMoney;
    Card * hand = new Card[2];
    Card * pCard1 = new Card;
    Card * pCard2 = new Card;
    hand[1] = *pCard1;
    hand[2] = *pCard2;
}

Player::~Player()
{
}

long Player::getStack() const
{
    return itsStack;
}

void Player::changeStack(long delta)
{
    itsStack = itsStack + delta;
}

void Player::giveHand(Card &c1, Card &c2)
{
    hand[1] = c1;
    hand[2] = c2;
}
*/

// ~~~~~~~~~~~~~~~~~~~~~~~ Deck Class ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
Deck::Deck()
{
    char Suits[] = {'H', 'D', 'C', 'S'};
    int i, v, s;
    Card * pCard;
    Card * deck = new Card[52];
    
    for (v = 2; v < 15; v++)
    {
        for(s = 0; s < 4; s++)
        {
            pCard = new Card(v, Suits[s]);
            deck[i] = *pCard;
            delete pCard;
            i++;
        }
    }
    shuffle();
}

Deck::~Deck()
{
}

void Deck::shuffle()
{
    std::random_shuffle(&deck[0], &deck[52]);
}

Card Deck::pop()
{
    loc++;
    return deck[loc];
}
*/



