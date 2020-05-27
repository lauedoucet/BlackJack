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
        total = total + card.getValue();
    }

    return total;
}

// method implementation for Deck class
Deck Deck::Populate() 
{
    Deck deck = Deck();
    vector<Card> pCards = vector<Card>();
    
   // for (Type type : )

   return deck;
}

void Deck::shuffle() 
{
    auto rng = default_random_engine {};
    //shuffle (   m_cards.begin(), m_cards.end(), rng);
}

void Deck::deal(Hand pHand)
{

}
