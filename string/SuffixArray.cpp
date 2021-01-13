#include "stringpro.hpp"

int main() {
    auto data = LoadTestcase<string>(__FILE__);
    Run(data, SuffixArray);
}