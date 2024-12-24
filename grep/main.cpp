#include<iostream>
#include<regex>
#include<fstream>
using namespace std;

int main(int argc, char *args[]) {
    string filename;
    bool invert = false;

    string arg;
    string searchText;
    if (argc < 2) {
        cerr << "option or searchText here." << endl;
        return -1;
    }
    for (int i=1; i < argc; i++) {
        arg = args[i];
        if (arg.find("-v") != string::npos) {
            invert = true;
            continue;
        }
        if (arg.find("-f") != string::npos) {
            if (i+1 < argc) {
                filename = args[i+1];
                i += 1;
                continue;
            } else {
                cerr << "filename please." << endl;
                return -1;
            }
        }

        searchText = arg;
    }

    if(searchText.empty()) {
        cerr << "searchText is empty." << endl;
        return -1;
    }
    regex searchRegex(searchText);

    fstream in;    
    if(!filename.empty()) {
        in.open(filename);
        if(!in) {
            cerr << "failed to open " << filename << endl;
            return -1;
        }
    }

    istream& input = in.is_open() ? static_cast<istream&>(in) : cin;
    string line;
    while (getline(input, line) && !line.empty()) {
        if (!regex_search(line, searchRegex) == invert) {
            cout << regex_replace(line, searchRegex, "\x1b[31m$&\x1b[m") << endl;
        }
    }  

    return 0;
}
