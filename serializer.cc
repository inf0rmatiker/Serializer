#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <ctype.h>

using namespace std;

/* Takes a string with 1 character, returns vector with tag and character */
vector<int> handleCharacter(string str);

/* Takes a string of any size, returns a vector with tag, untagged vnum, and all characters */
vector<int> handleString(string str);

/* Takes a long number, returns a vector with tag and vnum */
vector<int> handleNumber(long number);

/* 
 * Takes a single string line that is read from the file, 
 * breaks it up into sections delimited by whitespace,
 * and prints off the completed vectors returned from each section.
*/
void handleLine(string line);

vector<int> handleCharacter(string str){
	
	vector<int> myChar;
	
	if (str.size() != 1){
		cerr << "Formatting error: Please only have 1 character in single quotes!" << '\n';
		exit(1);
	}	
	else {
		myChar.push_back('c');
		myChar.push_back(str.at(0));
	}
	
	return myChar;
	
}

vector<int> handleString(string str){
    
	vector<int> myChars;
	int totalChars = str.size();
	
	// Add tag, vnum for length, then characters
	myChars.push_back('S');
	vector<int> vnum = handleNumber(totalChars);
    for (unsigned int i=1; i<vnum.size(); i++) myChars.push_back(vnum[i]);
    for (char c : str) myChars.push_back(c);
	
	return myChars;
	
}

vector<int> handleNumber(long number){
	
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
    
    if (minBits <= 16) tag = 's';
    else if (minBits <= 32) tag = 'i';
    else tag = 'l';
    
    // Push tag
    myVector.push_back(tag);
    
    // Number of additional bytes needed
    int additionalBytes = ceil((minBits - 4)/8.0);

    int bitPlaces = 8*additionalBytes;
    
    // Push length and leftmost 4 bits
	myVector.push_back((additionalBytes << 4) + ((number >> bitPlaces) & 0xf));
    
    // Push rest of number in 8 bit sections
	for (int i = bitPlaces - 4; i >= 0; i-=8){
		myVector.push_back((number >> (i-4)) & 0xff);
	}
	
	return myVector;
	
}

void handleLine(string line){
    
    vector<int> sectVect;
    
	string section = "";
	bool inQuotes = false;
    
	for (char c : line){
		
		switch (c){
			
			case '\"': // STRING
				// End of string
				if (inQuotes){
					// HANDLE STRING/CHAR and toggle inQuotes OFF
					sectVect = handleString(section);
					//cout << "SECTION: " << section << ": ";
					for (int i : sectVect){
						cout << hex << setfill('0') << setw(2) << i << ' ';
					}
					cout << '\n';
					section = "";
					inQuotes = false;
					continue;
				}
				// Beginning of string
				else {
					inQuotes = true;
					continue;
				}
			
			
			case '\'': // CHAR
				if (inQuotes){
					sectVect = handleCharacter(section);
					//cout << "SECTION: " << section << ": ";
					for (int i : sectVect){
						cout << hex << setfill('0') << setw(2) << i << ' ';
					}
					cout << '\n';
					section = "";
					inQuotes = false;
					continue;
				}
				else {
					inQuotes = true;
					continue;
				}
			
			default  : 
				if (inQuotes) section += c; // Add next character to string/char
				else if (!isspace(c)){
                    if (isdigit(c) || (c == '-' && (section.size() == 0))) section += c; // Add to number if it is a digit
                    else {
                        cerr << "Formatting error: Numbers can not contain other symbols!" << '\n';
                        exit(1);
                    }
                    
                }
				else {
					if (section.size() != 0){
						// HANDLE NUMBER
						long number = stol(section);
						sectVect = handleNumber(number);
						//cout << "SECTION: " << section << ": ";
						for (int i : sectVect){
							cout << hex << setfill('0') << setw(2) << i << ' ';
						}
						cout << '\n';
					}
					section = "";
				}
		}
	}
	if (inQuotes){
		cerr << "Formatting error: Quotes were not closed!" << '\n';
		exit(1);
	}
}

int main (int argc, char *argv[]) {
	// Iterate over files
	for (int i = 1; i < argc; i++){
		ifstream file (argv[i]);
		if (file.is_open()){
			string line;
			while (getline(file, line)){
				handleLine(line);
			}		
		}
		else {
			//Something went wrong with opening file!
			cerr << "Unable to open file " << argv[i] << "\n";
			exit(1);
		}
	}
    return 0;
}
