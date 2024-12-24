#include<iostream>
#include<regex>
#include<fstream>
#include<vector>
using namespace std;

bool invert = false;
regex searchRegex;

void grep_i(istream* input, string suffix) {
    string line;
    while (getline(*input, line) && !line.empty()) {
        if (!regex_search(line, searchRegex) == invert) {
            cout << suffix << " " << regex_replace(line, searchRegex, "\x1b[31m$&\x1b[m") << endl;
        }
    }
}

int main(int argc, char *args[]) {
    vector<string> filenames;

    string arg;
    if (argc < 2) {
        cerr << "searchText here." << endl;
        return -1;
    }
    string searchText = args[1];
    for (int i=2; i < argc; i++) {
        arg = args[i];
        if (arg.find("-v") != string::npos) {
            invert = true;
            continue;
        }
        filenames.push_back(arg);
    }

    if(searchText.empty()) {
        cerr << "searchText is empty." << endl;
        return -1;
    }
    searchRegex = basic_regex(searchText);

    if(filenames.empty()) {
        grep_i(&cin, "");
    } else {
        for (string filename : filenames) {
            fstream in(filename);
            if (!in) {
                cerr << filename << " is not exists." << endl;
            }

            istream& input = static_cast<istream&>(in);
            string suffix = filenames.size() <= 1 ? "" : "\x1b[35m"+ filename + ":" +"\x1b[m"; 
            grep_i(&input, suffix);
        }
    }  
    return 0;
}