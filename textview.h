#ifndef TEXTVIEW_H
#define TEXTVIEW_H
#include <iostream>
#include "view.h"



class TextView: public View {
 public:
   TextView ();
   void update(const ConcreteBoard* b) override;

   //friend std::ostream &operator<<(std::ostream &out, const View &v);
};

#endif
