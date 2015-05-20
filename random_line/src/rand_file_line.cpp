//============================================================================
// Name        : rand_file_line.cpp
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

using namespace std;

void read_file();	//Function to read and print schedule from file

int main(){

	cout << "Random line from txt file: ";
	read_file();

return(0);
}

void read_file(){
	string line;
	int count = 0, randnum = 4;
	ifstream myfile;
	myfile.open("file.txt");

	if(myfile.fail()){
		cout << "File failed" <<endl;
		exit(1);
	}

	while(!myfile.eof()){
		getline(myfile, line);
		count++;
	}

	srand (time(NULL));
	randnum = rand() % count + 1;
	myfile.clear();
	myfile.seekg(0, myfile.beg);


	for(int lineno=1;lineno <= count && myfile.good();lineno++){
		 getline (myfile,line);
	      if (lineno == randnum){
	          cout << line << endl;
	      }
	}
	myfile.close();
}
