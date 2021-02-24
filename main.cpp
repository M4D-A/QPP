#include <cmath>
#include "QRegister.h"
#include "CNF.h"
#define sqrt2 M_SQRT2f64;

void solve(const std::vector< std::vector<int32_t> >& cnf, uint32_t v_num){
    uint32_t reg_size = cnf.size() + v_num;

    std::vector< std::vector<uint32_t> > cnf_neg;
    std::vector< std::vector<uint32_t> > cnf_pos;
    std::vector< std::vector<uint32_t> > cnf_abs;
    std::vector<uint32_t> v_indices;
    std::vector<uint32_t> c_indices;

    for(uint32_t i=0; i<v_num; i++){
        v_indices.push_back(i);
    }

    for(uint32_t i=v_num; i<reg_size; i++){
        c_indices.push_back(i);
    }

    for(const auto& clause : cnf){
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

    QRegister reg = QRegister(cnf.size() + v_num);
    reg.had(v_indices);

    for(uint32_t i = 0; i<cnf.size(); i++){
        reg.nott(cnf_neg[i]);
        reg.nott(cnf_abs[i]);
        reg.ccnot(cnf_abs[i], v_num + i);
        reg.nott(v_num + i);
        reg.nott(cnf_abs[i]);
        reg.nott(cnf_neg[i]);
    }

    reg.crotZ(c_indices);

    for(uint32_t i = 0; i<cnf.size(); i++){
        reg.nott(cnf_neg[i]);
        reg.nott(cnf_abs[i]);
        reg.nott(v_num + i);
        reg.ccnot(cnf_abs[i], v_num + i);
        reg.nott(cnf_abs[i]);
        reg.nott(cnf_neg[i]);
    }

    reg.grover(v_indices);

    reg.print();
}





int main(){
    CNF cnf = CNF("a.dimacs");
    solve(cnf.data, cnf.var_num);
}
