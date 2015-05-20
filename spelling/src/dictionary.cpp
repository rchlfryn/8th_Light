//============================================================================
// Name        : dictionary.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
//Function to read and print schedule from file
void read_file();

//Function to compare the two words for longest substring
//Returns an int with most letters in common
int dictionary(string word1, string word2);

int main(){
	//This will read the file in and call dictionary
	read_file();
	cout << "The answer has been written to output.txt" <<endl;

return(0);
}

void read_file(){

	string word_bank[100];
	string line = "";
	string c = "0";
	int num=0, first=0, second=0;
	ifstream infile;
	ofstream outFile;

	//Open file of words
	infile.open("file.txt");

	if(infile.fail()){
		cout << "File failed" <<endl;
		exit(1);
	}
//Get number of entries
	getline(infile, c);
	num = stoi(c);
	word_bank[0]=c;
//Read file into array word_bank
	for(int i=1; !infile.eof(); i++){
		getline(infile, line);
		if(line == ""){
			i--;
		}else{
			word_bank[i] = line;
		}
	}

	infile.close();
	outFile.open("output.txt");
//Compares query word to [k] to two other words

	for(int k=1; k < num*3-2; k++){
		if(k == 1){
			first = dictionary(word_bank[k], word_bank[k+1]);
			second =dictionary(word_bank[k], word_bank[k+2]);
			if(dictionary(word_bank[k], word_bank[k+1]) > dictionary(word_bank[k], word_bank[k+2])){
				outFile << word_bank[k+1]<< endl;
			}
			else{
				outFile << word_bank[k+2]<< endl;
			}
		}else{
			k=k+2;
			first = dictionary(word_bank[k], word_bank[k+1]);
			second =dictionary(word_bank[k], word_bank[k+2]);
			if(first > second){
				outFile << word_bank[k+1]<< endl;
			}else{
				outFile << word_bank[k+2]<< endl;
			}
		}
	}
	//Close output file
	outFile.close();
}

int dictionary(string word1, string word2){
string ans1, ans2;
int count = 0;
/*for(int i =0; i < word1.length(); i++){
	for(int j =0; j < word2.length(); j++){
		for(int k =0; k < word1.length() && k < word2.length(); k++){
			if(word1.substr(i,k) == word2.substr(j,k)){
				count++;
			}
			else{
				count--;
				cout << word1.substr(i,k)<< "< different >" << word2.substr(j,k)<<endl;
			}


		}
	}
}
*/
for(int k =0; k < word1.length() && k < word2.length(); k++){
	if(word1[k] == word2[k]){
		count++;
	}
	else{
		count--;
	}


}

return count;
}
