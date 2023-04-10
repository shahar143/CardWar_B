//
// Created by super on 3/23/23.
//

#include "player.hpp"
using namespace ariel;
using namespace std;

Player::Player(const string& name){
    if(name.empty()){
        cout << "name can't be empty!\n";
        throw std::exception();
    }
    this->name = name;
}

void Player::update_rates(){
    win_rate = float(winning_count) / float(games_count);
    draw_rate = float(draw_amount) / float(cards_per_player);
    tie_rate = float(tie_count) / float(games_count);
}
void Player::update_games_count(){
    games_count++;
    update_rates();
}
void Player::update_winning_count(){
    winning_count++;
    update_games_count();
}
void Player::update_tie_count(){
    tie_count++;
    update_games_count();
}
void Player::update_cards_won(){
    cards_won += cardesTaken();
    update_rates();
}
void Player::update_draw_amount(){
    draw_amount++;
    update_rates();
}

const Card& Player::drawCard(){
    last_card_drawn = stack.front();
    stack.pop();
    return last_card_drawn;
}

void Player::print_stats(){
    cout << "player name: " << name << endl;
    cout << "win rate: " << win_rate << endl;
    cout << "draw rate: " << draw_rate << endl;
    cout << "tie rate: " << tie_rate << endl;
    cout << "games count: " << games_count << endl;
    cout << "winning count: " << winning_count << endl;
    cout << "tie count: " << tie_count << endl;
    cout << "cards won: " << cards_won << endl;
    cout << "draw amount: " << draw_amount << endl;
}