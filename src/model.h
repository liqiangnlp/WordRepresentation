/*
 * $Id:
 * 0015
 *
 * $File:
 * model.h
 *
 * $Proj:
 * WordRepresentation
 *
 * $Func:
 * word2vector model
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
 * 2014-09-01, 10:40
 */

#ifndef WORD_REPRESENTATION_MODEL_H_
#define WORD_REPRESENTATION_MODEL_H_

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <cmath>
#include "basic_method.h"

using namespace std;
using namespace word_representation_basic_method;

namespace word_representation_model {

class Model : public BasicMethod {
 public:
  long long words_count_;
  long long feature_size_;

 public:
  string vocab_file_;
  string binary_file_;

 public:
  string model_file_;

 public:
  bool binary_;

 public:
  vector<string> vocab_;

 public:
  vector<float> model_;

 public:
  Model() {
    words_count_ = 0;
    feature_size_ = 0;

    vocab_file_ = "";
    binary_file_ = "";
    model_file_ = "";

    binary_ = true;
  }
  ~Model() {}

 public:
  bool Init(map<string, string> &parameters);

 private:
  bool ReadWord2VectorModel();

 private:
  bool CheckParamsInConfig(map<string, string> &parameters);
  bool CheckEachParamInConfig(map<string, string> &parameters, string &parameter_key, string &default_value);

 private:
  bool CheckFilesInConfig(map<string, string> &parameters);
  bool CheckEachFileInConfig(map<string, string> &parameters, string &file_key);
};

}

#endif

