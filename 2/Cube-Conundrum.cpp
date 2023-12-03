#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

/*
blue
red
green

split on ;
split on ,
split on ' '

if map[color] < value;
map[color] = value

 */

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::istringstream iss(str);
    std::string token;

    while (std::getline(iss, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}

std::string removeChars(const std::string& str, char ch1, char ch2){
	std::string result;
	for (char ch : str) {
		if (ch != ch1 && ch != ch2) {
		    result += ch;
		}
	}
	return result;
}

int powerOfSet(std::string line){
	std::map<std::string, int> m{{"blue", 0}, {"red", 0}, {"green", 0}};
	std::string cleanString = removeChars(split(line, ':')[1], ',', ';');
	std::vector<std::string> words{split(cleanString, ' ')};

	auto it{words.begin()};
	it++;

	while (it != words.end()){
		int value{std::stoi(*it)};
		std::string color{*std::next(it)};

		std::cout << value << color << std::endl;
		if (m[color] < value){
			m[color] = value;
		}
		it += 2;
	}
	std::cout << m["blue"] << " blue, " << m["green"] << " green, "<<  m["red"] <<" red" << std::endl;
	return m["blue"] * m["green"] * m["red"];
}

bool isPossible(std::string line){
	
	std::map<std::string, int> m{{"blue", 0}, {"red", 0}, {"green", 0}};
	std::string cleanString = removeChars(split(line, ':')[1], ',', ';');
	std::vector<std::string> words{split(cleanString, ' ')};
	auto it{words.begin()};
	it++;

	while (it != words.end()){
		int value{std::stoi(*it)};
		std::string color{*std::next(it)};

		if (m[color] < value){
			m[color] = value;
		}
		it += 2;
	}
	
	if (m["blue"] <= 14 && m["green"] <= 13 && m["red"] <= 12){
		return true;
	} else{
		return false;
	}
}


int main (int argc, char *argv[]) {
	
	std::ifstream file;
	std::string line;
	file.open("input.txt");
	int sum{};

	int count{1};
	while (std::getline(file, line))
	{	
		std::cout << count << std::endl;
		//part2
		sum += powerOfSet(line);
		// part1
		// if (isPossible(line)){
		// 	sum += count;
		// }
		count++; 	
	}
	file.close();
	std::cout << sum << std::endl;
	return 0;
}	
