/*
 * $Id:
 * 0020
 *
 * $File:
 * analogy.cpp
 *
 * $Proj:
 * WordRepresentation
 *
 * $Func:
 * analogy
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
 * 2014-09-02, 12:56
 */

#include "analogy.h"

namespace word_representation_analogy {

bool Analogy::StartAnalogy(map<string, string> &parameters) {
  cerr<<"Start Analogy...\n"<<flush;
  model_.Init(parameters);

  float length = 0;
  for (long long i = 0; i < model_.words_count_; ++i) {
    length = 0;
    for (long long j = 0; j < model_.feature_size_; ++j) {
      length += model_.model_.at(i * model_.feature_size_ + j) * model_.model_.at(i * model_.feature_size_ + j);
    }
    length = sqrt(length);
    for (long long j = 0; j < model_.feature_size_; ++j) {
      model_.model_.at(i * model_.feature_size_ + j) /= length;
    }
  }

  vector<float> best_distance(closest_word_number);
  vector<string> best_word(closest_word_number);
  vector<string> word_vector;
  float distance = 0;
  vector<float> feature_score(model_.feature_size_, 0);
  string input_string;
  long long count;
  while (1) {
    for (long long i = 0; i < closest_word_number; ++i) {
      best_distance.at(i) = 0;
    }

    for (long long i = 0; i < closest_word_number; ++i) {
      best_word.at(i).clear();
    }
    
    cerr<<"Enter three words (EXIT to break): ";
    long long i = 0;
    getline(cin, input_string);
    ClearIllegalChar(input_string);
    RmEndSpace(input_string);
    RmStartSpace(input_string);
    cerr<<"input_string="<<input_string<<"\n"<<flush;

    if (input_string == "EXIT") {
      break;
    }
    word_vector.clear();
    Split(input_string, ' ', word_vector);
    count = word_vector.size();
    if (count != 3) {
      cerr<<count<<" words were entered, three words are needed at the input to perform the calculation\n"<<flush;
      continue;
    }

    vector<long long> word_position(word_vector.size(), -1);
    bool continue_flag = false;
    for (size_t i = 0; i < word_position.size(); ++i) {
      for (long long j = 0; j < model_.words_count_; ++j) {
        if (model_.vocab_.at(j) == word_vector.at(i)) {
          word_position.at(i) = j;
          break;
        }
      }

      cerr<<"\nWord: "<<word_vector.at(i)<<"  Position in vocabulary: "<<word_position.at(i)<<"\n"<<flush;
      if (word_position.at(i) == -1) {
        cerr<<"Out of dictionary word!\n";
        continue_flag = true;
        break;
      }
    }

    if (continue_flag) {
      continue;
    }

    cerr<<"\n                                              Word       Cosine distance"
        <<"\n------------------------------------------------------------------------\n";

    for (long long i = 0; i < model_.feature_size_; ++i) {
      feature_score.at(i) = (model_.model_.at(word_position.at(1) * model_.feature_size_ + i) - \
                             model_.model_.at(word_position.at(0) * model_.feature_size_ + i) + 
                             model_.model_.at(word_position.at(2) * model_.feature_size_ + i));
    }
    length = 0;
    for (long long i = 0; i < model_.feature_size_; ++i) {
      length += feature_score.at(i) * feature_score.at(i);
    }
    length = sqrt(length);

    for (long long i = 0; i < model_.feature_size_; ++i) {
      feature_score.at(i) /= length;
    }

    for (long long i = 0; i < closest_word_number; ++i) {
      best_distance.at(i) = 0;
    }
    for (long long i = 0; i < closest_word_number; ++i) {
      best_word.at(i).clear();
    }

    for (long long i = 0; i < model_.words_count_; ++i) {
      if (word_position.at(0) == i) {
        continue;
      }
      if (word_position.at(1) == i) {
        continue;
      }
      if (word_position.at(2) == i) {
        continue;
      }

      distance = 0;
      for (long long j = 0; j < model_.feature_size_; ++j) {
        distance += feature_score.at(j) * model_.model_.at(i * model_.feature_size_ + j);
      }

      for (long long j = 0; j < closest_word_number; ++j) {
        if (distance > best_distance.at(j)) {
          for (long long k = closest_word_number - 1; k > j; --k) {
            best_distance.at(k) = best_distance.at(k - 1);
            best_word.at(k) = best_word.at(k - 1);
          }
          best_distance.at(j) = distance;
          best_word.at(j) = model_.vocab_.at(i);
          break;
        }
      }
    }

    for (long long i = 0; i < closest_word_number; ++i) {
        cerr<<"                                        "<<i<<"   "<<best_word.at(i)<<"\t\t"<<best_distance.at(i)<<"\n"<<flush;
    }
  }
  return true;
}

}


