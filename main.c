#include "9cc.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    error("Invalid number of arguments");
    return 1;
  }
  
  // tokenize and parse
  user_input = argv[1];
  token = tokenize();
  Node *node = program(); 
  
  codegen(node);

  

  return 0;
}