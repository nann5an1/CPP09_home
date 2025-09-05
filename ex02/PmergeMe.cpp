#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){}
PmergeMe::~PmergeMe(){}
PmergeMe::PmergeMe(const PmergeMe &other){
    *this = other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe &other){
    if(this != &other)
        (void)other;
    return *this;
}


void PmergeMe::execute(int ac, char **av){
    digit_check(ac, av);
    // ford_johnson(vec);
    print_container(deq);
    ford_johnson(deq);
    // print_pair(vec);   
    // ford_johnson(deq);
    // print_vec();
    // print_deq();
    // print_container(input_vec);
    
    
}

//need to check for the duplicate number also
void PmergeMe::digit_check(int ac, char **av){
        for(int count = 1; count < ac; ++count){
            std::string str = av[count];
            int length = str.length() - 1;
            int i = 0;

            if(str[0] == '+')
                i++;
            while(i <= length)
                if(!isdigit(str[i++])) throw NotANumberException();
            if(strtod(str.c_str(), NULL) > INT_MAX) throw NotAnIntException();
            if(strtod(str.c_str(), NULL) < 0) throw PositiveNumberException();
            input_vec.push_back(strtod(str.c_str(), NULL));
            vec.push_back(strtod(str.c_str(), NULL));
            // vec = input_vec;
            deq.push_back(strtod(str.c_str(), NULL));
        }
}




// void PmergeMe::print_vec(){
//     std::cout << "Before: " << std::endl;
//     std::vector<int>::iterator it;
//     for(it = vec.begin(); it != vec.end(); it++){
//         std::cout << *it << " ";
//     }
//     std::cout << std::endl;
// }

// void PmergeMe::print_deq(){
//     std::cout << "Before: " << std::endl;
//     std::deque<int>::iterator it;
//     for(it = deq.begin(); it != deq.end(); it++){
//         std::cout << *it << " ";
//     }
//     std::cout << std::endl;
// }

