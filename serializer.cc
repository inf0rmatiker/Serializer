/* 
 * Author : Caleb Carlson
 * Date   : 02/23/2018
 * Project: HW3
 * Email  : cacaleb@rams.colostate.edu
 */
 
#include <iomanip>
#include <math.h> 
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "serializer.h"

using namespace std;

 vector<int> Serializer::serializeCharacter(string str){
	
	vector<int> myChar;
	
	if (str.size() != 1){
        if (str[0]==' ' && str.size() > 1){
            myChar.push_back('c');
            myChar.push_back(11);
        }
		cerr << "Formatting error: Please only have 1 character in single quotes!" << '\n';
		exit(1);
	}	
	else {
		myChar.push_back('c');
		myChar.push_back(str.at(0));
	}
	
	// Returns vector: TAG | CHAR
	return myChar;
	
}

vector<int> Serializer::serializeBool(string str){
    vector<int> boolVect;
    if (str.compare(string("true")) == 0) boolVect.push_back('t');
    else if (str.compare(string("false")) == 0) boolVect.push_back('f');
    else {
        cerr << "Formatting error: Please only have true or false for boolean values!" << '\n';
		exit(1);
    }
    
    return boolVect;
    
    
}

vector<int> Serializer::serializeString(string str){
    
	vector<int> myChars;
	int totalChars = str.size();
	// Add tag, vnum for length, then characters
	myChars.push_back('S');
	vector<int> vnum = serializeNumber(totalChars);
    for (unsigned int i=1; i<vnum.size(); i++) myChars.push_back(vnum[i]);
    for (char c : str) myChars.push_back(c);
	
    // Returns vector: TAG | VNUM LENGTH | CHARS
	return myChars;
	
}

vector<int> Serializer::serializeNumber(long number){
	
	long temp = number;
	vector<int> myVector;
	int minBits = 0;
    int tag;
		
    // Find minimum number of bits needed to represent binary number
    while (temp != -1 && temp != 0){
        temp >>= 1;
        minBits++;
    }
    minBits++;
    //cout << "Min bits : " << minBits << '\n';
    if (minBits <= 16) tag = 's';
    else if (minBits <= 32) tag = 'i';
    else tag = 'l';
    
    // Push tag
    myVector.push_back(tag);
    
    int additionalBytes = ceil((minBits - 4)/8.0); // 8
	
	int bitPlaces = 8*additionalBytes; //64
    //cout << "Min Bits: " << minBits << " addlBytes: " << additionalBytes << " bitPlaces: " << bitPlaces << '\n';
    // Push length and leftmost 4 bits
    if (bitPlaces > 63) {
        if (number < 0) myVector.push_back((additionalBytes << 4) | 0xf);
        else myVector.push_back((additionalBytes << 4));
        
    }
    else myVector.push_back((additionalBytes << 4) + ((number >> bitPlaces) & 0xf));
    
    // Push rest of number in 8 bit sections
	for (int i = bitPlaces - 4; i >= 0; i-=8){
		myVector.push_back((number >> (i-4)) & 0xff);
	}
	// Returns vector: TAG | LENGTH | NUMBER
	return myVector;
	
}

void Serializer::serializeLine(string line){
	
    vector<int> sectVect;
    char c;
    char prev = ' ';
	string section = "";
	bool strQuotes = false;
    bool charQuotes = false;
    
    
    
	for (unsigned int x=0; x<=line.size(); x++){
        // Test to see if you are at end of line or file and handle.
        if (x == line.size()) c = ' ';
        else if (x>0) {
            prev = line.at(x-1);
            c = line.at(x);
        }
        else c = line.at(x);
        
		switch (c){
			
			case '\"': // STRING
				// End of string
				if (strQuotes){
					// HANDLE STRING/CHAR and toggle inQuotes OFF
					sectVect = Serializer::serializeString(section);
					//cout << "SECTION: " << section << ": ";
					for (unsigned int i=0; i<sectVect.size(); i++){
                        if (i < sectVect.size() - 1) cout << hex << setfill('0') << setw(2) << sectVect[i] << ' ';
                        else cout << hex << setfill('0') << setw(2) << sectVect[i];
					}
					cout << '\n';
					section = "";
					strQuotes = false;
					continue;
				}
				else if (charQuotes) {
                    section += c;
                    continue;
                }
				// Beginning of string
				else {
                    if (!isspace(prev)){
                        cerr << "Formatting error: Items must be separated by whitespace!" << '\n';
                        exit(1);
                    }
					strQuotes = true;
					continue;
				}
			
			
			case '\'': // CHAR
				if (charQuotes){
					sectVect = Serializer::serializeCharacter(section);
					//cout << "SECTION: " << section << ": ";
					for (unsigned int i=0; i<sectVect.size(); i++){
                        if (i < sectVect.size() - 1) cout << hex << setfill('0') << setw(2) << sectVect[i] << ' ';
                        else cout << hex << setfill('0') << setw(2) << sectVect[i];
					}
					cout << '\n';
					section = "";
					charQuotes = false;
					continue;
				}
				else if (strQuotes) {
                    section += c;
                    continue;
                }
				else {
                    if (!isspace(prev)){
                        cerr << "Formatting error: Items must be separated by whitespace!" << '\n';
                        exit(1);
                    } 
					charQuotes = true;
					continue;
				}
			
			default  : // Anything other than quotes
				if (strQuotes || charQuotes) section += c; // Add next character to string/char
				else if (!isspace(c)){
                    // Read Number
                    if (isdigit(c) || (c == '-' && (section.size() == 0))) {
                        //If the previous character was not a digit
                        if (!isdigit(prev) && !isspace(prev) && prev!='-') {
                            cerr << "Formatting error: Numbers can not contain other symbols!" << '\n';
                            exit(1);
                        }
                        section += c; // Add to number if it is a digit
                    }
                    // Read True
                    else if (c == 't' && section.size() == 0 && isspace(prev)) {
                        section = line.substr(x,4);
                        //cout << section << '\n';
                        if (section.compare("true")==0) {
                            sectVect = Serializer::serializeBool(section);
                            cout << hex << setfill('0') << setw(2) << sectVect[0] << '\n';
                        }
						else {
							cerr << "Formatting error: Numbers can not contain other symbols!" << '\n';
							exit(1);
						}
                        x+=3;
                        section = "";
                    }
                    // Read False
                    else if (c == 'f' && section.size() == 0 && isspace(prev)) {
                        section = line.substr(x,5);
                        //cout << section << '\n';
                        if (section.compare("false")==0) {
							//cout << " FALSE ";
                            sectVect = Serializer::serializeBool(section);
                            cout << hex << setfill('0') << setw(2) << sectVect[0] << '\n';
                        }
						else {
							cerr << "Formatting error: Numbers can not contain other symbols!" << '\n';
							exit(1);
						}
                        x+=4;
                        section = "";
                    }
                    else {
                        cerr << "Formatting error: Numbers can not contain other symbols!" << '\n';
                        exit(1);
                    }
                    
                }
				else {
					if (section.size() != 0){
						// HANDLE NUMBER
						long number = stol(section);
						sectVect = Serializer::serializeNumber(number);
						//cout << "SECTION: " << section << ": ";
						for (unsigned int i=0; i<sectVect.size(); i++){
                            if (i < sectVect.size() - 1) cout << hex << setfill('0') << setw(2) << sectVect[i] << ' ';
                            else cout << hex << setfill('0') << setw(2) << sectVect[i];
                        }
						cout << '\n';
					}
					section = "";
				}
		}
	}
	if (strQuotes || charQuotes){
		cerr << "Formatting error: Quotes were not closed!" << '\n';
		exit(1);
	}
}


void Serializer::serializeFile(std::string filename){
	ifstream file (filename);
    if (file.is_open()){
    string line;
    while (getline(file, line)){
        Serializer::serializeLine(line);
    }		
    }
    else {
		//Something went wrong with opening file!
		cerr << "Unable to open file " << filename << "\n";
        exit(1);
    }
    file.close();
}