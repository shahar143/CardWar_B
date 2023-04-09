//
// Created by super on 3/23/23.
//

#ifndef CARDWAR_A_CARD_HPP
#define CARDWAR_A_CARD_HPP

#include <iostream>

namespace ariel{
    class Card{
    public:
        int card_type = 0;
        std::string card_name;

        Card(std::string card_name, int card_number);
        Card() = default;
        int compareTo(const Card& other);

    };
}

#endif //CARDWAR_A_CARD_HPP
