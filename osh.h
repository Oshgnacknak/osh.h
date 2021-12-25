#ifndef OSH_H
#define OSH_H 

#include <stdio.h>

namespace osh {

    template<typename P, typename T>
    concept PrintableTo = requires(P p, T t) {
        print1(p, t);
    };

    template<typename T>
    concept Formatter = requires(T t) {
        t.format("%s: %d\n", "Namespace", 123);
    };

    class FileFormatter {
        FILE* stream;

        public:
        FileFormatter(FILE* stream);

        template<typename... Args>
        void format(const char* fmt, Args...);
    };

    extern FileFormatter fout;
    extern FileFormatter ferr;

    template<typename P, PrintableTo<P>... Args>
    void printp(P& p, Args...);

    template<PrintableTo<Formatter>... Args>
    void print(Args...);
    template<PrintableTo<Formatter>... Args>
    void println(Args... args);

    void print1(Formatter auto&, const char*);
    void print1(Formatter auto&, char*);
    template<typename T> void print1(Formatter auto&, const T*);
    void print1(Formatter auto&, const char&);
    void print1(Formatter auto&, const int&);
    void print1(Formatter auto&, const short int&);
    void print1(Formatter auto&, const long int&);
    void print1(Formatter auto&, const long long int&);
    void print1(Formatter auto&, const float&);
    void print1(Formatter auto&, const double&);
    void print1(Formatter auto&, const long double&);

    template<typename T>
    void print1(FILE* stream, const T& t);
}

#endif /* OSH_H */

#ifdef OSH_H_IMPLEMENTATION

namespace osh {

    void print1(Formatter auto& fmt, const char* s) {
        fmt.format("%s", s);
    }

    void print1(Formatter auto& fmt, char* s) {
        fmt.format("%s", s);
    }

    template<typename T>
    void print1(Formatter auto& fmt, const T* p) {
        fmt.format("%p", p);
    }

    void print1(Formatter auto& fmt, const char& c) {
        fmt.format("%c", c);
    }

    void print1(Formatter auto& fmt, const int& n) {
        fmt.format("%d", n);
    }

    void print1(Formatter auto& fmt, const short int& n) {
        fmt.format("%d", n);
    }

    void print1(Formatter auto& fmt, const long int& n) {
        fmt.format("%ld", n);
    }

    void print1(Formatter auto& fmt, const long long int& n) {
        fmt.format("%lld", n);
    }

    void print1(Formatter auto& fmt, const float& f) {
        fmt.format("%f", f);
    }

    void print1(Formatter auto& fmt, const double& d) {
        fmt.format("%f", d);
    }

    void print1(Formatter auto& fmt, const long double& d) {
        fmt.format("%Lf", d);
    }

    template<typename P, typename... Args>
    void printp(P& p, Args... args) {
        (print1(p, args), ...);
    }

    template<typename... Args>
    void print(Args... args) {
        printp(fout, args...);
    }

    template<typename... Args>
    void println(Args... args) {
        printp(fout, args..., '\n');
    }

    FileFormatter fout(stdout);
    FileFormatter ferr(stderr);

    FileFormatter::FileFormatter(FILE* stream)
        : stream(stream) {}

    template<typename... Args>
    void FileFormatter::format(const char* fmt, Args... args) {
        fprintf(stream, fmt, args...);
    }

    template<typename T>
    void print1(FILE* stream, const T& t) {
        FileFormatter fmt(stream);
        print1(fmt, t);
    }

}

#endif // OSH_H_IMPLEMENTATION
