/*
 * $Id:
 * 0025
 *
 * $File:
 * wrrbm_train.h
 *
 * $Proj:
 * WordRepresentation
 *
 * $Func:
 * header file of wrrbm_train.h
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

#ifndef WORD_REPRESENTATION_WRRBM_TRAIN_H_
#define WORD_REPRESENTATION_WRRBM_TRAIN_H_

//#define _CPP11

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
#include <list>
#include <numeric>
#include <cstdio>
#include "debug.h"
#include "basic_method.h"

#ifdef _CPP11
#include <thread>
#include <mutex>
#else
#include "multi_threads.h"
using namespace word_representation_multi_threads;
#endif

#define MAX_STRING 100

using namespace std;
using namespace word_representation_basic_method;
using namespace word_representation_debug;


namespace word_representation_wrrbm_train {


class VocabWord {
 public:
  long long count_;

 public:
  vector<long long> v_point_;

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


//////////////////////////////////////////////////////////////////////////////////////////////////////////
class Configuration {
 public:
  int epoches_;
  int hidden_;

 public:
  int embedding_size_;
  int batch_size_;

 public:
  int left_;
  int right_;

 public:
  int burn_in_;

 public:
  int cutoff_;

 public:
  int save_frequency_;

 public:
  int block_size_;

 public:
  double pretrain_rate_;

 public:
  double bias_rate_;

 public:
  double init_momentum_;
  double final_momentum_;

 public:
  double l1_;
  double l2_;

public:
  int vocab_hash_size_;
  int vocab_max_size_;
  int vocab_size_;
  int remove_vocab_number_;
  long long train_words_;

 public:
  int min_count_;       // Words occuring less than min_count_ times will be discarded from the vocab
  int min_reduce_;

 public:
  string train_file_;
  long long train_file_size_;

 public:
  string output_file_;
  string log_file_;

 public:
  string save_vocab_file_;

 public:
  string prefix_;
  string dbn_sub_name_;
  string temp_data_prefix_;

 public:
  string temp_directory_;
  string log_directory_;
  string model_direcotory_;

 public:
  string rbm_path_;       // for re-training an existing model on a different corpus

 public:
  vector<int> v_hidden_sizes_;

 public:
  int threads_number_;

 public:
  bool debug_;

 public:
  bool binary_format_;
  bool text_format_;

 public:
  bool display_parameters_;

 public:
  Configuration() {
    epoches_ = 20;
    hidden_ = 300;
    embedding_size_ = 50;
    batch_size_ = 20;

    left_= 2;
    right_ = 1;

    burn_in_ = 80;

    cutoff_ = 2;

    save_frequency_ = 30;
    block_size_ = 100000;
    
    pretrain_rate_ = 0.1;
    bias_rate_ = 0.1;
    init_momentum_ = 0.5;
    final_momentum_ = 0.9;
    l1_ = 0;
    l2_ = 0;

    vocab_hash_size_ = 30000000;     // Maximum 30M * 0.7 = 21M words in the vocabulary
//  vocab_hash_size_ = 300000;     // Maximum 30M * 0.7 = 21M words in the vocabulary
    vocab_max_size_ = 1000000;          // Not in configuration file
    vocab_size_ = 0;
    remove_vocab_number_ = 0;
    train_words_ = 0;

    min_count_ = 2;
    min_reduce_ = 1;
    
    threads_number_ = 1;

    debug_ = false;
    binary_format_ = true;
    text_format_ = true;
    display_parameters_ = true;

    train_file_ = "";
    train_file_size_ = 0;

    output_file_ = "";
    log_file_ = "";

    save_vocab_file_ = "";

    prefix_ = "";
    dbn_sub_name_ = "";
    temp_data_prefix_ = "";

    temp_directory_ = "";
    log_directory_ = "";
    model_direcotory_ = "";

    rbm_path_ = "";       // for re-training an existing model on a different corpus
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


//////////////////////////////////////////////////////////////////////////////////////////////////////////
class RandomGenerator {
 public:
  int outcome_;
  vector<double> v_binomial_distribution_;
  vector<int> v_alias_of_each_random_;
  vector<double> v_old_multinomial_;

 public:
  RandomGenerator() {
    outcome_ = -1;
  };
  ~RandomGenerator() {};

 public:
  bool Init(vector<double> &v_multinomial_distribution);
 
 public:
  double GetProbability(int &id);

 public:
  bool SaveGenerator(string &file_path, Configuration &config);

 private:
  bool SaveGeneratorBinary(const char *file_path);
  bool SaveGeneratorText(const char *file_path);

 public:
   int Sample();
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////
struct MemoryBlock{
  char *data_;
  size_t block_size_;
  size_t used_size_;
};

class MemoryPool{
 public:
  const static size_t BLOCK_SIZE = 40960;
  const static size_t MAX_POOL_SIZE = 1024 * 1024 * 64;
 
 public:
   list<MemoryBlock *> list_used_;
   list<MemoryBlock *> list_free_;
   list<MemoryBlock *>::iterator iterator_;
   list<MemoryBlock *>::iterator iterator_end_;
   MemoryBlock *p_current_memory_block_;
   size_t total_size_;

 public:
   MemoryPool() : p_current_memory_block_(NULL), total_size_(0) {}
   ~MemoryPool();

 public: 
   void * Allocate(size_t &size);
   void Recycle();
   void Free();
   void PrintSize();

 private:
   MemoryBlock * AllocateBlock(size_t &size);
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////
class Wrrbm : public BasicMethod {
 public:
  Configuration config_;

 public:
  vector<VocabWord> v_vocab_;
  vector<int> v_vocab_hash_;

 public:
  vector<double> v_vocab_distribution_;  // multinomial distribution of the vocab

 public:
  RandomGenerator random_generator_;

 public:
  int ngram_;

 public:
  double *p_hidden_bias_;
  double *p_visible_bias_;

 public:
  double *p_projection_layer_;          // n * d projection layer

 public:
  vector<double *> v_weights_matrix_;    // H * D matrix

 public:
  MemoryPool memory_pool_;

 public:
  Wrrbm() {};
  ~Wrrbm() {};

 public:
  bool Init(map<string, string> &parameters);
  
 private:
  bool SaveVocab();

 private:
  int ReadWordIndex(FILE *fin);
  void ReadWord(char *word, FILE *fin);

 private:
  bool LearnVocabFromTrainFile();

 private:
   bool AddReservedWordToVocab();

 private:
  size_t AddWordToVocab(string &word);

 public:
  int SearchVocab(string &word);
 
 private:
  size_t GetWordHash(string &word);
  bool ReduceVocab();
//  bool SortVocab();
  bool FilterVocab();

 private:
  bool ComputeMultinomialDistribution();

 public:
  void ComputeHiddenGivenVisible(vector<int> &v_samples_of_visible, vector<double> &v_samples_of_hidden, vector<double> &v_prob_of_hidden);
  void ComputeVisibleGivenHidden(vector<double> &v_samples_of_hidden, vector<int> &v_samples_of_visible_last, vector<int> &v_samples_of_visible_new, \
                                 vector<double> &v_prob_of_visible_new, vector<bool> *p_samp_of_visible_last_flag);

 private:
  double ComputeDotProduct(double *p_vector_1, int length_1, double *p_vector_2, int length_2);

 private:
  double ComputeActivate(int word_id, int position, vector<double> &v_samples_of_hidden);

 public:
  bool SaveModel(string &file_path);

 private:
  bool SaveModelBinary(const char *model_path);
  bool SaveModelText(const char *model_path);

 public:
  void DisplayParameters(FILE *fp);

 private:
  inline double Sigmoid(double x);
  inline double Uniform(double min, double max);
  inline void StopNan(double x);

 public:
  void CheckNan();

 private:
  bool InitRbmAndTrainer();
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////
class WrrbmTrainer{
 public:
  Wrrbm *p_wrrbm_;

 public:
  double *p_hidden_bias_;
  double *p_hidden_bias_inc_;

  double *p_visible_bias_;
  double *p_visible_bias_inc_;

 public:
  double *p_projection_layer_;
  double *p_projection_layer_inc_;

 public:
  vector<bool> v_projection_update_flag_;   // projection_update_flag_[i] == true: the i-th row of projection_layer has been updated

 public:
  vector<double *> v_weights_matrix_;        // H * D matrix
  vector<double *> v_weights_matrix_inc_;

 public:
  time_t start_time_;

#ifdef _CPP11
 public:
  mutex mutex_bias_;
  mutex mutex_projection_layer_;
  mutex mutex_weights_matrix_;
  mutex mutex_wrrbm_;
#else
  Mutex mutex_bias_;
  Mutex mutex_projection_layer_;
  Mutex mutex_weights_matrix_;
  Mutex mutex_wrrbm_;
#endif

 public:
  WrrbmTrainer() {};
  ~WrrbmTrainer();

 public:
  bool TrainModel(Wrrbm *p_wrrbm);

 private:
  bool Init(Wrrbm *p_wrrbm);

 private:
  bool ReadData(FILE *fin, vector< vector<int> > &v_v_read_data);

 private:
  pair<double, double> MiniBatchUpdateMultiThreads(vector< vector<int> > &v_v_read_data, double &momentum);

 public:
  void MiniBatchUpdateThread(vector< vector<int> >::iterator begin, vector< vector<int> >::iterator end, double *p_error, double *p_hit, int thread_id);

 private:
  void UpdateParameter(int batch_size, double momentum);

 private:
   vector<char *> Split(char *p_buf, const char *p_delemiter);
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _CPP11
class WrrbmTrainingThread : public MultiThreads {
 public:
  WrrbmTrainer * p_wrrbm_trainer_;

 public:
  vector< vector<int> >::iterator begin_;
  vector< vector<int> >::iterator end_;
  double *p_error_;
  double *p_hit_;

 public:
  void *TrainModelThread();

 private:
  static void *Wrapper(void *ptr) {
    WrrbmTrainingThread *this_ptr = (WrrbmTrainingThread *)ptr;
    this_ptr->TrainModelThread();
    return 0;
  }

 public:
  void Start();
};
#endif

}



#endif

