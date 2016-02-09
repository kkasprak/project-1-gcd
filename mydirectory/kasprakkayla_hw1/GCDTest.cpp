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
 * Modified and used with permission by: Kayla Kasprak
 * Date last modified: 8 February 2016
 *
 **/

 #include "GCDTest.h"

/******************************************************************************
 * Constructor.
 **/
GCDTest::GCDTest()
{
}

/******************************************************************************
 * Destructor.
 **/
GCDTest::~GCDTest()
{
}

/******************************************************************************
 * General functions.
 **/

/******************************************************************************
 * Function to convert a binary number to a string of bits.
 * This computes the binary representation of a 'LONG' value 'n' in string
 * form.
 *
 * Implementation of the algorithm:
 * An empty string 'bits' is initalized to hold the string of bits.
 *
 * While 'n' is not zero, the following loop will run:
 *   If the number modulo 2 is equal to zero, it is even and a 0 should be 
 *   added to 'bits' at the beginning of the string.
 *
 *   Else, the number modulo 2 is equal to one and it is an odd number, which
 *   means that a 1 should be added to 'bits' at the begining of the string.
 *
 * Parameters:
 *   n - the number value being converted to a string of binary digits.
 * Returns::
 *   the string 'bits' consisting of 0's and 1's which is the binary
 *   representation of n.
 **/
string GCDTest::convertToBinary(LONG n)
{
  string bits = "";
  while (n != 0)
  {
    if (n % 2 == 0)//remainder of 0 after dividing by 2
    {
            bits = "0" + bits;
            //n = n >> 1;//n/2
            n = n/2;
        }
        else
        {
            bits = "1" + bits; //remainder of 1 after dividing by 2
            //n = n >> 1;//n/2
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
 * Binary gcd function.
 * This computes the gcd of two 'LONG' values 'a' and 'b' using the
 * subtract and shift alglorithm.
 *
 * Implementation of the algorithm:
 * We initially assign 'a_odd' <-- 'a' and 'b_odd' <-- 'b'.
 * We also assign k_a and k_b to equal 1. These will be the powers of
 * two that we will remove from a and b.
 *     a^1 = 1, so if no powers of two are removed, k=1.
 * The variables big, small, temp, and gcd are all of type 'LONG' and
 * are initialized to be zero.
 * The 'double' 'shiftCount' will be used to count the number of free
 * shifts. It must be of type 'double' because it is used in a
 * division caluclation with another double at the end of the function.
 *
 * If 'a' and 'b' are equal, the gcd is 'a' or 'b'. If either 'a' or 
 * 'b' are zero, then the gcd is the other value. We also ensure that
 * 'a' and 'b' are non-negative by returning the absolute value if they
 * in this special case.
 *
 * To remove the k_a powers of 2 in a to produce a_odd, loop:
 *     While 'a_odd' modulo 2 is 0 (a_odd is even) AND it is not equal
 *     to zero:
 *         the value k_a is increased by multiplying it by 2
 *         divide 'a' by 2 by 'a_odd >> 1'
 *     While 'b_odd' modulo 2 is 0 (a_odd is even) AND it is not equal
 *      to zero:
 *         the value of k_b is increased by multiplying it by 2
 *         divide 'b' by 2 by 'b_odd >> 1'
 *
 * To determine which is greater, 'a_odd' or 'b_odd':
 *     If 'a_odd' is greater than 'b_odd':
 *         'big' <-- 'a_odd' 
 *         'small' <-- 'b_odd'
 *     If 'b_odd' is greater than 'a_odd':
 *         'big' <-- 'b_odd'
 *         'small' <-- 'a_odd'
 *
 * Now that k_a and k_b powers of 2 have been removed from 'a_odd'
 * and 'b_odd' and the larger value has been assigned to 'big' and
 * the smaller value has been assined to small, we can begin to 
 * calculate the gcd:
 *     While the smaller number 'small' is not zero, loop:
 *         'big' <-- 'big' minus 'small'
 *         'big' <-- 'big' shifted right one bit
 *             (equal to 'big' divided by 2)
 *         While 'big' is even (binary ends in zero) and value of 'big' 
 *         is not equal to 0:
 *             shift 'big' right one bit (these are additional free shifts)
 *             for each free shift, 'shiftCount' increments by one'
 *
 *             After all free shifts, we check to see if 'a_odd' is greater
 *             than 'b_odd'. If so, 'a_odd' <-- 'big' and 'b_odd' <-- 'small'.
 *             If 'a_odd' is less than 'b_odd', 'a_odd' <-- 'small' and 
 *             'b_odd' <-- 'big'.
 *             
 *             The odd part of the gcd is 'big', so if 'big' modulus 2 is
 *             equal to 1, 'big' is odd and 'gcd' <-- 'big'. If it is not
 *             odd, 'small' must be odd and therefore 'gcd' <-- 'small'.
 *
 * Now we compare the bit lenths of 'a' and 'b'. The occurnece of the number 
 * of shifts (after the first free shift) divided by the bit length of either
 * 'a' or 'b' (whichever operand is greater) is the index at which the
 * frequency count will be incremented. This is done by the following:
 *     If the bit length of a is greather than the bit length of b
 *         index <-- (shiftCount divided by the bit length of a)*100
 *     Else the bit length of b is greater than the bit length of a
 *         index <-- (shiftCount divided by the bit length of b)*100
 * After calculating the index, increment the value at that index by one.
 *
 * Lastly, calculate the final value of the greatest common divisor 'gcd'
 * but raising the value to either 'k_a' or 'k_b', whichever value is
 * smaller. This is simply raising the gcd to 'k_a' or 'k_b' powers of
 * of two - the reverse of which was done at the beginning of the
 * algorithm.   
 * 
 * Return the gcd.      
 *
 * Note: We permit 'a' and 'b' to be negative and return the gcd of
 *       the absolute values of 'a' and 'b'.
 * Note: The test for 'big' being 0 covers the case when both inputs are 0
 *       and we return 0 as the gcd.
 * Note: In the GCD calculation, we test to make sure 'small' is not 0 in
 *       the outer loop and 'big' is not 0 in the inner loop to avoid
 *       infinite loops.
 *
 * Parameters:
 *   a, b - the values for which to compute the gcd
 * Returns::
 *   the gcd of a and b
 *
 **/
LONG GCDTest::gcdBinary(LONG a, LONG b)
{
    LONG k_a = 1;
    LONG k_b = 1;
    LONG a_odd = a;
    LONG b_odd = b;
    LONG big = 0;
    LONG small = 0;
    LONG temp = 0;
    LONG gcd = 0;
    double shiftCount = 0.0;
    int index = 0;
    
    if (a == b)
        return a;
    if (a == 0)
        return b;
    if (b == 0)
        return a;
    if (a < 0L)
        a = -a;
    if (b < 0L)
        b = -b;

    //Given nonnegative integers a and b
    //Remove the k_a powers of 2 in a to produce a_odd
    //Remove the k_b powers of 2 in b to produce b_odd
    while (a_odd % 2 == 0 && a_odd != 0) //a is even
    {
        k_a = (k_a * 2);
        a_odd = (a_odd >> 1); //a_odd/2
    }
    while (b_odd % 2 == 0 && b_odd !=0) //b is even
    {
        k_b = (k_b * 2);
        b_odd = (b_odd >> 1); //b_odd/2
    }

    //Assign the larger value to 'big' and the 
    //smaller value to 'odd'
    if (a_odd >= b_odd)
    {
        big = a_odd;
        small = b_odd;
    }
    if (a_odd < b_odd)
    {
        big = b_odd;
        small = a_odd;
    }
    
    //GCD Calculation
    while(small != 0)
    {
        big = big - small;
        big = big >> 1;
        //Check for free shifts
        while(big % 2 == 0 && big != 0)
        {
            big = big >> 1; //shift
            shiftCount++; //Increments for each free shift
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
    
    //Frequencies of occurence of the number of shifts divided
    //by the max bit length of the operands
    if(getBitLength(a) >= getBitLength(b))
    {
        index = (shiftCount/(static_cast<double>(getBitLength(a))))*100;
    }
    else
    {
        index = (shiftCount/(static_cast<double>(getBitLength(b))))*100;
    }

    //Increment the value at the index
    ++shiftFracFreqs.at(index);

    //Put back min(m_a, k_b) powers of 2
    gcd = (gcd * min(k_a, k_b));
    //Return gcd
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

/******************************************************************************
 * Function to get the bit length of a number 'n' of type 'LONG'
 * The variable 'length' is initialized to 0 and the 'string' 'binaryString'
 * is initialized to be empty.
 * 
 * If the number 'n' is 0, the length is 0 and the function will return 0.
 * If the number 'n' is less than 0, return bit length of 32 since it is a
 *     signed integer.
 * Else, pass 'n' to the function convertToBinary and assign the resulting
 *     string to 'binary string'.
 * Now we set 'lenth' <-- size of 'binaryString' 
 * 
 * NOTE: We handle exception of n being 0 by returning a bit length of 0.
 * NOTE: We handle the exception of n being negative by returning a bit length
 *      of 32.
 * NOTE: If n equals 1, the function returns a bit length of 1.
 *
 * Parameters:
 *   number 'n' of type 'LONG'
 * Returns::
 *   'int' 'length' containing  the length of the string of bits
 * 
 **/
int GCDTest::getBitLength(LONG n)
{
    int length = 0;
    int mask = 2147483647;
    string binaryString = "";
    
    if (0 == n) return 0; //this is a fudge
    
    if (n < 0) return 32;

    if (n == 1) return 1;
    
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
 * 
 * Parameters:
 *   None
 * Returns::
 *   string 's' containing bit lengths
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
 * 
 * NOTE: This function does not print indices holding a value of 0
 *
 * Parameters:
 *   none
 * Returns::
 *   string 's' containing the count (frequency) of bit lengths at
 *   the index calculated in the gcdBinary function
 **/
string GCDTest::stringifyShiftFracFreqs()
{
    string s = "Frequencies of shift fractions\n";
    
    for(int i = 0; i < shiftFracFreqs.size(); i++)
    {
        if(shiftFracFreqs.at(i) != 0)
        {
            s = s + to_string(i) + "     " + 
            to_string(shiftFracFreqs.at(i)) + "\n";
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

