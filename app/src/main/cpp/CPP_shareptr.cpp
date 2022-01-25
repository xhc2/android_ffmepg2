//
// Created by mrx on 2022/1/24.
//

#include <memory>
#include "CPP_shareptr.h"
#include "my_log.h"
using namespace std;
//shareptr 练习使用


class B :public  std::enable_shared_from_this<B>{
public:
    shared_ptr<B> getSelfRight(){
        return shared_from_this();
    }

    ~B() {
        LOGE(" delete B ");
    };
};

class A{

public:
    shared_ptr<A> getSelfWrong(){
        return shared_ptr<A>(this); //不能这么做 ，
    }
    ~A(){
        LOGE(" delete A ");
    }
};



void deletePtr(void *ptr){
    LOGE(" delete ptr %d ,  %p" ,*((int *)ptr) , ptr);
    delete ptr;
}




//share_ptr 需要注意避免导致循环引用
//share_ptr 中的指针计数是线程安全的，但是其中的资源是不安全的
void  CPP_shareptr::start(){
    ptr = make_shared<int>(100);
    ptr2 = std::shared_ptr<int> (new int(101) , deletePtr) ;
    std::shared_ptr<int> ptr3 = ptr2;

//    LOGE(" share count %d , %d , ptr2 %d ，ptr3 %d", ptr.use_count() , *ptr.operator->() , ptr2.use_count() , ptr3.use_count());
    ptr2.reset(new int(104));// 手动释放
//    LOGE(" RESET COUNT %d , %d " , ptr2.use_count()  ,  ptr3.use_count());
//    std::shared_ptr<int> p = new int(1);  error 不能将裸指针赋予 智能指针s

    std::shared_ptr<int> p4(new int(1) , [](int *p ){
        LOGE(" delete share lamda ptr %p" , p);
        delete p;
    });


    std::shared_ptr<int> p5(new int[10] , [](int *p ){
        LOGE(" delete share lamda shuzu ptr %p" , p);
        delete []p;
    });


    //如下调用，指向的内容都是同样的，但是会导致两次的析构，会导致错误
//    shared_ptr<A> a(new A);
//    shared_ptr<A> b = a->getSelfWrong();
//    LOGE(" a %d , b %d " , a.use_count() , b.use_count());

    //如下调用正确,只会一次析构
    shared_ptr<B> b1(new B);
    shared_ptr<B> b2 = b1->getSelfRight() ;
    LOGE(" B1 %d , B2 %d " , b1.use_count() , b2.use_count());


//    int count = 100;
//    while(count -- > 0){
//        LOGE(" count %d " , count );
//    }
    LOGE("----- end -----"  );
}


//unique_ptr 是独占性指针，且会自动释放
//unique_ptr 可以指向数组
void  CPP_shareptr::unique_ptr2(){
    unique_ptr<int> ptr1(new int(100));
//    unique_ptr<int> ptr2 = ptr1;//独占性指针，不能复制

    unique_ptr<int> ptr3 = std::move(ptr1);//ptr1 的资源被转移

    if(ptr1 == NULL){
        LOGE("----- ptr1 NULL-----"  );
    }
    if(ptr3 == NULL ){
        LOGE("----- ptr3 NULL-----"  );
    }

    shared_ptr<int> ptr10(new int(100) , [](int *p){delete p;}); //正确
//    unique_ptr<int> ptr12(new int(100) , [](int *p){delete p;}); //错误
    unique_ptr<int , void (*)(int *)> ptr13(new int(100) ,[](int *p){delete p;}); //正确

//    shared_ptr<int[]> ptr13(new int[10]); 错误，shapre 不能指向数组


    unique_ptr<int[]> ptr14(new int[100]);
    ptr14[99] = 100;
    LOGE(" PTR %d" , ptr14[99]);

    LOGE("----- end unique_ptr-----"  );
}



/**
 * weakptr 不管理生命周期
 * weak_ptr 是一种不控制对象生命周期的智能指针, 它指向一个 shared_ptr 管理的对象. 进行该对象的内
存管理的是那个强引用的shared_ptr， weak_ptr只是提供了对管理对象的一个访问手段。weak_ptr 设
计的目的是为配合 shared_ptr 而引入的一种智能指针来协助 shared_ptr 工作, 它只可以从一个
shared_ptr 或另一个 weak_ptr 对象构造, 它的构造和析构不会引起引用记数的增加或减少。weak_ptr
是用来解决shared_ptr相互引用时的死锁问题，如果说两个shared_ptr相互引用，那么这两个指针的引
用计数永远不可能下降为0，资源永远不会释放。它是对对象的一种弱引用，不会增加对象的引用计数，
和shared_ptr之间可以相互转化，shared_ptr可以直接赋值给它，它可以通过调用lock函数来获得
shared_ptr。

 weak_ptr 不能直接操作对应的资源
 */
void CPP_shareptr::weak_ptr2(){
    shared_ptr<int> ptr(new int(100));
    weak_ptr<int> ptr2 = ptr;
    LOGE(" PTR count %d" , ptr.use_count());


    weak_ptr<int> wp ;
    {
        std::shared_ptr<int> ap(new int(10));
        wp = ap ;
    }

    if(!wp.expired()){
        //没有被释放
        std::shared_ptr<int> tmp = wp.lock();
        LOGE(" shapre weak %d" , tmp.operator*());
    }

    LOGE(" ----- END WEAK -------");
}


class R{
public :
    R():ptr(new int(10)){
        LOGE(" R START ");
    }
    R(const R& a) :ptr(new int(*a.ptr)) {
        LOGE("copy constructor A");
    }
    R(R&& a) :ptr(a.ptr) {
        a.ptr = nullptr; LOGE("move constructor A");
    }
    ~R(){
        LOGE(" R del ");
        delete  ptr ;
        ptr = NULL;
    }
private:
    int *ptr ;
};


R Get(bool flag){
    R r ;
    R g ;
    LOGE(" READY return ");
    if(flag){
        return r;
    }
    else return g;

}

/**
 * 右值引用，需要再去对深浅copy理解下，现在还不太能直接理解
 */
void CPP_shareptr::rightValue(){
    {
        //这里需要把c98 的深浅copy 学习
        R r = Get(false);//这样会crash ， 因为r和 g 指向的ptr 都是同一个指针
    }

    LOGE(" RIGHT finish ! " );
}

void  CPP_shareptr::lumada2(){
    auto add = [](int a, int b)->int{
        return a + b;
    };
    LOGE(" a + b = %d " , add(10 , 2));
}


CPP_shareptr::~CPP_shareptr(){
//    LOGE("del share count %d ", ptr.use_count());

}