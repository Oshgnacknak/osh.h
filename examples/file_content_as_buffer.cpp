#include "osh.h"

using namespace osh;

int main() {
    StringBuffer sb = fileContentAsBuffer(__FILE__);
    auto destruct_sb = autoDestruct(sb);

    printp(sb, "\n");
    printp(sb, "void foo() {\n");
    printp(sb, "    println(\"Hallo Welt\");\n");
    printp(sb, "}\n");

    println(sb);

    return 0; 
}

#define OSH_H_IMPLEMENTATION
#include "osh.h"
