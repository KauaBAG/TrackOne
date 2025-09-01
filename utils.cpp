#include "utils.hpp"
bool ABeginsWithB(std::string a, std::string b)
{
    if(a.size() < b.size()) return false;
    for(int i = 0; i < b.size(); i++) if(a[i]!=b[i]) return false;
    return true;
}