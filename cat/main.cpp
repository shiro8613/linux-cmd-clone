#include<iostream>
#include<istream>
#include<fstream>
#include<vector>
using namespace std;

int main(int argc, char** args) {
    vector<string> out;
    for (int i=1; i < argc; i++) {
        char* filename = args[i];
        fstream in(filename);
        if (!in) {
            cerr << filename << " is not exists." << endl;
            return -1;
        }

        istream& input = static_cast<istream&>(in);
        string line;
        while (getline(input, line) && !line.empty()) {
            out.push_back(line);
        }
        in.close();
    }

    string line;
    if(argc < 2) {
        while (getline(cin, line)){
            cout << line << endl;
        }
    } else {
        for (string line : out) {
            cout << line << endl;
        }
    }

    return 0;
}