- handle file related errors
- file could not open/ does not exist

from the input file
----------------------
- check if the file header is correct
- read each line of the txt (read each token using stringstream as std::string)
- identify if each of the column is there

column 1
-format using (parse)std::get_time and std::tm

column 2
identity the "|"

column 3, value column
- convert to int
    - check if it's positive
    - check for bigint
    - either a float or a positive integer, between 0 and 1000


while also identifying each of the columns, do this
------------------------------------------
std::map(std::string, int)
- if all the columns are in right format -> put each them into std::map(the correct ones only) in date - value format
-give specific key to each of the undefined rows (later will be iterated and output specific err msg )check below

finding the date
------------------------------------------
- iterate the map and match with each of the dates from the csv (the substr before the ',') use 'find'
- then multipy the value and rate(substr after the ',')