#ifndef _SUBJECT_H
#define _SUBJECT_H 0

#include "observer.h"

template<typename StateType>
class Subject {
    public:
        virtual bool attach(Observer<StateType>* observer);
        virtual bool deattach(Observer<StateType> *observer);
        virtual void notify();
};

#endif // _SUBJECT_H
