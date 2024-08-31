/*

 Instructions to compile:g++ homework3.cpp
 Instructions to run:.\a.exe dbfile.txt query.txt
*/

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <algorithm>
#include <chrono>
#include <unordered_map>

using namespace std;

int main(int argc, char *argv[]) {
	// check for correct command-line arguments

	if (argc != 3) {
	   std::cout << "Usage: " << argv[0] << " <db file> <query file>" << std::endl;
	   std::exit(-1);
	}
    // parsing strings
	std::string line, name;
	std::regex delim("/");
	std::ifstream dbfile(argv[1]);
	if (!dbfile.is_open()) {
	   std::cout << "Unable to open file: " << argv[1] << std::endl;
	   std::exit(-1);
	}

    unordered_map<string,vector<string>> movieMap, actorMap;
    //movieMap contains <movie name, list of actors> 
    //actorMap contains <actor name, list of movies he is in>
    

	while (std::getline(dbfile, line)) {
        vector<string> v;
        // parse each line for tokens delimited by "/"
        auto begin = std::sregex_token_iterator(line.begin(), line.end(), delim, -1);
        auto end = std::sregex_token_iterator();
        // parse movie name
        string key = *begin; // key is movie name
        ++begin;
        //parse the actors;
        for (std::sregex_token_iterator word = begin; word != end; ++word) {
                movieMap[key].push_back(*word);
                actorMap[*word].push_back(key);
        }
        //count++;
	}
	dbfile.close();
	//map is now filled


    
    
	std::ifstream queryfile(argv[2]);
	if (!queryfile.is_open()) {
	   std::cout << "Unable to open file: " << argv[2] << std::endl;
	   std::exit(-1);
	}

    
	while (std::getline(queryfile, name)) {
        bool found = false;
	   if(movieMap.find(name) != movieMap.end())
       {
        found = true;
        //print out list of actors if query  is movie name
        for(auto item : movieMap[name])
        {
            cout <<"\t"<< item << endl;
        }
       }
       else //check if it is a actor name
       {
	   if(actorMap.find(name) != actorMap.end())
       {
        found = true;
        //print out list of movie the actor is in
        for(auto item : actorMap[name])
        {
            cout <<"\t"<< item << endl;
        }
       }
       }// if it is neither movie nor actor then print not found
       if(!found)
       {
        cout << "\tNot found" << endl;
       }
       
	}

	queryfile.close();

	return 0;
}
