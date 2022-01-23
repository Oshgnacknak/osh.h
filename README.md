# osh.h

My personal stdc++ replacement

Because compared to
```cpp
#include <iostream>

using namespace std;

int main() {
   cout << "Hollow World!" << endl;

   return 0;
}
```
this is better
```cpp
#define OSH_H_IMPLEMENTATION
#include "osh.h"

using namespace osh;

int main() {
    println("Hello, World!");

   return 0;
}
```
