//
// Created by USER on 18/10/2021.
//
#include <iostream>
#include <fstream>
#include "Registro.h"

class Extend_Hashing {
private:

public:
    AddressType searchNode(AddressType nodePosition, bitset key, int& height){
        HashNode node = indexFile.readRecord(nodePosition);
        if(!node.isLeaf()){
            if(key[height] != 0) {
                return searchNode(node.right, key, ++height);
            }
            else{
                return searchNode(node.left, key, ++height);
            }
        }
        else{
            return nodePosition;
        }
    }
    int add(Register record) {
        std::fstream arch(this->path.c_str(), std::ios::binary | std::ios::in);
        if (!arch.is_open()) {
            int header_value = -1;
            arch.close();
            arch.open(this->path.c_str(), std::ios::binary | std::ios::out);
            writeHeader(header_value, arch);
            writeRegister(record, 0, arch);
            std::cout << "Success\n";
        } else {
            int header_value = -1;
            int recordPosition;
            arch.close();
            arch.open(this->path.c_str(), std::ios::binary | std::ios::in | std::ios::out);

            readHeader(header_value, arch);
            if (header_value == -1) {
                recordPosition = numberOfRecords(arch);
                writeRegister(record, recordPosition, arch);
            } else {
                Register recordDeleted;
                readRegister(recordDeleted, header_value, arch);
                recordPosition = header_value;
                header_value = recordDeleted.nextDel;
                writeHeader(header_value, arch);
                writeRegister(record, recordPosition, arch);
            }
            arch.close();
            std::cout << "Success\n";
            return recordPosition;
        }
        return 0;
    }

    void insert(Register record) {
        if (bucketarch.getNumberOfRecords() == 0){
            initializeFirstValues();
        }
        bitset hashKey = myHash(record.getPrimaryKey());
        int h = 0;
        AddressType currentNodePosition = searchNode(ROOT, hashKey, h);
        HashNode currentNode = indexarch.readRecord(currentNodePosition);
        AddressType currentBucketPosition = currentNode.getBucketPosition();
        Bucket bucket = bucketarch.readRecord(currentBucketPosition);
        if(bucket.isFull()) {
            split(record, h, currentNodePosition, currentNode, currentBucketPosition, bucket);
        }
        else{
            bucket.add(record);
            bucket.sortBucket();
            bucketarch.writeRecord(currentBucketPosition, bucket);
        }

    }

};