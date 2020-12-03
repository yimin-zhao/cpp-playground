#include <cstdio>
class Empty{
    Empty(){};
    virtual int print(){};
};

int main() {
    printf("%d\n", sizeof(Empty));
    return 0;
}
