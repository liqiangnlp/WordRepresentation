/*
 * $Id:
 * 0007
 *
 * $File:
 * basic_method.h
 *
 * $Proj:
 * WordRepresentation
 *
 * $Func:
 * basic method
 *
 * $Version:
 * 1.0.0
 *
 * $Created by:
 * Qiang Li 
 *
 * $Email
 * liqiangneu@gmail.com
 *
 * $Last Modified by:
 * 2014-07-08,16:56
 */


#ifndef WORD_REPRESENTATION_BASIC_METHOD_H_
#define WORD_REPRESENTATION_BASIC_METHOD_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <ctime>
using namespace std;


namespace word_representation_basic_method {

class SystemCommand {
 public:
  string sortFile;
  string del     ;

 public:
  SystemCommand( string &newSortFile, string &newDel ) : sortFile( newSortFile ), del( newDel ) {}
};


class BasicMethod {
 public:
  typedef string::size_type STRPOS;

 public:
  bool Split( const string &phraseTable, const char &splitchar, vector< string > &dest );

 public:
  bool SplitWithStr( const string &src, const string &separator, vector< string > &dest );

 public:
  bool DeleteFileList( vector< string > &fileList, SystemCommand &systemCommand );


 public:
  string Size_tToString( size_t &source );
  string IntToString( int &source );
  string ConvertCharToString( char &input_char );

 public:
  bool ClearIllegalChar( string &str );

 public:
  bool ToUpper( string &str );
  bool ToLower( string &str );

 public:
  bool RmEndSpace   ( string &str );
  bool RmStartSpace ( string &str );

 public:
  bool RemoveExtraSpace( string &input_string, string &output_string );
};

}

#endif

