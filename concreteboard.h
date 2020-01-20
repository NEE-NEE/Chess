#ifndef CONCRETEBOARD_H
#define CONCRETEBOARD_H
#include <vector>
#include <memory>
#include <map>
#include <string>
#include "board.h"


// forward declaration
class Piece;
class TextView;
class GraphicView;
class King;

class ConcreteBoard: public Board {
  mutable std::vector<std::vector<std::unique_ptr <Piece>>> theBoard; // the actual board;
  std::map <char, int> chessCount; // keep track of the number of each type of chess;
  King *whiteKing;
  King *blackKing;
  int timer = 0;

 public:
   ConcreteBoard();
   ConcreteBoard(std::string boardType);
   void modifyBoard(int fromX, int fromY, int toX, int toY); // move piece from one pos to another(must be nullptr)
   void tryModifyBoard(int fromX, int fromY, int toX, int toY)const; 
   void removePiece(int x, int y); // remove the piece at pos (delete the piece, set to nullptr);
   void addPiece(int x, int y, char type); // add the piece at pos;
   Piece *getPiece(int x, int y) const; // get the chess ptr at position (x,y) in the board
   int getNum(char c);
   int getTimer() const;
   King *getKing(bool colour) const;
   bool inCheck(bool colour) const;
   void filterPossibleMoves(std::vector<std::vector<int>> &choices, int x, int y, bool color)const;
   void notify() const;
};

#endif
