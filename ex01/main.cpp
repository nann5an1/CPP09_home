#include "RPN.hpp"

int main(int ac, char **av){
    // if(ac > 2)
    //     throw ArgumentException();
    (void)ac;
    try
    {
        RPN rpn(av[1]);

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
   
}