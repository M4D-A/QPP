//
// Created by adam on 2/22/21.
//

#include "QRegister.h"

QRegister::QRegister(size_t n){
    states_num = 1u<<n;
    qreg = std::vector< std::complex<double> >(states_num,0);
    qreg[0] = {1, 0};
}



void QRegister::set(uint32_t n){
    std::fill(std::begin(qreg), std::end(qreg), 0);
    qreg[n] = {1, 0};
}

void QRegister::test_fill(){
    for(uint32_t i = 0; i < states_num; i++){
        qreg[i] = i;
    }
}

void QRegister::print(){
    for(uint32_t i = 0; i < states_num; i++){
        std::cout << "|" << i << ">  = " << qreg[i] << " :: " << std::abs(qreg[i])*std::abs(qreg[i]) <<std::endl;
    }
}

void QRegister::print(uint32_t n){
    for(uint32_t i = 0; i < n; i++){
        std::cout << "|" << i << ">  = " << qreg[i] << " :: " << std::abs(qreg[i])*std::abs(qreg[i]) <<std::endl;
    }
}



void QRegister::nott(uint32_t n){
    uint32_t mask = 1u << n;
    std::complex<double> swap;
    uint32_t noti;
    for(uint32_t i = 0; i < states_num; i++){
        if(i & mask){
            noti = i^mask;
            swap = qreg[i];
            qreg[i] = qreg[noti];
            qreg[noti] = swap;
        }
    }
}

void QRegister::nott(const std::vector<uint32_t>& N){
    for(uint32_t n : N){
        nott(n);
    }
}


void QRegister::cnot(uint32_t c, uint32_t n){
    uint32_t mask = 1u << n;
    uint32_t c_mask = 1u << c;
    std::complex<double> swap;
    uint32_t noti;
    for(uint32_t i = 0; i < states_num; i++){
        if((i & mask) && (i & c_mask)){
            noti = i^mask;
            swap = qreg[i];
            qreg[i] = qreg[noti];
            qreg[noti] = swap;
        }
    }
}

void QRegister::ccnot(const std::vector<uint32_t>& controls, uint32_t n){
    uint32_t c_mask = 0u;
    for(uint32_t c : controls){
        uint32_t temp_mask = 1u<<c;
        c_mask |= temp_mask;
    }
    uint32_t mask = 1u << n;
    std::complex<double> swap;
    uint32_t noti;
    for(uint32_t i = 0; i < states_num; i++){
        if( (i & mask) && ((i & c_mask) == c_mask) ){
            noti = i^mask;
            swap = qreg[i];
            qreg[i] = qreg[noti];
            qreg[noti] = swap;
        }
    }
}


void QRegister::had(uint32_t n){
    uint32_t mask = 1u << n;
    std::complex<double> temp;
    uint32_t noti;
    for(uint32_t i = 0; i < states_num; i++){
        if(i & mask){
            noti = i^mask;
            temp = qreg[i];
            qreg[i] = (qreg[noti] - temp)/sqrt2;    //  |1>  :=  |0> - |1>
            qreg[noti] = (qreg[noti] + temp)/sqrt2; //  |0>  :=  |0> + |1>
        }
    }
}

void QRegister::had(const std::vector<uint32_t>& N){
    for(auto n : N){
        uint32_t mask = 1u << n;
        std::complex<double> temp;
        uint32_t noti;
        for(uint32_t i = 0; i < states_num; i++){
            if(i & mask){
                noti = i^mask;
                temp = qreg[i];
                qreg[i] = (qreg[noti] - temp);    //  |1>  :=  |0> - |1>
                qreg[noti] = (qreg[noti] + temp); //  |0>  :=  |0> + |1>
            }
        }
    }

    uint32_t pow = N.size()/2;
    double denominator = 1<<pow;
    if(N.size() % 2) denominator *= sqrt2;

    for(auto& qstate : qreg){
        qstate /= denominator;
    }
}


void QRegister::rotX(uint32_t n){
    nott(n);
}

void QRegister::rotX(const std::vector<uint32_t>& N){
    for(uint32_t n : N){
        rotX(n);
    }
}

void QRegister::rotY(uint32_t n){
    uint32_t mask = 1u << n;
    std::complex<double> swap;
    uint32_t noti;
    for(uint32_t i = 0; i < states_num; i++){
        if(i & mask){
            noti = i^mask;
            swap = qreg[i];
            qreg[i] = qreg[noti] * NI;
            qreg[noti] = swap * I;
        }
    }
}

void QRegister::rotY(const std::vector<uint32_t>& N){
    for(uint32_t n : N){
        rotY(n);
    }
}

void QRegister::rotZ(uint32_t n){
    uint32_t mask = 1u << n;
    for(uint32_t i = 0; i < states_num; i++){
        if(i & mask){
            qreg[i] = qreg[i] * N1;
        }
    }
}

void QRegister::rotZ(const std::vector<uint32_t>& N){
    for(uint32_t n : N){
        rotZ(n);
    }
}


void QRegister::crotZ(const std::vector<uint32_t>& N){
    uint32_t mask = 0u;
    for(uint32_t n : N){
        uint32_t temp_mask = 1u<<n;
        mask |= temp_mask;
    }
    for(uint32_t i = 0; i < states_num; i++){
        if( (i & mask) == mask){
            qreg[i] = qreg[i] * N1;
        }
    }
}


void QRegister::phaseS(uint32_t n){
    uint32_t mask = 1u << n;
    for(uint32_t i = 0; i < states_num; i++){
        if(i & mask){
            qreg[i] = qreg[i] * I;
        }
    }
}

void QRegister::phaseS(const std::vector<uint32_t>& N){
    for(uint32_t n : N){
        phaseS(n);
    }
}

void QRegister::phaseT(uint32_t n){
    uint32_t mask = 1u << n;
    for(uint32_t i = 0; i < states_num; i++){
        if(i & mask){
            qreg[i] = qreg[i] * EIPI4;
        }
    }
}

void QRegister::phaseT(const std::vector<uint32_t>& N){
    for(uint32_t n : N){
        phaseT(n);
    }
}

void QRegister::phase(uint32_t n, double phi){
    std::complex<double> phaseValue = std::polar<double>(1, phi);
    uint32_t mask = 1u << n;
    for(uint32_t i = 0; i < states_num; i++){
        if(i & mask){
            qreg[i] = qreg[i] * phaseValue;
        }
    }
}

void QRegister::phase(const std::vector<uint32_t>& N, double phi){
    for(uint32_t n : N){
        phase(n, phi);
    }
}


void QRegister::cphaseS(const std::vector<uint32_t>& N){
    uint32_t mask = 0u;
    for(uint32_t n : N){
        uint32_t temp_mask = 1u<<n;
        mask |= temp_mask;
    }
    for(uint32_t i = 0; i < states_num; i++){
        if( (i & mask) == mask){
            qreg[i] = qreg[i] * I;
        }
    }
}

void QRegister::cphaseT(const std::vector<uint32_t>& N){
    uint32_t mask = 0u;
    for(uint32_t n : N){
        uint32_t temp_mask = 1u<<n;
        mask |= temp_mask;
    }
    for(uint32_t i = 0; i < states_num; i++){
        if( (i & mask) == mask){
            qreg[i] = qreg[i] * EIPI4;
        }
    }
}

void QRegister::cphase(const std::vector<uint32_t>& N, double phi){
    uint32_t mask = 0u;
    std::complex<double> phaseValue = std::polar<double>(1, phi);
    for(uint32_t n : N){
        uint32_t temp_mask = 1u<<n;
        mask |= temp_mask;
    }
    for(uint32_t i = 0; i < states_num; i++){
        if( (i & mask) == mask){
            qreg[i] = qreg[i] * phaseValue;
        }
    }
}


void QRegister::grover(const std::vector<uint32_t>& N){
    had(N);
    nott(N);
    crotZ(N);
    nott(N);
    had(N);
}


