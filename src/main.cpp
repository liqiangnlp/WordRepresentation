/*
 * $Id:
 * 0002
 *
 * $File:
 * main.cpp
 *
 * $Proj:
 * WordRepresentation
 *
 * $Func:
 * main function
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
 * 20120704, 20:59
 */

#include "main.h"

int main(int argc, char * argv[]) {
  GetParameter getParameter;
  if (getParameter.GetAllFunctions(argc)) {
    exit(1);
  } else if (getParameter.GetAllFunctions(argc, string(argv[ 1 ]))) {
    exit(1);
  } else if (getParameter.GetParameters(argc, string(argv[ 1 ]))) {
    exit(1);
  }

  Dispatcher dispatcher;
  dispatcher.ResolveParameters(argc, argv);
  return 0;
}

