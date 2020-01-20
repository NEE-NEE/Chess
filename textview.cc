#include "textview.h"
#include "concreteboard.h"
#include "piece.h"
using namespace std;


extern char BLACKCELL; // = '_';
extern char WHITECELL; // = ' ';
const string XCORD = "  abcdefgh";
const int YCORD = 8;
const string SPACE = " ";

TextView:: TextView() {
  for (int i = 0; i < SIZE; ++i) {
    for (int j = 0; j < SIZE; ++j) {
      theView[i][j] = ((i+j) % 2 == 0)? WHITECELL : BLACKCELL;
    }
  }
}


void TextView:: update(const ConcreteBoard* b) {
  for (int i = 0; i < SIZE; ++i) {
    for (int j = 0; j < SIZE; ++j){
      if (b->getPiece(i,j)) { // (i,j) is a chess piece
        theView[i][j] = b->getPiece(i,j)->getType();
      } else { //(i,j) is empty
        theView[i][j] = ((i+j) % 2 == 0)? WHITECELL : BLACKCELL;
      }
    }
  }
}


ostream &operator<<(std::ostream &out, const View &v) {
  for (int i = 0; i < SIZE; ++i) {
    for (int j = 0; j < SIZE; ++j){
      if (j == 0) out << YCORD-i << SPACE;
      out << v.theView[i][j];
    }
    out << endl;
  }
  out << endl;
  out << XCORD <<endl;
  return out;
}

