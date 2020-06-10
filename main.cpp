/* 
	Copyright 2020, Laurence Doucet, All rights reserved
*/

#include "blackjack.h"

using namespace std;

int main()
{
    cout << "\t Welcome to the COMP322 Blackjack game!" << endl << endl;

    double initial_bet = 0;
    cout << "Please enter the amount of your first bet: " << endl;
    cin >> (double) initial_bet;

    BlackJackGame game;
    HumanPlayer player = HumanPlayer(initial_bet);
    ComputerPlayer casino = ComputerPlayer();
    game.addPlayer(player);
    game.addCasino(casino);

    bool playAgain = true;
    char answer;
    while (playAgain)
    {
        game.play();
        // TODO: doesn't clear the hands :((
        player.getHand().clear();
        casino.getHand().clear();

        cout << "Would you like another round? (y/n): ";
        cin >> answer;
        cout << endl << endl;
        playAgain = (answer == 'y' ? true : false);

        if (answer == 'y') {
            cout << "Would you like to reset your bet? (y/n): ";
            cin >> answer;
            if (answer == 'y') {
                double reset_bet = 0;
                cout << "Please enter the reset amount: " << endl;
                cin >> reset_bet;
                player.setBet(reset_bet);
            }
        }
    }

    cout << "Game over!";

    return 0;
}