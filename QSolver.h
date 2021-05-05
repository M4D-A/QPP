//
// Created by Adam Jagielski on 24/2/21.
// Version 1.0 on 05/05/21.
//

#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
#include <fstream>
#include "CNF.h"
#include "QRegister.h"

#ifndef QPP_QSOLVER_H
#define QPP_QSOLVER_H

class QSolver {
private:
    std::vector< std::vector<uint32_t> > cnf_neg;
    std::vector< std::vector<uint32_t> > cnf_pos;
    std::vector< std::vector<uint32_t> > cnf_abs;
    std::vector<uint32_t> v_indices;
    std::vector<uint32_t> c_indices;
    uint32_t var_num;
    uint32_t cls_num;
    QRegister* reg;

public:
    explicit QSolver(CNF* cnf);
    QRegister* get_reg();
    void step(uint32_t s_num);
    uint32_t solve(uint32_t solutions_num);
};


#endif //QPP_QSOLVER_H
