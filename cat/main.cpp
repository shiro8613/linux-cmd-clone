#include<iostream>
#include<istream>
#include<fstream>
using namespace std;

int main(int argc, char** args) {
    string line;
    if(argc < 2) {
        while (getline(cin, line)){
            cout << line << endl;
        }
    } else {
        fstream in;
        for (int i=1; i < argc; i++) {
            char* filename = args[i];
            in.open(filename);
            if (!in) {
                cerr << filename << " is not exists." << endl;
                return -1;
            }

            istream& input = static_cast<istream&>(in);
            while (getline(input, line) && !line.empty()) {
                cout << line << endl;
            }
        
        in.close();
        }
    }
    
    return 0;
}