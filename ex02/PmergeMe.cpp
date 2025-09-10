#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){}
PmergeMe::~PmergeMe(){}
PmergeMe::PmergeMe(const PmergeMe &other){ *this = other; }
PmergeMe& PmergeMe::operator=(const PmergeMe &other){ if(this != &other) (void)other; return *this; }

int PmergeMe::duplicate_check(std::vector<int> &input_vec){
    std::vector<int> temp_vec = input_vec;
    std::sort(temp_vec.begin(), temp_vec.end());
    for(size_t i = 1; i < temp_vec.size(); i++)
        if(temp_vec[i] == temp_vec[i-1]) return 1;
    return 0;
}

void PmergeMe::digit_check(int ac, char **av){
    for(int count = 1; count < ac; ++count){
        std::string str = av[count];
        int length = str.length() - 1;
        int i = 0;
        if(str[0] == '+') i++;
        if(str.length() == 0) throw NotANumberException();
        while(i <= length)
            if(!isdigit(str[i++])) throw NotANumberException();
        if(strtod(str.c_str(), NULL) > INT_MAX) throw NotAnIntException();
        if(strtod(str.c_str(), NULL) < 0) throw PositiveNumberException();
        input_vec.push_back(strtod(str.c_str(), NULL));
        if(duplicate_check(input_vec)) throw DuplicateNumberException();
        vec.push_back(strtod(str.c_str(), NULL));
        deq.push_back(strtod(str.c_str(), NULL));
    }
}

double get_time_microseconds() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000.0 + tv.tv_usec) ;
}

void PmergeMe::execute(int ac, char **av){
    final_flag = 0;
    digit_check(ac, av);

    /////////////////// deque sorting /////////////////////////////
    
    //main idea => keep the pending separate (untouched)
    double start_time_deq = get_time_microseconds();
    sort_container(deq);
    double end_time_deq = get_time_microseconds();
    double duration_deq = end_time_deq - start_time_deq;

    /////////////////// vector sorting /////////////////////////////

    double start_time_vec = get_time_microseconds();
    sort_container(vec);
    double end_time_vec = get_time_microseconds();
    double duration_vec = end_time_vec - start_time_vec;
    

    //////////////////////// final output time comparisons //////////////////////
    print_container(input_vec);
    final_flag = 1;
    print_container(sorted_main_chaine);
    time_comparision_output(duration_deq, duration_vec);
}

void PmergeMe::time_comparision_output(double duration_deq, double duration_vec){
    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Time to process a range of "<< input_vec.size() 
              << " elements with std::deque : " << duration_deq << " us" << std::endl;
    std::cout << "Time to process a range of "<< input_vec.size() 
              << " elements with std::vector : " << duration_vec << " us" << std::endl;
}

int calculation(int n){ //jacobsthal formula
    int numerator = (std::pow(2, n))-(std::pow(-1, n));
    return numerator / 3;
}

//generate the index sequence of the Jacobsthal (1, 3, 2, 5, 4,....)
std::vector<int> PmergeMe::generate_sequence() {
    std::vector<int> seq;
    int n = original_pending.size();
    if (n == 0) return seq;

    int last = 1; // first index
    seq.push_back(1);

    for (int k = 3; ; ++k) {  // start at J(3)=3
        int j = calculation(k);
        if (j > n) j = n; //check if the jaconsthal value is greater than original pending size

        // insert from j down to last+1 (reverse order)
        for (int idx = j; idx > last; --idx)
            seq.push_back(idx);

        last = j;
        if (j == n) break;
    }
    return seq;
}


template <typename T>
void PmergeMe::jacobsthal(T& sorted_main) {
    if (original_pending.empty())
        return;

    std::vector<int> jacobsthal_sequence = generate_sequence();

    // std::cout << "original_pending[0]: " << original_pending[0] << std::endl;
    // std::cout << "value to insert" << original_pending[0] << std::endl;

    for (size_t i = 0; i < jacobsthal_sequence.size(); ++i) {
        int idx = jacobsthal_sequence[i];
        // std::cout << "idx1: " << idx << std::endl;
        // std::cout << "Value to insert: " << original_pending[idx - 1] << std::endl;
        binary_insertion_sort(sorted_main, original_pending[idx - 1]);
    }
    original_pending.clear();
}


// explicit instantiations
template void PmergeMe::jacobsthal<std::vector<int> >(std::vector<int>&);
template void PmergeMe::jacobsthal<std::deque<int> >(std::deque<int>&);

template <typename T>
void PmergeMe::sort_container(T& container){
    pairs.clear(); sorted_pairs.clear();
    main_chaine.clear(); pending_chaine.clear();
    original_pending.clear(); original_main.clear();
    sorted_main_chaine.clear();

    get_original_pairs(container);
    separate_pairs(pairs);

    original_pending = pending_chaine;
    original_main = main_chaine;

    // std::cout << "<< Original pending: >> " << std::endl; 
    // print_container(original_pending);
    // std::cout << std::endl;

    sorted_main_chaine = ford_johnson(original_main);

    // reorder pending according to new sorted_main order
    std::vector<int> reordered_pending;
    for (size_t i = 0; i < sorted_main_chaine.size(); ++i) {
        int main_val = sorted_main_chaine[i];
        for (size_t j = 0; j < pairs.size(); ++j) {
            if (pairs[j].first == main_val && pairs[j].second != -1) {
                reordered_pending.push_back(pairs[j].second);
                break;
            }
        }
    }
    for (size_t j = 0; j < pairs.size(); ++j) {
        if (pairs[j].second == -1) {
            reordered_pending.push_back(pairs[j].first);
        }
    }
    original_pending = reordered_pending;

    // std::cout << "<< Reordered pending: >> " << std::endl; 
    // print_container(original_pending);
    // std::cout << std::endl;
    
    jacobsthal(sorted_main_chaine);

   
    // print_container(sorted_main_chaine);
}

// explicit instantiations
template void PmergeMe::sort_container<std::vector<int> >(std::vector<int>&);
template void PmergeMe::sort_container<std::deque<int> >(std::deque<int>&);
