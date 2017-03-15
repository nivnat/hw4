//
// Created by Ari Trachtenberg for EC330 on 1/30/17.
//

#ifndef MINER_BIGNUM_H
#define MINER_BIGNUM_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

/**
 * A class to represent arbitrarily large non-negative integers.
 */
class bigNum {

public:

    // CONSTRUCTORS

    /**
     * Constructs a bigNum from a given non-negative int
     */
    bigNum(unsigned int num);

    /**
     * Constructs a bigNum from a given string.
     * @param num contains only characters 0-9 and represents a positive integer >= 0
     */
    bigNum(string num = "");

    /**
     * Constructs a copy of otherNum
     */
    bigNum(const bigNum& otherNum);

    // INFORMATIONAL
    /**
     * @return true iff this bigNum is exactly numerically equal to otherNum
     */
    bool operator==(const bigNum& otherNum) const;

    /**
     *
     * @param otherNum
     * @return true iff this number is numerically less than or equal to other number
     */
    bool operator<=(const bigNum& otherNum) const;

    /**
     * This bigNum becomes the same as otherNum
     * @return the (new) version of this bigNum
     */
    bigNum& operator=(const bigNum& otherNum);

    /**
     * @return the [index]-th least-significant digit of the number
     */
    int operator[](size_t index) const { return digits.at(index); }

    /**
     *
     * @return The number of significant digits in the number
     */
    size_t numDigits() const { return digits.size(); }

    /**
     * ARITHMETIC ASSIGNMENT OPERATORS
     */
    bigNum& operator+=(const bigNum& addor);
    bigNum& operator*=(const int cc);
    bigNum& operator*=(const bigNum& multiplicand);
    bigNum& operator/=(const bigNum& divisor);

protected:
    vector<int> digits; /** stores the digits of the current number */

private:

    /**
     * @param cc > 0
     * @return shifts the number to the left cc digits;
     *         equivalent to multiplying the current number by base^cc
     */
    void operator<<(int cc);


    // Constants
    const static int base = 10; // the base of the number

    // FRIENDS
    /**
     * Prints a human-readable version of bigNum [num]
     * onto a given output stream
     */
    friend std::ostream & operator<<(std::ostream& stream, const bigNum& num);
};

/**
 * External arithmetic operators
 */
bigNum& operator+(const bigNum& addend, const bigNum& addor);
bigNum& operator*(const bigNum& multiplicand, const bigNum& multiplicator);
bigNum& operator/(const bigNum& dividend, const bigNum& divisor);

/**
 * Optimized multiplication of a bigNum by an int
 * @param cc > 0 is assumed
 * @return the product of this number and cc
 */
bigNum& operator*(const bigNum& multiplicand, int cc);

#endif //MINER_BIGNUM_H
