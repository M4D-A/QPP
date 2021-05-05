//
// Created by Adam Jagielski on 24/2/21.
// Version 1.0 on 05/05/21.
//

#include "QSolver.h"

QSolver::QSolver(CNF* cnf) {
    var_num = cnf->get_var_num();
    cls_num = cnf->get_cls_num();
    uint32_t reg_size = cls_num + var_num;

    for(uint32_t i=0; i<var_num; i++){
        v_indices.push_back(i);
    }

    for(uint32_t i=var_num; i<reg_size; i++){
        c_indices.push_back(i);
    }

    for(const auto& clause : cnf->get_data()){
        std::vector<uint32_t> clause_neg;
        std::vector<uint32_t> clause_pos;
        std::vector<uint32_t> clause_abs;

        for(auto literal : clause){
            if(literal < 0){
                clause_neg.push_back(abs(literal) - 1);
            }
            if(literal > 0){
                clause_pos.push_back(abs(literal) - 1);
            }
            clause_abs.push_back(abs(literal) - 1);
        }

        cnf_neg.push_back(clause_neg);
        cnf_pos.push_back(clause_pos);
        cnf_abs.push_back(clause_abs);
    }

    reg = new QRegister(reg_size);
    reg->had(v_indices);
}

QRegister* QSolver::get_reg() {
    return reg;
}

void QSolver::step(uint32_t steps_num){
    for(uint j = 0; j < steps_num; j++){
        for(uint32_t i = 0; i<cls_num; i++){
            reg->nott(cnf_pos[i]);
            reg->ccnot(cnf_abs[i], var_num + i);
            reg->nott(var_num + i);
            reg->nott(cnf_pos[i]);
        }

        reg->crotZ(c_indices);

        for(int32_t i = (int32_t)cls_num - 1; i>=0; i--){
            reg->nott(cnf_pos[i]);
            reg->nott(var_num + i);
            reg->ccnot(cnf_abs[i], var_num + i);
            reg->nott(cnf_pos[i]);
        }
        reg->grover(v_indices);
    }
}

uint32_t QSolver::solve(uint32_t solutions_num) {
    reg->set(0);
    reg->had(v_indices);
    double r = M_PI/(4.0 * sqrt(solutions_num)) * pow(2.0,var_num/2.0);
    step(floor(r));
    return reg->measure();
}
