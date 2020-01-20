#ifndef GRAPHICVIEW_H
#define GRAPHICVIEW_H
#include <iostream>
#include "window.h"
#include "view.h"
#include "board.h"

extern int BOARDSIZE;
extern const int SIDEBAR;

// forward declaration
class ConcreteBoard;

class GraphicView: public View {
  Xwindow x{BOARDSIZE+SIDEBAR, BOARDSIZE+SIDEBAR};
 public:
   GraphicView ();
   void update(const ConcreteBoard* b) override;
};

#endif

