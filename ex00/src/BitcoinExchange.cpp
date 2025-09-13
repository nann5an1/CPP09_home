#include "../inc/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){}  
BitcoinExchange::~BitcoinExchange(){}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& other){
    *this = other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange& other){
    if(this != &other)
        this->map_db = other.map_db;
    return *this;
}

void BitcoinExchange::run(char *filename){
    std::string token;
    std::string line, input_line;
    std::fstream file, input_file;
    
    file.open("data.csv", std::ios::in);
    if (!file.is_open()) throw FailedToOpenException();

    //taking the csv file into the map
    map_input(file, line, map_db);

    //read the input txt file
    input_file.open(filename);
    if(input_file.fail()) throw FailedToOpenException();
    read_file_input(input_file, input_line, map_db);
}

//map input into map_db
void BitcoinExchange::map_input(std::fstream &file, std::string &line, std::map<std::string, double> &map_db){
   while(std::getline(file, line)){ //read the whole file
        std::stringstream ss(line);
        std::string date;
        std::string rate_str;

        //data processing into map_db
        int delimeter = line.find(",");
        date = line.substr(0, delimeter);\
        rate_str = line.substr(delimeter + 1, line.size());
        double rate = strtod(rate_str.c_str(), NULL);

        //insert into map
        map_db.insert(std::pair<std::string, double>(date, rate));
    }     
}

void BitcoinExchange::read_file_input(std::fstream &input_file, std::string &input_line, std::map<std::string, double> map_db){
    int bool_date = 0;
    int value_ret = 0;
    std::string token;

   std::getline(input_file, input_line);
    if (input_line.find("date | value") == std::string::npos) throw FormatException();

    //read input file
    while(std::getline(input_file, input_line)){
        std::stringstream ss(input_line); //get each token in the line
        std::string date_token, sep, value_str, extra;

        // if the first 3 tokens don't exist or there's more than 3 tokens it's invalid
         if (!(ss >> date_token >> sep >> value_str) || (ss >> extra)) {
            std::cout << "Error: bad input => " << input_line << std::endl;
            continue;
        }
        bool_date = identify_date(date_token);
        value_ret = value_check(value_str);

        if(!bool_date ) std::cout << "Error: bad input => " << input_line << std::endl;
        if(sep != "|")  std::cout << "Error: bad input => " << input_line << std::endl;
        else if(bool_date && sep == "|"){
            if(value_ret == -1) std::cout << "Error: not a positive number." << std::endl;                 
            else if(value_ret == -2) std::cout << "Error: too large a number." << std::endl;    
            else if (value_ret == 0) std::cout << "Error: value not within range." << std::endl;
            else if (value_ret == -3) std::cout << "Error: not a digit value." << std::endl;
            else if (value_ret == -4) std::cout << "Error: multiple decimals found." << std::endl;
            else if(bool_date) map_iteration(map_db, date_token, value_str);
        }
    }
}

int BitcoinExchange::identify_date(std::string token){
    struct tm tm;
    char* result = strptime(token.c_str(), "%Y-%m-%d", &tm); // attempt to convert to the format

    if(result != NULL && *result == '\0'){
        if(tm.tm_mon == 1 && tm.tm_mday > 29 && (tm.tm_year % 4 == 0 && (tm.tm_year % 100 != 0  || tm.tm_year % 400 == 0))) return 0; //leap year but day is over 29
        else if(tm.tm_mon == 1 && tm.tm_mday >= 29 && (tm.tm_year % 4 != 0 || (tm.tm_year % 100 == 0 && tm.tm_year % 400 != 0))) return 0; //not a leap year but day is equal & over 29
        return 1;
    } 
    else return 0;
    return 1;
}

int BitcoinExchange::value_check(std::string token){
    double value = strtod(token.c_str(), NULL);
    
    if(value > INT_MAX || value < INT_MIN) return -2;
    else if (value > 1000) return 0;
    else if(value < 0) return -1;

    int decimal = 0;
    for(size_t i = 0; i < token.length(); ++i){
        if(token[i] == '.'){
            if(decimal)
                return -4;
            decimal = 1;
            continue;
        } 
        else if(!isdigit(token[i])) return -3;
    }
    
    return 1;
}

void BitcoinExchange::map_iteration(std::map<std::string, double>& map_db, std::string& token, std::string value_str) {
    std::map<std::string, double>::iterator it = map_db.lower_bound(token);
    double value = strtod(value_str.c_str(), NULL);
    if (it == map_db.begin() && (it == map_db.end() || it->first != token)) {
        std::cout << "No earlier date available for " << token << std::endl;
        return;
    }
    // no exact match so step back to nearest lower date
    if (it == map_db.end() || it->first != token)
        --it;
    
    std::cout << token << " => " << value_str << " = "
              << std::fixed << std::setprecision(2) << (it->second * value)
              << std::endl;
}

// void BitcoinExchange::print_map(std::map<std::string, double> map_db){
//    for (std::map<std::string, double>::iterator it = map_db.begin(); it != map_db.end(); ++it) {
//         std::cout << it->first << " => " << std::fixed<< std::setprecision(2) << it->second << std::endl;
//         }
// }