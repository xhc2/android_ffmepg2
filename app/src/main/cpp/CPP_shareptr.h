//
// Created by mrx on 2022/1/24.
//

#ifndef ANDROID_FFMEPG2_CPP_SHAREPTR_H
#define ANDROID_FFMEPG2_CPP_SHAREPTR_H

class CPP_shareptr{

public :
//    auto ptr;
    std::shared_ptr<int> ptr;
    std::shared_ptr<int> ptr2;
    void  start();
    void unique_ptr2();
    void weak_ptr2();
    void rightValue();
    void lumada2();
    ~CPP_shareptr();

};



#endif //ANDROID_FFMEPG2_CPP_SHAREPTR_H
