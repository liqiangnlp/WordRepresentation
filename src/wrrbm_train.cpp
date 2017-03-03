/*
 * $Id:
 * 0026
 *
 * $File:
 * word2vector.cpp
 *
 * $Proj:
 * WordRepresentation
 *
 * $Func:
 * Word Representation RBM
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

#include "wrrbm_train.h"

namespace word_representation_wrrbm_train {

/*
 * $Name: Init
 * $Function: Initialize the parameters in configuration file.
 * $Date: 2014-07-09
 */
bool Configuration::Init(map<string, string> &parameters) {
  CheckParamsInConfig(parameters);
  CheckFilesInConfig(parameters);
  return true;
}


/*
 * $Name: CheckParamsInConfig
 * $Function: Check the parameters in configuration file.
 * $Date: 2014-07-09
 */
bool Configuration::CheckParamsInConfig(map<string, string> &parameters) {
  string parameter_key = "epoches";
  string default_value = "20";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  epoches_ = atoi(parameters[parameter_key].c_str());

  parameter_key = "hidden";
  default_value = "300";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  hidden_ = atoi(parameters[parameter_key].c_str());

  parameter_key = "embedding-size";
  default_value = "50";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  embedding_size_ = atoi(parameters[parameter_key].c_str());

  parameter_key = "batch-size";
  default_value = "20";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  batch_size_ = atoi(parameters[parameter_key].c_str());

  parameter_key = "left";
  default_value = "2";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  left_ = atoi(parameters[parameter_key].c_str());

  parameter_key = "right";
  default_value = "1";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  right_ = atoi(parameters[parameter_key].c_str());

  parameter_key = "burn-in";
  default_value = "80";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  burn_in_ = atoi(parameters[parameter_key].c_str());

  parameter_key = "cutoff";
  default_value = "2";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  cutoff_ = atoi(parameters[parameter_key].c_str());

  parameter_key = "save-frequency";
  default_value = "30";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  save_frequency_ = atoi(parameters[parameter_key].c_str());

  parameter_key = "block-size";
  default_value = "100000";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  block_size_ = atoi(parameters[parameter_key].c_str());

  parameter_key = "pretrain-rate";
  default_value = "0.1";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  pretrain_rate_ = atof(parameters[parameter_key].c_str());

  parameter_key = "bias-rate";
  default_value = "0.1";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  bias_rate_ = atof(parameters[parameter_key].c_str());

  parameter_key = "init-momentum";
  default_value = "0.5";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  init_momentum_ = atof(parameters[parameter_key].c_str());

  parameter_key = "final-momentum";
  default_value = "0.9";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  final_momentum_ = atof(parameters[parameter_key].c_str());

  parameter_key = "l1";
  default_value = "0";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  l1_ = atof(parameters[parameter_key].c_str());

  parameter_key = "l2";
  default_value = "0";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  l2_ = atof(parameters[parameter_key].c_str());

  parameter_key = "min-count";
  default_value = "2";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  min_count_ = atoi(parameters[parameter_key].c_str());

  parameter_key = "debug";
  default_value = "0";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  debug_ = (parameters[parameter_key] == "0" ? false : true);

  parameter_key = "binary-format";
  default_value = "1";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  binary_format_ = (parameters[parameter_key] == "0" ? false : true);

  parameter_key = "text-format";
  default_value = "0";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  text_format_ = (parameters[parameter_key] == "0" ? false : true);

  parameter_key = "display-parameters";
  default_value = "1";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  display_parameters_ = (parameters[parameter_key] == "0" ? false : true);

  parameter_key = "threads-number";
  default_value = "1";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  threads_number_ = atoi(parameters[parameter_key].c_str());

  parameter_key = "output-file";
  default_value = "output-file.txt";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  output_file_ = parameters[parameter_key];

  parameter_key = "log-file";
  default_value = "log-file.txt";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  log_file_ = parameters[parameter_key];

  parameter_key = "save-vocab";
  default_value = "save-vocab.txt";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  save_vocab_file_ = parameters[parameter_key];

  if (display_parameters_) {
    fprintf(stderr, "Word Representation RBM, liqiangneu@gmail.com\n");
    fprintf(stderr, "Parameters\n");
    fprintf(stderr, "%+20s  %-10d\n", "epoches", epoches_);
    fprintf(stderr, "%+20s  %-10d\n", "hidden", hidden_);
    fprintf(stderr, "%+20s  %-10d\n", "embedding-size", embedding_size_);
    fprintf(stderr, "%+20s  %-10d\n", "batch-size", batch_size_);
    fprintf(stderr, "%+20s  %-10d\n", "left", left_);
    fprintf(stderr, "%+20s  %-10d\n", "right", right_);
    fprintf(stderr, "%+20s  %-10d\n", "burn-in", burn_in_);
    fprintf(stderr, "%+20s  %-10d\n", "cutoff", cutoff_);
    fprintf(stderr, "%+20s  %-10d\n", "save-frequency", save_frequency_);
    fprintf(stderr, "%+20s  %-10d\n", "block-size", block_size_);
    fprintf(stderr, "%+20s  %-10f\n", "pretrain-rate", pretrain_rate_);
    fprintf(stderr, "%+20s  %-10f\n", "bias-rate", bias_rate_);
    fprintf(stderr, "%+20s  %-10f\n", "init-momentum", init_momentum_);
    fprintf(stderr, "%+20s  %-10f\n", "final-momentum", final_momentum_);
    fprintf(stderr, "%+20s  %-10f\n", "l1", l1_);
    fprintf(stderr, "%+20s  %-10f\n", "l2", l2_);
    fprintf(stderr, "%+20s  %-10d\n", "min-count", min_count_);
    fprintf(stderr, "%+20s  %-10d\n", "threads-number", threads_number_);

    fprintf(stderr, "%+20s  %-10s\n", "binary-format", binary_format_ ? "true" : "false");
    fprintf(stderr, "%+20s  %-10s\n", "text-format", text_format_ ? "true" : "false");
    fprintf(stderr, "%+20s  %-10s\n", "display-parameters", display_parameters_ ? "true" : "false");
    fprintf(stderr, "%+20s  %-10s\n", "debug", debug_ ? "true" : "false");

    fprintf(stderr, "%+20s  %-10s\n", "output-file", output_file_.c_str());
    fprintf(stderr, "%+20s  %-10s\n", "log-file", log_file_.c_str());
    fprintf(stderr, "%+20s  %-10s\n", "save-vocab", save_vocab_file_.c_str());
  }
  return true;
}


/*
 * $Name: CheckParamsInConfig
 * $Function: Check the parameters in configuration file.
 * $Date: 2014-07-09
 */
bool Configuration::CheckEachParamInConfig(map<string, string> &parameters, string &parameter_key, string &default_value) {
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
bool Configuration::CheckFilesInConfig(map<string, string> &parameters) {
  string file_key = "train-file";
  CheckEachFileInConfig(parameters, file_key);
  train_file_ = parameters[file_key];
  if (display_parameters_) {
    fprintf(stderr, "%+20s  %-10s\n", "train-file", train_file_.c_str());
    fflush(stderr);
  }
  return true;
}


/*
 * $Name: CheckEachFileInConfig
 * $Function: Check each file in configuration file.
 * $Date: 2014-07-09
 */
bool Configuration::CheckEachFileInConfig(map<string, string> &parameters, string &file_key) {
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


//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * $Name: Init
 * $Function: Initializing random generator
 * $Date: 2014-09-24
 */
bool RandomGenerator::Init(vector<double> &v_multinomial_distribution) {
  if (v_multinomial_distribution.size() == 0) {
    fprintf(stderr, "Error: multinomial distribution with 0 outcomes\n");
    exit(1);
  }

  v_old_multinomial_.clear();
  v_old_multinomial_.insert(v_old_multinomial_.begin(), v_multinomial_distribution.begin(), v_multinomial_distribution.end());

  outcome_ = v_multinomial_distribution.size();
  
  vector<int> v_larger, v_smaller;
  v_binomial_distribution_.resize(outcome_, 0);
  v_alias_of_each_random_.resize(outcome_, -1);
  
  for (int i = 0; i < outcome_; ++i) {
    v_binomial_distribution_.at(i) = outcome_ * v_multinomial_distribution.at(i);
    if (v_binomial_distribution_.at(i) > 1.0) {
      v_larger.push_back(i);
    } else {
      v_smaller.push_back(i);
    }
  }

  while (v_smaller.size() > 0) {
    int larger_end = v_larger.back();
    int smaller_end = v_smaller.back();
    v_alias_of_each_random_.at(smaller_end) = larger_end;
    v_smaller.pop_back();

    v_binomial_distribution_.at(larger_end) -= 1 - v_binomial_distribution_.at(smaller_end);
    if (1.0 - v_binomial_distribution_.at(larger_end) > 1.0e-6) {
      v_larger.pop_back();
      v_smaller.push_back(larger_end);
    }

    if (v_smaller.size() == 0) {
      v_binomial_distribution_.at(larger_end) = 1.0;
    }
  }

  int undefine_number = 0;
  for (int i = 0; i < outcome_; ++i) {
    if (v_alias_of_each_random_.at(i) == -1) {
      ++undefine_number;
    }
  }

  if (undefine_number == 1) {
    return true;
  }
  else {
    return false;
  }
}


/*
 * $Name: GetProbability
 * $Function: Get probability
 * $Date: 2014-09-25
 */
double RandomGenerator::GetProbability(int &old_id) {
  if (old_id < 0 || old_id >= outcome_) {
    fprintf(stderr, "Error: id is out %d of range (0-%d)!\n", old_id, outcome_ - 1);
    exit(1);
  }
  return v_old_multinomial_.at(old_id);
}


/*
 * $Name: SaveGenerator
 * $Function: Save generator
 * $Date: 2014-09-29
 */
bool RandomGenerator::SaveGenerator(string &file_path, Configuration &config) {
  if (config.binary_format_) {
    string file_path_binary = file_path + ".binary";
    if (config.display_parameters_) {
      fprintf(stderr, "%+20s  %-10s\n\n", "save-gener-binary", file_path_binary.c_str());
      fflush(stderr);
    }
    SaveGeneratorBinary(file_path_binary.c_str());
  }
  if (config.text_format_) {
    string file_path_text = file_path + ".text";
    SaveGeneratorText(file_path_text.c_str());
  }
  return true;
}


/*
 * $Name: SaveGeneratorBinary
 * $Function: Save generator binary
 * $Date: 2014-09-29
 */
bool RandomGenerator::SaveGeneratorBinary(const char *file_path) {
  FILE *fout = fopen(file_path, "wb");
  if (fout == NULL) {
    fprintf(stderr, "Error: can not open %s file!\n", file_path);
    exit(1);
  }
  if (fwrite(&outcome_, sizeof(outcome_), 1, fout) != 1) {
    return false;
  }
  if (fwrite(&v_binomial_distribution_[0], sizeof(double), v_binomial_distribution_.size(), fout) != v_binomial_distribution_.size()) {
    return false;
  }
  if (fwrite(&v_alias_of_each_random_[0], sizeof(int), v_alias_of_each_random_.size(), fout) != v_alias_of_each_random_.size()) {
    return false;
  }
  if (fwrite(&v_old_multinomial_[0], sizeof(double), v_old_multinomial_.size(), fout) != v_old_multinomial_.size()) {
    return false;
  }
  fclose(fout);
  return true;
}


/*
 * $Name: SaveGeneratorBinary
 * $Function: Save generator binary
 * $Date: 2014-09-29
 */
bool RandomGenerator::SaveGeneratorText(const char *file_path) { 
  return true;
}


/*
 * $Name: Sample
 * $Function: Sample
 * $Date: 2014-09-26
 */
int RandomGenerator::Sample() {
  if (outcome_ == -1) {
    fprintf(stderr, "Error: using un-initialized generator!\n");
    fflush(stderr);
    exit(1);
  }

  double u = rand() / (RAND_MAX + 1.0) * (outcome_ - 1 - (-1)) + (-1) + 1.0e-10;
  int i = (int)ceil(u);
  double p = (double)i - u;
  int return_value = p < v_binomial_distribution_[i] ? i : v_alias_of_each_random_[i];
  if (return_value == -1) {
    fprintf(stderr, "u=%.10e i=%d p=%4e v_binomial_distribution_[%d]=%.10e v_alias_of_each_random[%d]=%d\n", u, i, p, i, v_binomial_distribution_[i], i, v_alias_of_each_random_[i]);
    fflush(stderr);
    fgetc(stdin);
  }
  return return_value;

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * $Name: ~MemoryPool
 * $Function: 
 * $Date: 2014-09-25
 */
MemoryPool::~MemoryPool(){
  Free();
}


/*
 * $Name: ~MemoryPool
 * $Function:
 * $Date: 2014-09-25
 */
void * MemoryPool::Allocate(size_t &size) {
  size = ((size + 3) / 4) * 4;
  if (p_current_memory_block_ == NULL || p_current_memory_block_->block_size_ <= size + p_current_memory_block_->used_size_){
    iterator_ = list_free_.begin();
    iterator_end_ = list_free_.end();
    for (; iterator_ != iterator_end_; ++iterator_) {
      if ((*iterator_)->block_size_ > size) {
        p_current_memory_block_ = *iterator_;
        list_free_.erase(iterator_);
        break;
      }
    }

    if (p_current_memory_block_ == NULL || p_current_memory_block_->used_size_ + size >= p_current_memory_block_->block_size_) {
      p_current_memory_block_ = AllocateBlock(size);
    }
    list_used_.push_back(p_current_memory_block_);
  }
  p_current_memory_block_->used_size_ += size;
  return p_current_memory_block_->data_ + p_current_memory_block_->used_size_ - size;
}


/*
* $Name: Free
* $Function: Free memory pool
* $Date: 2014-09-25
*/
void MemoryPool::Recycle(){
  if (total_size_ > MAX_POOL_SIZE) {
    Free();
    return;
  }

  iterator_ = list_used_.begin();
  iterator_end_ = list_used_.end();
  for (; iterator_ != iterator_end_; ++iterator_) {
    (*iterator_)->used_size_ = 0;
  }
  list_free_.splice(list_free_.begin(), list_used_);
  p_current_memory_block_ = NULL;
}


/*
 * $Name: Free
 * $Function: Free memory pool
 * $Date: 2014-09-25
 */
void MemoryPool::Free() {
  while (!list_used_.empty()) {
    free(list_used_.front());
    list_used_.pop_front();
  }

  while (!list_free_.empty()) {
    free(list_free_.front());
    list_free_.pop_front();
  }

  p_current_memory_block_ = NULL;
  total_size_ = 0;
}


/*
 * $Name: PrintSize
 * $Function: Print total size
 * $Date: 2014-09-25
 */
void MemoryPool::PrintSize() {
  fprintf(stderr, "Pool Size=%lu k\n", total_size_ >> 10);
}


/*
 * $Name: AllocateBlock
 * $Function: Allocate Memory Block
 * $Date: 2014-09-25
 */
MemoryBlock * MemoryPool::AllocateBlock(size_t &size) {
  size_t allocate_size = size > BLOCK_SIZE ? size : BLOCK_SIZE;
  MemoryBlock * this_block = (MemoryBlock *)malloc(allocate_size + sizeof(MemoryBlock));
  if (this_block == NULL){
    fprintf(stderr, "Error: Allocate block failed!\n");
    fflush(stderr);
    exit(1);
  }
  this_block->data_ = (char*)((MemoryBlock*)this_block + 1);
  this_block->used_size_ = 0;
  this_block->block_size_ = allocate_size;
  total_size_ += allocate_size;
  return this_block;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * $Name: Init
 * $Function: Initializing wrrbm class
 * $Date: 2014-09-25
 */
bool Wrrbm::Init(map<string, string> &parameters) { 
  config_.Init(parameters);

  LearnVocabFromTrainFile();

  ComputeMultinomialDistribution();

  if (random_generator_.Init(v_vocab_distribution_) == false) {
    fprintf(stderr, "Initializing alias table failed\n");
    fflush(stderr);
    exit(1);
  }

  InitRbmAndTrainer();
  return true;
}


/*
 * $Name: SaveVocab
 * $Function: The vocabulary will be saved to file.
 * $Date: 2014-07-09
 */
bool Wrrbm::SaveVocab() {
  if (config_.display_parameters_) {
    fprintf(stderr, "%+20s  %-10s...\n", "save-vocab-file", config_.save_vocab_file_.c_str());
    fflush(stderr);
  }

  FILE *f_vocab = fopen(config_.save_vocab_file_.c_str(), "wb");
  if (f_vocab == NULL) {
    fprintf(stderr, "Error: Can not open %s file!\n", config_.save_vocab_file_.c_str());
    fflush(stderr);
    exit(1);
  }

  for (vector<VocabWord>::iterator iter = v_vocab_.begin(); iter != v_vocab_.end(); ++iter) {
    fprintf(f_vocab, "%s %d\n", iter->word_.c_str(), iter->count_);
  }
  fclose(f_vocab);
  return true;
}


/*
 * $Name: ReadWordIndex
 * $Function: Reads a word and returns its index in the vocabulary
 * $Date: 2014-08-28
 */
int Wrrbm::ReadWordIndex(FILE *fin) {
  char word[MAX_STRING];
  ReadWord(word, fin);
  if (feof(fin)) {
    return -1;
  }
  string word_string(word);
  return SearchVocab(word_string);
}


/*
 * $Name: ReadWord
 * $Function: Reads a single word from a file, assuming space + tab + EOL to be word boundaries
 * $Date: 2014-08-28
 */
void Wrrbm::ReadWord(char *word, FILE *fin) {
  int a = 0, ch;
  while (!feof(fin)) {
    ch = fgetc(fin);
    if (ch == 13) continue;
    if ((ch == ' ') || (ch == '\t') || (ch == '\n')) {
      if (a > 0) {
        if (ch == '\n') ungetc(ch, fin);
        break;
      }
      if (ch == '\n') {
        strcpy(word, (char *)"</s>");
        return;
      } else continue;
    }
    word[a] = ch;
    a++;
    if (a >= MAX_STRING - 1) a--;   // Truncate too long words
  }
  word[a] = 0;
}


/*
 * $Name: LearnVocabFromTrainFile
 * $Function: The vocabulary will be constructed from the training data.
 * $Date: 2014-07-09
 */
bool Wrrbm::LearnVocabFromTrainFile() {
  if (config_.display_parameters_) {
    fprintf(stderr, "\nLearning vocabulary from %s...\n", config_.train_file_.c_str());
    fflush(stderr);
  }
  v_vocab_hash_.resize(config_.vocab_hash_size_);

  for (int i = 0; i < config_.vocab_hash_size_; ++i) {
    v_vocab_hash_.at(i) = -1;
  }

  FILE *fin = fopen(config_.train_file_.c_str(), "rb");
  if (fin == NULL) {
    cerr<<"ERROR: Training file '"<<config_.train_file_<<"' not found.\n"<<flush;
    exit(1);
  }

  v_vocab_.reserve((unsigned int)config_.vocab_max_size_);

  AddReservedWordToVocab();

  char word[MAX_STRING];
  while (1) {
    ReadWord(word, fin);
    string word_string(word);

    if (feof(fin)) {
      break;
    }

    int index = SearchVocab(word_string);
    if (index == -1) {
      size_t vocab_size = AddWordToVocab(word_string);
      v_vocab_.at(vocab_size).count_ = 1;
    } else {
      ++v_vocab_.at(index).count_;
    }
  }
  FilterVocab();

  if (config_.save_vocab_file_ != "") {
    SaveVocab();
  }
  config_.train_file_size_ = ftell(fin);
  fclose(fin);
  return true;
}


/*
* $Name: AddReservedWordToVocab
* $Function: Add reserved word to vocab vector
* $Date: 2014-09-24
*/
bool Wrrbm::AddReservedWordToVocab() {
  string word_tmp = "<unk>";
  size_t vocab_size = AddWordToVocab(word_tmp);
  v_vocab_.at(vocab_size).count_ = 1;
  word_tmp = "<s>";
  vocab_size = AddWordToVocab(word_tmp);
  v_vocab_.at(vocab_size).count_ = 1;
  word_tmp = "</s>";
  vocab_size = AddWordToVocab(word_tmp);
  v_vocab_.at(vocab_size).count_ = 1;
  return true;
}


/*
 * $Name: AddWordToVocab
 * $Function: Add word to vocab vector
 * $Date: 2014-08-25
 */
size_t Wrrbm::AddWordToVocab(string &word) {
  size_t hash;

  VocabWord vocab_word;
  vocab_word.word_ = word;
  vocab_word.count_ = 0;
  v_vocab_.push_back(vocab_word);

  ++config_.vocab_size_;
  if (config_.vocab_size_ + 2 >= config_.vocab_max_size_) {
    config_.vocab_max_size_ += 1000000;
    v_vocab_.reserve(config_.vocab_max_size_);
  }

  hash = GetWordHash(word);
  while (v_vocab_hash_[hash] != -1) {
    hash = (hash + 1) % config_.vocab_hash_size_;
  }
  v_vocab_hash_[hash] = config_.vocab_size_ - 1;
  return config_.vocab_size_ - 1; 
}


/*
* $Name: GetWordHash
* $Function: Returns hash value of a word
* $Date: 2014-08-25
*/
size_t Wrrbm::GetWordHash(string &word) {
  size_t hash = 0;
  for (size_t i = 0; i < word.size(); ++i) {
    hash = hash * 257 + word[ i ];
  }
  hash = hash % config_.vocab_hash_size_;
  return hash;
}


/*
* $Name: SearchVocab
* $Function: Returns position of a word in the vocabulary; if the word is not found, returns -1
* $Date: 2014-08-26
*/
int Wrrbm::SearchVocab(string &word) {
  size_t hash = GetWordHash(word);
  while (1) {
    if (v_vocab_hash_.at(hash) == -1) {
      return -1;
    }
    if (word == v_vocab_.at(v_vocab_hash_.at(hash)).word_) {
      return v_vocab_hash_.at(hash);
    }
    hash = (hash + 1) % config_.vocab_hash_size_;
  }
}


/*
 * $Name: ReduceVocab
 * $Function: Reduces the vocabulary by removing infrequent tokens
 * $Date: 2014-08-26
 */
bool Wrrbm::ReduceVocab() {
  unsigned int hash;
  int j = 0;
  for (int i = 0; i < config_.vocab_size_; ++i) {
    if (v_vocab_.at(i).count_ > config_.min_reduce_) {
      v_vocab_.at(j).count_ = v_vocab_.at(i).count_;
      v_vocab_.at(j).word_ = v_vocab_.at(i).word_;
      ++j;
    }
  }
  config_.vocab_size_ = j;
  v_vocab_.resize(config_.vocab_size_);

  for (int i = 0; i < config_.vocab_hash_size_; ++i) {
    v_vocab_hash_.at(i) = -1;
  }

  for (int i = 0; i < config_.vocab_size_; ++i) {
    hash = GetWordHash(v_vocab_[i].word_);
    while (v_vocab_hash_[hash] != -1) {
      hash = (hash + 1) % config_.vocab_hash_size_;
    }
    v_vocab_hash_[hash] = i;
  }
  ++config_.min_reduce_;
  return true;
}


/*
 * $Name: SortVocab
 * $Function: Sorts the vocabulary by frequency using word counts
 * $Date: 2014-08-26
 */
/*
bool Wrrbm::SortVocab() {
  cerr<<"Sort Vocabulary...\n"<<flush;
  sort(v_vocab_.begin() + 3, v_vocab_.end(), VocabCompare);

  for (int i = 0; i < config_.vocab_hash_size_; ++i) {
    v_vocab_hash_.at(i) = -1;
  }

  int size = config_.vocab_size_;
  int remove_vocab_number = 0;
  size_t hash = 0;
  config_.train_words_ = 0;
  for (int i = 0; i < size; ++i) {
    if ((i > 2) && (v_vocab_.at(i).count_ <= config_.min_count_)) {
      config_.vocab_size_ = i;
      v_vocab_.resize(config_.vocab_size_);
      break;
    } else {
      hash = GetWordHash(v_vocab_[i].word_);
      while (v_vocab_hash_[hash] != -1) {
        hash = (hash + 1) % config_.vocab_hash_size_;
      }
      v_vocab_hash_[hash] = i;
      config_.train_words_ += v_vocab_.at(i).count_;
    }
  }
  config_.remove_vocab_number_ = size - config_.vocab_size_;
  v_vocab_.at(0).count_ = config_.remove_vocab_number_ / 10 > 0 ? config_.remove_vocab_number_ / 10 : 1;
  v_vocab_.at(1).count_ = 1;
  v_vocab_.at(2).count_ = 1;
  return true;
}
*/


/*
* $Name: FilterVocab
* $Function: Filter Vocab
* $Date: 2014-09-26
*/
bool Wrrbm::FilterVocab() {
  for (int i = 0; i < config_.vocab_hash_size_; ++i) {
    v_vocab_hash_.at(i) = -1;
  }

  int size = config_.vocab_size_;
  int remove_vocab_number = 0;
  size_t hash = 0;
  config_.train_words_ = 0;
  for (size_t i = 0; i < v_vocab_.size(); ++i) {
    if ((i > 2) && (v_vocab_.at(i).count_ <= config_.min_count_)) {
      v_vocab_.erase(v_vocab_.begin() + i);
      --i;
    } else {
      hash = GetWordHash(v_vocab_[i].word_);
      while (v_vocab_hash_[hash] != -1) {
        hash = (hash + 1) % config_.vocab_hash_size_;
      }
      v_vocab_hash_[hash] = i;
      config_.train_words_ += v_vocab_.at(i).count_;
    }
  }
  config_.vocab_size_ = v_vocab_.size();
  config_.remove_vocab_number_ = size - config_.vocab_size_;
  v_vocab_.at(0).count_ = config_.remove_vocab_number_ / 10 > 0 ? config_.remove_vocab_number_ / 10 : 1;
  v_vocab_.at(1).count_ = 1;
  v_vocab_.at(2).count_ = 1;
  if (config_.display_parameters_) {
    fprintf(stderr, "%+20s  %-10d\n%+20s  %-10d\n", "vocab-size", config_.vocab_size_, "removed", config_.remove_vocab_number_);
  }
  return true;
}


// Used later for sorting by word counts
bool VocabCompare(const VocabWord &a, const VocabWord &b) {
    return b.count_ < a.count_;
}


/*
 * $Name: ComputeMultinomialDistribution
 * $Function: Compute Multinomial Distribution
 * $Date: 2014-09-25
 */
bool Wrrbm::ComputeMultinomialDistribution() {
  if (config_.display_parameters_) {
    fprintf(stderr, "\nCompute Multinomial Distribution of the vocab\n");
    fflush(stderr);
  }

  v_vocab_distribution_.resize(v_vocab_.size());
  for (size_t i = 0; i != v_vocab_.size(); ++i) {
    v_vocab_distribution_.at(i) = (double)v_vocab_.at(i).count_;
  }

  double total_count = accumulate(v_vocab_distribution_.begin(), v_vocab_distribution_.end(), 0.0);
  if (config_.display_parameters_) {
    fprintf(stderr, "%+20s  %-10.2f\n", "total-word", total_count);
    fflush(stderr);
  }

  for (size_t i = 0; i < v_vocab_distribution_.size(); ++i) {
    v_vocab_distribution_.at(i) /= total_count;
  }
  return true;
}


/*
 * $Name: ComputeHiddenGivenVisible
 * $Function: Compute hidden given visible
 * $Date: 2014-09-26
 */
void Wrrbm::ComputeHiddenGivenVisible(vector<int> &v_samples_of_visible, vector<double> &v_samples_of_hidden, vector<double> &v_prob_of_hidden) {
  if (config_.debug_) {
    fprintf(stderr, "Compute Hidden Given Visible...\n");
    fflush(stderr);
  }

  if (v_samples_of_visible.size() != ngram_) {
    fprintf(stderr, "Error: Input vector size %d vs parameter ngram %d\n", (int)v_samples_of_visible.size(), ngram_);
    fflush(stderr);
    exit(1);
  }

  v_prob_of_hidden.resize(config_.hidden_);
  v_samples_of_hidden.resize(config_.hidden_);

  for (int j = 0; j < config_.hidden_; ++j) {
    double sum_dot_product = 0;
    for (int i = 0; i < ngram_; ++i) {
      // the j-th row of the i-th weight matrix
      double *p_weight_matrix = v_weights_matrix_[i];
      double *p_weight_matrix_j = &p_weight_matrix[j * config_.embedding_size_];

      // the embedding of the i-th word
      double *p_embedding_i = &p_projection_layer_[v_samples_of_visible[i] * config_.embedding_size_];
      sum_dot_product += ComputeDotProduct(p_embedding_i, config_.embedding_size_, p_weight_matrix_j, config_.embedding_size_);
    }
    double activate = p_hidden_bias_[j] + sum_dot_product;
    v_prob_of_hidden[j] = Sigmoid(activate);
    v_samples_of_hidden[j] = Uniform(0, 1) < v_prob_of_hidden[j];
  }

  if (config_.debug_) {
    fprintf(stderr, "Done!\n");
    fflush(stderr);
  }
  return;
}


/*
 * $Name: ComputeVisibleGivenHidden
 * $Function: Compute visible given hidden
 * $Date: 2014-09-26
 */
void Wrrbm::ComputeVisibleGivenHidden(vector<double> &v_samples_of_hidden, vector<int> &v_samples_of_visible_last, vector<int> &v_samples_of_visible_new, \
                                      vector<double> &v_prob_of_visible_new,  vector<bool> *p_samp_of_visible_last_flag) {
  if ((int)v_samples_of_hidden.size() != config_.hidden_) {
    fprintf(stderr, "Error: v_samples_of_hidden length %lu vs hidden %d!\n", v_samples_of_hidden.size(), config_.hidden_);
    fflush(stderr);
    exit(1);
  }

  v_prob_of_visible_new.resize(ngram_);
  v_samples_of_visible_new.resize(ngram_);

  if (p_samp_of_visible_last_flag != NULL) {
    p_samp_of_visible_last_flag->resize(ngram_, false);
  }

  vector<int> temp = v_samples_of_visible_last;
  for (int i = 0; i < ngram_; ++i) {
    map<int, double> activate_cache;
    
    for (int step = 0; step < config_.burn_in_; ++step) {
      int word_id_old = temp[i];
      int word_id_new = random_generator_.Sample();

      if (word_id_old == word_id_new) {
        continue;
      }

      if (p_samp_of_visible_last_flag != NULL) {
        (*p_samp_of_visible_last_flag)[i] = ((*p_samp_of_visible_last_flag)[i] || (word_id_new == v_samples_of_visible_last[i]));
      }

      double prob_old = random_generator_.GetProbability(word_id_old);
      double prob_new = random_generator_.GetProbability(word_id_new);

      double activate_old = 0.0;
      double activate_new = 0.0;

      map<int, double>::iterator iter = activate_cache.find(word_id_old);
      if (iter != activate_cache.end()) {
        activate_old = iter->second;
      } else {
        activate_old = ComputeActivate(word_id_old, i, v_samples_of_hidden);
        activate_cache[word_id_old] = activate_old;
      }

      iter = activate_cache.find(word_id_new);
      if (iter != activate_cache.end()) {
        activate_new = iter->second;
      } else {
        activate_new = ComputeActivate(word_id_new, i, v_samples_of_hidden);
        activate_cache[word_id_new] = activate_new;
      }

      double trans_prob = min<double>(1.0, prob_old / prob_new * exp(activate_new - activate_old));
      v_prob_of_visible_new[i] = trans_prob;
      if (Uniform(0, 1) < trans_prob) {
        temp[i] = word_id_new;
        if ((word_id_new == v_samples_of_visible_last[i] || word_id_old == v_samples_of_visible_last[i]) && config_.debug_) {
          fprintf(stderr, "\nword_old=%s visible_bias=%.2e sum_prob=%.2e activate_old=%.2e\n", v_vocab_[word_id_old].word_.c_str(), \
                  p_visible_bias_[word_id_old], activate_old - p_visible_bias_[word_id_old], activate_old);

          fprintf(stderr, "word_new=%s visible_bias=%.2e sum_prob=%.2e activate_new=%.2e\n", v_vocab_[word_id_new].word_.c_str(), \
                  p_visible_bias_[word_id_new], activate_new - p_visible_bias_[word_id_new], activate_new);

          fprintf(stderr, "word_old=%s prob=%-8.2e act=%-8.2e\n", v_vocab_[word_id_old].word_.c_str(), prob_old, activate_old);
          fprintf(stderr, "word_new=%s prob=%-8.2e act=%-8.2e\n", v_vocab_[word_id_new].word_.c_str(), prob_new, activate_new);
          fprintf(stderr, "exp_ratio=%.2e trans_prob=%-8.4e\n", exp(activate_new - activate_old), trans_prob);

        }
      }
    }
  }

  copy(temp.begin(), temp.end(), v_samples_of_visible_new.begin());

  if (config_.debug_) {
    fprintf(stderr, "-------final compute visible given hidden-------\n");
    for (int i = 0; i < ngram_; ++i) {
      fprintf(stderr, "%d=%s ", i, v_vocab_[v_samples_of_visible_last[i]].word_.c_str());
    }
    fprintf(stderr, " -> ");
    for (int i = 0; i < ngram_; ++i) {
      fprintf(stderr, "%d=%s ", i, v_vocab_[v_samples_of_visible_new[i]].word_.c_str());
    }
    fprintf(stderr, "\n");
    fflush(stderr);
  }
  return;
}


/*
 * $Name: ComputeDotProduct
 * $Function: Compute dot product
 * $Date: 2014-09-26
 */
double Wrrbm::ComputeDotProduct(double *p_vector_1, int length_1, double *p_vector_2, int length_2) {
  if (length_1 != length_2) {
    fprintf(stderr, "Error: vector length inconsistent l1 %d vs l2 %d!\n", length_1, length_2);
    fflush(stderr);
    exit(1);
  }
  if (p_vector_1 == NULL || p_vector_2 == NULL) {
    fprintf(stderr, "Error: ComputeDotProduct with null pointer!\n");
    fflush(stderr);
    exit(1);
  }
  if (length_1 <= 0 || length_2 <= 0) {
    fprintf(stderr, "Error: ComputeDotProduct with zero or negative length vector!\n");
    fflush(stderr);
    exit(1);
  }
  double sum_dot_product = 0.0;
  for (int i = 0; i < length_1; ++i) {
    sum_dot_product += p_vector_1[i] * p_vector_2[i];
  }
  return sum_dot_product;
}


/*
 * $Name: ComputeActivate
 * $Function: Compute activate
 * $Date: 2014-09-26
 */
double Wrrbm::ComputeActivate(int word_id, int position, vector<double> &v_samples_of_hidden) {
  double *p_embedding = &p_projection_layer_[word_id * config_.embedding_size_];
  vector<double> ud(config_.hidden_, 0);
  double *weight_matrix_this = v_weights_matrix_[position];
  for (int i = 0; i < config_.hidden_; ++i) {
    ud[i] = ComputeDotProduct(&weight_matrix_this[i * config_.embedding_size_], config_.embedding_size_, p_embedding, config_.embedding_size_);
    StopNan(ud[i]);
  }

  double bias = p_visible_bias_[word_id];
  double activate = bias + ComputeDotProduct(&ud[0], ud.size(), &v_samples_of_hidden[0], config_.hidden_);

  static int hit = 0;
  ++hit;
  return activate;
}


/*
 * $Name: SaveModelBinary
 * $Function: Save model binary
 * $Date: 2014-09-29
 */
bool Wrrbm::SaveModel(string &file_path) {
  if (config_.binary_format_) {
    string file_path_binary = file_path + ".binary";
    if (config_.display_parameters_) {
      fprintf(stderr, "\n%+20s  %-10s\n", "save-model-binary", file_path_binary.c_str());
      fflush(stderr);
    }
    return SaveModelBinary(file_path_binary.c_str());
  }
  if (config_.text_format_) {
    string file_path_text = file_path + ".text";
    return SaveModelText(file_path_text.c_str());
  }

  return true;
}


/*
 * $Name: SaveModelBinary
 * $Function: Save model binary
 * $Date: 2014-09-29
 */
bool Wrrbm::SaveModelBinary(const char *model_path) {
  FILE *fout = fopen(model_path, "wb");
  if (fout == NULL) {
    fprintf(stderr, "Error: can not open %s file!\n", model_path);
    exit(1);
  }

  // write parameters
  fwrite(&config_.left_, sizeof(config_.left_), 1, fout);
  fwrite(&config_.right_, sizeof(config_.right_), 1, fout);
  fwrite(&ngram_, sizeof(ngram_), 1, fout);
  fwrite(&config_.hidden_, sizeof(config_.hidden_), 1, fout);
  fwrite(&config_.embedding_size_, sizeof(config_.embedding_size_), 1, fout);
  fwrite(&config_.vocab_size_, sizeof(config_.vocab_size_), 1, fout);
  fwrite(&config_.burn_in_, sizeof(config_.burn_in_), 1, fout);

  // write visible bias, hidden bias, and word embeddings
  fwrite(p_visible_bias_, sizeof(double), config_.vocab_size_, fout);
  fwrite(p_hidden_bias_, sizeof(double), config_.hidden_, fout);
  fwrite(p_projection_layer_, sizeof(double), config_.vocab_size_ * config_.embedding_size_, fout);

  // write weights matrix
  for (int i = 0; i < ngram_; ++i) {
    fwrite(v_weights_matrix_[i], sizeof(double), config_.hidden_ * config_.embedding_size_, fout);
  }
  fclose(fout);
  return true;
}


/*
 * $Name: SaveModelBinary
 * $Function: Save model binary
 * $Date: 2014-09-29
 */
bool Wrrbm::SaveModelText(const char *model_path) {
  return true;
}



/*
 * $Name: DisplayParameters
 * $Function: Display parameters
 * $Date: 2014-09-29
 */
void Wrrbm::DisplayParameters(FILE *fp) {
  fprintf(fp, "Display model parameters...\n");
  fprintf(fp, "\tvisible bias:\n");
  for (int i = 0; i < config_.vocab_size_; ++i) {
    fprintf(fp, "%.2e ", p_visible_bias_[i]);
    if ((i + 1) % 10 == 0) {
      fprintf(fp, "\n");
    }
  }

  fprintf(fp, "\thidden bias:\n");
  for (int i = 0; i < config_.hidden_; ++i) {
    fprintf(fp, "%.2e ", p_hidden_bias_[i]);
    if ((i + 1) % 10 == 0) {
      fprintf(fp, "\n");
    }
  }
}



/*
 * $Name: Sigmoid
 * $Function: Sigmoid
 * $Date: 2014-09-26
 */
inline double Wrrbm::Sigmoid(double x) {
  return 1.0 / (1.0 + exp(-x));
}


/*
 * $Name: Uniform
 * $Function: Uniform function
 * $Date: 2014-09-26
 */
inline double Wrrbm::Uniform(double min, double max) {
  return rand() / (RAND_MAX + 1.0) * (max - min) + min;
}


/*
 * $Name: StopNan
 * $Function: stop nan
 * $Date: 2014-09-26
 */
inline void Wrrbm::StopNan(double x) {
  if (isnan(x)) {
    fprintf(stderr, "find nan!\n");
    fgetc(stdin);
  }
}


/*
 * $Name: CheckNan
 * $Function: Check nan
 * $Date: 2014-09-27
 */
void Wrrbm::CheckNan() {
  for (int i = 0; i < config_.hidden_; ++i) {
    if (isnan(p_hidden_bias_[i]) == true) {
      fprintf(stderr, "p_hidden_bias[%d]=%.2f\n", i, p_hidden_bias_[i]);
      fgetc(stderr);
    }
  }

  for (int i = 0; i < config_.vocab_size_; ++i) {
    if (isnan(p_visible_bias_[i]) == true) {
      fprintf(stderr, "p_visible_bias_[%d]=%.2f\n", i, p_visible_bias_[i]);
      fgetc(stderr);
    }
  }

  for (int i = 0; i < config_.vocab_size_ * config_.embedding_size_; ++i) {
    if (isnan(p_projection_layer_[i]) == true) {
      fprintf(stderr, "p_projection_layer_[%d][%d]=%.2f\n", config_.embedding_size_, i % config_.embedding_size_, p_projection_layer_[i]);
      fgetc(stderr);
    }
  }

  for (int i = 0; i < ngram_; ++i) {
    for (int j = 0; j < config_.hidden_ * config_.embedding_size_; ++j) {
      if (isnan(v_weights_matrix_[i][j]) == true) {
        fprintf(stderr, "v_weights_matrix_[%d][%d][%d]=%.2f\n", i, j / config_.embedding_size_, j % config_.embedding_size_, v_weights_matrix_[i][j]);
        fgetc(stderr);
      }
    }
  }
}



/*
 * $Name: InitRbmAndTrainer
 * $Function: Initializing rbm and trainer
 * $Date: 2014-09-25
 */
bool Wrrbm::InitRbmAndTrainer() {
  ngram_ = config_.left_ + config_.right_;

  size_t hidden_size = sizeof(double) * config_.hidden_;
  p_hidden_bias_ = (double *)memory_pool_.Allocate(hidden_size);
  memset(p_hidden_bias_, 0, hidden_size);

  size_t visible_size = sizeof(double) * config_.vocab_size_;
  p_visible_bias_ = (double *)memory_pool_.Allocate(visible_size);

  for (int i = 0; i < config_.vocab_size_; ++i) {
    p_visible_bias_[i] = log(random_generator_.GetProbability(i));
  }

  size_t projection_layer_size = sizeof(double) * config_.vocab_size_ * config_.embedding_size_;
  p_projection_layer_ = (double *)memory_pool_.Allocate(projection_layer_size);

  for (int i = 0; i < config_.vocab_size_; ++i) {
    for (int j = 0; j < config_.embedding_size_; ++j) {
      p_projection_layer_[i * config_.embedding_size_ + j] = rand() / (RAND_MAX + 1.0) * (0.1 - (-0.1)) + (-0.1);
    }
  }

  size_t weight_matrix_size = sizeof(double) * config_.hidden_ * config_.embedding_size_;
  for (int i = 0; i < ngram_; ++i) {
    double *p_weight_matrix = (double *)memory_pool_.Allocate(weight_matrix_size);
    for (int j = 0; j < config_.hidden_; ++j) {
      for (int k = 0; k < config_.embedding_size_; ++k) {
        p_weight_matrix[j * config_.embedding_size_ + k] = rand() / (RAND_MAX + 1.0) * (0.1 - (-0.1)) + (-0.1);
      }
    }
    v_weights_matrix_.push_back(p_weight_matrix);
  }
  return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * $Name: ~WrrbmTrainer
 * $Function: 
 * $Date: 2014-09-25
 */
WrrbmTrainer::~WrrbmTrainer() {
  delete[] p_hidden_bias_;
  delete[] p_hidden_bias_inc_;
  delete[] p_visible_bias_;
  delete[] p_visible_bias_inc_;
  delete[] p_projection_layer_;
  delete[] p_projection_layer_inc_;

  for (int i = 0; i < p_wrrbm_->ngram_; ++i) {
    delete[] v_weights_matrix_[i];
    delete[] v_weights_matrix_inc_[i];
  }
}


/*
 * $Name: TrainModel
 * $Function: Train Wrrbm Model
 * $Date: 2014-09-25
 */
bool WrrbmTrainer::TrainModel(Wrrbm *p_wrrbm) {
  Init(p_wrrbm);

  // Training
  FILE *fp_log = fopen(p_wrrbm->config_.log_file_.c_str(), "wb");
  if (fp_log == NULL) {
    fprintf(stderr, "Error: can not open %s file!\n", p_wrrbm->config_.log_file_.c_str());
    exit(1);
  }

  bool fin_file_end = false;
  FILE *fin = fopen(p_wrrbm->config_.train_file_.c_str(), "rb");
  if (fin == NULL) {
    fprintf(stderr, "Error: can not open %s file!\n", p_wrrbm->config_.train_file_.c_str());
    exit(1);
  }

  vector< vector<int> > v_v_read_data;
  double error = 0;
  double hit = 0;
  size_t data_size = 0;
  size_t batch_number = 0;
  time_t now;
  time(&start_time_);
  if (p_wrrbm_->config_.display_parameters_) {
    fprintf(stderr, "\nTraining ...\n");
  }
  
  for (int epoch = 0; epoch < p_wrrbm->config_.epoches_; epoch += fin_file_end) {
    double momentum = epoch > 5 ? p_wrrbm->config_.final_momentum_ : p_wrrbm->config_.init_momentum_;
    fin_file_end = ReadData(fin, v_v_read_data);

    if (1.0 * v_v_read_data.size() / p_wrrbm_->config_.batch_size_ > 0.5) {
      data_size += v_v_read_data.size();
      pair<double, double> error_hit;
      error_hit = MiniBatchUpdateMultiThreads(v_v_read_data, momentum);
      error += error_hit.first;
      hit += error_hit.second;
      time(&now);
      if (p_wrrbm_->config_.display_parameters_) {
        fprintf(stderr, "\r  epoch %-3d batch=%lu size=%lu error=%.2f hit=%.2f seconds=%d   ", epoch, ++batch_number, v_v_read_data.size(), error, hit, (int)difftime(now, start_time_) );
      }
    }

    if (fin_file_end) {
      time(&now);
      int seconds = (int)difftime(now, start_time_);
      start_time_ = now;
      if (p_wrrbm_->config_.display_parameters_) {
        fprintf(stderr, "\n  epoch=%-3d error=%-7.3e hit=%-7.3e data_size=%lu wer=%.2f%% hit_rate=%.2f%% mins=%d and seconds=%d", \
                epoch, error, hit, data_size, 100 * error / p_wrrbm_->ngram_ / data_size, 100 * hit / p_wrrbm_->ngram_ / data_size, \
                seconds / 60, ((int)seconds) % 60);
      }
      fprintf(fp_log, "epoch=%-3d error=%-7.3e hit=%-7.3e data_size=%lu wer=%.2f%% hit_rate=%.2f%% mins=%d and seconds=%d", \
              epoch, error, hit, data_size, 100 * error / p_wrrbm_->ngram_ / data_size, 100 * hit / p_wrrbm_->ngram_ / data_size, \
              seconds / 60, ((int)seconds) % 60);

      fflush(fp_log);
      fseek(fin, SEEK_SET, 0);
      error = hit = 0;
      data_size = batch_number = 0;

      if ((epoch + 1) % p_wrrbm_->config_.save_frequency_ == 0) {
        BasicMethod basic_method;
        string model_path = p_wrrbm_->config_.output_file_ + ".model." + basic_method.IntToString(epoch);
        string generator_path = p_wrrbm_->config_.output_file_ + ".generator." + basic_method.IntToString(epoch);
        p_wrrbm_->SaveModel(model_path);
        p_wrrbm_->random_generator_.SaveGenerator(generator_path, p_wrrbm_->config_);
      }
    }
  }

  if (p_wrrbm_->config_.display_parameters_) {
    fprintf(stderr, "Finally ...");
    fflush(stderr);
  }
  p_wrrbm->SaveModel(p_wrrbm_->config_.output_file_);
  string generator_path_final = p_wrrbm_->config_.output_file_ + ".generator";
  p_wrrbm->random_generator_.SaveGenerator(generator_path_final, p_wrrbm_->config_);
  fclose(fp_log);
  fclose(fin);
  return true;
}


/*
 * $Name: Init
 * $Function: Init WrrbmTrainer
 * $Date: 2014-09-25
 */
bool WrrbmTrainer::Init(Wrrbm *p_wrrbm) {
  p_wrrbm_ = p_wrrbm;
  p_hidden_bias_ = new double[p_wrrbm->config_.hidden_];
  p_hidden_bias_inc_ = new double[p_wrrbm->config_.hidden_];
  memset(p_hidden_bias_, 0, sizeof(double) * p_wrrbm->config_.hidden_);
  memset(p_hidden_bias_inc_, 0, sizeof(double) * p_wrrbm->config_.hidden_);

  p_visible_bias_ = new double[p_wrrbm->config_.vocab_size_];
  p_visible_bias_inc_ = new double[p_wrrbm->config_.vocab_size_];
  memset(p_visible_bias_, 0, sizeof(double) * p_wrrbm->config_.vocab_size_);
  memset(p_visible_bias_inc_, 0, sizeof(double) * p_wrrbm->config_.vocab_size_);

  p_projection_layer_ = new double[p_wrrbm->config_.vocab_size_ * p_wrrbm->config_.embedding_size_];
  p_projection_layer_inc_ = new double[p_wrrbm->config_.vocab_size_ * p_wrrbm->config_.embedding_size_];
  memset(p_projection_layer_, 0, sizeof(double) * p_wrrbm->config_.vocab_size_ * p_wrrbm->config_.embedding_size_);
  memset(p_projection_layer_inc_, 0, sizeof(double) * p_wrrbm->config_.vocab_size_ * p_wrrbm->config_.embedding_size_);

  for (int i = 0; i < p_wrrbm->ngram_; ++i) {
    double *p_weight_matrix = new double[p_wrrbm->config_.hidden_ * p_wrrbm->config_.embedding_size_];
    memset(p_weight_matrix, 0, sizeof(double) * p_wrrbm->config_.hidden_ * p_wrrbm->config_.embedding_size_);
    v_weights_matrix_.push_back(p_weight_matrix);

    p_weight_matrix = new double[p_wrrbm->config_.hidden_ * p_wrrbm->config_.embedding_size_];
    memset(p_weight_matrix, 0, sizeof(double) * p_wrrbm->config_.hidden_ * p_wrrbm->config_.embedding_size_);
    v_weights_matrix_inc_.push_back(p_weight_matrix);
  }
  v_projection_update_flag_.resize(p_wrrbm->config_.vocab_size_, false);


#ifndef _CPP11
  mutex_bias_.Init();
  mutex_projection_layer_.Init();
  mutex_weights_matrix_.Init();
  mutex_wrrbm_.Init();
#endif


  return true;
}


/*
 * $Name: ReadData
 * $Function: Read data from train file
 * $Date: 2014-09-25
 */
bool WrrbmTrainer::ReadData(FILE *fin, vector< vector<int> > &v_v_read_data) {
  const int MAX_BUF_LEN = 65536;
  char buf[MAX_BUF_LEN];
  char p_start[] = "<s>";
  char p_end[] = "</s>";
  v_v_read_data.clear();

  MemoryPool memory_pool;
  while ((int)v_v_read_data.size() < p_wrrbm_->config_.batch_size_ && fgets(buf, MAX_BUF_LEN, fin) != NULL) {
    vector<char *> v_words = Split(buf, " \t\r\n");
    while (v_words.size() > 0 && strcmp(v_words[0], p_start) == 0) {
      v_words.erase(v_words.begin());
    }

    while (v_words.size() > 0 && strcmp(v_words.back(), p_end) == 0) {
      v_words.pop_back();
    }

    size_t words_number = v_words.size();

    if (p_wrrbm_->config_.left_ > 0) {
      v_words.insert(v_words.begin(), p_wrrbm_->config_.left_, p_start);
    }

    if (p_wrrbm_->config_.right_ > 0) {
      v_words.insert(v_words.end(), p_wrrbm_->config_.right_ - 1, p_end);
    }

    if (p_wrrbm_->config_.debug_) {
      fprintf(stderr, "\nsentence :");
      for (size_t i = 0; i < v_words.size(); ++i) {
        fprintf(stderr, "%s ", v_words[i]);
      }
      fprintf(stderr, "\n");
      fflush(stderr);
    }

    size_t words_size = sizeof(int) * v_words.size();
    int *p_sentence_ids = (int *)memory_pool.Allocate(words_size);
    for (size_t i = 0; i < v_words.size(); ++i) {
      string this_word_string(v_words[i]);
      p_sentence_ids[i] = p_wrrbm_->SearchVocab(this_word_string) == -1 ? 0 : p_wrrbm_->SearchVocab(this_word_string);
    }

    if (p_wrrbm_->config_.debug_) {
      for (size_t i = 0; i < v_words.size(); ++i) {
        fprintf(stderr, "%s=%d ", p_wrrbm_->v_vocab_.at(p_sentence_ids[i]).word_.c_str(), p_sentence_ids[i]);
      }
      fprintf(stderr, "\n");
      fflush(stderr);
    }

    for (size_t i = 0; i < words_number; ++i) {
      vector<int> v_ids(p_wrrbm_->ngram_);
      copy(p_sentence_ids + i, p_sentence_ids + i + p_wrrbm_->ngram_, v_ids.begin());
      v_v_read_data.push_back(v_ids);
      if (p_wrrbm_->config_.debug_) {
        for (size_t j = 0; j < v_v_read_data.back().size(); ++j) {
          fprintf(stderr, "%-6s ", p_wrrbm_->v_vocab_.at(v_v_read_data.back()[j]).word_.c_str());
        }
        fprintf(stderr, "\n");
        fflush(stderr);
      }
    }
  }
  if (feof(fin) != 0) {
    return true;
  } else {
    return false;
  }
}


/*
 * $Name: MiniBatchUpdateMultiThreads
 * $Function: Mini batch update multi-threads function
 * $Date: 2014-09-26
 */
pair<double, double> WrrbmTrainer::MiniBatchUpdateMultiThreads(vector< vector<int> > &v_v_read_data, double &momentum) {
  // reset gradients
  memset(p_visible_bias_, 0, sizeof(double) * p_wrrbm_->config_.vocab_size_);
  memset(p_hidden_bias_, 0, sizeof(double) * p_wrrbm_->config_.hidden_);
  memset(p_projection_layer_, 0, sizeof(double) * p_wrrbm_->config_.vocab_size_ * p_wrrbm_->config_.embedding_size_);

  for (size_t i = 0; i < v_weights_matrix_.size(); ++i) {
    memset(v_weights_matrix_[i], 0, sizeof(double) * p_wrrbm_->config_.hidden_ * p_wrrbm_->config_.embedding_size_);
  }

  fill(v_projection_update_flag_.begin(), v_projection_update_flag_.end(), false);

  vector< vector<int> >::iterator begin = v_v_read_data.begin();
  vector< vector<int> >::iterator end = v_v_read_data.end();
  int data_per_thread = (end - begin) / p_wrrbm_->config_.threads_number_;
  vector<double> v_error(p_wrrbm_->config_.threads_number_, 0.0);
  vector<double> v_hit(p_wrrbm_->config_.threads_number_, 0.0);

#ifdef _CPP11
  vector<thread> v_training_threads;
  for (int i = 0; i < p_wrrbm_->config_.threads_number_ - 1; ++i) {
    v_training_threads.push_back(thread(&WrrbmTrainer::MiniBatchUpdateThread, this, \
                                       begin + i * data_per_thread, begin + (i + 1) * data_per_thread, \
                                       &v_error[0] + i, &v_hit[0] + i, i));
  }

  v_training_threads.push_back(thread(&WrrbmTrainer::MiniBatchUpdateThread, this, \
                                     begin + (p_wrrbm_->config_.threads_number_ - 1) * data_per_thread, end, \
                                     &v_error[0] + p_wrrbm_->config_.threads_number_ - 1, \
                                     &v_hit[0] + p_wrrbm_->config_.threads_number_ - 1, \
                                     p_wrrbm_->config_.threads_number_ - 1));

  for (int i = 0; i < (int)v_training_threads.size(); ++i) {
    v_training_threads.at(i).join();
  }
#else
  vector<WrrbmTrainingThread> v_wrrbm_training_thread;
  v_wrrbm_training_thread.resize(p_wrrbm_->config_.threads_number_);
  for (int i = 0; i < p_wrrbm_->config_.threads_number_ - 1; ++i) {
    v_wrrbm_training_thread.at(i).id_ = i;
    v_wrrbm_training_thread.at(i).p_wrrbm_trainer_ = this;
    v_wrrbm_training_thread.at(i).begin_ = begin + i * data_per_thread;
    v_wrrbm_training_thread.at(i).end_ = begin + (i + 1) * data_per_thread;
    v_wrrbm_training_thread.at(i).p_error_ = &v_error[0] + i;
    v_wrrbm_training_thread.at(i).p_hit_ = &v_hit[0] + i;
    v_wrrbm_training_thread.at(i).Start();
  }

  v_wrrbm_training_thread.at(p_wrrbm_->config_.threads_number_ - 1).id_ = p_wrrbm_->config_.threads_number_ - 1;
  v_wrrbm_training_thread.at(p_wrrbm_->config_.threads_number_ - 1).p_wrrbm_trainer_ = this;
  v_wrrbm_training_thread.at(p_wrrbm_->config_.threads_number_ - 1).begin_ = begin + (p_wrrbm_->config_.threads_number_ - 1) * data_per_thread;
  v_wrrbm_training_thread.at(p_wrrbm_->config_.threads_number_ - 1).end_ = end;
  v_wrrbm_training_thread.at(p_wrrbm_->config_.threads_number_ - 1).p_error_ = &v_error[0] + p_wrrbm_->config_.threads_number_ - 1;
  v_wrrbm_training_thread.at(p_wrrbm_->config_.threads_number_ - 1).p_hit_ = &v_hit[0] + p_wrrbm_->config_.threads_number_ - 1;
  v_wrrbm_training_thread.at(p_wrrbm_->config_.threads_number_ - 1).Start();

  for (int i = 0; i < p_wrrbm_->config_.threads_number_; ++i) {
    v_wrrbm_training_thread.at(i).Join();
  }
#endif

  int batch_size = end - begin;
  UpdateParameter(batch_size, momentum);

  double total_error = accumulate(v_error.begin(), v_error.end(), 0.0);
  double total_hit = accumulate(v_hit.begin(), v_hit.end(), 0.0);
  return pair<double, double>(total_error, total_hit);
}


/*
 * $Name: MiniBatchUpdateThread
 * $Function: Mini Batch Update Thread Function
 * $Date: 2014-09-26
 */
void WrrbmTrainer::MiniBatchUpdateThread(vector< vector<int> >::iterator begin, vector< vector<int> >::iterator end, \
                                         double *p_error, double *p_hit, int thread_id) {
  *p_error = 0;
  double *p_local_visible_bias = new double[p_wrrbm_->config_.vocab_size_];
  double *p_local_hidden_bias = new double[p_wrrbm_->config_.hidden_];
  double *p_local_projection_layer = new double[p_wrrbm_->config_.vocab_size_ * p_wrrbm_->config_.embedding_size_];
  memset(p_local_visible_bias, 0, sizeof(double) * p_wrrbm_->config_.vocab_size_);
  memset(p_local_hidden_bias, 0, sizeof(double) * p_wrrbm_->config_.hidden_);
  memset(p_local_projection_layer, 0, sizeof(double) * p_wrrbm_->config_.vocab_size_ * p_wrrbm_->config_.embedding_size_);

  vector<double *> v_local_weights_matrix;
  for (size_t i = 0; i < v_weights_matrix_.size(); ++i) {
    v_local_weights_matrix.push_back(new double[p_wrrbm_->config_.hidden_ * p_wrrbm_->config_.embedding_size_]);
    memset(v_local_weights_matrix[i], 0, sizeof(double) * p_wrrbm_->config_.hidden_ * p_wrrbm_->config_.embedding_size_);
  }

  int count = 0;
  for (vector< vector<int> >::iterator iter = begin; iter != end; ++iter) {
    ++count;
    vector<int> &v_samples_of_visible_0 = *iter;
    vector<int> v_samples_of_visible_1;
    vector<double> v_prob_of_visible_1;
    vector<double> v_samples_of_hidden_0;
    vector<double> v_samples_of_hidden_1;
    vector<double> v_prob_of_hidden_0;
    vector<double> v_prob_of_hidden_1;

    vector<bool> v_samp_of_visible_0_flag;

    // sampling
    p_wrrbm_->ComputeHiddenGivenVisible(v_samples_of_visible_0, v_samples_of_hidden_0, v_prob_of_hidden_0);
    p_wrrbm_->ComputeVisibleGivenHidden(v_samples_of_hidden_0, v_samples_of_visible_0, v_samples_of_visible_1, v_prob_of_visible_1, &v_samp_of_visible_0_flag);
    bool failed_flag = false;

    for (size_t i = 0; i < v_samples_of_visible_0.size(); ++i) {
      *p_hit += v_samp_of_visible_0_flag[i];
      if (v_samples_of_visible_0[i] != v_samples_of_visible_1[i]) {
        failed_flag = true;
      }
    }

    if (failed_flag == false) {
      continue;
    }

    p_wrrbm_->ComputeHiddenGivenVisible(v_samples_of_visible_1, v_samples_of_hidden_1, v_prob_of_hidden_1);


    for (size_t i = 0; i < v_samples_of_visible_0.size(); ++i) {
      if (p_wrrbm_->config_.debug_) {
        fprintf(stderr, "position=%lu\n", i);
        fflush(stderr);
      }

      double *p_local_weight_matrix_i = v_local_weights_matrix[i];
      double *p_embedding_0 = &p_wrrbm_->p_projection_layer_[v_samples_of_visible_0[i] * p_wrrbm_->config_.embedding_size_];
      double *p_embedding_1 = &p_wrrbm_->p_projection_layer_[v_samples_of_visible_1[i] * p_wrrbm_->config_.embedding_size_];

      for (int h = 0; h < p_wrrbm_->config_.hidden_; ++h) {
        for (int e = 0; e < p_wrrbm_->config_.embedding_size_; ++e) {
          p_local_weight_matrix_i[h * p_wrrbm_->config_.embedding_size_ + e] += v_prob_of_hidden_0[h] * p_embedding_0[e] - \
                                                                                v_prob_of_hidden_1[h] * p_embedding_1[e];
          if (p_wrrbm_->config_.debug_ && (h * p_wrrbm_->config_.embedding_size_ + e) % 10000 == 0) {
            fprintf(stderr, "done!\n");
            fflush(stderr);
          }
        }
      }

      // Compute reconstruction error
      if (v_samples_of_visible_0[i] != v_samples_of_visible_1[i]) {
        *p_error += 1;
        failed_flag = true;
      }
    }

    if (p_wrrbm_->config_.debug_ && ((int)*p_error % 10) == 0 && failed_flag) {
      for (size_t i = 0; i < v_samples_of_visible_0.size(); ++i) {
        fprintf(stderr, "%s ", p_wrrbm_->v_vocab_[v_samples_of_visible_0[i]].word_.c_str());
      }

      fprintf(stderr, " -> ");
      for (size_t i = 0; i < v_samples_of_visible_1.size(); ++i) {
        fprintf(stderr, "%s ", p_wrrbm_->v_vocab_[v_samples_of_visible_1[i]].word_.c_str());
      }
      fflush(stderr);
    }

    // update embedding parameters 
    for (size_t i = 0; i < v_samples_of_visible_0.size(); ++i) {
      double *p_weight_matrix_i = p_wrrbm_->v_weights_matrix_[i];
      double *p_local_embedding_0 = &p_local_projection_layer[v_samples_of_visible_0[i] * p_wrrbm_->config_.embedding_size_];
      double *p_local_embedding_1 = &p_local_projection_layer[v_samples_of_visible_1[i] * p_wrrbm_->config_.embedding_size_];
    
      for (int h = 0; h < p_wrrbm_->config_.hidden_; ++h) {
        for (int e = 0; e < p_wrrbm_->config_.embedding_size_; ++e) {
          p_local_embedding_0[e] += v_prob_of_hidden_0[h] * p_weight_matrix_i[h * p_wrrbm_->config_.embedding_size_ + e];
          p_local_embedding_1[e] -= v_prob_of_hidden_1[h] * p_weight_matrix_i[h * p_wrrbm_->config_.embedding_size_ + e];
        }
      }

      // update visible bias
      p_local_visible_bias[v_samples_of_visible_0[i]] += 1.0;
      p_local_visible_bias[v_samples_of_visible_1[i]] -= 1.0;
    }

    // update hidden bias
    for (int h = 0; h < p_wrrbm_->config_.hidden_; ++h) {
      p_local_hidden_bias[h] += v_prob_of_hidden_0[h] - v_prob_of_hidden_1[h];
    }
  }

  // for the shared data
#ifdef _CPP11
  mutex_bias_.lock();
#else
  mutex_bias_.Lock();
#endif
  for (int i = 0; i < p_wrrbm_->config_.hidden_; ++i) {
    p_hidden_bias_[i] += p_local_hidden_bias[i];
  }

  for (int i = 0; i < p_wrrbm_->config_.vocab_size_; ++i) {
    p_visible_bias_[i] += p_local_visible_bias[i];
  }
#ifdef _CPP11
  mutex_bias_.unlock();
#else
  mutex_bias_.Unlock();
#endif

  // for embedding
#ifdef _CPP11
  mutex_projection_layer_.lock();
#else
  mutex_projection_layer_.Lock();
#endif
  for (int i = 0; i < p_wrrbm_->config_.vocab_size_ * p_wrrbm_->config_.embedding_size_; ++i) {
    p_projection_layer_[i] += p_local_projection_layer[i];
  }
#ifdef _CPP11
  mutex_projection_layer_.unlock();
#else
  mutex_projection_layer_.Unlock();
#endif

  // for weight matrix
#ifdef _CPP11
  mutex_weights_matrix_.lock();
#else
  mutex_weights_matrix_.Lock();
#endif
  for (int i = 0; i < (int)v_local_weights_matrix.size(); ++i) {
    double *this_local_weight_matrix = v_local_weights_matrix[i];
    double *this_weight_matrix = v_weights_matrix_[i];
    for (int h = 0; h < p_wrrbm_->config_.hidden_; ++h) {
      for (int e = 0; e < p_wrrbm_->config_.embedding_size_; ++e) {
        this_weight_matrix[h * p_wrrbm_->config_.embedding_size_ + e] += this_local_weight_matrix[h * p_wrrbm_->config_.embedding_size_ + e];
      }
    }
  }
#ifdef _CPP11
  mutex_weights_matrix_.unlock();
#else
  mutex_weights_matrix_.Unlock();
#endif

  delete[] p_local_visible_bias;
  delete[] p_local_hidden_bias;
  delete[] p_local_projection_layer;
  for (size_t i = 0; i < v_local_weights_matrix.size(); ++i) {
    delete[] v_local_weights_matrix[i];
  }
  return;
}


/*
 * $Name: UpdateParameter
 * $Function: Update parameter
 * $Date: 2014-09-27
 */
void WrrbmTrainer::UpdateParameter(int batch_size, double momentum) {
  double pretrain_rate = p_wrrbm_->config_.pretrain_rate_ / batch_size;
  double bias_rate = p_wrrbm_->config_.bias_rate_ / batch_size;

  if (p_wrrbm_->config_.debug_) {
    fprintf(stderr, "\nUpdate parameter pretrain_rate=%.2e bias_rate=%.2e\n", pretrain_rate, bias_rate);
    fflush(stderr);
  }

  // Update hidden bias
  for (int h = 0; h < p_wrrbm_->config_.hidden_; ++h) {
    p_hidden_bias_inc_[h] = p_hidden_bias_inc_[h] * momentum + p_hidden_bias_[h] * pretrain_rate;
    p_wrrbm_->p_hidden_bias_[h] += p_hidden_bias_inc_[h] - p_wrrbm_->config_.l2_ * p_wrrbm_->p_hidden_bias_[h];

    if (isnan(p_wrrbm_->p_hidden_bias_[h]) == true) {
      fprintf(stderr, "momentum=%.e p_hidden_bias_inc[%d]=%.2e pretrain_rate=%.2e\n", momentum, h, p_hidden_bias_inc_[h], pretrain_rate);
      fgetc(stdin);
    }
  }

  // Update visible bias, bias_rate
  for (int i = 0; i < p_wrrbm_->config_.vocab_size_; ++i) {
    p_visible_bias_inc_[i] = p_visible_bias_inc_[i] * momentum + p_visible_bias_[i] * bias_rate;
    p_wrrbm_->p_visible_bias_[i] += p_visible_bias_inc_[i] - p_wrrbm_->config_.l2_ * p_wrrbm_->p_visible_bias_[i];

    if (p_wrrbm_->config_.debug_ && i % 1000 == 0) {
      fprintf(stderr, "p_visbile_bias[%d]=%.2e p_visible_bias_old[%d]=%.2e p_visible_bias_new[%d]=%.2e\n", i, p_visible_bias_[i], i, p_wrrbm_->p_visible_bias_[i] - p_visible_bias_inc_[i], i, p_wrrbm_->p_visible_bias_[i]);
    }
  }

  // Update weights matrix
  for (size_t i = 0; i < v_weights_matrix_.size(); ++i) {
    double *p_weight_matrix_inc_i = v_weights_matrix_inc_[i];
    double *p_weight_matrix_i = v_weights_matrix_[i];
    double *p_wrrbm_weight_matrix_i = p_wrrbm_->v_weights_matrix_[i];

    for (int h = 0; h < p_wrrbm_->config_.hidden_; ++h) {
      for (int e = 0; e < p_wrrbm_->config_.embedding_size_; ++e) {
        int point_x = h * p_wrrbm_->config_.embedding_size_ + e;
        p_weight_matrix_inc_i[point_x] = p_weight_matrix_inc_i[point_x] * momentum + p_weight_matrix_i[point_x] * pretrain_rate;
        p_wrrbm_weight_matrix_i[point_x] += p_weight_matrix_inc_i[point_x];
        if (p_wrrbm_->config_.debug_ == true && point_x % 300 == 0) {
          fprintf(stderr, "p_weight_matrix_i[%d]=%.2e p_wrrbm_weight_matrix_i_old[%d]=%.2e p_wrrib_weight_matrix_i_new[%d]=%.2e", point_x, p_weight_matrix_i[point_x], point_x, p_wrrbm_weight_matrix_i[point_x] - p_weight_matrix_inc_i[point_x], point_x, p_wrrbm_weight_matrix_i[point_x]);
        }
      }
    }
  }

  // Update word embedding: |p_wrrbm_->config_.vocab_size_| * p_wrrbm_->config_.embedding_size_ matrix
  for (int i = 0; i < p_wrrbm_->config_.vocab_size_; ++i) {
    for (int e = 0; e < p_wrrbm_->config_.embedding_size_; ++e) {
      int point_x = i * p_wrrbm_->config_.embedding_size_ + e;
      p_projection_layer_inc_[point_x] = p_projection_layer_inc_[point_x] * momentum + p_projection_layer_[point_x] * pretrain_rate;
      p_wrrbm_->p_projection_layer_[point_x] += p_projection_layer_inc_[point_x];

      if (p_wrrbm_->config_.debug_ && point_x % 300 == 0) {
        fprintf(stderr, "p_projection_layer[%d]=%.2e p_wrrbm_projection_layer_old[%d]=%.2e p_wrrbm_projection_layer_new[%d]=%.2e", point_x, p_projection_layer_[point_x], point_x, p_wrrbm_->p_projection_layer_[point_x] - p_projection_layer_[point_x] * bias_rate, point_x, p_wrrbm_->p_projection_layer_[point_x]);
      }
    }
  }
  
  p_wrrbm_->CheckNan();
  return;
}


/*
 * $Name: Split
 * $Function: Split string with delemiter
 * $Date: 2014-09-25
 */
vector<char *> WrrbmTrainer::Split(char *p_buf, const char *p_delemiter) {
  vector<char *> v_reserve;
  if (p_buf == NULL || p_delemiter == NULL) {
    return v_reserve;
  }

  char *p = p_buf;
  while (true) {
    while (*p && strchr(p_delemiter, *p) != NULL) {
      *p++ = 0;
    }
    if (!*p) {
      break;
    }
    v_reserve.push_back(p);
    while (*p && strchr(p_delemiter, *p) == NULL) {
      ++p;
    }
  }
  return v_reserve;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _CPP11
/*
 * $Name: Start
 * $Function: Start multi threads
 * $Date: 2014-09-12
 */
void WrrbmTrainingThread::Start() {
#ifdef HAVE_PTHREAD_H
  pthread_create( &hnd_, 0, &WrrbmTrainingThread::Wrapper, static_cast<void *>(this) );
#else
#ifdef _WIN32
  DWORD dword_id;
  hnd_ = BEGINTHREAD(0, 0, &WrrbmTrainingThread::Wrapper, this, 0, &dword_id );
#else
  TrainModelThread();
#endif
#endif
}


/*
 * $Name: TrainModelThread
 * $Function: Training word embedding
 * $Date: 2014-09-12
 */
void *WrrbmTrainingThread::TrainModelThread() { 
  p_wrrbm_trainer_->MiniBatchUpdateThread(begin_, end_, p_error_, p_hit_, id_);
  return 0;
}
#endif




}