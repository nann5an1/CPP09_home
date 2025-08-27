#include "RPN.hpp"

int main(int ac, char **av){
    if(ac > 2)
        throw ArgumentException();
    // char* input_str = av[1];    
    RPN rpn(av[1]);
}