#ifndef PIECE_H
#define PIECE_H

#include<vector>

class ConcreteBoard;
class Piece
{
protected:
	int color;
	int xCor;
	int yCor;
	int step = 0;
	char type;
public:
	Piece(int color, int xCor, int yCor, char type);
	int getColor();
	int &getX();
	int &getY();
	char& getType();
	int &getStep();
	virtual std::vector<std::vector<int>> possibleMoves(const ConcreteBoard* board) = 0;
	bool checkValidity(const ConcreteBoard* board, int xDst, int yDst);
};

class King : public Piece
{
public:
	King(int color, int xCor, int yCor, char type);
	std::vector<std::vector<int>> possibleMoves(const ConcreteBoard* board);
};

class Queen : public Piece
{
public:
	Queen(int color, int xCor, int yCor, char type);
	std::vector<std::vector<int>> possibleMoves(const ConcreteBoard* board);
};

class Bishop : public Piece
{
public:
	Bishop(int color, int xCor, int yCor, char type);
	std::vector<std::vector<int>> possibleMoves(const ConcreteBoard* board);
};

class Rook : public Piece
{
public:
	Rook(int color, int xCor, int yCor, char type);
	std::vector<std::vector<int>> possibleMoves(const ConcreteBoard* board);
};

class Knight : public Piece
{
public:
	Knight(int color, int xCor, int yCor, char type);
	std::vector<std::vector<int>> possibleMoves(const ConcreteBoard* board);
};

class Pawn : public Piece
{
public:
	Pawn(int color, int xCor, int yCor, char type);
	std::vector<std::vector<int>> possibleMoves(const ConcreteBoard* board);
};


#endif // !PIECE_H
