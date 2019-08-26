#include <iostream>
#include <string>
using std::string;

int main()
{
    int i =1;
    string out = "候选词" + std::to_string(i);
    std::cout << out << std::endl;
    return 0;
}

