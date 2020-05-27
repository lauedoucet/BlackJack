/* 
	Copyright 2020, Laurence Doucet, All rights reserved
*/

#include "blackjack.h"
#include <iostream>
#include <algorithm> 
#include <random>

// method implementations for Card class
Card::Card(Rank pRank, Type pType) {
    m_rank = pRank;
    m_type = pType;
}

int Card::getValue() {
    // Ace will always return one, value will be changed according to context
    int value;
    if (m_rank == Rank::JACK || m_rank == Rank::QUEEN || m_rank == Rank::KING) { value = 10; }
    else { value = (int) m_rank; }
    return value;
}

void Card::displayCard() {
    char cType;
    switch(m_type) {
        case Type::CLUBS : cType = 'C'; break;
        case Type::DIAMONDS : cType = 'D'; break;
        case Type::HEARTS : cType = 'H'; break;
        case Type::SPADES : cType = 'S'; break;
    }

    char cRank;
    switch(m_rank) {
        case Rank::JACK : cRank = 'J'; break;
        case Rank::QUEEN : cRank = 'Q'; break;
        case Rank::KING : cRank = 'K'; break;
        default : cRank = (int) m_rank;
    }

    cout << cRank << cType << endl;
}

// method implementation for Hand class
Hand::Hand() 
{   m_cards = vector<Card>();   }

Hand::Hand(vector<Card> pCards)
{   m_cards = pCards;   }

void Hand::add(Card pCard)
{   m_cards.push_back(pCard);   }

void Hand::clear()
{   m_cards.clear();    }

int Hand::getTotal() {
    int total = 0;
    for (Card card : m_cards)
    {
        total =+ card.getValue();
    }

    return total;
}

// method implementation for Deck class
Deck::Deck(vector<Card> pCards) {
    m_cards = pCards;
}

Deck Deck::Populate() 
{
    vector<Card> pCards = vector<Card>();
    // building our card vector with one of each card
    for (int i=0; i<4; i++)
    {
        for (int j=1; j<14; j++) {
            Rank rank = static_cast<Rank>(j);
            Type type = static_cast<Type>(i);
            pCards.push_back(Card(rank, type));
        }
    }
    Deck deck = Deck(pCards);
    return deck;
}

void Deck::shuffle() 
{
    auto rng = default_random_engine {};
    std::shuffle(m_cards.begin(), m_cards.end(), rng);
}

void Deck::deal(Hand pHand)
{
    // assumption: the deck is already shuffled
    //this just adds last element in vector to the Hand and deletes it from the Deck
    pHand.add(m_cards.back());
    m_cards.pop_back();
}
