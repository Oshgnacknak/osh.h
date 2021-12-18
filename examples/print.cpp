#define OSH_H_IMPLEMENTATION
#include "osh.h"

struct Vector2 {
    double x, y;
};

void print1(Vector2& v) {
    osh::print("Vector2(", v.x, ", ", v.y, ')');
}

int main() {

    osh::println("Concatinating different data types:",
        '-', 5, 6.0d, 9, '+', 'L');

    char c = 'A';
    osh::println("Printing char: ", c);

    int i = 69;
    osh::println("Printing int: ", i);
        
    short int si = 420;
    osh::println("Printing short int: ", si);
        
    long int li = 666;
    osh::println("Printing long int: ", li);
        
    long long int lli = 0xdeadbeef;
    osh::println("Printing long long int: ", lli);
        
    float f = 3.141592653589793;
    osh::println("Printing float: ", f);
        
    double d = 2.71828;
    osh::println("Printing double: ", d);

    long double ld = 1.141592653589793;
    osh::println("Printing long double: ", ld);

    osh::println("Printing a pointer to anythink (excluding char*): ",
        &i, ", ",
        &si, ", ",
        &li, ", ",
        &lli, ", ",
        &f, ", ",
        &d, ", ",
        &ld);

    char buf[32];
    buf[0] = 'b';
    buf[1] = 'u';
    buf[2] = 'f';
    buf[3] = 'f';
    buf[4] = 'e';
    buf[5] = 'r';
    buf[6] = '\0';
    osh::println("Printing char buffers: ", buf);

    Vector2 v = { 69, 420 };
    osh::println("Printing costume types (see print1 above): ", v);
    osh::println("^ Comment it out, error message is ACTUALLY readable");

    return 0; 
}
