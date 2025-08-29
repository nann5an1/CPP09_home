#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <exception>
#include <stdio.h>
#include <stack>
#include <sstream>
#include <algorithm>

class RPN{
    private:
        std::stack<int> rpn_stack;
        int prev_top;
    public:
        RPN();
        RPN(char *str_array);
        ~RPN();
        RPN(const RPN &other);
        RPN& operator=(const RPN &other);
        void do_operation(char token);
        void add();
        void print_stack();
        void subtract();
        void multiply();
        void divide();

};

class ArgumentException: public std::exception{
    public:
        const char* what() const throw(){
            return ("Argument count must be 2.");
        }
};

class ArgumentValueException: public std::exception{
    public:
        const char* what() const throw(){
            return ("Second value ofthe argument must be number");
        }
};


#endif