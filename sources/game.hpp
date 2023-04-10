//
// Created by super on 3/23/23.
//

#ifndef CARDWAR_A_GAME_HPP
#define CARDWAR_A_GAME_HPP

#include "card.hpp"
#include "player.hpp"
#include <iostream>
using namespace std;

namespace ariel{
    class Game {
    private:
        Player& p1;
        Player& p2;
        bool game_started = false;
        bool game_finished = false;
        queue<string> logs_queue;
        Player current_turn_winner;
        int table_card_count;
        Player game_winner;

        /*
         * @brief: this function will sort the cards and divide them between 2 player's stacks
         */
        void sort_cards();

    public:
        Game(Player& player1, Player& player2);
        void playTurn();
        void printLastTurn();
        void playAll();
        void printWiner();
        void printLog();
        void printStats();
    };
}




#endif //CARDWAR_A_GAME_HPP
