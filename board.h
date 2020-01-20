#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>


// forward declaration
class TextView;
class GraphicView;
class View;


// Board acts as a Subject
// View acts as an Observer

class Board {
 protected: 
  std::vector<View *> theViews;

 public:
   virtual ~Board() = 0;
   void attachView(TextView *v); // attach a View to Board;
   void attachView(GraphicView *v); // attach a View to Board;
};

#endif
