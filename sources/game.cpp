//
// Created by super on 3/23/23.
//

#include "game.hpp"
#include "player.hpp"
#include "card.hpp"
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <iostream>     // std::cout
#include <array>        // std::array
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
using namespace ariel;
using namespace std;

Game::Game(Player& player1, Player& player2): p1(player1), p2(player2){
    table_card_count = 0;
    p1.currently_playing = true;
    p2.currently_playing = true;
    sort_cards();
}

void Game::sort_cards(){
    vector<Card> cards_arr = {Card("Ace of Hearts", 1), Card("Ace of Diamonds", 1), Card("Ace of Clubs", 1), Card("Ace of Spades", 1),
                        Card("2 of Hearts", 2), Card("2 of Diamonds", 2), Card("2 of Clubs", 2), Card("2 of Spades", 2),
                        Card("3 of Hearts", 3), Card("3 of Diamonds", 3), Card("3 of Clubs", 3), Card("3 of Spades", 3),
                        Card("4 of Hearts", 4), Card("4 of Diamonds", 4), Card("4 of Clubs", 4), Card("4 of Spades", 4),
                        Card("5 of Hearts", 5), Card("5 of Diamonds", 5), Card("5 of Clubs", 5), Card("5 of Spades", 5),
                        Card("6 of Hearts", 6), Card("6 of Diamonds", 6), Card("6 of Clubs", 6), Card("6 of Spades", 6),
                        Card("7 of Hearts", 7), Card("7 of Diamonds", 7), Card("7 of Clubs", 7), Card("7 of Spades", 7),
                        Card("8 of Hearts", 8), Card("8 of Diamonds", 8), Card("8 of Clubs", 8), Card("8 of Spades", 8),
                        Card("9 of Hearts", 9), Card("9 of Diamonds", 9), Card("9 of Clubs", 9), Card("9 of Spades", 9),
                        Card("10 of Hearts", 10), Card("10 of Diamonds", 10), Card("10 of Clubs", 10), Card("10 of Spades", 10),
                        Card("Jack of Hearts", 11), Card("Jack of Diamonds", 11), Card("Jack of Clubs", 11), Card("Jack of Spades", 11),
                        Card("Queen of Hearts", 12), Card("Queen of Diamonds", 12), Card("Queen of Clubs", 12), Card("Queen of Spades", 12),
                        Card("King of Hearts", 13), Card("King of Diamonds", 13), Card("King of Clubs", 13), Card("King of Spades", 13)};


    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(cards_arr.begin(), cards_arr.end(), default_random_engine(seed));

    for(size_t i = 0; i < 52; i++){
        if(i % 2 == 0) p1.stack.push(cards_arr.at(i));
        else p2.stack.push(cards_arr.at(i));
    }
}

void Game::playTurn(){
    if(p1.name == p2.name){
        std::cout << "both players cannot have the same name!\n";
        throw std::exception();
    }
    /*if(p1.currently_playing == true || p2.currently_playing == true){
        std::cout << "one player cannot play in 2 games simultaneously!\n";
        throw std::exception();
    }*/
    if(game_started == false && ((p1.stacksize() != 26) || (p1.cards_taken != 0) ||
                                 (p2.stacksize() != 26) || (p2.cards_taken != 0))){
        std::cout << "game's stats wasn't defined currectly\n";
        throw exception();
    }
    if(game_finished == true){
        std::cout << "you cannot play anymore, the game has finished\n";
        throw exception();
    }
    game_started = true;
    if(p1.stack.empty() || p2.stack.empty()){
        return;
    }
    p1.last_card_drawn = p1.stack.front();
    p1.stack.pop();
    p2.last_card_drawn = p2.stack.front();
    table_card_count += 2;
    p2.stack.pop();
    string log = "";
    while(p1.last_card_drawn.compareTo(p2.last_card_drawn) == 0){
        p1.playerStats.draw_amount ++;
        p2.playerStats.draw_rate ++;
        int counter = 0;
        while(counter < 2){
            if(p1.stack.empty() || p2.stack.empty()){
                return;
            }
            p1.stack.pop();
            p2.stack.pop();
            table_card_count+= 2;
            counter++;
        }
        if(p1.stack.empty() || p2.stack.empty()){
            return;
        }
        p1.last_card_drawn = p1.stack.front();
        p1.stack.pop();
        p2.last_card_drawn = p2.stack.front();
        p2.stack.pop();
        table_card_count += 2;
        if(p1.last_card_drawn.card_type == p2.last_card_drawn.card_type)
            log += ("draw. " + p1.name + " played " + p1.last_card_drawn.card_name + ". " + p2.name + " played " +
                        p2.last_card_drawn.card_name + ". ");
    }
    if(p1.last_card_drawn.compareTo(p2.last_card_drawn) == 1){
        current_turn_winner = p1;
        p1.cards_taken += table_card_count;
        table_card_count = 0;
        log += ("draw. " + p1.name + " played " + p1.last_card_drawn.card_name + ". " + p2.name + " played " +
                p2.last_card_drawn.card_name + ". " + current_turn_winner.name + " won.");
    }
    else if(p1.last_card_drawn.compareTo(p2.last_card_drawn) == -1){
        current_turn_winner = p2;
        p2.cards_taken += table_card_count;
        cout << "p2 cards taken: " << p2.cardesTaken() << endl;
        cout << "table card count: " << table_card_count << endl;
        table_card_count = 0;
        log += ("draw. " + p1.name + " played " + p1.last_card_drawn.card_name + ". " + p2.name + " played " +
                p2.last_card_drawn.card_name + ". " + current_turn_winner.name + " won.");
    }
    logs_queue.push(log);
    if(p1.stacksize() == 0 || p2.stacksize() == 0){
        return;
    }
}


void Game::printLastTurn(){
    if(game_started == false){
        std::cout << "you cannot print the last turn before the game has started\n";
        throw std::exception();
    }
    cout << logs_queue.back() << endl;
}

void Game::playAll(){
    if(game_started == false && ((p1.stacksize() != 26) || (p1.cards_taken != 0) ||
                                 (p2.stacksize() != 26) || (p2.cards_taken != 0))){
        std::cout << "game's stats wasn't defined currectly\n";
        throw std::exception();
    }
    if(game_finished == true){
        std::cout << "you cannot play anymore, the game has finished\n";
        throw std::exception();
    }
    game_started = true;
    int counter = 0;
    while((p1.stacksize() != 0 || p2.stacksize() != 0) && counter <= 26){
        playTurn();
        counter++;
    }
    p2.playerStats.games_count++;
    p1.playerStats.games_count++;
    p1.playerStats.cards_won += p1.cardesTaken();
    p2.playerStats.cards_won += p2.cardesTaken();
    if(p1.cardesTaken() > p2.cardesTaken()){
        game_winner = p1;
        p1.playerStats.winning_count++;
    }
    else if(p2.cardesTaken() > p1.cardesTaken()){
        game_winner = p2;
        p2.playerStats.winning_count++;
    }
    else{
        cout << "it's a tie\n";
        p1.playerStats.tie_count++;
        p2.playerStats.tie_count++;
    }
    p1.playerStats.win_rate = (p1.playerStats.winning_count/p1.playerStats.games_count);
    p1.playerStats.tie_rate = (p1.playerStats.tie_count/p1.playerStats.games_count);
    p2.playerStats.win_rate = (p2.playerStats.winning_count/p2.playerStats.games_count);
    p2.playerStats.tie_rate = (p2.playerStats.tie_count/p2.playerStats.games_count);
    p1.playerStats.draw_rate = (p1.playerStats.draw_amount/26);
    p2.playerStats.draw_rate = (p2.playerStats.draw_amount/26);
    p1.currently_playing = false;
    p2.currently_playing = false;
    game_finished = true;
}

void Game::printWiner(){
    if(game_started == false){
        std::cout << "you cannot print the winner before the game has started or ended\n";
        throw std::exception();
    }
    cout << "the winner is: " << game_winner.name << endl;
}
void Game::printLog(){
    if(game_started == false){
        std::cout << "you cannot print the game logs before the game has started\n";
        throw std::exception();
    }
    int counter = 0;
    while(counter < logs_queue.size()){
        string log = logs_queue.front();
        cout << log << endl;
        logs_queue.pop();
        logs_queue.push(log);
        counter++;
    }
}

void Game::printStats(){
    cout << "print stats for player: " << p1.name << endl;
    cout << p1.name << " played " << p1.playerStats.games_count << " games\n";
    cout << p1.name << " won " << p1.playerStats.winning_count << " of them\n";
    cout << p1.name << " finished " << p1.playerStats.tie_count << " of them in tie\n";
    cout << "winning rate: " << p1.playerStats.win_rate << endl;
    cout << "tie rate: " << p1.playerStats.tie_rate << endl;
    cout << "draw rate: " << p1.playerStats.draw_rate << endl;
    cout << "won total of " << p1.playerStats.cards_won << " cards" << endl;

    cout << "print stats for player: " << p2.name << endl;
    cout << p2.name << " played " << p2.playerStats.games_count << " games\n";
    cout << p2.name << " won " << p2.playerStats.winning_count << " of them\n";
    cout << p2.name << " finished " << p2.playerStats.tie_count << " of them in tie\n";
    cout << "winning rate: " << p2.playerStats.win_rate << endl;
    cout << "tie rate: " << p2.playerStats.tie_rate << endl;
    cout << "draw rate: " << p2.playerStats.draw_rate << endl;
    cout << "won total of " << p2.playerStats.cards_won << " cards" << endl;
}


