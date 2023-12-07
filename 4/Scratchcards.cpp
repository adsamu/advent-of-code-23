#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>


std::vector<std::string> split(const std::string& str, char delimiter) {
	std::vector<std::string> result;
    	std::istringstream iss(str);
    	std::string token;

    	while (std::getline(iss, token, delimiter)) {
    	    	result.push_back(token);
    	}

    	return result;
}



int getWinnings(std::string line){

	std::vector<std::string> winVec{split(split(line, '|')[0], ' ')};
	std::set<std::string> winningNumbers(winVec.begin(), winVec.end());

	std::vector<std::string> myNumbers{split(split(line, '|')[1], ' ')};
	
	int wins{};
	for (auto nr : myNumbers){
		if (winningNumbers.contains(nr)){
			if(!nr.empty()){

				std::cout << nr << std::endl;
				wins++;
			}
		}
	}
	return wins;
}

int main (int argc, char *argv[]) {
	std::ifstream file;
	std::string line;
	file.open("input.txt");
	int sum{};

	// int wins{getWinnings(split("Card 1: 41  48   83 86 17 | 83 86  6 31 17  9 48 53", ':')[1])};
	// std::cout << wins << std::endl;
	// sum += wins > 0 ? std::pow(2, wins - 1) : 0;
	while (std::getline(file, line))
	{	
		int wins{getWinnings(split(line, ':')[1])};
		sum += wins > 0 ? std::pow(2, wins - 1) : 0;
	}
	file.close();
	std::cout << sum << std::endl;
	return 0;
}
