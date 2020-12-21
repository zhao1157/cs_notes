//======= 235 ======
#include <iostream>
#include <memory>

int main(){
    int * p = new int (2);
    {
        std::shared_ptr<int> sp (p);
        std::cout << *sp << std::endl;
        int *p1 = new int (9);
        sp.reset(p1);
        //std::cout << *p << std::endl; // p is freed by reset()
        std::cout << *sp << std::endl;
        *sp = 99;
        std::cout << *p1 << std::endl;
        std::cout << sp.get() << " " << p1 << std::endl;
    }

    std::shared_ptr<int> sp;
    std::cout << sp.unique() << std::endl;
    sp = std::make_shared<int>(3);
    std::cout << sp.unique() << std::endl;
    std::shared_ptr<int> spp = sp;
    std::cout << sp.unique() << spp.unique() << std::endl;
    spp.reset();
    std::cout << sp.unique() << spp.unique() << std::endl;
}


/*
//======= 234 =======
//This is to practice shared_ptr
#include <iostream>
#include <memory>

class P{
    private:
        int id;
    public:
        P(int _id = -1): id (_id){}
        ~P(){
            std::cout << id <<  " is destroyed\n";
        }
};

int main(){
    std::shared_ptr<int> p;
    std::cout << p.use_count() << std::endl;

    p = std::make_shared<int>();
    std::cout << p.use_count() << std::endl;
    
    {
        std::shared_ptr<int> p1 (p);
        std::cout << p.use_count() << " " << p1.use_count() << std::endl;
    }
    std::cout << p.use_count() << std::endl;

    std::cout << "________\n";
    std::shared_ptr<P> pp(new P[2]{P(7), P(9)}, std::default_delete<P[]>());
    //pp = std::make_shared<P>(9);
    std::cout << pp.use_count() << std::endl;
    std::shared_ptr<P> ppp = std::move(pp);
    std::cout << pp.use_count() << ppp.use_count() << std::endl;
}


//====== 233 ======
//This is to practice default_delete<>
#include <iostream>

int main(){
    int * ptr = new int (2);
    int * ptr_arr = new int [2] {9, 8};

    std::default_delete<int> del;
    std::default_delete<int[]> del_arr;
    del(ptr);

    del_arr(ptr_arr);
    //std::cout << ptr_arr[0] << std::endl;
}


//======= 232 =====
//This is to practice implementing unique_ptr
#include <iostream>

class Deleter{
    public:
        template<typename T>
        void operator ()(T *ptr){
            std::cout << ">>>>>>\n";
            delete ptr; 
            std::cout << "<<<<<\n";
        }
};

template<typename T, typename D = std::default_delete<T>>
class unique_ptr{
    private:
        T * ptr;
        D deleter;
    public:
        unique_ptr(T * _ptr): ptr(_ptr){
            deleter = D(); 
        }
        ~unique_ptr(){
            deleter(ptr);
        }
        unique_ptr(const unique_ptr &) = delete;

        T * get(){
            return ptr;
        }

        T * release(){
            T * _ptr = ptr;
            ptr = nullptr; // not deleting it yet, someone else should be responsible for it
            return _ptr;
        }
        
        void reset (T * _ptr = nullptr){
            deleter(ptr); // deleting the object
            ptr = _ptr;
        }    

        unique_ptr & operator = (unique_ptr && uptr){
            deleter(ptr);

            ptr = uptr.ptr;
            deleter = uptr.deleter;

            uptr.ptr = nullptr;

            return *this;
        }

        T * operator -> (){
            return ptr;
        }

        T & operator *(){
            return *ptr;
        }
};

class P{
    public:
        ~P(){
            std::cout << "destroyed\n";
        }
        void GET(){
            std::cout << "GET\n";
        }
};
int main(){
    std::default_delete<P> deleter = std::default_delete<P>();
    deleter(new P);
    std::cout << "_________\n";
    unique_ptr<P, std::default_delete<P>> uptr(new P), uptr2(new P);
    std::cout << "****\n";
    uptr2 = std::move(uptr);
    std::cout << "***\n";

    uptr2->GET();
    (*uptr2).GET();

    P *p = uptr2.release();
    delete p;

    std::cout << "_______\n";
    unique_ptr<P, Deleter> uuptr(new P);
}


//===== 231 ======
//This is to practice a[2], and a[2]=3
#include <iostream>

class SmartPointer{
    private:
        int * ptr;
    public:
        SmartPointer(int * arr): ptr(arr){}
        ~SmartPointer(){
            delete [] ptr;
        }

        int & operator[](int ind){
            return ptr[ind];
        }

        int & get(int ind) {
            return ptr[ind];
        }
};

int main(){
    SmartPointer sp(new int[2]{2,3});

    sp[1] = 9;

    sp.get(0) = 9;
    std::cout << sp[0] << sp[1] << std::endl;
}


//======= 230 =======
//This is to practice get_deleter() in unique_ptr, which gets the deleter class object
#include <iostream>
#include <memory>

class Deleter{
    private:
        int count;
    public:
        Deleter(int _count=0): count(_count){}
        template<typename T>
        void operator()(T * ptr){
            delete ptr;
            std::cout << "deleted " << ++count << std::endl;
        }
};

int main(){
    int *arr = new int [2] {-2, 3};
    Deleter()(arr);
    
    //std::unique_ptr<int, Deleter> uptr(new int (2), Deleter());

    Deleter del;
    std::cout << "___\n";
    del(new int);
    std::cout << "___\n";
    std::unique_ptr<int[], Deleter &> ptr(new int [2]{2,3}, del);

    std::cout << "****\n";
    ptr.get_deleter()(new int[2]);
    std::cout << "****\n";

    std::cout << "=====\n";
    ptr.reset();
    std::cout << "=====\n";
}


//======= 229 ======
//This is to practice class template functor in unique_ptr
#include <iostream>
#include <memory>

class P{
    public:
        template<typename T>
        void operator ()(T *a){
            delete a;
            std::cout << "deleted\n";
        }
};

int main(){
    int *a = new int(2);
    P p;
    //p(a);
    p.operator()<int>(a);
}


//======= 228 =======
//This is to practice move in template class
#include <iostream>

template<typename T>
class P{
    public:
        T a;
        P(T _a): a(_a){}
        //This one includes all other cases, but it requires T is the same for copy-from and copy-to objects
        //P(P & p){
        //    a = p.a;
        //}
        P(P<int> &p){
            a = static_cast<T> (p.a);
        }
        P(P<double> & p){
            a = static_cast<T> (p.a);
        }
};

int main(){
    P<double> p1(2.1415);
    P<int> p2(p1);
    std::cout << p1.a << " " << p2.a << std::endl;
}


//======= 227 =======
//This is to practice deleter in unique_ptr
#include <iostream>
#include <memory>

template<typename T>
class Del{
    public:
        Del() = default;
        ~Del(){
            std::cout << "del\n";
        }
        void operator()(T *ptr){
            delete ptr;
            std::cout << "deleted\n";
        }
};

int main(){
    //Del<double> d;
    Del<int> del;
    std::unique_ptr<int, Del<int>&> uptr(new int(2), del);
}


//====== 226 ======
//This is to practice reset() of unique_ptr
#include <iostream>
#include <memory>

int main(){
    std::unique_ptr<int> a(new int(3));
    std::cout << a.get() << std::endl;
    a.reset(); // first destroys the old pointer, then accetps the new pointer
    std::cout << a.get() << std::endl;

    std::unique_ptr<int> b (new int(9));
    a.reset(b.get()); // b returns the pointer, but not destroy it, a also manages the pointer
    b.release(); // free b from managing the pointer
    //b.reset();
}


//======= 225 ======
//This is to practice get() and release() of unique_ptr
#include <iostream>
#include <memory>

int main(){
    std::unique_ptr<int> a (new int(3));
    std::unique_ptr<int[]> aa (new int[2]{9, 8});

    int *pa;
    int *paa;

    pa = a.release();
    std::cout << *pa << std::endl;
    delete pa;

    paa = aa.release();
    std::cout << paa[0] << paa[1] << std::endl;
    delete[] paa;
}


//======= 224 =======
//This is to practice unique_ptr
#include <iostream>
#include <memory>

class P{
    public:
        ~P(){
            std::cout << "P is destroyed\n";
        }
};

int main(){
    std::unique_ptr<int> a;
    if (a.get()){
        std::cout << "not empty\n";
    } else {
        std::cout << "empty\n";
    }

    std::unique_ptr<int> b(new int);
    *(b.get()) = 3;
    std::cout << *b << std::endl;

    std::unique_ptr<int[]> c;
    c = std::unique_ptr<int[]>(new int[5]{2, 3, 4, 5, 6});
    std::cout << c[0] << c[1] << c[2] << c[3] << c[4] << std::endl;
    
    std::cout << c.get() << std::endl;
    std::unique_ptr<int[]> d = std::move(c);
    std::cout << "after being moved from: " << c << std::endl;
    std::cout << d.get() << std::endl;
    std::cout << d[0] << d[1] << d[2] << d[3] << d[4] << std::endl;

    std::unique_ptr<int> e (new int);
    *e = 33; // if e is not initialized, i.e. still holds nullptr, i.e. not allocating memory, so can not store object 
    std::cout << *e << std::endl;

    std::unique_ptr<int[]> f (std::move(d));
    std::cout << d.get() << " " << f.get() << std::endl;

    e = std::unique_ptr<int> (new int(9));
    std::cout << *e << std::endl;


    std::unique_ptr<P> pptr(new P);
    std::cout << "______\n";
    pptr = std::unique_ptr<P> (new P); // when new unique_ptr is assigned to pptr, the old object is released
    std::cout << "*******\n";
    std::unique_ptr<P> ppptr(new P);
    ppptr = std::move(pptr);
    std::cout << "_____\n";

}


//======= 223 =======
//This is to practice template function inside a class
#include <iostream>

class P{
    private:
        int id;
    public:
        P(int _id = -1): id(_id){}
        template<typename T>
        void test(T a){
            std::cout << a << id << std::endl;
        }
};

int main(){
    P p(2);
    p.test<int>(3); // also works without typename as template function can infer it from invoking
}


//====== 222 ======
//This is to practice implementing unique_ptr
#include <iostream>

template<typename T>
class Unique_Ptr{
    private:
        T *ptr = nullptr;
    public:
        Unique_Ptr(int id = 0): ptr(new T(id)){}
        ~Unique_Ptr(){
            delete ptr;
            std::cout << "ptr is deleted\n";
        }
        T & operator *(){
            return *ptr;
        }
};

class P{
    private:
        int id;
    public:
        P(int _id):id (_id){}
        ~P(){
            std::cout << "P is destroyed\n";
        }
};

int main(){
    Unique_Ptr<int> uptr(2);
    std::cout << *uptr << std::endl;

    Unique_Ptr<P> puptr;
}


//===== 221 =====
//This is to practice forward_list<>
#include <iostream>
#include <forward_list>

void traverse(std::forward_list<int> &flist){
    for (std::forward_list<int>::iterator iter = flist.begin(); iter != flist.end(); iter++) // can not use <, cause of incontiguous memory
        std::cout << *iter << " ";
    std::cout << "\n";
}

int main(){
    std::forward_list<int> flist;
    std::forward_list<int>::iterator flist_iter;
    flist.push_front(2);
    flist.push_front(3);
    flist_iter = flist.begin();
    flist_iter++; // can not --, as it is singly linked, only in forward direction, not backwards
    flist.emplace_after(flist_iter, 4); 
    flist_iter++;
    flist.insert_after(flist_iter, 5);
    flist.erase_after(flist_iter);
    
    traverse(flist);
}

//===== 220 =====
//This is to practice array container
#include <iostream>
#include <array>

int main(){
    std::array<int, 5> arr = {2,3,4};
    std::cout << arr.size() << std::endl;
    arr[0] = 2;
    std::cout << *(2+arr.data()) << std::endl;
    std::cout << "max_size " << arr.max_size() << " size " << arr.size() << std::endl;

    for (std::array<int, 5>::iterator iter = arr.begin(); iter < arr.end(); iter++)
        std::cout << *iter << " ";
    std::cout << "\n";

    std::cout << arr.front() << arr.back() << std::endl;
    arr.fill(2);
    for (auto & ele : arr)
        std::cout << ele << " ";
    std::cout << "\n";
}

//======= 219 ======
//This is to practice vector, which is a dynamic array by allocating more memory than its needs in exchange for expanding efficiency, allowing random access
#include <vector>
#include <iostream>

void traverse(std::vector<int> &vec){
    for (std::vector<int> ::iterator iter = vec.begin(); iter < vec.end(); iter ++)
        std::cout << *iter << " ";
    std::cout << "\n";
}

void pop_end(std::vector<int> & vec){
    std::cout << "before pop " << vec.capacity() << "\n"; // capcity() can be larger than the actual number of elements
    while(! vec.empty()){
        std::cout << vec.front() << vec.back() << " ";
        vec.pop_back();
    }
    std::cout << "after pop " << vec.capacity() << "\n";
}

int main(){
    std::vector<int> vec;

    vec.push_back(2);
    vec.push_back(23);
    vec.emplace_back(9);
    vec.emplace(vec.begin(), 10);

    traverse(vec);
    vec.erase(vec.begin()+1, vec.end()-1); // [)
    vec.erase(vec.end()-1);
    traverse(vec);
    vec.clear();
    std::cout << vec.size() << std::endl;
    
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(9);
    vec.push_back(9);
    vec.push_back(2);

    pop_end(vec);
    vec.reserve(200); // if this number is samller than the current capacity(), then nothing done
    std::cout << "reserve " << vec.capacity() << std::endl;
}


//======== 218 =======
//This is to practice queue, which opens at two ends, and one in one out, the two ends are the only places exposed to the outside, can not support iterator
#include <iostream>
#include <queue>
#include <stack> 

int main(){
    std::queue<int> que;

    que.emplace(2);
    que.push(3);
    que.push(23);

    //std::queue<int> ::iterator iter; // does not support iterators
    while (! que.empty()){
        std::cout << que.front() << que.back() << " " << que.size() << " ";
        que.pop();
    }
    std::cout << "\n";


    std::queue <int> que2, que3;
    que2.push(2);
    que.swap(que2);
    std::cout << que.size() << que2.size() << std::endl;

    que3.push(2);
    que3.pop();
    std::cout << que3.front(); // even though it is empty, it does not throw error

    std::stack<int> stak;
    stak.push(2);
    stak.pop();
    //std::cout << stak.top() << std::endl; // if the stack is empty, we can not call .top(), throw an error
}


//==== 217 =====
//This is to practice std::stack which only access its elements by top(), the underlying container could be vector, deque, list, not forward_list as which has no size() function
#include <iostream>
#include <stack>

int main(){
    std::stack<int> stak;
    stak.push(2);
    stak.push(3);
    stak.push(-1);

    std::cout << stak.top() << std::endl;
    //std::stack<int>::iterator iter; //does not support iterator
    //stak.begin();
    std::cout << stak.size() << std::endl;
    stak.emplace(23);

    while(! stak.empty()){
        std::cout << stak.top() << " ";
        stak.pop(); // pop the element in reverse order
    }
    std::cout << "\n";

    std::stack<int> b;
    b.push(999);
    std::cout << b.size() << std::endl;
    b.swap(stak);
    std::cout << stak.size() << " " << b.size() << std::endl;

    std::cout << stak.top() << " \n" ;//<< b.top() << "\n";
}


//====== 216 ======
//This is to test queue does not support indexing, iterator, we can only access it through .front() or .back(), not through iterator
#include <queue>
#include <iostream>

int main(){
    std::queue<int> que;
    que.push(2);
    que.push(3);
    //std::cout << que[0] << std::endl;
    std::cout << que.back() << que.front() << std::endl;
    //std::queue<int>::iterator iter; //does not support iterator
    while(!que.empty()){
        std::cout << que.front() << std::endl;
        que.pop();
    }
}


//======= 215 =====
//This is to practice list (constant time to insert/remove at any position, not support random accessing, so linear)
#include <list>
#include <iostream>

void traverse(std::list<int> & lt){
    //can not use < or >, use != or ==
    for (std::list<int>::iterator iter = lt.begin(); iter != lt.end(); iter++){
        std::cout << *iter << " ";
    }
    std::cout << "\n";
}

void pop_ends(std::list<int> & lt){
    int count = 0;
    while(!lt.empty()){
        count ++;
        if (count % 2 == 0){
            std::cout << lt.front();
            lt.pop_front();
        } else {
            std::cout << lt.back();
            lt.pop_back();
        }
    }
    std::cout << "\n";
}

int main(){
    std::list<int> lt;
    if (lt.begin() == lt.end()){
        std::cout << "empty\n";
    }
    std::list<int>::iterator iter;
    iter = lt.begin();
    lt.push_back(2);
    lt.push_front(3);
    lt.emplace_back(4);
    lt.emplace_front(5);
    //iter += 2; // no viable += operator
    iter ++;
    iter ++;
    lt.emplace(iter, 6);
    
    traverse(lt);

    pop_ends(lt);
    std::cout << "after popping, size of lt is " << lt.size() << std::endl;
}

//====== 214 =====
//This is to practice deque
#include <iostream>
#include <deque>

void fill_deq(std::deque<int> & deq){
    int val;
    do { 
        std::cin >> val; 
        if (val % 2 == 0){
            deq.push_back(val);
        } else{
            deq.push_front(val);
        }    
        // remove 0
        if (val == 0){
            deq.pop_back(); // for practice purpose
        }    
    } while(val);
}

void traverse(std::deque<int> & deq){
    for (std::deque<int>::iterator iter = deq.begin(); iter < deq.end(); iter ++)
        std::cout << *iter << " ";
    std::cout << "\n";
}

void rtraverse(std::deque<int> & deq){
    //for reverse iterator, use std::deque<int>::reverse_iterator
    for (std::deque<int>::reverse_iterator iter = deq.rbegin(); iter < deq.rend(); iter++){
        std::cout << *iter << " ";
    }
    std::cout << "\n";
}

void pop_both(std::deque<int> & deq){
    int count = 0;
    while(!deq.empty()){
        count ++;
        if (count % 2 == 0){
            std::cout << deq.back() << " ";
            deq.pop_back();
        } else{
            std::cout << deq.front() << " ";
            deq.pop_front();
        }
    }
    std::cout << "\n";
}

int main(){
    std::deque<int> deq;
    std::cout << "max number of elements can be held " << deq.max_size() << "\n";
    std::cout << "filing ...\n";
    fill_deq(deq);
    traverse(deq);
    rtraverse(deq);
    std::cout << "size of deque: " << deq.size() << std::endl;
    pop_both(deq);

    deq.resize(8, 100); // number of elements to resize to, value to fill if to expand
    traverse(deq);
    deq.resize(2); // remove and destroy the elements beyond the limit
    traverse(deq);
    deq.resize(5); // if not specified, use the default value for that type
    traverse(deq);
    std::cout << "current size " << deq.size() << std::endl;
    deq.shrink_to_fit(); // only allocate the memory size to the current number of elements
    int i = 0;
    for (std::deque<int>::reverse_iterator iter = deq.rbegin(); iter < deq.rend(); iter ++)
        //std::cout << *iter << " ";
        std::cout << deq[i++] << " ";

    std::cout << "\n";
    deq.push_back(99);
    deq.erase(deq.end()-2, deq.end()-1); // does not support reverse_iterator
    traverse(deq);

    deq.clear();
    std::cout << "size after clear " << deq.size() << std::endl;
    if (deq.begin() == deq.end()){
        std::cout << "empty\n";
    }
    deq.push_back(2);
    deq.emplace(deq.end(), 9); // it is equivalent to emplace_back(9);
    deq.emplace_back(99);
    deq.emplace_front(20);
    traverse(deq);
    
    std::cout << deq[2] << " " << deq.at(2) << std::endl;
    std::cout << deq[4] << std::endl;
    std::cout << deq.at(4) << std::endl;
}


//======= 213 =======
//This is to practice queue
#include <iostream>
#include <queue>
#include <stdlib.h>
#include <time.h>

int main(){
    std::queue <int> que;
    for (int i = 0; i < 5; i++){
        que.emplace(i);
    }
    std::cout << que.size() << std::endl;
    for (int i = 0; i < 5; i++){
        std::cout << que.front();
        que.pop();
    }
    std::cout << "\n";
    std::cout << que.size() << std::endl;
    
    srand(time(NULL));
    for (int i = 0; i < 9; i++)
        que.push(rand()%10);
    std::cout << que.size() << que.empty() << std::endl;
    while(!que.empty()){
        std::cout << que.front() << que.back() << " ";
        que.pop();
    }
    std::cout << std::endl;
}

//====== 212 =====
//This is to practice lvalue reference and rvalue reference
#include <iostream>

void f1(int && a){
    std::cout << "rvalue ref\n";
}
void f1(int & a){
    std::cout << "lvalue ref\n";
}

int main(){
    int a = 2;
    int & b = a;
    std::cout << &a << " " << & b << std::endl;
    if (&a != &b)
        throw("a and b are not aliase");

    const int & c = 3; // under the hood a temporary variable of value 3 is created, and the reference is bound this variable
    std::cout << c << std::endl;

    double && d = 3.14; // accepts a rvalue
    d -= 1;
    std::cout << d << std::endl;
    d = a;

    double && e = a;
    std::cout << e << std::endl;

    f1(d);
    f1(a);
    f1(a);
    f1(b);
    f1(e);
    f1(20);
    f1(std::move(a));
}

//======= 211 ======
//This is to practice thread pool
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <functional>
#include <atomic>
#include <chrono>

std::condition_variable cv_task;
std::mutex mu_task;

//since Threads are not copy-able, we make this class as a singleton
class ThreadPool{
    private:
        std::vector<std::thread> all_threads;
        std::queue<std::function<void()>> all_tasks;

        std::atomic<bool> stop;
        bool new_task;
        std::atomic<int> num_done;

        ThreadPool(int num = std::thread::hardware_concurrency() -1) {
            stop = false;
            new_task = false;
            num_done = 0;

            if (num > std::thread::hardware_concurrency() - 1){
                num = std::thread::hardware_concurrency() - 1;
            } 
            for (int i = 0; i < num; i++){
                all_threads.emplace_back(std::thread(&ThreadPool::thread_loop, this));        
            }
        }

        ~ThreadPool(){
            std::cout << "destroying\n";
            if (stop){
                std::cout << "stopping threads\n";
                for (auto & thread : all_threads){
                    if (thread.joinable())
                        thread.join();
                }
            }
        }
    public:
        ThreadPool(const ThreadPool & )=delete;
        ThreadPool & operator = (const ThreadPool &) = delete;
        static ThreadPool & GetThreadPool(){
            static ThreadPool threadpool;
            return threadpool;
        }
        void thread_loop(){
            int i = 1;
            std::function<void()> task;
            while(true){
                {
                    std::unique_lock<std::mutex> lock(mu_task);
                    cv_task.wait(lock, [this]{return new_task;});
                    task = std::move(all_tasks.front());
                    all_tasks.pop();
                }
                //runing this task
                task();
                i ++;
                std::cout << "____\n";
                num_done ++;
                if (num_done == 3 or i == 2)
                    break;
            }
            stop = (num_done == 3) ? true : false;
        }
        void add_task(std::function<void()> tsk){
            std::unique_lock<std::mutex> lock(mu_task);
            all_tasks.push(tsk);
            new_task = true;
            cv_task.notify_one();
        }
};

void work(){
    std::cout << "*\n";
}

int main(){
    for (int i = 0; i < 3; i++){
        ThreadPool::GetThreadPool().add_task(work);
    }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}


//====== 210 ======
//This is to practice std::accumulate(iter_start, iter_end, init_val)
#include <iostream>
#include <numeric> //std::accumulate
#include <vector>

double f1(double init, double ele){
    return ele - init;
}


int main(){
    // array
    double arr [] = {2, 3, 9, -1};
    std::cout << "array: " << std::accumulate(arr, arr+4, 10) << std::endl;
    std::cout << "array: " << std::accumulate(arr, arr+4, 10, f1) << std::endl; // the result of the last round goes to the first argument, and each element goes to the second position

    std::cout << "_____________\n";
    std::vector<double> vecs {2, -2, 9, 8};
    std::cout << "vector: " << std::accumulate(vecs.begin(), vecs.end()-1, 10) << std::endl;
    std::cout << "vector: " << std::accumulate(vecs.begin(), vecs.end(), 10, f1) << std::endl;
}


//===== 200 =====
//This is to practice noexcept specifier or operator
#include <iostream>

void f1(int i){
    throw(3);
}

void f2() noexcept{
}

void f3() noexcept(false){

}

void f4() noexcept(!noexcept(f1(33))){ // since declare as noexcept(true), if exception is not handled within the function, it will not be passed out, so we have to deal with this exception within
    try{
    f1(33);
    } catch(int i){
        std::cout << "caught within\n";
    }
}

void f5() noexcept(noexcept(f1(2))){ // since noexcept false, it can throw exception, thus we can handle the exception outside
    f1(33);
}

int main(){
    std::cout << "f1 noexcept: " << static_cast<bool>(noexcept(f1(2))) << std::endl;
    std::cout << "f2 noexcept: " << static_cast<bool> (noexcept(f2())) << std::endl;
    std::cout << "f3 noexcept: " << static_cast<bool> (noexcept(f3())) << std::endl;
    std::cout << "f4 noexcept: " << static_cast<bool> (noexcept(f4())) << std::endl;
    std::cout << "f5 noexcept: " << static_cast<bool> (noexcept(f5())) << std::endl; 

    f4();

    try{
        f5();
    } catch(int i){
        std::cout << "caught outside\n";
    }
}

//======= 199 ======
//This is to compare the performance of copying and moving 
#include <iostream>
#include <chrono>

class Timer{
    private:
        std::chrono::high_resolution_clock::time_point start, end;
    public:
        void Start(){
            start = std::chrono::high_resolution_clock::now();
        }
        void Time(){
            end = std::chrono::high_resolution_clock::now();
            std::cout << "Time taken is " << std::chrono::duration_cast<std::chrono::milliseconds> (end-start).count() << std::endl;
        }
};

template<typename T>
class DynamicArray{
    private:
        T *arr;
        int length;
    public:
        DynamicArray(int _len): arr(new T[_len]), length(_len){}
        ~DynamicArray(){
            delete [] arr;
        }
        T & operator[] (int ind){
            return arr[ind];
        }

        DynamicArray & operator = (DynamicArray & darr){
            if (this != & darr){
                delete [] arr;
                arr = new T[length];
                for (int i = 0; i < length; i++){
                    arr[i] = darr[i];
                }
            }
            return *this;
        }

        DynamicArray & operator = (DynamicArray && darr){
            if (this != &darr){
                delete [] arr;
                arr = darr.arr;
                length = darr.length;
                darr.arr = nullptr;
                darr.length = 0;
            }
            return *this;
        }
};

int main(){
    int size = 10000000;
    DynamicArray<double> arr(size);
    for (int i = 0; i < size; i++){
        arr[i] = i;
    }
    DynamicArray<double> arr_copy(size);

    Timer time;
    time.Start();
    arr_copy = arr;
    time.Time();

    DynamicArray<double> arr_move(size);
    time.Start();
    arr_move = std::move(arr);
    time.Time();
}

//======= 198 ======
//This is to practice copy/move constructor/assignment
#include <iostream>

class P{
    private:
        double *arr;
    public:
        P(): arr(new double(-3.14)){std::cout << "constructor\n";}
        ~P(){
            delete arr;
        }
        
        //======== copy constructor/assignment =======
        P(const P & p): arr(new double){
            std::cout << "copy constructor\n";
            * arr = * p.arr;
        }

        P & operator = (const P & p){
            std::cout << "copy assignment\n";
            if (this != &p){
                delete arr;
                arr = new double;
                * arr = * p.arr;
            }
            return * this;
        }
        //======= move constructor/assignment =======
        P (P && p) {
            std::cout << "move constructor\n";
            arr = p.arr;
            p.arr = nullptr;
        }
        P & operator = (P && p){
            std::cout << "move assignment\n";
            if (this != &p){
                delete arr;
                arr = p.arr;
                p.arr = nullptr;
            }
            return * this;
        }
};

int main(){
    P p1;
    P p2 = p1;

    p2 = p1;

    P p3 = std::move(p1);
    p3 = static_cast<P &&>(p2);
}


//====== 197 =====
//This is to practice move constructor and assignment 
#include <iostream>

class P{
    private:
        int id;
    public:
        P(int _id=-1): id(_id){}

        P(const P && p): id(std::move(p.id)){
            std::cout << "constructor: move\n"; 
        }
        P & operator = (const P && p){
            std::cout << "assignment: move\n";
            if (this != &p)
                id = std::move(p.id);
            return *this;
        }
        void Get(){
            std::cout << "id: " << id << ", " << & id << std::endl;
        }
};

int main(){
    {
        P p1(2);
        P p(std::move(p1));
        P p2 = std::move(p1);
    }
    P p1(3);
    {
        P p2;
        //p2 = std::move(p1);
        p2 = static_cast<P&&> (p1);
        //p2 = p1;
        p2.Get();
    }

    p1.Get();

    {
        int a = 2;
        int b = std::move(a);
        std::cout << &a << ", " << &b << std::endl;
    }
}


//====== 196 =====
//This is to test virtual and dynamic_cast
#include <iostream>

class B{
    public:
        virtual ~B(){
            std::cout << "B is destroyed\n";
        }
};

class D: public B{
    public:
        ~D(){
            std::cout << "D is destroyed\n";
        }
};

int main(){
    B * ptr;

    ptr = dynamic_cast<B*> (new D);

    if (ptr){
        std::cout << "dynamic_cast succeeded\n";
    } else{
        std::cout << "dynamic_cast failed\n";
    }

    delete ptr;
    std::cout << "_____\n";
    D *p = new D;
    delete p;
}

//======== 195 ==========
//This is to test passing arguments to packaged_task
#include <iostream>
#include <future>
#include <functional>

int work(double a){
    std::cout << a << std::endl;
    return static_cast<int> (2*a);
}

void test(int a, double b, std::string c){
    std::cout << a << ", " << b << ", " << c << std::endl;
}

int main(){
    std::packaged_task<int(double)> task(work);
    task(3.14);

    std::future<int> fu = task.get_future();
    std::cout << fu.get() << std::endl;
    
    std::packaged_task<void(double, int)> t1 (std::bind(test, std::placeholders::_2, std::placeholders::_1, "zls"));

    t1(3.9, 23);
   
}


//========= 194 ============
//This is to test the scope a class object
#include <iostream>
#include <functional>

class P{
    public:
        ~P(){
            std::cout << "P is destroyed\n";
        }
};

void test(P &p, int i){
}

int main(){
    P p;
    int i = 2;

    //test(std::move(p), std::move(i));
    test(std::ref(p), i);

    std::cout << "after test\n";
    std::cout << i << std::endl;
}


//========= 193 ==========
//This is to practice std::bind
#include <iostream>
#include <functional>

void work(int a, double b, std::string c){
    std::cout << a << ", " << b << ", " << c << std::endl;
}

int main(){
    int a = 2;
    double b = 3.14;
    std::string c = "zls";

    std::function<void()> f1 = std::bind(work, a, b, c);
    f1();

    std::function<void(double, int)> f2 = std::bind(work, std::placeholders::_2, std::placeholders::_1, c);
    f2(b, 2*a);
}


//=========== 192 ==========
//This is to practice packaged_task<return_type(arg_tyep1, arg_type2, ...)>
#include <iostream>
#include <future>
#include <functional> // for std::function, std::bind

void work(){
    std::cout << "In task\n";
}

int main(){
    std::packaged_task<void()> task(work);

    std::function<void()> f = std::bind(work);
    std::cout << " std::bind(), std::function<void()> \n";
    f();
    std::cout << " std::packaged_task<void()>\n";
    task();
}

//======= 191 ======
//This is to practice std::move
#include <iostream>
#include <deque>

int main(){
    int a [2] = {2, 3};
    int b = std::move(a[1]);

    std::cout << a[1] << std::endl;

    std::deque<int> deq;
    deq.push_back(2);
    deq.push_back(9);
    deq.push_back(22);

    b = std::move(deq.front());
    deq.pop_front();
    for(auto & ele : deq) 
        std::cout << ele << " ";
    std::cout << "\n";
}

//======= 190 ======
//This is to practice shared_future<void> to synchronize without a state
#include <iostream>
#include <mutex>
#include <thread>
#include <future>
#include <chrono>
#include <vector>

void Work(std::shared_future<void> sfu, std::mutex & mu){
    std::lock_guard<std::mutex> lock(mu);
    sfu.wait();
    std::cout << "\t" << std::this_thread::get_id() << " done waiting\n";
}

int main(){
    std::mutex mu;
    std::promise<void> prom;
    std::shared_future<void> sfu = prom.get_future();
    
    int num = std::thread::hardware_concurrency() - 1;

    std::vector<std::thread> my_threads;
    for (int i = 0; i < num; i++)
        my_threads.emplace_back(std::thread(Work, sfu, std::ref(mu)));
    
    std::cout << "sending signal\n"; 
    prom.set_value();
    
    for (auto & thread : my_threads)
        thread.join();
}


//====== 189 =======
//This is to practice std::shared_future<type> sf = std::future<type> fu.share()
#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <vector>

std::mutex mu;

void Work(std::shared_future<int> sfu){
    std::lock_guard<std::mutex> lock(mu);
    std::cout << std::this_thread::get_id() << ": " << sfu.get() << std::endl;
}

int main(){
    int num = std::thread::hardware_concurrency();

    std::vector<std::future<void>> thd;

    std::promise<int> prom;
    std::future<int> fu = prom.get_future();
    std::shared_future<int> sfu = fu.share();

    for (int i = 0; i < num - 1; i++)
        thd.emplace_back(std::async(Work, sfu));

    prom.set_value(4);
}


//======= 188 =======
//This is to practice passing values to threads using std::promise and std::future
#include <iostream>
#include <thread>
#include <future>
#include <stdlib.h>
#include <time.h>
#include <chrono>

std::chrono::nanoseconds sl(1);

void Work(std::future<int> &fu){
    std::cout << "waiting ...\n";
    int a = fu.get();
    std::cout << "done waiting\n";

    std::cout << a << std::endl;
    //fu.get(); // only get() once
}

int main(){
    std::promise <int> prom;
    std::future <int> fu = prom.get_future();
    
    // we need to assign std::async to a variable, otherwise hang 
    std::future<void> ret = std::async(std::launch::async, Work, std::ref(fu));
    
    std::this_thread::sleep_for(sl);
    prom.set_value(2);

}


//======= 187 ======
//This is to practice one thread sending info while others receiving it
#include <iostream>
#include <thread>
#include <future>
#include <stdlib.h>
#include <mutex>
#include <time.h>

struct P{
    std::string name;
    int age;
    P (std::string _name="xx", int _age=-9): name(_name), age(_age){}
};

std::mutex mu;

void Work(int id, std::promise<void> &prom, std::future<void> & fu){
    static P p;
    if (id == 0){
        srand(time(NULL));
        p = P("zls", rand()%70+30);
        prom.set_value();
        {
            std::lock_guard<std::mutex> lock(mu);
            std::cout << "The correct info is " << p.name << ": " << p.age << std::endl;
        }
    } else{
        fu.wait();
        {
            std::lock_guard<std::mutex> lock(mu);
            std::cout << p.name << ": " << p.age << std::endl;
        }
    }
}


int main(){
    std::promise <void> prom;
    std::future <void> fu = prom.get_future();
    
    int num = std::thread::hardware_concurrency();

    std::thread all_threads[num];

    for (int i = 0; i < num; i++) all_threads[i] = std::thread(Work, i, std::ref(prom), std::ref(fu));

    for (int i = 0; i < num; i++) all_threads[i].join();

}

//====== 186 =====
//This is to practice std::promise and std::future pair, which provides another way of communicating among threads
#include <iostream>
#include <thread>
#include <future>
#include <chrono>

std::chrono::seconds sl(1);

void Work(std::promise<int*> prom){ // don't use reference as we move the object here
    int a = 2;
    std::this_thread::sleep_for(sl);
    static int arr[2] = {a, a+a}; // make arr global or static, otherwise setmentation fault
    //prom.set_value(new int [2] {a, a+1});
    prom.set_value(arr);
}

int main(){
    std::promise<int *> prom;
    std::future <int *> fu = prom.get_future();

    std::thread my_thread = std::thread(Work, std::move(prom));
    
    std::cout << "waiting for arr\n";
    int *arr = fu.get();
    std::cout << "got arr\n";
    std::cout << arr[0] << " " << arr[1] << std::endl;
    my_thread.join();
}

//====== 185 ======
//This is to practice std::async(std::launch::async, func, arg), which is spawned in a different thread
#include <iostream>
#include <thread>
#include <future>
#include <chrono>

std::chrono::seconds sl(1);

int Work(){
    std::cout << std::this_thread::get_id() << " 23\n";
    std::this_thread::sleep_for(sl);
    return 23;
}

int main(){
    std::future<int> res = std::async(std::launch::async, Work);
    std::cout << "waiting for res\n";
    int i = res.get();
    std::cout << std::this_thread::get_id() << " main " << i << "\n";
}


//======= 184 =======
//This is to practice std::async
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <future> //std::async

std::chrono::seconds sl(1);
void Work(){
    std::this_thread::sleep_for(sl);
    std::cout << std::this_thread::get_id() << " done sleeping\n";
}

int main(){
    //std::launch::deferred -> in the same thread, not spawned in another thread
    std::future<void> sync = std::async(std::launch::deferred, Work);
    std::cout << std::this_thread::get_id() << " main\n";
    sync.wait(); // blocks until the result becomes available
}


//====== 183 =====
//This is to verify the assignment operator overloading working for static?
#include <iostream>

class P{
    public:
        static void operator () (){ //operato () overloading does not work for static methods
            std::cout << "static () operator overloading\n";
        }
};

int main(){
    P p;
}


//===== 182 =====
//how to make sure all threads are ready?
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

class Prize{
    private: 
        static int id;
        Prize(int _id = -1){
            id = _id;
        }
    public:
        Prize(const Prize &) = delete;
        Prize & operator = (const Prize &) = delete;
        static Prize & GetPrize(int _id){
            static Prize p(_id);
            std::cout << "Attending " << _id << std::endl;
            return p;
        }

        static void GetWinner(){
            std::cout << "The winner is " << id << std::endl;
        }
};

int Prize::id;

int ready = 0, go = 0, done = 0;
std::mutex mu, mu_work, mu_done;
std::condition_variable cv, cv_work, cv_done;

void Work(int id){
    {
        std::unique_lock<std::mutex> lock(mu);
        ready ++;
    }
    cv.notify_one();

    {
        std::unique_lock<std::mutex> lock(mu_work);
        cv_work.wait(lock, [] {return go == 1;});
        Prize::GetPrize(id);
    }

    {
        std::unique_lock<std::mutex> lock(mu_done);
        done ++;
        cv_done.notify_one();
    }

}

int main(){
    std::vector<std::thread> my_threads;
    for (int i = 0; i < 5; i++) my_threads.emplace_back(Work, i); 

    {
        std::unique_lock<std::mutex> lock(mu);
        cv.wait(lock, []{std::cout << "checking\n"; return ready == 5;});
        std::cout << "ready\n";
    }

    { 
        std::unique_lock<std::mutex> lock(mu_work);
        go = 1;
        cv_work.notify_all();
        std::cout << "go\n";
    }

    {
        std::unique_lock<std::mutex> lock(mu_done);
        cv_done.wait(lock, []{return done == 5;});
        std::cout << "Time to find out the winner\n";
    }
    Prize::GetWinner();

    for (auto & thread : my_threads) thread.join();
}



//====== 181 ======
//This is to enhance my understanding of cv.wait
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex mu;
std::condition_variable cv;

std::chrono::milliseconds sl(100);

void SendSignal(){
    std::this_thread::sleep_for(sl);
    std::lock_guard<std::mutex> lock(mu);
    std::cout << "defer signal\n";
    std::this_thread::sleep_for(sl*10);
    std::cout << "signal\n";
    cv.notify_all();    
    std::this_thread::sleep_for(sl*10);
    std::cout << "signal\n";
    cv.notify_all();
    std::this_thread::sleep_for(sl*10);
}

void Work(){
    std::unique_lock<std::mutex> lock(mu);
    std::cout << "here\n";
    cv.wait(lock);
    std::cout << "done\n";
}

int main(){
    std::thread my_threads[2];
    my_threads[0] = std::thread(SendSignal);
    my_threads[1] = std::thread(Work);

    my_threads[0].join();
    my_threads[1].join();
}



//===== 180 ======
//This is to enhancing my understanding of condition_variable
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::condition_variable cv;
std::mutex mu;

void work(int & num){
    num ++;
    cv.notify_all();
}

int main(){
    int a = 3;
    std::thread my_thread;
    my_thread = std::thread(&work, std::ref(a));
    my_thread.detach();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    {
        std::unique_lock<std::mutex> lock(mu);
        std::cout << a << std::endl;
        cv.wait(lock, [a]{std::cout << "checking\n"; return a == 4;});
    }
    std::cout << a << std::endl;

}

//====== 179 =====
//This is to enhance my understanding of cv.wait_for(unique_lock, duration, cond)
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::chrono::milliseconds sl(100);
std::condition_variable cv;
std::mutex mu;

int sig = 0;

void SendSignal(){
    std::this_thread::sleep_for(sl);
    cv.notify_all();
    std::this_thread::sleep_for(sl*0.2);
    sig = 1;
    cv.notify_all();
}

void Work(){
    auto start = std::chrono::high_resolution_clock::now();
    std::unique_lock<std::mutex> lock(mu);
    cv.wait_for(lock, sl*1.5, []{std::cout << "checking\n"; return sig == 1;});
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "time taken " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "\n";
}

int main(){
    std::thread my_threads[2];
    my_threads[0] = std::thread(SendSignal);
    my_threads[1] = std::thread(Work);


    my_threads[0].join();
    my_threads[1].join();
}


//====== 178 ======
//This is to practice cv.wait_until()
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>

std::chrono::high_resolution_clock::time_point init_time;
std::chrono::milliseconds sl(100);
std::condition_variable cv;
std::mutex mu;

void SendSignal(){
    std::this_thread::sleep_for(sl*3);
    cv.notify_one();
    cv.notify_one();
    std::cout << "Done signaling\n";
}

void Work(int i){
    std::this_thread::sleep_for(sl*i);
    std::unique_lock<std::mutex> lock(mu);
    std::cv_status status = cv.wait_until(lock, init_time - sl * 1.05);
    if (status == std::cv_status::timeout){
        std::cout << "timeout\n";
    } else if (status == std::cv_status::no_timeout) {
        std::cout << "received notify_all() first\n";
    }
    std::this_thread::sleep_for(sl*i*10);
}

int main(){
    init_time = std::chrono::high_resolution_clock::now();
    std::vector<std::thread> my_threads;
    my_threads.emplace_back(std::thread(SendSignal));
    my_threads.emplace_back(std::thread(Work, 1));
    my_threads.emplace_back(std::thread(Work, 2));

    for (auto & thread : my_threads){
        thread.join();
    }

}

//====== 177 ======
//This is to practice cv.wait_for(unique_lock, duration, cond) which returns bool, not std::cv_status::timeout/no_timeout
//to prevent spurious wakening
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::condition_variable cv;
std::mutex mu;

int sig = 0;
std::chrono::milliseconds sl(500);

void SendSignal(){
    cv.notify_all();
    std::this_thread::sleep_for(sl*1.2);

    sig = 1;
    cv.notify_all();
    
}

void Work(int i){
    std::unique_lock<std::mutex> lock(mu);
    if (cv.wait_for(lock, sl*i, []{return sig == 1;})){
        std::cout << i << ". sig = " << sig << std::endl;
    } else{
        std::cout << i << ". timeout sig = " << sig << std::endl;
    }

}

int main(){
    std::thread my_threads[3];
    my_threads[0] = std::thread(SendSignal);
    my_threads[1] = std::thread(Work, 1);
    my_threads[2] = std::thread(Work, 2);

    for (auto & thread : my_threads){
        thread.join();
    }
}

//====== 176 =====
//This is to practice wait_for(unique_lock, duration)
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex mu;
std::condition_variable cv;

void SendSignal(){
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "sending signal\n";
    cv.notify_all();
}

void Work(int i){
    std::this_thread::sleep_for(std::chrono::seconds(i));
    std::unique_lock<std::mutex> lock(mu);
    std::cv_status status = cv.wait_for(lock, std::chrono::seconds(1));
    if (status == std::cv_status::timeout){
        std::cout << "timeout\n";
    }else if (status == std::cv_status::no_timeout){
        std::cout << "no_timeout\n";
    }
}

int main(){
    std::thread my_threads[3];
    my_threads[0] = std::thread(SendSignal);
    my_threads[1] = std::thread(Work, 0); // returns when cv.notify_all() is called
    my_threads[2] = std::thread(Work, 1); // returns when duration runs out

    for (auto & thread : my_threads)
        thread.join();
}

//====== 175 =====
//This is to test that cv.wait() only works for unique_lock, not lock_guard
#include <iostream>
#include <thread>
#include <mutex>

std::condition_variable cv;
std::mutex mu;

void SendSignal(){
    cv.notify_all();
}

void Work(){
    std::lock_guard<std::mutex> lock(mu);
    cv.wait(lock, []{return true;}); //here wait() only takes unique_lock template class, not lock_guard template type
}

int main(){
    std::thread my_threads[2];

    my_threads[0] = std::thread(SendSignal);
    my_threads[1] = std::thread(Work);

    my_threads[0].join();
    my_threads[1].join();
}

//====== 174 =====
//This is to confirm threads are serialized in wait
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>

std::condition_variable cv;
std::mutex mu;

std::chrono::milliseconds sl(500);
void SendSignal(){
    std::this_thread::sleep_for(sl*2);
    cv.notify_all();
}

void Work(){
    std::unique_lock<std::mutex> lock(mu);
    cv.wait(lock);
    std::cout << std::this_thread::get_id() << "\n";
    for (int i = 0; i < 2; i++){
        std::this_thread::sleep_for(sl*2);
        std::cout << "\t" << i+1 << "\n";
    }
}

int main(){
    std::vector<std::thread> all_threads;
    all_threads.push_back(std::thread(SendSignal));    
    all_threads.push_back(std::thread(Work));
    all_threads.push_back(std::thread(Work));

    for (auto & thread : all_threads){
        thread.join();
    }
}

//====== 173 =====
//This is to practice always making one thread execute one block of first
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <atomic>

std::condition_variable produce_cv, consume_cv;
std::mutex produce_mu, consume_mu;

std::atomic<bool> start_produce (false), start_consume ( false);

std::vector<int> vecs;

void produce(){
    std::unique_lock<std::mutex> lock_produce(produce_mu);
    produce_cv.wait(lock_produce, []{std::cout << "checked\n"; return &start_produce;});    

    //start producing
    for (int i = 0; i < 3; i++)
        vecs.push_back(2*i);

    //done producing
    start_consume = true;
    consume_cv.notify_one();
}

bool cond(){
    static int count = 1;
    if (count == 1){
        start_produce = true;
        produce_cv.notify_one();
    }
    count ++;
    return start_consume;
}

void consume(){
    //std::cout << "c\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::unique_lock<std::mutex> lock_consume(consume_mu);
    consume_cv.wait(lock_consume, cond);
    std::cout << start_consume << std::endl;
    
    std::cout << "cosuming\n";
    //start consuming
    while(! vecs.empty()){
        std::cout << vecs.back() << " ";
        vecs.pop_back();
    }
    std::cout << "\n";
}

int main(){
    std::thread pro_con[2];
    pro_con[0] = std::thread(produce);
    pro_con[1] = std::thread(consume);

    for (auto & thread : pro_con){
        thread.join();
    }
}


//===== 172 =====
//This is to enhance my understanding of wait
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mu;
std::condition_variable cv;
int sig = 0;

bool cond(int id){
    std::cout << std::this_thread::get_id() << ": checking " << id << sig << std::endl;
    return sig == 1 || id == 0;
}

void Work(int id){
    //if (id == 1)
    //    std::this_thread::sleep_for(std::chrono::microseconds(5));
    std::unique_lock<std::mutex> lock(mu);
    cv.wait(lock, std::bind(cond, id));    
    if (id == 0){
        sig = 1;
        cv.notify_one();
    }
        
}

int main(){
    std::thread my_threads[2];
    my_threads[0] = std::thread(Work, 0);
    my_threads[1] = std::thread(Work, 1);
    
    //std::this_thread::sleep_for(std::chrono::seconds(1));
    //sig = 1;
    //cv.notify_all();
    for (auto & thread : my_threads)
        thread.join();
}


//====== 171 ======
//This is to practice producer/consumer design pattern
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <chrono>

std::vector <int> buckets;
bool full = false;

std::condition_variable cv;
std::mutex mu;

void produce(){
    int iterations = std::thread::hardware_concurrency() - 1;
    while(iterations --){
        std::unique_lock<std::mutex> lock(mu);
        for (int i = iterations + 1; i > 0; i --)
            buckets.push_back(i);
        full = true;
        std::cout << "size of buckets: " << buckets.size() << std::endl;
        lock.unlock();
        cv.notify_one();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void consume(){
    std::unique_lock<std::mutex> lock(mu);
    cv.wait(lock, []{std::cout << std::this_thread::get_id() << ": checking\n"; return full;});
    std::cout << std::this_thread::get_id() << " ";
    while(!buckets.empty()){
        std::cout << buckets.back() << " ";
        buckets.pop_back();
    }
    full = false;
    std::cout << std::endl;
}

int main(){
    std::vector<std::thread> my_threads;
    my_threads.emplace_back(std::thread(produce));
    for (int i = 0; i < std::thread::hardware_concurrency() - 1; i ++){
        my_threads.emplace_back(std::thread(consume));
    }

    for (std::thread & thread : my_threads){
        if (thread.joinable()){
            thread.join();
        }
    }
}


//====== 170 =====
//This is to enhance my understanding of wait()
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex mu, mu_print;
std::condition_variable cv;
std::chrono::milliseconds sl(100);

void Wait(){
    {
        std::unique_lock<std::mutex> lock(mu);
        cv.wait(lock); // still only one thread can lock the mutex

        std::unique_lock<std::mutex> lock_print(mu_print, std::defer_lock);
        lock_print.lock();
        std::cout << std::this_thread::get_id() << " sleeping for sl milliseconds\n";
        std::this_thread::sleep_for(sl*20);
        std::cout << "done sleeping\n";
    }
}

void Send_Signal(){
    std::this_thread::sleep_for(sl*1);
    //cv.notify_one();
    //std::this_thread::sleep_for(sl*20);
    //cv.notify_one();
    cv.notify_all();
}

int main(){
    std::thread my_threads[3];
    my_threads[0] = std::thread(Wait);
    my_threads[1] = std::thread(Wait);
    my_threads[2] = std::thread(Send_Signal);

    //my_threads[3] = std::thread();
    //my_threads[4] = std::thread();


    for (std::thread & thread : my_threads){
        thread.join();
    }
}

//===== 169 =====
//This is to enhance my understanding of condition_variable wait_for
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::condition_variable cv;
std::mutex mu;
std::chrono::milliseconds sl(100);

int sig;

void Send_Signal(){
    std::this_thread::sleep_for(sl*1);
    sig = 11;
    cv.notify_all();
    std::cout << "Done notifying 1\n";

    std::this_thread::sleep_for(sl*2);
    sig = 22;
    cv.notify_one();
    std::cout << "Done notifying 2\n";

    std::this_thread::sleep_for(sl*3);
    sig = 33;
    cv.notify_one();
    std::cout << "Done notifying 3\n";
}


void Wait(){
    int i = 3;
            std::unique_lock<std::mutex> lock(mu);
    while (i --){
        auto start_count = std::chrono::high_resolution_clock::now();
        //{
            //cv.wait(lock, []{return true;});
            cv.wait(lock);
        //}
        auto end_count = std::chrono::high_resolution_clock::now();
        std::cout << "time taken: " << std::chrono::duration_cast<std::chrono::milliseconds> (end_count - start_count).count() << "milliseconds: " << sig << std::endl;
    }
}

int main(){
    std::thread two_threads[2];
    two_threads[0] = std::thread(Send_Signal);
    two_threads[1] = std::thread(Wait);

    for (auto & thread : two_threads){
        if (thread.joinable()){
            thread.join();
        }
    }
}

//===== 168 =====
//This is to practice wait_for for condition variable.
//lock can be acquired if notify_all/one() and condtion are both met, or the time-duration is exceeded
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <mutex>

int sig = -1;

bool cond(){
    std::cout << std::this_thread::get_id() << " checking\n";
    return sig == 1;
}

void actions(int id, std::chrono::milliseconds sl, std::mutex & mu, std::condition_variable & cv){
    id += 1;
    std::unique_lock<std::mutex> lock(mu);
    if (cv.wait_for(lock, id*sl, cond)){
        std::cout << id << ". cond is met: " << sig << std::endl;
    }else{
        std::cout << id << ". timed out: " << sig << std::endl;
    }
}

void ssignal(std::chrono::milliseconds sl, std::condition_variable & cv){
    std::this_thread::sleep_for(sl + std::chrono::milliseconds(50)); // thread 1 timed out
    std::cout << "notifying all\n";
    cv.notify_one(); // since sig is still 0, pred() will be false, thus thread 2 will be timed out

    std::this_thread::sleep_for(sl*1);
    sig = 1;
    std::cout << "nofitying all\n";
    cv.notify_all(); // since sig = 1, thread 3 will exit before hitting timeout
}

int main(){
    std::mutex mu;
    std::condition_variable cv;
    std::chrono::milliseconds sl(500);

    std::vector<std::thread> my_threads;

    for (int i = 0; i < std::thread::hardware_concurrency()-1; i++){
        my_threads.push_back(std::thread(actions, i, sl, std::ref(mu), std::ref(cv)));
    }

    my_threads.push_back(std::thread(ssignal, sl, std::ref(cv)));
    //my_threads.push_back(std::thread(ssignal));

    for (std::thread & thread : my_threads){
        if (thread.joinable()){
            thread.join();
        }
    }
}

//===== 167 =====
//This is to practice condition_variable
#include <iostream>
#include <thread>
#include <mutex>
#include <stdlib.h>
#include <chrono>

bool cond (const double &balance){
    if (balance > 30000){
        return true;
    } else{
        return false;
    }
}
class Account{
    private:
        double balance;
    public:
        Account(double _bal): balance(_bal){}
        void Deposite(double amount, std::mutex & mu, std::condition_variable &cv){
            std::lock_guard<std::mutex> lock (mu);
            balance += amount;
            std::cout << "balance: " << balance << std::endl;
            cv.notify_one();
        }
        void Withdraw(double amount, std::mutex & mu, std::condition_variable & cv){
            //std::this_thread::sleep_for(std::chrono::seconds(2));
            std::unique_lock<std::mutex> lock(mu);
            std::cout << "\tbefore wait\n";
            cv.wait(lock, std::bind(cond, std::ref(balance)));
            //cv.wait(lock,[this]{return cond(balance);});
            //cv.wait(lock, [this]{return (balance) > 30000;});
            balance -= amount;
            std::cout << "balance: " << balance << std::endl;
        }
        void Get(){
            std::cout << "Balance: " << balance << std::endl;
        }
};

int main(){
    std::mutex mu;
    std::condition_variable cv;
    Account my_account(30000);
    std::thread actions[2];
    actions[1] = std::thread(&Account::Withdraw, &my_account, 2000, std::ref(mu), std::ref(cv));
    actions[0] = std::thread(&Account::Deposite, &my_account, 3000, std::ref(mu), std::ref(cv));

    for (std::thread & thread : actions){
        if (thread.joinable()){
            thread.join();
        }
    }
}

//====== 166 =====
//This is to practice static variable in a function
#include <iostream>

class P{
    private:
        int id;
    public:
        P(int _id = 0): id(_id) {
            std::cout << "P constructor\n";
        }
        void Set(int id){
            this -> id = id;
        }
        void Get(){
            std::cout << "id: " << this -> id << std::endl;
        }
};

void Test(int id){
    static P p[2] = {P(-1), P(-1)};
    int ind = id%2;
    if (ind == 1){
        p[ind].Set(id+1);
    } else{
        p[ind].Set(id);
    }
    p[ind].Get();
}

int main(){
    Test(0);
    std::cout << "___\n";
    Test(1);
    std::cout << "___\n";
    Test(2);
    std::cout << "____\n";
    Test(3);
    std::cout << "___\n";
}


//====== 165 =======
//This is to practice static member called in the main function
#include <iostream>

class B{
    public:
        B(){
            std::cout << "B constructor\n";
        }
        B(int i){
            std::cout << "new B constructor\n";
        }
};

class P{
    public:
        static B b;
    public:
        static int num;
        P(){
            num++;
        }
};

B P::b;
int P::num;

int main(){
    std::cout << "beginning of main()\n";
    P::num = 3;
    //P p(); //error: it is interpreted as a function declaration
    P p;
    std::cout << p.num << std::endl;

    P::b = B(2);
}


//=========== 164 ========
//This is to practice static function in a class to create a singleton
#include <iostream>

class P{
    private:
        int id;
        std::string name;
        P()=default;
    public:
        P (P&) = delete;
        P& operator = (P&)=delete;
        static P & GetIns(){
            static P ins;
            return ins;
        }

        ~P(){
            std::cout << "Singleton is destroyed\n";
        }

        void Set(int _id, std::string _name){
            id = _id;
            name = _name;
        }
        
        void Get(){
            std::cout << name << ": " << id << std::endl;
        }

};

int main(){
    P & p = P::GetIns();
    p.Set(2, "zls");
    p.Get();
    
    std::cout << "_________\n";
    P & pp = P::GetIns();
    pp.Get();

    std::cout << "___________\n";
    //P ppp = P::GetIns();
    //ppp.Get();
    //P ppp;
    //ppp = pp;
}


//========== 163 =========
//This is to practice deleting an object through another pointer
#include <iostream>

class P{
    public:
        ~P(){
            std::cout << "Destroyed\n";
        }
};

void del(P *ptr){
    delete ptr;
}

class PP{
    private:
        P * ptr;
    public:
        PP(P * _ptr): ptr(_ptr){}
        ~PP(){
            delete ptr;
        }
};

int main(){
    P *ptr = new P;
    P *ptr_1 = ptr;
    //delete ptr_1;
    del(ptr);
    
    PP(new P);

}

//============ 164 ============
//This is to practice releasing single-instance class
#include <iostream>

template<typename T>
class DestroySingleton{
    private:
        T *ptr;
    public:
        DestroySingleton(T * _ptr): ptr(_ptr){
            std::cout << "1\n";
        }
        ~DestroySingleton() {
            ptr -> Exist();
            delete ptr;
            ptr -> Exist();
            std::cout << "singleton is released\n";
        }

};

class Singleton{
    private:
        Singleton(int _id = -1): id(_id){
            std::cout << "Singleton is created\n";
        }
        int id;
    public:
        static DestroySingleton<Singleton> destroy;
        //static DestroySingleton destroy;
        static Singleton* sing_ins;
        ~Singleton(){
            std::cout << "Singleton is destroyed\n";
        }
        static Singleton & Getins(int _id){
            if (sing_ins == NULL){
                sing_ins = new Singleton(_id);
            }
            return * sing_ins;
        }

        void Exist(){
            std::cout << this -> id <<  " exist\n";
        }
        void SetID(int _id){
            id =_id;
        }

};

Singleton * Singleton::sing_ins = NULL;
DestroySingleton<Singleton> Singleton::destroy(&(Singleton::Getins(-99)));
//DestroySingleton Singleton::destroy(&(Singleton::Getins(-99))); //(Singleton::sing_ins);

int main(){
    std::cout << "0\n";
    {
        Singleton::Getins(9);
        //Singleton::Getins() . ~Singleton();
        //delete Singleton::sing_ins;
        Singleton::Getins(9).SetID(9);
    }
    std::cout << "____________ out of scope _________\n";
    Singleton::sing_ins -> Exist();
}


//=========== 163 ============
//This is to practice automatically releasing pointer resources in a class
#include <iostream>

class P{
    private:
        int * p;
        //P * p_arr;
        P(): p(new int(3)){} 
    public:
        class Inner{
            public:
                ~Inner(){
                    std::cout << "deleting pp\n";
                    delete pp;
                }

        };

        static Inner inner;
        static P * pp;
        //P(int & _a): p(&_a) {}
        //P(): p(new int), pp(new P){} // segmentation fault by pp infinit loop
        P(const P &) = delete;
        static void MakeIns(){
            if(pp == NULL){
                pp = new P;
            }
            //return *pp;
        }
        void Getp(){
            std::cout << *(this -> p) << std::endl;
        }
        ~P(){
            //delete p;
            std::cout << "resource p is released\n";
        }

};

P* P::pp = NULL;
P::Inner P::inner;

int main(){
    int a = 3;
    //P p(2); // since 2 is a rvalue, which has not memory address, thus it can not be assigned to a reference
    //P p(a);

    int b = 4;
    {
        int * ptr = &b;
        //delete ptr;
    }

    P::MakeIns(); 
    P::pp -> Getp();
    //P::pp -> ~P();
}



//======= 162 =======
//This is to practice array size
#include <iostream>

int aN = 3;

void Test(int N){
    //static int a[aN];
    int arr[N];
    static int * a = arr;
}

int main(){
    int a = 3;
    Test(a);
    int b[a];
}

//======= 161 ========
//This is to practice multi-instance class without using pointers
#include <iostream>
#include <vector>

const int N = 3;

class P{
    private:
        static P all_insts[N];
        static int num_calls;
        int id;
        P (int _id = -1): id(_id) {}
        ~P(){
            std::cout << "destroyed: " << id << std::endl;
        }
    public:
        static P & GetInstance(int i){
            int ind = i % N;
            num_calls ++;

            if (num_calls <= N){
                all_insts[ind] = P(i);
            }

            return all_insts[ind];
        }

        int GetID(){
            return this -> id;
        }
};

int P::num_calls = 0;
P P::all_insts[N]; // has to be defined outside of the class

int main(){
    std::vector<P*> all_p;
    for (int i = 0; i < 2*N; i++){
        all_p.emplace_back(&(P::GetInstance(i)));
    }

    for (auto &p : all_p){
        std::cout << p -> GetID() << std::endl;
    }

    for (int i = 0; i < N; i++){
        std::cout << all_p[i] -> GetID() << std::endl;
        std::cout << all_p[i] << " - " << all_p[i+N] << std::endl;
        if (all_p[i] == all_p[i+N]){
            std::cout << "duplicate\n";
        }
        else{
            std::cout << "different\n";
        }
    }
}

//====== 160 ======
//This is to understand what would happen if a resource is released by delete
#include <iostream>

int a = 3;

int main(){
    int * ptr = &a;
    delete ptr;
    std::cout << a << std::endl;
}

//====== 159 =====
//This is to practice new class being destroyed
#include <iostream>

class P{
    public:
        P(){
            std::cout << "\tcreated\n";
        }
        ~P(){
            std::cout << "\tdestroyed\n";
        }
};

int main(){
    std::cout << "before the scope\n";
    {
        P p;
    }
    std::cout << "after the scope\n";

    std::cout << "________\n";
    {
        P *p = new P;
        std::cout << "\t****\n";
        delete p; // without calling delete, the object will not be deleted
        std::cout << "\t****\n";
    }
    std::cout << "after the scope\n";
}

//====== 158 ======
//This is to practice limited-instance class
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

const int N = 2;
std::mutex mu_print;
class P{
    private:
        int id;
        static P * ptr[N];
        P(int ind): id(ind){}
        static int count;
        ~P(){
            delete ptr[this -> id];
            std::cout << "(Not getting called) destroying " << this -> id << std::endl;
        }
    public:
        static P & GetInstance(int i, std::mutex & mu){
            int ind = i%N;
            {
                std::lock_guard<std::mutex> lock(mu);
                if (ptr[ind] == NULL){
                    ptr[ind] = new P(ind);
                }
            }
            {
                std::lock_guard<std::mutex> lock(mu_print);
                std::cout << std::this_thread::get_id() << ": " << ptr[ind] -> GetID() << std::endl;
            }
            return *ptr[ind];
        }
        int GetID(){
            return this -> id;
        }
        static P** GetPtr(){
            return ptr;
        }
};
int P::count = 0;
P * P::ptr[N];

int main(){
    std::mutex mu;
    std::vector<std::thread> my_threads;
    for (int i = 0; i < std::thread::hardware_concurrency() + 4; i++){
        my_threads.emplace_back(P::GetInstance, i, std::ref(mu));
    }

    for (std::thread & thread : my_threads){
        if (thread.joinable()){
            thread.join();
        }
    }
    
    for (int i = 0; i < N; i++){
        std::cout << P::GetPtr()[i] -> GetID() << " ";
    }
    std::cout << std::endl;

    P** p_ptr = P::GetPtr();
    for (int i = 0; i < N; i++){
        std::cout << p_ptr[i] -> GetID() << " ";
        std::cout << (*(p_ptr+i)) -> GetID() << std::endl;
    }

    std::cout << "xx\n";
}

//====== 157 ======
//This is to practice class nested inside a class
#include <iostream>

class T{
    public:
        ~T(){
            std::cout << "T is destroyed\n";
        }
};

class P{
    private:
        struct B{ //class B {
            public:
                ~B(){
                    std::cout << "B is destroyed\n";
                }
        };

    public:
        ~P(){
            std::cout << "P is destroyed\n";
        }
        T t;
        static B b; // it only gets destroyed once throughout the lifetime of the program
};

P::B P::b; // if not initialized outside, then it won't be created?

int main(){
    P p, p2, p3;
}


//======== 156 ======
//This is to practice one-instance class
#include <iostream>

class P{
    private:
        int id;
        static P * ptr;
        P (int _id): id(_id){}
    public:
        static P & GetInstance(int _id){
            if (ptr == nullptr){
                ptr = new P(_id);
            }
            return *ptr;
        }

        P * Get(){
            return ptr;
        }

};

P * P::ptr; // = nullptr // =NULL

int main(){
    P p1 = P::GetInstance(2);
    //P p2 = P::GetInstance(3);
    P p2 = p1.GetInstance(3);

    if (p1.Get() == p2.Get()){
        std::cout << "the same object\n";
    }
}

//======== 155 =======
//This is to practice reference variable in a function
#include <iostream>

int X = 9;

void Test(int & b){
    int & a = b; // reference variable needs initialization, which makes it unnecessary as we can just make it as an argument
    int & c = X;
    c -- ;
}

int main(){
    int a = 2;
    Test(a);
    std::cout << X << std::endl;
}

//====== 154 ======
//This is to practice reference member in a class
#include <iostream>

class P{
    private:
        const int &a; // a reference member // use const if don't want to change it
        int &b;
    public:
        //P(int &_a){ a = _a; a ++;} // should explicitly initialize a reference member
        P(const int &_a, int &_b): a(_a), b(_b){b++;}
};

int main(){
    int a = 2, b =3;
    P p(a, b); // a is changed in p
    std::cout << a << " " << b << std::endl;
}


//===== 153 =====
//This is to practice creating an object only once among the threads
#include <thread>
#include <iostream>
#include <mutex>
#include <vector>
#include <time.h>
#include <stdlib.h>

std::mutex mu_id;

class P;
void print (P &, int);
class P{
    public:
        int id;
        P(int i = 999999999): id(i){
            //std::cout << "\tcreated " << i << std::endl; 
        }
        void Getid(){
            print (*this, 2);
        }
};

std::mutex mu0;

void print (P &p, int i){
    std::lock_guard<std::mutex> lock(mu0);
    if (i == 0){
        std::cout << std::this_thread::get_id() << " got the chance\n";
    }else if (i == 1){
        std::cout << std::this_thread::get_id() << " missed the chance\n";
    }else if (i == 2){
        std::cout <<std::this_thread::get_id() << ": " << p.id << std::endl;
    }

}

void create_p (int i, P &p){
    if (i != 3){
        throw 3;
    }
    p = P(i);
    print (p, 0);
}

void work(std::once_flag & initialize_flag, int i, P &p){
    int ready = 3;
    while (ready){
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        ready --;
    }
    try{
        std::call_once(initialize_flag, create_p, i, std::ref(p));
    }catch(...){
        print (p, 1);
    }
   
    //create a barrier 
    std::this_thread::sleep_for(std::chrono::seconds(1)); //assuming the object is finally created within 1 second, so this
                                                          //line ensures all threads get the correct object
    p.Getid();
}


int main(){
    P p;
    std::once_flag initialize_flag;
    std::vector<std::thread> my_threads;
    for (int i = 0; i < std::thread::hardware_concurrency(); i ++){
        my_threads.emplace_back(std::thread(work, std::ref(initialize_flag), i, std::ref(p)));
    }

    for(auto & thread : my_threads) {
        if (thread.joinable()){
            thread.join();
        }
    }
}


//======= 152 ========
//This is to practice pass by reference
#include <iostream>
#include <functional>

void Test(int &a, int &b){
    a ++;
    b ++;
}

int main(){
    int a = 3, b = 3;
    Test(a, b);
    std::cout << a << " " << b << std::endl;

    std::function<void()> f = std::bind(Test, std::ref(a), b);
    f();
    std::cout << a << " " << b << std::endl;
}


//====== 151 ======
//This is to practice random number generated
#include <iostream>
#include <stdlib.h>
#include <time.h>

int main(){
    srand(20000); //with a given seed, the random numbers generated are always the same
    std::cout << rand() << std::endl << rand() << 
       std::endl << rand() << std::endl;

    srand(static_cast<unsigned int> (time(NULL)));
    std::cout << "time: " << time(NULL) << std::endl;
    std::cout << rand () << " " << rand() << std::endl;
}


//======= 150 =======
//This is to test a function that returns an array
#include <iostream>

int *Test(){
    int arr[4];
    static int i = 3;
    i ++;
    arr[0] = i;
    arr[1] = i + 2;
    arr[2] = 99;
    arr[3] = 100;

    return arr+1; // is not suggested to return a local variable address, make it static.
}

int main(){
    int *arr1;
    arr1 = Test();
    std::cout << arr1[0] << " " << arr1[1] << arr1[2] << " " << sizeof(arr1)/sizeof(arr1[0]) << std::endl;
    
    Test();
    std::cout << arr1[0] << " " << arr1[1] << std::endl;

}

//======= 149 ======
//This is to practice call_once and once_flag
#include <thread>
#include <mutex>
#include <iostream>
#include <stdlib.h>
#include <vector>

#define PRIZE_NUM 19 

struct Arr{
    int order, num;
    Arr(int _order, int _num): order(_order), num(_num) {}
};

void Check(std::mutex &);

void print(std::mutex &, int, int, int);

void Lottery(std::once_flag & onceflag, std::mutex &mu){
    try{
        std::call_once(onceflag, Check, mu);    
    } catch(Arr &arr){ // *arr){
        print(mu, 0, arr.num, arr.order);
        //print (mu, 0, -99, order);
    }
}

void Check(std::mutex & mu){
    //print (mu, -1, -1, -1);
    static int order = 0;
    order += 1;
    int num = rand()%20;
    Arr arr(order, num);
    if (num == PRIZE_NUM){
        print (mu, 1, num, order);
    }else{
        //print (mu, -1, -1, -1);
        throw arr;
    }
}
void print(std::mutex &mu, int i, int num, int order){
    std::lock_guard<std::mutex> lock(mu);
    if (i == 0){
        std::cout  << order << ". " << std::this_thread::get_id() << " " << num << " checked\n";
    } else if (i == 1){
        std::cout << order << ". " << std::this_thread::get_id() << " got the prize number " << num << std::endl;
    } else{
        std::cout << "*** " << std::this_thread::get_id() << std::endl;
    }
}

int main(){
    std::once_flag onceflag;
    std::mutex mu;
    std::vector<std::thread> participants;
    for (int i = 0; i < 100; i ++){
        participants.emplace_back(std::thread(Lottery, std::ref(onceflag), std::ref(mu)));
    }
    
    for (auto & thread : participants){
        if (thread.joinable()){
            thread.join();
        }
    }

}

//====== 148 ======
//This is to practice exception handling
#include <iostream>

int main(){
    try{
        throw 2.3;
        throw 2; // this line is skipped as the control goes out of the scope
    }catch(int a){ // only takes one argument
        std::cout << "int\n";
    }catch(...){
        std::cout << "others\n";
    }

    try{
        try{
            throw 2;
        }catch (char a){
            std::cout << "char\n";
        }catch(...){
            throw 2.3;
        }
    }catch(double a){
        std::cout << "double\n"; 
    }catch (...){
        std::cout << "extern\n";
    }

    try{
        throw 2.2;
    }catch(int a){
        std::cout << "int\n";
    }
}

//====== 147 =====
//This is to practice try_lock_for() for fireworks
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <stdlib.h>

void Fireworks(std::timed_mutex & mu, std::chrono::milliseconds sl){
    //the trajactory of the firworks is done by the threads that do not lock the timed_mutex
    std::unique_lock<std::timed_mutex> lock(mu, std::defer_lock);
    while (!lock.try_lock_for(sl)){
        std::cout  << "-";
        std::this_thread::sleep_for(sl);
    }

    // now the thread got mu locked
    std::this_thread::sleep_for((1+rand()%20)*sl);
    std::cout << "----*\n"; //at least this high of the fireworks
}

int main(){
    std::vector<std::thread> firwork_threads;
    std::chrono::milliseconds sl(100);
    std::timed_mutex timed_mu;

    for (int i = 0; i < 10; i++){
        firwork_threads.emplace_back(Fireworks, std::ref(timed_mu), sl);
    }

    for (auto & thread : firwork_threads){
        if (thread.joinable()){
            thread.join();
        }
    }
}


//======= 146 =======
//This is to practice unique_lock try_lock_for which is only for timed_mutex, not mutex
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

void Try_Lock_For(std::timed_mutex & mu, std::chrono::seconds sl){
    std::unique_lock<std::timed_mutex> lock(mu, std::defer_lock);
    std::this_thread::sleep_for(std::chrono::nanoseconds(1));
    auto start_count = std::chrono::high_resolution_clock::now();
    if (lock.try_lock_for(sl)){
        std::cout << "succeeded\n";
    }else{
        std::cout << "failed to lock mu in 1 second\n";
        while (true){
            if (lock.try_lock()){
                std::cout << "Finally lock the timed_mutex\n";
                break;
            } else{
                std::this_thread::sleep_for(sl);
            }
        }
    }
    auto end_count = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken " << std::chrono::duration_cast<std::chrono::milliseconds> (end_count - start_count).count() << " millisecs" << std::endl;
}

void Lock_First(std::timed_mutex & mu, std::chrono::seconds sl){
    std::lock_guard<std::timed_mutex> lock(mu);
    std::this_thread::sleep_for(sl*3);
}

int main(){
    std::chrono::seconds sl(1);
    std::timed_mutex timed_mu;
    std::thread my_threads[2];
    my_threads[0] = std::thread(Try_Lock_For, std::ref(timed_mu), sl);
    my_threads[1] = std::thread(Lock_First, std::ref(timed_mu), sl);


    for (std::thread & thread : my_threads){
        if (thread.joinable()){
            thread.join();
        }
    }
}

//====== 145 =====
//This is to practice try_lock for std::unique_lock
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

class Test{
    private:
        std::mutex &mu;
        std::chrono::seconds sec;
        int a, b;
    public:
        Test(int _a, int _b, std::chrono::seconds _sec, std::mutex &_mu): mu(_mu), a(_a), b(_b), sec(_sec){}

        void operator () (){
            //std::unique_lock<std::mutex> lock (mu, std::defer_lock); //no need to call unlock explicitly
            std::this_thread::sleep_for(sec);
            while (true){
                //if (lock.try_lock()){
                if (mu.try_lock()){
                    std::cout << "succeeded, a = " << a << std::endl;
                    //lock.unlock(); // this is not necessary as the destructor will do the job
                    break;
                }else{
                    b ++;
                    std::cout << "failed to lock: " << b << std::endl;
                    std::this_thread::sleep_for(sec);
                    if (b > 10) break;
                }
            }
        }

        void start(){
            std::lock_guard<std::mutex> lock(mu);
            std::this_thread::sleep_for(sec*5);
            a += 2;
        }
};

int main(){
    std::mutex mu;
    Test test(2, 3, std::chrono::seconds(1), mu);

    std::thread t1 (test);
    std::thread t2 (&Test::start, &test);

    t1.join();
    t2.join();
    
    //mu.unlock();
    mu.lock(); // since mu is locked by a child thread, and it will never unlock it, so deadlock here
}



//====== 144 ======
//This is to practice std::defer_lock, std::adopt_lock
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

class BankAccount{
    private:
        static std::mutex mu_print;
        std::mutex mu;
        std::string name;
        double balance;
    public:
        BankAccount(std::string _name, double _balance): name(_name), balance(_balance){}
        friend void Transfer(BankAccount &, BankAccount &, double);
        friend void print_balance(BankAccount &, BankAccount &, double, double, double);
        friend void print_transaction(BankAccount &, BankAccount &);
};

std::mutex BankAccount::mu_print; // have to be declared/initialized here?

void print_balance(BankAccount &, BankAccount &);
 
void print_transaction(BankAccount & from, BankAccount & to){
    std::cout << std::this_thread::get_id() << ": " << from.name << ": " << from.balance << "; "
        << to.name << ": " << to.balance << std::endl;
}

void Transfer(BankAccount & from, BankAccount & to, double change){
    if (&from == &to){
        return;
    }
    double balance_from, balance_to;
    {
        //practice lock_guard/unique_lock, only with adopt_lock, since defer_lock is not supported for lock_guard
        //std::lock(from.mu, to.mu);
        //std::unique_lock<std::mutex> lock_1 (from.mu, std::adopt_lock);
        //std::unique_lock<std::mutex> lock_2 (to.mu, std::adopt_lock);

        std::unique_lock<std::mutex> lock_1 (from.mu, std::defer_lock);
        std::unique_lock<std::mutex> lock_2 (to.mu, std::defer_lock);
        std::lock(lock_1, lock_2);

        from.balance -= change;
        to.balance += change;
        
        //print_transaction (from, to);

        balance_from = from.balance;
        balance_to = to.balance;
    }

    print_balance(from, to, balance_from, balance_to, change);
}
void print_balance(BankAccount & from, BankAccount & to, double bal_from, double bal_to, double change){
    std::lock_guard<std::mutex> lock(BankAccount::mu_print);
    std::cout << std::this_thread::get_id() << ": " << change << " -> " << from.name << ": " << bal_from << "; " 
        << to.name << ": " << bal_to << std::endl; 
}

int main(){
    BankAccount acc_1("zls", 30000), acc_2("dsy", 15000),
                acc_3("xxx", 20000), acc_4("yyy", 1000000);
    
    std::vector<std::thread> my_threads;
    my_threads.emplace_back(std::thread(Transfer, std::ref(acc_1), std::ref(acc_2), 25000));
    my_threads.emplace_back(std::thread(Transfer, std::ref(acc_1), std::ref(acc_3), 500));
    my_threads.emplace_back(std::thread(Transfer, std::ref(acc_1), std::ref(acc_4), 15000));
    my_threads.emplace_back(std::thread(Transfer, std::ref(acc_3), std::ref(acc_2), 2000));
    my_threads.emplace_back(std::thread(Transfer, std::ref(acc_4), std::ref(acc_2), 2000));
    my_threads.emplace_back(std::thread(Transfer, std::ref(acc_2), std::ref(acc_2), 25000));

    for (std::thread & thread : my_threads){
        if (thread.joinable()){
            thread.join();
        }
    }
}

//====== 143 ======
//This is to practice try_lock(), which returns true if getting the lock, otherwise false
#include <thread>
#include <mutex>
#include <iostream>
#include <vector>
#include <chrono>

void task_1(std::mutex & mu, int &a, int & b, std::chrono::seconds sl){
    std::this_thread::sleep_for(sl);
    while (true){
        if (mu.try_lock()){
            std::cout << "task_1 a: " << a << std::endl;
            mu.unlock();
            break;
        } else{
            b ++;
            std::cout << "task_1 b: " << b << std::endl;
            std::this_thread::sleep_for(sl);
        }
    }
}

void task_2(std::mutex & mu, int & a, int &b, std::chrono::seconds sl){
    mu.lock();
    std::this_thread::sleep_for(5*sl);
    a ++;
    mu.unlock();
}


int main(){
    std::mutex mu;
    std::chrono::seconds sl(1);
    int a =0;
    int b = 0;
    std::vector<std::thread> all_threads;
    all_threads.emplace_back(std::thread(task_1, std::ref(mu), std::ref(a), std::ref(b), sl));
    all_threads.emplace_back(std::thread(task_1, std::ref(mu), std::ref(a), std::ref(b), sl));


    for (auto & thread : all_threads){
        if (thread.joinable()){
            thread.join();
        }
    }
}

//===== 142 =====
//This is to practice mutex in the main function
#include <mutex>
#include <iostream>
#include <thread>

int main(){
    std::mutex mu;

    mu.lock();
    std::cout << std::this_thread::get_id() << " locks\n";
    mu.unlock();
    std::cout << std::this_thread::get_id() << " unlocks\n";
}


//===== 141 ======
//This is to practice writing a lock_guard
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class LockGuard: public std::mutex{
    private:
        std::mutex &mu;
    public:
        LockGuard(std::mutex & _mu): mu(_mu){
            mu.lock();
            std::cout << "\tmu locked\n";
        } 
        ~LockGuard(){
            mu.unlock();              
            std::cout << "\tmu unlocked\n";
        }
};

void TestLG(std::mutex &mu){
    LockGuard lg(mu);
    std::cout << std::this_thread::get_id() << ": " << "xxxx\n";
}

int main(){
    //std::lock_guard<std::mutex> lock(mu);
    std::mutex mu;
    std::cout << "Before the scope\n";
    {
        LockGuard lg (mu);
    }
    std::cout << "After the scope\n";
    
    std::vector<std::thread> my_threads;
    my_threads.emplace_back(std::thread(TestLG, std::ref(mu)));
    my_threads.emplace_back(std::thread(TestLG, std::ref(mu)));

    for (auto & thread : my_threads){
        if (thread.joinable()){
            thread.join();
        }
    }

}

//===== 140 ======
//This is to practice lock_guard and adopt_lock, defer_lock
#include <thread>
#include <mutex>
#include <iostream>

std::mutex mu0, mu01, mu02;

void test_lock(std::mutex & mu){
    std::lock(mu, mu0, mu01); // without this line, the mutexes are not locked at all, so asynchronized
    //mu.lock();
    std::lock_guard<std::mutex> lock(mu, std::adopt_lock); //, std::defer_lock); not work for std::defer_lock, which is only working for std::unique_lock?
    std::lock_guard<std::mutex> lock_2(mu0, std::adopt_lock);
    std::unique_lock<std::mutex> lock_3(mu01, std::defer_lock);
    std::unique_lock<std::mutex> lock_4(mu02, std::defer_lock);
    //lock_3.unlock();
    mu01.unlock();
    //lock_3.lock();
    std::lock(lock_3, lock_4);

    std::cout << std::this_thread::get_id() << ": xxxx\n";
}

int main(){
    std::mutex mu;
    std::thread my_threads[2];
    my_threads[0] = std::thread(test_lock, std::ref(mu));
    my_threads[1] = std::thread(test_lock, std::ref(mu));


    for (std::thread & thread : my_threads){
        if (thread.joinable()){
            thread.join();
        }
    }
}


//====== 139 ====
//This is to figure out how we can pass a class object with mutex members to a function
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

struct Log{
    public:
        std::mutex mu;
};

void MakeLog(Log &log, std::string msg){
    std::lock_guard<std::mutex> lock(log.mu);
    std::cout << std::this_thread::get_id() << ": " << msg << std::endl;
}

int main(){
    Log log;
    std::vector<std::thread> LogThreads;
    LogThreads.emplace_back(std::thread(MakeLog, std::ref(log), "first"));
    LogThreads.emplace_back(std::thread(MakeLog, std::ref(log), "second"));
    LogThreads.emplace_back(std::thread(MakeLog, std::ref(log), "third"));


    for (auto & thread : LogThreads){
        if (thread.joinable()){
            thread.join();
        }
    }
}

//===== 138 ======
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>

struct Employee{
    public:
        std::mutex mu; // get one partner at a time
        std::string name;
        Employee (std::string _name): name(_name){}
        std::vector<std::string> partners;
        std::string Get_partners(){
            std::string all_partners = "";
            for (auto iter = partners.begin(); iter < partners.end() - 1; iter ++){
                all_partners += *iter + ", ";
            }
            all_partners += *(partners.end()-1);
            return all_partners;
        }
};

void SendEmail(Employee & e1, Employee & e2){
    static std::mutex mu;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::lock_guard<std::mutex> lock(mu); //make sure the cout is accessed by only one thread
    std::cout << e1.name << " got a new partner: " << e2.name << std::endl;
}

void Pair_partners(Employee & e1, Employee &e2){
    // each person can only pair with another person at a time, not multiple partners at a time
    // so use mutex to synchronize the process
    {
        std::lock(e1.mu, e2.mu); // the two locks are protected from getting into a deadlock
        std::lock_guard<std::mutex> lk1(e1.mu, std::adopt_lock);
        std::lock_guard<std::mutex> lk2(e2.mu, std::adopt_lock);
        
        e1.partners.push_back(e2.name);
        e2.partners.push_back(e1.name);
        //keep the output clean
        std::cout << e1.name << " and " << e2.name << " are partners.\n";
    }
     
    //since sending emails is very time consuming, we do it in parallel
    std::thread email_thread[2];
    email_thread[0] = std::thread(SendEmail, std::ref(e1), std::ref(e2));
    email_thread[1] = std::thread(SendEmail, std::ref(e2), std::ref(e1));
    
    email_thread[0].detach();
    email_thread[1].detach();
}


int main(){
    Employee bob ("Bob"), alice("Alice"), mike("Mike"), jim("Jim");
    std::vector<std::thread> make_partners;
    make_partners.emplace_back(std::thread(Pair_partners, std::ref(bob), std::ref(alice)));
    make_partners.emplace_back(std::thread(Pair_partners, std::ref(alice), std::ref(mike)));
    make_partners.emplace_back(std::thread(Pair_partners, std::ref(bob), std::ref(mike)));

    for (auto & thread : make_partners){
        if (thread.joinable()){
            thread.join();
        }
    }

    std::this_thread::sleep_for(std::chrono::seconds(3));
}

//====== 137 =====
#include <iostream>
#include <chrono>
#include <thread>

class P{
    public:
        P() = default;
        P(const P &p){
            std::cout << "\tcopy constructor\n";
        }
        P & operator = (const P &p){
            std::cout << "\tcopy assignment\n";
            return *this;
        }
};

P test_1(){
    P p;
    return p; // return value optimization, so a copy of the p is elided
}

P test_2(P p){
    std::cout << "before returning\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return p;
}

int main(){
    P p;
    p = test_1();
    
    std::cout << "______\n";
    P p2;
    p2 = test_2(p);
}

//===== 136 ====
//This is to practice when copy constructor and copy assignment are called
#include <iostream>

class P{
    public:
        int i = 0;
        P() = default;
        P (const P &p){ // p must be a lvalue, not rvalue, otherwise it is not copy constructor
            std::cout << "copy constructor is called\n";
        } 
        //Copy constructor must pass object by reference, not by value
        //P (const P p){
        //    std::cout << "value copy constructor is called\n";
        //}
        P & operator = (const P &p){ // works for both value and reference
            std::cout << "copy assignment is called\n";
            return *this;
        }
        //can not overload in this way, as passing an object does not distinguish the calling of the two functions
        //P & operator = (const P p){
        //    std::cout << "(value) copy assignment is called\n";
        //}
};

void test_1(const P &p){
    std::cout << "neither should be called\n";
}

void test_2(const P p){
    std::cout << "only copy constructor should be called\n";
}

P test_3(){
    P p;
    p.i = 200;
    return p; // return value optimization
}

P & test_4(){
    static P p;
    return p;
}

P test_5(P &p){
    std::cout << "before return\n";
    //if return by reference, there will be no copy constructor happening
    return p; // copy p into a rvalue using copy constructor to the scope of the function
}

P test_6(P p){
    std::cout << "before returning\n";
    return p;
}

int main(){
    P p;
    std::cout << "\t____________\n";
    test_1(p);

    std::cout << "\t____________\n";
    test_2(p);

    std::cout << "\t____ neither is called ________\n";
    test_3(); // the return value is not assigned to any P object

    std::cout << "\t____ copy assignment should be called ________\n";
    p = test_3();

    std::cout << "\t______ neither is called (test_3 returns a value, not a reference)________\n";
    P p2 (test_3()); // for copy constructor to work, the argument has to be a reference, not a value, i.e. a lvalue
    std::cout << p2.i << std::endl;

    std::cout << "\t______ copy constructor should be called \n";
    P p3 = test_4();

    std::cout << "\t__ both are called ____\n";
    p3 = test_5(p); //copy constructor is called inside the function, and copy assignment is called in this line

    std::cout << "\t___ 2 copy constructor calling and one copy assignment______\n";
    test_6(p);
}

//====== 135 ======
//This is to practice unique_lock
#include <iostream>
#include <thread>
#include <mutex>
#include <map>
#include <chrono>

template <typename T>
void ThreadTask(T a, std::mutex *mu){
    std::unique_lock<std::mutex> lock(*mu, std::defer_lock);
    std::cout << std::this_thread::get_id() << " is sleeping for 1 second\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    lock.lock();
    std::cout << "\t" << std::this_thread::get_id() << ": (locked) " << a << std::endl;
}

void FillGap(std::mutex *mu){
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::unique_lock<std::mutex> lock (*mu);
    std::cout << std::this_thread::get_id() << " filled the gap?\n";
}

void FillGap_2(std::mutex *mu){
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::unique_lock<std::mutex> lock(*mu);
    std::cout << std::this_thread::get_id() << " filled the gap_2?\n";
}

int main(){
    std::mutex mu;
    std::map <std::string, std::thread> map_threads;
    map_threads["int"] = std::thread(ThreadTask<int>, 2, &mu);
    //map_threads["double"] = std::thread(ThreadTask<double>, 3.14159253, &mu);
    //map_threads["string"] = std::thread(ThreadTask<std::string>, "****", &mu);
    map_threads["fillgap"] = std::thread(FillGap, &mu);
    map_threads["fillgap_2"] = std::thread(FillGap_2, &mu);


    for (auto iter = map_threads.begin(); iter != map_threads.end(); iter++){
        if (iter -> second.joinable()){
            iter -> second.join();
        }
    }
}

//====== 134 =====
//This is to test the performance of lock_guard and atomic operations and the later is faster
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include <atomic>

class Timer{
    private:
        std::chrono::high_resolution_clock::time_point counts_start, counts_end;
    public:
        //use functor to record the time stamp
        void operator () (std::string phase){
            if (phase == "start"){
                counts_start = std::chrono::high_resolution_clock::now();
            }else if (phase == "end"){
                counts_end = std::chrono::high_resolution_clock::now();
            }
        }

        void show_time(){
            std::cout << "The time duration is " << std::chrono::duration_cast<std::chrono::milliseconds> (counts_end - counts_start).count() << " milliseconds\n";
        }

};

std::mutex mu;

template <typename T>
void Task_thread(T &sum, int n, bool set_mutex = false){
    for (int i = 0; i < n; i++){
        //mu.lock();
        if (set_mutex){
            std::lock_guard<std::mutex> lock(mu);
            sum ++;
        } else{
            sum ++;
        }
        //mu.unlock();
    }
}

std::atomic<int> atomic_sum(0);
void Task_thread_atomic(int n){
    for (int i = 0; i < n; i++){
        atomic_sum ++;
    }
}

int main(){
    int n = 400000000;
    int sum = 0;
    Timer timer;

    timer("start");
    Task_thread<int>(sum, n);
    timer("end");
    
    std::cout << "_____ total sum ____\n";
    timer.show_time();
    std::cout << "sum = " << sum << std::endl;
   
    sum = 0; 
    timer("start");
    Task_thread<int>(sum, n/2);
    Task_thread<int>(sum, n/2);
    timer("end");
    std::cout << "_____total sum ____\n";
    timer.show_time();
    std::cout << "sum = " << sum << std::endl;

    sum = 0;
    std::thread two_thread[2];
    timer("start");
    two_thread[0] = std::thread(Task_thread<int>, std::ref(sum), n/2, false);
    two_thread[1] = std::thread(Task_thread<int>, std::ref(sum), n/2, false);
   
    for (auto & thread : two_thread){
        if (thread.joinable()){
            thread.join();
        }
    }
    timer("end");
    std::cout << "_____total sum (NO lock_guard<mutex>)____\n";
    timer.show_time();
    std::cout << "sum = " << sum << std::endl;

    sum = 0;
    //std::thread two_thread[2];
    timer("start");
    two_thread[0] = std::thread(Task_thread<int>, std::ref(sum), n/2, true);
    two_thread[1] = std::thread(Task_thread<int>, std::ref(sum), n/2, true);
    
    for (auto & thread : two_thread){
        if (thread.joinable()){
            thread.join();
        }
    }
    timer("end");
    std::cout << "_____total sum (lock_guard<mutex>)____\n";
    timer.show_time();
    std::cout << "sum = " << sum << std::endl;

    std::thread atomic_thread[2];
    timer("start");
    atomic_thread[0] = std::thread(Task_thread_atomic, n/2);
    atomic_thread[1] = std::thread(Task_thread_atomic, n/2);

    for (auto & thread : atomic_thread){
        if (thread.joinable()){
            thread.join();
        }
    }

    timer("end");
    std::cout << "_____total sum (atomic)____\n";
    timer.show_time();
    std::cout << "sum = " << atomic_sum << std::endl;
}

//============= 133 ===========
#include <chrono>
#include <iostream>
#include <thread>
#include <cmath>
#include <vector>


class Timer{
    private:
        std::chrono::high_resolution_clock::time_point counts_start, counts_end;
    public:
        void operator () (std::string phase){
            if (phase == "start"){
                counts_start = std::chrono::high_resolution_clock::now();
            }else if (phase == "end"){
                counts_end = std::chrono::high_resolution_clock::now();
            }
        }

        void duration(){
            std::cout << std::chrono::duration_cast<std::chrono::milliseconds> (counts_end - counts_start).count() << std::endl;
        }
};

void thread_task(int n){
    int sum = 0;
    for (int i = 0; i < n; i++){
        sum += std::pow(-1, i)*i;
    }
}

int main(){
    Timer timer;
    timer("start");
    std::this_thread::sleep_for(std::chrono::seconds(0));
    timer("end");
    timer.duration();

    timer("start");
    thread_task(20000000);
    thread_task(20000000);
    timer("end");
    timer.duration();

    std::vector<std::thread> my_threads;

    timer("start");
    my_threads.push_back(std::thread(thread_task, 20000000));
    //my_threads[0].join(); // allow the threads to execute in parallel 
    my_threads.push_back(std::thread(thread_task, 20000000));


    for (auto & thread : my_threads){
        if (thread.joinable())
            thread.join();
    }
    timer("end");
    timer.duration();
}

//=========== 132 ===========
//This is to practice high_resolution_clock
#include <iostream>
#include <chrono>
#include <thread>

int main(){
    std::cout << "The system ticks " << std::chrono::high_resolution_clock::period::den << " times per second\n";
    auto cycles_per_second = std::chrono::high_resolution_clock::period::den;
    
    auto start_count = std::chrono::high_resolution_clock::now(); 
    std::this_thread::sleep_for(std::chrono::seconds(2));
    auto end_count = std::chrono::high_resolution_clock::now();
    
    auto counts = (end_count - start_count).count();
    
    std::cout << "In 2 seconds, the systems ticks " << counts << " times\n";
    auto dur_seconds = std::chrono::duration_cast<std::chrono::seconds> (end_count - start_count).count();
    std::cout << "duration " << dur_seconds << "s\n";
    
    std::cout << "duration " << std::chrono::duration_cast<std::chrono::milliseconds>(end_count - start_count).count() << "millisec\n";
}


//===== 131 =====
//This is to practice jonable before joining or detaching a thread
#include <iostream>
#include <thread>
#include <fstream>
#include <chrono>

void print (std::string name, int n){
    std::ofstream f("txt");
    for (int i = 0; i < n; i++){
        f << name << ": " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
}

int main(){
    std::thread print_thread(print, "print_thread", 100000);
    
    std::this_thread::sleep_for(std::chrono::microseconds(5000));
    if (print_thread.joinable()){
        print_thread.detach();
    }
    //print_thread.join();
}

//====== 130 =====
#include <iostream>
#include <thread>

class P{
    public:
        void operator ()(std::string name){
            std::cout << name << ": " << std::this_thread::get_id() << std::endl;
        }
};

int main(){
    P p;
    //functor 
    std::thread pthread(p, "pthread"); //does not need to be (p) or (P())
    pthread.join();
}

//===== 129 ======
//This is to practice how to call functions inside a class for multithreading contexts
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

std::mutex mu;

void print (std::string);

class P{
    public:
        static void static_func(std::string name){
            print (name);
        }
        void non_static_func(std::string name){
            print (name);
        }
};

void print (std::string name){
    std::lock_guard<std::mutex> lock (mu);
    std::cout << name << ": " << std::this_thread::get_id() << std::endl;
}

int main(){
    std::vector<std::thread> task_thread;
    // calling a static function in a class
    task_thread.push_back(std::thread(&P::static_func, "static"));
    //calling a non-static function in a class
    task_thread.push_back(std::thread(&P::non_static_func, new P, "non_static"));
   
    //join or detach the threads created
    for (auto iter = task_thread.begin(); iter != task_thread.end(); iter++){
        //(*iter).join();
        iter -> join();
    }
}

//====== 128 =====
#include <iostream>
#include <fstream>
#include <mutex> 
#include <thread>

class LogFile{
    private:
        std::ofstream f;
        std::mutex mu;
    public:
        LogFile(std::string file_name){
            f.open(file_name);
        }
        void write_to_file(std::string msg, int n){
            for (int i = 0; i < n; i++){
                std::lock_guard<std::mutex> lock(mu);
                f << msg << ": " << i << " " << std::this_thread::get_id() << std::endl;
            }
        }
};

void ThreadLog(LogFile &log, std::string msg, int n){ // pass by reference
    log.write_to_file(msg, n);
}

int main(){
    LogFile log("log");

    //std::thread my_thread(log.write_to_file, "\tbranch", 3000); //compiling error!!!
    std::thread my_thread(ThreadLog, std::ref(log), "\tbranch", 3000); // in thread, pass by reference should use std::ref()

    log.write_to_file("main", 3000);

    my_thread.join();
}

//==== 127 ======
//write to a file 
#include <fstream>
int main(){
    std::ofstream f;
    f.open("txt");
    f << "love\n";
}

//===== 126 =====
//This is to practice data racing in multithreading context
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex mu;

class Task{
    public:
        void operator ()(std::string msg, int n){
            for (int i = 0; i < n; i++){
                //lock_guard get destroyed when out of scope
                {
                    //ensure only thread is executing this line of code
                    std::lock_guard<std::mutex> guard (mu);
                    //mu.lock();
                    std::cout << msg << std::this_thread::get_id() << ": " << i << std::endl;
                    //mu.unlock();
                }
                std::this_thread::sleep_for(std::chrono::nanoseconds(1));
            }
        }
};

class SmartThread{
    private:
        std::thread my_thread;
    public:
        SmartThread(int _n){
            this -> my_thread = std::thread(Task(), "Task thread ", _n);
        }
        ~SmartThread(){
            this -> my_thread.join();
            std::cout << std::this_thread::get_id() << " got destroyed\n";
        }
};

int main(){
    int n = 200;
    SmartThread st(n);
    Task main_task;
    main_task("\tMain thread ", n);

    //std::cout <<"main thread " << std::this_thread::get_id() << std::endl;
}

//===== 125 ====
//This is to enhance my understanding of copying assignment of class returned by a function
#include <iostream>

class P{
    public:
        P & operator = (const P &p){
            std::cout << "copy assignment\n";
            return *this;
        }
};

P copy(){
    P p;
    return p;
}
int main(){
    P p, p1;
    std::cout << "___\n";
    p1 = p;
    std::cout << "___\n";
    p1 = copy();
    std::cout << "___\n";
    copy();
}

//====== 124 =======
//This is to practice copy constructor and copy assignment
#include <iostream>

class P{
    private:
        int age;
        std::string name;
        std::string * ptr_gender; // make sure the object pointed to by ptr_gender is created first
    public:
        P(int _age = -100, std::string _name = "none", std::string _gender = "TBD"):
            age(_age), name(_name), ptr_gender(new std::string(_gender)){}

        //copy constructor
        P(const P &p){
            std::cout << "\tcopy constructor is being called\n";
            age  = p.age;
            name = p.name;
            //only copy the content
            ptr_gender = new std::string; //make sure the object pointed to by ptr_gender is created first
            *ptr_gender = "xx"; // *p.ptr_gender;
        }
        //copy assignment
        P & operator =(const P &p){
            std::cout << "\tcopy assignment is being called\n";
            if (this == &p)
                return *this;

            delete ptr_gender; // release any resources allocated before to this pointer
            age = p.age;
            name = p.name;
            *ptr_gender = "yy";
            return *this;
        }

        void Get(){
            std::cout << age << " " << name << " " << *ptr_gender << std::endl;
        }
};

int main(){
    P p1(30, "zls", "male");
    //P p2(p1);
    std::cout << "declaring and initializing\n";
    P p2 = p1; //only copy constructor when declaring and initializing it
    std::cout << "end of declaring and initializing\n";
    
    std::cout << "before assigning\n"; 
    p2 = p1;
    std::cout << "after assigning\n";
    p2.Get();
}

//===== 123 ====
//This is to test the std::move() semantics: for string, the variable being moved from is empty, but for int, it is not
#include <iostream>

int main(){
    std::string s = "hello";
    std::string arr[2];
    arr[0] = s;
    arr[1] = std::move(s);

    std::cout << arr[1] << std::endl;
    std::cout << s << std::endl; // the variable being moved from is now empty

    std::cout << "___________\n";

    double i = 2;
    double arri[2];
    arri[0] = i;
    arri[1] = std::move(i);
    std::cout << arri[1] << std::endl;
    std::cout << i << std::endl; // the variable being moved from still holds that value
}

//===== 122 ======
//This is enhance my understanding of std::thread::hardware_concurrency()
#include <iostream>
#include <thread>
#include <chrono>

void Task(int i){
    std::cout << std::this_thread::get_id() << ": " << i << std::endl;
}

int main(){
    int n = std::thread::hardware_concurrency();
    std::thread concurrent_threads[n];

    for (int i = 0; i < n; i++){
        concurrent_threads[i] = std::thread(Task, i);
        //concurrent_threads[i].join();
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));

    for (auto & thread : concurrent_threads){
        thread.detach();
    }
}

//===== 121 =====
//This is to practice hardware_concurrency()
#include <iostream>
#include <thread>

int main(){
    int num_cores = std::thread::hardware_concurrency();
    std::cout << num_cores << " concurrent threads are supported.\n";
}

//======== 120 =======
//This is to practice function in a thread function
#include <iostream>
#include <thread>
#include <chrono>

class P{
    public:
        void operator ()(int& n){
            for (int i = 0; i < n; i++){
                std::cout << std::this_thread::get_id() << " " << i << std::endl;
            }

            n = 200;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }

        ~P(){
            //std::thread::join();
        }
};

int main(){
    int n = 9;
    std::thread my_thread;
    my_thread = std::thread(P(), std::ref(n));
    
    //long enough for variable n to get modified 
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "\n\nFrom main (after) " << n << std::endl;
    std::cout << "before join\n";
    my_thread.join();
}

//======== 119 =========
//This is to enhance my understanding of functor
#include <iostream>
#include <chrono>
#include <thread>

class P{
    public:
        void operator ()(int i){
            int ind = 0;
            int secs = i/1000;
            while (secs - ind){
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                std::cout << "\t1 second\n";
                ind ++;
            }
            std::cout << "Done sleeping for " << secs << " seconds\n";
        }
};

int main(){
    P p;
    p(300);
}

//=========== 118 =======
//This is to practice () overloading, i.e. functor
#include <iostream>

class P{
    private:
        int age;
    public:
        P& operator () (int _age){
            this -> age = _age;
        }
        void Get(){
            std::cout << "age: " << this -> age << std::endl;
        }
};

int main(){
    P p;
    p(2);
    p.Get();
    p(5);
    p.Get();
}

//============ 117 =========
//This is to enhance my understanding of assignment operator overloading'
#include <iostream>

class P{
    private:
        int age;
        double height;
        std::string * name;
        int *num;
    public:
        P(int _age = -11, double _height = -200, std::string _name = "daemon", int _num = 5): age(_age), height(_height), name(new std::string (_name)), num(new int (_num)) {
            std::cout << "done constructing\n"; 
        }

        void Get_age(){
            std::cout << this -> age << std::endl;
        }
        void Get_height(){
            std::cout << this -> height << std::endl;
        }
        void Get_name(){
            std::cout << * this -> name << " " << this -> name << std::endl;
        }
        void Get_num(){
            std::cout << * this -> num << " " << this -> num << std::endl;
        }

        P & operator = (const P &p){
            std::cout << "assignment operator overloading\n";
            if (this != &p){
                this -> age = p.age; //-100;
                this -> height = p.height; //-300;
                //for pointers, we only want to copy the values, not the address
                // *this -> name = *p.name; //"default";
            }
            //without the above operations, this will just be the default setup
            //with the above operations, the original setup is modified
            return * this;
        }
};

int main(){
    P p(30, 180, "zls", 9); // calling constructor
    p.Get_age();
    p.Get_height();
    p.Get_name();
    p.Get_num();

    std::cout << "______________\n";
    //it is not constructing an object from scratch, but just copying data members from another object, so not calling constructor. Also it is not calling assignment operator overloading.
    P p2 = p; // it is not calling constructor or assignment operator overloading
    p2.Get_age();
    p2.Get_height();
    p2.Get_name();
    p2.Get_num();

    std::cout << "____________\n";
    P p3; // calling constructor, initializing including creating new pointers
    p3 = p; // calling assignment operator overloading, overriding the original data members 
    p3.Get_age();
    p3.Get_height();
    p3.Get_name();
    p3.Get_num();
}


//======== 116 =======
//This is to practice assignment operator overloading when there is a pointer member in the class
#include <iostream>

class Person{
    private:
        std::string addr;
        int *age; //has to be initialized when constructing an object
    public:
        Person(std::string _addr="earth_default"): addr(_addr), age(new int(-1)){}
        void Get_addr(){
            std::cout << addr << std::endl;
        }
        void Set_addr(std::string addr){
            this -> addr = addr;
        }

        void Set_age(int age){
            *(this -> age) = age;
        }
        void Get_age(){
            std::cout << *(this -> age) << " " << this -> age << std::endl;
        }

        Person & operator =(const Person & p){
            //if (*this != p)
            //if (this != &p)
            //   *(age) = *p.age;
            //without this line, age pointer points to a different address in constructor.
            this -> age = p.age; // this line ensures whenever there is an assignment operator, the age pointer points to the same address
            return * this;
        }
};

int main(){
    Person p1;
    p1.Get_addr();

    Person p2("china");
    p2.Get_addr();

    Person p3;
    p3 = p2;
    p3.Get_addr();
    p3.Set_addr("CH");
    p3.Get_addr();
    p2.Get_addr();

    p1.Set_age(30);
    p1.Get_age();

    //p2.Set_age(40);
    p2.Get_age();
    p2.Set_age(23);
    p3.Get_age();

    Person p4 = p2;
    p4.Get_age();
}

//======= 115 =======
//This is to test pass by value or reference in thread function
#include <iostream>
#include <thread>
#include <chrono>

void Task(int &a){
    a = 3;
}

int main(){
    int a = 2;
    std::thread my_thread(Task, std::ref(a)); //by default pass by value. To use by reference, use std::ref()
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << a << std::endl;
    my_thread.join();
}

//======== 114 =======
//since we have to join or detach a child thread before it goes out of scope, we can wrap it
#include <iostream>
#include <thread>

void f(int n){
    for (int i = 0; i < n; i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(i));
    }
}
class SmartThread{
    private:
        std::thread sm_thread;
    public:
        SmartThread(){}
        SmartThread(int n){
            sm_thread = std::thread(f, n);
        }

        ~SmartThread(){
            sm_thread.join();
        }
};

int main(){
    SmartThread st(3);
    //st = SmartThread(3); //since std::thread is not copiable, we can not copy another class object to another
}

//======= 113 ======
//This is test if we can spawn one child thread inside another child thread
#include<iostream>
#include <thread>
#include <chrono>

void Second_Thread();

void First_Thread(){

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << std::this_thread::get_id() << " slept for 1 second" << std::endl;

    std::thread second_thread(Second_Thread);

    second_thread.detach();
}

void Second_Thread(){
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << std::this_thread::get_id() << " slept for 1 second" << std::endl;
}

int main(){
    int n_sec = 2;
    int n_millisec = 3;
    std::thread first_thread(First_Thread);
    first_thread.detach();

    std::this_thread::sleep_for(std::chrono::seconds(n_sec) + std::chrono::milliseconds(n_millisec));
    std::cout << std::this_thread::get_id() << " slept for " <<  n_sec << " seconds " << n_millisec << " milliseconds\n";
}


//====== 112 =======
//This is to test a feature of class
#include <iostream>

class P{
    public:
        int i;
        P() = default;
        P(int i){
            this -> i = i;
        }
};

void Get(); // it is a function declartion

int main(){
    //P p(); // treated as a funciton declaration
    P p;
    std::cout << p.i << std::endl; // random number?
    p = P(); // default value?
    std::cout << p.i << std::endl;
    p = P(2);
    std::cout << p.i << std::endl;
}

//====== 111 =======
//if the child thread is detached from the main thread and the main thread exits before the child thread, the child thread will still run to the end
#include <iostream>
#include <thread>
#include <chrono>

void Task(){
    int n = 3;
    std::cout << "Beginning of the task " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(n));
    std::cout << "End of the task after " << n << " seconds.\n";
}

void Initiate_thread(){
    std::thread my_thread;
    my_thread = std::thread(Task);
    my_thread.detach();
    //my_thread.join();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << std::this_thread::get_id() << " after 1 second.\n";
}

int main(){
    int n = 1;
    Initiate_thread();
    std::this_thread::sleep_for(std::chrono::seconds(n));
    std::cout << std::this_thread::get_id() << " after " << n << " seconds.\n";
}


//===== 110 ======
//This is to practice thread take a function with arguments
#include <iostream>
#include <thread>
#include <chrono>

void Task(int i){
    std::cout << "Thread: " << std::this_thread::get_id() << ", " << i << std::endl;
}

int main(){
    std::thread my_threads[3] = {std::thread(Task, 0), std::thread(Task, 1), std::thread(Task, 2)};
    //my_threads[0] = std::thread(Task, 0);
    
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    for (auto & thread : my_threads){
        //thread.join(); // the main thread will waits for the child thread to finish
        thread.detach(); // the child thread is separated from the main thread, and it will execute independently
    }
}


//====== 109 ====
//This is to practice thread
#include <iostream>
#include <thread>
#include <chrono>
//#include <unistd.h> // for sleep()

static bool reached = false;
void Task(){
    int i = 1;
    while(! reached){
        std::cout << "In the task " << i << "\n";
        i ++;
        //sleep (.9);
        //std::this_thread::sleep_for(std::chrono::seconds(1));
        //std::this_thread::sleep_for(std::chrono::milliseconds(500));
        //std::this_thread::sleep_for(std::chrono::microseconds(500000));
        std::this_thread::sleep_for(std::chrono::nanoseconds(500000000));
    }
}

int main(){
    std::thread task_thread (Task);
    //sleep(2);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "In main thread, reached is set to true\n";
    reached = true;
    task_thread.join();
    //task_thread.detach();
}

//===== 108 =====
// this is to practice -> overloading
#include <iostream>

template <typename T>
class SmartPointer{
    private:
        T *ptr;
    public:
        SmartPointer(T *_ptr){
            ptr = _ptr;
        }
        ~SmartPointer (){
            delete ptr;
        }

        T * operator -> (){
            return ptr;
        }
};

int main(){
    std::string s = "hello", *ptr_s;
    ptr_s = &s;
    std::cout << s.size() << std::endl;
    std::cout << ptr_s -> size() << std::endl;

    std::cout << "_______\n";
    ptr_s = new std::string("hi");
    SmartPointer<std::string> sp (ptr_s); // (new std::string ("hi"));
    std::cout << sp -> size() << std::endl;
}

//====== 107 ====
//This is to practice assign a value to a function
#include <iostream>

int & assign_int(){
    static int a=-1;
    std::cout << a << std::endl;
    return a;
}

double & assign_double(double & d){
    return d;
}

int main(){
    assign_int() = 3;
    
    assign_int();

    std::cout << "______\n";
    double d = 9;
    assign_double(d) = 22;
    std::cout << d << std::endl;
}


//==== 106 ====
//This is to implement smart pointers which automatically handles freeing memory when out of scope
#include <iostream>

template <typename T>
class SmartPointer{
    private:
        T *ptr;
    public:
        SmartPointer(T *ptr){
            this -> ptr = ptr;
            std::cout << "Created\n";
        }
        ~SmartPointer(){
            if (this -> ptr){
                delete this -> ptr;
            }
            std::cout << typeid(ptr).name() <<  " is destroyed\n";
        }

        // operator overloading
        // return a reference, not just a value
        T &operator * (){ // prefix 
            return * (this -> ptr);
        }

        T Get(){
            return *this -> ptr;
        }
};

int main(){
    //creates a new scope
    {
        SmartPointer<int> i(new int);
        SmartPointer<std::string> s (new std::string);
    }
    //outside of the scope
    std::cout << "out of scope\n";

    std::cout << "________\n";
    SmartPointer<double> d(new double);
    *d = 2.3; //since this operator returns a reference, we can assign a value to that memory location
    std::cout << *d << " " << d.Get() << std::endl;
}

//====== 105 =======
//This is to test struct and class templates
#include <iostream>

template<typename T> class Person;

struct Get{
    private:
        //Person<Get> p; // Person is not defined yet
        Person<Get>;
    public:
        void get();
};

template<typename T>
class Person{
    private:
        void Get(){
            std::cout << "Person\n";
        }
    public:
        friend T;
};

void Get::get(){
    Person <Get> p;
    p.Get();
}

int main(){
    Get g;
    g.get();
}


//==== 104 ===
// a template class can be a friend of another class for all its instances, or just a few specific instances are its friends
#include <iostream>

template <typename T> 
class F1;

class PPerson;

class Person{
    private:
        void Get(){
            std::cout << "Person private method\n";
        }
    public:
        friend class F1<Person>; //only Person- and PPerso-F1 are its friends, other type-F1 classes are not its friends
        friend class F1<PPerson>;
        template <typename T> friend class F2; //all F2 classes are its friends
};

template <typename T>
class F1{
    public:
        void Get(T & p){
            p.Get();
        }
        void Getp(){
            Person p;
            p.Get();
        }
};

template<typename T>
class F2{
    public:
        void Get(){
            Person p;
            p.Get();
        }
};

class PPerson{
    private:
        //friend class F1<PPerson>;
        void Get(){
            std::cout << "PPerson private method\n";
        }
};

int main(){
    F1<Person> f1;
    f1.Get(*(new Person));
    std::cout << "_____\n";
    F1<PPerson> f2;
    //f2.Get(*(new PPerson)); //private and not a friend, so can not access it
    f2.Getp();

    std::cout << "_____\n";
    F2<int> f3;
    f3.Get();
    F2<double>f4;
    f4.Get();
    F2<F1<int>> f5;
    f5.Get();
}


//==== 103 ====
//if T is a customized class type, then "friend T" works to set class T as a friend class
#include <iostream>

template<typename T>
class Person{
    public:
        friend T;
    private:
        void Get(){
            std::cout << "Person\n";
        }
};

class GetPerson{
    public:
        void Get(Person<GetPerson> &p){
            p. Get();
        }
};

int main(){
    GetPerson getp;
    getp.Get(*(new Person<GetPerson>));
    Person<GetPerson> p;
    getp.Get(p);
}

//===== 102 =====
//This is to practice template friend class within a non-template class
#include <iostream>

template<typename T>
class GetPerson;

class Person{
    private:
        int age = 30;
        friend class GetPerson<Person>; //only Person-type GetPerson class is Person's friend class
};

class PPerson{
    private:
        std::string age = "string: 30";
        template <typename T> friend class GetPerson;
};

template<typename T>
class GetPerson{
    public:
        void Get(T &p);
};

template<typename T>
void GetPerson<T>::Get(T &p){
    std::cout << p.age << std::endl;
}

int main(){
    Person p;
    PPerson pp;
    GetPerson<Person> getp;
    getp.Get(p);
    //getp.Get(pp); //getp only works for Person class, not PPerson class
    GetPerson<PPerson> getpp;
    getpp.Get(pp);
}

//====== 101 =====
//This is to test the friend class
#include <iostream>

template<typename T>
class Friend;

template <typename T>
class Person{
    private:
        T name;
        template<typename TT> friend class Friend;
    public:
        Person(T _name);
};

template<typename T>
Person<T>::Person(T _name){
    name = _name;
}
template <typename T>
class Friend{
    public:
        void Get(Person<T> &p){
            std::cout << p.name << std::endl;
        }
};

int main(){
    Person<std::string> p("zls");
    Friend<std::string> f;
    f.Get(p);

    Person<int> p2(23);
    //f.Get(p2); // as template parameters do not match, they are not friends
}

//===== 100 ====
//A friend class which take a template class as an argument, then the friend class has to be template a class
#include <iostream>

template <typename T, int N>
class Person{
    private:
        T Gender[N];
        template<typename TT, int NN> friend class GetPerson; //has to be different T and N
    public:
        Person(T _a, T _b, T _c); //: Gender({_a, _b, _c}){}; // not valid in clang on mac
        void Get(){
            std::cout << Gender << std::endl; // in c++, array name represents the location of the array
        }
};

template <typename T, int N>
Person<T, N>::Person(T _a, T _b, T _c){ //: Gender({_a, _b, _c}){
    Gender[0] = _a;
    Gender[1] = _b;
    Gender[2] = _c;
}

template<typename T, int N>
class GetPerson{
    public:
        void Get(Person<T, N> &p){
            for (auto ele : p.Gender){
                std::cout << ele << " ";
            }
            std::cout << std::endl;
        }
};

int main(){
    Person<std::string, 3> p1 ("male", "female", "transgender");
    GetPerson<std::string, 3> getp;
    getp.Get(p1);
    p1.Get();
}


//========= 99 ========
//virtual polymorphism only works in pointer case, not by reference
#include <iostream>

class Base{
    public:
        virtual void Get(){
            std::cout << "Base\n";
        }
        void Get_1(){
            std::cout << "base get_1\n";
        }
};

class Derive:public Base{
    public:
        void Get() override{
            std::cout << "Derive\n";
        }
        void Get_1(){
            std::cout << "derive get_1\n";
        }
};

void Get(Base & b){
    b.Get();
    //b -> Get();
}

int main(){
    Derive d;
    Get(d);

    Base *ptr = &d;
    ptr -> Get();

    std::cout << "___________\n";
    ptr = static_cast<Base *> (&d); //pointer points to correct virtual function
    ptr -> Get();
    ptr -> Get_1();
    
    std::cout << "___________\n";
    Base b = static_cast<Base &> (d); //reference does not refer to the correct virtual function
    b . Get();
}

//====== 98 =====
//pure virtual class can not be instantiable
#include <iostream>

class Person{
    protected:
        std::string name;
    public:
        Person(std::string _name): name(_name){}
        virtual void Get(){
            std::cout << "Person\n";
        }
};

class Friend: public Person{
    private:
        int age;
    public:
        Friend(std::string _name, int _age): Person(_name), age(_age){}
        void Get() override{
            std::cout << "name: " << name << ", age: " << age << std::endl;
        }
        void xx(){
            std::cout << age << " ";
            std::cout << "Friend\n";
        }
};

int main(){
    Friend f1("dsy", 32);
    Person *p = dynamic_cast<Person *> (&f1);
    p -> Get();
    // one of the difference between static_cast and dynamic_cast is that dynamic_cast guarantees the usage of the virtual function in the derived class
    //p -> xx(); //xx() is not in Person class.

    Person pr = dynamic_cast<Person &> (f1);
    pr . Get();

    Friend *pf = dynamic_cast<Friend *> (p);
    pf -> Get();
    pf -> xx(); // after converting pointer p to Friend class, it can access xx() function
    std::cout << "_________\n";

    Friend pp = dynamic_cast < Friend &> (*p); // *p not p
    pp.xx();
}


//======= 97 =======
//This is to practice class templates and inheritence
#include <iostream>

class Person{
    public:
        virtual void Get() = 0;
};

template <typename T, typename U>
class PlanetPerson: public Person{
    private:
        T name;
        U age;
    public:
        static int num_of_planetperson;
        PlanetPerson(T _name, U _age): name(_name), age(_age){num_of_planetperson++;}
        void Get() override;
};

template<typename T, typename U>
int PlanetPerson<T, U>:: num_of_planetperson = 0;

template<typename T, typename U>
void PlanetPerson<T, U>::Get(){
    std::cout << "name typeid " << typeid(T).name() << ": " << name;
    std::cout << "; ";
    std::cout << "age typeid " << typeid(U).name() << ": " << age << std::endl;
}

void Get_Person(Person * p){
    p -> Get();
}

void Get_Person(Person &p){
    p.Get();
}

template<typename T, typename U>
class EarthCountry: public PlanetPerson<T, U>{
    private:
        T country_name;
    public:
        static int num_of_countries;
        EarthCountry(T _pname, U _page, T _cname): PlanetPerson<T, U>(_pname, _page),  country_name(_cname){num_of_countries ++;}

};

template<typename T, typename U>
int EarthCountry<T, U>:: num_of_countries = 0;


int main(){
    PlanetPerson<std::string, int> earth ("Earth", 300000);
    //earth.Get();
    Get_Person(static_cast<Person *> (&earth));
    Get_Person(static_cast<Person &> (earth));
    
    std::cout << "___________\n";
    PlanetPerson<double, float> mars (2.3, 4.6f);
    Get_Person(static_cast<Person &> (mars));

    std::cout << "__________\n";

    EarthCountry<std::string, int> china ("earth", 30, "china");
    china.Get();
    std::cout << china.num_of_planetperson << std::endl;
    std::cout << mars.num_of_planetperson << std::endl;
    std::cout << china.num_of_countries << std::endl;
}

//========= 96 =======
//class template
#include <iostream>

template<typename T, int N>
class Family{
    private:
        T members[N];
        static int num_of_families;
    public:
        Family(){num_of_families ++;}
        Family(T _a): members({_a}){num_of_families ++;}
        Family(T _a, T _b): members({_a, _b}){num_of_families ++;} 

        T * Get();

        static void Get_numoffamilies();
};

template <typename T, int N>
void Family<T, N> :: Get_numoffamilies(){
    std::cout << Family::num_of_families << std::endl; // inside the class/function, the template parameters are not required
}

template <typename T, int N>
int Family<T, N>::num_of_families = 0;

template<typename T, int N> 
T* Family<T, N>::Get(){
    return members;
}

int main(){
    const int N = 2;
    Family<std::string, N> f1("parent", "son");

    std::string *ptr = f1.Get();
    for (int i = 0; i < N; i++){
        std::cout << *ptr << " ";
        ptr++;
    }
    std::cout << std::endl;

    f1.Get_numoffamilies();
    Family<std::string, N>::Get_numoffamilies();
    Family<std::string, 1>::Get_numoffamilies();
    Family<std::string, 2>::Get_numoffamilies();
    Family<int, 2>::Get_numoffamilies();
    //Family::Get_numoffamilies(); // has to specify the tempalte parameters
}

//======= 95 ======
//This is to practice function template
#include <iostream>
#define PI 3.141592653

template <typename T>
void Get(T a){
    std:: cout << "type " << typeid(T).name() << ": " <<  a << std::endl;
}

template <typename T, typename U>
U Get(T a){
    return static_cast<U> (a);
}

//templates can also be for variables
template <int N>
void SetArray(){
    double arr[N];
    for (int i = 0; i < N; i++){
        arr[i] = PI * i;
    }

    for (auto ele : arr)
        std::cout << ele << " ";
    std::cout << std::endl;
}

template <typename T, int N>
void SetArray(){
    T arr[N];
    for (int i = 0; i < N; i++){
        arr[i] = PI*i;
    }

    for (auto ele:arr){
        std::cout << ele << " ";
    }
    std::cout << std::endl;
}

int main(){
    Get(2);
    Get<int> (3);
    Get<double>(3.2);
    Get<float>(2.3f);

    std::cout << "___________\n";
    std::cout << Get<double, int> (2.3) << std::endl;
    Get<double> (2.3);

    std::cout << "___________\n";
    SetArray<4> ();

    std::cout << "____________\n";
    SetArray<int, 4>();
    SetArray<float, 5> ();
}

//===== 94 ====
//this is to study this pointer
#include <iostream>

class P{
    public:
        int a = 3; // the size of an instance
        int Get_This(){
            std::cout << "This object is at " << this << std::endl;
            std::cout << sizeof(this) << std::endl;
            return 3;
        }
};

int main(){
    P p, *ptr;
    int *ptr_i;
    double *ptr_d;
    p.Get_This();
    std::cout << sizeof(p) << " " << sizeof(ptr) << std::endl; //if no member data, then size is 1, otherwise the sum of all member data
    std::cout << sizeof(ptr_i) << " " << sizeof(ptr_d) << std::endl;
}

//===== 93 ====
//This is to practice [] operator overloading
#include <iostream>
class Person{
    private:
        std::string name;
        int age;
        std::string gender;
    public:
        Person(std::string _name, int _age, std::string _gender): name(_name), age(_age), gender(_gender){}
        std::string operator [](int i){
            if (i == 0){
                return name; 
            } else if (i == 1) {
                return std::to_string(age);
            } else if (i == 2) {
                return gender;
            }
            return "error";
        }
};

int main(){
    Person me("zls", 30, "male");
    std:: cout << me[0] << " " << me[1] << " " << me[2] << std::endl;
}
//========== 92 ==========
//This is to practice operator overloading
#include <iostream>

struct Me{
    private:
        int age;
    public:
        Me(int _age):age(_age){}
        void operator +(int a) {
            age += a;
        }
        void Get_Age(){
            std::cout << this -> age << std::endl;
        }
        static int num;
        void operator ++(){
            num++;
        }
        void operator --(){
            std::cout << "my age: " + std::to_string(age) << std::endl;
        }

        //operator float() {
        //    std::cout << "age: " + std::to_string(age) << std::endl;
        //}
};

int Me::num = 0;

int main(){
    Me me(30);
    me+2;
    me.Get_Age();
    ++ me;
    std::cout << me.num << std::endl;

    std::cout << "23"+std::to_string(23) << std::endl;

    --me;
    //long int a = me; // not sure what this is going on
}

//========= 91 ========
//operator overloading for user defined types
#include <iostream>
#include <cmath> //pow(base, exponent)

class Complex;
class Multiply{
    public:
        Complex xx (const Complex & o1, const Complex & o2);
};
class Complex{
    private:
        int real, imagine;
    public:
        Complex(int r, int i):real(r), imagine(i){}
        void Get(){
            std::cout << real << " + i" << imagine << std::endl;
        }
        //operator overloading function is just like regular functions but with operator keyword before the name 
        Complex operator + (const Complex & another) const{ // const function
            Complex c(real + another.real, imagine + another.imagine);
            return c;
        }
        friend Complex operator - (const Complex & obj1, const Complex & obj2);
        friend Complex Multiply::xx(const Complex &, const Complex &);

        void operator ++ (int){ // the argument must be int
            std::cout << "postfix\n";
            real += 2;
            imagine ++;
        }
        void operator --(){
            std::cout << "prefix\n";
            real--;
            imagine--;
        }

        friend Complex operator * (const Complex & obj1, const Complex & obj2);

        bool operator > (const Complex & obj){
            if (pow(real, 2)+pow(imagine, 2) > pow(obj.real, 2)+pow(obj.imagine, 2)){
                return true;
            }else{
                return false;
            }
        }

};

Complex operator *(const Complex & obj1, const Complex & obj2){
    return Complex(obj1.real*obj2.real, obj1.imagine*obj2.imagine);
}

Complex operator -(const Complex & obj1, const Complex & obj2){
    return Complex(obj1.real-obj2.real, obj1.imagine-obj2.imagine);
}

Complex Multiply::xx(const Complex & o1, const Complex & o2){
    return Complex(o1.real*o2.real, o1.imagine*o2.imagine);
}


int main(){
    Complex c(2, 3), d(4, 5);
    c.Get();
    Complex e = c + d;
    e.Get();

    Complex f = c-d;
    f.Get();

    Multiply mul;
    Complex g = mul.xx(c, d);
    g . Get();

    std::cout << "________\n";
    c.Get();
    c++; //only prefix, how to do postfix
    c.Get();
    --c;
    c.Get();
    
    std::cout << "________\n";
    (c+d).Get();
    c.Get();
    (c-d).Get();
    Complex h = (c+d)*(c-d);
    h.Get();

    std::cout << "_________\n";
    std::cout << (c > d) << std::endl; 
}

//========= 90 ========
//This is to practice typeid
#include <iostream>

class Me{
};

struct P{};

int main(){
    int *i;
    double j;
    float *f;
    std::cout << typeid(i).name() << std::endl;
    std::cout << typeid(j).name() << std::endl;
    std::cout << typeid(f).name() << std::endl;

    Me me, *p_me;
    P you, *p_you;
    std::cout << typeid(me).name() << "; " << typeid(p_me).name() << std::endl;
    std::cout << typeid(you).name() << "; " << typeid(p_you).name()  << std::endl;
    std::cout << typeid(&me).name() << std::endl;

    if (typeid(&me).name() == typeid(p_me).name()){
        std::cout << "same type of varibales\n";
    }

    if (typeid(j).name() != typeid(i).name()){
        std::cout << "different types of variables\n";
    }
}

//========= 89 ========
//This is to overview function overloading
#include <iostream>

void Get(double i, int j){
    std::cout << "void Get(int i, double j)\n";
}

void Get(double i, double j){
    std::cout << "void Get(double i, double j)\n";
}

void Get(int i){
    std::cout << "void Get(int i)\n";
}

//redefine the previous function, not allowed
//void Get(const int i){
//    std::cout << "void Get(const int i)\n";
//}

class Me{

};


void Get(Me &me){
    std::cout << "void Get(Me &me)\n";
}
int main(){
    Get(3, 3.3);
    Get(3.0, 3.3);
    Get(2);
    Me me;
    Get(me);
}

//====== 88 =====
//default values in the arguments might cause ambiguity
#include <iostream>

void Get(int i = 0){
    std::cout << "void Get(int i = 0)\n";
}

void Get(){
    std::cout << "void Get()\n";
}

int main(){
    Get(); // ambiguous
}

//========== 87 ======
//This is to practice function overloading
#include <iostream>

void Get(){
    std::cout << "void Get\n";
}

int Get(){
    return 2;
}

int main(){
    // overloading can not be distinguished by the return type
    // ambiguating the Get() function
    int a = Get();
}

//===== 86 =====
//this is to practice const
#include <iostream>

int main(){
    int a = 2;
    int * const ptr=&a; // const pointer has to be initialized
    *ptr = 32; // it has to be int, not other types
    std::cout << a << std::endl;
    int b;
    //ptr = &b; // can not change the value of const pointer
}

//==== 85 ====
//This is to practice const functions
#include <iostream>

//void Get() const{ // To be a const function, it must be a member function of a class/struct
void Get_out(){
    std::cout << "Get\n";
}

class Me{
    private:
        int a = 2;
    public:
        static int stat;
        void Get() const{
            std::cout << "Get() " << this -> a << "\n";
            //a ++; // can not modify regular data member
            stat ++; // can modify static member data
            std::cout << "\tstat: " << this -> stat << std::endl;
            //this -> Name(); // Name has to be const to be called in a const member function
            Get_out(); // but can call whatever non member functions
        }
        void Name(){
            std::cout << "Name\n";
        }
        static void Get_stat(){
            std::cout << stat << std::endl;
            //std::cout << a << std::endl; // can only access static members
        }
};

int Me::stat = 3;

int main(){
    Get_out();

    Me me;
    me.Get();
    std::cout << Me::stat << std::endl; //static member belongs to class itself
    Me::Get_stat();
    //Me::Name(); // need an object
}
//===== 84 ====
//static/dynamic_cast<>(): for non-virtual functions, use the ones in the casted-type, otherwise the ones in the actual object; dynamic_cast only works if the casted-type is in the upper inheritence level of the acutal class
#include <iostream>
class Fake{
    public:
        virtual void Get(){
            std::cout << "Fake\n";
        }
};
class Base: public Fake{
    public:
        void get(){
            std::cout << "Base get()\n";
        }
        void Get(){
            std::cout << "Base\n";
        }
};

class Derive: public Base{
    private: 
        int a = 9;
    public:
        void Get(){
            std::cout << "Derive\n";
        }
        void DeriveOnly(){
            std::cout << "DeriveOnly\n" << this -> a << std::endl;
        }
};

int main(){
    Fake *ptr_f = new Derive;
    ptr_f -> Get();
    //ptr_f -> get(); //Fake type does not have get()
    Base *ptr_b = dynamic_cast<Base *> (ptr_f);
    ptr_b -> Get();
    ptr_b -> get(); //Base type has get()
    Derive *ptr_d = dynamic_cast<Derive*> (ptr_f);
    ptr_d -> Get();
    ptr_d -> DeriveOnly();

    std::cout << "_____\n";
    ptr_b = new Base;
    ptr_d = static_cast<Derive*> (ptr_b);
    //ptr_d = dynamic_cast<Derive*> (ptr_b); // won't work as the object which is pointed by ptr_b is just Base type, which does not inherit from Derive, and it is quite the opposite
    ptr_d -> Get(); //for virtual functions, they are always referred to the ones in the actual object, not the pointer type
    ptr_d -> get();
    ptr_d -> DeriveOnly();
    delete ptr_b;
}

//====== 83 =====
//A *ptr_a = new derive; dynamic_cast <derive_ptr or one_of_its_parent_ptr> (ptr_a);
#include <iostream>

class A{
    public:
        virtual void Get(){
            std::cout << "A\n";
        }
};

class B: public A{
    public:
        void Get() override {
            std::cout << "B\n";
        }
};

class C: public B{
    public:
        void Get() override {
            std::cout << "C\n";
        }
};

class D: public A{
    public:
        void Get(){
            std::cout << "D\n";
        }
};

int main(){
    A *ptr_a = new C;
    ptr_a -> Get();
    B *ptr_b = dynamic_cast<B*> (ptr_a);
    ptr_b -> Get();
    D *ptr_d = dynamic_cast<D*> (ptr_a);
    if (ptr_d){
        std::cout << "dynamic_cast succeeded\n";
    } else{
        std::cout << "dynamic_cast failed\n";
    }
    std::cout << "_____\n";
    ptr_a = new B; // the object is type B, so class C type pointer failed
    ptr_a -> Get();
    ptr_b = new B;
    ptr_b -> Get();
    C *ptr_c = dynamic_cast<C*> (new B); //weird
    ptr_c -> Get();
}

//======== 82 ========
//This is to distinguish teamates and opponents
#include <iostream>
#include <vector>

class Player{
    public:
        virtual void GetId() = 0;
};

class Teammates: public Player{
    public:
        void GetId() override{
            std::cout << "Teammates\n";
        }
};

class Opponents: public Player{
    public:
        void GetId() override{
            std::cout << "Opponents\n";
        }
};

int main(){
    std::vector <Player*> players;
    players.push_back(new Teammates);
    players.push_back(new Teammates);
    players.push_back(new Opponents);
    players.push_back(new Teammates);

    for (auto player_ptr: players){
        //player_ptr -> GetId();
        //use dynamic_cast to figure out the instances of the type we are interested in.
        if (Teammates * teammate_ptr = dynamic_cast<Teammates*>(player_ptr)) {
            teammate_ptr -> GetId();
        }
    }
}

//========== 81 =========
//This is to practice converting base type to derive type 
#include <iostream>

class Base{
    public:
        virtual void get(){
            std::cout << "get()\n";
        }
        void Get(){
            std::cout << "Base\n";
        }
};

class Derive: public Base{
    public:
        void Get(){
            std::cout << "Derive\n";
        }
};

int main(){
    Base *ptr_b;
    Derive *ptr_d;
    ptr_b = new Derive;
    ptr_b -> Get();

    //ptr_d = (Derive *) ptr_b;
    //ptr_d = static_cast<Derive *> (ptr_b);
    ptr_d = dynamic_cast<Derive *> (ptr_b);
    ptr_d -> Get();
    delete ptr_b;
}

//======== 80 ========
//This is to test dynamic_cast, which only works in virtual class and inheritence
//dynamic_cast: convert base type pointer (reference) to derived class type
#include <iostream>

class Base{
    public:
        virtual void Get(){
            std::cout << "Base\n";
        }
};

class Derive: public Base{
    public:
        void Get(){
            std::cout << "Derive\n";
        }
};

class DDerive: public Base{
    public:
        void Get(){
            std::cout << "DDerive\n";
        }
};

int main(){
    Base *ptr_b1 = new Derive, 
         *ptr_b2 = new DDerive;
    ptr_b1 -> Get(); 
    //cast base to derive type
    Derive * ptr_d1 = dynamic_cast<Derive*> (ptr_b1); //ptr_b1 must be virtual type
    ptr_d1 -> Get();

    std::cout << "_______\n";
    ptr_b2 -> Get();
    DDerive *ptr_d2 = dynamic_cast <DDerive*> (ptr_b1); // ptr_b1 points to Derive type instance while being converted to DDerive type
    if (ptr_d2){
        std::cout << "successful\n";
        ptr_d2 -> Get();
    }
    else{
        std::cout << "failed, can not execute Get()\n";
    }

    //use static_cast to convert derive type to base type
    ptr_b1 = dynamic_cast<Base *> (new DDerive); // converting derive class to base type does not need a dynamic_cast, just use static_cast
    ptr_b1 -> Get();

    std::cout << "___________\n";
    Derive * ptr_dd = dynamic_cast<Derive*> (new Base);
    if (ptr_dd){
        std::cout << "from new base to derive\n";
    }
    else{
        std::cout << "failed at converting from new base to derive\n";
    }
    delete ptr_b1, ptr_b2, ptr_d1, ptr_d2;
}


//========= 79 ========
//This is to test that the virtual functions in the derive class can be overridden by the ones in the base class
#include <iostream>

class base{
    public:
        void m(){
            std::cout << "m\n";
        }
        virtual void f(){
            std::cout << "base_f\n";
        }
};

class derive: public base{
    public:
        void f() override{
            std::cout << "f\n";
        }
};

int main(){
    derive *p;
    p = (derive *) new base;
    //p = static_cast<derive*>(new base);
    p -> m();
    p -> f(); //mutual overriding of virtual functions
    
    std::cout << "__________\n";
    base *pb;
    //pb = new derive;
    pb = static_cast<base *> (new derive);
    pb -> m();
    pb -> f(); //f() in base class is overriden by the one in derive
}

//==== 78 ====
//This is to practice static_cast in classes
#include <iostream>

class Base{
    public:
        int a = 3;
        void Get(){
            std::cout << "Base\n";
        }
};

class Derive: public Base{
    private:
        int b = 9;
        //char b = 'c';
    public:
        void Get_b(){
            std::cout << this -> b << std::endl;
        }
        void Get_D(){
            std::cout << "Derive\n";
        }
};

class Extra{
    public:
        int e = 8;
        void Get() {
            std::cout << "Extra\n";
        }
        void Get_e(){
            std::cout << this -> e << std::endl;
        }
};

int main(){
    Derive d, *ptr_d;
    Base b, *ptr_b;

    ptr_b = static_cast<Base *> (&d); //reference
    ptr_b -> Get();
    //ptr_b -> Get_D();
   
    std::cout << "_______\n"; 
    ptr_d = static_cast<Derive *> (&b);
    ptr_d -> Get();
    ptr_d -> Get_D();
    std::cout << ptr_d -> a << "\n";
    ptr_d -> Get_b();
    ((Derive *)(new Base)) -> Get_b();

    std::cout << "______\n";
    Derive *pd = &d;
    Base *pb = & b;

    ptr_d = static_cast<Derive *> (pb); // pointer
    ptr_d -> Get_b();
    ptr_b = static_cast<Base *> (pd);
    ptr_b -> Get();
    //ptr_b -> Get_b(); // in Base class no such function

    std::cout << "_______\n";
    Extra e, *ptr_e;
    //e = static_cast<Extra> (b);
    //ptr_e = static_cast<Extra *> (&b); //as Extra and Base has no relation, they can not be casted to each other
    ptr_e = (Extra *) &b; // the c-type cast is allowed
    ptr_e -> Get();
    ptr_e -> Get_e();
}

//===== 77 ====
//Ths is to practice static_cast
#include <iostream>

int main(){
    int a = 5, c;
    double b = 3.141592653, d;

    c = static_cast<int> (b); //() is required
    d = static_cast<double> (a); //
    std::cout << c << "\n" << d << "\n";

    static_cast<void> (a);
}

//======= 76 ======
//This is to practice virtual, static, inheritence in struct
#include <iostream>

struct Shape{
    private:
        static int born_index, num_shapes;
    public:
        Shape(){
            num_shapes ++;
            born_index ++;
        }

        ~Shape(){
            num_shapes --;
        }

        static int Get_BornIndex(){
            return born_index;
        }
        static int Get_ChildrenAlive(){
            return num_shapes;
        }

        //void Signature(){ //bind at comile time, 
        virtual void Signature(){ //bind at runtime
            std::cout << "Shape\n";
        }
};

int Shape::num_shapes = 0;
int Shape::born_index = 0;

struct Square: public Shape{
    private:
        int born_index = -1;
    public:
        Square(){
            born_index = Get_BornIndex();
        }
        void Born_Index(){
            std::cout << born_index << std::endl;
        }
        //override specifier can only be inside the class, not outside of it
        void Signature() override; // { // for readability, google recommends it
            //std::cout << "Square\n";
        //}
};

//void Square::Signature() override{ // virtual specifiers are not allowed outside of the class
void Square::Signature(){
    std::cout << "Square\n";
}

class Square_class: public Square{
    public:
        void Signature() final;//{ // put override to tell compiler or other readers that it overrides a virtual function in its base calss
            //std::cout << "Square_class\n";
        //}
};
//again virtual-specifier can not be outside of class, i.e. virtual/override/final can only be within the class
void Square_class::Signature() {
    std::cout<< "Square_class\n";
}

int main(){
    Square s1, s2;
    s1.Born_Index();
    s2.Born_Index();
    std::cout << "Shape children: " << Shape::Get_BornIndex() << std::endl;

    Square *ptr_s;
    ptr_s = new Square;
    delete ptr_s;
    std::cout << "Shape children: " << Shape::Get_BornIndex() << std::endl;
    std::cout << "Shape children alive: " << Shape::Get_ChildrenAlive() << std::endl;
    Shape * ptr_1 = &s1;
    ptr_1 -> Signature();
    
    std::cout << "_________\n";
    Square *ptr_2 = new Square_class;
    ptr_2 -> Signature();
    delete ptr_2;
}


//========== 75 ========
//This is to practice static members in inheritence
#include <iostream>

class Shape{
    public:
        static int num_shapes;
    public:
        Shape(){
            num_shapes ++;
        }
        ~Shape(){
            num_shapes --;
        }
        static void Get_NumShapes(){
            std::cout << num_shapes << std::endl;
        }
};

int Shape::num_shapes = 0;

class Rectangle: public Shape{
    
};

class Square: public Shape{
    public:
        ~Square(){
            num_shapes --; // deducted 2 when a square object is destroyed
        }
};

int main(){
    Rectangle r1, r2;
    
    Shape::Get_NumShapes();
    Rectangle::Get_NumShapes();
    Square::Get_NumShapes();
    std::cout << "__________\n";

    Square s1, s2;
    Rectangle::Get_NumShapes();
    Square::Get_NumShapes();
    Shape::Get_NumShapes();
    
    std::cout << "__________\n";
    r1.Get_NumShapes();
    r2.Get_NumShapes();
    s1.Get_NumShapes();
    s2.Get_NumShapes();

    std::cout << "__________\n";
    Square *ptr_s = new Square();
    std::cout << s1.num_shapes << std::endl;
    delete  ptr_s;
    std::cout << s1.num_shapes << std::endl;
}


//========== 74 ===========
//This is to practice static member in class
//The reason why static variable should be initialized outside of class is to avoid getting its value reset every time new instance of class is created
#include <iostream>

class Family{
    private:
        // to keep track of the number of instances active, we need to modifiy this value in its constructor and destructor functions
        static int num_families;    
    public:
        Family(){
            num_families ++;
        }
        ~Family(){
            num_families --;
        }
        //void Show_NumFamilies(){ //Family::Show_NumFamilies() is not valid as it requires an object, i.e. "this"
        static void Show_NumFamilies(){ // Family::Show_NumFamilies() is now valid as it's an attribute of the class
            std::cout << num_families << std::endl;
        }
};

int Family::num_families = 0;

int main(){
    Family f1, f2, f3;
    f1.Show_NumFamilies();
    f2.Show_NumFamilies();
    Family::Show_NumFamilies();
   
    // automatically keep track of the number of the instances created
    Family *ptr_f = new Family;
    Family::Show_NumFamilies();
    delete ptr_f;
    Family::Show_NumFamilies();
}

//===== 73 =====
// This is to practice static members in class
#include <iostream>

class Me{
    private:
        int a = 2;
        static int static_b; // can not be initialized inside the class, which is different from the static variable in a function
    public:
        Me(){
            static_b ++; // static variable is accessible to any members
        }
        static void Get_Static(){ //static function can only access static memmbers
            std::cout << static_b << std::endl; 
        }
        void Get(){
            std::cout << "Get\n";
        }
        static int c;
};

int Me::c = 3;
int Me::static_b = 0; // has to be initialized outside of class (independent of instances and in one translation unit)

int main(){
    Me me;
    Me::Get_Static(); //Static function can be accessible by class itself without be instantiated
    me.Get_Static();
    //Me::Get(); // can not call a non-static member function without an instance
    std::cout << Me::c << "\n"; //Me.c is wrong, Me does not refer to a value
}

//====== 72 =====
//This is to practice static variable in a function
#include <iostream>

//it is like (but "i" will be accessible globally, but we only want it accessible inside the function)
//int i = 0;
void Static(){
    static int times_called = 0; //comment this line out
    times_called ++;
    std::cout << times_called << std::endl;
}

int main(){
    for (auto i = 0; i < 3; i++){
        Static();
    }
}

//===== 71 =====
//This is to practice const in nullptr
#include <iostream>

class Me{
    private:
        int a = 2;
    public:
        void Get_none(){
            std::cout << "Get_none\n";
        }
        virtual void Get_no(){
            std::cout << "Get_no\n";
        }
        void Get_a(){
            std::cout << "Get_a: " << this -> a << std::endl;
        }
};

int main(){
    Me me, *ptr_me;
    ptr_me = nullptr;
    ptr_me -> Get_none(); // non-virtual function gets bound at compile time
    //ptr_me -> Get_no(); // virtual function gets bound at runtime
    //ptr_me -> Get_a(); // "this" is null
}

//======== 70 =========
//This is to if the base class of a friend class can be also a friend.
#include<iostream>

class Me;
class F_Base{
    public:
        void Get(Me &me);
};

class F: public F_Base{
    private:
        void Get(Me&);
};

class Me{
    private:
        int a=0;
        friend class F;
};

//void F_Base::Get(Me &me){
void F::Get(Me &me){
    me.a; // the base class of F can not be the context where private members of Me are accessible
}

int main(){

}

//=========== 69 ========
//This is to test if friend class of the derived class can access base class members
#include <iostream>

class Base{
    public:
        void Get_Base(){
            std::cout << "Base\n";
        }
};

class Friend;

class Derive: protected Base{
    friend class Friend;
};

class Friend{
    public:
        void Get(Derive &d){
            d . Get_Base();
        }
};

int main(){
    Derive d;
    Friend f;
    f.Get(d);
}

//====== 68 =========
//This is to practice function overloading
#include<iostream>
void func(int a){
    std::cout << "func int a\n";
}

void func(int &a){
    std::cout << "func int &a\n";
}

int main(){
    int a = 2;
    //func(a); // in this case, it is ambiguous to determine which one to use
}

//========= 67 =======
//This is to practice overloading in class inheritence
#include <iostream>

class Base{
    public:
        void Get(){
            std::cout << "Base Get\n";
        }
        void Get(int a){
            std::cout << "Base Get int\n";
        }
        void Get(float a){
            std::cout << "Base Get float\n";
        }
};

class Derive: public Base{
    public:
        //void Get(){}; // if function with name of Get is redefined, the functions with name of Get in the base class are all hidden
};

int main(){
    Derive d;
    d.Get();
    d.Get(2);
    d.Get(2.3f); //make 2.3 as float type
}


//======== 66 ===========
//This is to practice the type of inheritence
#include <iostream>

class Base{
    private: // never accessible to the derived class through -> or . operator, but can be accessed by some other type of functions
        int a = 3;
        std::string name = "Base";
    protected:
        float b = 3.1415926;
    public:
        std::string Get_Name(){
            return this -> name;
        }
        friend class Friend; // friendship is not inherited: parents' friends are not necessarily the childrens' friends

};

class DerivePublic;

class Friend{
    public:
        void Get_Base(Base &b){
            std::cout << b.a << std::endl;
        }
        void Get_DerivePublic(DerivePublic & d);
};

class DerivePublic: public Base{ 
    private:
        int a_d = 23;
        double b = 3.2;
    public:
        void Get(){
            std::cout << "Derive: " << this -> Get_Name() << std::endl;
        }
        void Get_a(){
            //std::cout << this -> a << std::endl; //a can only be accessible to Base or its friend class
        }
};

void Friend::Get_DerivePublic(DerivePublic &d){
    std::cout << d.a << std::endl; //a is private member of base, so it can still access it
    //std::cout << d.a_d << std::endl; // a_d is defined in the derived class, which is not a friend of Friend, so can not access it.
    //std::cout << d.b << std::endl; // b is redefined in the derived class, so it is not the one in the base class
}

class DeriveProtected: protected Base{
    private:
        int a_dp = 2;
    protected:
        int b_dp = 3;
    public:
        void Get(){
            std::cout << "DeriveProtected" << std::endl;
            //std::cout << this -> name << std::endl; // name is private to Base, it can not be accessed by its children
            std::cout << this -> Get_Name() << std::endl; // name can be accessible by the members of the base class, not the members of the derived class
            std::cout << this -> b << std::endl;
        }
};

class DerivePrivate: private Base{
};

class DDerivePrivate: public DerivePrivate{
    public:
        void Get(){
            //this -> b; // b is private in DerivePrivate class, so can not be inherited
        }
};

int main(){
    Friend f;
    Base b;
    DerivePublic d;
    d.Get();

    f.Get_Base(b);
    f.Get_DerivePublic(d);

    std::cout << "__________\n";
    DeriveProtected dp;
    dp.Get();
    //dp.Get_Name(); //Get_Name() is grouped into protected part of the DeriveProtected class, so can not be accessible outside of the class

}

//====== 65 =======
//to test if final function can be overloaded
#include <iostream>

class Base{
    public:
        virtual void Get(){
            std::cout << "Base\n";
        }
};

class Derive: public Base{
    public:
        void Get() final{ // can not be overridden (not hidden) by the derived class
            std::cout << "Derive\n";
        }
};

class DDerive: public Derive{
    public:
        void Get(int a){ //it supportes overloading even though its couterpart is final
            std::cout << "DDerive\n";
        }
};

void Get(Base &b){
    b.Get();
}

int main(){
    Base b;
    Derive d;
    DDerive dd;

    Get(b);
    Get(d);
    Get(dd);
    dd.Get(2);
}


//======= 64 ====
//this is to make sure the virtual functions are overridden not hidden by the ones in the derived class
#include <iostream>

class Base{
    public:
        virtual void Get(){
            std::cout << "Base" << std::endl;
        }
        void Test(){
            std::cout << "Base Test" << std::endl;
        }
};

class Derive: public Base{
    public:
        void Get(){
            std::cout << "Derive" << std::endl;
        }
        void Test(){
            std::cout << "Derive Test" << std::endl;
        }
        void Only_Derive(){
            std::cout << "Derive Only" << std::endl;
        }
};

int main(){
    Derive d;
    Base *ptr_b;
    d.Get();
    ptr_b = & d;
    ptr_b -> Get(); //though ptr_b points to Base class, Get is the one from Derive, as the one in Base is overridden by that in the Derive class
    ptr_b -> Test();
    //ptr_b -> Only_Derive(); //it is not a member in Base class
}

//===== 63 =====
//the same name functions will be hidden in the base class from the point of view of the derived class
#include <iostream>

class Base{
    public:
        void Get(int a){
            std::cout << "Base Get int\n";
        }
        void Get(float a, float b){
            std::cout << "Base Get float float\n";
        }
};

class Derive: public Base{
    public:
        //this hides both Get functions in the base class, just because the name they all share
        void Get(int a){
            std::cout << "Derive Get int\n";
        }
};

int main(){
    Derive d;
    d.Get(2);
    //d.Get(2.3, 3.3);

}

//====== 62 =====
//This is to practice final keyword: won't be overridden
#include <iostream>

class Base {
    public:
        virtual void Where() {
            std::cout << "Base\n";
        }

};

class Derive: public Base{
    public:
        void Where() final{ //final has to be paired with virtual
            std::cout << "Derive\n";
        }
};

class DDerive: public Derive{
    public:
        void WWhere(){ //Where can not be overriden
            std::cout << "DDerive\n";
        }
};

int main(){
    
}
//========= 61 =========
//abstract class (with pure virtual functions)
#include <iostream>

class Shape{
    public:
        //Shape(){}
        virtual void Get_Area()=0; // if not implemented in the derived class, then the derived class will also be abstract class
        void Get_Area_(int, int) {
            std::cout << "Shape: fake Get_Area()" << std::endl;
        }
        void Where(){ //though this is a abstract class, othere functions can be implemented explicitly
            std::cout << "Shape" << std::endl;
        }

};

class Rectangle: public Shape{
    private:
        int width, length;
    public:
        Rectangle(int _w, int _l): width(_w), length(_l){}
        void Get_Area() override final{ //if this is not implemented, then Rectangle will be abstract class which can not be instantiated
            std::cout << "Rectangle: " << width * length << std::endl;
        }
        //void Get_Area(int i, int j){
        //    std::cout << "Rectangle: fake Get_Area()" << std::endl;
        //}
        //function overriding 
        void Where() {
            std::cout << "Rectangle" << std::endl;
        }

};

int main(){
    //Shape s; //abstract class is not instantiable
    Rectangle r(2,3);
    r.Get_Area();
    r.Get_Area_(2, 2); // can not get r.Get_Area(2,3) to work. 
    r.Where();
}

//======= 60 =======
//This is to practice virtual functions
#include <iostream>

class Rectangle{
    protected:
        int a, b;
        int width;
        int length;
    public:
        Rectangle(int  _w, int _l):width(_w), length(_l){}
        virtual void Get_Area(){
            std::cout << "Rectangle: " << width*length << std::endl;
        }
        void Where(){
            std::cout << "Rectangle\n";
        }

};

class Square: public Rectangle{
    private:
        int c, d;
    public:
        Square(int _w, int _l): Rectangle(_w, _l){}
        void Get_Area(){
            std::cout << "Square: " << width * length * 0.5 << std::endl;
        }
        void Where(){
            std::cout << "Square\n";
        }
};

void Get_Area(Rectangle & r){
    r.Get_Area();
}

int main(){
    Rectangle r1(2, 3), *ptr_r;
    Square s1(2, 3), *ptr_s;
    r1.Get_Area();
    s1.Get_Area();

    std:: cout << "_________\n";
    ptr_r = &s1;
    ptr_r -> Get_Area(); //because of virtual funtion, though type casted to the base class, it still calls the function in the derived class
    std::cout << "__________\n";
    Get_Area(s1);

    std::cout << "___________\n";
    ptr_s = (Square *)& r1;
    ptr_s -> Get_Area (); // virtual make it stay with r1
    ptr_s -> Where(); // non-virtual makes it to the casted type
}

//======= 59 =========
//This is to practice explict type-casting
#include <iostream>

class A{
    private:
        int a, b;
    public:
        A(){}
        A(int _a, int _b): a(_a), b(_b){}
};

class B{
    private:
        int e, c, d=0; // weird, the order makes a difference // maybe it's not worth investigation
    public:
        B():c(2), d(3), e(4){} // nothing to do with this part
        B(int _c, int _d, int _e): c(22), d(33), e(44){} // nothing with this part
        void apb(){
            std:: cout << c << std::endl;
            std:: cout << d << std::endl;
            std:: cout << e << std::endl;
        }

};

int main(){
    A a(2,3);
    B * ptr_b = (B*) &a; // when explicit type casting, it is just like creating a new B instance with 2, 3 as initiazliation
    ptr_b -> apb(); //since only two arguments are passed to a and b, e will be random number.
}


//========= 58 =========
//This is to practice class inheritence
#include <iostream>

class Base {
    private:
        std::string s_1 = "s1_base";
    protected:
        std::string s_2 = "s2_base";
    public:
        Base(){}
        Base(std::string s1, std::string s2):s_1(s1), s_2(s2){}
        void Get_s1(){
            std::cout << "Base: " << this -> s_1 << std::endl;
        }
        void Get_s2(){
            std::cout << "Base: " << this -> s_2 << std::endl;
        }
        void test(){
            std::cout << "Base: test" << std::endl;
        }

};

class Derive: public Base {
    private:
        std::string s_1 = "xx";
        int age = 30;
    public:
        Derive():Base() {}
        Derive(std::string s1, std::string s2): Base(s1, s2){}
        void Get_s1(){
            std::cout << "Derive: " << this -> s_1 << std::endl; //s_1 is private in the base class if not defined in Derive class
            //std::cout << "Derive: s_1 is not visible in derived class" << std::endl;
        }
        void Get_s2(){
            std::cout << "Derive: " << this -> s_2 << std::endl;
        }
        void Get_age(){
            std::cout << "Derive: " << this -> age << std::endl;
        }

};

int main(){
    Base *ptr_b;
    Derive d; // Base class is called and some members are inherited to d(s_2, Get*)
    d.Get_s2(); //s_2 is from the Base class

    ptr_b = &d;
    ptr_b -> Get_s1(); // though s_1 is not visible to d, it is to the base part of d
    ptr_b -> Get_s2(); // if Get_s2() does not exist in Base, then compiling error

    std::cout << "__________" << std::endl;
    Base b;
    Derive * ptr_d;
    b.Get_s1();
    b.Get_s2();
    ptr_d = (Derive *) & b; // members can only be in Derive class space
    ptr_d -> Get_s2();
    ptr_d -> Get_s1();
    ptr_d -> Get_age(); //it does not have age member in b instance, so random number
    ptr_d -> test(); 
}

//========== 57 =========
//can we delete a class inside a function
#include <iostream>

class A{
    public:
        ~A(){
            std::cout << "destroying A" << std::endl;
        }
};

void del(A *a){
    delete a;
}

int main(){
    A a, *ptr_a;
    ptr_a = &a;
    //del(&a); 
    //delete ptr_a; //core dumped, delete should work with new in pair
    del(new A);
    std::cout << "__________" << std::endl;

}

//============ 56 =======
//This is to practice  friend class functions
#include <iostream>

class Me;
class My_Friend{
    public:
        My_Friend(){}
        void Get_MyName(Me &me);
};

class Me{
    private:
        std::string name = "none";
    public:
        Me(){}
        Me(std::string _name): name(_name){}
        friend void My_Friend::Get_MyName(Me &me);
};

//Can not be implemented inside the class as this function requires the implementation of class Me which is after My_Friend
void My_Friend::Get_MyName(Me &me){
        std::cout << "My friend knew my name: " << me.name << std::endl;
}

int main(){
    Me me("zls");
    My_Friend my_friend;

    my_friend.Get_MyName(me);

}
//====== 55 ======
//this is to practice friend functions
# include <iostream>

class Me{
    protected: // friend class/function can be in any area (private/protected/public)
        friend void Get_MyName(Me &); //the exact declaration
        int age = 30;
    private:
        std::string name = "none";
    public:
        Me(){}
        Me(std::string _name): name(_name){}
};

void Get_MyName(Me & me){
    std::cout << me.name << std::endl;
    std::cout << me.age << std::endl;
}

int main(){
    Me me;
    Get_MyName(me);

    Me you("zls");
    Get_MyName(you);
}


//========= 54 ==========
//this is to practice friend class
#include <iostream>

class Me{
    private:
        std::string name;
    protected:
        int age;
    public:
        Me(std::string _name, int _age): name(_name), age(_age){}
        friend class My_Friend; //In My_Friend, the instance of Me can access all members of itself
                                //but they are not members of My_Friend
        void test_outside(){
            std::cout << "test_me" << std::endl;
        }
};

class My_Friend{
    public:
        void Get_MyName(Me me){
            //due to My_Friend is a friend of Me class, inside My_Friend me can access its private and protected members
            std::cout << "My_Friend knew my name: " << me.name << std::endl;
            std::cout << "             & my age: " << me.age << std::endl;
            me.test_outside();
        }
};

int main(){
    Me me("LianshuiZhao", 30);
    My_Friend my_friend;
    my_friend.Get_MyName(me);
    //my_friend.test_outside(); // friend class can only access protected and private members, not public members
}

//======== 53 ========
#include <iostream>

class Base{
    private:
        std::string s_1 = "s_1_base";
    protected:
        std::string s_2 = "s_2_base";
    public:
        Base(){}
        Base(std::string s1, std::string s2): s_1(s1), s_2(s2){}
        void GetInfo(){
            std::cout << "BASE: " << this -> s_1 << "; " << this -> s_2 << std::endl;
        }
        ~Base(){
            std::cout << "~Base" << std::endl;
        }
};


class Derive: public Base{
    public:
        Derive():Base(){}
        Derive(std::string s1, std::string s2): Base(s1, s2){}
        void GetInfo(){
            //std::cout << "Derive: " << this -> s_1 << "; " << this -> s_2 << std::endl;
            std::cout << "Derive: " << this -> s_2 << std::endl;
        }
        ~Derive(){
            std::cout << "~Destroying derive" << std::endl;
        }

};

void Get_Base(Base * ptr_base){
    //always use the GetInfo() function of the Base class, not from the derived class
    ptr_base -> GetInfo();
    std::cout << "\tstart destroying base" << std::endl;
    delete ptr_base; //calling the base destructor
    std::cout << "\tfinishing destroying base" << std::endl;
}

int main(){
    Derive d;
    d.GetInfo(); 
    std::cout << "______________\n";
    Base * ptr_base = &d; //Base-type member functions
    ptr_base -> GetInfo();

    std::cout << "+++++++++++++\n";
    Derive d_v("s_1_derive", "s_2_derive");
    ptr_base = & d_v; //is this another type of polymorphism?
    ptr_base -> GetInfo();

    std::cout << "_+____________\n";
    Get_Base(new Derive("xx", "yy"));
    
    std::cout << "____________\n" << std::endl;
    Derive *d1 = new Derive();
    delete d1;

    std::cout << "_________\n";
    Derive *ptr_d = (Derive *) new Base;
    ptr_d -> GetInfo();
    delete ptr_d;
    std::cout << "__________\n";
    
}

//======= 52 ===========
// class inheritence
#include <iostream>

class Base{
    private: // can only be accessed by Base class itself and within the class, not outside
        std::string s_1 = "s_1_base";
    protected: // can be accessible by derived class
        std::string s_2 = "s_2_base";
    public:
        Base(){}
        void Get_Member(){
            std::cout << "BASE " << this -> s_1 << "; " << this -> s_2 << "\n";
        }
};

//inherit from protected and public members of base class
class Derive: public Base{
    private:
        //std::string s_1= "s_1_derive";
    public:
        Derive(): Base(){
        }

        void Get_FromBase(){
            //std::cout << "Derive: " << s_1 << "\n"; // if not defined in derived class, s_1 is private to Base class
            std::cout << "Derive: " << this -> s_2 << "\n"; // s_2 is protected to Base class, so can be accessible by derived class
        }
    
};

int main(){
    Derive d_1;
    d_1.Get_Member(); //Get_Member() is a public function, so can be called outside of class
    d_1.Get_FromBase();
}

//===== 51 =====
//Have a thorough study of class inheritence
#include <iostream>

class Family{
    private:
        int num_people;
        std::string name = "Family";
    public:
        Family(){}
        Family(int num): num_people(num){
        }
        void Get_NumPeople(){
            std::cout << "Family " << this -> num_people << std::endl;
            std::cout << "name: " << this -> name << std::endl;
        }
};

class My_Family: public Family{ //without public, it is private by default
    private:
        //since num_people and name are private in Family, so My_Family can not access them
        //thus we have to define our own copy of them, otherwise this->name/num_people will
        //try to access the ones in Family, causing access errors 
        int num_people;
        std::string name = "My_Family";
        int age;
    public:
        My_Family(int num): Family(num){
        }
        void Get_NumPeople(){
            //these variables are the ones in My_Family, not the ones in Family
            std::cout << "My_Family " << this -> num_people << std::endl;
            std::cout << "My name: " << this -> name << std::endl;
        }
        void Only_Children(){
            std::cout << "Only in the child class" << std::endl;
        }

};

void Family_NumPeople(Family *family){
    family -> Get_NumPeople();
}

int main(){
    Family family(0), *ptr_family;
    My_Family my_family(5), *ptr_my_family;

    ptr_family = & my_family;
    ptr_family -> Get_NumPeople(); // we do not get polymorphysim, i.e. always the function of the base class
    //ptr_family -> Only_Children(); //the base class does not have this member function, so can not call it
    std::cout << "_________" << std::endl;
    Family_NumPeople(& my_family);
    std::cout << "________" << std::endl;
    ptr_my_family = (My_Family *) & family; //since My_Family can not access the member attributes of Family, thus random values
    //if these attributes are protected and not redefined in My_Family, then My_Family can access the values in Family
    ptr_my_family -> Get_NumPeople();
}

//====== 50 ======
//This is to study the overriding of functions for classes
#include <iostream>

class Shape {
	protected:
		std::string name;
	public:
		Shape(std::string name){
			this -> name = name;
		}
		Shape(){
			std::cout << "Empty initialization" << std::endl;
		}

		void Shape_Name(){
			std::cout << "Shape: " << this -> name << std::endl;
		}
};
class Square: public Shape {
	public:
		Square(std::string name_arg): Shape() { // the base class should be called here
			//if name is passed, then name in this scope only refers to this one
			//Shape(name); // error in this way, got to be before {
			name = name_arg;
			std::cout << "before adding _end: " << name << std::endl; //here name is the one being passed into the constructor
			std::cout << this -> name << std::endl; // "this" pointer differentiates the class member and the argument being passed
			name += "_end";
			std::cout << "after adding _end: " << name << std::endl; // the same is here
			std::cout << this -> name << std::endl;
		}
		void Shape_Name(){
			std::cout << "Square: " << name << std::endl; // here now name refers to the class member
		}
};

int main(){
	Shape s_base("shape");
	s_base.Shape_Name();

	Square s_derive("square");
	s_derive . Shape_Name(); //. operator: can be separated with spaces
	
	std::cout << "++++++++++++" << std::endl;

	Shape *ptr_base = &s_base;
	Square *ptr_derive = &s_derive;

	ptr_base -> Shape_Name();
	ptr_derive -> Shape_Name();

	std::cout << "++++++++++++" << std::endl;

	ptr_base = & s_derive;
	ptr_base -> Shape_Name();

	ptr_derive = (Square *) & s_base;
	ptr_derive -> Shape_Name();

}
//========== 49 ==========
#include <iostream>
#include <map>
#include <vector>

int main(){
	std::map <int, std::string> me;
	me[0] = "zls";
	me[2] = "male";

	me.insert({3, "30"});
	me.insert({2, "femal"});//this does not change the value of an existing key
	me[2] = "female"; //this works

	for (auto entry = me.begin(); entry != me.end(); entry++){
		std::cout << entry -> first << "=" << entry -> second << "; ";
	}
	std::cout << std::endl;

	std::map <int, std::string>::iterator itr;
	itr = me.find(0);
	if (itr == me.end()){
		std::cout << "NOT FOUND" << std::endl;
	}else{
		std::cout << itr -> first << "=" << itr -> second << std::endl;
	}

	std::vector <int> keys;
	for (auto itr = me.begin(); itr != me.end(); itr ++){
		keys.push_back(itr->first);
	}
	for (auto i = 0; i < keys.size(); i++){
		std::cout << keys[i] << " ";
	}
	std::cout << std::endl;
	std::cout << me.size() << " " << me.max_size() << std::endl;
	me.erase(2);
	std::cout << me.size() << std::endl;
	std::cout << keys.size() << " ";
	keys.erase(keys.begin()+2);
	std::cout << keys.size() << std::endl;
	std::cout << keys.capacity() << std::endl;
	keys[40] = 30;
	std::cout << keys.capacity() << std::endl;
	keys.shrink_to_fit();
	std::cout << keys[40] << " " << keys.size() << std::endl;
}

//========== 48 =========
#include <iostream>
#include <vector>
#include <map>

int main(){//MAIN has to be int-return type
	std::vector <std::string> shared_entries;
	std::string entry;

	std::cout << "Please enter the entries you'd like to share (enter 'end' to stop):";
	while (true){
		std::cin >> entry;
		if (entry == "end")
			break;
		shared_entries.push_back(entry);
	}

	std::cout << "You would like to share the following information with us:";
	for (auto i = shared_entries.begin(); i < shared_entries.end(); i++){
		std::cout << *i << " ";
	}
	std::cout << std::endl;
	std::cout << "total " << shared_entries.size() << " entries" << std::endl;
	shared_entries.shrink_to_fit(); // DOES this save memory?

	std::map <std::string,std::string> my_info;
	std::cout << "Please enter your following information:" << std::endl;
	for (auto entry = shared_entries.begin(); entry < shared_entries.end(); entry ++){
		std::cout << *entry << ":";
		std::cin >> my_info[*entry];
	}

	for (auto entry = my_info.begin(); entry != my_info.end(); entry ++){
		std::cout << entry -> first << "=" << entry -> second << "; ";
	}
	std::cout << std::endl;
	for (auto entry = my_info.rbegin(); entry != my_info.rend(); entry ++){
		std::cout << entry -> first << " ";	
	}
	std::cout << std::endl;
	for (auto entry = shared_entries.begin(); entry < shared_entries.end(); entry ++){
		std::cout << *entry << "=" << my_info.at(*entry) << "; ";
	}
	std::cout << std::endl;
	//just to practice []
	std::cout << my_info["name"] << " " << my_info["age"] << std::endl;
}


//========= 47 ==========
//this is to pratice map
#include <iostream>
#include <vector>
#include <map>

int main(){
	std::map <int, std::string> me;
	std::map <int, std::string>::iterator itr; //iterator in the normal order
	me[1] = "ZLS";
	me[2] = "30";
	me[300] = "male";
	me[-23] = "str_23";

	std::cout << me[1] << " " << me[2] << " " << me[3] << std::endl;

	itr = me.find(232); //the key value to be tested has to be of the correct type supported in this map object
	if (itr != me.end()){
		std::cout << itr -> first << " " << itr -> second << std::endl;
	}else{
		std::cout << "Not found" << std::endl;
	}

	//map is always sorted, so usually not in the order the elementa are inserted/created
	for (auto i = me.begin(); i != me.end(); i++){
		std::cout << i -> first << " -> " << i -> second << " "; 
	}
	std::cout << std::endl;

	//reverse iterator
	std::map <int, std::string> ::reverse_iterator itr2; //iterator in the reverse order
	for (itr2 = me.rbegin(); itr2 != me.rend(); itr2 ++){ //or we can just use auto to simplify this 
		std::cout << itr2 -> first << " -> " << itr2 -> second << " ";
	}
	std::cout << std::endl;

	//map pointer comparison
	std::map<int, std::string> *you_ptr, you;
	you_ptr = &me; //BY VALUE
	you = me;

	(*you_ptr)[1] = "dsy_ptr";
	you[1] = "dys";
	std::cout << me[1] << " " << (*you_ptr)[1] << " " << you[1] << std::endl;

	std::vector <std::string> key;
	std::cout << "Please enter the information that you would like to share with us (enter 'end' to stop):";
	std::string entry;
	while(true){
		std::cin >> entry;
		if (entry == "end")
			break;
		std::cout << entry << std::endl;
		key.push_back(entry);
	}

	std::map <std::string, std::string> my_info;
	std::cout << "Please enter your" << std::endl;
	for (auto entry = key.begin(); entry < key.end(); entry ++){
		std::cout << "\t" << *entry << ":";
		std::cin >> my_info[*entry];
	}
	for (auto itr = my_info.begin(); itr != my_info.end(); itr ++){
		std::cout << itr->first << " -> " << itr -> second << "; ";
	}
	std::cout << std::endl;
}


//=============== 46 =============
// this is to test empty and iterator
#include<iostream>
#include<vector>

int main(){
	std::vector <int> a{2, 3, 4, 5};
	std::vector <float> b;
	//empty() is find out if a vector is empty or not
	std::cout << a.empty() << " " << b.empty() << std::endl;
	
	//iterator has to be of the same type as it points to
	std::vector<int>::iterator itr;
	for (itr = a.begin(); itr < a.end(); itr++){
		std::cout << *itr << " ";
	}
	std::cout << std::endl;
	//somehow this does not work
	//for (itr = a.rbegin(); itr != a.rend(); itr++){
	//	std::cout << *itr << " ";
	//}
	std::cout << std::endl;
}


//=========== 45 =========
//This is to test the vector, which stores data in contiguous manner
//the size is flexible, i.e. shrinking or expanding freely,
//the storage is handled by the container automatically
#include <iostream>
#include <vector>

int main(){
	std::vector<int> v1;

	int num_ele = 9;

	for (int i = 0; i < num_ele; i++){
		v1.push_back(i+1); // use push_back to assign values to the vector
	}

	std::cout << "Show the vector" << std::endl;
	//just like arrays, access its elements by indexing
	for (auto i = 0; i < num_ele; i++){
		std::cout << "\t" << v1[i] << std::endl;
	}
	
	//for an array we can access it by referencing
	int arr[5]={3, 4, 5, 6, 7};
	for (int i = 0; i < 5; i++){
		//std::cout << *(&arr[0]+i) << std::endl;
		std::cout << *(arr+i) << std::endl;
	}
	//through address iterator, we can access each element by dereferencing
	for (auto i = v1.begin(); i < v1.end(); i++){ //an iterator
		std::cout << "\t" << *i << std::endl;
	}
	for (auto i = v1.end() - 1; i >= v1.begin(); i--){
		std::cout << *i << std::endl;
	}
	//use the reverse order address iterator, note still use ++, not --
	for (auto i = v1.rbegin(); i != v1.rend(); i++){
		std::cout << *i << " ";
	}
	std::cout << std::endl;

	v1[4] = 222;
	std::cout << v1.back() << " " << v1[4] << " " << v1.at(4) << std::endl;
	std::cout << v1[0] << " " << v1[2] << std::endl;
	std::cout << v1.at(0) << " " << v1.at(2) << std::endl;

	std::cout << "size of int " << sizeof(int) << std::endl;
	int *v1_ptr = v1.data();
	int *add1, *add2;
	for (auto i = 0; i < 5; i++){
		std::cout << (v1_ptr+i) << " " << *(v1_ptr+i) << std::endl;
		if (i == 0)
			continue;
		add1 = v1_ptr+i-1;
		add2 = v1_ptr+i;
		std::cout << "\t" << add2-add1 << std::endl;
	}
	std::cout << std::endl;

	std::cout << 0x55ef3a6a4eb0 - 0x55ef3a6a4eb4 << std::endl;

	std::vector<double> v2;
	std::cout << v1.size() << " " << v1.capacity() << " " << v1.max_size() << " " << v2.max_size() << " " << v1.max_size()*1.0/v2.max_size() << std::endl;
	//shrink the vector
	v1.shrink_to_fit();
	std::cout << v1.capacity() << std::endl;
	//one size is changed, the capacity is modified
	v1.push_back(2323);
	std::cout << v1.size() << " " << v1.capacity()  << std::endl;
	v1.shrink_to_fit();
	std::cout << v1.capacity() << std::endl;
	std::cout << v1.front() << " " << v1.back() << std::endl;

	v1.insert(v1.begin(), 23);
	std::cout << v1.front() << std::endl;
	v1.insert(v1.end()-1, 0);
	std::cout << v1.at(v1.size()-2) << std::endl;
	v1.insert(v1.end(), 11);
	std::cout << v1.back() << std::endl;

	//v1.insert(*(v1.data()+v1.size()), 2222222);
	std::cout << "****" << v1[2] << std::endl;
	*(v1.data()+2) = 222222; //modify this address and is reflected in the vector
	std::cout << v1.back() << std::endl;
	std::cout << v1.size() << " " << v1.capacity() << std::endl;
	std::cout << *(v1.data()+2) << " " << v1[2] << std::endl;

	v1.clear();
	v1.shrink_to_fit();
	std::cout << v1.size() << std::endl;
	v1.push_back(22);
	v1.push_back(3);
	std::cout << v1.size() << " " << v1.capacity() << std::endl;

	v1.pop_back();
	std::cout << v1.size() << " " << v1.capacity() << " " << v1.back() << std::endl;

	v1.emplace_back(23234); //JUST LIKE POP_BACK()
	v1.emplace_back(200000);
	std::cout << v1.size() << " " << v1.capacity() << " " << v1.back() << std::endl;

	v1.erase(v1.end()-1); //remove the last element, just like pop_back()
	std::cout << v1.size() << " " << v1.capacity() << " " << v1.back() << std::endl;

	v1.clear();
	v1.assign(4, 2);
	for (auto i = v1.begin(); i < v1.end(); i++){
		std::cout << *i << " ";
	}
	std::cout << std::endl;
	int a[] = {9, 8, 7, 6, 5, 4};
	v1.assign(a, a+sizeof(a)/sizeof(int)); // assign array to a vector, and the values in its old version are cleared
	for (auto i = v1.begin(); i < v1.end(); i++){
		std::cout << *i << " ";
	}
	std::cout << std::endl;
	std::vector<int> v3;
	v3.assign(v1.begin()+1, v1.end()-1);
	for(auto i = v3.begin(); i < v3.end(); i++){
		std::cout << *i  << " ";
	}
	std::cout << std::endl;

	std::vector <double> v4;
	for (int i = 0; i <9; i++){
		v4.push_back(i);
	}

	for (auto i = v4.begin(); i < v4.end(); i++){
		//the odd-index values
		if ((i - v4.begin())%2 == 0){
			std::cout << *i << " ";
		}
	}
	std::cout << std::endl;

	//initializing
	std::vector <float> v5 {2.2, 3, 5.9};
	std::cout << v5[0] << " " << v5[1] << " " << v5[2] << std::endl;
}

//============ 44 ============
// thread example
#include <iostream>       // std::cout
#include <thread>         // std::thread

void foo()
{
  std::cout << std::this_thread::get_id() << std::endl;
}

void bar(int x)
{
  std::cout << std::this_thread::get_id() << std::endl;
}

int main()
{
  std::thread first (foo);     // spawn new thread that calls foo()
  first.join();
  std::thread second (bar,0);  // spawn new thread that calls bar(0)
    second.join();
    std::cout << std::this_thread::get_id() << std::endl;

  std::cout << "main, foo and bar now execute concurrently...\n";

  // synchronize threads:
  first.join();                // pauses until first finishes
  second.join();               // pauses until second finishes

  std::cout << "foo and bar completed.\n";

  return 0;
}

//============= 43 =========
#include <iostream>
#include <memory>
#include <unistd.h>
struct Person{
	public:
		int age;
		Person():age(-1){}
		Person(int age):age(age){}
		~Person(){
			std::cout << age << " is destroyed" << std::endl;
		}
};

int main(){
	std::shared_ptr<Person> p1; 
	//p1 = new int(2); // this is wrong as p1 and the assignment have different types
	p1 = std::make_shared<Person> ();
	std::cout << p1 << " " << p1.get() << " " << p1.use_count() << " " << p1->age << std::endl;

	std::cout << "before p1 switches" << std::endl;
	p1 = std::make_shared<Person> (3);
	std::cout << "after p1 switches" << std::endl;
	std::cout << p1 << " " << p1.get() << " " << p1.use_count() << " " << p1->age << std::endl;
	sleep(2);
	std::cout <<"__________ END __________" << std::endl;
}
//============= 42 ========
#include<iostream>
#include<memory>
#include<string>

struct Person{
	public:
		std::string name;
		Person():name("zls"){}
		Person(std::string name): name(name){}
		~Person(){
			std::cout << name << " is destroyed" << std::endl;
		}
};

int main(){
	std::shared_ptr<Person> p1(new Person("xx"));
	std::cout << p1 -> name << std::endl;
	//since p1 is pointing to another space, 'xx' will be destroyed
	p1 = std::make_shared<Person> ("yy"); //the arguments are the ones needed by the constructor
	//the same goes here, 'yy' will be destroyed
	p1 = std::make_shared<Person>();
	std::cout << p1 -> name << std::endl;
	std::cout << "__________ END __________" << std::endl;
}
//========== 41 ===========
#include <iostream>
#include <memory>
#include <map>

int main(){
	std::map<int, double> i_d;
	i_d.insert({2, 3.14});

	std::shared_ptr<std::map<int, double>> ptr_i_d (new std::map<int, double>);
	ptr_i_d->insert({2, 3.14});
	ptr_i_d->insert({3, 4.14});

	for (auto it = ptr_i_d->begin(); it != ptr_i_d->end(); it++){
		std::cout << it -> first << ": " << it -> second << std::endl;
	}

	std::cout << ptr_i_d << " " << ptr_i_d.use_count() << std::endl;

	ptr_i_d = std::make_shared<std::map<int, double>>();
	ptr_i_d->insert({9, 9.9});
	ptr_i_d->erase(9);
	std::cout << ptr_i_d << " " << ptr_i_d.use_count() << std::endl;
}

//========== 40 =========
//this is to practice make_shared which creates a shared_ptr that points to type T object with args
#include <iostream>
#include <memory>

int main(){
	int a = 3;
	std::shared_ptr<int> p_1 = std::make_shared<int> (a);

	std::cout << p_1.use_count() << " " << *p_1 << std::endl;
	std::cout << &a << std::endl << p_1 << std::endl << p_1.get() << std::endl;


	int *b ;//= new int(9);
	b = new int (9);
	std::shared_ptr<int> p_2(b);
	std::cout << b << std::endl << p_2 << std::endl;


	std::shared_ptr<int> p_3(&a);
}

//=========== 39 =========
//This is to practice shared_ptr with customized class
#include <iostream>
#include <string>
#include <memory>

class Person{
	private:
		std::string name;
		int age;
	public:
		Person(): name("xx"), age(30){};
		Person(std::string name, int age):name(name), age(age){}
		~Person(){
			std::cout << name << " is destroyed" << std::endl;
		}
		int get_age(){
			return age;
		}
};

int main(){
	std::shared_ptr<Person> me_ptr(new Person);
	std::cout << me_ptr->get_age() << std::endl;


	Person * me = new Person("zls", 29);
	std::shared_ptr<Person> me_ptr_2(me);
	std::cout << me_ptr_2->get_age() << me_ptr_2.use_count()<< std::endl;
	//delete me; //causing segmentation fault
	//std::shared_ptr<Person> me_ptr_3(me); //causing segmentation fault as me is trying to be deleted twice
	std::shared_ptr<Person> me_ptr_3(me_ptr_2);
	std::cout << "_________ END _________" << std::endl;
}

//========= 38 =========
//This is to practice shared_ptr
#include <iostream>
#include <memory>

int main(){
	int * p0;
	p0 = new int(30);
	std::cout << "p0 points to " << p0 << std::endl;
	std::shared_ptr<int> p1(p0);

	std::cout << "p1 use_count(): " << p1.use_count() << std::endl;
	std::cout << *p1 << std::endl;
	std::cout << p1 << std::endl;
	std::cout << &p1 << std::endl;

	std::shared_ptr<int> p2(p1);
	std::cout << "p1 use_count(): " << p1.use_count() << ", p2.use_count(): " << p2.use_count() << std::endl;
	std::shared_ptr<int> p3(p0); // in this case p1 and p2 doesnot know p3 is also pointing to p0, this might cause crashing
	std::cout << "p1 use_count(): " << p1.use_count() << ", p2.use_count(): " << p2.use_count() << ", p3.use_count(): " << p3.use_count() << std::endl;

	std::cout << *p1 << *p2 << *p3 << std::endl;
	delete p0; //what it really deletes is the content in the memory space pointed to by p0, not p0 itself
	std::cout << "after deleting p0, p0 points to " << p0 << std::endl;
	std::shared_ptr <int> p4(p1);
	std::cout << *p1  << " " << *p2 << " " << *p3 << " " << *p4<< std::endl;
}

//====== 37 ======
//this is to practice new and delete objects
#include <iostream>

struct me_struct{
	public:
	int me_i;
	me_struct(int _i){
		me_i = _i;
	}
	me_struct(){}
	~me_struct(){
		std::cout << "me_struct is destroyed " << me_i << std::endl;
	}
};

int main(){
	//dynamically allocate a memory space with size of sizeof(int)
	int *p = new int(2);
	//releasing the memory block pointed to by p, otherwise memory leak
	std::cout << *p << std::endl;
	delete p;

	double *p_double;
	p_double = new double;
	*p_double = 3.1415;
	std::cout << *p_double << std::endl;
	delete p_double;

	float *p_float = new float[3];
	for (int i = 0; i < 3; i++){
		p_float[i] = i*i;
	}
	std::cout << p_float[2] << std::endl;
	delete [] p_float;

	me_struct* me_ptr = new me_struct(2);

	std::cout << "Before deleting struct" << std::endl;
	delete me_ptr;
	std::cout << "After deleting struct" << std::endl;
	
	std::cout << "\n\n";
	me_struct * me_arr_p;
	me_arr_p = new me_struct[3];
	
	for (int i = 0; i < 3; i++){
		me_arr_p[i].me_i = i+3;
	}
	std::cout << "\n______ before ______\n";
	delete [] me_arr_p; // without this line, the struct objects will not be destroyed
	std::cout << "______ after ______\n";
	std::cout << "______ END _____\n";
}
//====== 36 ========
//this is to practice basic type initialization
#include <stdio.h>
int main(){
	int i(2); //initialize i, i.e. i = 2. it's just like initializing a custom class
	printf("i = %d\n", i);
}

//=========== 35 =========
//this is to test memcpy, which is defined in string.h
#include <iostream>
#include <string.h>
#include <string>

int main(){
	int a = 2;
	int b;
	std::cout << b ; // a very small number which is default
	memcpy(&b, &a, sizeof(a)); // source and destination have to be of the same type
	std::cout << "sizeof(a) " << sizeof(a) << ", b: " << b << std::endl;
	std::cout << "sizeof(size_t): " << sizeof(size_t) << std::endl;

	std::string str_1 = "love me";
	std::cout << "length of str_1 " << str_1.size() << std::endl;
	char str_2[str_1.size()];
	std::cout << "strlen " << strlen(str_1.c_str()) << std::endl;
	memcpy(str_2, str_1.c_str(), strlen(str_1.c_str())); 
	std::cout << sizeof(str_1) << std::endl;
	std::cout << "str_2 " << str_2 << std::endl;

	for(auto c : str_1){
		std::cout << c << " ";
	}
	std::cout << std::endl;
	//the size of string, string.size()
	std::cout << str_1[0] << str_1[str_1.size()-2] << std::endl;

	char str_3[] = "";
	std::cout << sizeof(str_3) << std::endl;
	puts("sdf"); // in c
}


//=========== 34 =========
//this is to test that thread shares information with the the main process
#include <iostream>
#include <thread>
#include <unistd.h>

int value = 0;
int send = 0;

void test_value(){
	int count = 0;
	sleep(1);
	send = 99;
	while(value == 0){
		sleep(1);
		std::cout << ++count << std::endl;
}
	std::cout << "test_thread exit " << value << std::endl;
}

int main(){
	std::thread test_thread (test_value);
	sleep(5);
	std::cout << "main process " << send << std::endl;
	sleep(3);
	value = 2;

	test_thread.join();
}

//========= 33 ========
//this is to practice string
#include <iostream>
#include <stdio.h> //printf

int main(){
	std::string a = "love", b = " ", c = "me", sentence;
	sentence = a+b+c;
	std::cout << "sentence: " << sentence << std::endl;
	printf ("sentence %s\n", sentence.c_str());
}
//============ 32 =======
//This is to practice getenv which grabs the environment variables
#include <iostream>

int main(){
	std::cout << std::getenv("mexx") << std::endl; 
	std::cout << std::getenv("PATH") << std::endl;
}


//======= 31 ======
//This is to practice thread and sleep function 
#include <thread>
#include <iostream>
#include <unistd.h> //sleep function in linux
void slm(){
	std::cout << std::this_thread::get_id() << " is sleeping for 3 s" << std::endl;
	sleep(3);
	std::cout << std::this_thread::get_id() << " woke up" << std::endl;
}

int main(){
	std::thread me(slm);
	sleep(0.5);
	std::cout << "main " << std::this_thread::get_id() << " is sleeping for 2 s" << std::endl;
	sleep(2);
	std::cout << "main " << std::this_thread::get_id() << " woke up" << std::endl;

	me.join(); //use join otherwise core dump error at the end
}


//========== 30 =========
#include "my_funcs/my_funcs.h"

#if defined_in_cmake == 0
#define cmake "zero"
#elif defined_in_cmake == 1
#define cmake "one"
#endif

int main(int argc, char*args[]){
	int a = ret_square(2);
	std::cout << a << std::endl;
	std::cout << "CMAKE --VERSION: " << cmake << std::endl;
}

//========== 29 ============
//This is to practice taking input from command line
#include <iostream>
#include <sstream>

int main(int argc, char *arg[]){
	std::cout << arg[0] << std::endl;
	for (int i = 1; i < argc; i++){
		std::cout << arg[i] << " ";
	}
	std::cout << std::endl;

	std::string i = "2323";
	std::stringstream convert;
	int a, b=-1;

	convert << arg[1] << " " << arg[2];
	convert >> a; //here the content in convert is not getting pushed out completely, so it will stay there
	std::cout << a << " " << b << std::endl;
	
	//concate numbers
	convert << " " << arg[1] << arg[2]; //here it combines the new and old ones in the stream
	convert >> a >> b;
	std::cout << a << " " << b << " " << arg[1] << " " << arg[2] << std::endl;
}

//========== 28 =======
#include <iostream>

#define NO_CLASS 0

#if (NO_CLASS == 1)
int add(int a, int b){
	return a+b;
}

int main(){
	std::cout << "Add_func: " << add(2, 3) << std::endl;
}
#else
class Add{
	protected:
		int a, b;
	public:
		Add(int a, int b){
			this -> a = a;
			this -> b = b;
		}
		int RetAdd(){
			return a+b;
		}
};

int main(){
	Add my_add(2, 3);
	std::cout << "My_add: " << my_add.RetAdd() << std::endl;
}

#endif


//=========== 27 =========
//this is to find the type of a variable
#include <iostream>
#include <typeinfo>

int main(){
	int i = 0;
	double j = 2.3;
	float a = 2;
	char c = 's';
	std::string b = "ss";
	std::cout << "int: " << typeid(i).name() << std::endl;
	std::cout << "double: " << typeid(j).name() << std::endl;
	std::cout << "float: " << typeid(a).name() << std::endl;
	std::cout << "char: " << typeid(c).name() << std::endl;
	std::cout << "string: " << typeid(b).name() << std::endl;

	std::string s = (std::string)typeid(b).name() + (std::string) typeid(j).name();
	std::cout << s << std::endl;
}


//========== 26 =======
#include <iostream>

int main(){
	const char * str1 = "ss"; //COMPILER warning, we should add const in front as string is a char constant
	const char *str2 = "xx";
	std::cout << str1 << " " << str2 << std::endl;

	const char * str3 = (char *) malloc(sizeof(char) * 3);
	std::cout << sizeof(str3) << std::endl; //POINTER size is still 8
	str3 = "xyz";
	std::cout << str3  << " " << ((std::string) str3).size() << std::endl;

	std::cout << str3[2] << std::endl;
	//str3[2] = 'x'; // YOU CAN NOT change const of chars
	// BUT we can do it in string
	std::string str4 = "xyz";
	std::cout << str4 << " -> ";
	str4[2] = 'x';
	std:: cout << str4 << std::endl;

	char str5[11] = "i love you";
	std::cout << sizeof(str5) << std::endl;
	std::cout << str5;
	for (int i = 0; i < sizeof(str5); i++){
		if (str5[i] == ' ')
			str5[i] = '_';
	}
	std::cout << " -> " << str5 << std::endl;

	std::cout << std::endl;

	char a = 'A', b = 'B';
	char *ptr = & a;
	//print out the address
	std::cout << static_cast<void*> (ptr) << " " << static_cast<void*> (&a) << std::endl;
	ptr = &b;
	std::cout << static_cast<void*> (ptr) << " " << static_cast<void*> (&b) << std::endl;
	
	//constant pointer which can not point to a second address, but you can change the content in the first address
	char *const const_ptr = &a;
	std::cout << static_cast<void*>(const_ptr) << " " << *const_ptr<< std::endl;
	//const_ptr = &b; 
	*const_ptr = 'a'; //'A' becomes 'a'
	std::cout << static_cast<void*>(const_ptr) << " " << *const_ptr << std::endl;

	//can not point to a second location, nor change the value in the first address through the pointer 
	const char *const cc_ptr = &a;
	std::cout << static_cast<const void *>(cc_ptr) << " | " << *cc_ptr << std::endl;
	//cc_ptr = &b;
	// *cc_ptr = b;
	//but we can change the value in the first address by other variables relating to it
	a = 'A';
	std::cout << static_cast<const void *>(cc_ptr) << " | " << *cc_ptr << std::endl;

}


//========== 25 =========
#include <iostream>

int main(){
	char a = 's';
	//char *a_ptr = &'s'; //invalid as & has to be followed by a variable, which is how we refer to objects. define a variable first
	//char *a_ptr = 's'; // type wrong
	char * a_ptr = &a;

	const char * b_ptr = "ss"; //however this migically works
	std::string str = b_ptr;
	std::cout << str <<  " " << sizeof(str) << " " << str.size()<< std::endl;
	str = "";
	std::cout << sizeof("") << " " << sizeof(str) << std::endl;

	//const char * c_ptr = str;
	const char * c_ptr = str.c_str();
	std::cout << c_ptr << sizeof(c_ptr) << std::endl;
}



//
//========= 24 ==========
#include <iostream>

int main(){
	//here str is just a pointer typed of char
	//mutable
	char c = 'd';
	char *c_ptr = &c; // need to pass an address to char pointer
	std::cout << c  << *c_ptr<< std::endl;
	c = 'e';
	//immutable
	const char d = 'e';
	std::cout << d << std::endl;
	//d = 'f'; //read-only variable
	
	//a sequence of char, AGAIN A POINTER, but a one with const char
	const char * seq = "this is the first";
	std::cout << sizeof(const char *) << " " << sizeof(seq) << std::endl; // the size of this type
	std::cout << sizeof(const int *) << " " << sizeof(double*); // looks like all pointers have size of 8
	for (int i = 0; i < 17; i++)
		std::cout << seq[i];
	std::cout << "--xx";
	std::cout << sizeof("") << " " << sizeof("more than one") << std::endl;

	//array of char
	char arr_char[] = {'2', '3', 'x', 'y'};
	std::cout << sizeof(arr_char) << " " << sizeof(arr_char[0]) << " " << sizeof(arr_char)/sizeof(arr_char[0]) << std::endl;
	for (auto c : arr_char)
		std::cout << c;
	std::cout << std::endl;
	//array of sequences
	const char *arr_str[] = {"sd", "sdfs", "", "s"};
	//here sizeof() means the size of the pointers
	std::cout << sizeof(arr_str) << " " << sizeof(arr_str[2]) << std::endl;
	for (auto strptr : arr_str)
		std::cout << strptr << "|";
	std::cout << std::endl;
	for (int i = 0; i < sizeof(arr_str)/sizeof(arr_str[0]); i++)
		std::cout << arr_str[i] << "|";
	
	//string
	std::cout << "\n\n";
	std::string stdstr = "sd";
	for (auto c : stdstr)
		std::cout << c << " ";
	std::string empty = "";
	std::cout << "empty string size: " << empty.size(); // this is different from sizeof("") as shown before
	std::cout << std::endl;
}


//============ 23 ===========
//This is to test string and char
#include <iostream>
#include <string>

std::string ret_str(){
	return "ret_str";
}

const char * ret_char(){
	static std::string s = "ret_str";
	//std::string s = "ret_str"; //this leads to garbage output
	return s.c_str(); // converting string to const char, 
	//return (char *) s; // can not do type casting, why?
}

int main(){
	std::string str = ret_str();
	std::cout << str << std::endl;

	const char * str_char = ret_char();
	std::cout << str_char << std::endl;
}


//====== 22 =====
//FAILED
//this is practice friend class template with a condition
#include <iostream>
template <typename T, typename V>
class AllNames{
        protected:
                T CurrAllNames;
        public:
                void AddOneName(V p){
                        this -> CurrAllNames += p.name;
                }
		void ShowAllNames(){
			std::cout << this -> CurrAllNames << std::endl;
		}
};

template <typename T, typename U>
class Person{
	protected:
		T age;
		U name;
		template <typename t, typename u> friend class AllNames;
	public:
		Person(T age, U name){
			this -> age = age;
			this -> name = name;
		}
};

int main(){
	Person <int, std::string> me(30, "zls");
	AllNames<std::string, Person<int, std::string>> allnames;
	allnames.AddOneName(me);
	allnames.AddOneName(me);
	allnames.ShowAllNames();
}

//======= 21 ======
#include <iostream>

int main(){
	std::string a = "zls";
	std::string b = "dsy";
	std::cout << a << " " << a.size() << " " << a.length() << std::endl;
	std::cout << a+b << (a+b).size() << " " << (a+b).length() << std::endl;
}

//===== 20 =====
//can we make friend class a template
#include <iostream>
template <typename T, typename U>
class Person{
	protected:
		template <typename V> friend class GetPerson; //here V should be a different name from those above
		T name;
		U age;
	public:
		Person(T name, U age){
			this -> name = name;
			this -> age = age;
		}
		void ShowPerson(){
			std::cout << this -> name << " " << this -> age << std::endl;
		}
};

template <typename T> 
class GetPerson{
	public:
		void ShowPerson(T p){
			std::cout << p.name << " " << p.age << std::endl;
		}
};

int main(){
	Person<std::string, int> me("zls", 30);
	me.ShowPerson();

	GetPerson<Person<std::string, int>> getme;
	getme.ShowPerson(me);
}

//======= 19 ======
#include <iostream>
#define INCLUDE_CLASS
#ifdef INCLUDE_CLASS
class Me{
	public:
		Me(){
			std::cout << "This is me" << std::endl;
		}
};
#endif

int main(){
	Me me;
}


//========= 18 ==========
//This is to test function overloading
#include <iostream>

int add(int a, int b){
	std::cout << " add_int: ";
	return a+b;
}

double add(double a, double b){
	std::cout << " add_double: ";
	return a+b;
}

float add(float a, float b){
	std::cout << " add_float: ";
	return a+b;
}

int add(int a){
	std::cout << " add_int_single ";
	return a;
}

double add(double a){
	std::cout << " add_double_single ";
	return a;
}

float add(float a){
	std::cout << " add_float_single ";
	return a;
}


int main(){
	int a = 2, b = 3;
	double c = 4, d = 5;
	float e = 6, f = 7;

	std::cout << add(a, b) << add(c, d) << add(e, f) << std::endl;
	std::cout << add(a) << add(c) << add(e) << std::endl;

}
//======= 17 ====
#include <iostream>

void not_swap(int a, int b){
	int tmp = a;
	a = b;
	b = tmp;
}

void swap(int &a, int &b){
	int tmp = a;
	a = b;
	b = tmp;
}

void swap_ptr (int *a, int *b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int main(){
	int a = 2, b = 3;
	not_swap(a, b);
	std::cout << a << b << std::endl;

	swap(a, b);
	std::cout << a << b << std::endl;

	a = 2; b = 3;
	swap_ptr(&a, &b);
	std::cout << a << b << std::endl;
}
//========= 16 =======
#include <iostream>

#define MaxNumPeople 5

struct Person{
	//it should use class as it contains private members
	public:
		std::string name;
		int age;
		std::string gender;
	
		Person(std::string name, int age, std::string gender) {
			this -> name = name;
			this -> age = age;
			this -> gender = gender;
		}
		Person(){}; // it seems this is a must-have function
		void InfoP(){
			std::cout << "\t " << this -> name << " " << this -> age << " " << this -> gender << std::endl;
		}
};

template <typename T, typename U, typename V> //here T is just Person
class Family{
	protected:
		friend class GetThisFamily;
		T AllMembers[MaxNumPeople];
		U current_numofpeople = 0;
		static V totalpeople; //count the total people of all families
	public:
		//no initialization functions
		void AddMember(T p){
			this -> totalpeople ++;
			this -> current_numofpeople ++;
			U ind = this -> current_numofpeople - 1;
			this -> AllMembers[ind] = p;
		}
		void GetFamily(){
			std::cout << "This family has " << this -> current_numofpeople << " people:" << std::endl;
			for (int i = 0; i < this -> current_numofpeople; i++){
				AllMembers[i].InfoP();
			}
		}
		V GetTotalPeople();
};

template <typename T, typename U, typename V> V Family<T, U, V>::totalpeople;

template <typename T, typename U, typename V> V Family<T, U, V>::GetTotalPeople(){
	return Family<T,U,V>::totalpeople;
}

//template <typename X> //T is just family in our case
class GetThisFamily{
	public:
		void ShowThisFamily(Family <Person, int, int> family){ 
			for (auto i = 0; i < family.current_numofpeople; i++)
				family.AllMembers[i].InfoP();
		}
};


int main(){
	Person p1("zls", 30, "male");
	Person p2("dsy", 32, "female");
	//========= one family =========
	Family<Person, int, int> my_family;
	my_family.AddMember(p1);
	my_family.AddMember(p2);

	my_family.GetFamily();
	//========= second family =========
	Family<Person, int ,int> you_family;
	you_family.AddMember(p2);
	you_family.AddMember(p1);
	you_family.AddMember(p2);

	you_family.GetFamily();

	std::cout << my_family.GetTotalPeople() << std::endl;

	//======== friend class ========
	std::cout << "==================" << std::endl;
	GetThisFamily getyou;
	std::cout << "my_family:" << std::endl;
	getyou.ShowThisFamily(my_family);
}

// non-template type class implementation
class Family{
	protected:
		Person AllMembers[MaxNumPeople];
		int current_numofpeople = 0;

	public:
		//only provide add_member method to add family members
		Family(){}
		void AddMembers(Person p){
			this -> current_numofpeople ++;
			int ind = this -> current_numofpeople - 1;
			this -> AllMembers[ind] = p;
		};

		int GetTotalPeople(){
			return this -> current_numofpeople;
		}

		void ExamineFamily(){
			//Person allmembers = this -> AllMembers; //can not do this as c++ does not support passing arrays, only pointers
			Person *allmembers = this -> AllMembers;
			for (int i = 0; i < this -> current_numofpeople; i++){
				std::cout << allmembers[i].name << " " << allmembers[i].age << " " << allmembers[i].gender << std::endl;
			}
		}
};

int main(){
	Person p1 ("ZLS", 30, "male");
	Person p2 ("DSY", 32, "female");

	Family my_family;
	my_family.AddMembers(p1);
	my_family.AddMembers(p2);
	
	std::cout << my_family.GetTotalPeople() << std::endl;
	
	my_family.ExamineFamily();
}

//======= 15 ========
#include <iostream>
//bubble sort for different numeric types: int, float, double, etc.
template <typename T>
void bubble_sort(T *arr, int n){
	for (int i = 0; i <= n-2 ; i++){
		for (int j = i+1; j <= n-1; j++){
			if (arr[i] > arr[j]) {
				T tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
}

int main(){
	int a[5] = {2, 0, 3, -5, 9};
	bubble_sort(a, 5);

	for (auto ele : a)
		std::cout << ele << " ";
	std::cout << std::endl;
}

//======= 14 ======
#include <iostream>

template <typename T, typename U, typename V>
void output(T t, U u, V v){
	std::cout << "value: size -> ";
	std::cout << t << ": " << sizeof(T) << "; " << u << ": " << sizeof(U) << "; " << v << ": " << sizeof(V) << " ";
	std::cout <<sizeof(t)/sizeof(T) << " " << sizeof(u)/sizeof(U) << " " << sizeof(v)/sizeof(V) << std::endl;
}

int main(){
	//pass some constants to a template function
	output<int, float, double>(2.2, 3.2, 4.2);

	int a = 3;
	std::string b = "xxx";
	double c[2]={32, 3};
	output(a, b, c);
	std::cout << *c << sizeof(c) << std::endl;
}

//========== 13 =========
//This is to practice template function
#include <iostream>

int double_int(int a){ return a*2;}
double double_double(double a){ return a*2;}
float double_float(float a){ return a*2;}
//create a template that does the same functionality
template <typename T>
T double_type(T a){
	std::cout << "sizeof this type: " << sizeof(T) << std::endl;
	return a*2;
}

int main(){
	int a = 2;
	double b = 3;
	float c = 4;
	std::cout << double_int(a) << " " << double_double(b) << " " << double_float(c) << std::endl;

	auto aa = double_type(a);
	auto bb = double_type(b);
	auto cc = double_type(c);
	std::cout << sizeof(aa) << sizeof(bb) << sizeof(cc) << std::endl;
	std::cout << aa << bb << cc << std::endl;

}


//============= 12 ================
#include "preprocessing.h"
#include <iostream>

#ifdef OUTSIDE_ANIMAL
Animal::Animal(int a, int b){
	this -> a = a;
	this -> b = b;
}
void Animal::Get(){
	std::cout << this -> a << " " << this -> b << std::endl;
}
#endif 

int main(){
	Animal a(2, 3);
	a.Get();
	std::cout << OUTSIDE_ANIMAL << std::endl;
}

//========= 11 ===========
#include <iostream>
#define max(a, b) (a>b? a:b) //MACRO functions can be very problematic
#define NUM_ELEMENTS 

#ifdef NUM_ELEMENTS //defined but without any value in it
//can not include more than MACROs
//std::cout << "xxxx" << std::endl;
#define XX 9
#endif
//void m(int a, int b){
//	a > b? a:b;
//}

int main(){
	std::cout << XX << std::endl;
	//here NUM_ELEMENTS is none, so there will be a compiling error
	//std::cout << NUM_ELEMENTS << std::endl;
	int a = 2;
	int b = 3;
	max(a, ++b);
	std::cout << b << std::endl;

	a = 2;
	b = 3;
	//define a function inside main()
	//lambda
	auto m = [](int a, int b){
		a > b? a:b;
	};
	m(a, ++b);
	std::cout << b << std::endl;
}



//========= 10 ==========
//This is to practice preprocessing macros
//
#include <iostream>
#include "preprocessing.h"

#ifndef NUM_ELEMENTS
#define NUM_ELEMENTS 100
#endif

#if NUM_ELEMENTS > 10
#undef NUM_ELEMENTS //BETTER undefine it first before redefining it
#define NUM_ELEMENTS 10
#elif NUM_ELEMENTS > 5
#undef NUM_ELEMENTS
#define NUM_ELEMENTS 5
#endif

int main(){
	double a[NUM_ELEMENTS];
	for (int i = 0; i < NUM_ELEMENTS; i++)
		a[i] = i;
	for (auto ele : a){
		std::cout << ele << " ";
	}
	std::cout << std::endl;
}


//=========== 9 ===========
//This is to practice struct (EXCEPT the default visibility, struct and class are basically the same)
//choose between struct and class: as long as there is a private/protected variable, use class
#include <iostream>

struct Info{
	//by default everything is public
	std::string name;
	int age;
};

Info RetInfo(){
	Info me;
	me.name = "ZLS";
	me.age = 30;
	return me;
}

int main(){
	Info me = RetInfo();
	std::cout << me.name << " " << me.age << std::endl;
}



//=========== 8 ==========
//this is to practice friend class
#include <iostream>

class Customer{
	private:
		//name and age can be accessible in GetCustomer environment
		friend class GetCustomer; 
		std::string name;
		int age;
	public:
		Customer(std::string name, int age){
			this -> name = name;
			this -> age = age;
		}
};

class GetCustomer{
	public: //without this keywork, it will be private by default
	void OutputCustomer (Customer customer){
		std::cout << "name: " << customer.name << "; age: " << customer.age << std::endl;
	}
};

int main(){
	Customer customer("zls", 30);
	GetCustomer getcustomer;
	getcustomer.OutputCustomer(customer);
}

//========= 7 ========
//practice polymorphism
#include <iostream>

class Base{
	public:
		Base(int i) {std::cout << "Base ArgInit" << std::endl;}
		Base(){std::cout << "Base Init" << std::endl;}
		virtual void WhereAbout(){std::cout << "Base" << std::endl;}
		void Random(){std::cout << "Random_Base" << std::endl;}
};

class Control{
        public:
                Control(){}
                void WhereAbout(){std::cout << "Control" << std::endl;}
		void CC(){std::cout << "CC_Control" << std::endl;}
};


class Child_1: public Base, public Control { //multiple inheritence
	public:
		//it seems the base constructor without argument is called implicitly unless it's called explicitly
		Child_1(){std::cout << "Child_1 Init" << std::endl;}
		Child_1(int i): Base(i) {std::cout << "Child_1 ArgInit" << std::endl;}
		//method with the same name as in base class, it will be overridden
		void WhereAbout(); // we can call the function in the base class, if not we have to declare and implement it
		void Random(){std::cout << "Random_Child_1" << std::endl;}
		virtual void CC(){std::cout << "CC_Child_1" << std::endl;}
};

void Child_1::WhereAbout(){
	std::cout << "Child_1" << std::endl;
}

void base_whereabout(Base *b){
	b -> WhereAbout(); //use the function in the pointed class
	b -> Random(); // use the function in the Base class
}

void control_whereabout(Control *c){
	//since both functions in the parsent class are non-virtual functions, so they will be called
	c -> WhereAbout();
	c -> CC();
}

void child_1_whereabout(Child_1 *c){
	c -> WhereAbout();
	c -> Random();
	c -> CC();
}

void child_1_whereabout_dot(Child_1 c){ //why & is used by someone else?
        c . WhereAbout();
        c . Random();
        c . CC();
}


int main(){
	Base c1; //DONT c1() if no arguments need to be passed
	c1.WhereAbout();

	std::cout << "======== Child_1 ======" << std::endl;
	Child_1 c2(2);
	c2.WhereAbout();
	
	std::cout << "======== Pure ========" << std::endl;
	//new creates a pointer pointing to Child_1, so the virtual functions in the type-cased class will be replaced
	Child_1 *c_ptr = new Child_1;
	c_ptr -> WhereAbout();
	std::cout << "***********" << std::endl;
	child_1_whereabout(c_ptr);
	
	//base_whereabout(new Base(2));
	std::cout << "========= Base Child_1 ========" << std::endl;
	base_whereabout(new Child_1(2));

	std::cout << "======== CC =========" << std::endl;
	control_whereabout(new Child_1);

	std::cout << "================" << std::endl;
	Child_1 C(2);
	child_1_whereabout_dot(C);
}


//============ 6 ===========
#include <iostream>
#include <cmath>

class Rectangle{
	protected:
		double height, width;

	public:
		Rectangle(double, double);
		Rectangle(){}
		~Rectangle(){std::cout << "Destroying Rectangle Instance " << this->height << std::endl;}

		void SetAll(double, double);
		double Area();
		double GetHeight(){return this -> height;}
		double GetWidth(){return this -> width;}
};
Rectangle::Rectangle(double h, double w){
	this -> height = h;
	this -> width =w;
}
void Rectangle::SetAll(double h, double w){
	this -> height = h;
	this -> width = w;
}
double Rectangle::Area(){
	return this->height * this->width;
}

double make_h(int i){
	return i;
}
double make_w(int i){
	return pow(i, 3);
}

int main(){
	//Rectangle is just like a datatype, e.g. int, dboule, etc., so we can create an array of this type
	Rectangle rec[2]; //this array is only destroyed just before exting main()

	std::cout << rec << " " << sizeof(double) << " " << sizeof(rec) << std::endl;
	
	for (int i = 1; i <=2; i++){
		int rec_ind = i - 1;
		rec[rec_ind].SetAll(make_h(i), make_w(i));
		std::cout << rec[rec_ind].GetHeight() << " " << rec[rec_ind].GetWidth() << " " << rec[rec_ind].Area() << std::endl;
	}
	//new and delete provide the possibility of controling allocating and deallocating objects at will
	Rectangle *rec_3 = new Rectangle(4, 44);
	std::cout << rec_3->Area() << std::endl;
	delete rec_3; // WITHOUT this line, seems the destructor is not called

	Rectangle *rec_arr = new Rectangle[3];
	for (int i = 4; i < 7; i++){
		rec_arr[i-4].SetAll(make_h(i+1), make_w(i+1));
		std::cout << rec_arr[i-4].GetHeight() << " " << rec_arr[i-4].GetWidth() << " " << rec_arr[i-4].Area() << std::endl;
	}
	delete [] rec_arr; //not sure why [] is needed here while it is not in the following array example

	//================
	int *t_1 = new int;
	delete t_1;
	double *t_2 = new double[3] {2, 3, 4};
	std::cout << t_2[0] << t_2[1] << t_2[2] << std::endl;	
	delete t_2;

	std::cout << "End of main, but the variables in this scope will be destroyed after this line." << std::endl;
}


//=========== 5 ========
//This is to practice virtual class with override
#include <iostream>
#include <cmath>

class Shape{
	protected:
		int s = 2323;
	public:
		//return some common properties
		//virtual functions with no implimentation, so add "= 0" after it
		virtual std::string Instance_Shape() = 0;
		virtual double Instance_Area() = 0;
		//int get_s(){
		//	return this -> s;
		//}
};

class Rectangle: public Shape{
	protected:
		double height;
		double width;
	public:
		Rectangle(double height, double width){
			this -> height = height;
			this -> width = width;
		}
		std::string Instance_Shape() override {
			return "Rectangle";
		}
		double Instance_Area() override final { //final: the child classes can not override this function
			return this -> height * this -> width;
		}
};

class Square: public Rectangle{
	public:
		Square(double side): Rectangle(side, side){}
		std::string Instance_Shape() override {
			return "Square";
		}
		int get_s(){
			return this-> s;
		}
};

void output_rectangle(Rectangle rec){ //when to use Rectangle&??
	std::cout << "Shape: " << rec.Instance_Shape() << "; Area: " << rec.Instance_Area() << std::endl;
}

class Circle: public Shape{
	protected:
		double radius;
	public:
		Circle(double radius){
			this -> radius = radius;
		}
		std::string Instance_Shape() override {
			return "Circle";
		}
		double Instance_Area() override {
			return M_PI * std::pow(this -> radius, 2);
		}
};

void output_circle(Circle cir){
	std::cout << "Shape: " << cir.Instance_Shape() << "; Area: " << cir.Instance_Area() << std::endl;
}

void output_shape(Shape &shape){ //can not use "Shape shape" as abstract class Shape can not have instances, but can have pointer like variable
	std::cout << "Shape: " << shape.Instance_Shape() << "; Area: " << shape.Instance_Area() << std::endl;
} 

int main(){
	//Shape shape; // the abstract class can not be instantiated
	Rectangle rec_1(2, 3), rec_2(4, 5);
		
	//std::cout << "Shape: " << rec_1.Instance_Shape() << "; Area: " << rec_1.Instance_Area() << std::endl;
	//std::cout << "Shape: " << rec_2.Instance_Shape() << "; Area: " << rec_2.Instance_Area() << std::endl;
	output_rectangle(rec_1);
	output_rectangle(rec_2);

	std::cout << std::endl << std::endl;
	
	Circle cir_1(1), cir_2(2);
	output_circle(cir_1);
	output_circle(cir_2);
	
	std::cout << std::endl << std::endl;
	output_shape(rec_1);
	output_shape(rec_2);
	output_shape(cir_1);
	output_shape(cir_2);

	std::cout << std::endl << std::endl;
	Square sqr(2);
	output_shape(sqr);
	std::cout << sqr.get_s() << std::endl;
}


//========== 4 ==========
//This is to comprehensively practice static syntax
//static variable in a function
#include <iostream>

void static_1(){
	//static is something like the mutables passed into a python closure
	static int a = 2;
	static double b[3] = {2.1, 3};
	int num_elements = sizeof(b)/sizeof(b[0]);
	a ++;
	for (int i = 0; i < num_elements; i++){
		b[i] ++;
	}
	
	std::cout << "a: " << a << " b: ";
	for (auto ele : b){
		std::cout << ele << " ";
	}	
	std::cout << std::endl;
}

//To test that static variables last till the end of the life of the program, we take class as an example
class Test_Static_LifeTime{
	private:
		int order;
	public:
		Test_Static_LifeTime(int);
		~Test_Static_LifeTime();
};

Test_Static_LifeTime::Test_Static_LifeTime(int order){
	this -> order = order;
	std::cout << "Test_Static_LifeTime_" << order << std::endl;
}

Test_Static_LifeTime::~Test_Static_LifeTime(){
	std::cout << "Destroying " << this -> order << std::endl;
}

//To test static variables/functions in class
class Static{
	private:
		int MaxNumIns = 3;
		int order;
		static int current_num_ins; //even though is private, it can still be initialized outside of class
	public:
		Static(int order){
			this -> order = order;
			current_num_ins ++;
			if (Static::GetCurrentnumins() > MaxNumIns){
				std::cout << "ERROR: exceeded the maxium number of objects allowed to create!!" << std::endl;
				this -> ~Static();
				std::cout << "\tDone fake deleting " << this -> order << " i.e. only executing the destructor." << std::endl;
			}
		}
		~Static(){
			std::cout << "Destroying " << this -> order << std::endl;
		}

		static int GetCurrentnumins(){
			return Static::current_num_ins;
		}

};
int Static::current_num_ins = 0; //it can only be initialized like this? I.E. outside of the original class and main function


int main(){
	static_1();
	static_1();
	if (true){ //LOWER-CASE
		Test_Static_LifeTime o_1(1);
		for (int i = 1; i < 1000000; i++)
			i*i;
		std::cout << "end of if " << std::endl;
		//looks like o_1 is alive till the end of if statement
	}
	//the class objects are destroyed in reverse order
	if (false){
		Test_Static_LifeTime o_2(2);
		Test_Static_LifeTime o_3(3);
	}
	std::cout << "\n\n==========\n";	
	Static me_1(1);
	Static me_2(2);
	Static me_3(3);
	Static me_4(4);
	Static me_5(5);

	//class::attribute or method, inside the class this->, object: obj.public_attribute or function
	std::cout << "the value of the static variable is shared among the objects " << Static::GetCurrentnumins() << me_1.GetCurrentnumins() << me_2.GetCurrentnumins() << std::endl;
	std::cout << "end of main" << std::endl;
}


//============= 3 ==========
//practice class
#include <iostream>

//test static variable which accumulates over the whole period of the program
void test_static_variable(){
	static int a = 9;
	a ++;
	std::cout << a << std::endl;
}
//test_static_variable::a = 9; // can not assign a static variable outside of a function
class Animal {
protected:
	//these can not be accessed by class instances directly
	std::string name;
	double height;
	double weight;
	static int numofanimals; //can not initialize non-const static variable
public:
	int fake_static = this -> numofanimals;
	//std::cout << "******* fake_static: " << fake_static << std::endl; // you can not print here, it only allows types
	std::string height_unit = "cm";
	std::string weight_unit = "kg";
	Animal(std::string name, double height, double weight); // no return type
	Animal();
	~Animal();

	void SetName(std::string);
	void SetHeight(double);
	void SetWeight(double);
	
	//static function can be accessed by both clas itself and class instances
	static void SetNumofanimals(int num){
		//inside a static function, we can not access instance a
		numofanimals = num;
	}

	std::string GetName();
	double GetHeight();
	double GetWeight();

	static int GetNumofanimals(){
		//return this -> numofanimals;
		//return Animal::numofanimals;
		return numofanimals; //don't use this ->, otherwise Animal:: will not be able to access it
	}

	void ToString(){
		std::cout << this -> name << " " << this -> height << " " << this -> weight << std::endl;
	}		

}; //; is needed

int Animal::numofanimals = 0; //it has to be assigned outside of the class

Animal::Animal(std::string name, double height, double weight){
	//use this -> pointer to access attributes/methods in class definition
	this -> name = name; //looks like this pointer is necessary
	this -> height = height;
	this -> weight = weight;
	Animal::numofanimals ++;
}

Animal::Animal(){
	this -> name = "zls";
	this -> height = 0;
	this -> weight = 0;
	Animal::numofanimals ++;
}

Animal::~Animal(){
	std::cout << GetName() << " is destroyed!" << std::endl;
}

void Animal::SetName(std::string name){
	this -> name = name;
}

void Animal::SetHeight(double height){
	this -> height = height;
}

void Animal::SetWeight(double weight){
	this -> weight = weight;
}

std::string Animal::GetName(){
	return name;
}

double Animal::GetHeight(){
	return this -> height;
}

double Animal::GetWeight(){
	return this -> weight;
}

class Dog: public Animal {
	protected:
		std::string sound;
	public: 
		Dog(std::string, double, double, std::string);
		Dog(): Animal(){
			std::cout << "empty dog" << std::endl;
		}
		std::string MakeSound();


};

Dog::Dog(std::string name, double height, double weight, std::string sound):Animal (name, height, weight){
	this -> sound = sound;
}

std::string Dog::MakeSound(){
	return this -> sound;
}

// xx returns 1 while xx() returns 9;
int xx(){
	return 9;
}

int main(){
	test_static_variable();
	test_static_variable();

	//Animal::numofanimals = 3; // can not be accessed as it is protected
	//Animal::SetNumofanimals(4);
	Animal me;
	//me.SetNumofanimals(1);
	//use dot operator to access attribute/method by an object
	me.SetName("Seth Zhao");
	me.SetHeight(178);
	me.SetWeight(69);

	std::cout << "name: " << me.GetName() << " height: " << me.GetHeight() << me.height_unit << " weight: " << me.GetWeight() << me.weight_unit << std::endl;
	std::cout << Animal::GetNumofanimals() << std::endl;
	std::cout << "fake_static: " << me.fake_static << std::endl;
	me.ToString();

	Animal you("zls", 178, 69);
	std::cout << "name: " << you.GetName() << " height: " << you.GetHeight() << you.height_unit << " weight: " << you.GetWeight() << you.weight_unit << std::endl;
        std::cout << you.GetNumofanimals() << std::endl;
	std::cout << "fake_static: " << you.fake_static << std::endl;
	you.ToString();

	std::cout << "\n\n=============" << std::endl;
	//Dog::SetNumofanimals (2);
	Dog dog;
	std::cout << dog.GetName() << std::endl;
	dog.ToString();
	std::cout << "number of dogs: " << Animal::GetNumofanimals() << std::endl;

	Dog dog_zls ("dog_zls", 178, 69, "bark");
	dog_zls.ToString();
	std::cout << "number of dogs: " << Animal::GetNumofanimals() << std::endl;

	std::cout << "\n\nxx returns " << xx << " (" << xx() << ")" << std::endl; //why it returns 1????

	std::cout << "\n\n========== Destroying ======" << std::endl;
}

//========= 2 =========
#include "my_funcs/my_func_1.h" 

int main(){
	int a = 2;
	std::cout << a << " " << ret_square(a) << std::endl;
}

//=============== 1 ==============
#include <iostream> //std::count is in iostream

int ret_double(int a) {
	return a*2;
}

void change_arr(double *arr, int num_elements){
	//std::cout << "arr: " << arr << std::endl;
	//int num_elements = sizeof(arr)/sizeof(arr[0]);
	std::cout << "num_elements: " << num_elements << std::endl;
	for (int i = 0; i < num_elements; i++){
		arr[i] += 1;
	}
}

 int * create_arr(){
	static int a[3] = {1, 2, 3}; // this variable is only allocated once and the previous values carry through to the future
				     // its initialization is executed only once
	for (int i = 0; i < 3; i++)
		a[i] += 2;
	return a; // it returns an address
}


int main(){
	std::string sep_line = "\n\n==================\n";
	
	//just get started warming up my c++ memory
	std::cout << sep_line;
	int a;
	a = 3;
	std::cout << "first" << std::endl << "second\n"; //\n looks like the same as std::endl
	std::cout << "input: " << a << ", ret_double returned:" << ret_double(a) << "\n";

	//try some arrays	
	std::cout <<sep_line;
	int list[3] = {4, 5, 6};
	std::cout << list[0] << ": " << list[1] << ": " << list[2] << "\n";
	//iterate over an array
	std::cout << "char has size of " << sizeof(char) << std::endl;
	std::cout << "int has size of " << sizeof(int) << std::endl;
	std::cout << "float has size of " << sizeof(float) << std::endl;
	std::cout << "double has size of " << sizeof(double) << std::endl;
	std::cout << "the size of list is " << sizeof(list) << std::endl;
	for (auto ele : list){ 
		std::cout << "\t" << ele << " whose size is " << sizeof(ele) << std::endl;
	}
	//ele is declared inside the for loop, so it is not accessible after it, which is quite different form python
	//std::cout << ele << "\n";
	
	//try some pointers
	std::cout << sep_line;
	//float a = 3; // a was declared before
	//int a = 4;
	float c = 4;
	float *c_pr = &c; //c_pr contains the address of c, *c_pr refers to what is in c
	std::cout << c << "'s address is " << &c << std::endl; 
	std::cout << *c_pr << "'s address is " << c_pr << std::endl;
	int num_elements = 7;
	double arr [num_elements] = {2.1, 3.0};
	for (auto ele : arr){
		std::cout << "\t" << ele << std::endl;
	}
	// change array elements
	change_arr(arr, num_elements); //cpp does not take the entire array, but it takes the position of an array, and number of elements
	std::cout << "after being modified" << std::endl;
	for (auto ele : arr){
		std::cout << ele << std::endl;
	}
	int skip_first_elements = 3;
	skip_first_elements = skip_first_elements < num_elements ? skip_first_elements : num_elements;
	change_arr(&arr[skip_first_elements], num_elements - skip_first_elements);
	std::cout << "not modify the first element" << std::endl;
	for (auto ele : arr){
		std::cout << "\t" << ele << std::endl;
	}
	std::cout << "all add 200" << std::endl;
	int i = -1;
	for (auto ele : arr){ //ele is a new variable, which has the same value as the element, but in different location
		i ++;
		std::cout << &arr[i] << " =? " << &ele << std::endl;
		* (&ele) = ele +200;
		std::cout << ele << std::endl;
	}
	for (auto ele : arr){
		std::cout << "\t" << ele << std::endl;
	}
	
	//try a function which returns arrays
	int *new_arr;
	int num_ele = 3;
	new_arr = create_arr();
	for (int i = 0; i < num_ele; i++){
		//std::cout << new_arr[0];
		std::cout << *(new_arr+i) << std::endl;
	}
	new_arr = create_arr();
	for (int i = 0; i < num_ele; i++){
		std::cout << "\t" << *(new_arr + i) << std::endl;
	}
}
*/
