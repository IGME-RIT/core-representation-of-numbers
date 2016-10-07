/*
Title: Representation of Integers and Floating Point numbers
File Name: main.cpp
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

// Programmers use numbers all the time in their work.  This begs the question,
//  "How do computers internally represent and modify numbers?"
// The answer is dependent on whether we are storing an integer (e.g. 3, -42, etc.) or
//  a floating point (anything not an integer) number (e.g. 0.1, 143.31, pi, etc.).
// See Integers.cpp to see how a computer deals with integers, and FloatingPoint.cpp for floats.
// We assume familiarity with the idea of a base system and with scientific notation.

#include "../header/ClassDeclarations.h"

int main() {
	Integers::IntegersExample();
	FloatingPoint::FloatingPointExample();

	std::cin.ignore();
	return 0;
}
