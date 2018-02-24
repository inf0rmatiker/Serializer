/* 
 * Author : Caleb Carlson
 * Date   : 02/23/2018
 * Project: HW3
 * Email  : cacaleb@rams.colostate.edu
 */
 
#include <iostream>
#include <fstream>
#include "unserializer.h"

using namespace std;
					

long Unserializer::unserializeNumber(ifstream &file){
    
    bool isNegative;
    int a, bitfill, length, firstByte;
	long vnum = 0L;
	
    file >> hex >> firstByte;
    
    if (file.eof()){
        cerr << "Serialized number was not entered correctly. Hit end of file!\n";
        exit(1);
    }
    
    // Is first bit set?
    isNegative = (((firstByte >> 3) & 1) == 1);
	length = (((firstByte & 0xf0) >> 4) & 0xf);
                            
    // How many bits do we need to fill with 1's for a neg num?
    bitfill = (sizeof(long)*8 - ((8*length) + 4) );
                            
    // Don't use a negative bitfill! You'll lose your bits!
    if (bitfill < 0) bitfill = 0;
                            
	vnum = firstByte & 0xf;
	if (length > 0){
        for (int b = 1; b <= length; b++){
			file >> hex >> a;
            if (file.eof()){
                cerr << "Serialized number was not entered correctly. Hit end of file!\n";
                exit(1);
            }   
			vnum = (vnum << 8) + a;
        }
    }
	if (isNegative){
        vnum = vnum << bitfill;
        vnum = vnum >> bitfill;
    }
    
    return vnum;
}

char Unserializer::unserializeCharacter(ifstream &file){
    int c;
    file >> hex >> c;
	if (c < 0 || c > 127) {
		cerr << "Please only use Ascii characters, and separate by whitespace!\n";
		exit(1);
	}
    return c;
}

string Unserializer::unserializeString(ifstream &file){
	string s;
	int length = unserializeNumber(file);
	for (int i = 0; i < length; ++i) {
		s += unserializeCharacter(file);
	}
	return s;
}

/* Takes a filename and processes it one line at a time using serializeLine */
void Unserializer::unserializeFile(std::string filename){
	ifstream file (filename);
	if (file.is_open()){
                
		int a;
		long vnum = 0L;
		char c;
		string s;
                
		while (file >> hex >> a){
			switch (a) {
				// BOOLEANS
				case 't': cout << "true" << '\n'; break;
				case 'f': cout << "false"<< '\n'; break;
						
				// VNUMS
				case 's':
				case 'i':
				case 'l':
					vnum = unserializeNumber(file);
					cout << vnum << '\n';
					break;
						
				// CHARACTER OR STRING
				case 'S': 
					s = unserializeString(file);
					cout << '\"' <<  s << "\"\n";
					break;
				case 'c': 
                    c = unserializeCharacter(file);
                    cout << '\'' << c << "\'\n";
                    break;
						
				default :
                    cerr << a << " is not a tag!" << '\n';
                    exit(1);
						
				}
			}
		}
	else {
		//Something went wrong with opening file!
        cerr << "Unable to open file " << filename << "\n";
        exit(1);				
	}
	file.close();
	
}
	 