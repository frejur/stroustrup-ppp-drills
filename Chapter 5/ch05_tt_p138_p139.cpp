#include "std_lib_facilities.h"

namespace ch05_tt_p138_p139
{
    int area(int length, int width);       // calculate area of a rectangle

    int main()
    {
        // Page 138
        /*int s1 = area(7;            // Error	C2143	syntax error: missing ')' before ';'
                                      // Error	C2660	'ch05_tt_p138::area': function does not take 1 arguments */

        /*int s2 = area(7)            // Error	C2660	'ch05_tt_p138::area': function does not take 1 arguments
                                      // Error	C2143	syntax error : missing ';' before 'return' */

        /*Int s3 = area(7);           // Error	C2065	'Int': undeclared identifier
                                      // Error	C2146	syntax error: missing ';' before identifier 's3'
                                      // Error	C2065	's3': undeclared identifier
                                      // Error	C2660	'ch05_tt_p138::area': function does not take 1 arguments */

        /* int s4 = area('7);         // Error	C2015	too many characters in constant
                                      // Error	C2146	syntax error: missing ')' before identifier 'missing'
                                      // Error	C2660	'ch05_tt_p138::area': function does not take 1 arguments
                                      // Error	C2146	syntax error: missing ';' before identifier 'missing'
                                      // Error	C2059	syntax error: ')'
                                      // Error	C2065	'missing': undeclared identifier
                                      // Error	C2143	syntax error: missing ';' before 'return' */

        // Page 139

        //int x0 = arena(7);          // Error	C3861	'arena': identifier not found

        //int x1 = area(7);           // Error	C2660	'ch05_tt_p138_p139::area': function does not take 1 arguments

        /*x2 = area("seven", 2);      // Error	C2065	'x2': undeclared identifier
                                      // Error	C2664	'int ch05_tt_p138_p139::area(int,int)': cannot convert argument 1 from 'const char [6]' to 'int'*/

        //int x4 = area(23, 2323, 1); // Error	C2660	'ch05_tt_p138_p139::area': function does not take 3 arguments

        //string s2 = area(21, 2);    // Error	C2440	'initializing': cannot convert from 'int' to 'std::basic_string<char,std::char_traits<char>,std::allocator<char>>'

        return 0;
    }
}