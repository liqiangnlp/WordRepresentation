/*
 * $Id:
 * 0005
 *
 * $File:
 * dispatcher.h
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
 * 2014-08-26,13:48
 */

#ifndef WORD_REPRESENTATION_DISPATCHER_H_
#define WORD_REPRESENTATION_DISPATCHER_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include "basic_method.h"
#include "word2vector.h"
#include "distance.h"
#include "accuracy.h"
#include "analogy.h"
#include "word2phrase.h"
#include "wrrbm_train.h"

using namespace std;
using namespace word_representation_basic_method;
using namespace word_representation_word2vector;
using namespace word_representation_distance;
using namespace word_representation_accuracy;
using namespace word_representation_analogy;
using namespace word_representation_word2phrase;
using namespace word_representation_wrrbm_train;

namespace word_representation_dispatcher {

/*
 * $Class: Dispatcher
 * $Function: A Dispatcher is a class that used to identify different functions.
 * $Date: 2013-05-07
 */
class Dispatcher {
 public:
  Dispatcher() {};
  ~Dispatcher() {};

 public:
  bool ResolveParameters(int argc, char * argv[]);

 private:
  bool SelectFunction(string &function_icon, map< string, string > &parameters);

 private:
  bool ReadConfigFile(map< string, string > &param);

 private:
  void AccessWord2VectorFunction(map< string, string > &parameters);
  void AccessWrrbmTrainFunction(map< string, string > &parameters);
  void AccessDistanceFunction(map< string, string > &parameters);
  void AccessAccuracyFunction(map< string, string > &parameters);
  void AccessAnalogyFunction(map< string, string > &parameters);
  void AccessWord2PhraseFunction(map< string, string > &parameters);

};

}

#endif




