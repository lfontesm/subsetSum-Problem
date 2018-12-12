#include "keyPair.hpp"
#include "key.hpp"

KeyPair::KeyPair() : 
    fst(Key()), 
    snd(Key()) {
}

KeyPair::KeyPair(const Key &k1, const Key &k2) :
    fst(k1 < k2 ? k1 : k2),
    snd(k1 < k2 ? k2 : k1) { // To facilitate operations, the first key will always be the lesser one
}

Key subset_map(const Key &k, const vector<Key> &T, map<KeyPair, int, KeyPairComparator> &m){
    Key sum;
    for (int i = 0; i < N; ++i) {
        if (bitP(k, i) == 0) continue;
        for (int j{i}; j < N; j++){
            if (bitP(k, i) && bitP(k, j)) {
                // sum += T[i];
                // KeyPair *kp = new KeyPair(T[i], T[j]);
                KeyPair kp(T[i], T[j]);

                map<KeyPair, int, KeyPairComparator>::iterator it;

                it = m.find(kp);
                if (it != m.end())
                    it->second += 1;
                else
                    m.insert(make_pair(kp, 1));

                // cout << "Key: [" << kp.fst << ";" << kp.snd << "]" << endl;
                
            }
        }
    }
    return sum;
}
