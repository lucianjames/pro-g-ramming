#include <iostream>
#include <string>

int upperAlphaStart = 65;
int upperAlphaEnd = 90;
int lowerAlphaStart = 97;
int lowerAlphaEnd = 122;

char lowerCaseRot13Character(char c){
	if(c+13 <= 'z'){ return c+13; }
	else{ return c-13; }
}

char upperCaseRot13Character(char c){
	if(c+13 <= 'Z'){ return c+13; }
	else{ return c-13; }
}

std::string Rot13(std::string input){
	// Input is passed by value, so we can modify it
	// Iterate through all characters in string
	for(int i=0; i<input.length(); i++){
		if(isalpha(input[i])){ // Must be a letter
			if(islower(input[i])){ // Different functions for upper and lower case because of ASCII values of A and a being different (for example)
				input[i] = lowerCaseRot13Character(input[i]);
			}
			else{
				input[i] = upperCaseRot13Character(input[i]);
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
