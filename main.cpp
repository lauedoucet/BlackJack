/*
    Copyright 2020, Laurence Doucet, All rights reserved
*/

#include "blackjack.h"
using namespace std;

int main()
{
    cout << "\t Welcome to the COMP322 Blackjack game!" << endl << endl;

    BlackJackGame game;
    HumanPlayer player = HumanPlayer();
    ComputerPlayer casino = ComputerPlayer();
    game.addPlayer(player);
    game.addCasino(casino);

    bool playAgain = true;

    game.getPlayer().displayBalance();
    cout << endl;

    double initial_bet = 0;
    cout << "Please enter the amount of your first bet: ";
    cin >> initial_bet;
    cout << endl;
    game.getPlayer().setBet(initial_bet);
    double current_balance = game.getPlayer().getBalance();
    game.getPlayer().setBalance(current_balance - initial_bet);

    bool play_again = true;
    char answer;

        while (play_again)
        {
            game.getPlayer().displayBalance();
            game.getPlayer().displayBet();
            cout << endl;

            game.play();
            game.getCasino().getHand().clear();
            game.getPlayer().getHand().clear();

            cout << "Would you like another round? (y/n): ";
            cin >> answer;
            cout << endl << endl;

            if (answer == 'y') {
                cout << "Would you like to reset your bet? (y/n): ";
                cin >> answer;
                cout << endl;
                if (answer == 'y') {
                    double current_bet = game.getPlayer().getBet();
                    double reset_bet = 0;
                    cout << "Please enter the reset amount: ";
                    cin >> reset_bet;
                    cout << endl;
                    game.getPlayer().setBet(reset_bet);
                    current_balance = game.getPlayer().getBalance();
                    game.getPlayer().setBalance(current_balance - (reset_bet - current_bet));
                }
                play_again = true;
            }
            else {
                play_again = false;
            }
        }

    char goodbye;
    cout << "Game over!" << endl << "Press any key to say goodbye! " << endl;
    cin >> goodbye;

    return 0;
}