# Serializer
Reads files containing numbers, strings, booleans, or characters separated by whitespace. Serializes them and outputs the tagged results to console.

- __Numbers__ input as integers are output as hexidecimal vnums
  - Format of vnum is 8n + 4 bits, where n is the number of additional bytes needed to store the number.
  - First 4 bits of output is unsigned length of additional bytes needed. 
  - Example 1) input 5 would return 73 05. 73 is hex for 's', meaning the number was small enough to fit into a short. 05 because 0         additional bytes were needed and 5 fits into the first signed 4 bits.
  - Example 2) input *4500000* would return *69 30 44 aa 20*. 69 for 'i' for int, 3 additional bytes were needed to store the number,       the other bytes denoting the number.
  - Input size restraint is max/min size of signed long int
  
- __Strings__ are input between double quotes and are output as hexidecimal bytes representing characters and length.
  - Format of string result is a vnum representing the length of the string, and then each byte of the input string returned in hex.
  - Input restraints is any Ascii character, excluding EOF or newline.
  
- __Booleans__ are input as *true* or *false*

- __Characters__ are input between single quotes and are output as just the character in hex.
  - Format of character must be only 1 char long, any more or less will result in program crash and burn.
  - Can be any Ascii character, excluding EOF or newline.
  
- __Tags__ precede every output with the hex character value of the following:
  - 's' for *short*
  - 'i' for *int*
  - 'l' for *long*
  - 'S' for *string*
  - 'c' for *char*
  
- Usage:
  - Download serializer.tar and extract. Compile with either the Makefile provided (Linux/g++ users) or make your own makefile to           compile it.
  - Once object file has been made, run as ./serializer [options] [filename...] Example: ./serializer -s -v datafile.txt
  - Options are:
    - *-s* : serialize
    - *-u* : unserialize
    - *-v* : verbose
  - Enjoy


# Unserializer

Reads serialized data and outputs unserialized results, one per line.

- Example 1) __69 30 44 aa 20__ -> __4500000__
