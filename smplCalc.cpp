/*
=========================================================
NANKAI UNIVERSITY, COLLEGE OF SOFTWARE ENGINEERING,
PROGRAMMING WITH HIGH LEVEL LANGUAGE, COURSE PROJECT - 2023
=========================================================
*/

/* List of Library used in this project*/

#include <iostream>   //library for input and output functionality
#include <fstream>    //Provides functions for files
#include <cstring>     //Handling strings library
#include <sstream>    //Implements the input/output operations on memory
#include <cmath>      //Operations and functions of mathematics
#include <regex>      //The regular expressions library
#include <map>        //Store elements in a mapped fashion
#include <functional> //Provides a set of predefined class templates for function objects
#include <algorithm>  //Instance searching, sorting, counting, manipulating and so on
#include <vector>     //Provides vector and matrix classes and vector arithmetic functions
#include <exception>  //Signal errors that cannot be handled locally
#include <thread>
#include <chrono>

#define EULER 2.71828182 // Solving ordinary differential equation
#define PI M_PI          // The ratio of a circle's circumference to diameter

using namespace std;

class Simple_Calculor
{
    map<string, double> variables;

    //  Functions for Mathematics Calculation
    bool math_Func(string math, double &result);
    void math_Op(string &math, string symbol, const function<double(double, double)> &f);
    void math_Func(string &math, string symbol, const function<double(double)> &f);

    static double addition_Func(double val1, double val2);       // function for Addition
    static double subtract_Func(double val1, double val2);       // function for Subtraction
    static double multiplication_Func(double val1, double val2); // function for Multiplication 
    static double division_Func(double val1, double val2);       // function for Division 
    static double exponent_Func(double val1, double val2);       // function for Exponential 

    // Cosine & aCosine in degree functions
    static double cos_Func(double f);
    static double cosRadSolv(double f);
    static double acosDegSolv(double f);
    static double acosRadSolv(double f);

    // Sine & aSine in degree Functions
    static double sinDegSolv(double f);
    static double sinRadSolv(double f);
    static double asinDegSolv(double f);
    static double asinRadSolv(double f);

    // Number and String Conversion Functions
    int hex_Dec(string hex_Value);
    bool validateHex_Input(string hex_Value);
    int BinToDec(int binValue);
    bool StringBinary(string str);

    // Other Supporting Functions
    void remove_Spaces(string &s);
    bool check_StrIsNum(string s);
    bool variable_Def(string Line_Code);
    double getVarMath(string my_Var);

    void string_Filter(char *str);
    bool check_Substring(string s2, string s1);

public:
    Simple_Calculor();
    bool file_Excution(string fileName_Var);

};

int main()
{

    Simple_Calculor calc;


 cout << "                                <=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=>                " << endl;
        cout << "\t\t\t\t| WELCOME TO SIMPLE CALCULATOR BY USING C++ - PROGRAM |" << endl;
        cout << "                                <=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=>                " << endl
             << endl;
        cout << "\t\t THIS CALCULATOR SUPPORT THE FOLLOWING OPERATIONS:-" << endl;
        cout << "                 -------------------------------------------------               " << endl;
        cout << "\t 1. Computations of Binary number (base 2), Hexadecimal number (base 16)" << endl;
        cout << "\t    and Decimal number {base 10}" << endl;
        cout << "\t 2. Variable definitions." << endl;
        cout << "\t 3. Simple calculations." << endl;
        cout << "\t 4. Two  Mathematical Functions:" << endl;
        cout << "\t\t   a. The  sin() -> Sine in degrees." << endl;
        cout << "\t\t   b. The  cos() -> Cosine in degrees." << endl;
        cout << "\t 5.  Multiple operators with Parenthesis and Variables." << endl;
        cout << "\t 6.  Also it support complex expressions." << endl;
        cout << "\t 7.  To exit the program press/type exit command." << endl;
        cout << "\n";
        cout << "\t\t *TIPS*" << endl;
        cout << "\t    For Hexadecimal; the number should start with 0x followed by hexadecimal number," << endl;
        cout << "\t    The letter of hexadecimal number should be capital letter and " << endl;
        cout << "\t    The Binary number should be end with small leller b." << endl;
        cout << "\t    letter b or x are letters for special purposes  do not declare these as a variables" << endl;

        cout << "\t*-=-*-=-=-*-=-=-*-=-=-*-=-=-*-=-=-*-=-=-*-=-=-*-=-=-*-=-=-*-=-=-*-=-=-*-=-=-*-=-=-*-=-=-*-=-*" << endl;
        cout << "\t|All rights reserved | NANKAI UNIVERSITY, COLLEGE OF SOFTWARE ENGINEERING | Copyright - 2023|" << endl;
        cout << "\t*-=-*-=-=-*-=-=-*-=-=-*-=-=-*-=-=-*-=-=-*-=-=-*-=-=-*-=-=-*-=-=-*-=-=-*-=-=-*-=-=-*-=-=-*-=-*" << endl;



    cout << "Enter the name of the file: ";
    string fileName;
    getline(cin, fileName);

   calc.file_Excution(fileName);

   std::this_thread::sleep_for(std::chrono::minutes(5));

}

Simple_Calculor::Simple_Calculor()
{
}

// Function to runs the commands found when running a file. As input it takes

bool Simple_Calculor::file_Excution(string file_name)
{

  string fileName = file_name;


    // Open the file for reading
    ifstream inputFile(fileName);

    // Check if the file is opened successfully
    if (!inputFile.is_open()) {
        cout<< "Error opening the file." << std::endl;
        return 1;
    }


    // Variables definition
    double result;
    string Read_line;

    variables["pi"] = PI;
    variables["e"] = EULER;

    // Continue to loop while the file is not finished or an no error has been occured

    while (getline(inputFile, Read_line))
    {
        Read_line = Read_line.substr(0, Read_line.size());
        try
        {

            // Pass arguments for filename and line to read


            // If the line has "----" command as Header print out header
            if (Read_line == "----")
            {
                cout << "----" << endl;
            }
             // Stop the loop, If an exit command is excuted
            else if (Read_line == "exit")
            {
                break;
            }
            // Move to the another line, If the line has assignment operation
            else if (variable_Def(Read_line))
            {
                continue;
            }
            // Move to the another line, If the line has math operations
            else if (math_Func(Read_line, result))
            {
                cout << result << endl;
            }

        }
        // Print error and return false If an exception string caughted
        catch (string e)
        {
            cout << e << endl;

            return false;
        }
    }

    // Close the file and return true, if the loop has been completed
    inputFile.close();

    return true;
}

// Function  to runs the commands entered by the users.
// It returns true if sucessful and false if errors occured

bool Simple_Calculor::variable_Def(string Line_Code)
{
    // Matching strings and for matching math/variable expressions
    regex mathRegex("[\\w]+[ ]?=[ ]?[^\\s]+");

    smatch match;

    if (regex_search(Line_Code, match, mathRegex))
    {
        Line_Code = match[0];

        // Split the string at "LET" and the "="
        int equalsIndex = Line_Code.find("=");
        // The variable name is the value between "LET" and "=". The math comes after the "="
        string my_Var = Line_Code.substr(0, equalsIndex);
        string math = Line_Code.substr(equalsIndex + 1);

        // Remove the spaces left in the variable.
        remove_Spaces(my_Var);

        double result;

        math_Func(math, result);

        variables[my_Var] = result;

        return true;
    }
    // Return False If the expression did not match either regex
    else
    {
        return false;
    }
}

// Mathmatics Functions

bool Simple_Calculor::math_Func(string math, double &result)
{
    // Loops over all of the string
    for (long unsigned int i = 0; i < math.size(); i++)
    {
        /* Check for parentheses and if they are found solve the
         math inside them and then replace the parentheses with the result
        */
        if (math.at(i) == '(')
        {
            /*
            This holds the parentheses count. A '(' increaes the cound by one
             while a ')' decreases the cound by one. When pCount equals zero you know that you
             have found the right parentheses that matches your current left parentheses.
             */
            int pCount = 1;

            // Position where the left parenteseis was found.
            int pPos = i;

            // Index to start looking for the right parentheses
            long unsigned int index = i + 1;

            // loop until either the end of the string or the right parentheses was found
            while (index < math.size() && pCount != 0)
            {
                if (math.at(index) == '(')
                {
                    pCount++;
                }
                if (math.at(index) == ')')
                {
                    pCount--;
                }
                index++;
            }

            // If the end of the string is reached and the mathching parentheses was not found then throw and error
            if (index >= math.size() && pCount != 0)
            {
                cout << "ERROR: Parentheses mismatch." << endl;
                // throw string("ERROR: Parentheses mismatch.");
            }
            else
            {
                // Extract the command inside the parentheses
                string pSub = math.substr(pPos + 1, index - pPos - 2);

                // Check if it is not blank
                if (pSub == "")
                {
                    throw string("Error: Empty parentheses.");
                }

                // Solve the math and replace the parentheses with the answer
                math_Func(pSub, result);
                math.erase(pPos, index - pPos);
                math.insert(pPos, to_string(result));
            }
        }
    }

    // Run the mathematical operation functions
    math_Op(math, "^", this->exponent_Func);
    math_Op(math, "*", this->multiplication_Func);
    math_Op(math, "/", this->division_Func);
    math_Op(math, "+", this->addition_Func);
    math_Op(math, "-", this->subtract_Func);

    // Run the sine Calculation Function functions
    math_Func(math, "asinr", asinRadSolv);
    math_Func(math, "sinr", sinRadSolv);
    math_Func(math, "asin", asinDegSolv);
    math_Func(math, "sin", sinDegSolv);

    // Run the cosine Calculation functions
    math_Func(math, "acosr", acosRadSolv);
    math_Func(math, "cosr", cosRadSolv);
    math_Func(math, "acos", acosDegSolv);
    math_Func(math, "cos", cos_Func);

    remove_Spaces(math);
    int binValue, decnumber;

    if (check_StrIsNum(math))
    {
        result = stof(math);

    }
    else if (StringBinary(math) && check_Substring("b", math))
    {

        math.erase(remove(math.begin(), math.end(), 'b'), math.end());

        binValue = stoi(math);
        decnumber = BinToDec(binValue);
        math = to_string(decnumber);
        result = stof(math);
    }
    else if (validateHex_Input(math) && check_Substring("0x", math))
    {

    if (math.substr(0, 2) == "0x") {
            math = math.substr(2);
        }

        decnumber = hex_Dec(math);
        math = to_string(decnumber);
        result = stof(math);
    }
    else
    {
        result = getVarMath(math);
    }

    return true;
}

/*
Runs the given math operation function on the math string. As input it takes a referance to
the math string, the symbol for the operator, and a funciton pointer to the functions that will
be used to actually solve the operator. This function returns nothing.
*/
void Simple_Calculor::math_Op(string &math, string symbol, const function<double(double, double)> &f)
{
    // Make a regex to find all the instances of the operator
    smatch sm;
    regex reg("[\\w.]+[ ]?\\" + symbol + "[ ]?[\\w.]+");

    // Find and loop through all the instances
    while (regex_search(math, sm, reg))
    {
        string sub = sm[0];

        remove_Spaces(sub);

        int splitIndex = sub.find(symbol);

        // Get the data on the left and right side of the operator
        string left = sub.substr(0, splitIndex);
        string right = sub.substr(splitIndex + 1);

        double val2, val1;
        int binValue, decnumber;

        // Check if the right side is a variable and if it is access its value from one of the maps.
        if (check_StrIsNum(right))
        {
            val2 = stof(right);
        }
        else if (StringBinary(right) && check_Substring("b", right))
        {

            right.erase(remove(right.begin(), right.end(), 'b'), right.end());

            binValue = stoi(right);
            decnumber = BinToDec(binValue);
            right = to_string(decnumber);
            val2 = stof(right);
        }
        else if (validateHex_Input(right) && check_Substring("0x", right))
        {
            string chars = "0x";
            for (char c : chars)
            {
                right.erase(remove(right.begin(), right.end(), c), right.end());
            }
            decnumber = hex_Dec(right);
            right = to_string(decnumber);
            val2 = stof(right);
        }
        else if (variables.find(right) != variables.end())
        {
            val2 = getVarMath(right);
        }

        // Check if the left side is a variable and if it is access its value from one of the maps.
        if (check_StrIsNum(left))
        {

            val1 = stof(left);
        }
        else if (StringBinary(left) && check_Substring("b", left))
        {

            left.erase(remove(left.begin(), left.end(), 'b'), left.end());

            binValue = stoi(left);
            decnumber = BinToDec(binValue);
            left = to_string(decnumber);
            val1 = stof(left);
        }
        else if (validateHex_Input(left) && check_Substring("0x", left))
        {
            string chars = "0x";
            for (char c : chars)
            {
                left.erase(remove(left.begin(), left.end(), c), left.end());
            }
            decnumber = hex_Dec(left);
            left = to_string(decnumber);
            val2 = stof(left);
        }
        else

        {
            val1 = getVarMath(left);
        }

        // Solve the math for the operator using the given function
        double result = f(val1, val2);

        // Replace the operator and the values to its left and right with the answer
        int startPos = sm.position(0);
        int len = sm[0].str().size();
        math.erase(startPos, len);
        math.insert(startPos, to_string(result));
    }
}

// Functions for solve the math operations
double Simple_Calculor::exponent_Func(double val1, double val2)
{
    return pow(val1, val2);
}

double Simple_Calculor::multiplication_Func(double val1, double val2)
{
    return val1 * val2;
}

double Simple_Calculor::division_Func(double val1, double val2)
{
    if (val2 == 0) {
        std::cout << "Error: Division by zero. Returning NaN." << std::endl;
        return std::numeric_limits<double>::quiet_NaN();
    }
    return val1 / val2;
}

double Simple_Calculor::addition_Func(double val1, double val2)
{
    return val1 + val2;
}

double Simple_Calculor::subtract_Func(double val1, double val2)
{
    return val1 - val2;
}

// Functions for solving sine
double Simple_Calculor::sinDegSolv(double f)
{
    return sin((f * PI) / 180.0);
}

double Simple_Calculor::sinRadSolv(double f)
{
    return sin(f);
}

double Simple_Calculor::asinDegSolv(double f)
{
    return (asin(f) * 180.0) / PI;
}

double Simple_Calculor::asinRadSolv(double f)
{
    return asin(f);
}

// Functions for solving cosine
double Simple_Calculor::cos_Func(double f)
{
    return cos((f * PI) / 180.0);
}

double Simple_Calculor::cosRadSolv(double f)
{
    return cos(f);
}

double Simple_Calculor::acosDegSolv(double f)
{
    return (acos(f) * 180.0) / PI;
}

double Simple_Calculor::acosRadSolv(double f)
{
    return acos(f);
}

// Runs the given math operation function on the math string.
void Simple_Calculor::math_Func(string &math, string symbol, const function<double(double)> &f)
{
    // Create the regex that will actually find the given functio "symbol" such as sin
    smatch sm;
    regex reg(symbol + "([\\w.]+)");

    // Find all the instances of the "symbol" and loop through all of them
    while (regex_search(math, sm, reg))
    {
        string value = sm[0].str().substr(symbol.size());
        remove_Spaces(value);
        double doubleValue;

        // Check if the right side is a variable and if it is access its value from one of the maps.
        if (check_StrIsNum(value))
        {
            doubleValue = stof(value);
        }
        else if (variables.find(value) != variables.end())
        {
            doubleValue = getVarMath(value);
        }

        // Solve for the value using the given function pointer
        double result = f(doubleValue);

        // Check and make sure the value return was not a nan.
        if (isnan(result))
        {
            throw string("ERROR: Invalid function operation");
        }

        // Repalce the operator and its value with the answer
        int startPos = sm.position(0);
        int len = sm[0].str().size();
        math.erase(startPos, len);
        math.insert(startPos, to_string(result));
    }
}

// Supporting Functions

// Retreive a variable value as a double for use in the math solver
double Simple_Calculor::getVarMath(string my_Var)
{
   
    if (variables.find(my_Var) != variables.end())
    {
        return variables[my_Var];
    }
    else
    {
        // throw string("ERROR: Invalid Input or Function/Variable not found."+my_Var);
        // cout << "ERROR: Invalid Input or Function/Variable not found." << endl;
        return std::numeric_limits<double>::quiet_NaN();
    }
}

// Checks if the given string only contains numbers
bool Simple_Calculor::check_StrIsNum(string s)
{
    for (long unsigned int i = 0; i < s.size(); i++)
    {
        if (isdigit(s.at(i)) == false && s.at(i) != '.')
        {
            return false;
        }
    }

    return true;
}

// Uses a reges to remove all space from the given string
void Simple_Calculor::remove_Spaces(string &s)
{
    regex r("[ ]+");

    s = regex_replace(s, r, "");
}

// function to check if the value is binary

bool Simple_Calculor::StringBinary(string str)
{


    if (!str.empty() && str.back() == 'b') {
        str.pop_back();
    }



    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] != '1' && str[i] != '0')
            return false;
    }
    return true;
}

// function to convert Binary to decimal
int Simple_Calculor::BinToDec(int BinaryBits)
{
    int dec = 0, i = 0, rem;
    while (BinaryBits != 0)
    {
        rem = BinaryBits % 10;
        dec = dec + rem * pow(2, i);
        i++;
        BinaryBits = BinaryBits / 10;
    }
    return dec;
}



// Function to validate Hexadecimal input data
bool Simple_Calculor::validateHex_Input(string hex_Value)
{
    string chars = "0x";
    for (char c : chars)
    {
        hex_Value.erase(remove(hex_Value.begin(), hex_Value.end(), c), hex_Value.end());
    }

    bool result = false;
    int len = hex_Value.size();
    if (len < 1)
    {
        cout << "Empty input?\n";
        result = false;
    }
    else
    {
        result = true;
    }

    // now validate every symbol of the line
    for (int i = 0; i < len; i++)
    {
        // convert to uppercase for further operation with uppercase
        hex_Value[i] = toupper(hex_Value[i]);

        if (!(((floor(hex_Value[i]) == ceil(hex_Value[i]))      // check if is integer
               && (hex_Value[i] >= '0' && hex_Value[i] <= '9')) // if is integer, check value
              || ((isalpha(hex_Value[i]))                      // if is a latin letter
                  && (hex_Value[i] >= 'A' && hex_Value[i] <= 'F'))))
        {
            // check that it is A-F

            result = false;
            break;
        }
    }

    return result;
}

// Function to convert hexadecimal to decimal
int Simple_Calculor::hex_Dec(string hex_Value)
{

    int len = hex_Value.size();

    // Initializing base value to 1, i.e 16^0
    int base = 1;

    int dec_val = 0;

    // Extracting characters as digits from last character
    for (int i = len - 1; i >= 0; i--)
    {
        // if character lies in '0'-'9', converting it to integral 0-9 by subtracting 48 from ASCII value.
        if (hex_Value[i] >= '0' && hex_Value[i] <= '9')
        {
            dec_val += (hex_Value[i] - 48) * base;

            base = base * 16; // incrementing base by power
        }

        // if character lies in 'A'-'F' , converting it to integral 10 - 15 by subtracting 55 from ASCII value
        else if (hex_Value[i] >= 'A' && hex_Value[i] <= 'F')
        {
            dec_val += (hex_Value[i] - 55) * base;

            base = base * 16; // incrementing base by power
        }
    }

    return dec_val;
}

// A function to check if String has substring

bool Simple_Calculor::check_Substring(string s2, string s1)
{
    int counter = 0; // pointing s2
    int i = 0;
    for (; i < s1.length(); i++)
    {
        if (counter == s2.length())
            break;
        if (s2[counter] == s1[i])
        {
            counter++;
        }
        else
        {
            // Special case where character preceding the i'th character is duplicate
            if (counter > 0)
            {
                i -= counter;
            }
            counter = 0;
        }
    }
    return counter < s2.length() ? 0 : 1;
}

// A function to remove "b" and '0x' from input string
void Simple_Calculor::string_Filter(char *str)
{
    int n = strlen(str);

    int i = -1; // previous character
    int j = 0;  // current character

    while (j < n)
    {
        // check if current and next character forms ac
        if (j < n - 1 && str[j] == '0' && str[j + 1] == 'x')
            j += 2;

        // if current character is b
        else if (str[j] == 'b')
            j++;

        // if current char is 'c && last char in output is 'a' so delete both
        else if (i >= 0 && str[j] == 'x' && str[i] == '0')
            i--, j++;

        // else copy curr char to output string
        else
            str[++i] = str[j++];
    }
    str[++i] = '\0';
}
