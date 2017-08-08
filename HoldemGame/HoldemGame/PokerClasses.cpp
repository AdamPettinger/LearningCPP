//
//  PokerClasses.cpp
//  HoldemGame
//
//  Created by Adam on 7/14/17.
//  Copyright © 2017 Adam. All rights reserved.
//

#include "PokerClasses.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASSES!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~CARD CLASS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Card::Card(short num, char suit)
{
    short *pNum = new short;
    char *pChar = new char;
    itsNum = *pNum = num;
    itsSuit = *pChar = suit;
    delete pNum;
    delete pChar;
}
Card::Card()
{
    itsNum = 0;
    itsSuit = 'N';
}
Card::~Card()
{
}

void Card::setNum(short val)
{
    itsNum = val;
}

void Card::setSuit(char suit)
{
    itsSuit = suit;
}

std::string Card::str() const
{
    std::string out;
    
    switch (itsNum)
    {
        case 10:
            out = "10 ";
            break;
            
        case 11:
            out = "J  ";
            break;
            
        case 12:
            out = "Q  ";
            break;
            
        case 13:
            out = "K  ";
            break;
            
        case 14:
            out = "A  ";
            break;
            
        default:
            out = std::to_string(itsNum) + "  ";
    }
    
    out = out + itsSuit;
    return out;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~DECK CLASS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Deck::Deck()
{
    //std::cout << "Creating Deck, mate\n";
    short v, s;
    char suit = 'H';
    short i=0;
    
    for (s=0; s < 4; s++)
    {
        switch (s)
        {
            case(0):
                suit = 'H';
                break;
            case(1):
                suit = 'D';
                break;
            case(2):
                suit = 'C';
                break;
            default:
                suit = 'S';
        }
        
        for(v = 2; v < 15; v++)
        {
            Card * pCard = new Card(v, suit);
            itsDeck.push_back(*pCard);
            delete pCard;
            
            i++;
        }
    }
}

Deck::~Deck(){};


void Deck::shuffle()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(itsDeck.begin(), itsDeck.end(), std::default_random_engine(seed));
}

void Deck::reset()
{
    loc = 0;
    shuffle();
}

Card& Deck::pop()
{
    if (loc == 0)
    {
        loc++;
        return itsDeck[0];
    }
    loc ++;
    return itsDeck[loc - 1];
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~PLAYER CLASS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Player::Player(short num, long starting)
{
    money = starting;
    name = "Player " + std::to_string(num);
}

Player::Player()
{
    money = 0;
    name = "Player 0";
    Card * hand = new Card[2];
    hand[0] = hand[1] = Card();
}

Player::~Player(){};

void Player::add(long wins)
{
    money = money + wins;
}

long Player::sub(long loss)
{
    if(loss >= money)
    {
        all = true;
        betAmount = money;
        money = 0;
        return betAmount;
    }
    
    money = money - loss;
    betAmount = loss;
    return loss;
}

void Player::giveCard(Card &c, short num)
{
    if (num > 1) return;
    hand[num] = c;
}

std::string Player::str(bool showHand)
{
    std::string out = name + ". Stack = $" + std::to_string(money) + ". Hand:\t";
    
    if (showHand)
    {
        out = out + hand[0].str() + "\t" + hand[1].str() + "\n";
    }
    else
    {
       out = out + "*  *\t*  *\n";
    }
    
    return out;
}

void Player::resetHand()
{
    hand = new Card[2];
    betAmount = 0;
    inHand = true;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~TABLE CLASS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Table::Table(){};

Table::~Table(){};

void Table::setPlayers(short num)
{
    numPlayers = num;
}

void Table::potAdd(long num)
{
    pot = pot + num;
}

void Table::cycle()
{
    pot = 0;
    BBpos++;
    SBpos++;
    board.erase(board.begin(), board.end());
    
    if (BBpos == numPlayers)
    {
        BBpos = 0;
    }
    
    if (SBpos == numPlayers)
    {
        SBpos = 0;
    }
}

void Table::addCard(Card& c)
{
    board.push_back(c);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~GAME CLASS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Game::Game(short num, long startingStack, long SBamount)
{
    table->setPlayers(num);
    numPlayers = num;
    deck->shuffle();
    minBet = SBamount;
    
    for (int i=0; i < num; i++)
    {
        Player * pPlayer = new Player(i+1, startingStack);
        //std::cout << "pPlayer: " << pPlayer << "\n";
        players.push_back(*pPlayer);
        //order.push_back(&players[i]); // PUTTING THIS HERE DID NOT WORK??
        delete pPlayer;
    }
    
    for (int i=0; i < players.size(); i++)
    {
        order.push_back(&players[i]);
    }
    
    addGameLog("New game with " + std::to_string(num) + " players.\n");
}

Game::~Game()
{
    delete deck;
}

void Game::removePlayer()
{
    std::vector<Player> newPlayers;
    int removed = 0;
    for(int i=0; i<numPlayers; i++)
    {
        if(players[i].mon() == 0)
        {
            addGameLog(players[i].getName() + " removed from the game.\n");
            table->addHandLog(players[i].getName() + " has lost and is out of the game.\n");
            removed ++;
        }
        else
        {
            newPlayers.push_back(players[i]);
        }
        
    }
    numPlayers -= removed;
    players = newPlayers;

}

void Game::clear()
{
    deck->reset();
    pickWinner();
    long winnings =(table->stack())/order.size();
    for(int i=0; i<order.size(); i++)
    {
        order[i]->add(winnings);
        table->addHandLog(order[i]->getName() + " wins $" + std::to_string(winnings) + "\n");
        addGameLog(order[i]->getName() + " wins $" + std::to_string(winnings));
        addGameLog(" in hand number " + std::to_string(handNum) + ".\n");
    }
    
    table->cycle();
    firstBet = true;
    toCall = 0;
    
    short sb = table->SB();
    order.erase(order.begin(), order.end());
    
    if(checkAllIn())
    {
        removePlayer();
    }
    
    for(int i=0; i < numPlayers; i++)
    {
        players[i].resetHand();

        order.push_back(&players[sb]);
        
        sb++;
        
        if(sb == numPlayers)
        {
            sb = 0;
        }
    }
}

void Game::dealPlayers()
{
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<order.size(); j++)
        {
            order[j]->giveCard(deck->pop(), i);
        }
    }
}

void Game::bet(Player &better, long betSize)
{
    
    if(!firstBet)
    {
        betSize += toCall;
    }
    
    betSize = better.sub(betSize);
    
    if(betSize < minBet && !better.allIn())
    {
        std::cout << "Min Bet Size, setting bet to Min...\n";
        betSize = minBet;
    }

    firstBet = false;
    table->potAdd(betSize);
    toCall = betSize;
    
    std::string log = better.getName() + " raises to $" + std::to_string(betSize) + ".\n";
    if (better.allIn())
    {
        wentAllIn = true;
        log += better.getName() + " is ALL IN\n";
        addGameLog(better.getName() + " went ALL IN\n");
    }
    
    table->addRoundLog(log);
    table->addHandLog(log);
}

void Game::call(Player &caller)
{
    long callSize = caller.sub(toCall - caller.betAmount);
    table->potAdd(callSize);
    
    std::string log = caller.getName();
    
    if(firstBet)
    {
        log += " checks.\n";
    }
    else
    {
        log += " calls $" + std::to_string(callSize) + ".\n";
    }
    
    if(caller.allIn())
    {
        wentAllIn = true;
        log += caller.getName() + " is ALL IN\n";
        addGameLog(caller.getName() + " went ALL IN\n");
        
        for(int p=0; p<moved.size(); p++)
        {
            long owed = moved[p]->betAmount - callSize;
            if(owed != 0)
            {
                moved[p]->add(owed);
                log += moved[p]->getName() + " gets $" + std::to_string(owed) + " back.\n";
            }
        }
    }
    
    table->addRoundLog(log);
    table->addHandLog(log);
}

void Game::dealTable(short num)
{
    for(int i=0; i < num; i++)
    {
        table->addCard(deck->pop());
    }
    
    
}

bool Game::checkAllIn()
{
    for(int p=0; p<numPlayers; p++)
    {
        if(players[p].allIn())
        {
            wentAllIn = true;
            return true;
        }
    }
    wentAllIn = false;
    return false;
}

void Game::display(Player& P, bool show, bool sP)
{
    std::string history = table->roundHist();
    
    std::string tStr = "Pot: " + std::to_string(table->stack()) + "\t\t";
    std::vector<Card> tCards = table->cards();
    
    for(int i=0; i < tCards.size(); i++)
    {
        tStr += tCards[i].str() + "\t";
    }
    
    if(sP)
    {
        tStr += "\n";
        
        for(int i=0; i < order.size(); i++)
        {
            tStr += order[i]->str(false);
        }
        
        for(int i=0; i < moved.size(); i++)
        {
            tStr += moved[i]->str(false);
        }
    }
    
    tStr += "\n";
    
    std::string pStr = P.str(show);
    
    std::string oStr = "\nOptions: \t'1' = Show Hand\n\t\t\t'2' = Show Players\n\t\t\t";
    oStr += "'3' = Fold\n\t\t\t";
    
    if(firstBet)
    {
        oStr += "'4' = Check\n\t\t\t'5' = Bet\n";
    }
    else
    {
        oStr += "'4' = Call " + std::to_string(toCall - P.betAmount) + "\n";
        oStr += "\t\t\t'5' = Raise\n";
    }
    
    
    std::cout << "\t**** DON'T LOOK PAST HERE ****\n";
    std::cout << "\t**** DON'T LOOK PAST HERE ****\n";
    std::cout << "\t**** DON'T LOOK PAST HERE ****\n";
    
    std::cout << history;
    std::cout << tStr;
    std::cout << pStr;
    std::cout << oStr;
}

int Game::getOption()
{
    std::string ans;
    std::cout << "Enter option: ";
    std::getline (std::cin, ans);
    
    int val = std::stoi(ans);
    if(val > 5 || val < 1)
    {
        return -1;
    }
    
    return val;
}

long Game::getBet()
{
    std::string ans;
    if(firstBet)
    {
        std::cout << "Enter bet ammount: ";
    }
    else
    {
        std::cout << "Enter ammount to raise by: ";
    }
    std::getline (std::cin, ans);
    
    int val = std::stoi(ans);
    return val;
}

void Game::playRound()
{
    int opt;
    long betSize;
    bool showHand = false;
    bool showPlayers = false;
    table->clearRoundLog();
    
    while(order.size() > 0)
    {
        display(*order.front(), false, false);
        opt = getOption();
        
        while(opt == 1 || opt == 2)
        {
            if(opt == 1)
            {
                showHand = true;
                display(*order.front(), showHand, false);
                opt = getOption();
            }
            else
            {
                showPlayers = true;
                display(*order.front(), showHand, showPlayers);
                opt = getOption();
            }

        }
        
        switch (opt)
        {
            case(3):
                table->addRoundLog(order.front()->getName() + " folds.\n");
                table->addHandLog(order.front()->getName() + " folds.\n");
                order.front()->setInHand(false);
                order.erase(order.begin());
                break;
            case(4):
                call(*order.front());
                moved.push_back(order.front());
                order.erase(order.begin());
                break;
            case(5):
                betSize = getBet();
                bet(*order.front(), betSize);
                
                for (int i=0; i<moved.size(); i++)
                {
                    order.push_back(moved[i]);
                }
                moved.erase(moved.begin(), moved.end());
                moved.push_back(order.front());
                order.erase(order.begin());
                
                break;
        }
        
        showPlayers = showHand = false;
    }
    
    firstBet = true;
    toCall = 0;
    
    short sb = table->SB();
    moved.erase(moved.begin(), moved.end());
    for(int i=0; i < numPlayers; i++)
    {
        
        if(players[sb].in())
        {
            players[sb].betAmount = 0;
            order.push_back(&players[sb]);
        }
        
        sb++;
        
        if(sb == numPlayers)
        {
            sb = 0;
        }
    }
}

int Game::playHand()
{
    wentAllIn = false;
    handNum ++;
    
    dealPlayers();
    
    std::string gLog = "Hand " + std::to_string(handNum) + ": ";
    for (int i=0; i<players.size(); i++)
    {
        gLog += players[i].getName() + " = $" + std::to_string(players[i].mon()) + "  ";
    }
    addGameLog(gLog + "\n");
    
    table->clearHandLog();
    table->addHandLog("Dealing Players for Hand " + std::to_string(handNum) + "...\n");
    table->addHandLog(order.front()->getName() + " is the Small Blind\n");
    table->addHandLog(order[2]->getName() + " is the Big Blind\n");
    
    bet(*order.front(), minBet);
    order.push_back(order.front());
    order.erase(order.begin());
    
    bet(*order.front(), minBet);
    moved.push_back(order.front());
    order.erase(order.begin());
    
    playRound();
    if(order.size() == 1)
    {
        clear();
        return 0;
    }
    
    dealTable(3);
    table->addHandLog("Dealing the Flop... ($" + std::to_string(table->stack()) + ")\n");
    
    if(!wentAllIn)
    {
        playRound();
    }
    
    if(order.size() == 1)
    {
        clear();
        return 0;
    }
    
    dealTable(1);
    table->addHandLog("Dealing the Turn... ($" + std::to_string(table->stack()) + ")\n");
        
    if(!wentAllIn)
    {
        playRound();
    }
    
    if(order.size() == 1)
    {
        clear();
        return 0;
    }
    dealTable(1);
    table->addHandLog("Dealing the River... ($" + std::to_string(table->stack()) + ")\n");
    
    if(!wentAllIn)
    {
        playRound();
    }
    
    if(order.size() == 1)
    {
        clear();
        return 0;
    }
    
    std::vector<Card> tCards = table->cards();
    for(int i=0; i < tCards.size(); i++)
    {
        std::cout << tCards[i].str() << "\t";
    }

    std::cout << "\n";
    for(int i=0; i < order.size(); i++)
    {
        std::cout << order[i]->str(true);
    }
    
    clear();
    
    if(wentAllIn)
    {
        return 1;
    }
    return 0;
}

void Game::playGame()
{
    while(numPlayers > 1)
    {
        playHand();
    }
}

void Game::pickWinner()
{
    
    for(int i=0; i<order.size(); i++)
    {
        std::vector<Card> cards = table->cards();
        cards.push_back(order[i]->hand[0]);
        cards.push_back(order[i]->hand[1]);
        
        cards = sortCards(cards);
        
        std::vector<short> row = getScore(cards);
        mScores.push_back(row);
    }
    
    short maxA[13];
    for(int i=0; i<mScores[0].size(); i++)
    {
        short max = -1;
        for(int j=0; j<order.size(); j++)
        {
            if(mScores[j][i] > max)
            {
                max = mScores[j][i];
            }
        }
        maxA[i] = max;
    }
    
    bool done = false;
    short removed = 1;
    
    while(!done && removed < order.size())
    {
        bool goon = true;
        
        for(int i=0; i<mScores[0].size(); i++)
        {
            if (!goon) continue;
            
            for(int j=0; j<order.size(); j++)
            {
                if(mScores[j][i] < maxA[i])
                {
                    mScores.erase(mScores.begin() + j);
                    order.erase(order.begin() + j);
                    
                    removed ++;
                    goon = false;
                    continue;
                }
            }
        }
        done = true;
    }
    
    mScores.erase(mScores.begin(), mScores.end());
}

std::vector<Card> Game::sortCards(std::vector<Card> pCards)
{
    std::vector<Card> sorted;
    
    for(int i=0; i<7; i++)
    {
        short s = pCards.size();
        short maxLoc = 0;
        short max = 2;
        for(int j=0; j<s; j++)
        {
            if(pCards[j].val() >= max)
            {
                max = pCards[j].val();
                maxLoc = j;
            }
        }
        
        sorted.push_back(pCards[maxLoc]);
        pCards.erase(pCards.begin() + maxLoc);
    }
    
    return sorted;
}

std::vector<Card> Game::removeCards(std::vector<Card> cards, short value)
{
    std::vector<Card> output;
    for(int i=0; i<cards.size(); i++)
    {
        if(cards[i].val() != value)
        {
            output.push_back(cards[i]);
        }
    }
    return output;
}

std::vector<Card> Game::removeSuits(std::vector<Card> cards, char rSuit)
{
    std::vector<Card> output;
    for(int i=0; i<cards.size(); i++)
    {
        if(cards[i].suit() == rSuit)
        {
            output.push_back(cards[i]);
        }
    }
    return output;
}

std::vector<short> Game::getScore(std::vector<Card> cards)
{
    std::vector<short> score;
    score.assign(13, -1);
    
    short straight = checkS(cards);
    char flush = checkF(cards);
    
    if (straight != -1 && flush != 'N')
    {
        score[0] = straight;
        std::cout << "Straight Flush! " << straight << "\n";
        return score;
    }
    else if (straight != -1)
    {
        score[4] = straight;
        std::cout << "Straight! " << straight << "\n";
        return score;
    }
    else if (flush != 'N')
    {
        score[3] = 1;
        cards = removeSuits(cards, flush);
        score = checkHC(score, cards, 5);
        std::cout << "Flush! " << flush << "\n";
        return score;
    }
    
    score[1] = checkXK(cards, 4);
    if (score[1] != -1)
    {
        cards = removeCards(cards, score[1]);
        score = checkHC(score, cards, 1);
        std::cout << "4 of a Kind! " << score[1] << "\n";
        std::cout << "Leftover Card: " << score[8] << "\n";
        return score;
    }
    
    short tKind = checkXK(cards, 3);
    if(tKind != -1)
    {
        cards = removeCards(cards, tKind);
        short pair = checkXK(cards, 2);
        
        if(pair != -1)
        {
            score[2] = 15*tKind + pair;
            std::cout << "Full House! 3 of " << tKind << "\n";
            std::cout << "Full House! 2 of " << pair << "\n";
            return score;
        }
        else
        {
            score[5] = tKind;
            score = checkHC(score, cards, 2);
            std::cout << "3 of a Kind! " << tKind << "\n";
            std::cout << "Leftover Card: " << score[8] << "\n";
            std::cout << "Leftover Card: " << score[9] << "\n";
            return score;
        }
    }
    
    short pair1 = checkXK(cards, 2);
    if(pair1 != -1)
    {
        cards = removeCards(cards, pair1);
        short pair2 = checkXK(cards, 2);
        
        if(pair2 != -1)
        {
            score[6] = 15*pair1 + pair2;
            cards = removeCards(cards, pair1);
            cards = removeCards(cards, pair2);
            score = checkHC(score, cards, 1);
            std::cout << "2 Pair. High Pair: " << pair1 << "\n";
            std::cout << "2 Pair. Low Pair: " << pair2 << "\n";
            return score;
        }
        else
        {
            score[7] = pair1;
            cards = removeCards(cards, pair1);
            score = checkHC(score, cards, 3);
            std::cout << "1 Pair: " << pair1 << "\n";
            return score;
        }
    }
    
    score = checkHC(score, cards, 5);
    return score;
}

char Game::checkF(std::vector<Card> cards)
{
    char suits[4] = {'H', 'D', 'S', 'C'};
    
    for(int i=0; i<4; i++)
    {
        short missed = 0;
        short j = 6;
        
        while(missed < 3 && j > -1)
        {
            if(cards[j].suit() != suits[i])
            {
                missed ++;
            }
            
            j--;
        }
        if(missed < 3)
        {
            return suits[i];
        }
    }
    return 'N';
}

short Game::checkS(std::vector<Card> cards)
{
    short inRow = 1;
    short max = 0;
    short targ = 5;
    short iLow = 0;
    bool low[4] = {false, false, false, false};
    
    
    for(int i=0; i<(cards.size() - 1); i++)
    {
        if(cards[i].val() == cards[i+1].val())
        {
            continue;
        }
        else if((cards[i].val() - cards[i+1].val()) == 1)
        {
            inRow ++;
            max = (max < cards[i].val()) ? (cards[i].val()) : (max);
        }
        else
        {
            inRow = 1;
            max = 0;
        }
        
        if(inRow == 5)
        {
            return max;
        }
        if(cards[i+1].val() == targ)
        {
            targ --;
            low[iLow] = true;
            iLow ++;
        }
        
        else if(low[3] && cards[0].val() == 14)
        {
            return 5;
        }
        
    }
    return -1;
}

std::vector<short> Game::checkHC(std::vector<short> rScore, std::vector<Card> rCards, short num)
{
    std::vector<short> score = rScore;
    short loc = 8;
    
    for (int i=0; i<num; i++)
    {
        score[loc] = rCards[i].val();
        loc ++;
    }
    
    
    return score;
}

short Game::checkXK(std::vector<Card> cards, short x)
{
    short counter = 1;
    
    for (int i=0; i<(cards.size()-1); i++)
    {
        if(cards[i].val() == cards[i+1].val())
        {
            counter ++;
        }
        else
        {
            counter = 1;
        }
        
        if(counter == x)
        {
            return cards[i].val();
        }
    }
    return -1;
}

