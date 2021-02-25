#include <cmath>
#include "QSolver.h"
#include "CNF.h"

int main(){
    CNF cnf = CNF("a.dimacs");
    QSolver qs = QSolver(&cnf);
    qs.solve();
}
