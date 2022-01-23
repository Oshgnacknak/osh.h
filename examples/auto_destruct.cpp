#include "osh.h"

using namespace osh;

struct V1 {
    float x;

    V1(float x = 0) : x(x) {}

    V1 operator+(V1 that) {
        return {x + that.x};
    }

    void destruct() {
        println("V1 destructed: ", x);
    }
};

int main() {
    {
        StringBuffer a = "Hello";
        auto destroyA = autoDestruct(a);

        println("AutoDestruct created: ", a);

        StringBuffer b = a;
        b.format(", World!");
        println("AutoDestruct shallow copied and used: ", b);
    }
    println("AutoDestruct destructed");

    V1 v; // Not affected by the below
    {
        typedef AutoDestruct<V1> V1; // Enable AutoDestruct for the whole scope (c++'s default behavior)
        println("\nUsing AutoDestruct in arithmetic expressions:");
        V1 result = V1(10) + V1(20);
        println("Result: ", result.x);

        v = V1(2494) + result;
    }
    V1(50); // Not affected by the above

    println("v has the value: ", v.x);

    return 0; 
}

#define OSH_H_IMPLEMENTATION
#include "osh.h"
