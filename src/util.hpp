#if !defined(UTIL_HPP)
#define UTIL_HPP

#include <istream>
#include "key.hpp"

std::vector<Key> read_input(){
    std::vector<Key> T;
    std::string s;

    for (int i{0}; i < N; i++){
        std::cin >> s;
        T.push_back(Key(s));
    }
    return T;
}

void usage(const string &s){
    cout << s << " [password] < in/<file>" << endl;
}

#endif // UTIL_HPP

