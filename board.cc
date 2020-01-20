#include "board.h"
#include "view.h"
#include "textview.h"
#include "graphicview.h"
using namespace std;


Board:: ~Board() {}


void Board:: attachView(TextView *v) {
  theViews.emplace_back(v);
}


void Board:: attachView(GraphicView *v) {
  theViews.emplace_back(v);
}

