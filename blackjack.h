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
        Hand m_hand;

    public:
        virtual bool isDrawing() = 0;
        virtual bool isBusted();
        virtual void addHand(const Hand&);
        virtual Hand& getHand();
};

class HumanPlayer : public AbstractPlayer { 
    public:
        HumanPlayer();
        void announce(const char*);
        bool isDrawing();
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

    public:
        BlackJackGame();
        void play();
        void addCasino(const ComputerPlayer&);
        void addDeck(const Deck&);
};

#endif