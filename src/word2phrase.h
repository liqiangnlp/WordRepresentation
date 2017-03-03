/*
* $Id:
* 0021
*
* $File:
* word2phrase.h
*
* $Proj:
* WordRepresentation
*
* $Func:
* word 2 phrase
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
* 2014-09-02, 17:39
*/

#ifndef WORD_REPRESENTATION_WORD2PHRASE_H_
#define WORD_REPRESENTATION_WORD2PHRASE_H_

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include "basic_method.h"
#include "word2vector.h"

using namespace std;
using namespace word_representation_basic_method;
using namespace word_representation_word2vector;

namespace word_representation_word2phrase {

class Word2PhraseConfig {
 public:
  int vocab_hash_size_;
  int vocab_max_size_;
  int vocab_size_;
  int max_string_;
  long long train_words_;
  int min_count_;

 public:
  string train_file_;
  string output_file_;
  string save_vocab_file_;

 public:
  float threshold_;

 public:
  Word2PhraseConfig() {
//  vocab_hash_size_ = 500000000;
    vocab_hash_size_ = 5000000;
    vocab_max_size_ = 10000;
    vocab_size_ = 0;
    max_string_ = 60;
    train_words_ = 0;
    min_count_ = 5;
    threshold_ = 100;
    train_file_ = "";
    output_file_ = "";
    save_vocab_file_ = "";
  }
  ~Word2PhraseConfig() {}

 public:
  bool Init(map<string, string> &parameters);

 private:
  bool CheckParamsInConfig(map<string, string> &parameters);
  bool CheckEachParamInConfig(map<string, string> &parameters, string &parameter_key, string &default_value);

 private:
  bool CheckFilesInConfig(map<string, string> &parameters);
  bool CheckEachFileInConfig(map<string, string> &parameters, string &file_key);
};



class Word2Phrase : public BasicMethod {

 public:
  vector<VocabWord> vocab_;

 public:
  vector<int> vocab_hash_;

 public:
  Word2PhraseConfig config_;

 public:
  Word2Phrase() {}
  ~Word2Phrase() {}

 public:
  bool ConvertWord2Phrase(map<string, string> &parameters);


 private:
  bool LearnVocabFromTrainFile();

 private:
  bool SaveVocab();

 private:
  size_t AddWordToVocab(string &word);

 private:
  size_t GetWordHash(string &word);
  int SearchVocab(string &word);
  bool ReduceVocab();
  bool SortVocab();

};

}

#endif

