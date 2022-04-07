#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>  // C++ exceptions
#include "trie.hpp"

using namespace std;
using namespace structures;

string find_prefix_in_line(string line) {
    string return_string;
    int prefix_length = 0;
    int initial_index = (line.find("[") + 1);
    for (int i = initial_index ; i < line.size(); i++) {
        if (line[i] == ']') {
            break;
        }
        prefix_length++;        
    }
    return_string = line.substr(initial_index, prefix_length);
    return return_string;
}
int main() {
    
    using namespace std;    
    string filename;
    string word;
    Trie myTrie;
    cin >> filename;  // entrada

    string line;
    ifstream myfile (filename);    
    int last_line_length = 0;
    int last_line_pos = -1;
    int char_pos = 0;
    if (myfile.is_open()) {
        while ( getline (myfile,line) ) {                       
            string prefix_in_line;
            prefix_in_line = find_prefix_in_line(line);
            //cout << prefix_in_line << "\n";
            char_pos = last_line_length + last_line_pos + 1;
            int this_line_length = line.size();                            
            myTrie.insert(prefix_in_line, this_line_length, char_pos);    
            //cout << "comprimento da linha = " << this_line_length << "\n"; 
            //cout << "char pos = " << char_pos << "\n";
            last_line_length = this_line_length;
            last_line_pos = char_pos;             
        }       
        myfile.close(); 
    }
    else cout << "Unable to open file";    
    
    while (1) {  // leitura das palavras ate' encontrar "0"
        cin >> word;
        if (word.compare("0") == 0) {
            break;
        }
        if (myTrie.isPrefix(word)) {
            myTrie.printResult(word);            
        } else {
            cout << "is not prefix\n";
        }        
        //cout << word << endl;
    }

    return 0;
}
