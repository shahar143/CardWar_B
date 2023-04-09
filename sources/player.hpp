//
// Created by super on 3/23/23.
//

#ifndef CARDWAR_A_PLAYER_HPP
#define CARDWAR_A_PLAYER_HPP
#include <string>
#include <utility>
#include <iostream>
#include <queue>
#include "card.hpp"

using namespace std;
namespace ariel{
    typedef struct playerStats{
        float win_rate = 0;
        int cards_won = 0;
        float draw_rate = 0;
        int draw_amount = 0;
        float tie_rate = 0;
        int games_count = 0;
        int winning_count = 0;
        int tie_count = 0;
    }PlayerStats;

    class Player{
    public:
        string name;
        bool currently_playing = false;
        queue<Card> stack;
        int cards_taken = 0;
        Card last_card_drawn;
        PlayerStats playerStats;

        Player(const string& name){
            if(name.empty()){
                cout << "name can't be empty!\n";
                throw std::exception();
            }
            this->name = name;
            cards_taken = 0;
            last_card_drawn = Card();
        }

        Player()= default;

        int stacksize() const{
            return int(stack.size());
        }
        int cardesTaken() const{
            return cards_taken;
        }

        queue<Card> get_stack() const{
            return stack;
        }

        Card get_last_card_drawn() const{
            return last_card_drawn;
        }

        void set_last_card_drawn(Card& card){
            last_card_drawn = card;
        }

        PlayerStats get_player_stats() const{
            return playerStats;
        }

        string get_name() const{
            return name;
        }

        bool get_currently_playing() const{
            return currently_playing;
        }

        void set_currently_playing(bool choice){
            currently_playing = choice;
        }
    };
}



#endif //CARDWAR_A_PLAYER_HPP
