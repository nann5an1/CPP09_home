#include "RPN.hpp"

RPN::RPN(){}

RPN::RPN(char *str_array){ //str_array = av[1]
    int flag = 0;
    std::string str = str_array;
    std::istringstream ss(str);
    std::string token;

    if(str.length() == 0 || str == " ") throw EmptyArgException();
    else if(str.find("\(") != std::string::npos || str.find(")") != std::string::npos) throw BracketException();
    else if(str.find("+") == std::string::npos && 
            str.find("-") == std::string::npos &&
            str.find("*") == std::string::npos &&
            str.find("/") == std::string::npos)
        throw NoOperatorException();
    // else{
    //      for (int i = 0; i <= 9; i++)
    //         str.find(i + '0') == std::string::npos ? throw NoNumberException() : 0;
    // }
       
    // std::cout << "Token print << " << std::endl;
    while (ss >> token){ //read token by token
        // std::cout << token << " ";

        // check if the second token is number
        if(flag == 1 && (token == "+" || token == "-" || token == "*" || token == "/"))
            throw ArgumentValueException();
        else if(token.length() > 1 && (atoi(token.c_str()) < 0 || atoi(token.c_str()) >= 10)) throw ValueLimitException();
        else if (token.length() > 1)throw FormatException();
        else{
            if(token == "+" || token == "-" || token == "*" || token == "/" )
                do_operation(token[0]);
            else{
                // std::cout << "token for push << " << token  << std::endl;
                this->rpn_stack.push(token[0] - '0');
                // print_stack();
            }
        }
        flag++;
    }
    if(rpn_stack.size() > 1)
        throw StackOverloadException();
    std::cout << "\nrpn result << " << rpn_stack.top() << std::endl;
}

RPN::~RPN(){}
RPN::RPN(const RPN &other){
    *this = other;
}

RPN& RPN::operator=(const RPN &other){
    if(this != &other)
        this->rpn_stack = other.rpn_stack;
    return *this;
}

void RPN::do_operation(char token){
    if(rpn_stack.size() < 2)
        throw StackSizeException();
    int newTop;
    int firstTop = this->rpn_stack.top();
    this->rpn_stack.pop();
    int secTop = this->rpn_stack.top();
    this->rpn_stack.pop();
  
    switch (token)
    {
    case '+':
        newTop = secTop + firstTop;
        break;
    case '-':
        newTop = secTop - firstTop;
        break;
    case '*':
        newTop = secTop * firstTop;
        break;
    case '/':
        if(firstTop == 0)
            throw DivideByZeroException();
        newTop = secTop / firstTop;
        break;
    default:
        break;
    }
    this->rpn_stack.push(newTop);
    // print_stack();
}

void RPN::print_stack(){
    std::stack<int> temp_stack = rpn_stack;
    std::cout << "--- stack print ---" << std::endl;
    while(!temp_stack.empty()){
        std::cout << temp_stack.top() << " ";
        temp_stack.pop();
    }
    std::cout << std::endl;
}