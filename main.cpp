#include <iostream>
#include <array>
#include <complex>
#include <vector>
#include <cmath>
#define sqrt2 M_SQRT2f64;

constexpr static const std::complex<double> I;
constexpr static const std::complex<double> NI;

template<size_t S>
class QRegister{
public:
    uint32_t states_num =  1u<<S;
    std::array< std::complex<double>, 1u<<S > qreg;
    const double recsqrt2 = 1.0 / sqrt2;
    const std::complex<double> I = {0,1};
    const std::complex<double> NI = {0,-1};
    const std::complex<double> EIPI4 = {recsqrt2, recsqrt2};

    QRegister(){
        std::fill(std::begin(qreg), std::end(qreg), 0);
        qreg[0] = {1, 0};
    }

    void set(uint32_t n){
        std::fill(std::begin(qreg), std::end(qreg), 0);
        qreg[n] = {1, 0};
    }

    void test_fill(){
        for(uint32_t i = 0; i < states_num; i++){
            qreg[i] = i;
        }
    }

    void nott(uint32_t n){
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

    void nott(const std::vector<uint32_t>& N){
        for(uint32_t n : N){
            nott(n);
        }
    }

    void cnot(uint32_t n, uint c){
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

    void ccnot(uint32_t n, const std::vector<uint32_t>& controls){
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

    void had(uint32_t n){
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

    void had(const std::vector<uint32_t>& N){
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

    void rotX(uint32_t n){
        nott(n);
    }

    void rotY(uint32_t n){
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

    void rotZ(uint32_t n){
        uint32_t mask = 1u << n;
        for(uint32_t i = 0; i < states_num; i++){
            if(i & mask){
                qreg[i] = qreg[i] * -1;
            }
        }
    }

    void rotX(const std::vector<uint32_t>& N){
        for(uint32_t n : N){
            rotX(n);
        }
    }

    void rotY(const std::vector<uint32_t>& N){
        for(uint32_t n : N){
            rotY(n);
        }
    }

    void rotZ(const std::vector<uint32_t>& N){
        for(uint32_t n : N){
            rotZ(n);
        }
    }

    void phaseS(uint32_t n){
        uint32_t mask = 1u << n;
        for(uint32_t i = 0; i < states_num; i++){
            if(i & mask){
                qreg[i] = qreg[i] * I;
            }
        }
    }

    void phaseT(uint32_t n){
        uint32_t mask = 1u << n;
        for(uint32_t i = 0; i < states_num; i++){
            if(i & mask){
                qreg[i] = qreg[i] * EIPI4;
            }
        }
    }

    void phase(uint32_t n, double phi){
        std::complex<double> phaseValue = std::polar<double>(1, phi);
        uint32_t mask = 1u << n;
        for(uint32_t i = 0; i < states_num; i++){
            if(i & mask){
                qreg[i] = qreg[i] * phaseValue;
            }
        }
    }

    void phaseS(const std::vector<uint32_t>& N){
        for(uint32_t n : N){
            phaseS(n);
        }
    }

    void phaseT(const std::vector<uint32_t>& N){
        for(uint32_t n : N){
            phaseT(n);
        }
    }

    void phase(const std::vector<uint32_t>& N, double phi){
        for(uint32_t n : N){
            phase(n, phi);
        }
    }

    void cphaseS(const std::vector<uint32_t>& N){
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

    void cphaseT(const std::vector<uint32_t>& N){
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

    void cphase(const std::vector<uint32_t>& N, double phi){
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

    void print(){
        for(uint32_t i = 0; i < states_num; i++){
            std::cout << "|" << i << ">  = " << qreg[i] << std::endl;
        }
    }
};

int main(){
    QRegister<7> reg = QRegister<7>();
    reg.had({0,1,2});

    reg.nott({0,1});
    reg.ccnot(3,{0,1});
    reg.nott({0,1,3});

    reg.nott({0});
    reg.nott({0,2});
    reg.ccnot(4,{0,2});
    reg.nott({0,2,4});
    reg.nott({0});

    reg.nott({1,2});
    reg.nott({1,2});
    reg.ccnot(5,{1,2});
    reg.nott({1,2,5});
    reg.nott({1,2});

    reg.nott({0,2});
    reg.ccnot(6,{0,2});
    reg.nott({0,2,6});

    reg.cphase({3,4,5,6},M_PI);

    reg.nott({0,2,6});
    reg.ccnot(6,{0,2});
    reg.nott({0,2});

    reg.nott({1,2});
    reg.nott({1,2,5});
    reg.ccnot(5,{1,2});
    reg.nott({1,2});
    reg.nott({1,2});

    reg.nott({0});
    reg.nott({0,2,4});
    reg.ccnot(4,{0,2});
    reg.nott({0,2});
    reg.nott({0});

    reg.nott({0,1,3});
    reg.ccnot(3,{0,1});
    reg.nott({0,1});

    reg.had({0,1,2});
    reg.nott({0,1,2});
    reg.cphase({0,1,2}, M_PI);
    reg.nott({0,1,2});
    reg.had({0,1,2});



    reg.print();

}
