#ifndef REGISTRO_H
#define REGISTRO_H

#include <iostream> 

struct Registro{
  char name [30];
  char NOC [26];
  char discipline [17];
  char event[8];
  long next;
  char file;

  void print(){
    std::cout<<name<<" "<<NOC<<" "<<discipline<<" "<<event<<" "<<next<<" "<<file<<std::endl;
  }
};

#endif //REGISTRO_H