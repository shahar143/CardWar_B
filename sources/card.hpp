//
// Created by super on 3/23/23.
//

#ifndef CARDWAR_A_CARD_HPP
#define CARDWAR_A_CARD_HPP

#include <iostream>
using namespace std;

namespace ariel{
    class Card{
    private:
        int card_type = 0;
        string card_name;

    public:
        Card(string card_name, int card_number);
        Card() = default;

        /*
         * @return 1 if this card is bigger than the other card
         * @return -1 if this card is smaller than the other card
         * @return 0 if this card is equal to the other card
         */
        int compareTo(const Card& other) const;

        //getters:
        int getCardType() const {return card_type;}
        string getCardName() const {return card_name;}
    };
}

#endif //CARDWAR_A_CARD_HPP
