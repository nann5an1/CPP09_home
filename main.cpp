#include "PmergeMe.hpp"

// =================== Insertion Sort ===================
// Worst-case comparisons for n elements: n*(n-1)/2
size_t insertion_sort_comparisons(size_t n) {
    return n * (n - 1) / 2;
}

// =================== Merge Sort ===================
// Approximate number of comparisons for n elements: n*log2(n)
size_t merge_sort_comparisons(size_t n) {
    if (n < 2) return 0;
    // exact recurrence: C(n) = C(floor(n/2)) + C(ceil(n/2)) + n - 1
    // but approximation n*log2(n) is fine
    return static_cast<size_t>(n * log2(n));
}

//F(n) = sum ceil(log2((3/4)*k))
long long Ford_(int n) {
    long long sum = 0;
    for (int k = 1; k <= n; ++k) {
        double val = (3.0 / 4.0) * k;
        sum += (long long)ceil(log2(val));
    }
    return sum;
}

// Stirling approximation for log2(n!)
double log2_factorial_stirling(int n) {
    if (n == 0) return 0;
    return n * log2(n)
        - n * log2(exp(1.0))
        + 0.5 * log2(2 * M_PI * n);
}

// Approximation for F(n)
double NotFord(int n) {
    if (n == 0) return 0;
    return log2_factorial_stirling(n) + n * log2(3.0 / 4.0);
}

int main(int ac, char** av){
    
    try
    {
        if(ac > 1){
            PmergeMe pmerge;
            pmerge.execute(ac, av);
            // std::ios::sync_with_stdio(false);
            std::cout << std::fixed << std::setprecision(5);

            std::vector<int> test_vals;
            test_vals.push_back(21);
            test_vals.push_back(22);
            test_vals.push_back(25);
            test_vals.push_back(30);
            test_vals.push_back(50);
            test_vals.push_back(2500);
            test_vals.push_back(3000);

            
            for (size_t n = 0; n < test_vals.size(); ++n) {
                std::cout << "Tested with = " << std::setw(4) << test_vals[n]
                    << " | comparison count (Ford) = " << std::setw(8) << Ford_(test_vals[n]) //Ford–Johnson comparison count formula.
                    << " | logarithmic form (approx): = " << std::setw(12) << NotFord(test_vals[n]) //Stirling’s approximation (logarithmic form)
                    << " | Insertion comparisons: " << insertion_sort_comparisons(test_vals[n])
                    << " | Merge comparisons (approx): " << merge_sort_comparisons(test_vals[n])
                    << std::endl;
            }
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