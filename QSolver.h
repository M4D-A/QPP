//
// Created by adam on 2/25/21.
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
public:
    CNF* cnf;
    QSolver(CNF* cnf);
    void solve();
};


#endif //QPP_QSOLVER_H
