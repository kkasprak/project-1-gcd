#include "GCDTest.h"

/******************************************************************************
 *
 * Class 'GCDTest' for testing gcd algorithms.
 *
 * This functions mostly as a wrapper for code that will generate pairs of
 * random numbers and then compute the gcd. We also have the option of
 * applying tests for correctness.
 *
 * The primary entry point for this class is intended to be the function
 * 'runTheTests', which will invoke specific tests.
 *
 * Author: Duncan A. Buell
 * Date last modified: 23 January 2016
 *
 * [COMMENTS IN THIS PROGRAM THAT ARE IN SQUARE BRACKETS AND ALL CAPS ARE
 *  NOT INTENDED TO BE REAL COMMENTS IN THE CODE BUT RATHER DIRECTIONS TO 
 *  YOU, THE 350 STUDENTS, ABOUT HOW TO DOCUMENT CODE AND WHAT TO DOCUMENT.]
 * [THERE MUST ALWAYS BE A HEADER FOR EVERY CLASS THAT OUTLINES THE OVERALL
 *  STRUCTURE OF WHAT'S IN THE CLASS. YOU MUST ALWAYS HAVE YOUR NAME AND YOU
 *  SHOULD ALWAYS HAVE THE DATE OF LAST EDIT.]
 *
**/

/******************************************************************************
 * Constructor
**/
GCDTest::GCDTest()
{
}

/******************************************************************************
 * Destructor
**/
GCDTest::~GCDTest()
{
}

/******************************************************************************
 * General functions.
**/

/******************************************************************************
 * Function to convert a binary number to its bit string.
**/
string GCDTest::convertToBinary(LONG n)
{
  string bits = "";

  while (n != 0)
  {
    if (n % 2 == 0)
    {
      bits = "0" + bits;
      n = n/2;
    }
    else
    {
      bits = "1" + bits;
      n = n/2;
    }
  }
  return bits;
}

/******************************************************************************
 * Function to create the numbers to be tested.
**/
void GCDTest::createNumbers(LONG howManyTests, LONG maxTestNumberSize)
{
  int bitLength = 0;

  cout << "create " << howManyTests << " records" << endl;

  bitLength = this->getBitLength(maxTestNumberSize) + 1;
  for (int i = 0; i < bitLength; ++i)
  {
    this->bitLengthFreqs.push_back(0L);
  }

  // we can hard code the 200 because these are fractions
  for (int i = 0; i < 201; ++i)
  {
    this->shiftFracFreqs.push_back(0L);
  }

  MyRandom myRandom;
  LONG upperLimit = maxTestNumberSize;

  for (int i = 0; i < howManyTests; ++i)
  {
    LONG a = myRandom.randomUniformInt(0, upperLimit);
    LONG b = myRandom.randomUniformInt(0, upperLimit);
    this->veca.push_back(a);
    this->vecb.push_back(b);

    bitLength = this->getBitLength(a);
    ++(this->bitLengthFreqs.at(bitLength));

    bitLength = this->getBitLength(b);
    ++(this->bitLengthFreqs.at(bitLength));
  }

  cout << "done with creation of " << howManyTests << " pairs" << endl;
}

/******************************************************************************
 * Function to format a progress line.
**/
string GCDTest::formatProgress(LONG sub, LONG a, LONG b,
                               LONG g, LONG gbin, LONG g3)
{
  string s = "";
  s += Utils::Format(sub, 11) + " ";
  s += Utils::Format(a, 11) + " ";
  s += Utils::Format(b, 11) + " ";
  s += Utils::Format(g, 6) + " ";
  s += Utils::Format(gbin, 6) + " ";
  s += Utils::Format(g3, 6);
  return s;
}

/*********************************************************************
 * Binary gcd
**/
LONG GCDTest::gcdBinary(LONG a, LONG b)
{
  //TODO
  LONG k_a = 1;
  LONG k_b = 1;
  LONG a_odd = a;
  LONG b_odd = b;
  LONG big = 0;
  LONG small = 0;
  LONG temp = 0;
  LONG gcd = 0;
  double shiftCount = 0.0;
  cout << "In GCDTest" << endl;

  if (a == b)
    return a;
  if (a == 0)
    return b;
  if (b == 0)
    return a;
  //Given nonnegative integers a and b
  //Remove the k_a powers of 2 in a to produce a_odd
  //Remove the k_b powers of 2 in b to produce b_odd
  cout << "Printing a and b" << endl;
  cout << "a = " << a << endl;
  cout << "b = " << b << endl;
  while (a_odd % 2 == 0 && a_odd != 0)//a is even
  {
    cout << "While: a_odd is even" << endl;
    k_a = (k_a*2);
    a_odd = (a_odd/2);
  }
  while (b_odd % 2 == 0 && b_odd !=0)//b is even
  {
    cout << "While: b_odd is even" << endl;
    k_b = (k_b*2);
    b_odd = (b_odd/2);
  }

  cout << "Both ints now odd" << endl;
  cout << "a_odd " << a_odd << endl;
  cout << "b_odd " << b_odd << endl;

  //Now that both integers are odd, gcd must be odd
  if (a_odd >= b_odd)
  {
    cout << "a is bigger " << big;
    cout << "b smaller" << small;
    big = a_odd;
    small = b_odd;
  }
  if (a_odd < b_odd)
  {
    cout << "b is bigger " << big << endl;
    cout << "a smaller" << small << endl;
    big = b_odd;
    small = a_odd;
  }

  cout << "Big = " << big << endl;
  cout << "Small = " << small << endl;

  while(small != 0)
  {
    big = big - small;
    big = big >> 1;
    while(big % 2 == 0 && big != 0)//while big is zero
    {
      big = big >> 1;
      shiftCount++;//Increments for each free shift
    }
    if(big < small)
    {
      temp = big;
      big = small;
      small = temp;
    }

    if(big % 2 == 1)
    {
      gcd = big;
    }
    else
      gcd = small;
  }
    cout << "gcd before multiplying by min" << gcd << endl;
    cout << "k_a is " << k_a << endl;
    cout << "k_b is " << k_b << endl;
    gcd = (gcd * min(k_a, k_b));
    cout << "gcd is" << gcd << endl;
    cout << "ShiftCount/getBitLength(a)" << (shiftCount/double(getBitLength(a)))*100 << endl;

    cout << "Bit length of a is: " << double(getBitLength(a)) << endl;
    cout << "Bit length of b is: " << double(getBitLength(b)) << endl;
    cout << "Shift count is: " << shiftCount << endl;

    int index = 0;

    if(getBitLength(a) >= getBitLength(b))
    {
      index = (shiftCount/(double(getBitLength(a))))*100;
    }
    else
    {
      index = (shiftCount/(double(getBitLength(b))))*100;
    }

    ++shiftFracFreqs.at(index);
    return gcd;
    
  }

/*********************************************************************
 * Naive gcd function.
 * This computes the gcd of two 'LONG' values 'a' and 'b' using the
 * standard naive algorithm that uses division.
 *
 * Implementation of the algorithm:
 * We initially assign 'big' <-- 'a' and 'small' <-- 'b'.
 * We then ensure that 'big' and 'small' are nonnegative.
 * If either is zero, then the gcd is the other value.
 * Now loop: 
 *     Set 'rem' to the value of 'big' modulo 'small' 
 *     While 'rem' is still positive:
 *         'big' <-- 'small'         
 *         'small' <-- 'rem'         
 *         'rem' <-- 'big' modulo ''small'         
 *     When the loop finishes, return 'small' as the gcd
 * 
 * Note: We permit 'a' and 'b' to be negative and return the gcd of
 *       the absolute values of 'a' and 'b'.
 * Note: If we start with 'a' < 'b', then the first step just flips the
 *       order, and after that we will always have 'small' < 'big'.
 * Note: The test for 'big' being 0 covers the case when both inputs are 0
 *       and we return 0 as the gcd.
 * Note: The test for 'small' being 0 ensures we don't try to mod down
 *       by 0, which isn't well defined.
 * 
 * Parameters:
 *   a, b - the values for which to compute the gcd
 * Returns::
 *   the gcd of a and b
 *
 * [NOTE CAREFULLY HERE ALL THE 'NOTES'. THEY POINT OUT THE SPECIAL CASES
 *  AND HOW THEY ARE HANDLED.]
**/
LONG GCDTest::gcdNaive(LONG a, LONG b)
{
  LONG big, small, rem;
  big = a;
  small = b;
  if (big < 0L)
    big = -big;
  if (small < 0L)
    small = -small;
  if (0L == big)
    return(small);
  else if (0L == small)
    return(big);
  else
  {
    rem = big % small;
    while (rem != 0L)
    {
      big = small;
      small = rem;
      rem = big % small;
    }
    return(small);
  }
}

/*********************************************************************
**/
int GCDTest::getBitLength(LONG n)
{
  int length = 0;
  int mask = 2147483647;
  string binaryString = "";

  if (0 == n) return 0; // this is a fudge

  if (n < 0) return 32;

  binaryString = convertToBinary(n);
  length = binaryString.size();

  return length;
}

/*********************************************************************
**/
void GCDTest::runTheTests()
{
  double timeNew;
  string timestring;

  // test binary
  // the 'true' variable says we want to do the additional test on
  //     the quotients a/g and b/g to try to verify that in fact our
  //     gcd is correct
  timestring = Utils::timecall("bef binary true", timeNew);
  cout << timestring << endl;
  testBinary(true);
  timestring = Utils::timecall("aft binary true", timeNew);
  cout << timestring << endl;

  cout << "done with the computation" << endl;
}

/*********************************************************************
 * This function simply turns the 'vector' of bit length frequencies
 * into a readable formatted string for printing by the function
 * that called it.
**/
string GCDTest::stringifyBitLengthFreqs()
{
  string s = "Frequencies of bit lengths\n";

  for(int i = 0; i < bitLengthFreqs.size(); i++)
  {
    s = s + to_string(i) + "     " + to_string(bitLengthFreqs.at(i)) + "\n";
  }

  return s;
}

/*********************************************************************
 * This function simply turns the 'vector' of shift fractions
 * frequencies into a readable formatted string for printing by the
 * function that called it. 
**/
string GCDTest::stringifyShiftFracFreqs()
{
  string s = "Frequencies of shift fractions\n";

  for(int i = 0; i < shiftFracFreqs.size(); i++)
  {
    if(shiftFracFreqs.at(i) != 0)
    {
    s = s + to_string(i) + "     " + to_string(shiftFracFreqs.at(i)) + "\n";
    }
  }

  return s;
}

/*********************************************************************
**/
void GCDTest::testBinary(bool extraTest)
{
  LONG a, aa, b, bb, g, gg;
  LONG testlimit = (LONG) this->veca.size()/10;

  for (UINT i = 0; i < this->veca.size(); ++i)
  {
    a = this->veca.at(i);
    b = this->vecb.at(i);
    g = this->gcdBinary(a, b);

    if (0 == (i % testlimit))
    {
      cout << this->formatProgress(i, a, b, -1, g, -1) << endl;
    }

    if (extraTest)
    {
      aa = a/g;
      bb = b/g;
      gg = this->gcdNaive(aa, bb);
      if (gg != 1)
      {
        cout << "ERROR " << a << " " << b << " " << g << endl;
        exit(0);
      }
    }
  }
}

