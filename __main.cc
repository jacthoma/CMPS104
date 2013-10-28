/* James Thomas
 * jacthoma@ucsc.edu
 *
 * CMPS 104a
 * Assignment 1
 *
 * variables in snake_case
 * fucntions in camelCase
 */

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "jct_lib.h"

#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lyutils.h"
#include "auxlib.h"
#include "astree.h"
#include "stringset.h"
#include <ctime>

using namespace std;

const string cpp_name = "/usr/bin/cpp";
const size_t LINESIZE = 1024;
string yyin_cpp_command;
// From cppstrtok.cc
// 
// Chomp the last character from a buffer if it is delim.

/*
void chomp (char* string, char delim) {
   size_t len = strlen (string);
   if (len == 0) return;
   char* nlpos = string + len - 1;
   if (*nlpos == delim) *nlpos = '\0';
}

/* USE LYUTIL ASTRE INPUT
// Run cpp against the lines of the file.
void cpplines (FILE* pipe, char* filename, FILE* debug_file) {
   	int linenr = 1;
   	char inputname[LINESIZE];
   	strcpy (inputname, filename);
   	for (;;) {
    	char buffer[LINESIZE];
        char* fgets_rc = fgets (buffer, LINESIZE, pipe);
        if (fgets_rc == NULL) break;
        chomp (buffer, '\n');
        fprintf (debug_file, "%s:line %d: [%s]\n", filename, linenr, buffer);
        int sscanf_rc = sscanf (buffer, "# %d \"%[^\"]\"",
                              &linenr, filename);
        if (sscanf_rc == 2) {
            fprintf (debug_file, "DIRECTIVE: line %d file \"%s\"\n", linenr, filename);
            continue;
      	}
      	char* savepos = NULL;
      	char* bufptr = buffer;
      	for (int tokenct = 1;; ++tokenct) {
        	char* token = strtok_r (bufptr, " \t\n", &savepos);
        	bufptr = NULL;
        if (token == NULL) break;
        	fprintf (debug_file, "token %d.%d: [%s]\n",
            	    linenr, tokenct, token);
		intern_stringset(token);
     	}
      ++linenr;
   	}	
}
*/

// Open a pipe from the C preprocessor.
// Exit failure if can't.
// Assignes opened pipe to FILE* yyin.
void yyin_cpp_popen (const char* filename) {
   yyin_cpp_command = cpp_name;
   yyin_cpp_command += " ";
   yyin_cpp_command += filename;
   yyin = popen (yyin_cpp_command.c_str(), "r");
   if (yyin == NULL) {
      syserrprintf (yyin_cpp_command.c_str());
      exit (get_exitstatus());
   }
}

void yyin_cpp_pclose (void) {
   int pclose_rc = pclose (yyin);
   eprint_status (yyin_cpp_command.c_str(), pclose_rc);
   if (pclose_rc != 0) set_exitstatus (EXIT_FAILURE);
}


int main (int argc, char* argv[]){
// 	flag variables
	bool yylex_flag;
	int  yy_flex_debug;
	bool yyparse_flag;
	bool set_debugflags_flag;
	string debugflags;
	bool cpp_argument_flag;
	bool error_flag = false;
	string cpp_argument;

//	Get time for time stamping the error file
	time_t time_;
	time(&time_);
	string timestamp = ctime(&time_);
	FILE* debug_file = fopen("debug_file", "w");
	FILE* error_file = freopen("error_file", "a", stderr);
	fprintf(stderr, "----------------------------\n");
	fprintf(stderr, "| %s |\n", str_to_char(timestamp.substr(0,timestamp.length()-1)));
	fprintf(stderr, "----------------------------\n");

	char option;

	string in_program_file;
	string program_name;
	string program_extension;
	string correct_extension = "oc";
//	Check if an input program is specified
	if(	argc <= 1) {
		printf("No input program to compile\n");
		fprintf(stderr, "No input program to compile\n\n");
		return 1;
	}
	else {
//		Parse and store the input file name
		program_name = argv[ argc-1 ];
		in_program_file = program_name;
//		Check the input file extension
		program_extension = Right(program_name, '.');
		if(program_extension.compare(correct_extension)) {
			printf("Invalid input program extension: %s\n", str_to_char(program_extension));
			fprintf(stderr, "Invalid input program extension: %s\n\n", str_to_char(program_extension));
			return 1;
		}
//		Remove the file extension from the program name
		program_name = Right(program_name, '\\');
		program_name = Left(program_name, '.');
	}
	while( (option = getopt(argc, argv, "@:D:ly") ) != -1 ) {
		switch(option) {
			case 'l' :
				yylex_flag = true;
				yy_flex_debug = 1; 
				break;
			case 'y' :
				yyparse_flag = true;
				break;
			case 'D' :
				cpp_argument_flag = true;
				cpp_argument = optarg;
				break;
			case '@' :
				set_debugflags_flag = true;
				debugflags = optarg;
				break;
			case '?' :
				if (optopt == 'D' || optopt == '@') {
					fprintf(stderr, "Option -%c requires an argument.\n\n", optopt);
				}
				else {
					fprintf(stderr, "Unknown optiont character '\\x%x'.\n\n", optopt);
				}
				return 1;
			default :
				abort();
		}
	}
   //string command = CPP + " " + in_program_file;
   //fprintf (debug_file, "command=\"%s\"\n", command.c_str());
   //FILE *pipe = popen (command.c_str(), "r");
   yyin_cpp_popen (str_to_char(in_program_file));
   /*
   if (pipe == NULL) {
     syserrprintf (command.c_str());
   }else {
     cpplines (pipe, str_to_char(in_program_file), debug_file);
     int pclose_rc = pclose (pipe);
     eprint_status (command.c_str(), pclose_rc);
   }
   */
   int parsecode = 0;
   parsecode = yyparse();

// Declare and open output files
   FILE *output_file_tokens = fopen (str_to_char(program_name + ".tok"), "w");
   FILE *output_file_stringset = fopen (str_to_char(program_name + ".str"), "w");
// Write to output files 
   dump_stringset (output_file_stringset);
   cout << "199" << endl;
   dump_astree (output_file_tokens, yyparse_astree);	
   cout << "201" << endl;
// Close output files
   fclose (output_file_stringset);
   fclose (output_file_tokens);
   fclose (debug_file);
   if (!error_flag){
      fprintf (stderr, "No errors.\n");
   }
   fprintf (stderr, "\n");
   fclose (error_file);
	
   /////free_ast (yyparse_astree);
   cout << "212" << endl;
   yyin_cpp_pclose();
   yylex_destroy();
   return 0;
}
