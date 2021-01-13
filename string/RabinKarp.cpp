#include "stringpro.hpp"

int main() {
    auto set = LoadTestcase<string, string>(__FILE__);
    Run2(set, RabinKarp);
}