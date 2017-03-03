/*
 * $Id:
 * 0017
 *
 * $File:
 * accuracy.h
 *
 * $Proj:
 * WordRepresentation
 *
 * $Func:
 * compute accuracy
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
 * 2014-09-01, 10:55
 */

#ifndef WORD_REPRESENTATION_ACCURACY_H_
#define WORD_REPRESENTATION_ACCURACY_H_

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include "model.h"
#include "basic_method.h"

using namespace std;
using namespace word_representation_model;
using namespace word_representation_basic_method;

namespace word_representation_accuracy {

class Accuracy : public BasicMethod {
 public:
  Model model_;

 public:
  string question_file_;

 public:
  long long closest_word_number;

 public:
  long long threadhold_;

 public:
  Accuracy() {
    closest_word_number = 1;
    threadhold_ = 0;
  }
  ~Accuracy() {}

 public:
  bool ComputeAccuracy(map<string, string> &parameters);

 private:
  bool Init(map<string, string> &parameters);

 private:
  bool CheckParamsInConfig(map<string, string> &parameters);
  bool CheckEachParamInConfig(map<string, string> &parameters, string &parameter_key, string &default_value);

 private:
  bool CheckFilesInConfig(map<string, string> &parameters);
  bool CheckEachFileInConfig(map<string, string> &parameters, string &file_key);
};

}

#endif

