#include "RPN.hpp"

int main(int ac, char **av){
   
    try
    {
        if(ac != 2)
            throw ArgumentException();
        RPN rpn(av[1]);

        RPN rpn2(rpn);
        RPN rpn3 = rpn ;
       
        rpn2.print_stack();
        // rpn3.print_stack();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}