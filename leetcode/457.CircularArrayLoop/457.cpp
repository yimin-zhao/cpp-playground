#include "../helper.h"
using namespace std;
class Solution {
public:
    bool circularArrayLoop(vector<int>& nums) {
        if (nums.size() < 2) return false;

        for (size_t i = 0; i < nums.size(); ++i) {
            if (nums[i] < 0) continue;
            int cur = i, len = 0;
            while (cur < nums.size()) {
                len++;
                if (nums[cur] < 0) break;
                cur += nums[cur];
            }
            if (cur >= nums.size() 
                && (cur % nums.size()) == i
                && len > 1)
                return true;
        }
        return false;
    }
};

int main(int argc, char *argv[]) {
    ifstream ifs(argv[1], ifstream::in);
    string str;
    Solution solver;
    while (getline(ifs, str)) {
        //auto input = stoi(str);
        auto input = stringToIntegerVector(str);
        //auto input = stringToListNode(str);
        auto res = solver.circularArrayLoop(input);
        //ppIntegerVector(res);
        ppInteger(res);
        //ppLinkedList(res);
        //ppStringVector(res);
    }
    return 0;
}