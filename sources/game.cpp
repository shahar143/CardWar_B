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
    p1.set_currently_playing(true);
    p2.set_currently_playing(true);
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
        if(i % 2 == 0) p1.addCard(cards_arr.at(i));
        else p2.addCard(cards_arr.at(i));
    }
}

void Game::playTurn(){
    if(p1.get_name() == p2.get_name()){
        cout << "both players cannot have the same name!\n";
        throw exception();
    }
    if((!game_started) && ((p1.stacksize() != 26) || (p1.cardesTaken() != 0) ||
                                 (p2.stacksize() != 26) || (p2.cardesTaken() != 0))){
        cout << "game's stats wasn't defined currectly\n";
        throw exception();
    }
    if(game_finished){
        cout << "you cannot play anymore, the game has finished\n";
        throw exception();
    }
    game_started = true;
    if(p1.stacksize() == 0 || p2.stacksize() == 0){
        return;
    }
    p1.set_last_card_drawn(p1.drawCard());
    p2.set_last_card_drawn(p2.drawCard());
    table_card_count += 2;
    string log = "";
    while(p1.get_last_card_drawn().compareTo(p2.get_last_card_drawn()) == 0){
        p1.update_draw_amount();
        p2.update_draw_amount();
        int counter = 0;
        while(counter < 2){
            if(p1.stacksize() == 0 || p2.stacksize() == 0){
                return;
            }
            p1.drawCard();
            p2.drawCard();
            table_card_count+= 2;
            counter++;
        }
        if(p1.stacksize() == 0 || p2.stacksize() == 0){
            return;
        }
        p1.set_last_card_drawn(p1.drawCard());
        p2.set_last_card_drawn(p2.drawCard());
        table_card_count += 2;
        if(p1.get_last_card_drawn().getCardType() == p2.get_last_card_drawn().getCardType())
            log += ("draw. " + p1.get_name() + " played " + p1.get_last_card_drawn().getCardName() + ". " + p2.get_name() + " played " +
                        p2.get_last_card_drawn().getCardName() + ". ");
    }
    if(p1.get_last_card_drawn().compareTo(p2.get_last_card_drawn()) == 1){
        current_turn_winner = p1;
        p1.set_cards_taken(p1.cardesTaken() + table_card_count);
        table_card_count = 0;
        log += ("draw. " + p1.get_name() + " played " + p1.get_last_card_drawn().getCardName() + ". " + p2.get_name() + " played " +
                p2.get_last_card_drawn().getCardName() + ". " + current_turn_winner.get_name() + " won.");
    }
    else if(p1.get_last_card_drawn().compareTo(p2.get_last_card_drawn()) == -1){
        current_turn_winner = p2;
        p2.set_cards_taken(p2.cardesTaken() + table_card_count);
        table_card_count = 0;
        log += ("draw. " + p1.get_name() + " played " + p1.get_last_card_drawn().getCardName() + ". " + p2.get_name() + " played " +
                p2.get_last_card_drawn().getCardName() + ". " + current_turn_winner.get_name() + " won.");
    }
    logs_queue.push(log);
    if(p1.stacksize() == 0 || p2.stacksize() == 0){
        return;
    }
}

void Game::printLastTurn(){
    if(!game_started){
        cout << "you cannot print the last turn before the game has started\n";
        throw exception();
    }
    cout << logs_queue.back() << endl;
}

void Game::playAll(){
    if((!game_started) && ((p1.stacksize() != 26) || (p1.cardesTaken() != 0) ||
                                 (p2.stacksize() != 26) || (p2.cardesTaken() != 0))){
        cout << "game's stats wasn't defined currectly\n";
        throw exception();
    }
    if(game_finished){
        cout << "you cannot play anymore, the game has finished\n";
        throw exception();
    }
    game_started = true;
    int counter = 0;
    while(p1.stacksize() != 0 && p2.stacksize() != 0 && counter <= 26){
        playTurn();
        counter++;
    }
    if(p1.stacksize() != 0 || p2.stacksize() != 0){
        queue<Card> tmp;
        while(p1.stacksize() != 0){
            tmp.push(p1.drawCard());
        }
        while(p2.stacksize() != 0){
            tmp.push(p2.drawCard());
        }
        while(!tmp.empty() && (tmp.size() % 2 == 0)){
            p1.addCard(tmp.front());
            tmp.pop();
            p2.addCard(tmp.front());
            tmp.pop();
        }
    }
    p2.update_games_count();
    p1.update_games_count();
    p1.update_cards_won();
    p2.update_cards_won();
    if(p1.cardesTaken() > p2.cardesTaken()){
        game_winner = p1;
        p1.update_winning_count();
    }
    else if(p2.cardesTaken() > p1.cardesTaken()){
        game_winner = p2;
        p2.update_winning_count();
    }
    else{
        cout << "it's a tie\n";
        p1.update_tie_count();
        p2.update_tie_count();
    }
    p1.set_currently_playing(false);
    p2.set_currently_playing(false);
    game_finished = true;
}

void Game::printWiner(){
    if(!game_started){
        cout << "you cannot print the winner before the game has started or ended\n";
        throw exception();
    }
    cout << "the winner is: " << game_winner.get_name() << endl;
}
void Game::printLog(){
    if(!game_started){
        cout << "you cannot print the game logs before the game has started\n";
        throw exception();
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
    p1.print_stats();
    p2.print_stats();
}


