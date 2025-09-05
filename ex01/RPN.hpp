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
        void do_operation(char token);
    public:
        RPN();
        RPN(char *str_array);
        ~RPN();
        RPN(const RPN &other);
        RPN& operator=(const RPN &other);
        void print_stack();

};

class ArgumentException: public std::exception{
    public:
        const char* what() const throw(){
            return ("ArgumentException: Argument count must be 2.");
        }
};

class ArgumentValueException: public std::exception{
    public:
        const char* what() const throw(){
            return ("ArgumentValueException: Second value of the argument must be number");
        }
};

class ValueLimitException: public std::exception{
    public:
        const char* what() const throw(){
            return ("ValueLimitException: Value must be range between 0 to 9.");
        }
};

class DivideByZeroException: public std::exception{
    public:
        const char* what() const throw(){
            return ("Cannot divide by zero.");
        }
};

class EmptyArgException:public std::exception{
    public:
        const char* what() const throw(){
            return ("EmptyArgException: Stack is empty.");
        }
};

class BracketException:public std::exception{
    public:
        const char* what() const throw(){
            return ("Error");
        }
};

class NoOperatorException:public std::exception{
    public:
        const char* what() const throw(){
            return ("NoOperatorException: No Operator is inputed for RPN.");
        }
};

class FormatException:public std::exception{
    public:
        const char* what() const throw(){
            return ("FormatException:Operators and numbers must be separated by spaces.");
        }
};

class NoNumberException:public std::exception{
    public:
        const char* what() const throw(){
            return ("NoNumberException: Number not found for RPN.");
        }
};

class StackSizeException:public std::exception{
    public:
        const char* what() const throw(){
            return ("StackSizeException: Less than 2 numbers in stack for RPN.");
        }
};

class StackOverloadException:public std::exception{
    public:
        const char* what() const throw(){
            return ("StackSizeException: Not enough operators/ numbers overload in stack for RPN.");
        }
};

#endif