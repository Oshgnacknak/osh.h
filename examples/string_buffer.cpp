#include "osh.h"

using namespace osh;

int main() {
    StringBuffer sb = "Defining it, as if it was a const char*\n";

    printp(sb, "Printing some nice text, as if it goes to stdout: ", 1, 2, 3, '\n'); 

    sb.format("Some %dnice %s action going on\n", 1, "printf");
    println("This is quite nice: ", sb, "really really nice");

    StringBuffer sub = sb.substr(-10, -6);
    printp(sub, " - Yes, it support python like indices!\n");
    println(sub, "For more things, see `examples/darray.cpp`");

    return 0;
}

#define OSH_H_IMPLEMENTATION
#include "osh.h"
