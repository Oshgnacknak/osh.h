#ifndef OSH_H
#define OSH_H 

#include <stdio.h>

namespace osh {

    template<typename P, typename T>
    concept PrintableTo = requires(P p, T t) {
        print1(p, t);
    };

    template<typename P, PrintableTo<P>... Args>
    void printp(P& p, Args...);

    template<PrintableTo<FILE*>... Args>
    void print(Args...);
    template<PrintableTo<FILE*>... Args>
    void println(Args... args);

    void print1(FILE*, const char*);
    void print1(FILE*, char*);
    template<typename T> void print1(FILE*, const T*);
    void print1(FILE*, const char&);
    void print1(FILE*, const int&);
    void print1(FILE*, const short int&);
    void print1(FILE*, const long int&);
    void print1(FILE*, const long long int&);
    void print1(FILE*, const float&);
    void print1(FILE*, const double&);
    void print1(FILE*, const long double&);

}

#endif /* OSH_H */

#ifdef OSH_H_IMPLEMENTATION

namespace osh {

    void print1(FILE* stream, const char* s) {
        fputs(s, stream);
    }

    void print1(FILE* stream, char* s) {
        fputs(s, stream);
    }

    template<typename T>
    void print1(FILE* stream, const T* p) {
        fprintf(stream, "%p", p);
    }

    void print1(FILE* stream, const char& c) {
        fputc(c, stream);
    }

    void print1(FILE* stream, const int& n) {
        fprintf(stream, "%d", n);
    }

    void print1(FILE* stream, const short int& n) {
        fprintf(stream, "%d", n);
    }

    void print1(FILE* stream, const long int& n) {
        fprintf(stream, "%ld", n);
    }

    void print1(FILE* stream, const long long int& n) {
        fprintf(stream, "%lld", n);
    }

    void print1(FILE* stream, const float& f) {
        fprintf(stream, "%f", f);
    }

    void print1(FILE* stream, const double& d) {
        fprintf(stream, "%f", d);
    }

    void print1(FILE* stream, const long double& d) {
        fprintf(stream, "%Lf", d);
    }

    template<typename P, typename... Args>
    void printp(P& p, Args... args) {
        (print1(p, args), ...);
    }

    template<typename... Args>
    void print(Args... args) {
        printp(stdout, args...);
    }

    template<typename... Args>
    void println(Args... args) {
        printp(stdout, args..., '\n');
    }

}

#endif // OSH_H_IMPLEMENTATION
