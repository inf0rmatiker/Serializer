/* 
 * Author : Caleb Carlson
 * Date   : 02/23/2018
 * Project: HW3
 * Email  : cacaleb@rams.colostate.edu
 */

#include <vector>
 
 class Serializer {
	public:
		/* Takes a string with 1 character, returns vector with tag and character */
		std::vector<int> serializeCharacter(std::string str);

		/* Takes a string of any size, returns a vector with tag, untagged vnum, and all characters */
		std::vector<int> serializeString(std::string str);

		/* Takes a string containing either true or false, returns a vector with either t or f */
		std::vector<int> serializeBool(std::string str);

		/* Takes a long number, returns a vector with tag and vnum */
		std::vector<int> serializeNumber(long number);

		/* 
		* Takes a single string line that is read from the file, 
		* breaks it up into sections delimited by whitespace,
		* and prints off the completed vectors returned from each section.
		*/
		void serializeLine(std::string line);
		
		
		/* Takes a filename and processes it one line at a time using serializeLine */
		void serializeFile(std::string filename);
	 
	
 };