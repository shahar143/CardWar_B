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
        /*
         * @param card_name: the name of the card
         * @param card_number: the number of the card
         * implementation is not exposed to the user. only game can create cards and assign them to players.
         */
        Card(string card_name, int card_number);
        Card() = default;

        /*
         * @return 1 if this card is bigger than other
         * @return -1 if this card is smaller than
         * @return 0 if this card is equal to other
         */
        int compareTo(const Card& other) const;

        //getters:
        int getCardType() const {return card_type;}
        string getCardName() const {return card_name;}
    };
}

#endif //CARDWAR_A_CARD_HPP
