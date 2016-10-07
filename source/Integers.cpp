/*
Title: Representation of Integers and Floating Point numbers
File Name: Integers.cpp
Copyright © 2016
Author: Andrew Litfin
Written under the supervision of David I. Schwartz, Ph.D., and
supported by a professional development seed grant from the B. Thomas
Golisano College of Computing & Information Sciences
(https://www.rit.edu/gccis) at the Rochester Institute of Technology.
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.
This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "../header/ClassDeclarations.h"

void Integers::IntegersExample()
{
	std::cout << "Integers Example\n----------------\n";

	/////////////////////
	// Numeral systems //
	/////////////////////

	// Computers, as you are probably aware, work on nothing more than a series of zeroes and ones.
	// How then do they represent a number such as 42?
	// To understand, we must know what is meant by the term "numeral system."
	// A numeral system is a writing system to express numbers.
	// The most common system in use today base 10 (the number of fingers on your hands).
	// Hence a number such as 231 in base 10 actually means 2*10^2 + 3*10^1 + 1*10^0 (where I use ^ for exponentiation).
	// It is possible to choose any natural number greater than 1 as a base (what happens when you exponentiate 1 to any power?).
	// In this way, the base 10 value 231 in base 8 is 347 = 3*8^2 + 4*8^1 + 7*8^0, or in base 16 is E7 = 14*16^1 + 7*16^0.
	//  (Base 16 in a common base used by programmers. The base 16 digits A-F represent the base 10 numbers 10-15.)
	if (231 == 0347 && 231 == 0xE7)
		std::cout << "231 is 347 in octal or E7 in hexadecimal.\n";
	// N.B. If a number starts with 0, it is interpreted as being in octal (base 8),
	//  and if a number starts with 0x, it is interpreted as being a hexadecimal number (base 16).

	// Computers operate solely in base 2. In this way, there are exactly two digits: 0 and 1.
	// So, 231 in base 2 is 11100111 = 1*2^7 + 1*2^6 + 1*2^5 + 0*2^4 + 0*2^3 + 1*2^2 + 1*2^1 + 1*2^0.
	// Each 0 and 1 is called a "bit," short for "binary digit." A set of 8 bits is called a "byte."
	//  (As an aside, a set of 4 bits is called a "nibble," and a nibble can be represented by one hexadecimal digit.
	//   This is why one byte is represented as two hexadecimal digits, or equivalently, two nibbles.)
	if (231 == 0b11100111)
		std::cout << "231 is 11100111 in binary.\n";
	// N.B. Similar to above, a 0b prefix indicates a binary literal.

	// More examples of different representations of the same value:
	int myNum0 =  4095; // decimal (base 10)
	int myNum1 = 0xFFF; // hexadecimal (base 16)
	int myNum2 = 07777; // octal (base 8)
	int myNum3 = 0b111111111111; // binary (base 2)
	// As you can see, as the radix (base number) increases, the amount of information encoded in one digit increases,
	//  so the total length of the string representing the value decreases.
	// Conversely, as the radix decreases, so does the amount of information encoded in one digit, so the length increases.

	// So that's how computers represent integers! As a series of 0s and 1s in base 2.

	///////////////////
	// Integer types //
	///////////////////

	// In C++ and many similar languages, there are a few types of integers, all of which work the same way, varying only in size.
	// These are, from smallest to largest,
	//  - short
	//  - int
	//  - long
	//  - long long (since C++11)
	// The exact sizes differ based on which compiler and target architecture are used,
	//  but the C++ standard specifies they are, respectively, at _least_ 2, 2, 4, and 8 bytes, (16, 16, 32, and 64 bits)
	//  though look at the output from the next lines to see the exact values on your system.
	std::cout << "sizeof(short): " << sizeof(short) << '\n';
	std::cout << "sizeof(int): " << sizeof(int) << '\n';
	std::cout << "sizeof(long): " << sizeof(long) << '\n';
	std::cout << "sizeof(long long): " << sizeof(long long) << '\n';
	// The standard also guarantees that the sizes are ordered as given above.
	// Not all languages make this distinction explicit, but all modern languages represent integers this way.

	/////////////////////
	// Signed integers //
	/////////////////////

	// You might think "how then does a computer represent a negative integer?"
	// Enter: the Sign Bit.
	// For each of the four types of integers listed above, there are two flavors: signed and unsigned.
	//  - Unsigned integers work exactly as above, as a strictly base 2 number,
	//    where each 0 and 1 represents the presence or absence of a power of two.
	//    As such, an unsigned integer of bit length n can represent any integer between 0 and 2^n - 1.
	//    For example, an unsigned short can exactly represent any integer between 0 and 65535 (inclusive).
	//  - Signed integers have one special bit at the start (the "most significant" bit, which is farthest left)
	//    that says whether the number in question is positive or negative.
	//    From here there are two ways of representing negative numbers:
	//    * One's complement: Invert all bits. So, where 3 is 0...0011, -3 is 1...1100 
	//       (note that the first bit is 1, indicating negative)
	//      One's complement can only represent integers between -(2^(n-1) - 1) and 2^(n-1) - 1 (inclusive).
	//       So a signed short using one's complement can exactly represent numbers between -32767 and 32767 (inclusive).
	//      As an interesting consequence, there are actually two ways of representing 0:
	//       1...1111 and 0...0000, where the former is -0 and the latter is +0.
	//    * Two's complement: Invert all bits and add one. Using the example from above, 3 is still 0...0011, but -3 is 1...1101.
	//      Two's complement can represent integers between -2^(n-1) and 2^(n-1) - 1 (inclusive).
	//       For example, a signed short can represent any integer between -32768 and 32767.
	//      Two's complement avoids the problem of having two representations of zero.
	//       If you try to apply two's complement to zero, you actually achieve integer overflow 
	//        and the value wraps back around to 0.
	//      Two's complement is what almost every modern computer architecture uses to represent negative numbers.
	if (-3 == 0xFFFFFFFD)
		std::cout << "This is how negative numbers look to a computer.\n";
	if ((0 ^ 0xFFFFFFFF) + 1 == 0)
		std::cout << "This is how two's complement avoids two representations of zero.\n";
	// N.B. In the last line, the ^ is the XOR operator. By XORing with a mask of all 1s, we invert every bit.

	////////////////////////////////
	// Maximum and minimum values //
	////////////////////////////////

	// Since numbers on computers have fixed lengths, they can only represent a finite number of distinct values.
	// In C++, they are as follows:
	std::cout << "Unsigned Short - Minimum: 0 Maximum: " << USHRT_MAX << '\n';
	std::cout << "Unsigned Int - Minimum: 0 Maximum: " << UINT_MAX << '\n';
	std::cout << "Unsigned Long - Minimum: 0 Maximum: " << ULONG_MAX << '\n';
	std::cout << "Unsigned Long Long - Minimum: 0 Maximum: " << ULLONG_MAX << '\n';
	std::cout << "Signed Short - Minimum: " << SHRT_MIN << " Maximum: " << SHRT_MAX << '\n';
	std::cout << "Signed Int - Minimum: " << INT_MIN << " Maximum: " << INT_MAX << '\n';
	std::cout << "Signed Long - Minimum: " << LONG_MIN << " Maximum: " << LONG_MAX << '\n';
	std::cout << "Signed Long Long - Minimum: " << LLONG_MIN << " Maximum: " << LLONG_MAX << '\n';
}
