#ifndef OSH_H
#define OSH_H 

#define OSH_H_VERSION 2.0

#include <stdio.h>

namespace osh {

    template<typename R>
    concept Runnable = requires(R r) {
        r();
    };

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

    template<PrintableTo<FileFormatter>... Args>
    void eprint(Args&&...);
    template<PrintableTo<FileFormatter>... Args>
    void eprintln(Args&&...);

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

    template<Runnable R>
    struct Defer {
        R defered;

    public:
        Defer(R);
        ~Defer();
    };

    template<typename T>
    class DArray {
    protected:
        T* elements;
        size_t size_ = 0;
        size_t capacity;
    public:
        DArray(size_t = 10);
        void destruct();
        size_t size() const;
        void setSize(size_t);
        void growToCapacity(size_t);
        void ensureCapacity(size_t);
        void push(const T&);
        void clear();
        T& operator[](ssize_t);
    };

    class StringBuffer : public DArray<char> {
    public:
        StringBuffer(size_t = 10);
        StringBuffer(const char*);
        char* cstr() const;
        template<typename... Args> void format(const char* fmt, Args&&...);
        StringBuffer substr(ssize_t begin, ssize_t end) const;
        void setSize(size_t);
        char& operator[](int index);
    };

    void print1(Formatter auto&, const StringBuffer&);

    StringBuffer fileContentAsBuffer(const char* filename);

    int listIndex(int index, const int& size);

    template<typename T>
    void swap(T& a, T& b);

    template<typename T>
    T min(T a, T b);
    
    template<typename T>
    T max(T a, T b);
}

#endif /* OSH_H */

#ifdef OSH_H_IMPLEMENTATION

#include <stdlib.h>
#include <string.h>

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

    template<PrintableTo<FileFormatter>... Args>
    void eprint(Args&&... args) {
        printp(ferr, args...);
    }

    template<PrintableTo<FileFormatter>... Args>
    void eprintln(Args&&... args) {
        printp(ferr, args..., '\n');
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


    template<Runnable R>
    Defer<R>::Defer(R runnable)
        : defered(runnable) {}
    
    template<Runnable R>
    Defer<R>::~Defer() {
        defered();
    }

    template<typename T>
    DArray<T>::DArray(size_t capacity) : capacity(capacity) {
        elements = (T*) malloc(sizeof(T) * capacity);
    }

    template<typename T>
    void DArray<T>::destruct() {
        if (elements != nullptr) {
            free(elements);
        }
    }

    template<typename T>
    size_t DArray<T>::size() const {
        return size_;
    }

    template<typename T>
    void DArray<T>::setSize(size_t newSize) {
        growToCapacity(newSize);
        size_ = newSize;
    }

    template<typename T>
    void DArray<T>::growToCapacity(size_t newCapacity) {
        if (newCapacity > capacity) {
            capacity = max(capacity *= 2, newCapacity);
            elements = (T*) realloc(elements, sizeof(T) * capacity);
        }
    }

    template<typename T>
    void DArray<T>::ensureCapacity(size_t required) {
        growToCapacity(size_ + required);
    }

    template<typename T>
    void DArray<T>::push(const T& t) {
        ensureCapacity(1);
        elements[size_++] = t;
    }

    template<typename T>
    void DArray<T>::clear() {
        setSize(0);
    }

    template<typename T>
    T& DArray<T>::operator[](ssize_t index) {
        index = listIndex(index, size_);
        return elements[index];
    }

    StringBuffer::StringBuffer(size_t capacity) : DArray(capacity) {
        if (capacity > 0) {
            elements[0] = '\0';
        }
    }

    StringBuffer::StringBuffer(const char* initial) : DArray(strlen(initial)) {
        size_ = capacity;
        memcpy(this->elements, initial, size_);
    }

    char* StringBuffer::cstr() const {
        return elements;
    }

    StringBuffer StringBuffer::substr(ssize_t begin, ssize_t end) const {
        begin = listIndex(begin, size_);
        end = listIndex(end, size_);
        assert(begin <= end);

        size_t size = end - begin + 1;
        StringBuffer s(size);
        s.size_ = size;
        memcpy(s.elements, elements + begin, size);

        return s;
    }

    void StringBuffer::setSize(size_t newSize) {
        DArray::setSize(newSize);
        if (capacity > 0) {
            elements[size_] = '\0';
        }
    }

    template<typename... Args>
    void StringBuffer::format(const char* fmt, Args&&... args) {
        int required = 1 + snprintf(nullptr, 0, fmt, args...);
        ensureCapacity(required);
        snprintf(elements + size_, required, fmt, args...);
        size_ += required - 1;
    }

    void print1(Formatter auto& fmt, const StringBuffer& s) {
        printp(fmt, s.cstr());
    }

    StringBuffer fileContentAsBuffer(const char* filename) {
        FILE* f = fopen(filename, "r");
        assert(f != NULL);

        fseek(f, 0, SEEK_END);
        int capacity = ftell(f);
        StringBuffer s(capacity);
        
        rewind(f);
        int read = fread(s.cstr(), sizeof(char), capacity, f);
        assert(read == capacity);
        
        s.setSize(capacity);
        return s;
    }

    int listIndex(int index, const int& size) {
        assert(index >= -size && index < size,
            "Index", index, "out of bounce");

        if (index < 0) {
            index += size;
        }

        return index;
    }

    template<typename T>
    void swap(T& a, T& b) {
        T t = a;
        a = b;
        b = t;
    }

    template<typename T>
    T min(T a, T b) {
        return a < b ? a : b;
    }

    template<typename T>
    T max(T a, T b) {
        return a > b ? a : b;
    }
}

#endif // OSH_H_IMPLEMENTATION
