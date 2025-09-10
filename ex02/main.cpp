#include "PmergeMe.hpp"

int main(int ac, char** av){
    
    try
    {
        if(ac > 1){
            PmergeMe pmerge;
            pmerge.execute(ac, av);
        }
        else
            throw ArgumentNotEnough();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
   
    return 0;
}