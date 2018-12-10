#include "keyPair.hpp"
#include "util.hpp"

int main(int argc, char *argv[]){
    if (argc < 2){
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    map<KeyPair*,int> m;

    vector<Key> T = read_input(); // Computes T table

    Key encrypted(argv[1]);
    encrypted.print_key();
    cout << endl;

    Key max;
    for (int i{0}; i < C; i++) max.digit[i] = R-1;

    Key match; // Key we want to match
    Key checker;
    Key a("aaa5");
    while (match != a){
        subset_map(match, T, m);
        // match.print_key();
        ++match;
    }
    for (auto p : m){
        cout << "Key: [" << p.first.fst << ";" << p.first.snd << "], Val: " << p.second << endl;
        // delete p.first;
    }

    return 0;
}
