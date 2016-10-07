/*
Title: Representation of Integers and Floating Point numbers
File Name: FloatingPoint.cpp
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

#include "ClassDeclarations.h"

// Create a union of a floating point number and an integer.
// In this way we can set the bits of a floating point number manually.
//  (Floating point numbers do not allow bitwise operations.)
// If you don't know what the union keyword does, see [core-keywords].
union FloatOrUInt32
{
	uint32_t i;
	float f;
};

// The following structure and function will be useful in the last part of the example, but must be defined here.
// A 3D vector
struct vec3 {
	float x, y, z;
};

// Compute the dot product of two vec3s
float Vec3_DotProduct(vec3 lhs, vec3 rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

void FloatingPoint::FloatingPointExample()
{
	std::cout << "\nFloating Point\n--------------\n";
	std::cout << std::setprecision(10);
	// The following exposition follows that of Bishop and Verth in "Essential Mathematics for Games."

	////////////////////////////////
	// Scientific notation review //
	////////////////////////////////

	// To understand floating point numbers, it will be helpful to review scientific notation.
	// Scientific notation for a real number is defined as being the following form:
	//   1) A real number, called the significand, such that the absolute value is between 
	//       1.0 (inclusive) and 10.0 (exclusive).
	//      E.g. -5.4 is a valid significand, but 11.2 or 0.42 could not.
	//      (The significand is more commonly referred to as the mantissa.
	//       While this terminology is common among programmers, it is not historically accurate,
	//        and is discouraged by the IEEE floating-point standard.
	//        for more information, see <https://en.wikipedia.org/wiki/Significand>.)
	//   2) An integer, called the exponent.
	// The scientific notation of a value is then
	//   significand * 10^(exponent).
	// The only exception is the value 0, which is represented simply as 0.0.

	////////////////////////////////
	// Binary scientific notation //
	////////////////////////////////

	// Binary scientific notation works exactly as above.
	//  1) The significand has absolute value between 1.0 (inclusive) and 2.0 (exclusive)
	//  2) An integer exponent
	// The value is
	//  significand * 2^(exponent)
	// As a consequence of (1), all binary scientific numbers start with a 1, with the exception of the value 0.

	// For example, 42 in base 10, which is 101010 in base 2, has scientific representations of 4.2 * 10^1 and 1.0101 * 2^4

	////////////////////
	// Floating point //
	////////////////////

	// Nearly all modern systems use IEEE754 floating point to represent non-integer values.
	// It is based on binary scientific notation.
	// A single-precision floating point value is a 32-bit number with the following layout:
	//  - 1 sign bit
	//  - 8 exponent bits (unsigned)
	//  - 23 significand bits (unsigned)
	// When represented visually, they are usually broken into blocks, such as
	//  0|011_1110_0|010_0000_0000_0000_0000_0000, which is the value 0.15625 exactly.
	// The value is given by (-1)^s * (1.F)_2 * 2^(e-127), where F is the "fractional" portion (i.e., the fractional part of the significand).
	//  The leading 1 is implicit, since as noted in the above section, all values in binary scientific notation start with a 1.
	//  Note the similarity to binary scientific notation.
	//  In the example, we have (-1)^0 * (1.01000000000000000000000)_2 * 2^(124 - 127) = (1) * (1.01)_2 * 2^(-3) = 2^-3 + 2^-5 = 0.15625.

	// You may think "Why is 127 automatically subracted from the exponent?" In short, it allows for the first bit to "act like" a sign,
	//  even though it's not.  When the exponent is 0x00 or 0xFF, that indicates either that the value is zero or subnormal
	//   (see <https://en.wikipedia.org/wiki/Denormal_number>),
	//  or that the value is "infinite" or NaN, respectively.

	// +-------------------------------------------------+
	// | Exponent | Significand 0 | Significand non-zero |
	// |----------|---------------|----------------------|
	// |   0x00   |    0 or -0    |   denormal number    |
	// |0x01..0xFE|         normalized value             |
	// |   0xFF   |  inf or -inf  |          NaN         |
	// +-------------------------------------------------+

	////////////////////////////////////////////////////////
	// Example: manually creating a floating point number //
	////////////////////////////////////////////////////////

	// Example 1
	// Let's apply what we've learned to see if we can construct a floating point number on our own.
	// Let's see if we can manually construct the number 42.0f.
	// In binary scientific notation, 42 = 32 + 8 + 2 = 2^5 + 2^3 + 2^1 = (1 + 2^-2 + 2^-4)*2^5 = 1.0101_2 * 2^101_2
	// Then the final bitfield should look like this:
	// 0|100_0010_0|010_1000_0000_0000_0000_0000
	//  -Sign is positive
	//  -Remember that IEEE754 subtracts 127 from the given exponent to get the actual exponent
	//  -Leading 1 is implicit

	FloatOrUInt32 fortytwo = { 0x42280000 }; // This is the hexadecimal form of the bitfield above.
	std::cout << "Forty two as a float is " << fortytwo.f << '\n';

	// Example 2
	// A slightly more difficult example: -34.75
	// -34.75 = (-1) * (32 + 2 + 0.5 + 0.25) = (-1) * (2^5 + 2^1 + 2^-1 + 2^-2) = (-1) * (1 + 2^-4 + 2^-6 + 2^-7) * 2^5
	//  = (-1) * 1.0001011 * 2^5
	// The bitfield then is
	// 1|100_0010_0|000_1011_0000_0000_0000_0000
	//  -Only major difference from the last one is the sign is negative

	FloatOrUInt32 negativethirtyfourpointsevenfive = { 0xC20B0000 };
	std::cout << "Negative thirty four point seven five as a float is " << negativethirtyfourpointsevenfive.f << '\n';

	// Example 3
	// The previous two examples were "easy" in that the numbers could be exactly represented.
	// Indeed, this is the case in single-precision floating point numbers for all integers from -2^24 up to 2^24.
	// Let's try representing 0.1.
	// We have 0.1 = 0.0625 + 0.03125 + 0.00390625 + 0.001953125 + ... = 2^-4 + 2^-5 + 2^-8 + 2^-9 + ...
	//  = 0.0(0011), where the parenthesis indicate the inner part is repeated indefinitely.
	// Then this is 1.(1001)_2 * 2^-4.
	// However, as was mentioned earlier, the computer has only a finite amount of space to work with.
	// At some point it _must_ stop and have a final digit.
	// So what we have so far is
	// 0|011_1101_1|100_1100_1100_1100_1100_1100|_1100...
	// At this point there are two options: the computer can either truncate all the rest, at which point the result is
	FloatOrUInt32 slightlylessthanzeropointone = { 0x3DCCCCCC };
	std::cout << "Truncating rounding gives 0.1f = " << slightlylessthanzeropointone.f << '\n';

	// Alternatively the computer can look at the next four actual digits (1100) and round up the last digit to be
	FloatOrUInt32 slightlygreaterthanzeropointone = { 0x3DCCCCCD };
	if (0.1f == slightlygreaterthanzeropointone.f)
		std::cout << "Rounding up gives 0.1f = " << slightlygreaterthanzeropointone.f << '\n';

	// Rounding up has a lower relative error, so the computer chooses that route.
	// (By relative error, I mean if the actual number is A, RelErr_A = abs((Repr(A)-A)/A).)

	// This is why 0.1 + 0.2 is not exactly 0.3.  This is a big problem for things like financial transations,
	//  and is the motivation behind the Decimal type.  For most purposes however, floating point is accurate enough.
	// You can find more information on the decimal type at <https://en.wikipedia.org/wiki/Decimal_data_type>.

	//////////////////////////////
	// Limitations in precision //
	//////////////////////////////

	// In general, floating point is only accurate to about 7 decimal places (depending on the value being represented).
	// Floating point arithmetic then is almost never exact, and can lead to problems when dealing with numbers
	//  that have large differences in magnitude.
	// For example:
	if (1000000.0f + 0.01f == 1000000.0f)
		std::cout << "One million plus one one-hundredth is equal to one million.\n";

	// In general, as soon as you perform any operations to floating point numbers, you lose precision.
	// As goes the saying: "You lose precision if you breathe. Floats can smell the fear of the edge case."

	////////////////////////////////
	// Maximum and minimum values //
	////////////////////////////////

	// Much as with integers, since floating point numbers have a fixed length, they can only represent a finite set of values.
	// The standard doesn't refers to the least representable value (at least in C++11) as lowest.
	// Minimum is instead reserved for the minimum normalized positive value of the type.
	std::cout << "Single-precision float - Lowest: " << -FLT_MAX << " Maximum: " 
		<< FLT_MAX << " Smallest non-zero: " << FLT_MIN << '\n';
	std::cout << "Double-precision float - Lowest: " << -DBL_MAX << " Maximum: " 
		<< DBL_MAX << " Smallest non-zero: " << DBL_MIN << '\n';
	std::cout << "Extended-precision float - Lowest: " << -LDBL_MAX << " Maximum: " 
		<< LDBL_MAX << " Smallest non-zero: " << LDBL_MIN << '\n';

	// As mentioned above briefly, IEEE754 supports "denormal" numbers. These extend the range, but at a loss of precision.
	// The minimum positive denormal numbers are
	std::cout << "Single-precision float - Smallest denormal: " << FLT_TRUE_MIN << '\n';
	std::cout << "Double-precision float - Smallest denormal: " << DBL_TRUE_MIN << '\n';
	std::cout << "Extended-precision float - Smallest denormal: " << LDBL_TRUE_MIN << '\n';

	///////////////////////////////////////////
	// Application: Epsilon and dot products //
	///////////////////////////////////////////

	// Epsilon is a new idea that will also be useful to know: it is the difference between 1.0 and the next representable value.
	//  It is most often used to avoid checking equality, since floating point numbers tend to drift away from exact values.
	//  For example, in games programming, say you want to check if a point is on a plane.
	//   Rather than taking a dot product of the point with the plane normal and checking for equality to zero,
	//    you will probably want instead to check if the dot product is within a range around zero.

	// Say we have a plane defined by the normal
	vec3 normal = { 1.0f / sqrtf(3.0f), 1.0f / sqrtf(3.0f), 1.0f / sqrtf(3.0f) };
	// that intersects the origin.
	// We want to check if the position
	vec3 position = { 0.78063f, 0.984654f, -1.765284f };
	// is on the plane.

	// We can check this by calculating the dot product of the position with the normal and checking if it is zero.

	// The position is on the plane (as can be confirmed by hand or via Wolfram|Alpha), but
	if (Vec3_DotProduct(position, normal) == 0.0f)
		std::cout << "This won't get printed because the floating point result is not exactly zero.\n";
	// Instead we need
	if (Vec3_DotProduct(position, normal) <= FLT_EPSILON)
		std::cout << "This will get printed, because Vec3_DotProduct(position, normal) actually returns "
			<< Vec3_DotProduct(position, normal) << '\n';

	// Don't worry if you don't know how this code relates to the geometric interpretation of a plane.
	// What you need to know now is how the dot product is calculated:
	//  as the multiplication and addition of floating point numbers.
	// This example shows how floating point representations of most real numbers is not exact.
}
