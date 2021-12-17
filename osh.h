#ifndef OSH_H
#define OSH_H 

namespace osh {

    template<typename T>
    void print1(T& t);

    template<typename... Args>
    void print(Args... args);

    template<typename... Args>
    void println(Args... args);
}

#endif /* OSH_H */

#ifdef OSH_H_IMPLEMENTATION

#include <stdio.h>

namespace osh {

    void print1(const char* s) {
        fputs(s, stdout);
    }

    void print1(char* s) {
        fputs(s, stdout);
    }

    template<typename T>
    void print1(T* p) {
        printf("%p", p);
    }

    void print1(char& c) {
        putchar(c);
    }

    void print1(int& n) {
        printf("%d", n);
    }

    void print1(short int& n) {
        printf("%d", n);
    }

    void print1(long int& n) {
        printf("%ld", n);
    }

    void print1(long long int& n) {
        printf("%lld", n);
    }

    void print1(float& f) {
        printf("%f", f);
    }

    void print1(double& d) {
        printf("%f", d);
    }

    void print1(long double& d) {
        printf("%Lf", d);
    }

    void print() {}

    template<typename T, typename... Args>
    void print(T& t, Args... args) {
        print1(t);
        print(args...);
    }

    template<typename... Args>
    void println(Args... args) {
        print(args..., '\n');
    }
}

#endif // OSH_H_IMPLEMENTATION
