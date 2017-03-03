/*
 * $Id:
 * 0003
 *
 * $File:
 * parameter_controller.h
 *
 * $Proj:
 * WordRepresentation 
 *
 * $Func:
 * control parameters
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
 * 20120703,09:50
 */

#ifndef WORD2VECTOR_PARAMETER_CONTROLLER_H_
#define WORD2VECTOR_PARAMETER_CONTROLLER_H_

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

namespace word2vector_parameter_controller {

class GetParameter {
 public:
  void GetParamsOfWord2Vector();
  void GetParamsOfWrrbm();
  void GetParamsOfDistance();
  void GetParamsOfAccuracy();
  void GetParamsOfAnalogy();
  void GetParamsOfWord2Phrase();

 public:
  bool GetParameters(int argc, string argv);

 public:
  bool GetAllFunctions(int argc);
  bool GetAllFunctions(int argc, string argv);
};

}


#endif


