/* 
	Copyright 2020, Laurence Doucet, All rights reserved
*/

#include <iostream>
#include <vector>

#ifndef BLACKJACK_H
#define BLACKJACK_H

using namespace std;

enum class Rank {ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
enum class Type {CLUBS, DIAMONDS, HEARTS, SPADES};

class Card {
    private:
         Rank m_rank;
         Type m_type;

    public:
        Card(const Rank&, const Type&);
        int getValue();
        void displayCard() const;
        Rank getRank() const;
        Type getType() const;
};

class Hand {
    private: 
        mutable vector<Card> m_cards;

    public:
        Hand();
        Hand(const vector<Card>&);
        void add(const Card&);
        void clear();
        int getTotal();
        void displayHand();
        int getSize();
        bool hasPair();
};

class Deck {
    private: 
        vector<Card> m_cards;

    public:
        Deck();
        Deck(const vector<Card>&);
        void Populate();
        void shuffle();
        Card deal();
};

class AbstractPlayer {
    protected: 
        mutable Hand m_hand;

    public:
        virtual bool isDrawing() = 0;
        virtual bool isBusted();
        virtual void addHand(const Hand&);
        virtual Hand& getHand();
};

class HumanPlayer : public AbstractPlayer { 
    private:
        double m_bet;
        double m_balance;

    public:
        HumanPlayer();
        void announce(const char*);
        bool isDrawing();
        void doubleDown();
        void split();

        void requestBet();
        void setBet(double);
        double getBet();
        void displayBet();

        void setBalance(double);
        double getBalance();
        void displayBalance();
};

class ComputerPlayer : public AbstractPlayer {
    public: 
        ComputerPlayer();
        bool isDrawing();
};

class BlackJackGame {
    private:
        Deck m_deck;
        ComputerPlayer m_casino;
        HumanPlayer m_player;

    public:
        BlackJackGame();
        void play();
        void addCasino(const ComputerPlayer&);
        void addPlayer(const HumanPlayer&);
        ComputerPlayer& getCasino();
        HumanPlayer& getPlayer();
        void addDeck(const Deck&);
};

#endif