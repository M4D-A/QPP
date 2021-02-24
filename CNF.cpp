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

void CNF::print(){
    for(const auto& clause : data){
        for(auto literal : clause){
            std::cout << literal << " ";
        }
        std::cout << std::endl;
    }
}