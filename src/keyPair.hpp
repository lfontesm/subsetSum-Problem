#if !defined(KEYPAIR_H_)
#define KEYPAIR_H_

#include <map>
#include "key.hpp"

class KeyPair{
public:
    KeyPair();
    KeyPair(const Key &k1, const Key &k2);
    KeyPair(KeyPair &&) = default;
    KeyPair(const KeyPair &) = default;
    KeyPair &operator=(KeyPair &&) = default;
    KeyPair &operator=(const KeyPair &) = default;
    ~KeyPair();

private:
    Key fst;
    Key snd;
    
};

#endif // KEYPAIR_H_
