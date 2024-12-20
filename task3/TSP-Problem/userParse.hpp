#ifndef USERPARSE_HPP
#define USERPARSE_HPP
#include <string>
#include <vector>

class userParse {

public:
    int getCities();
    void setCities(int city);
    void loadArray();
    void fillStartArray();
    int findFactorial(int num);
    double findCost(std::string temp);
    double findCostTemp(int x, int y);
    std::vector<std::string> permute(int permsThisCall);
    std::string printS();

private:
    int city;
    double adArray[20][20]; // for matrix 20x20
    int s[20];
};


#endif //USERPARSE_HPP
