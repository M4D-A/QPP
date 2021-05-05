//
// Created by Adam Jagielski on 24/2/21.
// Version 1.0 on 05/05/21.
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
    std::vector< std::complex<double> > q_state;
    const double recsqrt2 = 1.0 / sqrt2; //1/sqrt(2)
    const std::complex<double> I = {0,1}; //i
    const std::complex<double> NI = {0,-1}; //-i
    const std::complex<double> N1 = {-1,0}; //-1
    const std::complex<double> EIPI4 = {recsqrt2, recsqrt2}; //e^{i*pi/4} = 1/sqrt(2) + i/sqrt(2)

public:
    explicit QRegister(size_t n);   //Create Quantum register with [n] qubits, set it into |0> state

    void set(uint32_t s); //Set register into |s> state

    void nott(uint32_t n); //NOT-gate on qubit [n]
    void nott(const std::vector<uint32_t>& N); //NOT-gate on every qubit in [N]

    void cnot(uint32_t c, uint32_t n); //CNOT-gate on qubit [n] with [c] as control qubit
    void ccnot(const std::vector<uint32_t>& controls, uint32_t n); //CNOT-gate on qubit [n] with [C] as control qubits

    void had(uint32_t n); //HAD-gate on qubit [n]
    void had(const std::vector<uint32_t>& N); //HAD-gate on every qubit in [N]

    void rotX(uint32_t n); //ROTX-gate on qubit [n]
    void rotX(const std::vector<uint32_t>& N); //ROTX-gate on every qubit in [N]
    void rotY(uint32_t n); //ROTY-gate on qubit [n]
    void rotY(const std::vector<uint32_t>& N); //ROTY-gate on every qubit in [N]
    void rotZ(uint32_t n); //ROTZ-gate on qubit [n]
    void rotZ(const std::vector<uint32_t>& N); //ROTZ-gate on every qubit in [N]

    void crotZ(const std::vector<uint32_t>& N); //Controlled ROTZ-gate on every qubit in [N]

    void phaseS(uint32_t n); //S-gate on qubit [n]
    void phaseS(const std::vector<uint32_t>& N); //S-gate on every qubit in [N]
    void phaseT(uint32_t n); //T-gate on qubit [n]
    void phaseT(const std::vector<uint32_t>& N); //T-gate on every qubit in [N]
    void phase(uint32_t n, double phi); //phase-gate on qubit [n] by angle [phi]
    void phase(const std::vector<uint32_t>& N, double phi); //phase-gate on every qubit in [N] by angle [phi]

    void cphaseS(const std::vector<uint32_t>& N); //Controlled S-gate on every qubit in [N]
    void cphaseT(const std::vector<uint32_t>& N); //Controlled T-gate on every qubit in [N]
    void cphase(const std::vector<uint32_t>& N, double phi); //Controlled phase-gate on every qubit in [N] by angle [phi]


    void oracle(uint32_t s); //|x> => |x>^{f(x)} transformation for f(s) = 1
    void oracle(const std::vector<uint32_t>& S); //|x> => |x>^{f(x)} transformation for f(s) = 1 for s in S
    void grover(const std::vector<uint32_t>& N); //Grover diffusion operator

    uint32_t measure(); //measure state of quantum register

    void print(); //Print exact coefficients of register states and probabilities for measuring given state
};


#endif //QPP_QREGISTER_H
