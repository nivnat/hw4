//
// Created by Ari Trachtenberg on 3/15/17.
//

#include "bigNum.h"

/**
 * Reduce #num to a smaller number
 * @return A number between 1 and range-1 inclusive
 */
bigNum reduce(const bigNum& num, const bigNum& range) {
    if (num==0)
        return 1;
    if (num<=range)
        return num;
    else
        return reduce(num/2 + 1, range);
}

/*
 * Computes a hash of the provided #plaintext
 * @param nonce A nonce with which to vary the hash
 * @param plaintext The text to hash
 */
bigNum hasher(bigNum nonce, string plaintext) {
    const bigNum bigPrime("671998030559713968361666935769");

    bigNum theHash = nonce; // seed value
    std::string::iterator iter;
    for (iter=plaintext.begin(); iter!=plaintext.end(); iter++) {
        theHash = reduce(theHash * (*iter), bigPrime);
    }
    return theHash;
}