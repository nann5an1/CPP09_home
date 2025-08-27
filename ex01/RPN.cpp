#include "RPN.hpp"

RPN::RPN(){}

RPN::RPN(char *str_array){ //str_array = av[1]
    std::string str = str_array;
    std::istringstream ss(str);
    std::string token;
    while (ss >> token){
        std::cout << token << std::endl;
        if(token == "+" || token == "-" || token == "*" || token == "/" )
            do_operation("+");
    }
   
    
}

RPN::~RPN(){}
RPN::RPN(const RPN &other){
    *this = other;
}

RPN& RPN::operator=(const RPN &other){
    (void)other;
    return *this;
}

void RPN::do_operation(std::string token){

}