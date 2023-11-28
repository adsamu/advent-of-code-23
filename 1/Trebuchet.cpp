#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
/*
part 1 answer: 54239 
part 2 answer: 55343
*/
int getValues(std::string line)
{
	auto head = line.begin();
	auto tail = line.end();
	while (true){

		if (*head < '0'  || *head > '9')
		{
			head++;

		} 
		else if (*tail < '0' || *tail > '9')
		{
			tail--;	
		}
		else {
			return std::stoi(std::string{*head} + std::string{*tail});
		}

	}
}

int getValues2(std::string line)
{
	std::map<std::string, int> translate{{"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4},
					      {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};
	std::set<std::string> digits = {"one", "two", "three", "four", "five", 
					"six", "seven", "eight", "nine", "zero"};
	auto head = line.begin();
	auto tail = line.end()-1;

	std::string headThree{"---"};
	std::string headFour{"----"};
	std::string headFive{"-----"};

	std::string tailThree{"---"};
	std::string tailFour{"----"};
	std::string tailFive{"-----"};
	int firstDigit, secondDigit;
	bool found{false};
	
	while(!found){

		if (*head >= '0' && *head <= '9')
		{
			firstDigit = std::stoi(std::string{*head});
			found = true;
		}  
		if (digits.contains(headThree) || 
	  	    digits.contains(headFour) ||
		    digits.contains(headFive))
		{
			firstDigit = (translate[headThree] + translate[headFour] + translate[headFive]);
			found = true;
		} 
		headThree += *head;
		headThree.erase(0, 1);

		headFour += *head;
		headFour.erase(0, 1);

		headFive += *head;
		headFive.erase(0, 1);
		head++;
	}
	found = false;
	while(!found){

		if (*tail >= '0' && *tail <= '9')
		{
			secondDigit = std::stoi(std::string{*tail});
			found = true;
		}  
		if (digits.contains(tailThree) || 
	  	    digits.contains(tailFour) ||
		    digits.contains(tailFive))
		{
			secondDigit = (translate[tailThree] + translate[tailFour] + translate[tailFive]);
			found = true;
		} 
			tailThree = *tail + tailThree;
			tailThree.pop_back();

			tailFour = *tail + tailFour;
			tailFour.pop_back();

			tailFive = *tail + tailFive;
			tailFive.pop_back();
		tail--;
	}

	return 10 * firstDigit + secondDigit;

}

int main (int argc, char *argv[]) {
	
	std::ifstream file;
	std::string line;
	file.open("input.txt");
	int sum{};

	while (std::getline(file, line))
	{
		sum += getValues2(line)	;
	}
	file.close();
	std::cout << sum << std::endl;
	return 0;
}	
