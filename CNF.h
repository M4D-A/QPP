//
// Created by adam on 2/24/21.
//
#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
#include <fstream>

#ifndef QPP_CNF_H
#define QPP_CNF_H

class CNF {
public:
    std::vector< std::vector<int32_t> > data;
    uint32_t var_num;
    uint32_t cls_num;
    explicit CNF(const std::string& filename);
    CNF(uint32_t k, uint32_t v, uint32_t c);
    void print();
};

#endif //QPP_CNF_H
