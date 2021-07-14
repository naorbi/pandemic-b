#include "Player.hpp"
#include "Board.hpp"
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

const int cards_of_cure = 5;

namespace pandemic{

    Player& Player::drive(City _city){
        if(connect_cities.at(_city).count(city) == 0 && connect_cities.at(city).count(_city) == 0){
            throw std::invalid_argument{"the city " + name_of_city.at(city) + " don't match with " + name_of_city.at(_city)};
        }
        if(city == _city){throw invalid_argument("you cannot drive this city this time");}
        city = _city;
        return *this;
    }

    Player& Player::fly_direct(City _city){
        if(card.count(_city) == 0){
            throw invalid_argument("you don't have card for the city " + name_of_city.at(_city));
        }
        if(city == _city){throw invalid_argument("you cannot fly this city this time");}
        card.erase(_city);
        city = _city;
        return *this;
    }

    Player& Player::fly_charter(City _city){
        if(card.count(city) == 0){
            throw invalid_argument("you don't have the " + name_of_city.at(city) + " card");
        }
        if(city == _city){throw invalid_argument("you cannot fly this city this time");}
        card.erase(city);
        city = _city;
        return *this;
    }

    Player& Player::fly_shuttle(City _city){
        if (board.get_research_station().count(city) == 0){
        throw invalid_argument(name_of_city.at(city) + " don't have research station");
        }
        if (board.get_research_station().count(_city) == 0){
        throw invalid_argument(name_of_city.at(_city) + " don't have research station");
        }
        if(city == _city){
            throw invalid_argument("you cannot fly this city this time");
        }
        city = _city;
        return *this;
    }
  
    Player& Player::build(){
        if(card.count(city) == 0){
            throw invalid_argument("you don't have card of the city " + name_of_city.at(city));
        }
        board.build(city);
        card.erase(city);
        return *this;
    }
    
    Player& Player::discover_cure(Color col){
        if(board.get_research_station().count(city) == 0){
            throw std::invalid_argument("There is not research station in the city " + name_of_city.at(city));
        }
        int counter = 0;
        for(const auto& t : card){
            if(colors_of_cities.at(t) == col){
                counter++;
            }
        }
        if(cards_of_cure > counter){
            throw std::invalid_argument("you have " + to_string(counter) +" of color " + colors.at(col) + " cards");
        }
        counter = 0;
        for(auto c = card.begin(); c != card.end(); counter++){
            if(colors_of_cities.at(*c) == col) {
                c = card.erase(c);
            }
            else {
                ++c;
            }
        }
        board.set_discovered_cure(col);
        return *this;
    }

    Player& Player::treat(City _city){
        if(city != _city){
            throw invalid_argument("you are not in the city " + name_of_city.at(_city));
        }
        if(board.disease_level[_city] == 0){
            throw invalid_argument("At " + name_of_city.at(_city) + " there is no disease cubes");
        }
        if(board.get_discovered_cure().count(colors_of_cities.at(_city)) != 0){
            board.disease_level[_city] = 0;
        }
        else{board.disease_level[_city]--;}
        return *this;
    }

    Player& Player::take_card(City _city){
        card.insert(_city);
        return *this;
    }

    void Player::remove_cards(){
        card.clear();
    }
};
