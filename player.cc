#include <string>
#include <stdlib.h>
#include <memory>
#include "player.h"
#include "concreteboard.h"
#include "piece.h"


int SIZE = 8;


Player:: Player(bool color, ConcreteBoard * board, bool type):color{color}, chessBoard{board}, type{type}{}


Player:: ~Player(){}


Human:: Human (bool color, ConcreteBoard * board):Player{color, board, 0} {}


//   Human::makeMove
//called by Controller
//	1. check move valid, if not throw (str)
//	2. move piece from Board side
void Human:: makeMove(int fromX, int fromY, int toX, int toY){
	Piece * dest = chessBoard->getPiece(toX, toY);
	Piece * toMove = chessBoard->getPiece(fromX, fromY);
	if(toMove && toMove->getColor() == color && toMove->checkValidity(chessBoard, toX, toY)){
		if (dest){chessBoard->removePiece(toX, toY);}
		else if ((toMove->getType() == 'P' || toMove->getType() == 'p') && fromY != toY)
			{
				chessBoard->removePiece(fromX, toY);
			}
		else if ((toMove->getType() == 'K' || toMove->getType() == 'k') && ((fromY-toY)==2 || (fromY-toY)==-2))
			{
				if ((fromY-toY)==2)
				{
					chessBoard->modifyBoard(fromX, 0, fromX, 3); // move the rook
				}
				if ((fromY-toY)==-2)
				{
					chessBoard->modifyBoard(fromX, 7, fromX, 5); // move the rook
				}
			}
		chessBoard->modifyBoard(fromX, fromY, toX, toY);
	}else{
		throw std::string("Invalid move");
	}
}


Machine:: Machine (bool color, ConcreteBoard * board, int level): Player{color, board, 1},level{level}{}


void Machine:: makeMove() {
	if (level == 1){
		makeMoveLv1();
	}else if(level == 2){
		makeMoveLv2();
	}else if(level == 3){
		makeMoveLv3();
	}else if(level == 4){
	  makeMoveLv4();
	}
}


//1. for all available Pieces, filter out movable ones
//2. random seletion from list of all movables
//3. random seletion from list of possible moves
void Machine:: makeMoveLv1(){
	std::vector<Piece*> movableP;
	for(int r = 0; r < SIZE; r++){
		for(int c = 0; c < SIZE; c++){
			Piece * temp = chessBoard->getPiece(r, c);
			if (temp &&
			temp->getColor() == color &&
			(temp->possibleMoves(chessBoard)).size() > 0  )
			{movableP.emplace_back(temp);}
		}
	}
	if (movableP.size() == 0)
 	{
  		std::cout << color << " has no moves" << std::endl;
  		return;
 	}	
	int randomIndex = std::rand() % movableP.size();
	Piece * toMove = movableP.at(randomIndex);

	std::vector<std::vector<int>> pos = toMove->possibleMoves(chessBoard);

	int randomPos = std::rand() % pos.size();
	/***should return (x,y) as a vector*/
	int toX = pos.at(randomPos).at(0);
	int toY = pos.at(randomPos).at(1);
	int fromX = toMove->getX();
	int fromY = toMove->getY();

	Piece * dest = chessBoard->getPiece(toX, toY);
	// pawn changes to another piece
	if (toMove->getType() == 'P' && toX == 0)
	{
		if (chessBoard->getPiece(toX, toY)) chessBoard->removePiece(toX, toY);
		chessBoard->modifyBoard(fromX, fromY, toX, toY);
		chessBoard->removePiece(toX, toY);
		randomIndex = std::rand() % 3;
		char types[4]= { 'N', 'B', 'Q', 'R' };
		char randomType = types[randomIndex];
		chessBoard->addPiece(toX, toY, randomType);
	}
	else if (toMove->getType() == 'p' && toX == 7)
	{
		if (chessBoard->getPiece(toX, toY)) chessBoard->removePiece(toX, toY);
		chessBoard->modifyBoard(fromX, fromY, toX, toY);
		chessBoard->removePiece(toX, toY);
		randomIndex = std::rand() % 3;
		char types[4]= { 'n', 'b', 'q', 'r' };
		char randomType = types[randomIndex];
		chessBoard->addPiece(toX, toY, randomType);
	}
	else
	{
		if (dest) { chessBoard->removePiece(toX, toY); }
		// en passant
		else if ((toMove->getType() == 'P' || toMove->getType() == 'p') && fromY != toY)
		{
			chessBoard->removePiece(fromX, toY);
		}
		// castling
		else if ((toMove->getType() == 'K' || toMove->getType() == 'k') && ((fromY - toY) == 2 || (fromY - toY) == -2))
		{
			if ((fromY - toY) == 2)
			{
				chessBoard->modifyBoard(fromX, 0, fromX, 3); // move the rook
			}
			if ((fromY - toY) == -2)
			{
				chessBoard->modifyBoard(fromX, 7, fromX, 5); // move the rook
			}
		}
		chessBoard->modifyBoard(fromX, fromY, toX, toY);
	}
}


//1. find first capturing/check move we countered
//2. if no capturing/check move available, call makeMoveLv1()
void Machine::makeMoveLv2(){
	for (int r = 0; r< SIZE;r++){
		for (int c = 0; c < SIZE; c++){

			// a piece of my color
			Piece * temp = chessBoard->getPiece(r, c);
			if (temp && temp->possibleMoves(chessBoard).size() > 0 && temp->getColor() == color){
				std::vector<std:: vector<int>> possibleMoves = temp->possibleMoves(chessBoard);
				int fromX = temp->getX();
                                int fromY = temp->getY();
				// for each possible moves of this piece
				for(int i = 0; i < possibleMoves.size(); i++){
					int toX = possibleMoves.at(i).at(0);
					int toY = possibleMoves.at(i).at(1);
					Piece * dest = chessBoard->getPiece(toX, toY);

					// one possible move can capture the opponent's piece
					if(dest && dest->getColor() != color) {
						//capturing move
						chessBoard->removePiece(toX, toY);
						chessBoard->modifyBoard(fromX, fromY, toX, toY);
						// pawn changes to another piece
						if (temp->getType() == 'P' && toX == 0)
						{
							chessBoard->removePiece(toX, toY);
							int randomIndex = std::rand() % 3;
							char types[4]= { 'N', 'B', 'Q', 'R' };
							char randomType = types[randomIndex];
							chessBoard->addPiece(toX, toY, randomType);
						}
						else if (temp->getType() == 'p' && toX == 7)
						{
					    		chessBoard->removePiece(toX, toY);
					    		int randomIndex = std::rand() % 3;
					    		char types[4]= { 'n', 'b', 'q', 'r' };
					    		char randomType = types[randomIndex];
					    		chessBoard->addPiece(toX, toY, randomType);
					  	}
						return;
					}
					else if ((temp->getType() == 'P' || temp->getType() == 'p') && fromY != toY)
					{
						chessBoard->removePiece(fromX, toY);
						chessBoard->modifyBoard(fromX, fromY, toX, toY);
						return;
					}
					// capture never comes with castling, so no need to consider;


					// cannot capture, check if make the opponent in check
				else{
						std::vector<std:: vector<int>> pPossibleMoves = temp->possibleMoves(chessBoard);
						for (int i = 0; i < pPossibleMoves.size(); i++){
                                        		int pToX = pPossibleMoves.at(i).at(0);
                                        		int pToY = pPossibleMoves.at(i).at(1);
							if(chessBoard->getKing(!color)->getX() == pToX &&
							   chessBoard->getKing(!color)->getY() == pToY){
								// check move
								chessBoard->modifyBoard(temp->getX(), temp->getY(), toX, toY);
								return;
							}
						}
					}
				}
			}
		}
	}
	makeMoveLv1();
}


void Machine::makeMoveLv3(){
  // for each movable piece of player
  for(int r = 0; r< SIZE; r++){
    for(int c = 0; c< SIZE; c++){
      Piece * temp = chessBoard->getPiece(r, c);
      if(temp && temp->possibleMoves(chessBoard).size() > 0 && temp->getColor()==color){

        // check if it might be captured
        for(int nr = 0; nr < SIZE; nr++){
          for (int nc = 0; nc < SIZE; nc++){
            Piece * temp1 = chessBoard->getPiece(nr, nc);
            if(temp1 && temp1->getColor()!=color && temp1->checkValidity(chessBoard, r, c)){ // piece at (r,c) might be captured

              // collect all possible moves the piece
	      std::vector<std::vector<int>> possibleMoves = temp->possibleMoves(chessBoard);
	      int fromX = temp->getX();
	      int fromY = temp->getY();

	      // for each possible move, check if it is going to be captured
	      for(int i = 0; i < possibleMoves.size(); i++){
		  int toX = possibleMoves.at(i).at(0);
		  int toY = possibleMoves.at(i).at(1);
		  bool avoidCap = true;
		  for(int anr = 0; nr < SIZE; nr++){
		    for (int anc = 0; nc < SIZE; nc++){
		      Piece * temp2 = chessBoard->getPiece(anr, anc);
		      if(temp2 && temp2->getColor()!=color && temp2->checkValidity(chessBoard, toX, toY)){ // if the piece goes to (toX,toY), it might be captured
		      	avoidCap = false;
		      }
		    }
		  }

		  // it will not be captured if the piece make this move
		  if (avoidCap) {
	 	    Piece * dest = chessBoard->getPiece(toX, toY);
		    // pawn changes to another piece
		    if (temp->getType() == 'P' && toX == 0) {
			if (chessBoard->getPiece(toX, toY)) chessBoard->removePiece(toX, toY);
			chessBoard->modifyBoard(fromX, fromY, toX, toY);
			chessBoard->removePiece(toX, toY);
			int randomIndex = std::rand() % 3;
			char types[4]= { 'N', 'B', 'Q', 'R' };
			char randomType = types[randomIndex];
			chessBoard->addPiece(toX, toY, randomType);
			return;
		     } else if (temp->getType() == 'p' && toX == 7) {
			if (chessBoard->getPiece(toX, toY)) chessBoard->removePiece(toX, toY);
			chessBoard->modifyBoard(fromX, fromY, toX, toY);
			chessBoard->removePiece(toX, toY);
		   	int randomIndex = std::rand() % 3;
		   	char types[4]= { 'n', 'b', 'q', 'r' };
		    	char randomType = types[randomIndex];
		    	chessBoard->addPiece(toX, toY, randomType);
			return;
	 	     } else {
			if (dest) { chessBoard->removePiece(toX, toY); }
			// en passant
			else if ((temp->getType() == 'P' || temp->getType() == 'p') && fromY != toY) {
			  chessBoard->removePiece(fromX, toY);}
			// castling
			else if ((temp->getType() == 'K' || temp->getType() == 'k') && ((fromY - toY) == 2 || (fromY - toY) == -2)) {
			  if ((fromY - toY) == 2) { chessBoard->modifyBoard(fromX, 0, fromX, 3);} // move the rook
			  if ((fromY - toY) == -2) { chessBoard->modifyBoard(fromX, 7, fromX, 5);} // move the rook
			}
			chessBoard->modifyBoard(fromX, fromY, toX, toY);
			return;
		     }
		   }
		 }
	      }
	   }
	}
      }
    }
  } // we have gone over the chess board and we did not find such piece that can avoid capture
  makeMoveLv2();
}


void Machine::makeMoveLv4(){
// some strategies added

// 1. A pawn, upon reaching the other end of the board is replaced by a Queen
//    as it is the most "powerful" piece

// for each pawn of the black player
	for(int r = 0; r< SIZE; r++){
		for(int c = 0; c< SIZE; c++){
			Piece * temp = chessBoard->getPiece(r, c);
			if(color && temp && temp->possibleMoves(chessBoard).size() > 0 && temp->getColor()==color
	       && temp->getType()=='p') {
	       // check if it is at the second last row of the other end of the board
	       if (temp->getX() == 6) {
	         std::vector<std::vector<int>> possibleMoves = temp->possibleMoves(chessBoard);
				   int fromX = temp->getX();
				   int fromY = temp->getY();
	         // check if the possible moves contains the one towards the end of the board
	         for(int i = 0; i < possibleMoves.size(); i++){
	           int toX = possibleMoves.at(i).at(0);
	           int toY = possibleMoves.at(i).at(1);
	           if (toX == 7) {
	             if (chessBoard->getPiece(toX, toY)) chessBoard->removePiece(toX, toY);
	             chessBoard->modifyBoard(temp->getX(), temp->getY(), toX, toY);
	             chessBoard->removePiece(toX, toY);
	             chessBoard->addPiece(toX, toY, 'q');
							 return;
	           }
	         }
	       }
	     } else if(!color && temp && temp->possibleMoves(chessBoard).size() > 0 && temp->getColor()==color
 	       		 && temp->getType()=='P') {
 	       		// check if it is at the second last row of the other end of the board
 	       	if (temp->getX() == 1) {
 	            std::vector<std::vector<int>> possibleMoves = temp->possibleMoves(chessBoard);
		    int fromX = temp->getX();
 		    int fromY = temp->getY();
 	            // heck if the possible moves contains the one towards the end of the board
 	            for(int i = 0; i < possibleMoves.size(); i++){
 	              int toX = possibleMoves.at(i).at(0);
 	              int toY = possibleMoves.at(i).at(1);
 	              if (toX == 0) {
 	                if (chessBoard->getPiece(toX, toY)) chessBoard->removePiece(toX, toY);
 	                chessBoard->modifyBoard(temp->getX(), temp->getY(), toX, toY);
 	                chessBoard->removePiece(toX, toY);
 	                chessBoard->addPiece(toX, toY, 'Q');
			return;
 	              }
		   }
 	        }
	   }
       }
    } // we have gone over the chess board and we did not find such piece that can avoid capture
    makeMoveLv3();
}
