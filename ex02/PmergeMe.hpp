#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <algorithm>
#include <stdlib.h>
#include <iterator>
#include <iostream>
#include <vector>
#include <deque>
#include <exception>
#include <limits.h>
#include <utility>

class PmergeMe{
    private:
        std::vector<int> input_vec;
        std::vector<int> vec;
        std::deque<int> deq;
    public:
        PmergeMe();
        ~PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);

        void digit_check(int ac, char **av);
        void execute(int ac, char **av);

        //print_container_template
        template <typename T>
        void print_container(T &container){
            
            typename T::iterator it;
            std::cout << "Before: " << " ";
            for(it = container.begin(); it != container.end(); it++){
                std::cout << *it << " ";
            }
            std::cout << std::endl;
        }

        template <typename T>
        void print_pair(T &container) {
            typename T::iterator it;
            std::cout << "Print pair: ";
            for (it = container.begin(); it != container.end(); ++it) {
                std::cout << "[" << it->first << ", " << it->second << "]";
                if (it + 1 != container.end()) {   // works only for random-access (vector)
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }

        //ford_johnson_template
        template <typename T>
        void ford_johnson(T &container){    
            typename T::iterator it;

            std::vector<std::pair<int, int> > paired;
            std::vector<std::pair<int, int> >::iterator it_paired;

            // Step 1: make into pairs, larger element first
            for(it = container.begin(); it != container.end(); ++it){
                if((it + 1) != container.end()){
                    if(*it < *(it + 1))
                        std::swap(*it, *(it + 1));

                    paired.push_back(std::make_pair(*it, *(it + 1)));
                    ++it;
                }
                else{
                    paired.push_back(std::make_pair(*it, -1));
                    break;
                }
            }

            // Step 2: insertion sort by first element of the pair
            for(it_paired = paired.begin() + 1; it_paired != paired.end(); ++it_paired){
                std::pair<int,int> key = *it_paired;
                std::vector<std::pair<int,int> >::iterator j = it_paired;

                while(j != paired.begin() && (j-1)->first > key.first){
                    *j = *(j-1);
                    --j;
                }

                *j = key;
            }

            // Step 3: print the pairs
            for(it_paired = paired.begin(); it_paired != paired.end(); ++it_paired){
                std::cout << "[" << it_paired->first << ", " << it_paired->second << "] ";
            }
            std::cout << std::endl;
        }

            
        // void print_vec();
        // void print_deq();
    
        
};

class NotANumberException: public std::exception{
    public:
        virtual const char* what() const throw(){
            return "Error: not a number.";
        }
};

class NotAnIntException: public std::exception{
    public:
        virtual const char* what() const throw(){
            return "Error: not an integer.";
        }
};

class PositiveNumberException: public std::exception{
    public:
        virtual const char* what() const throw(){
            return "Error: no negative number is allowed.";
        }
};

#endif