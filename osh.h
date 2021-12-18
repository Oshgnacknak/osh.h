#ifndef OSH_H
#define OSH_H 

namespace osh {

    template<typename T>
    concept IsPrintable = requires(T t) {
        print1(t);
    };

    template<IsPrintable... Args>
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
    void print1(const T* p) {
        printf("%p", p);
    }

    void print1(const char& c) {
        putchar(c);
    }

    void print1(const int& n) {
        printf("%d", n);
    }

    void print1(const short int& n) {
        printf("%d", n);
    }

    void print1(const long int& n) {
        printf("%ld", n);
    }

    void print1(const long long int& n) {
        printf("%lld", n);
    }

    void print1(const float& f) {
        printf("%f", f);
    }

    void print1(const double& d) {
        printf("%f", d);
    }

    void print1(const long double& d) {
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
