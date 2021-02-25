#include "QSolver.h"
#include "CNF.h"

int main(){
    CNF cnf = CNF(3,6,18);
    cnf.print();
    QSolver qs = QSolver(&cnf);
    qs.solve();
}
