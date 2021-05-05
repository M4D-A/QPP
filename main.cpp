#include "QSolver.h"
#include "CNF.h"
#include "QRegister.h"

int main(int argc, char** argv){

    int32_t start_time  = time(NULL);
    CNF cnf = CNF(argv[1]);
    int32_t s = (argc > 2) ? atoi(argv[2]) : 1;

    QSolver q_solver  = QSolver(&cnf);
    uint32_t bit_solution = q_solver.solve(s);
    std::vector<int32_t> solution = CNF::uint_to_vector(bit_solution, cnf.get_var_num());

    std::cout << "c <<QSOLVER>>" << std::endl;
    std::cout << "c Filename: " << argv[1] << ", claues: " << cnf.get_cls_num() << ", variables: " << cnf.get_var_num() << std::endl;
    std::cout << "c" << std::endl;

    if(cnf.eval(solution)){
        std::cout<<"s SATISFIABLE"<<std::endl;
        std::cout<<"v ";
        for(auto l : solution){
            std::cout<<l<<" ";
        }
        std::cout<<"0"<<std::endl;
    }
    else{
        std::cout<<"s UNDETERMINED"<<std::endl;
    }
    std::cout << "c" << std::endl;
    std::cout << "c Time elaped: " << (time(NULL) - start_time) << std::endl;
}

