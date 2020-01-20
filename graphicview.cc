#include "graphicview.h"
#include "concreteboard.h"
#include "piece.h"
#include "sstream"
using namespace std;


int BOARDSIZE = 680;
int XMIDDLE = (int) BOARDSIZE / SIZE * 0.32 + 0.5;
int YMIDDLE = (int) BOARDSIZE / SIZE * 0.7 + 0.5;
int OFFSET = 32;
const int SIDEBAR = 25;
const float  RSIDEX = 0.4;
const float  RSIDEY = 0.53;
const float  CSIDEX = 0.47;
const float  CSIDEY = 16;
char WHITECELL = ' ';
char BLACKCELL = '_';


GraphicView:: GraphicView () {
  int cellSize = BOARDSIZE / SIZE;
  for (int i = 0; i < SIZE; ++i) {
    for (int j = 0; j < SIZE; ++j) {
      theView[i][j] = ((i+j) % 2 == 0)? WHITECELL : BLACKCELL;
    }
  }
  x.fillRectangle(0, 0, SIDEBAR, BOARDSIZE, Xwindow::Black);
  x.fillRectangle(0, BOARDSIZE, BOARDSIZE+SIDEBAR, SIDEBAR, Xwindow::Black);
  for (int i = 0; i < SIZE; ++i) {
    char theCord = '8' - i;
    string theCordStr(1, theCord);
    x.drawString(SIDEBAR*RSIDEX, (int)cellSize*(i+RSIDEY), theCordStr, Xwindow:: White);
  }
  for (int i = 0; i < SIZE; ++i) {
    char theCord = 'a' + i;
    string theCordStr(1, theCord);
    x.drawString((int)SIDEBAR+cellSize*(i+CSIDEX), (int)BOARDSIZE+CSIDEY, theCordStr, Xwindow:: White);
  }
  for (int i = 0; i < SIZE; ++i) {
    for (int j = 0; j < SIZE; ++j) {
      if (theView[i][j] == WHITECELL) {
        x.fillRectangle(j*cellSize+SIDEBAR, i*cellSize, cellSize, cellSize, Xwindow::Orange);
      } else if (theView[i][j] == BLACKCELL) {
        x.fillRectangle(j*cellSize+SIDEBAR, i*cellSize, cellSize, cellSize, Xwindow::Brown);
      }
    }
  }
}


void GraphicView:: update(const ConcreteBoard* b) {
  // temperary char view for comparison;
  char newView[SIZE][SIZE];
  for (int i = 0; i < SIZE; ++i) {
    for (int j = 0; j < SIZE; ++j){
      if (b->getPiece(i,j)) { // (i,j) is a chess piece
        newView[i][j] = b->getPiece(i,j)->getType();
      } else { //(i,j) is empty
        newView[i][j] = ((i+j) % 2 == 0)? WHITECELL : BLACKCELL;
      }
    }
  }
  int cellSize = BOARDSIZE / SIZE;
  for (int i = 0; i < SIZE; ++i) {
    for (int j = 0; j < SIZE; ++j) {
      if (theView[i][j] != newView[i][j]) {
        char theChess = newView[i][j];
        if (theChess >= 'a' && theChess <= 'z') {
          theChess = theChess - OFFSET;
          string theChessStr(1, theChess);
          x.drawBigString(j*cellSize+XMIDDLE+SIDEBAR, i*cellSize+YMIDDLE, theChessStr, Xwindow:: Black);
        } else if (theChess >= 'A' && theChess <= 'Z') {
          string theChessStr(1, theChess);
          x.drawBigString(j*cellSize+XMIDDLE+SIDEBAR, i*cellSize+YMIDDLE, theChessStr, Xwindow:: White);
        } else if (theChess == WHITECELL) {
          x.fillRectangle(j*cellSize+SIDEBAR, i*cellSize, cellSize, cellSize, Xwindow::Orange);
        } else if (theChess == BLACKCELL) {
          x.fillRectangle(j*cellSize+SIDEBAR, i*cellSize, cellSize, cellSize, Xwindow::Brown);
        }
        theView[i][j] = newView[i][j];
      }
    }
  }
}
