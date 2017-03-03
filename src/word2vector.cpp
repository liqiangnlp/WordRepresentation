/*
 * $Id:
 * 0010
 *
 * $File:
 * word2vector.cpp
 *
 * $Proj:
 * WordRepresentation
 *
 * $Func:
 * word 2 vector
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

#include "word2vector.h"

namespace word_representation_word2vector {


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
  string parameter_key = "max-string";
  string default_value = "100";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  max_string_ = atoi(parameters[ parameter_key ].c_str());

  parameter_key = "exp-table-size";
  default_value = "1000";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  exp_table_size_ = atoi(parameters[ parameter_key ].c_str());

  parameter_key = "max-exp";
  default_value = "6";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  max_exp_ = atoi(parameters[ parameter_key ].c_str());

  parameter_key = "max-sentence-length";
  default_value = "1000";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  max_sentence_length_ = atoi(parameters[ parameter_key ].c_str());

  parameter_key = "max-code-length";
  default_value = "40";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  max_code_length_ = atoi(parameters[ parameter_key ].c_str());

  parameter_key = "size";
  default_value = "100";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  layer1_size_ = atoi(parameters[ parameter_key ].c_str());

  parameter_key = "min-count";
  default_value = "5";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  min_count_ = atoi(parameters[parameter_key].c_str());

  parameter_key = "window";
  default_value = "5";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  window_ = atoi(parameters[ parameter_key ].c_str());

  parameter_key = "sample";
  default_value = "0";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  sample_ = (float)atof(parameters[ parameter_key ].c_str());

  parameter_key = "alpha";
  default_value = "0.025";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  alpha_ = (float)atof(parameters[ parameter_key ].c_str());
  starting_alpha_ = alpha_;

  parameter_key = "model";
  default_value = "1";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  model_ = atoi(parameters[ parameter_key ].c_str());

  parameter_key = "classes";
  default_value = "0";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  classes_ = atoi(parameters[ parameter_key ].c_str());

  parameter_key = "threads-number";
  default_value = "1";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  threads_number_ = atoi(parameters[ parameter_key ].c_str());

  parameter_key = "binary";
  default_value = "0";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  binary_ = (parameters[parameter_key] == "0" ? false : true);

  parameter_key = "hs";
  default_value = "0";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  hs_ = (parameters[parameter_key] == "0" ? false : true);

  parameter_key = "debug";
  default_value = "0";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  debug_ = (parameters[parameter_key] == "0" ? false : true);

  parameter_key = "display-parameters";
  default_value = "0";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  display_parameters_ = (parameters[parameter_key] == "0" ? false : true);

  parameter_key = "negative";
  default_value = "0";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  negative_ = atoi(parameters[ parameter_key ].c_str());

  parameter_key = "save-vocab";
  default_value = "save-vocab.txt";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  save_vocab_file_ = parameters[ parameter_key ];

  parameter_key = "output-file";
  default_value = "output-file.txt";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  output_file_ = parameters[ parameter_key ];

  parameter_key = "output-word-cluster";
  default_value = "output-word-cluster.txt";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  output_word_cluster_ = parameters[ parameter_key ];

  if (display_parameters_) {
    fprintf(stderr, "Word2Vector, liqiangneu@gmail.com\n");
    fprintf(stderr, "Parameters\n");
    fprintf(stderr, "%+20s  %-10d\n", "max-string", max_string_);
    fprintf(stderr, "%+20s  %-10d\n", "exp-table-size", exp_table_size_);
    fprintf(stderr, "%+20s  %-10d\n", "max-exp", max_exp_);
    fprintf(stderr, "%+20s  %-10d\n", "max-sentence-length", max_sentence_length_);
    fprintf(stderr, "%+20s  %-10d\n", "max-code-length", max_code_length_);
    fprintf(stderr, "%+20s  %-10d\n", "size", layer1_size_);
    fprintf(stderr, "%+20s  %-10d\n", "min-count", min_count_);
    fprintf(stderr, "%+20s  %-10d\n", "window", window_);
    fprintf(stderr, "%+20s  %-10f\n", "sample", sample_);
    fprintf(stderr, "%+20s  %-10f\n", "alpha", alpha_);
    fprintf(stderr, "%+20s  %-10s\n", "model", model_ == 1 ? "Skip-Gram" : "CBOW");
    fprintf(stderr, "%+20s  %-10d\n", "classes", classes_);
    fprintf(stderr, "%+20s  %-10d\n", "threads-number", threads_number_);
    fprintf(stderr, "%+20s  %-10s\n", "binary", binary_ ? "true" : "false");
    fprintf(stderr, "%+20s  %-10s\n", "hs", hs_ ? "true" : "false");
    fprintf(stderr, "%+20s  %-10d\n", "negative", negative_);
    fprintf(stderr, "%+20s  %-10s\n", "debug", debug_ ? "true" : "false");
    fprintf(stderr, "%+20s  %-10s\n", "save-vocab", save_vocab_file_.c_str());
    fprintf(stderr, "%+20s  %-10s\n", "output-file", output_file_.c_str());
    fprintf(stderr, "%+20s  %-10s\n", "output-word-cluster", output_word_cluster_.c_str());
    fflush(stderr);
  }
  return true;
}


/*
 * $Name: CheckParamsInConfig
 * $Function: Check the parameters in configuration file.
 * $Date: 2014-07-09
 */
bool Configuration::CheckEachParamInConfig(map<string, string> &parameters, string &parameter_key, string &default_value) {
#ifdef __DEBUG_CONFIGURATION__
    cerr<<"Configuration::CheckEachParamInConfig...\n"<<flush;
#endif
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
  string file_key = "read-vocab-file";
  if (parameters[file_key] != "") {
    CheckEachFileInConfig(parameters, file_key);
    read_vocab_file_ = parameters[file_key];
    if (display_parameters_) {
      fprintf(stderr, "%+20s  %-10s\n", "read-vocab-file", read_vocab_file_.c_str());
      fflush(stderr);
    }
  }

  file_key = "train-file";
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


/*
 * $Name: TrainModel
 * $Function: Train word2vector model.
 * $Date: 2014-07-09
 */
bool Word2Vector::TrainModel(map<string, string> &parameters) { 
  config_.Init(parameters);
  PreComputeExpTable();

  if (config_.read_vocab_file_ != "") {
    ReadVocab();
  } else {
    LearnVocabFromTrainFile();
  }

  InitNet();
  if (config_.negative_ > 0) {
    InitUnigramTable();
  }

  config_.start = clock();

  vector<Word2VectorTrainingThread> word2vector_training_thread;
  word2vector_training_thread.resize(config_.threads_number_);
  if (config_.display_parameters_) {
    fprintf(stderr, "\nTraining ...\n");
    fflush(stderr);
  }
  for (int i = 0; i < config_.threads_number_; ++i) {
    word2vector_training_thread.at(i).id_ = i;
    word2vector_training_thread.at(i).word2vector_ = this;
    word2vector_training_thread.at(i).Start();
  }
  for (int i = 0; i < config_.threads_number_; ++i) {
    word2vector_training_thread.at(i).Join();
  }

  if (config_.display_parameters_) {
    fprintf(stderr, "\n\nFinally ...\n");
    fflush(stderr);
  }
  if (config_.binary_) {
    OutputModelBinary();
  } else {
    OutputModel();
  }
  if (config_.classes_ > 0 ){
    KMeansClustering();
    OutputKMeansClustering();
  }

  cerr<<"\n"<<flush;

  return true;
}


/*
bool Word2Vector::ComputeTrainFileSize() { 
  FILE *fi = fopen(config_.train_file_.c_str(), "rb");
  if (fi==NULL) {
    cerr<<"ERROR: Training file'"<<config_.train_file_<<"' not found.\n"<<flush;
    exit(1);
  }
  fseek(fi, 0, SEEK_END);
  config_.train_file_size_ = ftell(fi);
#ifdef __DEBUG_WORD2VECTOR__
  cerr<<"train_file_size="<<config_.train_file_size_<<"\n"<<flush;
#endif
  return true;
}
*/


/*
 * $Name: TrainCbowModelThread
 * $Function: Train.cbow model thread
 * $Date: 2014-09-11
 */
void Word2Vector::TrainCbowModelThread(int &id) { 
  clock_t now;
  FILE *fi = fopen(config_.train_file_.c_str(), "rb");
  if (fi==NULL) {
    cerr<<"ERROR: Training file'"<<config_.train_file_<<"' not found.\n"<<flush;
    exit(1);
  }

  long long seek_position = config_.train_file_size_ / (long long)config_.threads_number_ * (long long)id;
  fseek(fi, (long)seek_position, SEEK_SET);

  long long word_count = 0;
  long long last_word_count = 0;
  long long sentence_length = 0;
  long long sentence_position = 0;
  long long word_index, last_word_index;
  long long a, b, d;
  long long c;
  long long l1, l2;
  long long target, label;
  float f, g;
  unsigned long long next_random = (unsigned long long)id;
  vector<long long> sen(config_.max_sentence_length_, 0);
  vector<float> neu1(config_.layer1_size_, 0);
  vector<float> neu1e(config_.layer1_size_, 0);

  while (1) {
    if (word_count - last_word_count > 10000) {
      config_.word_count_actual_ += word_count - last_word_count;
      last_word_count = word_count;

      now = clock();
      if (config_.display_parameters_) {
        /*
        cerr <<"\rAlpha: "<<config_.alpha_
             <<" Progress: "<< config_.word_count_actual_ / (float)(config_.train_words_ + 1) * 100
             <<"% Words/thread/sec: "<< config_.word_count_actual_ / ((float)(now - config_.start + 1) / (float)CLOCKS_PER_SEC * 1000)<<"k"
             <<flush;
        */
        fprintf(stderr, "\r  Thread-id=%d(of %d)  Alpha=%.4f  Progress=%.2f%%  Words/thread/sec=%.2fk   ", id, config_.threads_number_, config_.alpha_, config_.word_count_actual_ / (float)(config_.train_words_ + 1) * 100, config_.word_count_actual_ / ((float)(now - config_.start + 1) / (float)CLOCKS_PER_SEC * 1000));
      }

      config_.alpha_ = config_.starting_alpha_ * (1 - config_.word_count_actual_ / (float)(config_.train_words_ + 1));
      if (config_.alpha_ < config_.starting_alpha_ * 0.0001f) {
        config_.alpha_ = config_.starting_alpha_ * 0.0001f;
      }
    }

    if (sentence_length == 0) {
      while (1) {
        word_index = ReadWordIndex(fi);
        if (feof(fi)) {
          break;
        }
        if (word_index == -1) {
          continue;
        }
        ++word_count;
        if (word_index == 0) {
          break;
        }

        if (config_.sample_ > 0) {
          float random_value = (sqrt(vocab_.at(word_index).count_ / (config_.sample_ * config_.train_words_)) + 1) * \
                               (config_.sample_ * config_.train_words_) / vocab_.at(word_index).count_;
          next_random = next_random * (unsigned long long)25214903917 + 11;
          if (random_value < (next_random & 0xFFFF) / (float)65536) {
            continue;
          }
        }
        sen.at(sentence_length) = word_index;
        ++sentence_length;
        if(sentence_length >= config_.max_sentence_length_) {
          break;
        }
      }
      sentence_position = 0;
    }
    if (feof(fi)) {
      break;
    }

    if (word_count > config_.train_words_ / config_.threads_number_) {
      break;
    }
    word_index = sen.at(sentence_position);
    if (word_index == -1) {
      continue;
    }

    for (c = 0; c < config_.layer1_size_; ++c) {
      neu1.at(c) = 0;
    }
    for (c = 0; c < config_.layer1_size_; ++c) {
      neu1e.at(c) = 0;
    }

    next_random = next_random * (unsigned long long)25214903917 + 11;
    b = next_random % config_.window_;

    // CBOW, Continuous Bag-of-Words Model ////////////
    // in -> hidden
    for (a = b; a < config_.window_ * 2 + 1 - b; ++a) {
      if (a != config_.window_) {
        c = sentence_position - config_.window_ + a;
        if (c < 0) {
          continue;
        }
        if (c >= sentence_length) {
          continue;
        }
        last_word_index = sen.at(c);
        if (last_word_index == -1) {
          continue;
        }
        for (c = 0; c < config_.layer1_size_; ++c) {
          neu1.at(c) += syn0_.at(c + last_word_index * config_.layer1_size_);
        }
      }
    }
    if (config_.hs_) {
      for (d = 0; d < vocab_.at(word_index).codelen_; ++d) {
        f = 0;
        l2 = vocab_.at(word_index).point_.at(d) * config_.layer1_size_;
        // Propagate hidden -> output
        for (c = 0; c < config_.layer1_size_; ++c) {
          f += neu1.at(c) * syn1_.at(c + l2);
        }
        if (f <= -config_.max_exp_) {
          continue;
        } else if (f >= config_.max_exp_) {
          continue;
        } else {
          f = exp_table_.at((int)((f + config_.max_exp_) * (config_.exp_table_size_ / config_.max_exp_ / 2)));
        }
        // 'g' is the gradient multiplied by the learning rate
        if (vocab_.at(word_index).code_.at(d) == '1') {
          g = (1 - 1 - f) * config_.alpha_;
        } else if (vocab_.at(word_index).code_.at(d) == '0') {
          g = (1 - 0 - f) * config_.alpha_;
        }
        // Propagate errors output -> hidden
        for (c = 0; c < config_.layer1_size_; ++c) {
          neu1e.at(c) += g * syn1_.at(c + l2);
        }
        // Learn weights hidden -> output
        for (c = 0; c < config_.layer1_size_; ++c) {
          syn1_.at(c + l2) += g * neu1.at(c);
        }
      }
    }
    
    // Negative Sampling
    if (config_.negative_ > 0) {
      for (d = 0; d < config_.negative_ + 1; ++d) {
        if (d == 0) {
          target = word_index;
          label = 1;
        } else {
          next_random = next_random * (unsigned long long)25214903917 + 11;
          target = table_.at((next_random >> 16) % config_.table_size_);
          if (target == 0) {
            target = next_random % (config_.vocab_size_ - 1) + 1;
          }
          if (target == word_index) {
            continue;
          }
          label = 0;
        }
        l2 = target * config_.layer1_size_;
        f= 0;
        for (c = 0; c < config_.layer1_size_; ++c) {
          f += neu1.at(c) * syn1_negative_.at(c + l2);
        }
        if (f > config_.max_exp_) {
          g = (label - 1) * config_.alpha_;
        } else if (f < -config_.max_exp_) {
          g = (label - 0) * config_.alpha_;
        } else {
          g = (label - exp_table_.at((int)((f + config_.max_exp_) * (config_.exp_table_size_ / config_.max_exp_ / 2)))) * config_.alpha_;
        }
        for (c = 0; c < config_.layer1_size_; ++c) {
          neu1e.at(c) += g * syn1_negative_.at(c + l2);
        }
        for (c = 0; c < config_.layer1_size_; ++c) {
          syn1_negative_.at(c + l2) += g * neu1.at(c);
        }
      }
    }

    // hidden -> in
    for (a = b; a < config_.window_ * 2 + 1 - b; ++a) {
      if (a != config_.window_) {
        c = sentence_position - config_.window_ + a;
        if (c < 0) {
          continue;
        }
        if (c >= sentence_length) {
          continue;
        }
        last_word_index = sen.at(c);
        if (last_word_index == -1) {
          continue;
        }
        for (c = 0; c < config_.layer1_size_; ++c) {
          syn0_.at(c + last_word_index * config_.layer1_size_) += neu1e.at(c);
        }
      }
    }

    ///////////////////////////////////////////////////

    ++sentence_position;
    if (sentence_position >= sentence_length) {
      sentence_length = 0;
      continue;
    }
  }

  fclose(fi);
  neu1.clear();
  neu1e.clear();
  /*
  if (config_.display_parameters_) {
    fprintf(stderr, "\n%+20s  %-10d  Done!\n", "Thread-id", id);
    fflush(stderr);
  }
  */
}


/*
 * $Name: TrainSkipGramModelThread
 * $Function: Train.skip-gram model thread
 * $Date: 2014-09-11
 */
void Word2Vector::TrainSkipGramModelThread(int &id) { 
  clock_t now;
  FILE *fi = fopen(config_.train_file_.c_str(), "rb");
  if (fi==NULL) {
    cerr<<"ERROR: Training file'"<<config_.train_file_<<"' not found.\n"<<flush;
    exit(1);
  }

  long long seek_position = config_.train_file_size_ / (long long)config_.threads_number_ * (long long)id;
  fseek(fi, (long)seek_position, SEEK_SET);

  long long word_count = 0;
  long long last_word_count = 0;
  long long sentence_length = 0;
  long long sentence_position = 0;
  long long word_index, last_word_index;
  long long a, b, d;
  long long c;
  long long l1, l2;
  long long target, label;
  float f, g;
  unsigned long long next_random = (unsigned long long)id;
  vector<long long> sen(config_.max_sentence_length_, 0);
  vector<float> neu1(config_.layer1_size_, 0);
  vector<float> neu1e(config_.layer1_size_, 0);

  while (1) {
    if (word_count - last_word_count > 10000) {
      config_.word_count_actual_ += word_count - last_word_count;
      last_word_count = word_count;

      now = clock();
      if (config_.display_parameters_) {
        /*
        cerr<<"\rAlpha: "<<config_.alpha_
            <<" Progress: "<<config_.word_count_actual_ / (float)(config_.train_words_ + 1) * 100
            <<"% Words/thread/sec:"<< config_.word_count_actual_ / ((float)(now - config_.start + 1) / (float)CLOCKS_PER_SEC * 1000)<<"k"
            <<flush;
        */
        fprintf(stderr, "\r  Thread-id=%d(of %d)  Alpha=%.4f  Progress=%.2f%%  Words/thread/sec=%.2fk   ", id, config_.threads_number_, config_.alpha_, config_.word_count_actual_ / (float)(config_.train_words_ + 1) * 100, config_.word_count_actual_ / ((float)(now - config_.start + 1) / (float)CLOCKS_PER_SEC * 1000));
      }
      config_.alpha_ = config_.starting_alpha_ * (1 - config_.word_count_actual_ / (float)(config_.train_words_ + 1));
      if (config_.alpha_ < config_.starting_alpha_ * 0.0001f) {
        config_.alpha_ = config_.starting_alpha_ * 0.0001f;
      }
    }

    if (sentence_length == 0) {
      while (1) {
        word_index = ReadWordIndex(fi);
        if (feof(fi)) {
          break;
        }
        if (word_index == -1) {
          continue;
        }
        ++word_count;
        if (word_index == 0) {
          break;
        }

        if (config_.sample_ > 0) {
          float random_value = (sqrt(vocab_.at(word_index).count_ / (config_.sample_ * config_.train_words_)) + 1) * \
                               (config_.sample_ * config_.train_words_) / vocab_.at(word_index).count_;
          next_random = next_random * (unsigned long long)25214903917 + 11;
          if (random_value < (next_random & 0xFFFF) / (float)65536) {
            continue;
          }
        }
        sen.at(sentence_length) = word_index;
        ++sentence_length;
        if(sentence_length >= config_.max_sentence_length_) {
          break;
        }
      }
      sentence_position = 0;
    }
    if (feof(fi)) {
      break;
    }

    if (word_count > config_.train_words_ / config_.threads_number_) {
      break;
    }
    word_index = sen.at(sentence_position);
    if (word_index == -1) {
      continue;
    }

    for (c = 0; c < config_.layer1_size_; ++c) {
      neu1.at(c) = 0;
    }
    for (c = 0; c < config_.layer1_size_; ++c) {
      neu1e.at(c) = 0;
    }

    next_random = next_random * (unsigned long long)25214903917 + 11;
    b = next_random % config_.window_;

    // Continuous Skip-gram Model /////////////////////
    for (a = b; a < config_.window_ * 2 + 1 - b; ++a) {
      if (a != config_.window_) {
        c = sentence_position - config_.window_ + a;
        if (c < 0) {
          continue;
        }
        if (c >= sentence_length) {
          continue;
        }
        last_word_index = sen.at(c);
        if (last_word_index == -1) {
          continue;
        }

        l1 = last_word_index * config_.layer1_size_;
        for (c = 0; c < config_.layer1_size_; ++c) {
          neu1e[c] = 0;
        }

        // Hierarchical softmax
        if (config_.hs_) {
          for (d = 0; d < vocab_.at(word_index).codelen_; ++d) {
            f = 0;
            l2 = vocab_.at(word_index).point_.at(d) * config_.layer1_size_;
            // Propagate hidden -> output
            for (c = 0; c < config_.layer1_size_; ++c) {
              f += syn0_.at(c + l1) * syn1_.at(c + l2);
            }
            if (f <= -config_.max_exp_) {
              continue;
            } else if (f >= config_.max_exp_) {
              continue;
            } else {
              f = exp_table_.at((int)((f + config_.max_exp_) * (config_.exp_table_size_ / config_.max_exp_ / 2)));
            }

            // 'g' is the gradient multiplied by the learning rate
            if (vocab_.at(word_index).code_.at(d) == '1') {
              g = (1 - 1 - f) * config_.alpha_;
            } else if (vocab_.at(word_index).code_.at(d) == '0') {
              g = (1 - 0 - f) * config_.alpha_;
            }

            // Propagate errors output -> hidden
            for (c = 0; c < config_.layer1_size_; ++c) {
              neu1e.at(c) += g * syn1_.at(c + l2);
            }
            // Learn weights hidden -> output
            for (c = 0; c < config_.layer1_size_; ++c) {
              syn1_.at(c + l2) += g * syn0_.at(c + l1);
            }
          }
        }

        // Negative Sampling
        if (config_.negative_ > 0) {
          for (d = 0; d < config_.negative_ + 1; ++d) {
            if (d == 0) {
              target = word_index;
              label = 1;
            } else {
              next_random = next_random * (unsigned long long)25214903917 + 11;
              target = table_.at((next_random >> 16) % config_.vocab_size_);
              if (target == 0) {
                target = next_random % (config_.vocab_size_ - 1) + 1;
              }
              if (target == word_index) {
                  continue;
              }
              label = 0;
            }
            l2 = target * config_.layer1_size_;
            f = 0;
            for (c = 0; c < config_.layer1_size_; ++c) {
              f += syn0_.at(c + l1) * syn1_negative_.at(c + l2);
            }
            if (f > config_.max_exp_) {
              g = (label - 1) * config_.alpha_;
            } else if (f < -config_.max_exp_) {
              g = (label - 0) * config_.alpha_;
            } else {
              g = (label - exp_table_.at((int)((f + config_.max_exp_) * \
                  (config_.exp_table_size_ / config_.max_exp_ / 2)))) * config_.alpha_;
            }

            for (c = 0; c < config_.layer1_size_; ++c) {
              neu1e.at(c) += g * syn1_negative_.at(c + l2);
            }
            for (c = 0; c < config_.layer1_size_; ++c) {
              syn1_negative_.at(c + l2) += g * syn0_.at(c + l1);
            }
          }
        }

        // Learn weights input -> hidden
        for (c = 0; c < config_.layer1_size_; ++c) {
          syn0_.at(c + l1) += neu1e.at(c);
        }
      }
    }
    ///////////////////////////////////////////////////

    ++sentence_position;
    if (sentence_position >= sentence_length) {
      sentence_length = 0;
      continue;
    }
  }

  fclose(fi);
  neu1.clear();
  neu1e.clear();
  /*
  if (config_.display_parameters_) {
    fprintf(stderr, "\n%+20s  %-10d  Done!\n", "Thread-id", id);
    fflush(stderr);
  }
  */
}


/*
* $Name: PreComputeExpTable
* $Function: Precompute exp_table_.
* $Date: 2014-07-09
*/
bool Word2Vector::PreComputeExpTable() {
  exp_table_.reserve( config_.exp_table_size_ );
  for (int i = 0; i < config_.exp_table_size_; ++i) {
    float precompute_value = exp((i / (float)config_.exp_table_size_ * 2 - 1) * config_.max_exp_);
    precompute_value = precompute_value / (precompute_value + 1);
    exp_table_.push_back(precompute_value);
  }
  return true;
}


/*
 * $Name: ReadVocab
 * $Function: The vocabulary will be read from the inputted vocabulary file, not constructed from the training data.
 * $Date: 2014-07-09
 */
bool Word2Vector::ReadVocab() {
#ifdef __DEBUG_WORD2VECTOR__
  cerr<<"ReadVocab...\n"<<flush;
#endif

  string sentence_tmp;
  ifstream in_file_vocab(config_.read_vocab_file_.c_str());
  if (!in_file_vocab) {
      cerr<<"ERROR: Vocabulary file '"<<config_.read_vocab_file_<<"' not found.\n"<<flush;
      exit(1);
  }
  in_file_vocab.clear();
  in_file_vocab.close();
  return true;
}


/*
 * $Name: SaveVocab
 * $Function: The vocabulary will be saved to file.
 * $Date: 2014-07-09
 */
bool Word2Vector::SaveVocab() {
  if (config_.display_parameters_) {
    fprintf(stderr, "%+20s  %-10s\n", "save-vocab-file", config_.save_vocab_file_.c_str());
    fflush(stderr);
  }
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
 * $Name: ReadWordIndex
 * $Function: Reads a word and returns its index in the vocabulary
 * $Date: 2014-08-28
 */
int Word2Vector::ReadWordIndex(FILE *fin) {
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
void Word2Vector::ReadWord(char *word, FILE *fin) {
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
bool Word2Vector::LearnVocabFromTrainFile() {
  if (config_.display_parameters_) {
    fprintf(stderr, "\nLearning vocabulary from %s\n", config_.train_file_.c_str());
    fflush(stderr);
  }
  vocab_hash_.resize(config_.vocab_hash_size_);

  for (size_t i = 0; i < config_.vocab_hash_size_; ++i) {
    vocab_hash_.at(i) = -1;
  }

  FILE *fin = fopen(config_.train_file_.c_str(), "rb");
  if (fin == NULL) {
    cerr<<"ERROR: Training file '"<<config_.train_file_<<"' not found.\n"<<flush;
    exit(1);
  }

  string word_tmp = "</s>";
  vocab_.reserve((unsigned int)config_.vocab_max_size_);
  AddWordToVocab(word_tmp);

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
      vocab_.at(vocab_size).count_ = 1;
    } else {
      ++vocab_.at(index).count_;
    }

    if (config_.vocab_size_ > config_.vocab_hash_size_ * 0.7) {
      ReduceVocab();
    }
  }
  SortVocab();

  if (config_.save_vocab_file_ != "") {
    SaveVocab();
  }
  config_.train_file_size_ = ftell(fin);
  fclose(fin);
  return true;
}


/*
 * $Name: AddWordToVocab
 * $Function: Add word to vocab vector
 * $Date: 2014-08-25
 */
size_t Word2Vector::AddWordToVocab(string &word) {
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
    config_.vocab_max_size_ += 1000000;
    vocab_.reserve( config_.vocab_max_size_ );
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
size_t Word2Vector::GetWordHash(string &word) {
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
int Word2Vector::SearchVocab(string &word) {
//  string word_string(word);
  size_t hash = GetWordHash(word);
//  cerr<<"searchvocab,hash="<<hash<<"\n"<<flush;
  while (1) {
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
bool Word2Vector::ReduceVocab() {
  unsigned int hash;
  int j = 0;
  for (int i = 0; i < config_.vocab_size_; ++i) {
    if (vocab_.at(i).count_ > config_.min_reduce_) {
      vocab_.at(j).count_ = vocab_.at(i).count_;
      vocab_.at(j).word_ = vocab_.at(i).word_;
      ++j;
    }
  }
  config_.vocab_size_ = j;
  vocab_.resize(config_.vocab_size_);

  for (int i = 0; i < config_.vocab_hash_size_; ++i) {
    vocab_hash_.at(i) = -1;
  }

  for (int i = 0; i < config_.vocab_size_; ++i) {
    hash = GetWordHash(vocab_[i].word_);
    while (vocab_hash_[hash] != -1) {
      hash = (hash + 1) % config_.vocab_hash_size_;
    }
    vocab_hash_[hash] = i;
  }
  ++config_.min_reduce_;
  return true;
}


/*
 * $Name: SortVocab
 * $Function: Sorts the vocabulary by frequency using word counts
 * $Date: 2014-08-26
 */
bool Word2Vector::SortVocab() {
  sort(vocab_.begin() + 1, vocab_.end(), VocabCompare);

  for (int i = 0; i < config_.vocab_hash_size_; ++i) {
    vocab_hash_.at(i) = -1;
  }

  int size = config_.vocab_size_;
  size_t hash = 0;
  config_.train_words_ = 0;
  for (int i = 0; i < size; ++i) {
    if ((i > 0) && (vocab_.at(i).count_ < config_.min_count_)) {
      config_.vocab_size_ = i;
      vocab_.resize( config_.vocab_size_);
      break;
    } else {
      hash = GetWordHash(vocab_[i].word_);
      while (vocab_hash_[hash] != -1) {
        hash = (hash + 1) % config_.vocab_hash_size_;
      }
      vocab_hash_[hash] = i;
      config_.train_words_ += vocab_.at(i).count_;
    }
  }

  if (config_.display_parameters_) {
    fprintf(stderr, "%+20s  %-10d\n%+20s  %-10d\n", "vocab-size", config_.vocab_size_, "train-words", config_.train_words_);
    fflush(stderr);
  }
  return true;
}


// Used later for sorting by word counts
bool VocabCompare(const VocabWord &a, const VocabWord &b) {
    return b.count_ < a.count_;
}


/*
* $Name: InitNet
* $Function: Init net
* $Date: 2014-08-26
*/
bool Word2Vector::InitNet() {
  syn0_.resize((long long)config_.vocab_size_ * config_.layer1_size_);
  long long syn1_size = config_.layer1_size_ * config_.vocab_size_;
  if (config_.hs_) {
/*
    for (long long i = 0; i < config_.layer1_size_; ++i) {
      for (long long j = 0; j < config_.vocab_size_; ++j) {
        syn1.at(j * config_.layer1_size_ + i) = 0;
      }
    }
*/
    syn1_.resize((long long)config_.vocab_size_ * config_.layer1_size_);
    for (long long i = 0; i < syn1_size; ++i) {
      syn1_.at(i) = 0;
    }
  }

  if (config_.negative_ > 0) {
    syn1_negative_.resize((long long)config_.vocab_size_ * config_.layer1_size_);
    for (long long i = 0; i < syn1_size; ++i) {
      syn1_negative_.at(i) = 0;
    }
  }

  /*
  for (long long i = 0; i < config_.layer1_size_; ++i) {
    for (long long j = 0; j < config_.vocab_size_; ++j) {
      syn0.at(j * config_.layer1_size_ + i) = (rand() / (float)RAND_MAX - 0.5) / config_.layer1_size_;
    }
  }
  */

  for (long long i = 0; i < syn1_size; ++i) {
    syn0_.at(i) = (float)(rand() / (float)RAND_MAX - 0.5) / config_.layer1_size_;
//      syn0.at(i) = (float)(1 / (float)RAND_MAX - 0.5) / config_.layer1_size_;
  }
  CreateBinaryTree();
  return true;
}

/*
 * $Name: CreateBinaryTree
 * $Function: Create binary Huffman tree using the word counts, 
 *            frequent words will have short uniqe binary codes.
 * $Date: 2014-08-26
 */
bool Word2Vector::CreateBinaryTree() {
  long long count_vector_size = config_.vocab_size_ * 2;
  vector<long long> count(count_vector_size);
  for (long long i = 0; i < config_.vocab_size_; ++i) {
    count.at(i) = vocab_.at(i).count_;
  }
  long long pre_define_value = (long long)1e15;
  for (long long i = config_.vocab_size_; i < count_vector_size; ++i) {
    count.at(i) = pre_define_value;
  }

  vector<long long> binary(count_vector_size, 0);
  vector<long long> parent_node(count_vector_size);

  // Following algorithm constructs the Huffman tree by adding one node at a time
  long long pos1 = config_.vocab_size_ - 1;
  long long pos2 = config_.vocab_size_;
  long long min1i = 0, min2i = 0;
  for (long long i = 0; i < config_.vocab_size_ - 1; ++i) {
    // First, find two smallest nodes 'min1, min2'
    if (pos1 >= 0) {
      if (count.at(pos1) < count.at(pos2)) {
        min1i = pos1;
        --pos1;
      } else {
        min1i = pos2;
        ++pos2;
      }
    } else {
      min1i = pos2;
      ++pos2;
    }

    if (pos1 >= 0) {
      if (count.at(pos1) < count.at(pos2)) {
        min2i = pos1;
        --pos1;
      } else {
        min2i = pos2;
        ++pos2;
      }
    } else {
      min2i = pos2;
      ++pos2;
    }
    
    count.at(config_.vocab_size_ + i) = count.at(min1i) + count.at(min2i);
    parent_node.at(min1i) = config_.vocab_size_ + i;
    parent_node.at(min2i) = config_.vocab_size_ + i;
    binary.at(min2i) = 1;
  }

  // Now assign binary code to each vocabulary word
  vector<int> code;
  vector<long long> point;
  code.reserve(config_.max_code_length_);
  point.reserve(config_.max_code_length_);

  for (long long i = 0; i < config_.vocab_size_; ++i) {
    long long j = i;
    long long k = 0;
    point.clear();
    code.clear();
    while (1) {
      code.push_back(binary.at(j));
      point.push_back(j);
      ++k;
      j = parent_node.at(j);
      if (j == config_.vocab_size_ * 2 - 2) {
        break;
      }
    }
    vocab_.at(i).codelen_ = k;
    vocab_.at(i).point_.resize(k + 1);
    vocab_.at(i).point_.at(0) = config_.vocab_size_ - 2;
    vocab_.at(i).code_.resize(k);
    for (j = 0; j < k; ++j) {
      //vocab_.at(i).code_.at(k - j - 1) = code.at(j);
      if (code.at(j) == 1) {
        vocab_.at(i).code_.at(k - j - 1) = '1';
      } else {
        vocab_.at(i).code_.at(k - j - 1) = '0';
      }
      vocab_.at(i).point_.at(k - j) = point.at(j) - (long long)config_.vocab_size_;
#ifdef __DEBUG_WORD2VECTOR__
//      cerr<<"point["<<j<<"]="<<point.at(j)<<" ";
#endif
    }
/*
#ifdef __DEBUG_WORD2VECTOR__
    cerr<<"\n"<<flush;
    cerr<<"vocab="<<vocab_.at(i).word_<<" "<<vocab_.at(i).count_<<" "<<vocab_.at(i).code_<<" "<<vocab_.at(i).codelen_<<"\n"<<flush;
    for (vector<long long>::iterator iter = vocab_.at(i).point_.begin(); iter != vocab_.at(i).point_.end(); ++iter) {
      cerr<<*iter<<" ";
    }
    cerr<<"\n\n"<<flush;
#endif
*/
  }
  return true;
}

/*
* $Name: InitUnigramTable
* $Function: 
* $Date: 2014-08-27
*/
bool Word2Vector::InitUnigramTable() {
  long long train_words_pow = 0;
  float d1, power = 0.75;

  table_.resize(config_.table_size_);

  for (int i = 0; i < config_.vocab_size_; ++i) {
    train_words_pow += (long long)pow((float)vocab_.at(i).count_, power);
  }

  int j = 0;
  d1 = pow(vocab_.at(j).count_, power) / (float)train_words_pow;

  for (int i = 0; i < config_.table_size_; ++i) {
    table_.at(i) = j;
    if (i / (float)config_.table_size_ > d1) {
      ++j;
      d1 += pow(vocab_.at(j).count_, power) / (float)train_words_pow;
    }
    if (j >= config_.vocab_size_) {
      j = config_.vocab_size_ - 1;
    }
  }
  return true;
}

/*
 * $Name: KMeansClustering
 * $Function: Run K-means on the word vectors
 * $Date: 2014-08-29
 */
bool Word2Vector::KMeansClustering() {
  int clusters_count = config_.classes_;
  int iterator_count = 10;

  vector<int> centroids_count(clusters_count, 1);
//  vector<int> vocabs_cluster_id(config_.vocab_size_, 0);
  vocab_cluster_id_.resize(config_.vocab_size_, 0);
  
  float close_v, x;
  int close_id;
  vector<float> centroids(clusters_count * config_.layer1_size_, 0);

  for (int i = 0; i < config_.vocab_size_; ++i) {
    vocab_cluster_id_.at(i) = i % clusters_count;
  }

  for (int i = 0; i < iterator_count; ++i) {
    for (int j = 0; j < clusters_count * config_.layer1_size_; ++j) {
      centroids.at(j) = 0;
    }
    for (int j = 0; j < clusters_count; ++j) {
      centroids_count.at(j) = 1;
    }
    for (int k = 0; k < config_.vocab_size_; ++k) {
      for (int l = 0; l < config_.layer1_size_; ++l) {
        centroids.at(vocab_cluster_id_.at(k) * config_.layer1_size_ + l) += syn0_.at(k + config_.layer1_size_ + l);
      }
      ++centroids_count.at(vocab_cluster_id_.at(k)); // warning ? +1
    }

    for (int j = 0; j < clusters_count; ++j) {
      close_v = 0;
      for (int k = 0; k < config_.layer1_size_; ++k) {
        centroids.at(j * config_.layer1_size_ + k) /= centroids_count.at(j); // warning ? +1
        close_v += centroids.at(j * config_.layer1_size_ + k) * centroids.at(j * config_.layer1_size_ + k);
      }
      close_v = sqrt(close_v);
      for (int k = 0; k < config_.layer1_size_; ++k) {
        centroids.at( j * config_.layer1_size_ + k) /= close_v;
      }
    }

    for (int k = 0; k < config_.vocab_size_; ++k) {
      close_v = -10;
      close_id = 0;
      for (int j = 0; j < clusters_count; ++j) {
        x = 0;
        for (int l = 0; l < config_.layer1_size_; ++l) {
          x += centroids.at(j * config_.layer1_size_ + l) * syn0_.at(k * config_.layer1_size_ + l);
        }
        if (x > close_v) {
          close_v = x;
          close_id = j;
        }
      }
      vocab_cluster_id_.at(k) = close_id;
    }
  }
  return true;
}


/*
 * $Name: OutputKMeansClustering
 * $Function: Output word clustering computed by K-Means method
 * $Date: 2014-08-30
 */
bool Word2Vector::OutputKMeansClustering() {
  cerr<<"output_word_cluster="<<config_.output_word_cluster_<<"\n"<<flush;
  ofstream out_word_cluster(config_.output_word_cluster_.c_str());
  if (!out_word_cluster) {
    cerr<<"ERROR: Output file'"<<config_.output_word_cluster_<<"' can not be opened.\n"<<flush;
    exit(1);
  }
  for (int i = 0; i < config_.vocab_size_; ++i) {
    out_word_cluster<<vocab_.at(i).word_<<" "<<vocab_cluster_id_.at(i)<<"\n";
  }
  out_word_cluster.close();
  return true;
}



/*
 * $Name: OutputModel
 * $Function: Output model
 * $Date: 2014-08-27
 */
bool Word2Vector::OutputModel() {
  if (config_.display_parameters_) {
    fprintf(stderr, "%+20s  %-10s", "output-file", config_.output_file_.c_str());
    fflush(stderr);
  }
  ofstream out_file(config_.output_file_.c_str());
  if (!out_file) {
    cerr<<"ERROR: Output file'"<<config_.output_file_<<"' can not be opened.\n"<<flush;
    exit(1);
  }

  // Save the word vectors
  out_file<<config_.vocab_size_<<" "<<config_.layer1_size_<<"\n";
  for (int i = 0; i < config_.vocab_size_; ++i) {
    out_file<<vocab_.at(i).word_;
    if (config_.binary_) {

    } else {
      for (int j = 0; j < config_.layer1_size_; ++j) {
        out_file<<" "<<syn0_.at(i * config_.layer1_size_ + j);
      }
      out_file<<"\n";
    }
  }
  out_file.close();
  return true;
}


/*
 * $Name: OutputModelBinary
 * $Function: Output model binary
 * $Date: 2014-08-30
 */
bool Word2Vector::OutputModelBinary() {
  string vocab_file = config_.output_file_ + ".vocab";
  string binary_file = config_.output_file_ + ".binary";

  ofstream out_vocab_file(vocab_file.c_str());
  if (!out_vocab_file) {
    cerr<<"ERROR: Output file'"<<vocab_file<<"' can not be opened.\n"<<flush;
    exit(1);
  }

  ofstream out_binary_file(binary_file.c_str(), ios::binary);
  if (!out_binary_file) {
    cerr<<"ERROR: Output file'"<<binary_file<<"' can not be opened.\n"<<flush;
    exit(1);
  }

  if (config_.display_parameters_) {
    fprintf(stderr, "%+20s  %-10s\n", "model-vocab", vocab_file.c_str());
    fprintf(stderr, "%+20s  %-10s\n", "model-binary", binary_file.c_str());
    fflush(stderr);
  }

  out_vocab_file<<config_.vocab_size_<<" "<<config_.layer1_size_<<"\n";
  for (int i = 0; i < config_.vocab_size_; ++i) {
    out_vocab_file<<vocab_.at(i).word_<<"\n";
    for (int j = 0; j < config_.layer1_size_; ++j) {
      out_binary_file.write(reinterpret_cast<char *>(&syn0_.at(i * config_.layer1_size_ + j)), sizeof(float));
    }
  }

  out_vocab_file.close();
  out_binary_file.close();
  return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * $Name: Start
 * $Function: Start multi threads
 * $Date: 2014-09-12
 */
void Word2VectorTrainingThread::Start() {
#ifdef HAVE_PTHREAD_H
  pthread_create( &hnd_, 0, &Word2VectorTrainingThread::Wrapper, static_cast<void *>(this) );
#else
#ifdef _WIN32
  DWORD dword_id;
  hnd_ = BEGINTHREAD(0, 0, &Word2VectorTrainingThread::Wrapper, this, 0, &dword_id );
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
void *Word2VectorTrainingThread::TrainModelThread() { 
  if (word2vector_->config_.model_ == 0) {             // train the cbow architecture
    word2vector_->TrainCbowModelThread(id_);
  } else if (word2vector_->config_.model_ == 1) {      // train the skip-gram architecture
    word2vector_->TrainSkipGramModelThread(id_);
  }
  return 0;
}




}