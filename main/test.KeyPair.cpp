#include <set>
#include "keyPair.hpp"
#include "util.hpp"
#include <algorithm>
#include <functional>

int main(int argc, char *argv[]){
    if (argc < 2){
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    map<KeyPair, int, KeyPairComparator> m;

    vector<Key> T = read_input(); // Computes T table

    Key encrypted(argv[1]);
    encrypted.print_key();
    cout << endl;

    Key max;
    for (int i{0}; i < C; i++) max.digit[i] = R-1;

    Key match; // Key we want to match
    Key checker;
    Key a("aa55");
    Key b("aaa5");
    Key c;
    Key d("5555");
    while (match != max){
        subset_map(match, T, m);
        // match.print_key();
        ++match;
    }
    subset_map(match, T, m);

    KeyPair kp(a, b);
    KeyPair kp2(b, a);

    // Declaring the type of Predicate that accepts 2 pairs and return a bool
    typedef std::function<bool(pair<KeyPair, int>, pair<KeyPair, int>)> Comparator;
 
	// Defining a lambda function to compare two pairs. It will compare two pairs using second field
	Comparator compFunctor =
        [](const pair<KeyPair, int> &elem1 , const pair<KeyPair, int> &elem2){
            return elem1.second >= elem2.second;
        };

    // Declaring a set that will store the pairs using above comparision logic
	set<pair<KeyPair, int>, Comparator> setOfWords(
        m.begin(), m.end(), compFunctor);

    // if (kp < kp2)
    //     cout << "aaa\n";
    // else
    //     cout << "bbb\n";
    cout << "kp: " << kp.fst << ";" << kp.snd << ". kp2: " << kp.fst << ";" << kp.snd << endl;


    // for (auto &p : m){
    //     cout << "Key: [" << p.first.fst << ";" << p.first.snd << "], Val: " << p.second << endl;
    // }

    for (auto &p : setOfWords)
        cout << "Key: [" << p.first.fst << ";" << p.first.snd << "], Val: " << p.second << endl;
    

    return 0;
}
