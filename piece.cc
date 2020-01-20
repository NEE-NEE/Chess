#include "piece.h"
#include "concreteboard.h"
#include <string>


Piece::Piece(int color, int xCor, int yCor, char type)
	: color{ color }, xCor{ xCor }, yCor{ yCor }, type{ type } {}

int Piece::getColor()
{
	return color;
}

int& Piece::getX()
{
	return xCor;
}

int& Piece::getY()
{
	return yCor;
}

char& Piece::getType()
{
	return type;
}

int& Piece::getStep()
{
	return step;
}

Knight::Knight(int color, int xCor, int yCor, char type)
	: Piece(color, xCor, yCor, type) {}

std::vector<std::vector<int>> Knight::possibleMoves(const ConcreteBoard* board)
{
	std::vector<std::vector<int>> choices;
	const int xSrc = xCor;
	const int ySrc = yCor;
	int xDst;
	int yDst;
	xDst = xSrc + 2;
	if (0 <= xDst && xDst <= 7)
	{
		yDst = ySrc + 1;
		if (0 <= yDst && yDst <= 7)
		{
			if (!(board->getPiece(xDst, yDst)) || (board->getPiece(xDst, yDst)->getColor()) != getColor())
			{
				std::vector<int> m = { xDst, yDst };
				choices.push_back(m);
			}
		}
		yDst = ySrc - 1;
		if (0 <= yDst && yDst <= 7)
		{
			if (!(board->getPiece(xDst, yDst)) || (board->getPiece(xDst, yDst)->getColor()) != getColor()) // move only
			{
				std::vector<int> m = { xDst, yDst };
				choices.push_back(m);
			}
		}
	}
	xDst = xSrc - 2;
	if (0 <= xDst && xDst <= 7)
	{
		yDst = ySrc + 1;
		if (0 <= yDst && yDst <= 7)
		{
			if (!board->getPiece(xDst, yDst) || board->getPiece(xDst, yDst)->getColor() != getColor()) // move only
			{
				std::vector<int> m = { xDst, yDst };
				choices.push_back(m);
			}
		}
		yDst = ySrc - 1;
		if (0 <= yDst && yDst <= 7)
		{
			if (!board->getPiece(xDst, yDst) || board->getPiece(xDst, yDst)->getColor() != getColor()) // move only
			{
				std::vector<int> m = { xDst, yDst };
				choices.push_back(m);
			}
		}
	}
	xDst = xSrc + 1;
	if (0 <= xDst && xDst <= 7)
	{
		yDst = ySrc + 2;
		if (0 <= yDst && yDst <= 7)
		{
			if (!board->getPiece(xDst, yDst) || board->getPiece(xDst, yDst)->getColor() != getColor()) // move only
			{
				std::vector<int> m = { xDst, yDst };
				choices.push_back(m);
			}
		}
		yDst = ySrc - 2;
		if (0 <= yDst && yDst <= 7)
		{
			if (!board->getPiece(xDst, yDst) || board->getPiece(xDst, yDst)->getColor() != getColor()) // move only
			{
				std::vector<int> m = { xDst, yDst };
				choices.push_back(m);
			}
		}
	}
	xDst = xSrc - 1;
	if (0 <= xDst && xDst <= 7)
	{
		yDst = ySrc + 2;
		if (0 <= yDst && yDst <= 7)
		{
			if (!board->getPiece(xDst, yDst) || board->getPiece(xDst, yDst)->getColor() != getColor()) // move only
			{
				std::vector<int> m = { xDst, yDst };
				choices.push_back(m);
			}
		}
		yDst = ySrc - 2;
		if (0 <= yDst && yDst <= 7)
		{
			if (!board->getPiece(xDst, yDst) || board->getPiece(xDst, yDst)->getColor() != getColor()) // move only
			{
				std::vector<int> m = { xDst, yDst };
				choices.push_back(m);
			}
		}
	}
	board->filterPossibleMoves(choices, xCor, yCor, color);
	return choices;
}

King::King(int color, int xCor, int yCor, char type)
	: Piece(color, xCor, yCor, type) {}

std::vector<std::vector<int>> King::possibleMoves(const ConcreteBoard* board)
{
	std::vector<std::vector<int>> choices;
	const int xSrc = xCor;
	const int ySrc = yCor;
	int xDst;
	int yDst;
	xDst = xSrc + 1;
	if (0 <= xDst && xDst <= 7)
	{
		yDst = ySrc + 1;
		if (0 <= yDst && yDst <= 7)
		{
			if (!board->getPiece(xDst, yDst) || board->getPiece(xDst, yDst)->getColor() != color) // move only
			{
				std::vector<int> m = { xDst, yDst };
				choices.push_back(m);
			}
		}
		yDst = ySrc;
		if (0 <= yDst && yDst <= 7)
		{
			if (!board->getPiece(xDst, yDst) || board->getPiece(xDst, yDst)->getColor() != color)
			{
				std::vector<int> m = { xDst, yDst };
				choices.push_back(m);
			}
		}
		yDst = ySrc;
		if (0 <= yDst && yDst <= 7)
		{
			if (!board->getPiece(xDst, yDst) || board->getPiece(xDst, yDst)->getColor() != color)
			{
				std::vector<int> m = { xDst, yDst };
				choices.push_back(m);
			}
		}
		yDst = ySrc - 1;
		if (0 <= yDst && yDst <= 7)
		{
			if (!board->getPiece(xDst, yDst) || board->getPiece(xDst, yDst)->getColor() != color)
			{
				std::vector<int> m = { xDst, yDst };
				choices.push_back(m);
			}
		}
	}
	xDst = xSrc;
	if (0 <= xDst && xDst <= 7)
	{
		yDst = ySrc + 1;
		if (0 <= yDst && yDst <= 7)
		{
			if (!board->getPiece(xDst, yDst) || board->getPiece(xDst, yDst)->getColor() != color) // move only
			{
				std::vector<int> m = { xDst, yDst };
				choices.push_back(m);
			}
		}
		yDst = ySrc - 1;
		if (0 <= yDst && yDst <= 7)
		{
			if (!board->getPiece(xDst, yDst) || board->getPiece(xDst, yDst)->getColor() != color) // move only
			{
				std::vector<int> m = { xDst, yDst };
				choices.push_back(m);
			}
		}
	}
	xDst = xSrc - 1;
	if (0 <= xDst && xDst <= 7)
	{
		yDst = ySrc + 1;
		if (0 <= yDst && yDst <= 7)
		{
			if (!board->getPiece(xDst, yDst) || board->getPiece(xDst, yDst)->getColor() != color) // move only
			{
				std::vector<int> m = { xDst, yDst };
				choices.push_back(m);
			}
		}
		yDst = ySrc;
		if (0 <= yDst && yDst <= 7)
		{
			if (!board->getPiece(xDst, yDst) || board->getPiece(xDst, yDst)->getColor() != color)
			{
				std::vector<int> m = { xDst, yDst };
				choices.push_back(m);
			}
		}
		yDst = ySrc - 1;
		if (0 <= yDst && yDst <= 7)
		{
			if (!board->getPiece(xDst, yDst) || board->getPiece(xDst, yDst)->getColor() != color) // move only
			{
				std::vector<int> m = { xDst, yDst };
				choices.push_back(m);
			}
		}
	}
	//castling
	if (getColor()) //black
	{
		if (step == 0 && board->getPiece(0, 0) && board->getPiece(0, 0)->getType() == 'r' && board->getPiece(0, 0)->getStep() == 0
			&& !board->getPiece(0, 1) & !board->getPiece(0, 2) && !board->getPiece(0, 3))
		{
			std::vector<int> m = { 0,2 };
			choices.push_back(m);
		}
		if (step == 0 && board->getPiece(0, 7) && board->getPiece(0, 7)->getType() == 'r' && board->getPiece(0, 7)->getStep() == 0
			&& !board->getPiece(0, 5) && !board->getPiece(0, 6))
		{
			std::vector<int> m = { 0,6 };
			choices.push_back(m);
		}
	}
	else //white
	{
		if (step == 0 && board->getPiece(7, 0) && board->getPiece(7, 0)->getType() == 'R' && board->getPiece(7, 0)->getStep() == 0
			&& !board->getPiece(7, 1) && !board->getPiece(7, 2) && !board->getPiece(7, 3))
		{
			std::vector<int> m = { 7,2 };
			choices.push_back(m);
		}
		if (step == 0 && board->getPiece(7, 7)  && board->getPiece(7, 7)->getType() == 'R' && board->getPiece(7, 7)->getStep() == 0
			&& !board->getPiece(7, 5) && !board->getPiece(7, 6))
		{
			std::vector<int> m = { 7,6 };
			choices.push_back(m);
		}
	}
	board->filterPossibleMoves(choices, xCor, yCor, color);
	return choices;
}

Bishop::Bishop(int color, int xCor, int yCor, char type)
	: Piece(color, xCor, yCor, type) {}

std::vector<std::vector<int>> Bishop::possibleMoves(const ConcreteBoard* board)
{
	std::vector<std::vector<int>> choices;
	const int xSrc = xCor;
	const int ySrc = yCor;
	int xDst;
	int yDst;
	for (int i = -7; i <0; ++i)
	{
		xDst = xSrc + i;
		yDst = ySrc + i;
		if ((0 <= xDst && xDst <= 7) && (0 <= yDst && yDst <= 7) && (!board->getPiece(xDst, yDst) || board->getPiece(xDst, yDst)->getColor() != color))
		{
			bool blocked = 0;
			for (int j = 1; j<-i; ++j)
			{
				if (board->getPiece(xSrc - j, ySrc - j)) blocked = 1; break;
			}
			if (!blocked)
			{
				std::vector<int> m = { xDst, yDst };
				choices.push_back(m);
			}
		}
		xDst = xSrc - i;
		yDst = ySrc + i;
		if ((0 <= xDst && xDst <= 7) && (0 <= yDst && yDst <= 7) && (!board->getPiece(xDst, yDst) || board->getPiece(xDst, yDst)->getColor() != color))
		{
			bool blocked = 0;
			for (int j = 1; j<-i; ++j)
			{
				if (board->getPiece(xSrc + j, ySrc - j)) blocked = 1; break;
			}
			if (!blocked)
			{
				std::vector<int> m = { xDst, yDst };
				choices.push_back(m);
			}
		}
	}
	for (int i = 7; i >0; --i)
	{
		xDst = xSrc - i;
		yDst = ySrc + i;
		if ((0 <= xDst && xDst <= 7) && (0 <= yDst && yDst <= 7) && (!board->getPiece(xDst, yDst) || board->getPiece(xDst, yDst)->getColor() != color))
		{
			bool blocked = 0;
			for (int j = 1; j<i; ++j)
			{
				if (board->getPiece(xSrc - j, ySrc + j)) blocked = 1; break;
			}
			if (!blocked)
			{
				std::vector<int> m = { xDst, yDst };
				choices.push_back(m);
			}
		}
		xDst = xSrc + i;
		yDst = ySrc + i;
		if ((0 <= xDst && xDst <= 7) && (0 <= yDst && yDst <= 7) && (!board->getPiece(xDst, yDst) || board->getPiece(xDst, yDst)->getColor() != color))
		{
			bool blocked = 0;
			for (int j = 1; j<i; ++j)
			{
				if (board->getPiece(xSrc + j, ySrc + j)) blocked = 1; break;
			}
			if (!blocked)
			{
				std::vector<int> m = { xDst, yDst };
				choices.push_back(m);
			}
		}
	}
	board->filterPossibleMoves(choices, xCor, yCor, color);
	return choices;
}

Rook::Rook(int color, int xCor, int yCor, char type)
	: Piece(color, xCor, yCor, type) {}


std::vector<std::vector<int>> Rook::possibleMoves(const ConcreteBoard* board)
{
	std::vector<std::vector<int>> choices;
	const int xSrc = xCor;
	const int ySrc = yCor;
	int xDst;
	int yDst;
	for (int i = 0; i<8; ++i)
	{
		xDst = xSrc - i;
		if (0 <= xDst && xDst <= 7)
		{
			yDst = ySrc;
			if (!board->getPiece(xDst, yDst) || board->getPiece(xDst, yDst)->getColor() != getColor()) // move only
			{
				bool blocked = 0;
				for (int j = 1; j<i; ++j)
				{
					if (board->getPiece(xSrc - j, ySrc)) blocked = 1; break;
				}
				if (!blocked)
				{
					std::vector<int> m = { xDst, yDst };
					choices.push_back(m);
				}
			}
		}
		xDst = xSrc + i;
		if (0 <= xDst && xDst <= 7)
		{
			yDst = ySrc;
			if (!board->getPiece(xDst, yDst) || board->getPiece(xDst, yDst)->getColor() != getColor()) // move only
			{
				bool blocked = 0;
				for (int j = 1; j<i; ++j)
				{
					if (board->getPiece(xSrc + j, ySrc)) blocked = 1; break;
				}
				if (!blocked)
				{
					std::vector<int> m = { xDst, yDst };
					choices.push_back(m);
				}
			}
		}
		yDst = ySrc - i;
		if (0 <= yDst && yDst <= 7)
		{
			xDst = xSrc;
			if (!board->getPiece(xDst, yDst) || board->getPiece(xDst, yDst)->getColor() != getColor()) // move only
			{
				bool blocked = 0;
				for (int j = 1; j < i; ++j)
				{
					if (board->getPiece(xSrc, ySrc - j)) blocked = 1; break;
				}
				if (!blocked)
				{
					std::vector<int> m = { xDst, yDst };
					choices.push_back(m);
				}
			}
		}
		yDst = ySrc + i;
		if (0 <= yDst && yDst <= 7)
		{
			xDst = xSrc;
			if (!board->getPiece(xDst, yDst) || board->getPiece(xDst, yDst)->getColor() != getColor()) // move only
			{
				bool blocked = 0;
				for (int j = 1; j < i; ++j)
				{
					if (board->getPiece(xSrc, ySrc + j)) blocked = 1; break;
				}
				if (!blocked)
				{
					std::vector<int> m = { xDst, yDst };
					choices.push_back(m);
				}
			}
		}

	}
	board->filterPossibleMoves(choices, xCor, yCor, color);
	return choices;
}


Queen::Queen(int color, int xCor, int yCor, char type)
	: Piece(color, xCor, yCor, type) {}

std::vector<std::vector<int>> Queen::possibleMoves(const ConcreteBoard* board)
{
	std::vector<std::vector<int>> m2;
	const int xSrc = xCor;
	const int ySrc = yCor;
	int xDst;
	int yDst;
	for (int i = 0; i<8; ++i)
	{
		xDst = xSrc - i;
		if (0 <= xDst && xDst <= 7)
		{
			yDst = ySrc;
			if (!board->getPiece(xDst, yDst) || board->getPiece(xDst, yDst)->getColor() != getColor()) // move only
			{
				bool blocked = 0;
				for (int j = 1; j<i; ++j)
				{
					if (board->getPiece(xSrc - j, ySrc)) blocked = 1; break;
				}
				if (!blocked)
				{
					std::vector<int> m = { xDst, yDst };
					m2.push_back(m);
				}
			}
		}
		xDst = xSrc + i;
		if (0 <= xDst && xDst <= 7)
		{
			yDst = ySrc;
			if (!board->getPiece(xDst, yDst) || board->getPiece(xDst, yDst)->getColor() != getColor()) // move only
			{
				bool blocked = 0;
				for (int j = 1; j<i; ++j)
				{
					if (board->getPiece(xSrc + j, ySrc)) blocked = 1; break;
				}
				if (!blocked)
				{
					std::vector<int> m = { xDst, yDst };
					m2.push_back(m);
				}
			}
		}
		yDst = ySrc - i;
		if (0 <= yDst && yDst <= 7)
		{
			xDst = xSrc;
			if (!board->getPiece(xDst, yDst) || board->getPiece(xDst, yDst)->getColor() != getColor()) // move only
			{
				bool blocked = 0;
				for (int j = 1; j < i; ++j)
				{
					if (board->getPiece(xSrc, ySrc - j)) blocked = 1; break;
				}
				if (!blocked)
				{
					std::vector<int> m = { xDst, yDst };
					m2.push_back(m);
				}
			}
		}
		yDst = ySrc + i;
		if (0 <= yDst && yDst <= 7)
		{
			xDst = xSrc;
			if (!board->getPiece(xDst, yDst) || board->getPiece(xDst, yDst)->getColor() != getColor()) // move only
			{
				bool blocked = 0;
				for (int j = 1; j < i; ++j)
				{
					if (board->getPiece(xSrc, ySrc + j)) blocked = 1; break;
				}
				if (!blocked)
				{
					std::vector<int> m = { xDst, yDst };
					m2.push_back(m);
				}
			}
		}

	}
	
	std::vector<std::vector<int>> m1;
	for (int i = -7; i <0; ++i)
	{
		xDst = xSrc + i;
		yDst = ySrc + i;
		if ((0 <= xDst && xDst <= 7) && (0 <= yDst && yDst <= 7) && (!board->getPiece(xDst, yDst) || board->getPiece(xDst, yDst)->getColor() != color))
		{
			bool blocked = 0;
			for (int j = 1; j<-i; ++j)
			{
				if (board->getPiece(xSrc - j, ySrc - j)) blocked = 1; break;
			}
			if (!blocked)
			{
				std::vector<int> m = { xDst, yDst };
				m1.push_back(m);
			}
		}
		xDst = xSrc - i;
		yDst = ySrc + i;
		if ((0 <= xDst && xDst <= 7) && (0 <= yDst && yDst <= 7) && (!board->getPiece(xDst, yDst) || board->getPiece(xDst, yDst)->getColor() != color))
		{
			bool blocked = 0;
			for (int j = 1; j<-i; ++j)
			{
				if (board->getPiece(xSrc + j, ySrc - j)) blocked = 1; break;
			}
			if (!blocked)
			{
				std::vector<int> m = { xDst, yDst };
				m1.push_back(m);
			}
		}
	}
	for (int i = 7; i >0; --i)
	{
		xDst = xSrc - i;
		yDst = ySrc + i;
		if ((0 <= xDst && xDst <= 7) && (0 <= yDst && yDst <= 7) && (!board->getPiece(xDst, yDst) || board->getPiece(xDst, yDst)->getColor() != color))
		{
			bool blocked = 0;
			for (int j = 1; j<i; ++j)
			{
				if (board->getPiece(xSrc - j, ySrc + j)) blocked = 1; break;
			}
			if (!blocked)
			{
				std::vector<int> m = { xDst, yDst };
				m1.push_back(m);
			}
		}
		xDst = xSrc + i;
		yDst = ySrc + i;
		if ((0 <= xDst && xDst <= 7) && (0 <= yDst && yDst <= 7) && (!board->getPiece(xDst, yDst) || board->getPiece(xDst, yDst)->getColor() != color))
		{
			bool blocked = 0;
			for (int j = 1; j<i; ++j)
			{
				if (board->getPiece(xSrc + j, ySrc + j)) blocked = 1; break;
			}
			if (!blocked)
			{
				std::vector<int> m = { xDst, yDst };
				m1.push_back(m);
			}
		}
	}
	std::vector<std::vector<int>> m;
	m.reserve(m1.size() + m2.size());
	m.insert(m.end(), m1.begin(), m1.end());
	m.insert(m.end(), m2.begin(), m2.end());
	board->filterPossibleMoves(m, xCor, yCor, color);
	return m;
}

Pawn::Pawn(int color, int xCor, int yCor, char type)
	: Piece(color, xCor, yCor, type) {}

std::vector<std::vector<int>> Pawn::possibleMoves(const ConcreteBoard* board)
{
	std::vector<std::vector<int>> choices;
	const int xSrc = xCor;
	const int ySrc = yCor;
	int xDst;
	int yDst;
	if (getColor()) //black
	{
		if (step) //moved
		{
			xDst = xSrc + 1;
			if (0 <= xDst && xDst <= 7)
			{
				if (!board->getPiece(xDst, ySrc)) {
					std::vector<int> m = { xDst, ySrc };
					choices.push_back(m);
				}
				yDst = ySrc - 1;
				if (0 <= yDst && yDst <= 7 && board->getPiece(xDst, yDst) && board->getPiece(xDst, yDst)->getColor() != color)
				{
					std::vector<int> m = { xDst, yDst };
					choices.push_back(m);
				}
				yDst = ySrc + 1;
				if (0 <= yDst && yDst <= 7 && board->getPiece(xDst, yDst) && board->getPiece(xDst, yDst)->getColor() != color)
				{
					std::vector<int> m = { xDst, yDst };
					choices.push_back(m);
				}
			}
		}
		else
		{
			xDst = xSrc + 1;
			if (0 <= xDst && xDst <= 7)
			{
				if (!board->getPiece(xDst, ySrc)) {
					std::vector<int> m = { xDst, ySrc };
					choices.push_back(m);
				}
				yDst = ySrc - 1;
				if (0 <= yDst && yDst <= 7 && board->getPiece(xDst, yDst) && board->getPiece(xDst, yDst)->getColor() != color)
				{
					std::vector<int> m = { xDst, yDst };
					choices.push_back(m);
				}
				yDst = ySrc + 1;
				if (0 <= yDst && yDst <= 7 && board->getPiece(xDst, yDst) && board->getPiece(xDst, yDst)->getColor() != color)
				{
					std::vector<int> m = { xDst, yDst };
					choices.push_back(m);
				}


			}
			xDst = xSrc + 2;
			if (0 <= xDst && xDst <= 7)
			{
				if (!board->getPiece(xDst, ySrc)) {
					std::vector<int> m = { xDst, ySrc };
					choices.push_back(m);
				}
			}
		}
		//en passant
		xDst = xSrc + 1;
		yDst = ySrc - 1;
		if (xDst >= 0 && xDst <= 7 && yDst >= 0 && yDst <= 7 && board->getPiece(xSrc, yDst) && board->getPiece(xSrc, yDst)->getType() == 'P'
			&& board->getPiece(xSrc, yDst)->getStep() == board->getTimer())
		{
			std::vector<int> m = { xDst, yDst };
			choices.push_back(m);
		}
		xDst = xSrc + 1;
		yDst = ySrc + 1;
		if (xDst >= 0 && xDst <= 7 && yDst >= 0 && yDst <= 7 && board->getPiece(xSrc, yDst) && board->getPiece(xSrc, yDst)->getType() == 'P'
			&& board->getPiece(xSrc, yDst)->getStep() == board->getTimer())
		{
			std::vector<int> m = { xDst, yDst };
			choices.push_back(m);
		}
	}
	else //white
	{
		if (step) //moved
		{
			xDst = xSrc - 1;
			if (0 <= xDst && xDst <= 7)
			{
				if (!board->getPiece(xDst, ySrc))
				{
					std::vector<int> m = { xDst, ySrc };
					choices.push_back(m);
				}
				yDst = ySrc - 1;
				if (0 <= yDst && yDst <= 7 && board->getPiece(xDst, yDst) && board->getPiece(xDst, yDst)->getColor() != color)
				{
					std::vector<int> m = { xDst, yDst };
					choices.push_back(m);
				}
				yDst = ySrc + 1;
				if (0 <= yDst && yDst <= 7 && board->getPiece(xDst, yDst) && board->getPiece(xDst, yDst)->getColor() != color)
				{
					std::vector<int> m = { xDst, yDst };
					choices.push_back(m);
				}
			}
		}
		else
		{
			xDst = xSrc - 1;
			if (0 <= xDst && xDst <= 7)
			{
				if (!board->getPiece(xDst, ySrc)) {
					std::vector<int> m = { xDst, ySrc };
					choices.push_back(m);
				}
				yDst = ySrc - 1;
				if (0 <= yDst && yDst <= 7 && board->getPiece(xDst, yDst) && board->getPiece(xDst, yDst)->getColor() != color)
				{
					std::vector<int> m = { xDst, yDst };
					choices.push_back(m);
				}
				yDst = ySrc + 1;
				if (0 <= yDst && yDst <= 7 && board->getPiece(xDst, yDst) && board->getPiece(xDst, yDst)->getColor() != color)
				{
					std::vector<int> m = { xDst, yDst };
					choices.push_back(m);
				}

			}
			xDst = xSrc - 2;
			if (0 <= xDst && xDst <= 7)
			{
				if (!board->getPiece(xDst, ySrc)) {
					std::vector<int> m = { xDst, ySrc };
					choices.push_back(m);
				}
			}
		}
		//en passant
		xDst = xSrc - 1;
		yDst = ySrc - 1;
		if (xDst >= 0 && xDst <= 7 && yDst >= 0 && yDst <= 7 && board->getPiece(xSrc, yDst) && board->getPiece(xSrc, yDst)->getType() == 'p'
			&& board->getPiece(xSrc, yDst)->getStep() == board->getTimer())
		{
			std::vector<int> m = { xDst, yDst };
			choices.push_back(m);
		}
		xDst = xSrc - 1;
		yDst = ySrc + 1;
		if (xDst >= 0 && xDst <= 7 && yDst >= 0 && yDst <= 7 && board->getPiece(xSrc, yDst) && board->getPiece(xSrc, yDst)->getType() == 'p'
			&& board->getPiece(xSrc, yDst)->getStep() == board->getTimer())
		{
			std::vector<int> m = { xDst, yDst };
			choices.push_back(m);
		}
	}

	board->filterPossibleMoves(choices, xCor, yCor, color);
	return choices;
}


bool Piece::checkValidity(const ConcreteBoard* board, int xDst, int yDst)
{
	std::vector<std::vector<int>> choices = possibleMoves(board);

	for (auto m : choices)
	{
		if (m[0] == xDst && m[1] == yDst)
		{
			return true;
		}
	}
	return false;
}
