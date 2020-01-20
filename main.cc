#include "controller.h"
#include "player.h"
#include "board.h"
#include "concreteboard.h"
#include "view.h"
#include "textview.h"
#include "graphicview.h"
#include "piece.h"
#include <iostream>
using namespace std;

int main(){
	Controller ctrl;
	string s;
	while(cin >> s){
		//terminate if EOF
		/*user choose Graphic or Text*/
	try {
		if (s == "game"){
			string whitePlayer;
			string blackPlayer;
			cin >> whitePlayer;
			cin >> blackPlayer;
			//if a game is in process newGame throws exception
			//loop continues
			try{
			ctrl.newGame(whitePlayer, blackPlayer);}catch(string &e){ cout<< e << endl;}
			if(!ctrl.twoCptPlay())ctrl.cptFirstStep();
		}else if(s == "resign"){
			ctrl.resign();
		}else if(s == "move"){
			string pos1;
			string pos2;
			cin >> pos1;
			cin >> pos2;
			if (ctrl.isPromote(pos1, pos2)){
				char promoteTo;
				cin >> promoteTo;
				if (promoteTo != 'k' && promoteTo != 'K') ctrl.promoteP(pos1, pos2, promoteTo);
			} else {try{ctrl.move(pos1, pos2);}catch(string &e){ cout<< e<< endl;}}
			if (ctrl.inCheck(1) && ctrl.isCheckmate(1)){
				cout<<"Checkmate! White wins!"<<endl;
				ctrl.endGame(0);
			} else if (ctrl.inCheck(1)) { 
                                cout<<"Black is in check."<<endl;
			} else if (ctrl.isStalemate()) {
				cout <<"Stalemate!"<<endl;
				ctrl.endGame(-1);
                        } else if (ctrl.inCheck(0) && ctrl.isCheckmate(0)) {
                                cout<<"Checkmate! Black wins!"<<endl;
				ctrl.endGame(1);
			} else if (ctrl.inCheck(0)) {
				cout<<"White is in check."<<endl;
			}
		}else if(s == "setup"){
			try{ctrl.setupEmptyBoard();	}catch(string &e){ cout << e << endl;}
			string c;
			while (cin >>c ) {
				if (c == "+") {
					char type;
					cin >>type;
					string pos;
                        		cin >> pos;
					try{ctrl.setupAdd(pos, type);}catch(string &e){cout<<e<<endl;}
				}else if(c == "-"){
					string pos;
					cin >> pos;
					try{ctrl.setupRemove(pos);}catch(string &e){cout<<e<<endl;}
				}else if(c == "="){
					string color;
					cin >> color;
					try{ctrl.setupNextToPlay(color);}catch(string &e){cout << e<< endl;}
				}else if(c == "done"){
					try{if (ctrl.setupDone()) break;}catch(string &e){cout<<e<<endl;}
				}
			}
		}
	} catch(...){}
	}

	cout<<"Final Score:" << endl << "White: " << ctrl.getScoreW() <<endl;
	cout << "Black: " << ctrl.getScoreB()<< endl;


}
