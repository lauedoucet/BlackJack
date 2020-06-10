/*
    Copyright 2020, Laurence Doucet, All rights reserved
*/

#include "blackjack.h"
using namespace std;

int main()
{
    cout << "\t Welcome to the COMP322 Blackjack game!" << endl << endl;

    /**************Game set up************************/
    BlackJackGame game;
    HumanPlayer player = HumanPlayer();
    ComputerPlayer casino = ComputerPlayer();
    game.addPlayer(player);
    game.addCasino(casino);

    game.getPlayer().displayBalance();
    cout << endl;
    game.getPlayer().requestBet();

    /***************Game loop*************************/
    bool play_again = true;
    char answer;
    while (play_again) {

        game.getPlayer().displayBalance();
        game.getPlayer().displayBet();
        cout << endl;

        game.play();

        /*********Clear hands in case they want to play a new round*****************/
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
                game.getPlayer().requestBet();
                play_again = true;
            }
        }
        else {
            play_again = false;
        }
    }
    char goodbye;
    cout << "Game over!" << endl << "Press any key to say goodbye :)" << endl;
    cin >> goodbye;

    return 0;
}