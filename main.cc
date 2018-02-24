#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include "serializer.h"
#include "unserializer.h"

using namespace std;

int main (int argc, char *argv[]) {
    
    int option, sflag = 0, uflag = 0, vflag = 0;
    string usageMessage = "Usage: " + string(argv[0]) + " [options] [filename...]\n" + "Options: -s -u -v\n-s: Serialize\n-u: Unserialize\n-v: Verbose\n";
    if (argc <= 1){
        cerr << usageMessage;
        exit(1);
    }
    
    // Get options and handle incorrect combinations
    while ((option = getopt(argc, argv, "+suv")) != -1){
        switch (option) {
            case 'v' : 
                vflag = 1; break;
            case 's' : 
                if (uflag > 0) {
                   cerr << "Options entered incorrectly!\nCannot use -s and -u together.\n" << usageMessage;
                   exit(1);
                }
                sflag = 1; break;
            case 'u' : 
                if (sflag > 0) {
                   cerr << "Options entered incorrectly!\nCannot use -s and -u together.\n" << usageMessage;
                   exit(1);
                }
                uflag = 1; break;
            default  : 
                cerr << "Options entered incorrectly!\n" << usageMessage;
                exit(1);
        }
    }
    if (optind >= argc){
        cerr << "Expected arguments after options...\n" << usageMessage;
        exit(1);
    }
    
    
	// SERIALIZE
    if (uflag < 1){
		Serializer serializer;
        for (int i = optind; i < argc; i++){
			if (vflag > 0) cerr << "Processing file " << argv[i] << '\n';
            serializer.serializeFile(argv[i]);
        }
    }
	// UNSERIALIZE
	else {
		Unserializer unserializer;
		for (int i = optind; i < argc; i++){
			if (vflag > 0) cerr << "Processing file " << argv[i] << '\n';
			unserializer.unserializeFile(argv[i]);
		}
	

	}

    return 0;
}
