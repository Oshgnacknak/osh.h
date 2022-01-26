#include "osh.h"

using namespace osh;

int main() {
    DArray<int> fib;

    fib.push(0);
    fib.push(1);

    for (int i = 0; i < 20; i++) {
        fib.push(fib[-1] + fib[-2]);
    }

    for (int i = 0; i < fib.size(); i++) {
        println(i, ": ", fib[i]);
    }

    return 0;
}

#define OSH_H_IMPLEMENTATION
#include "osh.h"
