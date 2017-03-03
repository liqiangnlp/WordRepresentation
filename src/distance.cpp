/*
* $Id:
* 0014
*
* $File:
* distance.cpp
*
* $Proj:
* WordRepresentation
*
* $Func:
* distance
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
* 2014-08-30, 18:51
*/

#include "distance.h"

namespace word_representation_distance {

/*
 * $Name: ComputeDistance
 * $Function: Compute distance
 * $Date: 2014-08-30
 */
bool Distance::ComputeDistance(map<string,string> &parameters) {
  cerr<<"ComputeDistance\n"<<flush;
  model_.Init(parameters);
  
  ComputeCosineDistance();
  return true;
}


/*
 * $Name: ComputeCosineDistance
 * $Function: Compute consine distance
 * $Date: 2014-08-31
 */
bool Distance::ComputeCosineDistance() {
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
  vector<string> words;
  vector<long long> word_position;
  string input_string;
  long long count;
  float distance;
  vector<float> feature_score;
  while (1) {
    for (long long i = 0; i < closest_word_number; ++i) {
      best_distance.at(i) = 0;
    }

    for (long long i = 0; i < closest_word_number; ++i) {
      best_word.at(i).clear();
    }
    
    cerr<<"Enter word or sentence (EXIT to break): ";
    long long i = 0;
    getline(cin, input_string);
    ClearIllegalChar(input_string);
    RmEndSpace(input_string);
    RmStartSpace(input_string);
    cerr<<"input_string="<<input_string<<"\n"<<flush;

    if (input_string == "EXIT") {
      break;
    }
    words.clear();
    Split(input_string, ' ', words);
    count = words.size();
    word_position.resize(count, 0);
    cerr<<"count="<<count<<"\n"<<flush;

    long long j;
    for (long long i = 0; i < count; ++i) {
      for (j = 0; j < model_.words_count_; ++j) {
        if (model_.vocab_.at(j) == words.at(i)) {
          break;
        }
      }
      if (j == model_.words_count_) {
        j = -1;
      }
      word_position.at(i) = j;
      cerr<<"\nWord: "<<words.at(i)<<"  Position in vocabulary: "<<word_position.at(i)<<"\n";

      if (j == -1) {
        cerr<<"Out of dictionary word!\n";
        break;
      }
    }

    if (j == -1) {
      continue;
    }
    cerr<<"\n                                              Word       Cosine distance"
        <<"\n------------------------------------------------------------------------\n";

    feature_score.resize(model_.feature_size_, 0);
    for (long long i = 0; i < model_.feature_size_; ++i) {
      feature_score.at(i) = 0;
    }
    for (long long i = 0; i < count; ++i) {
      if (word_position.at(i) == -1) {
        continue;
      }
      for (long long j = 0; j < model_.feature_size_; ++j) {
//        cerr<<vocab_.at(word_position.at(i))<<" "<<word_position.at(i)<<" "<<j<<" "<<model_.at(word_position.at(i) * feature_size_ + j)<<" "<<feature_score.at(j)<<"\n"<<flush;
        feature_score.at(j) += model_.model_.at(word_position.at(i) * model_.feature_size_ + j);
      }
    }
    length = 0;
    for (long long i = 0; i < model_.feature_size_; ++i) {
      length += feature_score.at(i) * feature_score.at(i);
    }
    length = sqrt(length);                   // length = count
    cerr<<"length="<<length<<"\n"<<flush;

    for (long long i = 0; i < model_.feature_size_; ++i) {
      feature_score.at(i) /= length;
    }

    for (long long i = 0; i < closest_word_number; ++i) {
      best_distance.at(i) = -1;
    }

    for (long long i = 0; i < closest_word_number; ++i) {
      best_word.at(i).clear();
    }

    for (long long i = 0; i < model_.words_count_; ++i) {
      long long j = 0;
      for (long long k = 0; k < count; ++k) {
        if (word_position.at(k) == i) {
          j = 1;
        }
      }
      if (j == 1) {
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


