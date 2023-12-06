#include <cstddef>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <tuple>
#include <vector>
#include <map>
#include <array>
// #include <string>


class Grid {
public:
    Grid(std::ifstream& file);
    // void print() const; // Utility function to print the grid
    
    std::vector<std::string> grid;
    int Parse();
    int Parse2();
private:
    int getNr(std::pair<size_t, size_t> const& pos);
    int getPartNr(size_t const& row, size_t const& col);
    std::vector<std::pair<size_t, size_t>> getNbrNrs(size_t row, size_t col);
    bool checkSymbols(std::vector<std::pair<size_t, size_t>> const& numberIndices);
    void fillRow(const std::string& line, size_t row);

    size_t width, length;
};

Grid::Grid(std::ifstream& file) {

    std::string line;
    while (std::getline(file, line)) {
        if (grid.empty()) { // First line, determine the width
            width = line.length();
        }
	grid.push_back(line);
        
    }
    length = grid.size();
    file.close();
}

int Grid::Parse(){
    std::vector<std::pair<size_t, size_t>> numberIndices;
    long int sum{};

    for (size_t i = 0; i < this->length; i++){
	for (size_t j = 0; j < this->width; j++){
	    char ch{this->grid[i][j]};
	    // std::cout << ch << std::endl;
	    if (ch == '*'){
		sum += this->getPartNr(i, j);

	    } 	
	}
    } 
    return sum;
}

/*
1 .	
1 * 
1 1 
*/
int Grid::getPartNr(size_t const& row, size_t const& col){
    // std::cout << row << col << std::endl;
    std::vector<std::pair<size_t, size_t>> adjNr{this->getNbrNrs(row, col)};
    
    if (adjNr.size() == 2){
	return this->getNr(adjNr[0]) * this->getNr(adjNr[1]);
    }
    return 0;
}

int Grid::getNr(std::pair<size_t, size_t> const& pos){
    std::string number{};
    size_t forward{pos.second};
    size_t back{pos.second-1};
    // std::cout << pos.first << ' ' << pos.second << std::endl;
    while (true){
	char fch = this->grid[pos.first][forward];
	char bch = this->grid[pos.first][back];
	if (fch >= '0' && fch <= '9'){
	    number += fch;
	    forward++;
	} else if (bch >= '0' && bch <= '9'){
	    number = bch + number;
	    back--;
	} else {
	    std::cout << number << std::endl;
	    return std::stoi(number);
	}	
    }
}

std::vector<std::pair<size_t, size_t>> Grid::getNbrNrs(size_t row, size_t col){
    std::vector<std::pair<size_t, size_t>> nbrs;
    bool numberFound{false};
    for (size_t i = row > 0 ? row - 1 : 0; i <= row + 1 && i < length; i++) {
	std::pair<size_t, size_t> pos{};
	for (size_t j = col > 0 ? col - 1 : 0; j <= col + 1 && j < width; j++) {
	    char ch{this->grid[i][j]};
	    if (!numberFound && ch >= '0' && ch <= '9'){
		numberFound = true;
	    }else if (numberFound && (ch < '0' || ch > '9')){
		nbrs.push_back(pos);
		numberFound = false;
	    }
	    pos = {i, j};
	} 
	if (numberFound){
	    nbrs.push_back(pos);
	    numberFound = false;
	}
    } 
    // std::cout << nbrs[0].second<< nbrs[1].second << std::endl;
    return nbrs;
}
// int Grid::Parse(){
//     std::vector<std::pair<size_t, size_t>> numberIndices;
//     int sum{};
//     std::string number{};
//
//     for (size_t i = 0; i < this->length; i++){
// 	for (size_t j = 0; j < this->width; j++){
// 	    char ch{this->grid[i][j]};
// 		
// 	    if (ch >= '0' && ch <= '9'){
// 		number += ch;
// 		numberIndices.push_back({i, j});
// 	    } else if (!number.empty() && this->checkSymbols(numberIndices)) {
// 		std::cout << number << std::endl;
// 		sum += std::stoi(number);
// 		number.clear();
// 		numberIndices.clear();
// 		
// 	    } else if (!number.empty()){
// 		number.clear();
// 		numberIndices.clear();
// 	    }
// 	}
//     } 
//     return sum;
// }

// bool Grid::checkSymbols(std::vector<std::pair<size_t, size_t>> const& numberIndices){
//     std::string str;
//     for(auto pairs : numberIndices){
// 	str += this->getNeighbours(pairs.first, pairs.second);
//     }
//     for (auto ch : str){
// 	if ( (ch < '0' || ch > '9') && ch != '.'){
// 	    std::cout << str << std::endl;
// 	    return true;
// 	}
//     }    
//     return false;
// }



int main (int argc, char *argv[]) {
	
    std::ifstream file;
    std::string line;
    file.open("input.txt");
    Grid grid{file};	
    file.close();
    long int sum{grid.Parse()};
    std::cout << sum << std::endl;
    return sum;
}
