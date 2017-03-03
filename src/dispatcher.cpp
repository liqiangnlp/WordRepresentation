/*
 * $Id:
 * 0006
 *
 * $File:
 * dispatcher.cpp
 *
 * $Proj:
 * WordRepresentation
 *
 * $Func:
 * dispatcher method
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
 * 2014-08-26,10:45
 */

#include "dispatcher.h"

namespace word_representation_dispatcher {

/*
 * $Name: ResolveParameters
 * $Function: Resolves parameters from the command line.
 * $Date: 2013-05-07
 */
bool Dispatcher::ResolveParameters(int argc, char * argv[]) {
  string function_icon( argv[ 1 ] );
  vector< string > argument;

  for(int i = 2; i != argc; ++i) {
    argument.push_back( argv[ i ] );
#ifdef WIN32
    string::size_type pos = 0;
    while( ( pos = argument.back().find( "/" ) ) != string::npos ) {
      argument.back().replace( pos, 1, "\\" );
    }
#endif
  }

  map< string, string > param;
  for(vector< string >::iterator iter = argument.begin(); iter != argument.end(); ++iter) {
    string temp1( *iter   );
    string temp2( *++iter );

    param.insert( make_pair( temp1, temp2 ) );
  }
  return SelectFunction(function_icon, param);
}


/*
 * $Name: SelectFunction
 * $Function: Selects function.
 * $Date: 2013-05-07
 */
bool Dispatcher::SelectFunction(string &function_icon, map< string, string > &parameters) {
  if (function_icon == "--WORD2VEC") { 
    AccessWord2VectorFunction(parameters);
  }else if (function_icon == "--WRRBM") {
    AccessWrrbmTrainFunction(parameters);
  } else if (function_icon == "--DISTANCE") {
    AccessDistanceFunction(parameters);
  } else if (function_icon == "--ACCURACY") {
    AccessAccuracyFunction(parameters);
  } else if (function_icon == "--ANALOGY") {
    AccessAnalogyFunction(parameters);
  } else if (function_icon == "--WORD2PHRASE") {
    AccessWord2PhraseFunction(parameters);
  }

  return true;
}


/*
 * $Name: ReadConfigFile
 * $Function: Reads configuration file.
 * $Date: 2013-05-07
 */
bool Dispatcher::ReadConfigFile(map< string, string > &param) {
  if (param.find( "-config" ) == param.end()) {
    cerr<<"ERROR: Please add \"-config\" in your command!\n"<<flush;
    exit( 1 );
  }

  ifstream inputConfigFile( param[ "-config" ].c_str() );
  if ( !inputConfigFile ) {
    cerr<<"ERROR: Config File does not exist, exit!\n"<<flush;
    exit( 1 );
  }

  string lineOfConfigFile;
  while (getline(inputConfigFile, lineOfConfigFile)) {
    BasicMethod bm;
    bm.ClearIllegalChar( lineOfConfigFile );
    bm.RmStartSpace    ( lineOfConfigFile );
    bm.RmEndSpace      ( lineOfConfigFile );

    if ( lineOfConfigFile == "" || *lineOfConfigFile.begin() == '#' ) {
      continue;
    } else if (lineOfConfigFile.find("param=\"") == lineOfConfigFile.npos || lineOfConfigFile.find("value=\"") == lineOfConfigFile.npos) {
      continue;
    } else {
      string::size_type pos = lineOfConfigFile.find( "param=\"" );
      pos += 7;
      string key;
      for ( ; lineOfConfigFile[ pos ] != '\"' && pos < lineOfConfigFile.length(); ++pos ) {
        key += lineOfConfigFile[ pos ];
      }
      if ( lineOfConfigFile[ pos ] != '\"' ) {
        continue;
      }

      pos = lineOfConfigFile.find( "value=\"" );
      pos += 7;
      string value;

      for ( ; lineOfConfigFile[ pos ] != '\"' && pos < lineOfConfigFile.length(); ++pos ) {
        value += lineOfConfigFile[ pos ];
      }

      if ( lineOfConfigFile[ pos ] != '\"' ) {
        continue;
      }

      if ( param.find( key ) == param.end() ) {
        param.insert( make_pair( key, value ) );
      } else {
        param[ key ] = value;
      }
    }
  }
  return true;
}

void Dispatcher::AccessWord2VectorFunction(map< string, string > &parameters){
  ReadConfigFile(parameters);
  
  Word2Vector word2vector;
  word2vector.TrainModel(parameters);
  return;
}

void Dispatcher::AccessWrrbmTrainFunction(map< string, string > &parameters){
  ReadConfigFile(parameters);

  Wrrbm wrrbm;
  wrrbm.Init(parameters);

  WrrbmTrainer wrrbm_trainer;
  wrrbm_trainer.TrainModel(&wrrbm);

  return;
}

void Dispatcher::AccessDistanceFunction(map< string, string > &parameters){
  cerr<<"AccessDistanceFunction"<<"\n"<<flush;
  ReadConfigFile(parameters);
  Distance distance;
  distance.ComputeDistance(parameters);
  return;
}

void Dispatcher::AccessAccuracyFunction(map< string, string > &parameters){
  cerr<<"AccessAccuracyFunction"<<"\n"<<flush;
  ReadConfigFile(parameters);
  Accuracy accuracy;
  accuracy.ComputeAccuracy(parameters);
  return;
}


void Dispatcher::AccessAnalogyFunction(map< string, string > &parameters){
  cerr<<"AccessAnalogyFunction"<<"\n"<<flush;
  ReadConfigFile(parameters);
  Analogy analogy;
  analogy.StartAnalogy(parameters);
  return;
}


void Dispatcher::AccessWord2PhraseFunction(map< string, string > &parameters){
  cerr<<"AccessWord2PhraseFunction"<<"\n"<<flush;
  ReadConfigFile(parameters);
  Word2Phrase word2phrase;
  word2phrase.ConvertWord2Phrase(parameters);
  return;
}


}

