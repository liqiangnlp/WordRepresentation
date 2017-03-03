/*
 * $Id:
 * 0009
 *
 * $File:
 * word2vector.h
 *
 * $Proj:
 * WordRepresentation
 *
 * $Func:
 * header file of word2vector
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
 * 2014-07-08, 21:11
 */

#ifndef WORD_REPRESENTATION_WORD2VECTOR_H_
#define WORD_REPRESENTATION_WORD2VECTOR_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include "multi_threads.h"
#include "debug.h"
#include "basic_method.h"

#define MAX_STRING 100

using namespace std;
using namespace word_representation_multi_threads;
using namespace word_representation_debug;
using namespace word_representation_basic_method;


namespace word_representation_word2vector {


class VocabWord {
 public:
  long long count_;

 public:
  vector<long long> point_;

 public:
  string word_;
  string code_;
  long long codelen_;

 public:
  VocabWord() {
    count_ = 0;
    word_ = "";
    code_ = "";
    codelen_ = 0;
  }

 public:
  bool operator < (const VocabWord &vocab_word)const {
    return count_ < vocab_word.count_;
 }
};


bool VocabCompare(const VocabWord &a, const VocabWord &b);


class Configuration {
 public:
  unsigned int max_string_;
  int exp_table_size_;
  int max_exp_;
  int max_sentence_length_;
  int max_code_length_;

 public:
  int table_size_;

 public:
  long long layer1_size_;
  int vocab_max_size_;
  int vocab_size_;
  long long train_words_;
  int min_count_;       // Words occuring less than min_count_ times will be discarded from the vocab
  int min_reduce_;

 public:
  long long word_count_actual_;

 public:
  bool hs_;
  bool binary_;

 public:
  int negative_;


 public:
  int window_;

 public:
  float sample_;
  float alpha_;
  float starting_alpha_;

 public:
  int vocab_hash_size_;

 public:
  int threads_number_;

 public:
  string train_file_;
  long long train_file_size_;

 public:
  string output_file_;
  string output_word_cluster_;

 public:
  string read_vocab_file_;
  string save_vocab_file_;

 public:
  int model_;                    // Use the continuous bag of words model or skip-gram model; default is '1' ('0' = cbow model, '1' = skip-gram model)
  int classes_;                  // '0' = save the word vectors, '1' = run k-means on the word vectors

 public:
  bool debug_;

 public:
  bool display_parameters_;

 public:
  clock_t start;

 public:
  Configuration() {
    max_string_ = 100;
    exp_table_size_ = 1000;
    max_exp_ = 6;
    max_sentence_length_ = 1000;
    max_code_length_ = 40;

    table_size_ = (int)1e8;

    layer1_size_ = 100;
    vocab_max_size_ = 1000000;          // Not in configuration file
    vocab_size_ = 0;                 // Not in configuration file
    train_words_ = 0;
    min_count_ = 5;
    min_reduce_ = 1;

    word_count_actual_ = 0;

    window_ = 5;
    sample_ = 0;
    alpha_ = 0.025f;
    starting_alpha_ = 0;

    vocab_hash_size_ = 30000000;     // Maximum 30M * 0.7 = 21M words in the vocabulary

    threads_number_ = 1;

    hs_ = true;
    negative_ = 0;
    binary_ = false;

    debug_ = false;
    display_parameters_ = true;

    read_vocab_file_ = "";
    save_vocab_file_ = "";

    train_file_ = "";
    train_file_size_ = 0;

    output_file_ = "";
    output_word_cluster_ = "";

    model_ = 1;
    classes_ = 0;
  }

 public:
  bool Init(map<string, string> &parameters);
 
 private:
  bool CheckParamsInConfig(map<string, string> &parameters);
  bool CheckEachParamInConfig(map<string, string> &parameters, string &parameter_key, string &default_value);

 private:
  bool CheckFilesInConfig(map<string, string> &parameters);
  bool CheckEachFileInConfig(map<string, string> &parameters, string &file_key);

};


class Word2Vector : public BasicMethod {
 public:
  vector<float> exp_table_;
  vector<int>   vocab_hash_;

 public:
  vector<float> syn0_;
  vector<float> syn1_;
  vector<float> syn1_negative_;

 public:
  vector<VocabWord> vocab_;

 public:
  vector<int> vocab_cluster_id_;

 public:
  vector<int> table_;

 public:
  Configuration config_;

 public:
  Word2Vector() {};
  ~Word2Vector() {};

 public:
  bool TrainModel(map<string, string> &parameters);

 public:
  void TrainCbowModelThread(int &id);
  void TrainSkipGramModelThread(int &id);

 private:
  bool PreComputeExpTable();

 private:
  bool ReadVocab();
  bool SaveVocab();

 private:
  int ReadWordIndex(FILE *fin);
  void ReadWord(char *word, FILE *fin);

 private:
  bool LearnVocabFromTrainFile();

 private:
  size_t AddWordToVocab(string &word);

 private:
  size_t GetWordHash(string &word);
  int SearchVocab(string &word);
  bool ReduceVocab();
  bool SortVocab();

 private:
  bool InitNet();

 private:
  bool CreateBinaryTree();

 private:
  bool InitUnigramTable();

 private:
  bool KMeansClustering();
  bool OutputKMeansClustering();

 private:
  bool OutputModel();
  bool OutputModelBinary();
};


class Word2VectorTrainingThread : public MultiThreads {
 public:
  Word2Vector * word2vector_;

 public:
  void *TrainModelThread();

 private:
  static void *Wrapper(void *ptr) {
    Word2VectorTrainingThread *this_ptr = (Word2VectorTrainingThread *)ptr;
    this_ptr->TrainModelThread();
    return 0;
  }

 public:
  void Start();
};
}



#endif

