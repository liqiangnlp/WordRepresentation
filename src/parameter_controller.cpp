/*
 * $Id:
 * 0003
 *
 * $File:
 * parameter_controller.cpp
 *
 * $Proj:
 * WordRepresentation
 *
 * $Func:
 * header file of control parameters
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
 * 2012-12-04,09:56
 */

#include "parameter_controller.h"


namespace word2vector_parameter_controller {

void GetParameter::GetParamsOfWord2Vector() {
  cerr<<"Vector Representation of Words Toolkit V1.0.0, liqiangneu@gmail.com\n"
      <<"[FUNCTION]\n"
      <<"                             Word2Vector\n"
      <<"[OPTION]\n"
      <<"            -config : Configuration file.\n"
      <<"             -input : Use inputted text data to train the model.\n"
      <<"              -size : Set size of word vectors.\n"
      <<"            -window : Set max skip length between words.\n"
      <<"            -binary : Save the resulting vectors in binary moded.\n"
      <<"            -output : Save the resulting words vectors.\n"
      <<"        -save-vocab : The vocabulary will be saved to file.\n"
      <<"        -read-vocab : The vocabulary will be read from file, no constructed from the training data.\n"
      <<"               -log : Log File.\n"
      <<"[EXAMPLE]\n"
      <<"         WordRepresentation  --WORD2VEC  -config config-file\n"
      <<flush;
  return;
}


void GetParameter::GetParamsOfWrrbm() {
  cerr<<"Vector Representation of Words Toolkit V1.0.0, liqiangneu@gmail.com\n"
      <<"[FUNCTION]\n"
      <<"                       Word Representation RBM\n"
      <<"[OPTION]\n"
      <<"            -config : Configuration file.\n"
      <<"[EXAMPLE]\n"
      <<"         WordRepresentation  --WRRBM  -config config-file\n"
      <<flush;
  return;
}


void GetParameter::GetParamsOfDistance() {
  cerr <<"Vector Representation of Words Toolkit V1.0.0, liqiangneu@gmail.com\n"
       <<"[FUNCTION]\n"
       <<"                               Distance\n"
       <<"[OPTION]\n"
       <<"            -config : Configuration file.\n"
       <<"[EXAMPLE]\n"
       <<"         WordRepresentation  --DISTANCE  -config config-file\n"
       <<flush;
  return;
}


void GetParameter::GetParamsOfAccuracy() {
  cerr <<"Vector Representation of Words Toolkit V1.0.0, liqiangneu@gmail.com\n"
       <<"[FUNCTION]\n"
       <<"                               Accuracy\n"
       <<"[OPTION]\n"
       <<"            -config : Configuration file.\n"
       <<"[EXAMPLE]\n"
       <<"         WordRepresentation  --ACCURACY  -config config-file\n"
       <<flush;
  return;
}


void GetParameter::GetParamsOfAnalogy() {
  cerr <<"Vector Representation of Words Toolkit V1.0.0, liqiangneu@gmail.com\n"
       <<"[FUNCTION]\n"
       <<"                               Analogy\n"
       <<"[OPTION]\n"
       <<"            -config : Configuration file.\n"
       <<"[EXAMPLE]\n"
       <<"         WordRepresentation  --Analogy  -config config-file\n"
       <<flush;
  return;
}


void GetParameter::GetParamsOfWord2Phrase() {
  cerr <<"Vector Representation of Words Toolkit V1.0.0, liqiangneu@gmail.com\n"
       <<"[FUNCTION]\n"
       <<"                               Word2Phrase\n"
       <<"[OPTION]\n"
       <<"            -config : Configuration file.\n"
       <<"[EXAMPLE]\n"
       <<"         WordRepresentation  --WORD2PHRASE  -config config-file\n"
       <<flush;
  return;
}


bool GetParameter::GetAllFunctions(int argc) {
  if (argc <= 1) {
    cerr << "Vector Representation of Words Toolkit V1.0.0, liqiangneu@gmail.com\n"
         << "[USAGE]\n"
         << "          WordRepresentation     <action>         [OPTIONS]\n"
         << "[ACTION]\n"
         << "             --WORD2VEC            :   Training Word2Vector Model.\n"
         << "             --WRRBM               :   Training WRRBM Model.\n"
         << "             --WORD2PHRASE         :   Convert Word 2 Phrase.\n"
         << "             --DISTANCE            :   Compute Distance.\n"
         << "             --ACCURACY            :   Compute Accuracy.\n"
         << "             --ANALOGY             :   Analogy.\n"
         << "[TOOLS]\n"
         << "     >> Training Word2Vector Model\n"
         << "          WordRepresentation              --WORD2VEC\n"
         << "          WordRepresentation              --WRRBM\n"
         << "          WordRepresentation              --WORD2PHRASE\n"
         << "          WordRepresentation              --DISTANCE\n"
         << "          WordRepresentation              --ACCURACY\n"
         << "          WordRepresentation              --ANALOGY\n\n"
         << flush;
    return true;
  }
  return false;
}


bool GetParameter::GetAllFunctions(int argc, string argv) {
  if ((argc % 2 != 0) || (argc % 2 == 0) && \
     ((argv != "--WORD2VEC") && (argv != "--DISTANCE") && \
      (argv != "--ACCURACY") && (argv != "--ANALOGY") && \
      (argv != "--WORD2PHRASE") && (argv != "--WRRBM"))) {
    cerr << "Vector Representation of Words Toolkit V1.0.0, liqiangneu@gmail.com\n"
         << "[USAGE]\n"
         << "          WordRepresentation     <action>         [OPTIONS]\n"
         << "[ACTION]\n"
         << "             --WORD2VEC            :   Training Word2Vector Model.\n"
         << "             --WRRBM               :   Training WRRBM Model.\n"
         << "             --WORD2PHRASE         :   Convert Word 2 Phrase.\n"
         << "             --DISTANCE            :   Compute Distance.\n"
         << "             --ACCURACY            :   Compute Accuracy.\n"
         << "             --ANALOGY             :   Analogy.\n"
         << "[TOOLS]\n"
         << "     >> Training Word2Vector Model\n"
         << "          WordRepresentation              --WORD2VEC\n"
         << "          WordRepresentation              --WRRBM\n"
         << "          WordRepresentation              --WORD2PHRASE\n"
         << "          WordRepresentation              --DISTANCE\n"
         << "          WordRepresentation              --ACCURACY\n"
         << "          WordRepresentation              --ANALOGY\n\n"
         << flush;
    return true;
        }
        return false;
    }


bool GetParameter::GetParameters( int argc, string argv ) {
  if (argc == 2) {
    if (argv == "--WORD2VEC") { 
      GetParamsOfWord2Vector();
    } else if (argv == "--WRRBM") {
      GetParamsOfWrrbm();
    } else if (argv == "--DISTANCE") {
      GetParamsOfDistance();
    } else if (argv == "--ACCURACY") {
      GetParamsOfAccuracy();
    } else if (argv == "--ANALOGY") {
      GetParamsOfAnalogy();
    } else if (argv == "--WORD2PHRASE") {
      GetParamsOfWord2Phrase();
    }
    return true;
  }
  return false;
}

}


