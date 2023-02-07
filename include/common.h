#pragma once 
#include<vector>
#include<string>
#include<sstream>
using namespace std;



string reverseString(string st)
{
    string reverseString;
    for (string::reverse_iterator i = st.rbegin(); i != st.rend(); i++)
        reverseString += *i;
    return reverseString;
}
vector<std::string> split(std::string s, char delimeter)
{
    vector<std::string> tokens;

    stringstream sp(s.c_str());

    string intermediate;

    while (getline(sp, intermediate, delimeter))
    {
        tokens.push_back(intermediate);
    }
    return tokens;
}
std::string stripString(std::string str)
{
    string mainstring = str;
    while (1)
    {
        if (mainstring.at(0) == ' ')
        {
            mainstring.erase(mainstring.begin());
        }
        else
            break;
    }
    string s = reverseString(mainstring);
    while (1)
    {
        if (s.at(0) == ' ')
        {

            s.erase(s.begin());
        }
        else
            break;
    }

    return reverseString(s);
};