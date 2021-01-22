#include <vector>

using time_t = unsigned int;

class OrderController {
public:
  struct OrderRequest {
    time_t reqTimestamp;
  };
private:
  time_t timeWindow, upperLimit;
  vector<time_t> vec;
  int vecHead
public:
  OrderController(time_t timeWindow, time_t upperLimit):
    timeWindow(timeWindow), upperLimit(upperLimit) {
      vecHead = 0;
      vec.assign(timeWindow, -1);
  };

  // OrderController 使用环形队列，队列长队为单位时间 N 运行的最大请求数量 M
  // 使用 vecHead 来记录当前的队列头部，而 (vecHead + 1) % M 则是队尾
  // 一开始队列为空，则顺序写入请求的时间戳，当队列满后，tail指向最旧的请求
  // 如果最早的请求时间已经早于设置的时间窗口，则直接覆盖，反之表示达到了最大
  // 请求上限后，时间不足 N，拒绝当前请求。
  // 时间复杂度为 O(1), 空间复杂度为 O(N)
  bool allow(const OrderRequest& order) {
    int current = order.reqTimestamp;
    int tail = (vecHead + 1) % upperLimit;
    if (vec[tail] == -1 || vec[tail] < current - timeWindow) {
      vec[tail] = current;
      return true;
    } else {
      return false;
    }
  }
};

