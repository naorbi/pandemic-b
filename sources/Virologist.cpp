#include "Virologist.hpp"

using namespace std;

namespace pandemic{

    // can treat all city with card of the city that he want to treat, without to be there.
    Player& Virologist::treat(City _city){
        if(card.count(_city) == 0 && city != _city){
            throw invalid_argument("You are not in city " + name_of_city.at(_city));
        }
        card.erase(_city);
        if(board.disease_level[_city] == 0){
            throw invalid_argument("At " + name_of_city.at(_city) + " no have disease cubes");
        }
        if(board.get_discovered_cure().count(colors_of_cities.at(city)) != 0){
            board.disease_level[_city] = 0;
            return *this;
        }
        board.disease_level[_city]--;
        return *this;
    }
};
