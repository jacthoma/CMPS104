/*	Author:  James Thomas
 *	Contact: jacthoma@ucsc.edu	
 *
 *	File:    jct_lib.cpp
 *
 *  Description: 
 *  	Various C++ functions that I have found helpful
 * 		and have needed to use multiple times.
 */

#ifndef JCT_LIB_H
#define JCT_LIB_H
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>

using namespace std;


//	Method: string Right
//		The specified number of characters starting from the right of the string
//
//	Arguments: 
//		string s 	 : the string to take the segment from
//		int num_char : the number of characters to select from the string
// 
//	Output:
//		string out_string : the specified number of characters from the right portion of the input string
string Right(const string s, int num_char){
	string out_string = "";
	for( string::const_iterator it = s.end()-num_char; it != s.end(); ++it ){
		out_string += *it;
	}
	return out_string;
}
//	Alternative version of string Right
//		returns all characters before a specified character is found
string Right(const string s, char find_char){
	string out_string = "";
	string::const_iterator it = s.end()-1;
	while(*it != find_char){
		out_string = *it + out_string;
		it--;
		if(it == s.begin()-1){
			break;
		}
	}
	return out_string;
}

//	Method: string Left
//		The specified number of characters starting from the left of the string
//
//	Arguments: 
//		string s : the string to take the segment from
//		int num_char : the number of characters to select from the string
// 
//	Output:
//		string out_string: the specified number of characters from the left portion of the input string
string Left(const string s, int num_char){
	string out_string = "";
	for( string::const_iterator it = s.begin(); it != s.begin()+num_char; ++it ){
		out_string += *it;
	}
	return out_string;
}
//  Alternative version of string Left
//		returns all charters before a specified character is found
string Left(const string s, char find_char){
	string out_string = "";
	string::const_iterator it = s.begin();
	while(*it != find_char){
		out_string += *it;
		it++;
	}
	return out_string;
}

//	Method: int ReverseFind
//		Returns the location of a string in a string 
//		giving priotity to the characters at the end of th string
//
//	Arguments:
//		string s : the string to be search
//		string find : the character or string to be found
//
//	Output:
//		index : the index of the found character
//			-1 if the character or string was not found
int ReverseFind(string s, string find){
	int index = 0;
	int s_index = s.length();
	string test;
	string::const_iterator it = s.end();
	string::const_iterator find_it;
	while(it != s.begin()){
		if(*it == *find.begin()){
			find_it = it;
			for(int i = 0; i < (int)find.length(); i++){
				test += *find_it;
				find_it ++;
			}
			if(test.compare(find) == 0){
				return s_index;
			}
		}
		--it;
		--s_index;
	}
	return index;
}

//	Method: int ReverseFind
//		Returns the location of a character in a string 
//		giving priotity to the characters at the end of th string
//
//	Arguments:
//		string s  : the string to be search
//		char find : the character to be found
//
//	Output:
//		index : the index of the found character
//			-1 if the character or string was not found
int ReverseFind(string s, char find){
	int index = -1;
	int c_index = s.length();
	string::const_iterator it = s.end();
	while(it != s.begin()){
		if(*it == find){
			return c_index;
		}
		--it;
		--c_index;
	}
	return index;
}

//	Method: string Mid
//		returns a potion of the string specified but the arguments
//
//	Arguments:
//		string s    : the initial input string
//		int s_index : the index of the input string that is to be
//					  the begining of the output string
//		n_count     : the number of characters to extract from the
//			          input string and return in the output string
//
//	Output:
//		string out_string	: a middle segment of the input string
string Mid(string s, int s_index, int n_count){
	string out_string = "";
	string::const_iterator it = s.begin() + s_index;
	while(it != s.begin() + s_index + n_count){
		out_string += *it;
		it++;
	}
	return out_string;
}

//	Method: char* string_to_char
//		convert a string to an array of characters
//
//	Arguments: string s  : the string to be converted to characters
//
//	Output: char* output : the character string representation of the input string, s
char* str_to_char(string s){
	char* output = new char[ s.length()+1 ];
	strcpy(output, s.c_str());
	return output;
}

//	Method: char* str_is_number
//		check if a string contains only integer digits
//
//	Arguments: string input_string, the string to be checked
//
//	Outut: true if input_string contains only integer digits, false otherwise
inline bool str_is_number(const string input_string){
	string::const_iterator it = input_string.begin();
	while(it != input_string.end() && isdigit(*it)) ++it;
	return !input_string.empty() && it == input_string.end();
}

//	Method: filesize
//		returns the file size in bytes of a file
//
//	Arguments:
//		char* filename: name of the file for analysis 
//
//	Output:
//		length of the input file
ifstream::pos_type filesize(const char* filename){
   	ifstream in(filename, ifstream::in | ifstream::binary);
  	in.seekg(0, ifstream::end);
  	return in.tellg(); 
}

//	Method: aboslute_double
//		returns the absolute value of a double
//
//	Arguments:
//		double d : the double to perform the absolute value function on
//
//	Output:
//		the absolute value of the input
inline double absolute_double(double d){
	if(d < 0){
		return (-1 * d);
	}
	return d;
}
#endif
