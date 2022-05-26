#include <iostream>
#include <string>

std::string Rot13(std::string input){
	// Input is passed by value, so we can modify it
	// Iterate through all characters in string
	for(int i=0; i<input.length(); i++){
		if(isalpha(input[i])){ // Must be a letter
			if(islower(input[i])){ // Different functions for upper and lower case because of ASCII values of A and a being different (for example)
				if(input[i]+13 <= 'z'){ input[i] += 13; }
				else{ input[i] -= 13; }
			}
			else{
				if(input[i]+13 <= 'Z'){ input[i] += 13; }
				else{ input[i] -= 13; }
			}
		}
	}
	return input;
}

int main(){
	std::string strng;

	// Get input
	std::cout << "Enter string:\n";
	std::getline(std::cin, strng);

	// Do rot13!
	std::cout << Rot13(strng) << std::endl;

	return 0;
}
