#ifndef OSH_H
#define OSH_H 

#include <stdio.h>

namespace osh {

    template<typename T>
    T min(T a, T b);
    
    template<typename T>
    T max(T a, T b);

    template<typename P, typename T>
    concept PrintableTo = requires(P p, T t) {
        print1(p, t);
    };

    template<typename T>
    concept Formatter = requires(T t) {
        t.format("If it supports %s, it suppots %p!!1%d!elf", "printf", "printp", 1);
    };

    class FileFormatter {
        FILE* stream;

        public:
        FileFormatter(FILE* stream);

        template<typename... Args>
        void format(const char* fmt, Args&&...);
        void flush();
    };

    extern FileFormatter fout;
    extern FileFormatter ferr;

    template<typename P, PrintableTo<P>... Args>
    void printp(P& p, Args...);

    template<PrintableTo<Formatter>... Args>
    void print(Args...);
    template<PrintableTo<Formatter>... Args>
    void println(Args&&... args);

    void print1(Formatter auto&, const char*);
    void print1(Formatter auto&, char*);
    template<typename T> void print1(Formatter auto&, const T*);
    void print1(Formatter auto&, const char&);
    void print1(Formatter auto&, const int&);
    void print1(Formatter auto&, const short int&);
    void print1(Formatter auto&, const long int&);
    void print1(Formatter auto&, const long long int&);
    void print1(Formatter auto&, const unsigned char&);
    void print1(Formatter auto&, const unsigned int&);
    void print1(Formatter auto&, const unsigned short int&);
    void print1(Formatter auto&, const unsigned long int&);
    void print1(Formatter auto&, const unsigned long long int&);
    void print1(Formatter auto&, const float&);
    void print1(Formatter auto&, const double&);
    void print1(Formatter auto&, const long double&);

    template<typename T>
    void print1(FILE* stream, const T& t);

    template<PrintableTo<Formatter>... Args>
    [[noreturn]] void panic(Args&&... args);

    template<typename... Args>
    void assert(bool condition, Args&&... args);

    template<typename T>
    concept Destructible = requires(T t) {
        t.destruct();
    };

    template<Destructible T>
    struct AutoDestruct : public T {
        template<typename... Args>
        AutoDestruct(Args&&... args);

        ~AutoDestruct();
    };

    template<Destructible T>
    AutoDestruct<T> autoDestruct(T t);
    template<typename T>
    void swap(T& a, T& b);
}

#endif /* OSH_H */

#ifdef OSH_H_IMPLEMENTATION

#include <stdlib.h>

namespace osh {

    template<typename T>
    T min(T a, T b) {
        return a < b ? a : b;
    }

    template<typename T>
    T max(T a, T b) {
        return a > b ? a : b;
    }

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

    void print1(Formatter auto& fmt, const unsigned char& c) {
        printp(fmt, (char) c);
    }

    void print1(Formatter auto& fmt, const unsigned int& n) {
        fmt.format("%u", n);
    }

    void print1(Formatter auto& fmt, const unsigned short int& n) {
        fmt.format("%lu", n);
    }

    void print1(Formatter auto& fmt, const unsigned long int& n) {
        fmt.format("%lu", n);
    }

    void print1(Formatter auto& fmt, const unsigned long long int& n) {
        fmt.format("%llu", n);
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
    void printp(P& p, Args&&... args) {
        (print1(p, args), ...);
    }

    template<typename... Args>
    void print(Args&&... args) {
        printp(fout, args...);
    }

    template<typename... Args>
    void println(Args&&... args) {
        printp(fout, args..., '\n');
    }

    FileFormatter fout(stdout);
    FileFormatter ferr(stderr);

    FileFormatter::FileFormatter(FILE* stream)
        : stream(stream) {}

    template<typename... Args>
    void FileFormatter::format(const char* fmt, Args&&... args) {
        fprintf(stream, fmt, args...);
    }

    template<typename T>
    void print1(FILE* stream, const T& t) {
        FileFormatter fmt(stream);
        print1(fmt, t);
    }

    void FileFormatter::flush() {
       fflush(stream);
    }

    template<typename... Args>
    void panic(Args&&... args) {
        printp(ferr, args...);
        exit(1);
    }

    template<typename... Args>
    void assert(bool condition, Args&&... args) {
        if (!condition) {
            if (sizeof...(Args) > 0) {
                panic(args...);
            } else {
                panic("Assertion failed");
            }
        }
    }

    template<typename T>
    template<typename... Args>
    AutoDestruct<T>::AutoDestruct(Args&&... args) : T(args...) {}

    template<Destructible T>
    AutoDestruct<T>::~AutoDestruct() {
        this->destruct();
    }

    template<Destructible T>
    AutoDestruct<T> autoDestruct(T t) {
        return (AutoDestruct<T>) t;
    }
    template<typename T>
    void swap(T& a, T& b) {
        T t = a;
        a = b;
        b = t;
    }
}

#endif // OSH_H_IMPLEMENTATION
