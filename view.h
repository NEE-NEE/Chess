#ifndef VIEW_H
#define VIEW_H
#include <iostream>
#include <vector>


const int SIZE = 8;


// forward declaration
class ConcreteBoard;

class View {
 protected:
  char theView[SIZE][SIZE];

 public:
   virtual void update(const ConcreteBoard *b) = 0;

   friend std::ostream &operator<<(std::ostream &out, const View &v);
};

#endif
