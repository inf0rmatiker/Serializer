/* 
 * Author : Caleb Carlson
 * Date   : 02/23/2018
 * Project: HW3
 * Email  : cacaleb@rams.colostate.edu
 */

#include <iostream>
#include <fstream>

 class Unserializer {
	public:
		
		/* Takes a reference to an ifstream, returns the serialized vnum as an unserialized long */
		long unserializeNumber(std::ifstream &);

		/* Takes a reference to an ifstream, returns the serialized vnum as an unserialized long */
		bool unserializeBool(std::ifstream &);

		/* Takes a reference to an ifstream, returns the serialized sequence of characters
		as an unserialized string */
		std::string unserializeString(std::ifstream &);

		/* Takes a reference to an ifstream, returns an unserialized character */
		char unserializeCharacter(std::ifstream &);
		
		/* Takes a filename and processes it one line at a time using serializeLine */
		void unserializeFile(std::string filename);
	 
	
 };