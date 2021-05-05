//
// Created by Adam Jagielski on 24/2/21.
// Version 1.0 on 05/05/21.
//

#include <iostream>
#include <complex>
#include <vector>
#include <list>
#include <cmath>
#include <fstream>
#include <algorithm>

#ifndef QPP_CNF_H
#define QPP_CNF_H

class CNF {
private:
    std::vector< std::vector<int32_t> > data; //set of clauses of literals
    uint32_t var_num; //number of variables in formula
    uint32_t cls_num; //number of clauses in formula

public:
    explicit CNF(const std::string& filename); //read CNF from DIMACS format file
    explicit CNF(uint32_t k, uint32_t v, uint32_t c); //random CNF with [c] clauses of length [k] and [v] variables
    explicit CNF(uint32_t k, uint32_t v); //random single solution CNF with clauses of length [k] and [v] variables
    bool eval(std::vector<int32_t> solution); //evaluate solution
    void print(); //human-readable print of formula

    std::vector< std::vector<int32_t> > get_data();
    uint32_t get_var_num() const;
    uint32_t get_cls_num() const;

    //AUXILIARY
    static std::vector<int32_t> uint_to_vector(uint32_t bitwise, uint32_t size); //Convert bit-wise solution into DIMACS format solution vector
    static uint32_t vector_to_uint(const std::vector<int32_t>& vec); //Convert DIMACS format solution vector into bit-wise solution
};

#endif //QPP_CNF_H
