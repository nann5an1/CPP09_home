#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <cassert>
#include <algorithm>
#include <stdlib.h>
#include <iomanip>
#include <iterator>
#include <iostream>
#include <vector>
#include <deque>
#include <exception>
#include <limits.h>
#include <utility>
#include <cmath>
#include <sys/time.h>

class PmergeMe {
    private:
        int final_flag;
        std::vector<std::pair<int, int> > pairs, sorted_pairs;
        std::vector<int> vec, input_vec,
        main_chaine, pending_chaine, original_pending, 
        original_main, sorted_main_chaine;
        std::deque<int> deq;
        static int  n_comparisons;
    public:
        PmergeMe();
        ~PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);

        void digit_check(int ac, char **av);
        void execute(int ac, char **av);
        std::vector<int> generate_sequence();
        void time_comparision_output(double duration_deq, double duration_vec);
        int duplicate_check(std::vector<int> &input_vec);
        static bool    comparison_count(int a, int b);

        // print helpers
        template <typename T>
        void print_container(T& container){
        final_flag ? std::cout << "After: " : std::cout << "Before: ";
        
        // std::cout << container.size() << std::endl;
        if(container.size() > 5){
            for(size_t it = 0; it != container.size() - (container.size() - 5); it++)
                std::cout << container[it] << " ";
            std::cout << "[...]" << std::endl;
        }
        else{
            for(size_t it = 0; it != container.size(); it++)
                std::cout << container[it] << " " ;
            std::cout << std::endl;
        }
    }

    //debug print pairs
        template <typename T>
        void print_pair(T& container) {
            typename T::iterator it;
            std::cout << "Print pair: ";
            for (it = container.begin(); it != container.end(); ++it) {
                std::cout << "[" << it->first << ", " << it->second << "]";
                if (it + 1 != container.end()) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }

        // ford–johnson recursive
        template <typename T>
        T ford_johnson(T& container) {
            if (container.size() <= 1) return container;

            std::vector<std::pair<typename T::value_type, typename T::value_type> > local_pairs;
            ford_original_pairs(container, local_pairs); //local pairs has the ordered pairs of the container

            T bigger_elements;
            T smaller_elements;
            ford_separate_pairs(local_pairs, bigger_elements, smaller_elements);

            T sorted_main = ford_johnson(bigger_elements);

            for (typename T::iterator it = smaller_elements.begin(); it != smaller_elements.end(); ++it) {
                typename T::iterator pos = std::lower_bound(sorted_main.begin(), sorted_main.end(), *it, comparison_count);
                sorted_main.insert(pos, *it);
            }
            return sorted_main;
        }

        // pair operations
        template <typename T>
        void separate_pairs(T& container){
            typename T::iterator it;
            for(it = container.begin(); it != container.end(); ++it){
                if(it->second != -1)
                    main_chaine.push_back(it->first);
                if(it->second == -1)
                    pending_chaine.push_back(it->first);
                else
                    pending_chaine.push_back(it->second);
            }
        }

        template <typename T>
        void get_original_pairs(T& container){
            typename T::iterator it;
            for(it = container.begin(); it != container.end(); ++it){
                if((it + 1) != container.end()){
                    if(*it < *(it + 1))
                        std::swap(*it, *(it + 1));
                    pairs.push_back(std::make_pair(*it, *(it + 1)));
                    ++it;
                }
                else{
                    pairs.push_back(std::make_pair(*it, -1));
                    break;
                }
            }
        }

        template <typename T>
        void ford_original_pairs(const T& container, std::vector<std::pair<int,int> >& paired) { //container is the original main chain, paired is the local pairs
            typename T::const_iterator it;
            for (it = container.begin(); it != container.end(); ++it) {
                if ((it + 1) != container.end()) {
                    int a = *it;
                    int b = *(it + 1);
                    if (a < b)
                        std::swap(a, b);
                    paired.push_back(std::make_pair(a, b));
                    ++it;
                } else {
                    paired.push_back(std::make_pair(*it, -1));
                    break;
                }
            }
        }

        template <typename T>
        void ford_separate_pairs(
            const std::vector<std::pair<int,int> >& paired, //paired is the ordered pairs [10, 3], [14, 2]
            T& bigger_elements,
            T& smaller_elements
        ) {
            typename std::vector<std::pair<int,int> >::const_iterator it;
            for (it = paired.begin(); it != paired.end(); ++it) {
                if(it->second != -1)
                    bigger_elements.push_back(it->first);
                if(it->second == -1)
                    smaller_elements.push_back(it->first);
                else
                    smaller_elements.push_back(it->second);
            }
        }

    
        template <typename T>
        void binary_insertion_sort(T& container, int value_to_insert) {
            typename T::iterator pos = std::lower_bound(container.begin(), container.end(), value_to_insert, comparison_count);
            container.insert(pos, value_to_insert);
        }

        //declarations
        template <typename T>
        void jacobsthal(T& sorted_main);

        template <typename T>
        void sort_container(T& container);
};

class NotANumberException: public std::exception{
    public: const char* what() const throw(){ return "Error."; }
};
class NotAnIntException: public std::exception{
    public: const char* what() const throw(){ return "Error: not an integer."; }
};
class PositiveNumberException: public std::exception{
    public: const char* what() const throw(){ return "Error: no negative number is allowed."; }
};
class DuplicateNumberException: public std::exception{
    public: const char* what() const throw(){ return "Error: Duplicate number included."; }
};
class ArgumentNotEnough: public std::exception{
    public: const char* what() const throw(){ return "Error: Argument count less than 2"; }
};
#endif
