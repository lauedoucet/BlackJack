/* 
	Copyright 2020, Laurence Doucet, All rights reserved
*/

#include "blackjack.h"
#include <algorithm> 
#include <random>
#include <chrono>

using namespace std;

/***************************Card Class Implementation**************************/ 
Card::Card(const Rank &p_rank, const Type &p_type) {
    m_rank = p_rank;
    m_type = p_type;
}

// Returns value of card according to rank
// Ace will always return one, value will be changed according to context
int Card::getValue() {
    int value;
    if (m_rank == Rank::JACK || m_rank == Rank::QUEEN || m_rank == Rank::KING) { value = 10; }
    else { value = (int) m_rank; }
    return value;
}

// Prints card rank and type
void Card::displayCard() const {
    char c_type;
    switch(m_type) {
        case Type::CLUBS : c_type = 'C'; break;
        case Type::DIAMONDS : c_type = 'D'; break;
        case Type::HEARTS : c_type = 'H'; break;
        case Type::SPADES : c_type = 'S'; break;
    }

    char c_rank;
    switch(m_rank) {
    case Rank::JACK: c_rank = 'J'; cout << c_rank; break;
        case Rank::QUEEN : c_rank = 'Q'; cout << c_rank; break;
        case Rank::KING : c_rank = 'K'; cout << c_rank; break;
        default: int rank = (int)m_rank; cout << rank;
    }

    cout << c_type;
}

Rank Card::getRank() const { return m_rank; }

Type Card::getType() const { return m_type; }


/**********************Hand Class Implementation************************/
Hand::Hand() 
{   m_cards = vector<Card>();   }

Hand::Hand(const vector<Card> &p_cards)
{   m_cards = p_cards;   }

// Appends p_card at the end of m_cards
void Hand::add(const Card &p_card)
{   m_cards.push_back(p_card);   }

// Empties m_cards
void Hand::clear()
{   m_cards.clear();    }

// Returns total value of Hand = sum of values based on rank
int Hand::getTotal() {
    int total = 0;
    for (Card card : m_cards)
    {
        total = total + card.getValue();
    }

    return total;
}

// Displays all cards as a list with the total Hand value
void Hand::displayHand() {
    for (Card card : m_cards)
    {
        card.displayCard();
        cout << " ";
    }
    cout << "[" << getTotal() << "]" << endl;
}

// Returns the number of cards in m_cards
int Hand::getSize() { return m_cards.size(); }


/*************************Deck Class Implementation**************************/ 
Deck::Deck() {
    m_cards = vector<Card>();
}
Deck::Deck(const vector<Card> &p_cards) {   
    m_cards = p_cards;
}

// Changes m_cards to a standard 52 card deck, not shuffled
void Deck::Populate()
{
    vector<Card> p_cards = vector<Card>();
    // building our card vector with one of each card
    for (int i = 0; i < 4; i++)
    {
        for (int j = 1; j < 14; j++) {
            Rank rank = static_cast<Rank>(j);
            Type type = static_cast<Type>(i);
            p_cards.push_back(Card(rank, type));
        }
    }
    m_cards = p_cards;
}

// Shuffles the deck through m_cards using a random_number_engine that uses current time as a seed
void Deck::shuffle() 
{
    auto rng = default_random_engine {};
    rng.seed(time(0));
    std::shuffle(m_cards.begin(), m_cards.end(), rng);
}

// Removes one card from the back of the deck and returns it
// Assumes that the deck is already shuffled
Card Deck::deal()
{
    // back returns a reference so we need to return a copy of the card
    Card ref = m_cards.back();
    Card card = Card(ref.getRank(), ref.getType());
    m_cards.pop_back();
    return card;
}


/************************AbstractPlayer Class Implementation*******************/

// Returns true if the total value of the Hand is > 21
bool AbstractPlayer::isBusted() {
    return (m_hand.getTotal() > 21);
}

void AbstractPlayer::addHand(const Hand &p_hand) {
    m_hand = p_hand;
}

Hand& AbstractPlayer::getHand() {
    return m_hand;
}


/*************************HumanPlayer Class Implementation***********************/
HumanPlayer::HumanPlayer() {}

// Returns true if player is not busted and wants to draw
bool HumanPlayer::isDrawing() {
    if (isBusted()) {
        return false;
    }
    else {
        bool draw;
        cout << "Do you want to draw? (y/n) " << endl;
        char answer;
        cin >> answer;
        if (answer == 'y') { draw = true; }
        else { draw = false; }
        return draw;
    }
}

// Displays whether the player won or not (useless, based on assigment instructions)
void HumanPlayer::announce(const char* message) {
    cout << message << endl;
}


/*************************HumanPlayer Class Implementation***********************/
ComputerPlayer::ComputerPlayer() {}

// Returns true if total value of hand is <= 16
bool ComputerPlayer::isDrawing() {
    return (m_hand.getTotal() <= 16);
}


/***********************BlackJackGame Class Implementation**********************/
BlackJackGame::BlackJackGame() {}

void BlackJackGame::addCasino(const ComputerPlayer &p_casino) {
    m_casino = p_casino;
}

void BlackJackGame::addDeck(const Deck &p_deck) {
    m_deck = p_deck;
}

// Sets up game (casino, player and deck) and executes game loop
void BlackJackGame::play() {

    // create casino and player
    ComputerPlayer casino = ComputerPlayer();
    addCasino(casino);
    HumanPlayer player = HumanPlayer();

    // create Deck and shuffle
    Deck deck = Deck();
    deck.Populate();
    deck.shuffle();
    addDeck(deck);

    // deal and display cards to computer (1) and player (2)
    casino.getHand().add(deck.deal());
    cout << "Casino: ";
    casino.getHand().displayHand();
    cout << endl;

    player.getHand().add(deck.deal());
    player.getHand().add(deck.deal());
    cout << "Player: ";
    player.getHand().displayHand();
    cout << endl;

    // ask if player wants to draw, loop until they don't want to draw anymore or are busted (immediately lose)
    while(player.isDrawing())
    {
        player.getHand().add(deck.deal());
        cout << "Player: ";
        player.getHand().displayHand();
        cout << endl;
    }

    if (player.isBusted()) {
        player.announce("Player busts.");
    } else {
        // computer draws until not able to
        while (casino.isDrawing()) {
            casino.getHand().add(deck.deal());
            cout << "Casino: ";
            casino.getHand().displayHand();
            cout << endl;
        }

        if (casino.isBusted())
        {
            // if computer busts = player wins
            player.announce("Casino busts. Player wins.");
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
