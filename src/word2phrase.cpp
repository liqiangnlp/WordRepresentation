/*
 * $Id:
 * 0022
 *
 * $File:
 * word2phrase.cpp
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
 * 2014-09-02, 17:40
 */

#include "word2phrase.h"

namespace word_representation_word2phrase {


bool Word2PhraseConfig::Init(map<string, string> &parameters) {
  cerr<<"Init parameters...\n"<<flush;
  CheckParamsInConfig(parameters);
  CheckFilesInConfig(parameters);
  return true;
}


/*
 * $Name: CheckParamsInConfig
 * $Function: Check the parameters in configuration file.
 * $Date: 2014-07-09
 */
bool Word2PhraseConfig::CheckParamsInConfig(map<string, string> &parameters) {
  string parameter_key;
  string default_value;
  parameter_key = "threshold";
  default_value = "100";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  threshold_ = (float)atof(parameters[parameter_key].c_str());

  parameter_key = "output-file";
  default_value = "output.txt";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  output_file_ = parameters[parameter_key];
  return true;
}


/*
 * $Name: CheckParamsInConfig
 * $Function: Check the parameters in configuration file.
 * $Date: 2014-07-09
 */
bool Word2PhraseConfig::CheckEachParamInConfig(map<string, string> &parameters, string &parameter_key, string &default_value) {
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
bool Word2PhraseConfig::CheckFilesInConfig(map<string, string> &parameters) {
  string file_key;
  file_key = "train-file";
  CheckEachFileInConfig(parameters, file_key);
  train_file_ = parameters[file_key];
  return true;
}


/*
 * $Name: CheckEachFileInConfig
 * $Function: Check each file in configuration file.
 * $Date: 2014-07-09
 */
bool Word2PhraseConfig::CheckEachFileInConfig(map<string, string> &parameters, string &file_key) {
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


bool Word2Phrase::ConvertWord2Phrase(map<string, string> &parameters) {
  cerr<<"Convert Word 2 Phrase...\n"<<flush;
  config_.Init(parameters);
  LearnVocabFromTrainFile();
  cerr<<"train_words="<<config_.train_words_<<"\n"<<flush;

  ifstream in_train_file(config_.train_file_.c_str());
  if (!in_train_file) {
    cerr<<"ERROR: Training file'"<<config_.train_file_<<"' not found.\n"<<flush;
    exit(1);
  }

  ofstream out_file(config_.output_file_.c_str());
  if (!out_file) {
    cerr<<"ERROR: Can not open output file '"<<config_.output_file_<<"'.\n"<<flush;
  }

  string last_word, bigram_word;
  string sentence_tmp;
  size_t line_no = 0;
  long long count = 0;
  long long oov = 0;
  long long index, last_index = -1;
  long long p_last = 0, p_this = 0, p_last_this = 0;
  float score;
  while (getline(in_train_file, sentence_tmp)) {
    ++line_no;
    if (line_no % 10000 == 0) {
      cerr<<"\r  Process "<<line_no<<" lines."<<flush;
    }
    ClearIllegalChar(sentence_tmp);
    RmEndSpace(sentence_tmp);
    RmStartSpace(sentence_tmp);

    sentence_tmp += " </s>";
    vector<string> words_tmp;
    Split(sentence_tmp, ' ', words_tmp);
    for (vector<string>::iterator iter = words_tmp.begin(); iter != words_tmp.end(); ++iter) {
      if (*iter == "</s>") {
        out_file<<"\n";
        continue;
      }
      ++count;
      oov = 0;
      index = SearchVocab(*iter);
      if (index == -1) {
        oov = 1;
      } else {
        p_this = vocab_.at(index).count_;
      }

      if (last_index == -1) {
        oov = 1;
      }

      last_index = index;
      bigram_word = last_word + "_" + *iter;
      index = SearchVocab(bigram_word);
      if (index == -1) {
        oov = 1;
      } else {
        p_last_this = vocab_.at(index).count_;
      }

      if (p_last < config_.min_count_) {
        oov = 1;
      }
      if (p_this < config_.min_count_) {
        oov = 1;
      }
      if (oov) {
        score = 0;
      } else {
        // score = ((count(last and this) - min_count) / count(last) / count(this)) * train_words
        score = (p_last_this - config_.min_count_) / (float)p_last / (float)p_this * (float)config_.train_words_;  
      }

      if (score > config_.threshold_) {
        out_file<<"_"<<*iter;
        p_this = 0;
      } else {
        out_file<<" "<<*iter;
      }
 
      p_last = p_this;
      last_word = *iter;
    }
  }
  cerr<<"\r  Process "<<line_no<<" lines.\n"<<flush;
  return true;
}


/*
 * $Name: LearnVocabFromTrainFile
 * $Function: The vocabulary will be constructed from the training data.
 * $Date: 2014-09-02
 */
bool Word2Phrase::LearnVocabFromTrainFile() {
  cerr<<"Learning Vocabulary from train file...\n"<<flush;
  vocab_hash_.resize(config_.vocab_hash_size_);

  for (size_t i = 0; i < config_.vocab_hash_size_; ++i) {
    vocab_hash_.at(i) = -1;
  }

  ifstream in_train_file(config_.train_file_.c_str());
  if (!in_train_file) {
      cerr<<"ERROR: Training file'"<<config_.train_file_<<"' not found.\n"<<flush;
      exit(1);
  }

  string word_tmp = "</s>";
  vocab_.reserve((unsigned int)config_.vocab_max_size_);
  AddWordToVocab(word_tmp);

  string sentence_tmp;
  long long start = 1;
  size_t line_no = 0;
  string last_word, bigram_word;
  config_.train_words_ = 0;
  while (getline(in_train_file,sentence_tmp)) {
    ++line_no;
    ClearIllegalChar(sentence_tmp);
    RmEndSpace(sentence_tmp);
    RmStartSpace(sentence_tmp);

    sentence_tmp += " </s>";
    vector<string> words_tmp;
    Split(sentence_tmp, ' ', words_tmp);
    for (vector<string>::iterator iter = words_tmp.begin(); iter != words_tmp.end(); ++iter) {
      if (*iter == "</s>") {
        start = 1;
        continue;
      } else {
        start = 0;
      }
      ++config_.train_words_;

      int index = SearchVocab(*iter);
      if (index == -1) {
        size_t vocab_size = AddWordToVocab(*iter);
        vocab_.at(vocab_size).count_ = 1;
      } else {
        ++vocab_.at(index).count_;
      }

      if (start) {
        continue;
      }
      bigram_word = last_word + "_" + *iter;
      last_word = *iter;

      index = SearchVocab(bigram_word);
      if (index == -1) {
        size_t vocab_size = AddWordToVocab(bigram_word);
        vocab_.at(vocab_size).count_ = 1;
      } else {
        ++vocab_.at(index).count_;
      }

      if (config_.vocab_size_ > config_.vocab_hash_size_ * 0.7) {
        ReduceVocab();
      }
    }

    if (line_no % 10000 ==0) {
      cerr<<"\r  Processed "<<line_no<<" lines.";
    }
  }
  cerr<<"  Processed "<<line_no<<" lines.\n";
  SortVocab();
  if (config_.save_vocab_file_ != "") {
    SaveVocab();
  }
  in_train_file.clear();
  in_train_file.close();
  return true;
}


/*
 * $Name: SaveVocab
 * $Function: The vocabulary will be saved to file.
 * $Date: 2014-07-09
 */
bool Word2Phrase::SaveVocab() {
  cerr<<"Save vocabulary...\n"<<flush;
  cerr<<"save_vocab_file_="<<config_.save_vocab_file_<<"\n"<<flush;
  ofstream out_vocab(config_.save_vocab_file_.c_str());
  if (!out_vocab) {
      cerr<<"ERROR: Output vocabulary file'"<<config_.save_vocab_file_<<"' can not be opened.\n"<<flush;
      exit(1);
  }

  for (vector<VocabWord>::iterator iter = vocab_.begin(); iter != vocab_.end(); ++iter) {
    out_vocab<<iter->word_<<" "<<iter->count_<<"\n";
  }

  out_vocab.close();
  return true;
}



/*
 * $Name: AddWordToVocab
 * $Function: Add word to vocab vector
 * $Date: 2014-08-25
 */
size_t Word2Phrase::AddWordToVocab(string &word) {
  size_t hash;
//  size_t length = word.size() + 1;
//  if (length > config_.max_string_) {
//    length = config_.max_string_;
//  }

  VocabWord vocab_word;
  vocab_word.word_ = word;
  vocab_word.count_ = 0;
  vocab_.push_back(vocab_word);

  ++config_.vocab_size_;
  if (config_.vocab_size_ + 2 >= config_.vocab_max_size_) {
    config_.vocab_max_size_ += 10000;
    vocab_.reserve(config_.vocab_max_size_);
  }

  hash = GetWordHash(word);
  while (vocab_hash_[hash] != -1) {
    hash = (hash + 1) % config_.vocab_hash_size_;
  }
  vocab_hash_[hash] = config_.vocab_size_ - 1;
  return config_.vocab_size_ - 1; 
}


/*
* $Name: GetWordHash
* $Function: Returns hash value of a word
* $Date: 2014-08-25
*/
size_t Word2Phrase::GetWordHash(string &word) {
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
int Word2Phrase::SearchVocab(string &word) {
  size_t hash = GetWordHash(word);
//  cerr<<"searchvocab,hash="<<hash<<"\n"<<flush;
  while ( 1 ) {
    if (vocab_hash_.at(hash) == -1) {
      return -1;
    }
    if (word == vocab_.at(vocab_hash_.at(hash)).word_) {
      return vocab_hash_.at(hash);
    }
    hash = (hash + 1) % config_.vocab_hash_size_;
  }
}


/*
 * $Name: ReduceVocab
 * $Function: Reduces the vocabulary by removing infrequent tokens
 * $Date: 2014-08-26
 */
bool Word2Phrase::ReduceVocab() {
#ifdef __DEBUG_WORD2VECTOR__
  cerr<<"Reduce Vocab...\n"<<flush;
#endif
  return true;
}


/*
 * $Name: SortVocab
 * $Function: Sorts the vocabulary by frequency using word counts
 * $Date: 2014-08-26
 */
bool Word2Phrase::SortVocab() {
  cerr<<"Sort Vocabulary...\n"<<flush;
  sort(vocab_.begin() + 1, vocab_.end(), VocabCompare);

  for (int i = 0; i < config_.vocab_hash_size_; ++i) {
    vocab_hash_.at(i) = -1;
  }

  int size = config_.vocab_size_;
  size_t hash = 0;
//  config_.train_words_ = 0;
  for (int i = 0; i < size; ++i) {
    if ((i > 0) && (vocab_.at(i).count_ < config_.min_count_)) {
      config_.vocab_size_ = i;
      vocab_.resize(config_.vocab_size_);
      break;
    } else {
      hash = GetWordHash(vocab_[i].word_);
      while (vocab_hash_[hash] != -1) {
        hash = (hash + 1) % config_.vocab_hash_size_;
      }
      vocab_hash_[hash] = i;
//      config_.train_words_ += vocab_.at(i).count_;
    }
  }

  cerr<<"Vocab size="<<config_.vocab_size_<<"\n"<<flush;
//      <<"Words in train file="<<config_.train_words_<<"\n"<<flush;
  return true;
}

}


