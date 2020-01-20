#ifndef _PLAYER_H
#define _PLAYER_H
#include <memory>
#include <string>

class ConcreteBoard;

class Player{
        protected:
	bool color;
	bool type;
        ConcreteBoard * chessBoard;
	public:
	Player(bool color, ConcreteBoard * board, bool type);
	~Player();
	bool  getColor(){return color;}
	bool  getType(){return type;}
	virtual void makeMove(int fromX, int fromY, int toX, int toY)=0;
	virtual void makeMove() = 0;
};

class Human: public Player{
	public:
	Human(bool color, ConcreteBoard * board);
	void makeMove(int fromX, int fromY, int toX, int toY)override;
	void makeMove() {}
};

class Machine: public Player{
	int level;
	void makeMoveLv1();
	void makeMoveLv2();
	void makeMoveLv3();
	void makeMoveLv4();
	public:
	Machine(bool color, ConcreteBoard * board, int level);
	void makeMove()override;
	void makeMove(int fromX, int fromY, int toX, int toY)override{}
};

#endif
