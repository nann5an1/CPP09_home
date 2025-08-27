#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <exception>
#include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
#include <stack>
#include <sstream>


class RPN{
    public:
        RPN();
        RPN(char *str_array);
        ~RPN();
        RPN(const RPN &other);
        RPN& operator=(const RPN &other);
        void do_operation(std::string token);
};

class ArgumentException: public std::exception{
    public:
        const char* what() const throw(){
            return ("Arguement count must be 2.");
        }
};


#endif