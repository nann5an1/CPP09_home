#ifndef BITCOIN_EXCHANGE_HPP
# define BITCOIN_EXCHANGE_HPP

#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <limits.h>
#include <stdlib.h>
#include <map>

class BitcoinExchange{
    private:
        std::map <std::string, double> map_db;
        int value_check(std::string token);
        int identify_date(std::string token);
        void map_iteration(std::map <std::string, double> &map_db, std::string &date_token, int val_token);
        void map_input(std::fstream &file, std::string &line, std::map<std::string, double> &map_db);
        void read_file_input(std::fstream &input_file, std::string &input_line, std::map<std::string, double> map_db);
    public:
        BitcoinExchange();
        ~BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        void run(char* filename);
        // void print_map(std::map<std::string, double> map_db);
};

class FormatException : public std::exception{
    public:
        const char* what() const throw(){
            return ("FormatException: Wrong header format in input txt.");
        }
};

#endif