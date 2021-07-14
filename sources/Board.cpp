#include "Board.hpp"

using namespace std;

namespace pandemic{ 

    int &Board::operator[](City city){
        return this->disease_level[city];
    }

    std::ostream& operator<<(ostream& out, Board& board){
        for(auto& level : board.disease_level){
            out << "[" << name_of_city.at(level.first) << ", " << level.second << "]" << endl;
        }
        for(size_t i = 0; i < 4; i++){
            out << "the color of cure is: " << colors.at(i);
        }
        for(const auto& station : board.research_station){
            out << "Research stations existed: " << name_of_city.at(station) << endl;
        }
        return out;
    }
    bool Board::is_clean(){
        for(auto& city : disease_level){
            if(city.second != 0){
                return false;
            }
        }
        return true;
    }

    void Board::remove_cures(){
        discovered_cure.clear();
    }

    void Board::remove_stations(){
        this->research_station.clear();
    }

    void Board::build(City city){
        this->research_station.insert(city);
    }

    void Board::set_cure(Color col){
        this->discovered_cure.insert(col);
    }
};
