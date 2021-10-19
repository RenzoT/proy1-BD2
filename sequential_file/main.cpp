#include <iostream>
#include <string.h>
#include "SequentialFile.h"
#include <vector>
#include "functions.h"

using namespace std;


int main() {
  auto sec = SequentialFile("datos","data_aux");
  //auto data = load_csv();
  //sec.insertAll(data);

  // auto rec = sec.search("CALDAS Max","DAZA Fabian");
  // for (auto it = begin(rec); it != end(rec); it++){
  //   (*it).print();
  // }
  auto i = sec.search("CALDAS Max");
  i.print();

  // Registro registro1{"RODRIGUEZ Mau","Peru","Football","Men"};
  // Registro registro2{"TENAZOA Renzo","Peru","Football","Men"};
  // Registro registro3{"CHOQUEHUANCA Said","Peru","Football","Men"};
  // Registro registro4{"CRISTO Rey","Peru","Football","Men"};
  // Registro registro5{"LAPADULA Gianluca","Peru","Football","Men"};
  // Registro registro6{"GUERRERO Paolo","Peru","Football","Men"};
  // Registro registro7{"OREJAS Flores","Peru","Football","Men"};

  // sec.add(registro1);
  // sec.add(registro2);
  // sec.add(registro3);
  // sec.add(registro4);
  // sec.add(registro5);
  // sec.add(registro6);
  // sec.add(registro7);

  // i = sec.search("CHOQUEHUANCA Said");
  // i.print();

  //sec.write_all_to_CSV();
  return 0;
}