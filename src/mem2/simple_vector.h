#include <memory>
#include <stdlib.h>

template <typename T>
class SimpleVector {
public:
    SimpleVector ():
        elements(nullptr), first_free(nullptr), cap(nullptr) {}
    SimpleVector (const SimpleVector<T>&);
    SimpleVector& operator = (const SimpleVector<T>&);
    ~SimpleVector();
    void push_back(const T& a);
    void pop_back();
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return  cap - elements; }
    T *begin() const { return elements; }
    T *end() const { return first_free; }
private:
    static std::allocator<T> alloc;
    void check_n_alloc() { if (size() == capacity()) reallocate(); }
    std::pair<T*, T*> alloc_n_copy
        (const T*, const T*);
    void free();
    void reallocate();
    T *elements;
    T *first_free;
    T *cap;
};
