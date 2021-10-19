#include <string.h>
#include <fstream>
#include <vector>
#include "Registro.h"
#include <algorithm>


using namespace std;
class SequentialFile{
private:
  string dataFileName;
  string auxFileName;

  string record_to_text(Registro &record){
    string text = ""; 
    text += string(record.name);
    text += ',';
    text += string(record.NOC);
    text += ',';
    text += string(record.discipline);
    text += ',';
    text += string(record.event);
    text += "\n";
    return text;
  }  


  void reBuild(){
      Registro record;
      fstream mainFile, auxFile, helperFile;
      mainFile.open(this->dataFileName, ios::in | ios::out | ios::binary);
      auxFile.open(this->auxFileName, ios::in | ios::out| ios::binary);
      helperFile.open("helper.dat", ios::out |ios::binary);

      int next = 1;
      mainFile.read((char*) &record, sizeof(record));

      auto tempNext = record.next;
      auto tempFile = record.file;
      record.next = next;
      record.file = 'd';
      helperFile.write((char*) &record, sizeof(record));
      helperFile<<"\n";

      while(tempNext != -1){
        ++next;

        if (tempFile == 'd'){
          mainFile.seekg(tempNext * (sizeof(Registro) + 1));
          mainFile.read((char*) &record, sizeof(record));
        }
        else{
          auxFile.seekg(tempNext * (sizeof(Registro) + 1));
          auxFile.read((char*) &record, sizeof(record));
        }

        tempNext = record.next;
        tempFile = record.file;

        record.next = next;
        record.file  = 'd';

        helperFile.write((char*) &record, sizeof(record));
        helperFile<<"\n";
      }

      helperFile.seekg(helperFile.tellg() - (sizeof(Registro) + 1));
      record.next = -1;
      helperFile.write((char*) &record, sizeof(record));
      
      mainFile.close();
      helperFile.close();
      auxFile.close();   
      remove(this->dataFileName.c_str());
      remove(this->auxFileName.c_str());
      rename("helper.dat", this->dataFileName.c_str());
      fstream aux;
      aux.open(this->auxFileName,ios::out);
      aux.close();

  }
  
  long binarySearch(fstream& file, long size, string key, bool &buscar){
    long int m;
    long int begin = 0;
    long int last = size - 1;
    bool isDeleted = false;
    Registro registro;
    int deletionCount = 0;

    while(begin <= last) {
        deletionCount = 0;
        m = begin + (last - begin) / 2;
        file.seekg(m * (sizeof(Registro) + 1));
        file.read((char*) &registro, sizeof(Registro));

        // while(registro.next == -2){
        //   --m;
        //   deletionCount++;
        //   file.seekg(m * (sizeof(Registro) + 1));
        //   file.read((char*) &registro, sizeof(Registro));
        //   isDeleted = true;
        // }
        
        if(string(registro.name) == key) {
          buscar = true;
          return m;
        }
        if(string(registro.name) < key) {begin = m + 1 + deletionCount;}
        else {last = m - 1 - deletionCount;}
    }

    if(key > string(registro.name)) {
        return m;
    } else {
        return m - 1; 
    }
  }

  long LinearSearch(fstream &file, string key, Registro registro, bool buscar){
    long pos;
    while(registro.next != -1 && registro.file != 'd' && registro.name != key){
      file.seekg(registro.next * (sizeof(Registro) + 1));
      pos = file.tellg() / (sizeof(Registro) +1);
      file.read((char*) &registro, sizeof(Registro));
    }
    if(registro.name == key){
      buscar = true;
    }

    return pos;
  }

  
public:
  SequentialFile(string fileName,string auxName){
    this->dataFileName = fileName + ".dat";
    this->auxFileName = auxName + ".dat";
  }

  void search_to_csv(Registro &result){
    Registro record;
    fstream csvFile;
    csvFile.open("search.csv",ios::out);
    csvFile<<record_to_text(record);
    csvFile.close();
  }

  void search_to_csv(vector<Registro> &results){
    Registro record;
    fstream csvFile;
    csvFile.open("search.csv",ios::out);
    for (auto it = begin(results); it!= end(results);it++){
        csvFile<<record_to_text((*it));
    }
    csvFile.close();
  }

  void write_all_to_CSV(){
    Registro record;
    fstream mainFile, auxFile, csvFile;
    mainFile.open(this->dataFileName, ios::in | ios::out | ios::binary);
    auxFile.open(this->auxFileName, ios::in | ios::out| ios::binary);
    csvFile.open("all.csv",ios::out);

    int next = 1; 
    mainFile.read((char*) &record, sizeof(record));
    csvFile<<record_to_text(record);

    auto tempNext = record.next;
    auto tempFile = record.file;
    while(tempNext != -1){
      ++next;
      if (tempFile == 'd'){
        mainFile.seekg(tempNext * (sizeof(Registro) + 1));
        mainFile.read((char*) &record, sizeof(record));
        csvFile<<record_to_text(record);
      }
      else{
        auxFile.seekg(tempNext * (sizeof(Registro) + 1));
        auxFile.read((char*) &record, sizeof(record));
        csvFile<<record_to_text(record);
      }
      tempNext = record.next;
      tempFile = record.file;

      record.next = next;

  }
  mainFile.close();
  auxFile.close();
  csvFile.close();
}

  void insertAll(vector<Registro> registros){
    fstream file;
    file.open(this->dataFileName, ios::out| ios::binary);

    if(file.is_open()){
      //sort
        sort(registros.begin(), registros.end(), [this](const Registro& r1, const Registro& r2) {
            return strcmp(r1.name, r2.name) < 0;
        });

        file.seekg(0, ios::end);

        long  next = 1;

        for(auto it = begin(registros); it != end(registros); ++it) {
            (*it).next = next;
            (*it).file = 'd';

            if(it == end(registros) - 1) {
                (*it).next= -1;
            }

            file.write((char*)&(*it),sizeof(Registro));
            file<<"\n";
            ++next;
        }

        file.close();

    }
    else{
        cout<<"No se pudo abrir el archivo"<<endl;
    }
  }

  void add(Registro registro){
    fstream mainFile;
    mainFile.open(this->dataFileName,ios::in | ios::out | ios::binary);

    if (mainFile.is_open()){
      bool exists = false;
      mainFile.seekg(0,ios::end);
      long n_elements = mainFile.tellg()/(sizeof(Registro) + 1);
      long pos = binarySearch(mainFile,n_elements,registro.name,exists);

      if (exists){
          cout<<"El registro ya existe "<<endl;
      }
      else{
          Registro record;
          mainFile.seekg(pos * (sizeof(Registro) + 1));
          mainFile.read((char*)&record,sizeof(record));

          fstream auxFile;
          auxFile.open(this->auxFileName,ios::in | ios::out| ios::binary);

          if (auxFile.is_open()){
              long aux_pos;
              long next;
              char file;

              if (record.file == 'a'){
                  aux_pos = LinearSearch(auxFile,record.name,record,exists);

                  if (exists){
                      throw "El registro ya existe ";
                  }
                  else{
                      next = record.next;
                      file = record.file;

                      auxFile.seekg(0,ios::end);
                      record.next = (auxFile.tellg()/(sizeof(Registro) + 1));
                      record.file = 'a';

                      auxFile.seekg(aux_pos * sizeof(Registro) + 1);
                      auxFile.write((char*) &record,sizeof(Registro));
                      auxFile << "\n";
                  }

              }
              else{
                  next = record.next;
                  file = record.file;

                  auxFile.seekg(0,ios::end);
                  record.next = (auxFile.tellg() / (sizeof(Registro) + 1));
                  record.file = 'a';

                  mainFile.seekg(pos * (sizeof(Registro) + 1));
                  mainFile.write((char*) &record,sizeof(Registro));
              }
              
              auxFile.seekg(0, ios::end);
              registro.next = next;
              registro.file = file;
              auxFile.write((char*) &registro,sizeof(Registro));
              auxFile<<"\n";

              long n_elementsAux = auxFile.tellg() / (sizeof(Registro) + 1);

              auxFile.close();

              if(n_elementsAux == 5) {
                  reBuild();
              }

          }
          else{
              cout<<"No se pudo abrir el archivo auxiliar"<<endl;
          }

      }

    }
    else{
        cout<<"No se pudo abrir el archivo de datos"<<endl;
    }
}


  bool deleteRow(string key){
    bool isDeleted;
    fstream mainFile;
    mainFile.open(this->dataFileName,ios::in | ios::out |ios::binary);

    if (mainFile.is_open()){
      bool exists = false;
      mainFile.seekg(0,ios::end);
      long n_elements = mainFile.tellg()/(sizeof(Registro) + 1);
      long pos = binarySearch(mainFile,n_elements,key,exists);

      Registro record;
      mainFile.seekg(pos * (sizeof(Registro)+1));
      mainFile.read((char*) &record, sizeof(Registro));

      if (exists){
        Registro helper;

        mainFile.seekg((pos - 1) * (sizeof(Registro)+1));
        mainFile.read((char*) &helper, sizeof(Registro));
        helper.next = record.next;
        helper.file = record.file;
        record.next = -2;
        mainFile.seekg((pos - 1) * (sizeof(Registro)+1));
        mainFile.write((char*) &helper, sizeof(Registro));
        mainFile<<"\n";
        mainFile.write((char*) &record, sizeof(Registro));
        mainFile<<"\n";
        mainFile.close();

        return true;
      }
      else{
        if (record.file == 'a'){
          fstream auxFile;
          Registro helper;
          auxFile.open(this->auxFileName,ios::in| ios::out| ios::binary);

          if (auxFile.is_open()){
            long auxPos = LinearSearch(auxFile,key,helper,exists);

            if (exists){
              record.next = helper.next;
              record.file = helper.file;
              helper.next = -2;

              mainFile.seekg(pos * sizeof(Registro) + 1);
              auxFile.seekg(auxPos * sizeof(Registro) + 1);
              mainFile.write((char*)&record,sizeof(Registro));
              mainFile<<"\n";
              auxFile.write((char*)&helper,sizeof(Registro));
              auxFile<<"\n";

              mainFile.close();
              auxFile.close();
              return true;
            }
            else {
              cout<< "El registro a eliminar no existe";
              return false;
            }
          }  
          else{
            cout<<"El archivo auxiliar no pudo abrirse";
          }
        } 
        else{
          cout<< "El registro a eliminar no existe";
          return false;
        }
      }
    }
    else{
      cout<<"El archivo no pudo abrirse";
    }
  }

  Registro search(string key){
    Registro record;

    fstream inFile;
    inFile.open(this->dataFileName,ios::in | ios::binary);
    if (inFile.is_open()){
      
      bool exists = false;
      inFile.seekg(0,ios::end);
      long n_elements = inFile.tellg() / (sizeof(Registro) + 1);
      long pos = binarySearch(inFile,n_elements,key,exists); //binarySearch
      inFile.seekg(pos * (sizeof(Registro) + 1));
      inFile.read((char*)&record, sizeof(Registro));
      inFile.close();

      if (exists){
        search_to_csv(record);
        return record;
      }
      else{
        if(record.file == 'd'){
            throw "El registro no existe";
        }
        else{
          fstream auxFile;
          auxFile.open(this->auxFileName,ios::in| ios::binary);

          if (auxFile.is_open()){
            LinearSearch(auxFile,key,record,exists);
            auxFile.close();

            if (exists){
              search_to_csv(record);
              return record;
            }
            else throw "El registro no existe";

          }
          else{
            throw "No se pudo abrir el archivo auxiliar";
          }
        }
      }
    }
    else{
      cout<< "No se pudo abrir el archivo de datos "<<this->dataFileName;
    }
  }
  

  vector<Registro> search(const string begin, const string end) {
      vector<Registro> records;

      Registro result;

      fstream mainFile, auxFile;
      mainFile.open(this->dataFileName, ios::in | ios::binary);
      auxFile.open(this->auxFileName, ios::in | ios::binary);

      if(mainFile.is_open() && auxFile.is_open()) {
          bool find = false;

          mainFile.seekg(0, ios::end);
          long unsigned int size = mainFile.tellg() / (sizeof(Registro) + 1);

          long unsigned int position = binarySearch(mainFile, size, begin, find);

          if(!find && result.file == 'd') {
              cout <<"El registro no existe no en el archivo de datos";
          }

          if(find) {
              mainFile.seekg(position * (sizeof(Registro) + 1));
              mainFile.read((char*)&result,sizeof(Registro));
          } else {
              bool find = false;

              LinearSearch(auxFile, begin, result, find);

              if(!find) {
                  cout<<"El registro no existe en el archivo auxiliar";
              }
          }

          records.push_back(result);

          while(result.next != -1 && result.name != end) {
              if(result.file == 'd') {
                  mainFile.seekg(result.next * (sizeof(Registro) + 1));
                  mainFile.read((char*)&result,sizeof(Registro));
              } else {
                  auxFile.seekg(result.next * (sizeof(Registro) + 1));
                  auxFile.read((char*)&result,sizeof(Registro));
              }

              records.push_back(result);
          }

          mainFile.close();
          auxFile.close();
      } else {
          cout<< "No se pudo abrir el archivo de datos";
      }
      search_to_csv(records);
      return records;
  }
  
};