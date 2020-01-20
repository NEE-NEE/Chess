#ifndef _CONTROLLER_H
#define _CONTROLLER_H
#include <string>
#include <memory>

//fwd declaration
class Player;
class ConcreteBoard;
class TextView;
class GraphicView;

class Controller{
	std::unique_ptr<TextView> textDisplay;
	std::unique_ptr<GraphicView> graphicDisplay;
	std::unique_ptr<ConcreteBoard> chessBoard;
        /*CONTROL OUTPUT*/
	std::unique_ptr<Player> white;
	int scoreW;
	std::unique_ptr<Player> black;
	int scoreB;
	int status;
	/* status code
	   0 No Game in process
	   1 Setup Mode
	   2 A game in process
	   3
	*/
	bool currPlayer;
	/* 0 white to play
	   1 black to play*/
	public:
	Controller();
	~Controller();

	int getScoreW() const noexcept {return scoreW;}
	int getScoreB() const noexcept {return scoreB;}

	void newGame(std::string &whitePlayer, std::string &blackPlayer);
	void resign();
	void move(std:: string &pos1, std:: string &pos2);
	bool twoCptPlay();
	void cptFirstStep();
	void endGame(int whoWins);

	void setupEmptyBoard();
	void setupAdd(std::string &pos, char &type);
	void setupRemove(std::string &pos);
	void setupNextToPlay(std::string &color);
	bool setupDone();

	bool isCheckmate(bool color);
	bool isStalemate();
	bool inCheck(bool color);
	bool isPromote(std::string &pos1, std::string &pos2);
	void promoteP(std::string &pos1, std::string &pos2, char type);

	void display();/*call Board::attachView*/

	std::string checkStatus();

};

#endif
