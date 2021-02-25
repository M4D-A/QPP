//
// Created by adam on 2/22/21.
//
#include <iostream>
#include <complex>
#include <vector>
#include <cmath>

#ifndef QPP_QREGISTER_H
#define QPP_QREGISTER_H

#define sqrt2 M_SQRT2f64

class QRegister{

private:
    uint32_t states_num;
    std::vector< std::complex<double> > qreg;
    const double recsqrt2 = 1.0 / sqrt2;
    const std::complex<double> I = {0,1};
    const std::complex<double> NI = {0,-1};
    const std::complex<double> N1 = {-1,0};
    const std::complex<double> EIPI4 = {recsqrt2, recsqrt2};

public:
    explicit QRegister(size_t n);
    void set(uint32_t n);
    void test_fill();
    void print();
    void print(uint32_t n);

    void nott(uint32_t n);
    void nott(const std::vector<uint32_t>& N);

    void cnot(uint32_t c, uint32_t n);
    void ccnot(const std::vector<uint32_t>& controls, uint32_t n);

    void had(uint32_t n);
    void had(const std::vector<uint32_t>& N);

    void rotX(uint32_t n);
    void rotX(const std::vector<uint32_t>& N);
    void rotY(uint32_t n);
    void rotY(const std::vector<uint32_t>& N);
    void rotZ(uint32_t n);
    void rotZ(const std::vector<uint32_t>& N);

    void crotZ(const std::vector<uint32_t>& N);

    void phaseS(uint32_t n);
    void phaseS(const std::vector<uint32_t>& N);
    void phaseT(uint32_t n);
    void phaseT(const std::vector<uint32_t>& N);
    void phase(uint32_t n, double phi);
    void phase(const std::vector<uint32_t>& N, double phi);

    void cphaseS(const std::vector<uint32_t>& N);
    void cphaseT(const std::vector<uint32_t>& N);
    void cphase(const std::vector<uint32_t>& N, double phi);

    void grover(const std::vector<uint32_t>& N);


};


#endif //QPP_QREGISTER_H
