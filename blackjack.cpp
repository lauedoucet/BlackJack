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
        case Rank::ACE: c_rank = 'A'; cout << c_rank; break;
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
// Ace counts as 1 if 11 would bring it over 21
int Hand::getTotal() {
    int total = 0;
    int ace_count = 0;

    for (Card card : m_cards)
    {
        if (card.getRank() == Rank::ACE) {
            ace_count++;
        }
        else {
            total = total + card.getValue();
        }
    }

    while (ace_count > 0) {
        if (total + 11 > 21) { total = total + 1; }                // Ace counts as 1
        else { total = total + 11; }                               // Ace counts as 11
        ace_count--;
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

bool Hand::hasPair() {

    bool pair_found = false;

    for (Card card_outer : m_cards) {
        for (Card card_inner : m_cards) {
            if (card_outer.getRank() == card_inner.getRank() && card_outer.getType() != card_inner.getType()) {
                pair_found = true;
                break;
            }
        }

        if (pair_found) { break; }
    }
    
    return pair_found;
}


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
HumanPlayer::HumanPlayer() { 
    m_bet = 0;
    m_balance = 500;
}

// Returns true if player is not busted and wants to draw
bool HumanPlayer::isDrawing() {
    if (isBusted()) {
        return false;
    }
    else {
        bool draw;
        cout << "Do you want to draw? (y/n) ";
        char answer;
        cin >> answer;
        cout << endl;
        if (answer == 'y') { draw = true; }
        else { draw = false; }
        return draw;
    }
}

// Displays whether the player won or not (useless, based on assigment instructions)
void HumanPlayer::announce(const char* message) {
    cout << message << endl << endl;
}

void HumanPlayer::doubleDown() {

}

void HumanPlayer::split() {
    // create second hand
    cout << "Splitting....." << endl;
}

// Asks player to input their bet amount
void HumanPlayer::requestBet() {
    double current_bet = getBet();
    double reset_bet = 0;
    cout << "Please enter your bet amount: ";
    cin >> reset_bet;
    cout << endl;
    setBet(reset_bet);
    double current_balance = getBalance();
    setBalance(current_balance - (reset_bet - current_bet));
}

void HumanPlayer::setBet(double amount) {
    m_bet = amount;
}

double HumanPlayer::getBet() {
    return m_bet;
}

void HumanPlayer::displayBet() {
    cout << "You current bet is: " << m_bet << endl << endl;
}

void HumanPlayer::setBalance(double p_balance) {
    m_balance = p_balance;
}

double HumanPlayer::getBalance() {
    return m_balance;
}

void HumanPlayer::displayBalance() {
    cout << "Your current balance is: " << m_balance << endl << endl;
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

void BlackJackGame::addPlayer(const HumanPlayer& p_player) {
    m_player = p_player;
}

void BlackJackGame::addDeck(const Deck &p_deck) {
    m_deck = p_deck;
}

ComputerPlayer& BlackJackGame::getCasino() {
    return m_casino;
}

HumanPlayer& BlackJackGame::getPlayer() {
    return m_player;
}

// Sets up game (casino, player and deck) and executes game loop
void BlackJackGame::play() {

    // create Deck and shuffle
    Deck deck = Deck();
    deck.Populate();
    deck.shuffle();
    addDeck(deck);

    // deal and display cards to computer (1) and player (2)
    m_casino.getHand().add(deck.deal());
    cout << "Casino: ";
    m_casino.getHand().displayHand();
    cout << endl;

    m_player.getHand().add(deck.deal());
    m_player.getHand().add(deck.deal());
    cout << "Player: ";
    m_player.getHand().displayHand();
    cout << endl;

    // check if blackjack
    if (m_player.getHand().getTotal() == 21)
    {
        m_player.setBet(m_player.getBet() * 2.5);
        m_player.announce("BlackJack! Player wins.");
        m_player.displayBet();
    } else if (getPlayer().getHand().hasPair()) {

        // ask player is they want to split
        char answ;
        cout << "Would you like to split? (y/n):";
        cin >> answ;
        cout << endl;
        if (answ == 'y') {
            getPlayer().split();
        }

    } else {

        // ask player if they would like to double down
        // ask if player wants to draw, loop until they don't want to draw anymore or are busted (immediately lose)
        while (m_player.isDrawing())
        {
            m_player.getHand().add(deck.deal());
            cout << "Player: ";
            m_player.getHand().displayHand();
            cout << endl;
        }

        if (m_player.isBusted()) {
            m_player.setBet(0);
            m_player.announce("Player busts.");
            m_player.displayBet();
        } else {
            // computer draws until not able to
            while (m_casino.isDrawing()) {
                m_casino.getHand().add(deck.deal());
                cout << "Casino: ";
                m_casino.getHand().displayHand();
                cout << endl;
            }

            if (m_casino.isBusted())
            {
                // if computer busts = player wins
                m_player.setBet(m_player.getBet() * 2);
                m_player.announce("Casino busts. Player wins.");
                m_player.displayBet();

            } else {

                // compare values of player and computer and announce result
                if (m_player.getHand().getTotal() == m_casino.getHand().getTotal())
                {
                    m_player.announce("Push: no one wins.");
                    m_player.displayBet();
                }
                else if (m_player.getHand().getTotal() > m_casino.getHand().getTotal()) {
                    m_player.setBet(m_player.getBet() * 2);
                    m_player.announce("Player wins.");
                    m_player.displayBet();
                }
                else {
                    m_player.setBet(0);
                    m_player.announce("Casino wins.");
                    m_player.displayBet();
                }
            }
        }

    }
}
