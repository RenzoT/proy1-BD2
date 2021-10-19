//
// Created by USER on 18/10/2021.
//
#include <iostream>
#include <fstream>



vector<Register> searchInRange(Key beginKey, Key endKey){
    int bucketNumber = bucketFile.getNumberOfRecords();
    vector<Register> result;
    for(int i = 0; i < bucketNumber; i++){
        Bucket bucket_temp = bucketFile.readRecord(i);
        for(auto &it : bucket_temp.getRecords()){
            if(it.lessThanEqualKey(endKey) and it.greatherThanEqualKey(beginKey)){
                result.push_back(it);
            }
        }
    }
    sort(result.begin(), result.end(), Bucket::compareRecords);
    return result;
}