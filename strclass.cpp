// strclass.cc

#include "strclass.h"
#include <string.h>

String::String ()
{
	string = new char[1]; string[0] = '\0'; MaxLength = 0;
}

String::String (const String& str) //copy constructor
{
	if (str.MaxLength == 0) {
		string = new char[1]; string[0] = '\0'; MaxLength = 0;
	}
	else {
		string = strdup(str.string);
		MaxLength = strlen(string);
	}
}

String::String (const char * str) // create from C string
{
	string = strdup (str);
	MaxLength = strlen (string);
}

String::~String ()
{
	if (string != 0) delete string;
	MaxLength = 0;
	string = 0;
}

String::operator char * ()
{
	return strdup(string);
}


String & String::operator = (const String & str)
// assignment
{
	if (strlen (str.string) >= MaxLength)
	{
		delete string;
		string = strdup(str.string);
		MaxLength = strlen(string);
	}
	strcpy (string, str.string);
	return *this;
}

String::operator char* () {
	return this->string;
}

int String::operator < (const String &str) const
// less than, lexicographic
{	return strcmp(string, str.string) < 0;}

int String::operator <= (const String & str) const
{	return strcmp(string, str.string) <= 0;}

int String::operator == (const String & str) const
{	return strcmp(string, str.string) == 0;}

char * String::str () const // return a copy of the string
{	return strdup(string);}

const int String::getMaxLength() {
	return this->MaxLength;
}