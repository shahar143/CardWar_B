//
// Created by super on 3/23/23.
//

#include "card.hpp"
#include <iostream>

using namespace ariel;

Card::Card(std::string card_name, int card_number): card_type(){
    this->card_type = card_number;
    this->card_name = card_name;
}

int Card::compareTo(const Card& other) const{
    if(this->card_type == 1){
        if(other.card_type != 2 && other.card_type != 1) return 1;
        else if(other.card_type == 2) return -1;
        else if(other.card_type == 1) return 0;
    }
    else if(other.card_type == 1){
        if(this->card_type != 2) return -1;
        else return 1;
    }
    else{
        if(this->card_type > other.card_type) return 1;
        else if(this->card_type < other.card_type) return -1;
        else return 0;
    }
    return 0;
}

