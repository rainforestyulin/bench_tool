#include "simple_vector.h"

template <typename T>
std::allocator<T> SimpleVector<T>::alloc;
template <typename T>
void SimpleVector<T>::push_back(const T& a)
{
    check_n_alloc();
    alloc.construct(first_free++, a);
};
template <typename T>
void SimpleVector<T>::pop_back()
{
    auto remove_elem = first_free;
    remove_elem--;
    if(remove_elem)
    {
        alloc.destroy(remove_elem);
        first_free--;
    }
}
template <typename T>
std::pair<T*, T*> SimpleVector<T>::alloc_n_copy(const T* a, const T* b)
{
    auto data = alloc.allocate(b - a);
    return { data, uninitialized_copy(a, b, data) };
}
template <typename T>
void SimpleVector<T>::free()
{
    if (elements)
    {
        for (auto p = first_free; p != elements;)
        {
           alloc.destroy(--p);
        }
        alloc.deallocate(elements, cap - elements);
    }
}
template <typename T>
SimpleVector<T>::SimpleVector(const SimpleVector<T> &s)
{
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}
template <typename T>
SimpleVector<T>::~SimpleVector() { free(); }
template <typename T>
SimpleVector<T>& SimpleVector<T>:: operator = (const SimpleVector<T> &rhs)
{
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = data.second;
    return *this;
}
template <typename T>
void SimpleVector<T>::reallocate()
{
    auto newcapacity = size() ? 2 * size() : 1;
    auto newdata = alloc.allocate(newcapacity);
    auto dest = newdata;
    auto elem = elements;
    for (size_t i = 0; i < size(); ++i)
    {
        alloc.construct(dest++, std::move(*elem++));
    }
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}
