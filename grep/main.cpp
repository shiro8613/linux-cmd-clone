#include<iostream>
#include<regex>
#include<fstream>
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
    if (argc < 2) {
        cerr << "searchText here." << endl;
        return -1;
    }

    searchRegex = basic_regex(args[1]);
    
    char** filenames = (char**)malloc(sizeof(char*) * argc);
    string arg;
    int filenames_idx = 0;
    for (int i=2; i < argc; i++) {
        arg = args[i];
        if (arg.find("-v") != string::npos) {
            invert = true;
            continue;
        }
        filenames[filenames_idx] = args[i];
        filenames_idx++;
    }

    if (argc <= 2) {
        free(filenames);
        grep_i(&cin, "");
        return 0;
    }

    string suffix;
    fstream in;
    for(int i=0; i < filenames_idx; i++) {
        char* filename = filenames[i];
        in.open(filename);
        if (!in) {
            cerr << filename << " is not exists." << endl;
        }

        istream& input = static_cast<istream&>(in);
        
        suffix = filenames_idx <= 1 ? "" : "\x1b[35m:" + string(filename) + "\x1b[m";
        grep_i(&input, suffix);
        in.close();
    }

    free(filenames);

    return 0;
}