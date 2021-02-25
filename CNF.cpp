//
// Created by adam on 2/24/21.
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

    std::vector<uint32_t> base = std::vector<uint32_t>(v);
    for(uint32_t i = 0; i < v; i++){
        base[i] = i+1;
    }

    for(uint32_t n = 0; n < c; n++){
        for(uint32_t i = v-1; i >= 1; --i){
            uint32_t j = rand() % (i+1);
            uint32_t temp = base[i];
            base[i] = base[j];
            base[j] = temp;
        }

        std::vector<int32_t> clause;
        for(uint32_t i = 0; i < k; i++) {
            int32_t literal = rand()%2 ? base[i] : -base[i];
            clause.push_back(literal);
        }
        data.push_back(clause);
    }
}

void CNF::print(){
    for(const auto& clause : data){
        for(auto literal : clause){
            std::cout << literal << " ";
        }
        std::cout << std::endl;
    }
}

