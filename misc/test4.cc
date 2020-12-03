#include <iostream>
#include <vector>
#include <queue>

using namespace std;
class KthLargest {
public:
    priority_queue<int, vector<int>, greater<int>()> que;
    int kth;
    KthLargest(int k, vector<int> nums): kth(k){
        for (int num : nums) {
            que.push(num);
            if (que.size() > k) que.pop();
        }
    }
    
    int add(int val) {
        que.push(val);
        if (que.size() > kth) que.pop();
        return que.top();
    }
};

int main(){
    return 0;
}