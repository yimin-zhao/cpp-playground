#include "../helper.h"

using namespace std;
class Solution {
public:
    vector<int> lexicalOrder(int n) {
        return {1, 2};
    }
};

int main(int argc, char *argv[]) {
    ifstream ifs(argv[1], ifstream::in);
    string str;
    Solution solver;
    while (getline(ifs, str)) {
        
        auto input = stoi(str);
        ppInteger(input);
        //auto input = stringToIntegerVector(str);
        //auto input = stringToListNode(str);
        auto res = solver.lexicalOrder(input);
        ppIntegerVector(res);
        //ppInteger(res);
    }
    
    return 0;
}

