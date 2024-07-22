#ifndef _WEATHERSUBJECT_H
#define _WEATHERSUBJECT_H 0

#include <vector>
#include "subject.h"
#include "observer.h"

class WeatherSubject: Subject<int> {
    public:
        void setWeather(int grades);
        bool attach(Observer<int>* observer);
        bool deattach(Observer<int> *observer);
        void notify();
    private:
        int _grades = 0;
        std::vector<Observer<int>*> _observers;
};

#endif // _WEATHERSUBJECT_H
