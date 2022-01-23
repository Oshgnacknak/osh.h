#ifndef OSH_H
#define OSH_H 

#include <stdio.h>

namespace osh {

    template<typename T>
    T min(T a, T b);
    
    template<typename T>
    T max(T a, T b);

    template<typename T, typename P>
    concept PrintableTo = requires(T t, P p) {
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
    void printp(P&, Args...);

    template<PrintableTo<FileFormatter>... Args>
    void print(Args&&...);
    template<PrintableTo<FileFormatter>... Args>
    void println(Args&&...);

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

    template<PrintableTo<FileFormatter>... Args>
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

    class StringBuffer {
        char* data;
        int _size = 0;
        int capacity;
    public:
        StringBuffer(int = 10);
        StringBuffer(const char*);
        void destruct();
        int size() const;
        char* cstr() const;
        template<typename... Args> void format(const char* fmt, Args&&...);
        void ensureCapacity(int);
        StringBuffer substr(const int& begin, const int& end) const;
        void clear();
        char& operator[](const int& index);
        StringBuffer& operator+=(const char&);
    };

    template<typename T>
    void checkIndex(const T& index, const T& size);

    void print1(Formatter auto&, const StringBuffer&);

    template<typename T>
    void swap(T& a, T& b);
}

#endif /* OSH_H */

#ifdef OSH_H_IMPLEMENTATION

#include <stdlib.h>
#include <string.h>

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
        fmt.format("%llu", n);
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

    template<typename P, PrintableTo<P>... Args>
    void printp(P& p, Args... args) {
        (print1(p, args), ...);
    }

    template<PrintableTo<FileFormatter>... Args>
    void print(Args&&... args) {
        printp(fout, args...);
    }

    template<PrintableTo<FileFormatter>... Args>
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

    void FileFormatter::flush() {
       fflush(stream);
    }

    template<PrintableTo<FileFormatter>... Args>
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

    StringBuffer::StringBuffer(int capacity) : capacity(capacity) {
        data = (char*) malloc(capacity);
        if (capacity > 0) {
            data[0] = '\0';
        }
    }

    StringBuffer::StringBuffer(const char* data) : StringBuffer(strlen(data)) {
        _size = capacity;
        memcpy(this->data, data, _size);
    }

    int StringBuffer::size() const {
        return _size;
    }

    char* StringBuffer::cstr() const {
        return data;
    }

    StringBuffer StringBuffer::substr(const int& begin, const int& end) const {
        checkIndex(begin, _size);
        checkIndex(end, _size);
        assert(begin < end);

        StringBuffer s(end - begin);
        memcpy(s.data, data, s._size);

        return s;
    }

    template<typename... Args>
    void StringBuffer::format(const char* fmt, Args&&... args) {
        int required = 1 + snprintf(nullptr, 0, fmt, args...);
        ensureCapacity(required);
        snprintf(data + _size, required, fmt, args...);
        _size += required;
    }

    void StringBuffer::ensureCapacity(int required) {
        capacity = max(capacity *= 2, _size + required);
        data = (char*) realloc(data, capacity);
    }

    void StringBuffer::clear() {
        _size = 0;
        if (capacity > 0) {
            data[_size] = '\0';
        }
    }

    void StringBuffer::destruct() {
        if (data != nullptr) {
            free(data);
        }
    }

    char& StringBuffer::operator[](const int& index) {
        checkIndex(index, capacity);
        return data[index];
    }

    StringBuffer& StringBuffer::operator+=(const char& c) {
        ensureCapacity(1);
        data[_size++] = c;
        data[_size] = '\0';
        return *this;
    }

    void print1(Formatter auto& fmt, const StringBuffer& s) {
        printp(fmt, s.cstr());
    }

    template<typename T>
    void checkIndex(const T& index, const T& size) {
        assert(index >= 0 && index < size,
            "Index", index, "out of bounce");
    }

    template<typename T>
    void swap(T& a, T& b) {
        T t = a;
        a = b;
        b = t;
    }
}

#endif // OSH_H_IMPLEMENTATION
