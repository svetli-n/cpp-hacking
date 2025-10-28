#ifndef SMART_PTR_H
#define SMART_PTR_H

#include <iostream>
#include <type_traits>
#include <utility>

namespace sp {

    template<class T, class Deleter = void(*)(T*)>
    class UniquePointer{

        public:
            UniquePointer() : obj(nullptr), deleter([](T* p){ delete p; }) {
                std::cout << "default constructor" << std::endl;
            }
            
            template<class... Args>
            UniquePointer(Args&&... args)
                : obj(new T(std::forward<Args>(args)...)), deleter([](T* p){ delete p; }) {
                std::cout << "constructor" << std::endl;
            }
            
            template<class D>
            UniquePointer(T* ptr, D&& del) : obj(ptr), deleter(std::forward<D>(del)) {
                std::cout << "constructor with deleter" << std::endl;
            }
            
            ~UniquePointer() {
                if(obj) {
                    deleter(obj);
                    std::cout << "destructor" << std::endl;
                }
            }
            
            UniquePointer(const UniquePointer& other) = delete;
            UniquePointer& operator=(const UniquePointer& other) = delete;
            
            UniquePointer(UniquePointer&& other) : obj(other.obj), deleter(std::move(other.deleter)) {
                other.obj = nullptr;
            }
            
            UniquePointer& operator=(UniquePointer&& other) {
                std::cout << "move assignment operator called" << std::endl;
                if(this != &other) {
                    if(obj) deleter(obj);
                    obj = other.obj;
                    deleter = std::move(other.deleter);
                    other.obj = nullptr;
                }
                return *this;
            }
            
            T& operator*(){
                return *obj;
            }
            T* operator->(){
                return obj;
            }
            
            T* get(){
                return obj;
            }

        private:
            T* obj;
            Deleter deleter;
    };

    template<class T, class... Args>
    auto make_unique(Args&&... args){
        return UniquePointer<T>(std::forward<Args>(args)...);
    };

    template<class T, class Deleter = void(*)(T*)>
    class SharedPointer{

        public:
            SharedPointer() : obj(nullptr), cnt(nullptr) {}
            
            template<class... Args>
            explicit SharedPointer(std::in_place_t, Args&&... args) : obj(new T(std::forward<Args>(args)...)), cnt(new int(1)) {
                std::cout << "shared constructed" << std::endl;
            }

            template<class D>
            SharedPointer(T* t, D&& del) : obj(t), cnt(new int(1)), deleter(std::forward<D>(del)) {
                std::cout << "shared constructed with deleter" << std::endl;
            }

            ~SharedPointer(){
                if(cnt) {
                    (*cnt)--;
                    if(*cnt<=0) {
                        deleter(obj);
                        delete cnt;
                        std::cout << "all shared destructed" << std::endl;
                    }
                    std::cout << "shared destructed" << std::endl;
                }
            }
            
            SharedPointer(const SharedPointer& t) : obj(t.obj), cnt(t.cnt), deleter(t.deleter) {
                if(cnt) (*cnt)++;
                std::cout << "shared copied" << std::endl;
            }
            
            SharedPointer(SharedPointer&& t) = delete;
            SharedPointer& operator=(const SharedPointer& t){
                if(this != &t) {
                    if(cnt && --(*cnt) == 0) {
                        deleter(obj);
                        delete cnt;
                    }
                    obj = t.obj;
                    cnt = t.cnt;
                    deleter = t.deleter;
                    if(cnt) (*cnt)++;
                }
                return *this;
            }
            SharedPointer& operator=(SharedPointer&& t) = delete;
            
            T& operator*(){
                return *obj;
            }
            
            T* operator->(){
                return obj;
            }

            int get_cnt(){
                return *cnt; 
            }

        private:
            T* obj;
            int* cnt;
            Deleter deleter = [](T* p){ delete p; };
    };

    template<class T, class... Args>
    auto make_shared(Args&&... args) {
        return SharedPointer<T>(std::in_place, std::forward<Args>(args)...);
    }

}

#endif // SMART_PTR_H

