#include "osh.h"

using namespace osh;

int main() {
    StringBuffer sb = fileContentAsBuffer(__FILE__);
    Defer destruct_sb([&]() {
        sb.destruct();
    });

    printp(sb, "\n");
    printp(sb, "void foo() {\n");
    printp(sb, "    println(\"Hallo Welt\");\n");
    printp(sb, "}\n");

    println(sb);

    return 0; 
}

#define OSH_H_IMPLEMENTATION
#include "osh.h"
