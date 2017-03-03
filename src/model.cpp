/*
* $Id:
* 0016
*
* $File:
* model.cpp
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
* 2014-09-01, 18:51
*/

#include "model.h"

namespace word_representation_model {


/*
 * $Name: Init
 * $Function: Init
 * $Date: 2014-08-30
 */
bool Model::Init(map<string,string> &parameters) {
  CheckParamsInConfig(parameters);
  CheckFilesInConfig(parameters);
  ReadWord2VectorModel();
  return true;
}


/*
 * $Name: ReadWord2VectorModel
 * $Function: 
 * $Date: 2014-08-30
 */
bool Model::ReadWord2VectorModel() {
  if (binary_) {
    ifstream in_vocab(vocab_file_.c_str());
    if (!in_vocab) {
      cerr<<"Error: Model vocab'"<<vocab_file_<<"' not found.\n"<<flush;
      exit(1);
    }

    ifstream in_binary(binary_file_.c_str(), ios::binary);
    if (!in_binary) {
      cerr<<"Error: Model binary'"<<binary_file_<<"' not found.\n"<<flush;
      exit(1);
    }

    string tmp_string;
    getline(in_vocab, tmp_string);
    ClearIllegalChar(tmp_string);
    RmEndSpace(tmp_string);
    RmStartSpace(tmp_string);
    vector<string> tmp_vector;
    Split(tmp_string, ' ', tmp_vector);
    if (tmp_vector.size() != 2) {
      cerr<<"Error: Model vocab'"<<vocab_file_<<"' format error.\n"<<flush;
      exit(1);
    }
    words_count_ = atoi(tmp_vector.at(0).c_str());
    feature_size_ = atoi(tmp_vector.at(1).c_str());
    cerr<<"words_count="<<words_count_<<"\n"
        <<"feature_size="<<feature_size_<<"\n"<<flush;

    vocab_.resize(words_count_);
    model_.resize(words_count_ * feature_size_, 0);

    string word;
    size_t word_number = 0;
    cerr<<"Read vocab file...\n"<<flush;
    while (getline(in_vocab, word)) {
      ClearIllegalChar(word);
      RmEndSpace(word);
      RmStartSpace(word);
      vocab_.at(word_number) = word;

      for (long long i = 0; i < feature_size_; ++i) {
        in_binary.read(reinterpret_cast<char *>(&model_.at(word_number * feature_size_ + i)), sizeof(float));
      }
      ++word_number;
      if (word_number % 10000 == 0) {
        cerr<<"\r  Processed "<<word_number<<" lines."<<flush;
      }
    }
    cerr<<"\r  Processed "<<word_number<<" lines.\n"<<flush;

    if (word_number != words_count_) {
      cerr<<"Error: Model vocab'"<<vocab_file_<<"' format error.\n"<<flush;
      exit(1);
    }
    in_vocab.close();
    in_binary.close();
  } else {
    ifstream in_model(model_file_.c_str());
    if (!in_model) {
      cerr<<"Error: Model '"<<model_file_<<"' not found.\n"<<flush;
      exit(1);
    }

    string tmp_string;
    getline(in_model, tmp_string);
    ClearIllegalChar(tmp_string);
    RmEndSpace(tmp_string);
    RmStartSpace(tmp_string);
    vector<string> tmp_vector;
    Split(tmp_string, ' ', tmp_vector);
    if (tmp_vector.size() != 2) {
      cerr<<"Error: Model '"<<vocab_file_<<"' format error.\n"<<flush;
      exit(1);
    }
    words_count_ = atoi(tmp_vector.at(0).c_str());
    feature_size_ = atoi(tmp_vector.at(1).c_str());
    cerr<<"words_count="<<words_count_<<"\n"
        <<"feature_size="<<feature_size_<<"\n"<<flush;

    vocab_.resize(words_count_);
    model_.resize(words_count_ * feature_size_, 0);

    string word_and_feature;
    size_t word_number = 0;
    cerr<<"Read vocab file...\n"<<flush;
    while (getline(in_model, word_and_feature)) {
      ClearIllegalChar(word_and_feature);
      RmEndSpace(word_and_feature);
      RmStartSpace(word_and_feature);
      tmp_vector.clear();
      Split(word_and_feature, ' ',tmp_vector);
      vocab_.at(word_number) = tmp_vector.at(0);

      for (long long i = 0; i < feature_size_; ++i) {
        model_.at(word_number * feature_size_ + i) = (float)atof(tmp_vector.at(i + 1).c_str());
      }
      ++word_number;
      if (word_number % 10000 == 0) {
        cerr<<"\r  Processed "<<word_number<<" lines."<<flush;
      }
    }
    cerr<<"\r  Processed "<<word_number<<" lines.\n"<<flush;

    if (word_number != words_count_) {
      cerr<<"Error: Model vocab'"<<vocab_file_<<"' format error.\n"<<flush;
      exit(1);
    }
  }

/*
  string out_test_file = model_file_ + ".output.test";
  cerr<<"output_model="<<out_test_file<<"\n"<<flush;
  ofstream out_test( out_test_file.c_str() );
  out_test<<words_count_<<" "<<feature_size_<<"\n";
  for (int i = 0; i < words_count_; ++i) {
    out_test<<vocab_.at(i);
    for (int j = 0; j < feature_size_; ++j) {
      out_test<<" "<<model_.at(i * feature_size_ + j);
    }
    out_test<<"\n";
  }
  out_test.close();
*/

  return true;
}


/*
 * $Name: CheckParamsInConfig
 * $Function: Check the parameters in configuration file.
 * $Date: 2014-07-09
 */
bool Model::CheckParamsInConfig(map<string, string> &parameters) {
  string parameter_key;
  string default_value;
//  parameter_key = "";
//  default_value = "1";
//  CheckEachParamInConfig(parameters, parameter_key, default_value);
//  threads_number_ = atoi(parameters[ parameter_key ].c_str());

  parameter_key = "binary";
  default_value = "0";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  binary_ = (parameters[parameter_key] == "0" ? false : true);
  return true;
}


/*
 * $Name: CheckParamsInConfig
 * $Function: Check the parameters in configuration file.
 * $Date: 2014-07-09
 */
bool Model::CheckEachParamInConfig(map<string, string> &parameters, string &parameter_key, string &default_value) {
  if (parameters.find(parameter_key) == parameters.end()) {
    parameters[ parameter_key ] = default_value;
  }
  return true;
}


/*
 * $Name: CheckFilesInConfig
 * $Function: Check the files in configuration file.
 * $Date: 2014-07-09
 */
bool Model::CheckFilesInConfig(map<string, string> &parameters) {
  string file_key;
  if (binary_) {
    file_key = "model-vocab";
    CheckEachFileInConfig(parameters, file_key);
    vocab_file_ = parameters[file_key];

    file_key = "model-binary";
    CheckEachFileInConfig(parameters, file_key);
    binary_file_ = parameters[file_key];
  } else {
    file_key = "model";
    CheckEachFileInConfig(parameters, file_key);
    model_file_ = parameters[file_key];
  }
  return true;
}


/*
 * $Name: CheckEachFileInConfig
 * $Function: Check each file in configuration file.
 * $Date: 2014-07-09
 */
bool Model::CheckEachFileInConfig(map<string, string> &parameters, string &file_key) {
  if (parameters.find(file_key) != parameters.end()) {
    ifstream in_file(parameters[file_key].c_str());
    if (!in_file) {
      cerr<<"ERROR: Please check the path of '"<<file_key<<"' in configuration file.\n"<<flush;
      exit( 1 );
    }
    in_file.clear();
    in_file.close();
  } else {
    cerr<<"ERROR: Please add parameter '"<<file_key<<"' in configuration file.\n"<<flush;
    exit( 1 );
  }
  return true;
}

}


