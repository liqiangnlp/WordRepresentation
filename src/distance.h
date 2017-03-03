/*
 * $Id:
 * 0013
 *
 * $File:
 * distance.h
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
 * 2014-08-30, 18:50
 */

#ifndef WORD_REPRESENTATION_DISTANCE_H_
#define WORD_REPRESENTATION_DISTANCE_H_

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <cmath>
#include "model.h"
#include "basic_method.h"

using namespace std;
using namespace word_representation_model;
using namespace word_representation_basic_method;

namespace word_representation_distance {

class Distance : public BasicMethod {
 public:
  Model model_;

 public:
  long long closest_word_number;

 public:
  Distance() {
    closest_word_number = 40;
  }
  ~Distance() {}

 public:
  bool ComputeDistance(map<string, string> &parameters);

 private:
  bool ComputeCosineDistance();
};

}

#endif

