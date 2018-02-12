# Serializer
Reads files containing numbers, strings, or characters separated by whitespace. Serializes them and outputs the tagged results to console.

- Numbers input as integers are output as hexidecimal vnums
  - Format of vnum is 8n + 4 bits, where n is the number of additional bytes needed to store the number.
  - First 4 bits of output is unsigned length of additional bytes needed. 
  - Example 1) input 5 would return 05, as no additional bytes were needed to store the number, and 5 fit into the first 4 bits.
  - Example 2) input 300 would return 11 2c, as 1 additional byte was needed to store the number, the other 3 nibbles denoting the number.
  - Input size restraint is max/min size of signed long int
  
- Strings are input between double quotes and are output as hexidecimal bytes representing characters and length.
  - Format of string result is a vnum representing the length of the string, and then each byte of the input string returned in hex.
  - Input restraints is any Ascii character, excluding EOF or newline.
  
  
- Characters are input between single quotes and are output as just the character in hex.
  - Format of character must be only 1 char long, any more or less will result in program crash and burn.
  - Can be any Ascii character, excluding EOF or newline.
  
- Tags precede every output with the hex character value of the following:
  - 's' for short
  - 'i' for int
  - 'l' for long
  - 'S' for string
  - 'c' for char
  
- Usage:
  - Compile and run serializer.cc with either the Makefile provided (Linux/g++ users) or make your own makefile to compile it.
  - Once object file has been made, run as ./serializer <file_1> <file_2> ... <file_n> to read from file_1 through file_n.
  - Enjoy
