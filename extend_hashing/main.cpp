#include <bits/stdc++.h>

using namespace std;

struct Register{

    int nextDel;
};

void readHeader(int header,fstream& file){

}

int numberOfRecords(fstream& file){

}

void writeRegister(Register record,int position, fstream& file){

}

void readRegister(Register record,int header, fstream& file){

}

void writeHeader(int header, fstream& file){

}

int add(Register record){
    fstream file(this->path.c_str(), ios::binary | ios::in);
    if(file.is_open()){
        file.close();
        file.open(this->path.c_str(), ios::binary | ios::in | ios::out);
        int header;
        readHeader(header, file);
        int recordPosition;
        if(header == -1) {
            recordPosition = numberOfRecords(file);
            writeRegister(record, recordPosition, file);
        }
        else{ // ESTRATEGIA LIFO
            Register recordDeleted;
            readRegister(recordDeleted, header, file);
            recordPosition = header;
            header = recordDeleted.nextDel;
            writeHeader(header, file);
            writeRegister(record, recordPosition, file);
        }
        file.close();
        cout << "Se agrego correctamente - add()" << endl;
        return recordPosition;
    }
    else{
        file.close();
        file.open(this->path.c_str(), ios::binary | ios::out);
        int header = -1;
        writeHeader(header, file);
        writeRegister(record, 0, file);

        cout << "Se agrego correctamente - add()" << endl;
        return 0;
    }
}

void insert(Register record){
    if(bucketFile.getNumberOfRecords() == 0)
        initializeFirstValues();
    int height = 0;
    bitset hashKey = myHash(record.getPrimaryKey());
        AddressType currentNodePosition = searchNode(ROOT, hashKey, height);
    HashNode currentNode = indexFile.readRecord(currentNodePosition);
    AddressType currentBucketPosition = currentNode.getBucketPosition();
    Bucket bucket = bucketFile.readRecord(currentBucketPosition);
    if(!bucket.isFull()){
        bucket.add(record);
        bucket.sortBucket();
        bucketFile.writeRecord(currentBucketPosition, bucket);
    }else
        split(record, height, currentNodePosition, currentNode, currentBucketPosition, bucket);
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
