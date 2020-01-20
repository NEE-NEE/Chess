#include "concreteboard.h"
#include "piece.h"
#include "view.h"
using namespace std;

// global constant;
int EMPTYROWS = 4; // number of lines with chesses at opening
bool WHITE = 0;
bool BLACK = 1;


ConcreteBoard:: ConcreteBoard() {
  // first line for black player;
  int row = 0;
  int col = 0;
  vector<unique_ptr <Piece>> line1;
  line1.emplace_back(make_unique<Rook> (BLACK, row, col, 'r'));
  line1.emplace_back(make_unique<Knight> (BLACK, row, ++col, 'n'));
  line1.emplace_back(make_unique<Bishop> (BLACK, row, ++col, 'b'));
  line1.emplace_back(make_unique<Queen> (BLACK, row, ++col, 'q'));
  unique_ptr<King> bk = make_unique<King> (BLACK, row, ++col, 'k');
  blackKing = bk.get();
  line1.emplace_back(move(bk));
  line1.emplace_back(make_unique<Bishop> (BLACK, row, ++col, 'b'));
  line1.emplace_back(make_unique<Knight> (BLACK, row, ++col, 'n'));
  line1.emplace_back(make_unique<Rook> (BLACK, row, ++col, 'r'));
  theBoard.emplace_back(move(line1));

  // second line for black player;
  vector<unique_ptr <Piece>> line2;
  ++row; // row = 1;
  for (int i = 0; i < SIZE; ++i) {
    line2.emplace_back(make_unique<Pawn> (BLACK, row, i, 'p'));
  }
  theBoard.emplace_back(move(line2));

  // empty lines;
  for (int i = 0; i < EMPTYROWS; ++i) {
    ++row; // row = 2,3,4,5;
    vector<unique_ptr<Piece>> line;
    for (int j = 0; j < SIZE; ++j) {
      line.emplace_back(nullptr);
    }
    theBoard.emplace_back(move(line));
  }

  // first line for white player;
  vector<unique_ptr <Piece>> line7;
  ++row; // row = 6;
  for (int i = 0; i < SIZE; ++i) {
    line7.emplace_back(make_unique<Pawn> (WHITE, row, i, 'P'));
  }
  theBoard.emplace_back(move(line7));

  // second line for white player;
  ++row; // row = 7;
  col = 0;
  vector<unique_ptr <Piece>> line8;
  line8.emplace_back(make_unique<Rook> (WHITE, row, col, 'R'));
  line8.emplace_back(make_unique<Knight> (WHITE, row, ++col, 'N'));
  line8.emplace_back(make_unique<Bishop> (WHITE, row, ++col, 'B'));
  line8.emplace_back(make_unique<Queen> (WHITE, row, ++col, 'Q'));
  unique_ptr<King> wk = make_unique<King> (WHITE, row, ++col, 'K');
  whiteKing = wk.get();
  line8.emplace_back(move(wk));
  line8.emplace_back(make_unique<Bishop> (WHITE, row, ++col, 'B'));
  line8.emplace_back(make_unique<Knight> (WHITE, row, ++col, 'N'));
  line8.emplace_back(make_unique<Rook> (WHITE, row, ++col, 'R'));
  theBoard.emplace_back(move(line8));


  // initialize the number of chess pieces(full chess opening)
  // black
  chessCount['r'] = 2;
  chessCount['n'] = 2;
  chessCount['b'] = 2;
  chessCount['q'] = 1;
  chessCount['k'] = 1;
  chessCount['p'] = 8;
  // white
  chessCount['R'] = 2;
  chessCount['N'] = 2;
  chessCount['B'] = 2;
  chessCount['Q'] = 1;
  chessCount['K'] = 1;
  chessCount['P'] = 8;
}


ConcreteBoard:: ConcreteBoard(string boardType) {
  if (boardType == "empty") {
    for (int i = 0; i < SIZE; ++i) {
      vector<unique_ptr <Piece>> line;
      for (int j = 0; j < SIZE; ++j) {
        line.emplace_back(nullptr);
      }
      theBoard.emplace_back(move(line));
    }

    // initialize the number of chess pieces(empty board)
    // black
    chessCount['r'] = 0;
    chessCount['n'] = 0;
    chessCount['b'] = 0;
    chessCount['q'] = 0;
    chessCount['k'] = 0;
    chessCount['p'] = 0;
    // white
    chessCount['R'] = 0;
    chessCount['N'] = 0;
    chessCount['B'] = 0;
    chessCount['Q'] = 0;
    chessCount['K'] = 0;
    chessCount['P'] = 0;
  }
}


void ConcreteBoard:: modifyBoard(int fromX, int fromY, int toX, int toY) {
  theBoard[toX][toY] = move(theBoard[fromX][fromY]);
  theBoard[fromX][fromY].reset();
  ++timer;
  theBoard[toX][toY]->getX() = toX;
  theBoard[toX][toY]->getY() = toY;
  theBoard[toX][toY]->getStep() = timer;
  notify();
}

void ConcreteBoard::tryModifyBoard(int fromX, int fromY, int toX, int toY)const {
  theBoard[toX][toY] = move(theBoard[fromX][fromY]);
  theBoard[fromX][fromY].reset();
  theBoard[toX][toY]->getX() = toX;
  theBoard[toX][toY]->getY() = toY;
}


void ConcreteBoard:: removePiece(int x, int y) {
  char type = theBoard[x][y]->getType();
if (type == 'k') blackKing = nullptr;
if (type == 'K') whiteKing = nullptr;
  chessCount[type] -= 1;
  theBoard[x][y].reset();
  notify();
}


void ConcreteBoard:: addPiece(int x, int y, char type) {
  chessCount[type] += 1;
  if (type == 'r') theBoard[x][y] = make_unique<Rook> (BLACK, x, y, 'r');
  if (type == 'n') theBoard[x][y] = make_unique<Knight> (BLACK, x, y, 'n');
  if (type == 'b') theBoard[x][y] = make_unique<Bishop> (BLACK, x, y, 'b');
  if (type == 'q') theBoard[x][y] = make_unique<Queen> (BLACK, x, y, 'q');
  if (type == 'k'){
  unique_ptr<King> bk = make_unique<King> (BLACK, x, y, 'k');
  blackKing = bk.get();
	theBoard[x][y] = move(bk);
	}
  if (type == 'p') theBoard[x][y] = make_unique<Pawn> (BLACK, x, y, 'p');
  if (type == 'R') theBoard[x][y] = make_unique<Rook> (WHITE, x, y, 'R');
  if (type == 'N') theBoard[x][y] = make_unique<Knight> (WHITE, x, y, 'N');
  if (type == 'B') theBoard[x][y] = make_unique<Bishop> (WHITE, x, y, 'B');
  if (type == 'Q') theBoard[x][y] = make_unique<Queen> (WHITE, x, y, 'Q');
  if (type == 'K') {
  unique_ptr<King> wk = make_unique<King> (WHITE, x, y, 'K');
  whiteKing = wk.get();
	theBoard[x][y] = move(wk);
	}
  if (type == 'P') theBoard[x][y] = make_unique<Pawn> (WHITE, x, y, 'P');
  notify();
}


Piece *ConcreteBoard:: getPiece(int x, int y) const {
  return theBoard[x][y].get();
}


int ConcreteBoard:: getNum(char c) {
  return chessCount[c];
}


int ConcreteBoard:: getTimer() const {
  return timer;
}


King *ConcreteBoard:: getKing(bool colour) const {
  if (colour) return blackKing;
  return whiteKing;
}
bool ConcreteBoard:: inCheck(bool color) const {
        int kingX;
        int kingY;
        int deltaX_P;
        if (color){ kingX = blackKing->getX();
                    kingY = blackKing->getY();
                    deltaX_P = 1;}
        else{       kingX = whiteKing->getX();
                    kingY = whiteKing->getY();
                    deltaX_P = -1;}
        //CHECK P attach
        if      (kingX+deltaX_P < SIZE && kingX+deltaX_P >=0 && kingY+1 >= 0 && kingY+1 < SIZE &&
		 theBoard[kingX+deltaX_P][kingY+1]!=nullptr){
                if      ( color && theBoard[kingX+deltaX_P][kingY+1]->getType() == 'P'){
                        return true;
                }else if(!color && theBoard[kingX+deltaX_P][kingY+1]->getType() == 'p'){
                        return true;
                }
        }else if(kingX+deltaX_P < SIZE && kingX+deltaX_P >=0 && kingY-1 >= 0 && kingY-1 < SIZE &&
		 theBoard[kingX+deltaX_P][kingY-1]!=nullptr){
                if(color && theBoard[kingX+deltaX_P][kingY-1]->getType() == 'P'){
                        return true;
                }else if(!color && theBoard[kingX+deltaX_P][kingY-1]->getType() == 'p'){
                        return true;
                }
        }
        int deltaN[8][2] = {{-2,-1},{-2,1},{2,1},{2,-1},{1, 2},{1, -2},{-1,2},{-1,-2}};
        for (auto posn: deltaN){
                int tempX = kingX + posn[0];
                int tempY = kingY + posn[1];
                if(tempX < SIZE && tempX >= 0&&tempY < SIZE&&tempY>=0){
                        if(theBoard[tempX][tempY]!=nullptr){
                        if (color && theBoard[tempX][tempY]->getType() == 'N'){return true;}
                        else if(!color && theBoard[tempX][tempY]->getType() == 'n'){return true;}
                }}



}
        //CHECK Queen Bishop 
        int delta[4][2] = {{1,1},{1,-1},{-1,1},{-1,-1}};
        for(auto posn: delta){
                int tempX = kingX;
                int tempY = kingY;
                tempX+=posn[0];
                tempY+=posn[1];
                while(tempX < SIZE && tempX>= 0 && tempY< SIZE && tempY >=0){
                       if(theBoard[tempX][tempY]!=nullptr){
                         if(color && (theBoard[tempX][tempY]->getType() == 'Q' ||theBoard[tempX][tempY]->getType() == 'B')){return true;}
                        else if(!color && (theBoard[tempX][tempY]->getType() == 'q' ||theBoard[tempX][tempY]->getType() == 'b')){return true;}
                        }
                        tempX+=posn[0];
                        tempY+=posn[1];
                }
        }
        //CHECK Queeen Rook
        int deltaI[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
        for(auto posn: deltaI){
                int tempX = kingX;
                int tempY = kingY;
                tempX+=posn[0];
                tempY+=posn[1];
                while(tempX< SIZE &&tempX >= 0&& tempY< SIZE&&tempY>=0){
                       if(theBoard[tempX][tempY]!=nullptr){
                        if(color && (theBoard[tempX][tempY]->getType() == 'Q' ||theBoard[tempX][tempY]->getType() == 'R')){return true;}
                        else if(!color && (theBoard[tempX][tempY]->getType() == 'q' ||theBoard[tempX][tempY]->getType() == 'r')){return true;}
                }
                tempX+=posn[0];
                tempY+=posn[1];
        }
        }
        return false;

}

void ConcreteBoard::filterPossibleMoves(vector<vector<int>> &choices, int x, int y, bool color) const{
        vector<unique_ptr<Piece>> deleted;
        vector<vector<int>> newC;
        for (auto posn: choices){
                if (theBoard[posn[0]][posn[1]]!=nullptr){
                        deleted.emplace_back(move(theBoard[posn[0]][posn[1]]));
                        tryModifyBoard(x, y, posn[0],posn[1]);
                          if(!inCheck(color)){newC.emplace_back(posn);}
                        tryModifyBoard(posn[0],posn[1],x,y);
                        theBoard[posn[0]][posn[1]] = move(deleted.back());
                }else{
                        tryModifyBoard(x, y, posn[0],posn[1]);
                        if(!inCheck(color)){newC.emplace_back(posn);}
                        tryModifyBoard(posn[0],posn[1],x,y);
                }
        }
        choices.swap(newC);
}

void ConcreteBoard:: notify() const {
  for (auto &views : theViews) views->update(this);
}
