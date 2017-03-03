/*
 * $Id:
 * 0018
 *
 * $File:
 * accuracy.cpp
 *
 * $Proj:
 * WordRepresentation
 *
 * $Func:
 * compute accuracy
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
 * 2014-09-01, 10:55
 */

#include "accuracy.h"

namespace word_representation_accuracy {

bool Accuracy::ComputeAccuracy(map<string, string> &parameters) {
  cerr<<"Compute Accuracy...\n"<<flush;
  model_.Init(parameters);
  Init(parameters);

  if (threadhold_) {
    if (model_.words_count_ > threadhold_) {
      model_.words_count_ = threadhold_;
      model_.vocab_.resize(model_.words_count_);
      model_.model_.resize(model_.words_count_ * model_.feature_size_);
    }
  }

  for (long long i = 0; i < model_.words_count_; ++i) {
    for (string::iterator iter = model_.vocab_.at(i).begin(); iter != model_.vocab_.at(i).end(); ++iter) {
      if (islower((unsigned char)*iter)) {
        *iter = toupper((unsigned char)*iter);
      }
    }
  }

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

  ifstream in_question(question_file_.c_str());
  if (!in_question) {
    cerr<<"Error: Question file'"<<question_file_<<"' not found.\n"<<flush;
    exit(1);
  }

  string sentence = "";
  int question_id = 0;
  int this_correct_count = 0, this_total_count = 0;
  int total_correct_count = 0, total_count = 0;
  int semantic_correct_count = 0, semantic_total_count = 0;
  int syntactic_correct_count = 0, syntactic_total_count = 0;
  int seen_question = 0;
  int total_question = 0;
  float distance = 0;
  vector<float> feature_score(model_.feature_size_, 0);


  int sentence_number = 0;
  clock_t start = clock();
  clock_t end;
  while (getline(in_question, sentence)) {
    ++sentence_number;
    if (sentence_number % 1000 == 0) {
      end = clock();
      cerr<<"\r  Process "<<sentence_number<<" lines. "
          <<(sentence_number / ((float)(end - start + 1) / (float)CLOCKS_PER_SEC))<<" sent / s"
          <<flush;
    }
    ClearIllegalChar(sentence);
    RmEndSpace(sentence);
    RmStartSpace(sentence);
    if (sentence == "") {
      continue;
    }

/*
    for (long long i = 0; i < closest_word_number; ++i) {
      best_distance.at(i) = 0;
    }
    for (long long i = 0; i < closest_word_number; ++i) {
      best_word.at(i).clear();
    }
*/

    for (string::iterator iter = sentence.begin(); iter != sentence.end(); ++iter) {
      if (islower((unsigned char)*iter)) {
        *iter = toupper((unsigned char)*iter);
      }
    }

    vector<string> word_vector;
    Split(sentence, ' ', word_vector);

    if (word_vector.at(0) == ":") {
      if (total_count == 0) {
        total_count = 1;
      }
      if (question_id != 0) {
        cerr<<"\rACCURACY TOP1: "<<this_correct_count / (float)this_total_count * 100<<" % ("<<this_correct_count<<" / "<<this_total_count<<")"<<
            "              \n";
        cerr<<"Total accuracy: "<<total_correct_count / (float)total_count * 100<<" %   "
            <<"Semantic accuracy: "<<semantic_correct_count / (float)semantic_total_count * 100<<" %   "
            <<flush;
        if (syntactic_total_count == 0) {
          cerr<<"\n"
              <<flush;
        } else {
          cerr<<"Syntactic accuracy: "<<syntactic_correct_count / (float)syntactic_total_count * 100<<" %\n"
              <<flush;
        }
      }
      ++question_id;
      cerr<<sentence<<"                   \n"<<flush;
      this_correct_count = 0;
      this_total_count = 0;
      continue;
    }

    vector<long long> word_position(word_vector.size(), -1);
    for (size_t i = 0; i < word_position.size(); ++i) {
      for (long long j = 0; j < model_.words_count_; ++j) {
        if (model_.vocab_.at(j) == word_vector.at(i)) {
          word_position.at(i) = j;
          break;
        }
      }
    }

    for (long long i = 0; i < closest_word_number; ++i) {
      best_distance.at(i) = 0;
    }
    for (long long i = 0; i < closest_word_number; ++i) {
      best_word.at(i).clear();
    }
    ++total_question;


    if (word_position.at(0) == -1) {
      continue;
    }
    if (word_position.at(1) == -1) {
      continue;
    }
    if (word_position.at(2) == -1) {
      continue;
    }
    if (word_position.at(3) == -1) {
      continue;
    }


/*
    bool continue_flag = false;
    for (vector<long long>::iterator iter = word_position.begin(); iter != word_position.end(); ++iter) {
      if (*iter == -1) {
        continue_flag = true;
        break;
      }
    }
    if (continue_flag) {
      continue;
    }
*/

    for (long long i = 0; i < model_.feature_size_; ++i) {
      feature_score.at(i) = (model_.model_.at(word_position.at(1) * model_.feature_size_ + i) - \
                             model_.model_.at(word_position.at(0) * model_.feature_size_ + i) + 
                             model_.model_.at(word_position.at(2) * model_.feature_size_ + i));
    }
    ++seen_question;

    for (long long i = 0; i < model_.words_count_; ++i) {
/*
      continue_flag = false;
      for (size_t j = 0; j < word_position.size() - 1; ++j) {
        if (word_position.at(j) == i) {
          continue_flag = true;
          break;
        }
      }

      if (continue_flag) {
        continue;
      }
*/

      
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

    if (word_vector.at(3) == best_word.at(0)) {
      ++this_correct_count;
      ++total_correct_count;
      if (question_id <= 5) {
        ++semantic_correct_count;
      } else {
        ++syntactic_correct_count;
      }
    }

    if (question_id <= 5) {
      ++semantic_total_count;
    } else {
      ++syntactic_total_count;
    }

    ++this_total_count;
    ++total_count;
  }
  cerr<<"\r  Process "<<sentence_number<<" lines. "
      <<(sentence_number / ((float)(end - start + 1) / (float)CLOCKS_PER_SEC))<<" sent / s"
      <<flush;

  cerr<<"\rACCURACY TOP1: "<<this_correct_count / (float)this_total_count * 100<<" % ("<<this_correct_count<<" / "<<this_total_count<<")"
      <<"              \n";
  cerr<<"Total accuracy: "<<total_correct_count / (float)total_count * 100<<" %   "
      <<"Semantic accuracy: "<<semantic_correct_count / (float)semantic_total_count * 100<<" %   "
      <<"Syntactic accuracy: "<<syntactic_correct_count / (float)syntactic_total_count * 100<<" %\n";
  cerr<<"Questions seen:"<<seen_question<<" total:"<<total_question<<" seen/total:"<<seen_question / (float)total_question * 100<<"% "
      <<" speed:"<<(total_question / ((float)(end - start + 1) / (float)CLOCKS_PER_SEC))<<"sent/s\n"
      <<flush;


  return true;
}


bool Accuracy::Init(map<string, string> &parameters) {
  CheckParamsInConfig(parameters);
  CheckFilesInConfig(parameters);
  return true;
}


/*
 * $Name: CheckParamsInConfig
 * $Function: Check the parameters in configuration file.
 * $Date: 2014-07-09
 */
bool Accuracy::CheckParamsInConfig(map<string, string> &parameters) {
  string parameter_key;
  string default_value;
  parameter_key = "threadhold";
  default_value = "0";
  CheckEachParamInConfig(parameters, parameter_key, default_value);
  threadhold_ = atoi(parameters[parameter_key].c_str());
  return true;
}


/*
 * $Name: CheckParamsInConfig
 * $Function: Check the parameters in configuration file.
 * $Date: 2014-07-09
 */
bool Accuracy::CheckEachParamInConfig(map<string, string> &parameters, string &parameter_key, string &default_value) {
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
bool Accuracy::CheckFilesInConfig(map<string, string> &parameters) {
  string file_key;
  file_key = "question-file";
  CheckEachFileInConfig(parameters, file_key);
  question_file_ = parameters[file_key];
  return true;
}


/*
 * $Name: CheckEachFileInConfig
 * $Function: Check each file in configuration file.
 * $Date: 2014-07-09
 */
bool Accuracy::CheckEachFileInConfig(map<string, string> &parameters, string &file_key) {
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


