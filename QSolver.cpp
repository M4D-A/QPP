//
// Created by adam on 2/25/21.
//

#include "QSolver.h"

QSolver::QSolver(CNF* cnf_att) {
    cnf = cnf_att;
}

void QSolver::solve(){
    uint32_t reg_size = cnf->data.size() + cnf->var_num;

    std::vector< std::vector<uint32_t> > cnf_neg;
    std::vector< std::vector<uint32_t> > cnf_pos;
    std::vector< std::vector<uint32_t> > cnf_abs;
    std::vector<uint32_t> v_indices;
    std::vector<uint32_t> c_indices;

    for(uint32_t i=0; i<cnf->var_num; i++){
        v_indices.push_back(i);
    }

    for(uint32_t i=cnf->var_num; i<reg_size; i++){
        c_indices.push_back(i);
    }

    for(const auto& clause : cnf->data){
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

    QRegister reg = QRegister(cnf->data.size() + cnf->var_num);
    reg.had(v_indices);

    for(uint32_t i = 0; i<cnf->data.size(); i++){
        reg.nott(cnf_pos[i]);
        reg.ccnot(cnf_abs[i], cnf->var_num + i);
        reg.nott(cnf->var_num + i);
        reg.nott(cnf_pos[i]);
    }

    reg.crotZ(c_indices);

    for(uint32_t i = 0; i<cnf->data.size(); i++){
        reg.nott(cnf_pos[i]);
        reg.nott(cnf->var_num + i);
        reg.ccnot(cnf_abs[i], cnf->var_num + i);
        reg.nott(cnf_pos[i]);
    }

    reg.grover(v_indices);

    reg.print(1u<<cnf->var_num);
}