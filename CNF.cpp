//
// Created by Adam Jagielski on 24/2/21.
// Version 1.0 on 05/05/21.
//

#include "CNF.h"
CNF::CNF(const std::string& filename){
    std::fstream cnf_file;
    cnf_file.open(filename, std::ios::in);
    if(!cnf_file){
        std::cout<<"file not found"<<std::endl;
        exit(1);
    }

    std::string line;
    while(getline(cnf_file, line)){ //read data from file object and put it into string.
        if(line[0] == 'c')
            continue;
        std::stringstream ss;
        ss << line;
        std::string temp;
        int32_t literal;
        std::vector<int32_t> clause;
        while (!ss.eof()) {
            ss >> temp;
            if (std::stringstream(temp) >> literal)
                clause.push_back(literal);
            temp = "";
        }
        if(line[0] == 'p'){
            var_num = clause[0];
            cls_num = clause[1];
        }
        else{
            clause.pop_back();
            data.push_back(clause);
        }

    }
    cnf_file.close();
}

CNF::CNF(uint32_t k, uint32_t v, uint32_t c) {
    var_num = v;
    cls_num = c;

    std::vector<int32_t> base = std::vector<int32_t>(v);
    for(int32_t i = 0; i < v; i++){
        base[i] = i+1;
    }

    for(uint32_t n = 0; n < c; n++){
        for(uint32_t i = v-1; i >= 1; --i){
            uint32_t j = rand() % (i+1);
            int32_t temp = base[i];
            base[i] = base[j];
            base[j] = temp;
        }

        std::vector<int32_t> clause(k);
        for(uint32_t i = 0; i < k; i++) {
            clause[i] = rand()%2 ? base[i] : -base[i];
        }
        data.push_back(clause);
    }
}

CNF::CNF(uint32_t k, uint32_t v) {
    var_num = v;

    std::list<std::vector<int32_t>> solutions;
    for(int32_t i = 0; i < (1<<v); i++){
        std::vector<int32_t> sol;
        for(int32_t j = 1;j <= v; j++) {
            sol.push_back( (i>>(j-1))&1 ? -j : j );
        }
        solutions.push_back(sol);
    }

    std::vector<int32_t> base = std::vector<int32_t>(v);
    for(int32_t i = 0; i < v; i++){
        base[i] = i+1;
    }

    uint32_t solution_counter = solutions.size();
    while(solution_counter > 1 || solution_counter == 0){
        for(uint32_t i = v-1; i >= 1; --i){
            uint32_t j = rand() % (i+1);
            int32_t temp = base[i];
            base[i] = base[j];
            base[j] = temp;
        }

        std::vector<int32_t> clause(k);
        for(uint32_t i = 0; i < k; i++) {
            int32_t literal = rand()%2 ? base[i] : -base[i];
            clause[i] = literal;
        }
        data.push_back(clause);

        uint32_t old_solution_counter = solution_counter;
        solution_counter = 0;
        for(const auto& s : solutions){
            if( eval(s) ) ++solution_counter;
        }

        if(solution_counter == old_solution_counter || solution_counter == 0){
            data.pop_back();
        }
    }
    cls_num = data.size();
}

bool CNF::eval(std::vector<int32_t> solution) {
    for(const auto& clause : data){
        bool clause_sat = false;
        for(auto literal : clause) {
            if (std::find(solution.begin(), solution.end(), literal) != solution.end()) {
                clause_sat = true;
                break;
            }
        }
        if(!clause_sat){
            return false;
        }
    }
    return true;
}

void CNF::print(){
    std::cout<<"v: "<<var_num<<", c: "<<cls_num<<std::endl;
    for(const auto& clause : data){
        for(auto literal : clause){
            std::cout << literal << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<int32_t> CNF::uint_to_vector(uint32_t bitwise, uint32_t size) {
    std::vector<int32_t> ret_value(size);
    for(int32_t i=0; i<size; i++){
        ret_value[i] = (bitwise >> i) & 1u ? (i + 1) : -(i + 1);
    }
    return ret_value;
}

uint32_t CNF::vector_to_uint(const std::vector<int32_t>& vec) {
    uint32_t ret_value = 0u;
    for(int32_t literal : vec){
        if(literal > 0){
            ret_value |= (1u << (literal - 1));
        }
    }
    return ret_value;
}

uint32_t CNF::get_var_num() const {
    return var_num;
}

uint32_t CNF::get_cls_num() const {
    return cls_num;
}

std::vector<std::vector<int32_t> > CNF::get_data() {
    return data;
}





