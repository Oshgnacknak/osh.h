#include "osh.h"

using namespace osh;

int main() {
    {
        StringBuffer a = "Hello";
        Defer destroyA([&] { a.destruct(); });

        println("AutoDestruct created: ", a);

        StringBuffer b = a;
        b.format(", World!");
        println("AutoDestruct shallow copied and used: ", b);
    }
    println("AutoDestruct destructed");

    return 0; 
}

#define OSH_H_IMPLEMENTATION
#include "osh.h"
