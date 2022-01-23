#include "osh.h"

using namespace osh;

struct Vector2 {
    double x, y;
};

void print1(Formatter auto& fmt, Vector2& v) {
    printp(fmt, "Vector2(", v.x, ", ", v.y, ')');
}

int main() {
    println("Hallo, Welt");
    
    println("Concatinating different data types:",
        '-', 5, 6.0d, 9, '+', 'L');

    char c = 'A';
    println("Printing char: ", c);

    int i = 69;
    println("Printing int: ", i);
        
    short int si = 420;
    println("Printing short int: ", si);
        
    long int li = 666;
    println("Printing long int: ", li);
        
    long long int lli = 0xdeadbeef;
    println("Printing long long int: ", lli);

    unsigned char uc = 'E';
    println("Printing unsigned char: ", uc);
    
    unsigned int ui = 1337;
    println("Printing unsigned int: ", ui);
    
    unsigned short int usi = 25565;
    println("Printing unsigned short int: ", usi);
    
    unsigned long int uli = 0xadbdef;
    println("Printing unsigned long int: ", uli);
    
    unsigned long long int ulli = 987665543210;
    println("Printing unsigned long long int: ", ulli);
        
    float f = 3.141592653589793;
    println("Printing float: ", f);
        
    double d = 2.71828;
    println("Printing double: ", d);

    long double ld = 1.141592653589793;
    println("Printing long double: ", ld);

    println("Printing a pointer to anythink (excluding char*): ",
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
    println("Printing char buffers: ", buf);

    Vector2 v = { 69, 420 };
    println("Printing costume types (see print1 above): ", v);
    println("^ Comment it out, error message is ACTUALLY readable");

    printp(ferr, "Printing to stderr: ", "you error is soos ", d, f, '\n');

    FileFormatter fmt(stderr);
    printp(fmt, "Printing to any FILE* other than stdout: ", buf, " - ", v, '\n');

    return 0;
}

#define OSH_H_IMPLEMENTATION
#include "osh.h"
