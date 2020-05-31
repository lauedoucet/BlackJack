/* 
	Copyright 2020, Laurence Doucet, All rights reserved
*/

#include "blackjack.h"
#include <algorithm> 
#include <random>

using namespace std;

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

    cout << cRank << cType;
}

Rank Card::getRank() { return m_rank; }

Type Card::getType() { return m_type; }

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

void Hand::displayHand() {
    for (Card card : m_cards)
    {
        card.displayCard();
        cout << " ";
    }
    cout << "[" << (*this).getTotal() << "]";
}

int Hand::getSize() { return m_cards.size(); }

// method implementation for Deck class
Deck::Deck(vector<Card> pCards) {
    m_cards = pCards;
}

Deck::Deck() {}

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
    // this just adds last element in vector to the Hand and deletes it from the Deck
    pHand.add(m_cards.back());
    m_cards.pop_back();
}

// method implementation for *Player classes
bool AbstractPlayer::isBusted() {
    // busted if total value of cards > 21
    return (m_hand.getTotal() > 21);
}

void AbstractPlayer::addHand(Hand p_hand) {
    m_hand = p_hand;
}

Hand AbstractPlayer::getHand() {
    return m_hand;
}

HumanPlayer::HumanPlayer() {}

bool HumanPlayer::isDrawing() {
    // check if they are busted first!
    if ((*this).isBusted()) {
        return false;
    }
    else {
        // ask player if they would like to draw again
        bool draw;
        cout << "Do you want to draw? (y/n) " << endl;
        char answer;
        cin >> answer;
        if (answer == 'y') { draw = true; }
        else { draw = false; }
        return draw;
    }
}

void HumanPlayer::announce(const char* message) {
    // logs if player won, lost or had a push situation (same hand value)
    // (kinda useless but required in the assignment)
    cout << message << endl;
}

ComputerPlayer::ComputerPlayer() {}

bool ComputerPlayer::isDrawing() {
    return (m_hand.getTotal() <= 16);
}

BlackJackGame::BlackJackGame() {}

void BlackJackGame::addCasino(ComputerPlayer p_casino) {
    m_casino = p_casino;
}

void BlackJackGame::addDeck(Deck p_deck) {
    m_deck = p_deck;
}

void BlackJackGame::play() {
    // create casino and player
    ComputerPlayer casino = ComputerPlayer();
    casino.addHand(Hand());
    (*this).addCasino(casino);
    HumanPlayer player = HumanPlayer();
    player.addHand(Hand());

    // create Deck and shuffle
    Deck deck = Deck();
    deck.Populate();
    deck.shuffle();
    (*this).addDeck(deck);

    // deal and display cards to computer (1) and player (2)
    deck.deal(casino.getHand());
    cout << "Casino: ";
    casino.getHand().displayHand();
    cout << endl;

    deck.deal(player.getHand());
    deck.deal(player.getHand());
    cout << "Player: ";
    player.getHand().displayHand();
    cout << endl;

    // ask if player wants to draw, loop until they don't want to draw anymore or are busted (immediately lose)
    while(player.isDrawing())
    {
        deck.deal(player.getHand());
        cout << "Player: ";
        player.getHand().displayHand();
        cout << endl;
    }

    if (player.isBusted()) {
        player.announce("Player busts.");
    } else {
        // computer draws until not able to
        while (casino.isDrawing()) {
            deck.deal(casino.getHand());
            cout << "Casino: ";
            casino.getHand().displayHand();
            cout << endl;
        }

        if (casino.isBusted())
        {
            // if computer busts = player wins
            player.announce("Casino busts. /nPlayer wins.");
        } else {
            // compare values of player and computer and announce result
            if (player.getHand().getTotal() == casino.getHand().getTotal())
            {
                player.announce("Push: no one wins.");
            } else if (player.getHand().getTotal() > casino.getHand().getTotal()) {
                player.announce("Player wins.");
            } else {
                player.announce("Casino wins.");
            }
        }
    }
}
