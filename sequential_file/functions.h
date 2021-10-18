#ifndef Functions_H
#define Functions_H

#include "Registro.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>
using namespace std;

Registro vec_to_reg(vector<string> &vec){
    Registro rec;
    strcpy(rec.name,vec[0].c_str());
    strcpy(rec.NOC, vec[1].c_str());
    strcpy(rec.discipline, vec[2].c_str());
    strcpy(rec.event, vec[3].c_str());
    return rec;
}

vector<Registro> load_csv() { 
	fstream file;
    file.open("./../Coaches.csv", ios::in); 

    if(file.is_open()) {
        vector<Registro> data;
        vector<string> row;
        string line, word, temp; 

        while (getline(file, line, '\n')) { 
            row.clear(); 
            stringstream s(line); 

            while (getline(s, word, ',')) { 
                row.push_back(word); 
            } 

            data.push_back(vec_to_reg(row));
        }

        return data;
    } else {
        cout<<"No se pudo abrir el csv";
    }

    throw new exception;
} 


#endif //Functions