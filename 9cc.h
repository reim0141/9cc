#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// kind of token
typedef enum {
  TK_RESERVED,  // symbol
  TK_IDENT,     // identifier
  TK_NUM,       // integer
  TK_EOF,       // End of File
} TokenKind;

typedef struct Token Token;

// Type of Token
struct Token {
  TokenKind kind; // type of token
  Token *next;    // next token 
  int val;        // num 
  char *str;      // string of token
  int len;         // length of token
};

typedef struct LVar LVar;

struct LVar {
  LVar *next;
  char *name;
  int len;
  int offset;
};



void error(char *fmt, ...);
void error_at(char *loc, char *fmt, ...);
bool consume(char *op);

void expect(char *op);
int expect_number();
bool at_eof();
Token *tokenize();

extern char *user_input;
extern Token *token;
extern LVar *locals;

//
// Parser
//

typedef enum {
  ND_ADD, // +
  ND_SUB, // -
  ND_MUL, // *
  ND_DIV, // /
  ND_EQ,  // ==
  ND_NE,  // !=
  ND_LT,  // <
  ND_LE,  // <=
  ND_RETURN, // return
  ND_ASSIGN, // =
  ND_LVAR, // local variables
  ND_NUM, // integer
  ND_IF,  // if
  ND_FOR,  // for
  ND_WHILE, // while
  ND_BLOCK, // {...}
  ND_FUNCALL, // Function call
} NodeKind;

typedef struct Node Node;
struct Node {
  NodeKind kind;
  Node *lhs;
  Node *rhs;
  int val;
  int offset;
  Node *cond;
  Node *then;
  Node *els;
  Node *init;
  Node *inc;
  Node *next;
  Node *body;
  char *funcname;
};


// program    = stmt*
// stmt       = expr ";"
// expr       = assign
// assign     = equality ("=" assign)?
// equality   = relational ("==" relational | "!=" relational)*
// relational = add ("<" add | "<=" add | ">" add | ">=" add)*
// add        = mul ("+" mul | "-" mul)*
// mul        = unary ("*" unary | "/" unary)*
// unary      = ("+" | "-")? primary
// primary    = num | ident | "(" expr ")"Node *expr();

extern Node *code[100];

Node *program();
void codegen(Node *node);
