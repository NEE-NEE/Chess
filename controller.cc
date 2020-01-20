#include "player.h"
#include "concreteboard.h"
#include "controller.h"
#include "piece.h"
#include "textview.h"
#include "graphicview.h"
#include <sstream>


Controller::Controller():
textDisplay{nullptr},graphicDisplay{nullptr},chessBoard{nullptr}, white{nullptr}, scoreW{0}, black{nullptr}, scoreB{0}, status{0}, currPlayer{0}{}


Controller::~Controller(){}

void Controller:: cptFirstStep() {
	if (!currPlayer && white->getType()) {
		white->makeMove();
		currPlayer = 1;
		std::cout<< *textDisplay.get();
        }
}

bool Controller:: twoCptPlay() {
        if (white->getType() && black->getType()) {
		bool endOfGame = 0;
		while (!endOfGame) {
			if (currPlayer) {
				black->makeMove();
				std::cout<< *textDisplay.get();
				if (inCheck(0) && isCheckmate(0)) {
					std::cout<<"Checkmate! Black wins!"<<std::endl;
                			scoreB+=1;
        				white.reset();
        				black.reset();
        				chessBoard.reset();
        				textDisplay.reset();
        				graphicDisplay.reset();
        				status = 0;
					endOfGame = 1;
				} else if (inCheck(0)) {
                                	std::cout<<"White is in check."<<std::endl;
				} else if (isStalemate()){
					std::cout<<"Stalemate!"<<std::endl;
				} else {
					currPlayer = 0;
				}
			} else {
				white->makeMove();
				std::cout<< *textDisplay.get();
				if (inCheck(1) && isCheckmate(1)) {
                                	std:: cout<<"Checkmate! White wins!"<< std::endl;
                               		scoreW+=1;
                                	white.reset();
                                	black.reset();
                                	chessBoard.reset();
                                	textDisplay.reset();
                                	status = 0;
					endOfGame = 1;
                        	} else if (inCheck(1)) {
                                	std::cout<<"Black is in check."<<std::endl;
                        	} else if (isStalemate()) {
					std::cout<<"Stalemate!"<<std::endl;
				} else {
                                	currPlayer = 1;
                        	}
			}
		}
	return true;        
}
return false;
}


void Controller:: endGame(int whoWins) {
	if (whoWins == 1) scoreB += 1;
	if (!whoWins == 0) scoreW += 1;
	white.reset();
        black.reset();
        chessBoard.reset();
	textDisplay.reset();
	status = 0;
}


/**  Controller::newGame  **/
// called whenever "game w b" issued
//	1. check if a game is in process and throw exception
//	2. else, create new Board and Players and View(attach)
void Controller:: newGame(std::string &whitePlayer, std::string &blackPlayer){
	if (status > 1) throw std::string("A game is already in process!");
	/**NEW BOARD and pass Board* to Player**/

  	// initialize board and views;
	chessBoard = std::make_unique<ConcreteBoard> ();
	textDisplay = std::make_unique<TextView>();
	if (graphicDisplay) graphicDisplay.reset();
	graphicDisplay = std::make_unique<GraphicView>();

	// attach views to the board
	TextView *tv = textDisplay.get();
	GraphicView *gv = graphicDisplay.get();
	chessBoard->attachView(tv);
	chessBoard->attachView(gv);
	chessBoard->notify();
        std::cout << *textDisplay.get();

	// initialize players;
	ConcreteBoard *cb = chessBoard.get();
	if (whitePlayer == "human") {white = std::make_unique<Human> (0, cb);
	}else{	int levelW = whitePlayer.at(whitePlayer.size()-2) - '0';
		white = std::make_unique<Machine> (0, cb, levelW);
	}

	if (blackPlayer == "human") {black = std::make_unique<Human> (1, cb);
	}else{	int levelB = blackPlayer.at(blackPlayer.size()-2) - '0';
		black = std::make_unique<Machine> (1, cb, levelB);
	}
	currPlayer = 0;
	status = 2;
}


void Controller::resign () {
	if (currPlayer){
		scoreW +=1;
		std::cout << "White wins!" << std::endl;
	}else{
		scoreB+=1;
		std::cout << "Black wins!" << std::endl;
	}

	white.reset();
	black.reset();
	chessBoard.reset();
	textDisplay.reset();
	status = 0;
}


/**  Controller::move  **/
//called whenever "move a3 e3" issued
//	1. check if game in process
//	2. check pos1 pos2 validity. throw except (str)
//	3. throw except if player->makeMove throws except
void Controller:: move(std:: string &pos1, std:: string &pos2){
	int fromX;
  	int fromY;
  	int toX;
  	int toY;
	if (pos1.length() == 2 && pos2.length() == 2 && //status > 1 &&
	    pos1[0]<= 'h' && pos1[0] >= 'a' && pos2[0] <= 'h' && pos2[0] >= 'a' &&
	    pos1[1]<= '8' && pos1[1] >= '1' && pos2[1] <= '8' && pos2[1] >= '1'){
		/*conversion to APPROPRIATE FORMAT*/
		//(a8) == (0,0)
        	fromX = '8' - pos1[1];
                fromY = pos1[0] - 'a';
                toX = '8' - pos2[1];
                toY = pos2[0] - 'a';
	}else{throw std::string("Invalid command!");}
	if (currPlayer) {
		try{black->makeMove(fromX, fromY, toX, toY);}catch(...){throw std::string("Invalid move!");}
		currPlayer = 0;
	}else{
	try{white->makeMove(fromX, fromY, toX, toY);}catch(...){throw std::string("Invalid move!");}
		currPlayer = 1;
	}
	std::cout<< *textDisplay.get();
	if (currPlayer){
		if(black->getType()){
		// Machine
			black->makeMove();
			currPlayer = 0;
			std::cout<< *textDisplay.get();	}
	}else{
		if(white->getType()){
			white->makeMove();
			currPlayer = 1;
			std::cout<< *textDisplay.get();}
	}
}

/**  Controller::setUpEmptyBoard  **/
//called when "setup" issued
//  	1. check if game is running, throw excep (str)
// 	2. else, reset chessBoade, set status = 1 (setup Mode)
void Controller:: setupEmptyBoard(){
	if (chessBoard->getTimer() != 0){throw std::string("A game is already in process!");
	}else{
		chessBoard.reset();
		chessBoard = std::make_unique<ConcreteBoard> ("empty");

	        // attach views to the board
        	TextView *tv = textDisplay.get();
        	GraphicView *gv = graphicDisplay.get();
        	chessBoard->attachView(tv);
        	chessBoard->attachView(gv);
        	chessBoard->notify();
        	std::cout << *textDisplay.get();
		status = 1;//indicates setup mode
		//Player would have access to new empty board as the pointer chessBoard now points to new Board?
	}/*BOARD CONSTRUCTOR*/
}


//check if pos valid, if not throw(str)
//check if pos already have piece, throw(str)
//add piece
void Controller:: setupAdd(std::string &pos, char &type){
	int toX;
	int toY;
	if (status == 1 &&
            pos[0]<= 'h' && pos[0] >= 'a' && pos[1] <= '8' && pos[1] >= '1'){
                toX = '8' - pos[1];
                toY = pos[0] - 'a';
        }else{throw std::string("Invalid command!");}

	if (chessBoard->getPiece(toX, toY)) throw std::string("Position already has a piece!");
	try{ chessBoard->addPiece(toX, toY, type);
	}catch(...){}
	std::cout<< *textDisplay.get();
}


void Controller:: setupRemove(std::string &pos){
        int toX;
        int toY;
        if (status == 1 &&
            pos[0]<= 'h' && pos[0] >= 'a' && pos[1] <= '8' && pos[1] >= '1'){
                toX = '8' - pos[1];
                toY = pos[0] - 'a';
        }else{throw std::string("Invalid command!");}

	if(!chessBoard->getPiece(toX, toY)) throw std::string("Position does not have a piece to be removed!");

	try{ chessBoard->removePiece(toX, toY);
	}catch(...){}
	std::cout<< *textDisplay.get();

}


void Controller:: setupNextToPlay(std::string &color){
	if (status != 1) throw std::string("Invalid command!");
	if (color == "white" || color == "White" || color == "WHITE" || color == "W" || color == "w")
		{currPlayer = 0;
	}else if (color == "black" || color == "Black" || color == "BLACK" || color == "B" || color == "b")
		{currPlayer = 1;}
}


bool Controller:: setupDone(){
	if (status != 1) throw std::string("Invalid command!");
	std::cout<<"CHECKctrl:setupDone: 1"<<std::endl;
	if (chessBoard->getNum('k') != 1 || chessBoard->getNum('K') != 1) return false;
	std::cout<<"CHECKctrl:setupDone: 2"<<std::endl;
	for (int i = 0; i < SIZE; ++i) {
		if (chessBoard->getPiece(0,i) &&
		   (chessBoard->getPiece(0,i)->getType() == 'p' || 
		    chessBoard->getPiece(0,i)->getType() == 'P')) {
			return false;
		}
		if (chessBoard->getPiece(7,i) &&
                   (chessBoard->getPiece(7,i)->getType() == 'p' || 
		    chessBoard->getPiece(7,i)->getType() == 'P')) {
                        return false;
                }
	}
	if (chessBoard->inCheck(1) || chessBoard->inCheck(0)) return false;
	status = 2;
	std::cout<< *textDisplay.get();
	return true;
}


//1. King of color has no possible moves
bool Controller:: isCheckmate(bool color){
	//find pointer to King
	King * theKing = chessBoard->getKing(color);
	if(theKing->possibleMoves(chessBoard.get()).size() == 0){ return true;}
	return false;
}


bool Controller:: isStalemate(){
	if (currPlayer && chessBoard->inCheck(1)) return false;
	if (currPlayer && chessBoard->inCheck(0)) return false;
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (chessBoard->getPiece(i,j) && chessBoard->getPiece(i,j)->getColor() == currPlayer
			    && chessBoard->getPiece(i,j)->possibleMoves(chessBoard.get()).size() != 0) {
				return false;
			}
		}
	}
        return true;
}


//1. King
bool Controller:: inCheck(bool color) {
	return chessBoard->inCheck(color);

}

//   Controller::isPromote
//1. check if pos1,pos2 are dest on board
//2. check if pos2 is opponent's last row
//3. checi if pos1 is Pawn
//4. check legal move
//5. return ture.
bool Controller::isPromote(std::string &pos1, std::string &pos2){
        int fromX;
        int fromY;
        int toX;
        int toY;
        if (pos1[0]<= 'h' && pos1[0] >= 'a' && pos2[0] <= 'h' && pos2[0] >= 'a' &&
            pos1[1]<= '8' && pos1[1] >= '1' && pos2[1] <= '8' && pos2[1] >= '1'){
        /*conversion to APPROPRIATE FORMAT*/
        //(a8) == (0,0)
                fromX = '8' - pos1[1];
                fromY = pos1[0] - 'a';
                toX = '8' - pos2[1];
                toY = pos2[0] - 'a';
        }else{throw std::string("Invalid command!");}
	Piece * temp = chessBoard->getPiece(fromX, fromY);
	if (currPlayer && temp && temp->getType() =='p'&& toX == 7 &&
	    temp->checkValidity(chessBoard.get(), toX, toY)){std:: cout << "black true" << std:: endl; return true;}
        if (!currPlayer && temp && temp->getType() =='P'&& toX == 0 &&
	    temp->checkValidity(chessBoard.get(), toX, toY)){std:: cout << "white true" << std:: endl; return true;}
	return false;
}


void Controller::promoteP(std::string &pos1, std::string &pos2, char type){
	int fromX = '8' - pos1[1];
        int fromY = fromY = pos1[0] - 'a';
        int toX = '8' - pos2[1];
        int toY = pos2[0] - 'a';
	if (currPlayer) {
                try{black->makeMove(fromX, fromY, toX, toY);}catch(...){throw std::string("Invalid move!");}
        }else{
        	try{white->makeMove(fromX, fromY, toX, toY);}catch(...){throw std::string("Invalid move!");}
        }
	chessBoard->removePiece(toX, toY);
        chessBoard->addPiece(toX, toY, type);
	currPlayer = (currPlayer)? 0 : 1;
        std::cout<< *textDisplay.get();
        if (currPlayer){
                if(black->getType()){
                //Machine
                        black->makeMove();
                        currPlayer = 0;
                        std::cout<< *textDisplay.get();
                }
        }else{
                if(white->getType()){
                        white->makeMove();
                        currPlayer = 1;
                        std::cout<< *textDisplay.get();
                }
        }
}

