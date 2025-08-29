#include "RPN.hpp"

RPN::RPN(){}

RPN::RPN(char *str_array){ //str_array = av[1]
    int flag = 0;
    std::string str = str_array;
    std::istringstream ss(str);
    char token;
    std::cout << "Token print << " << std::endl;
    while (ss >> token){ //read token by token
        // std::cout << token << " ";

        // check if the second token is number
        if(flag == 1 && (token == '+' || token == '-' || token == '*' || token == '/')){
            throw ArgumentValueException();
        }
        else{
            //  std::cout << "token " << token <<  std::endl;
            if(token == '+' || token == '-' || token == '*' || token == '/' ){
                do_operation(token);
            }
            else{
                // std::cout << "token for push << " << token - '0' << std::endl;
                // std::cout << rpn_stack.top() << std::endl;
                this->rpn_stack.push(token - '0');
            }
                
        }
        flag++;
    }
    // std::cout << "--- stack loop ---" << std::endl;
    // while(!rpn_stack.empty()){
    //     // std::cout << "\nrpn stack top << " << rpn_stack.top() << std::endl;
    //     rpn_stack.pop();
    // }
        
    std::cout << "\nrpn stack top << " << rpn_stack.top() << std::endl;
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

void RPN::add(){
    int temp;
    temp = rpn_stack.top();
    rpn_stack.pop();
    temp += rpn_stack.top();
    rpn_stack.pop();
    rpn_stack.push(temp);
    // std::cout << "result << " << temp << std::endl;
    print_stack();
}

void RPN::subtract(){
    int top = rpn_stack.top();
    rpn_stack.pop();
    int sec_top = rpn_stack.top();
    rpn_stack.push(sec_top - top);
    print_stack();
}

void RPN::do_operation(char token){
    // int secTop;
    // int top;

    //////////////
    switch (token)
    {
    case '+':
        add();
        break;
    case '-':
        subtract();
        break;
    default:
        break;
    }
   
}

void RPN::print_stack(){
    std::stack<int> temp_stack = rpn_stack;
    std::cout << "--- stack loop ---" << std::endl;
    while(!temp_stack.empty()){
        std::cout << temp_stack.top() << " ";
        temp_stack.pop();
    }
    std::cout << std::endl;
}