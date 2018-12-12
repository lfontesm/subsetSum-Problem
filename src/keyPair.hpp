#if !defined(KEYPAIR_H_)
#define KEYPAIR_H_

#include <map>
#include "key.hpp"

class KeyPair{
public:
    KeyPair();
    KeyPair(const Key &k1, const Key &k2);

    Key fst;
    Key snd;

    inline bool operator<(const KeyPair& other) const {
        if (this->fst == other.fst)
            return this->snd < other.snd;
        return this->fst < other.fst;
    }

    friend bool operator==(const KeyPair &kp1, const KeyPair &kp2){
        return (kp1.fst == kp2.fst && kp1.snd == kp2.snd);
    }

private:
};

struct KeyPairComparator{
    bool operator()(const KeyPair &left, const KeyPair &right) const{
        return left < right;
    }
};

Key subset_map(const Key &k, const vector<Key> &T, map<KeyPair, int, KeyPairComparator> &m);

inline int bitP(const Key &k, const int &i) {
    return (k.digit[i/B] >> (B - 1 - i % B)) & 1;
}


#endif // KEYPAIR_H_
