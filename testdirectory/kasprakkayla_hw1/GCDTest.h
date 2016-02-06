/****************************************************************
 * Header file for the gcd test.
 *
 * Author/copyright:  Duncan Buell
 * Date: 17 January 2016
 *
**/

#ifndef GCDTEST_H
#define GCDTEST_H

#include <iostream>
#include <vector>
using namespace std;

#include "../../Utilities/Scanner.h"
#include "../../Utilities/ScanLine.h"

#include "MyRandom.h"

class GCDTest
{
public:
  GCDTest();
  virtual ~GCDTest();

  void createNumbers(LONG howManyTests, LONG maxTestNumberSize);
  void runTheTests();
  string stringifyBitLengthFreqs();
  string stringifyShiftFracFreqs();

private:
  vector<LONG> bitLengthFreqs;
  vector<LONG> shiftFracFreqs;
  vector<LONG> veca;
  vector<LONG> vecb;

  string convertToBinary(LONG n);
  string formatProgress(LONG sub, LONG a, LONG b,
                        LONG g, LONG gbin, LONG g3);
  LONG gcdBinary(LONG a, LONG b);
  LONG gcdNaive(LONG a, LONG b);

  int getBitLength(LONG n);

  void testBinary(bool extraTest);

};

#endif
