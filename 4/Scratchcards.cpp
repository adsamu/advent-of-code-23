#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>
#include <set>
#include <numeric>


std::vector<std::string> split(const std::string& str, char delimiter) {
	std::vector<std::string> result;
    	std::istringstream iss(str);
    	std::string token;

    	while (std::getline(iss, token, delimiter)) {
    	    	result.push_back(token);
    	}

    	return result;
}

size_t getWinnings(std::string line){

	std::vector<std::string> winVec{split(split(line, '|')[0], ' ')};
	std::set<std::string> winningNumbers(winVec.begin(), winVec.end());
	std::vector<std::string> myNumbers{split(split(line, '|')[1], ' ')};
	
	size_t wins{};
	for (auto nr : myNumbers){
		if (winningNumbers.contains(nr)){
			if(!nr.empty()){

				wins++;

			}
		}
	}
	return wins;
}

int scratchcards(std::vector<size_t>& cards, std::vector<size_t> const& winnings) {

	std::vector<int> sums(cards.size(), 1);
	for(auto card : cards) {
		for (size_t copy = card+1; copy <= card+winnings[card]; copy++) {
			if (copy < winnings.size()){

				sums[copy] += sums[card];

			}
		}
	}

	return std::accumulate(sums.begin(), sums.end(), 0);
}

int main (int argc, char *argv[]) {
	std::ifstream file;
	std::string line;
	std::vector<size_t> winnings;	
	std::vector<size_t> cardNrs{};
	size_t card{};
	int sum{};

	file.open("input.txt");
	while (std::getline(file, line))
	{	
		size_t wins{getWinnings(split(line, ':')[1])};
		winnings.push_back(wins);
		sum += wins > 0 ? std::pow(2, wins - 1) : 0;
		
		cardNrs.push_back(card);
		card++;

	}
	file.close();
	std::cout << "Part one: " << sum << std::endl;
	std::cout << "Part Two: "<< scratchcards(cardNrs, winnings) << std::endl;
	return 0;
}
