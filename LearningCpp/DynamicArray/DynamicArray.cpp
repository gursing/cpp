#include <iostream>
using namespace std;
//#define LOGON

#ifdef LOGON
#define LOG std::cout << __PRETTY_FUNCTION__ << std::endl;
#else
#define LOG
#endif

template<typename T>
constexpr void test(T actual, T expected, std::string testName) {
    if (expected == actual) {
        std::cout << testName << " passed!!" << std::endl;
    }
    else {
        std::cout << testName << " failed!!" << std::endl;
        std::cout << "expected " << expected << " but was " << actual << std::endl;
    }
}

template<typename T>
class MyVector {
private:
    T* elems;
    size_t sz;
    size_t ptr = 0;
    const size_t gfactor = 2;
    void copy(const T* selems, T* delems, int size) {
        LOG
            for (int i = 0; i < size; ++i) delems[i] = selems[i];
    }
public:
    MyVector(size_t s) : elems{ new T[s] }, sz{ s }, ptr{ sz } {
        LOG
    }

    MyVector(const MyVector& v) : MyVector(v.sz) {
        LOG
            copy(v);
    }

    MyVector(MyVector&& v) {
        LOG
            sz = v.sz;
        elems = v.elems;
        ptr = sz;
        v.sz = 0;
        v.elems = nullptr;
    }

    MyVector(std::initializer_list<T> lst) : MyVector(lst.size()) {
        LOG
            std::copy(lst.begin(), lst.end(), elems);
    }

    MyVector& operator=(const MyVector& v) {
        LOG
            if (this == &v) return *this;
        delete[] elems;
        elems = new T[v.sz];
        sz = v.sz;
        ptr = sz;
        copy(v.elems, elems, sz);
        return *this;
    }

    MyVector& operator=(MyVector&& v) {
        LOG
            if (this == &v) return *this;
        delete[] elems;
        sz = v.sz;
        elems = v.elems;
        ptr = sz;

        v.sz = 0;
        v.elems = nullptr;
        return *this;
    }

    T& operator[](int idx) {
        LOG
            return elems[idx];
    }

    const T& operator[](int idx) const {
        LOG
            return elems[idx];
    }

    size_t size() const {
        LOG
            return ptr;
    }

    size_t capacity() const {
        LOG
            return sz;
    }

    void push_back(T elem) {
        LOG
            if (ptr == sz) {
                int newsz = gfactor * sz;
                auto newelems = new T[newsz];
                copy(elems, newelems, ptr);

                delete[] elems;
                sz = newsz;
                elems = newelems;
            }

        elems[ptr++] = elem;
    }

    ~MyVector() {
        LOG
            sz = 0;
        delete[] elems;
        elems = nullptr;
    }
};

MyVector<int> getClone() {
    return MyVector<int>{1, 2, 3};
}

int main() {
    MyVector<int> v{ 1,2,3,4,5 };
    test(v.size(), static_cast<size_t>(5), "v_size");
    test(v[0], 1, "v_access");
    test(v[1], 2, "v_access");
    test(v[2], 3, "v_access");
    test(v[3], 4, "v_access");
    test(v[4], 5, "v_access");

    MyVector<int> vclone(3);
    vclone[0] = 1, vclone[1] = 2, vclone[2] = 3;
    test(vclone.size(), static_cast<size_t>(3), "v_clone_size");
    test(vclone[0], 1, "v_clone_access");
    test(vclone[1], 2, "v_clone_access");
    test(vclone[2], 3, "v_clone_access");

    vclone = v;
    test(vclone.size(), static_cast<size_t>(5), "vclone_size");
    test(vclone[0], 1, "vclone_access");
    test(vclone[1], 2, "vclone_access");
    test(vclone[2], 3, "vclone_access");
    test(vclone[3], 4, "vclone_access");
    test(vclone[4], 5, "vclone_access");

    MyVector<int> vpushback = { 1,2,3 };
    test(vpushback.size(), static_cast<size_t>(3), "v_pushback_size");
    test(vpushback.capacity(), static_cast<size_t>(3), "v_pushback_capacity");
    test(vpushback[0], 1, "v_pushback_access");
    test(vpushback[1], 2, "v_pushback_access");
    test(vpushback[2], 3, "v_pushback_access");
    vpushback.push_back(4);
    test(vpushback.size(), static_cast<size_t>(4), "v_pushback_size");
    test(vpushback.capacity(), static_cast<size_t>(6), "v_pushback_capacity");
    vpushback.push_back(5);
    vpushback.push_back(6);
    test(vpushback.size(), static_cast<size_t>(6), "v_pushback_size");
    test(vpushback.capacity(), static_cast<size_t>(6), "v_pushback_capacity");
    test(vpushback[0], 1, "v_pushback_access");
    test(vpushback[1], 2, "v_pushback_access");
    test(vpushback[2], 3, "v_pushback_access");
    test(vpushback[3], 4, "v_pushback_access");
    test(vpushback[4], 5, "v_pushback_access");
    test(vpushback[5], 6, "v_pushback_access");
    vpushback.push_back(7);
    test(vpushback.size(), static_cast<size_t>(7), "v_pushback_size");
    test(vpushback.capacity(), static_cast<size_t>(12), "v_pushback_capacity");
    test(vpushback[0], 1, "v_pushback_access");
    test(vpushback[1], 2, "v_pushback_access");
    test(vpushback[2], 3, "v_pushback_access");
    test(vpushback[3], 4, "v_pushback_access");
    test(vpushback[4], 5, "v_pushback_access");
    test(vpushback[5], 6, "v_pushback_access");
    test(vpushback[6], 7, "v_pushback_access");

    MyVector<int> vmove = getClone();
    test(vmove.size(), static_cast<size_t>(3), "v_move_size");
    test(vmove[0], 1, "v_move_access");
    test(vmove[1], 2, "v_move_access");
    test(vmove[2], 3, "v_move_access");
}