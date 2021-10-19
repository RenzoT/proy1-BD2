//
// Created by USER on 18/10/2021.
//
#include <iostream>
#include <fstream>


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


vector<Register> search(Key searchKey){
    bitset hashKey = myHash(searchKey);
    AddressType currentNodePosition = searchNode(ROOT, hashKey, 0);
    HashNode currentNode = indexFile.readRecord(currentNodePosition);
    AddressType currentBucketPosition = currentNode.getBucketPosition();
    vector<Register> result;
    while(currentBucketPosition != -1){
        Bucket bucket = bucketFile.readRecord(currentBucketPosition);
        for(auto &r : bucket.getRecords()){
            if(r.compareByPrimaryKey(searchKey)){
                result.push_back(r);
            }
        }
        currentBucketPosition = bucket.getNextBucket();
    }
    return result;
}