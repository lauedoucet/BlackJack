/* 
	Copyright 2020, Laurence Doucet, All rights reserved
*/

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
        Card(Rank pRank, Type pType);
        int getValue();
        void displayCard();

        Rank getRank() { return m_rank; }
        Type getType() { return m_type; }
};

class Hand {
    private: 
        vector<Card> m_cards;

    public:
        Hand();
        Hand(vector<Card> pCards);
        void add(Card pCard);
        void clear();
        int getTotal();

        int getSize() { return m_cards.size(); }
};

class Deck {
    private: 
        vector<Card> m_cards;

        // private constructor creates an empty Deck
        // allows us to only create a standard 52 Deck
        Deck(vector<Card>);
    public:
        static Deck Populate();
        void shuffle();
        void deal(Hand pHand);
};

class AbstractPlayer {
    protected: 
        Hand m_hand;
    public:
        virtual bool isDrawing() const = 0;
        virtual bool isBusted();
};

class HumanPlayer : AbstractPlayer { 
    public:
        HumanPlayer();
        bool isDrawing();
        void announce();
};

class ComputerPlayer : AbstractPlayer {
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
};

#endif