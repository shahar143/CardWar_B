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

constexpr float cards_per_player = 26;

using namespace std;
namespace ariel{
    class Player{
    private:
        string name;
        bool currently_playing = false;
        int cards_taken = 0;
        Card last_card_drawn = Card();
        queue<Card> stack;

        //////////////////////////////////////////////////////////
        //player stats:
        //////////////////////////////////////////////////////////
        float win_rate = 0;
        int cards_won = 0;
        float draw_rate = 0;
        int draw_amount = 0;
        float tie_rate = 0;
        int games_count = 0;
        int winning_count = 0;
        int tie_count = 0;
        /////////////////////////////////////////////////////////
    public:

        Player(const string& name);
        Player() = default;

        //player initializers:
        const string& get_name() const{return name;}
        void set_name(const string& name){this->name = name;}
        const bool& get_currently_playing() const{return currently_playing;}
        void set_currently_playing(bool choice){currently_playing = choice;}

        //stats updaters:
        void update_rates();
        void update_games_count();
        void update_winning_count();
        void update_tie_count();
        void update_cards_won();
        void update_draw_amount();

        //stats setters and getters:
        int stacksize() const{return int(stack.size());}
        int cardesTaken() const{return cards_taken;}
        const Card& drawCard();
        void addCard(const Card& card){stack.push(card);}
        void print_stats();

        void set_cards_taken(int amount){cards_taken = amount;}
        const Card& get_last_card_drawn() const{return last_card_drawn;}
        void set_last_card_drawn(const Card& card){last_card_drawn = card;}

    };
}



#endif //CARDWAR_A_PLAYER_HPP
