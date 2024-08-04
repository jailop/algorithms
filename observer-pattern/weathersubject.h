#ifndef _WEATHERSUBJECT_H
#define _WEATHERSUBJECT_H 0

#include <vector>
#include "subject.h"
#include "weatherobserver.h"

class WeatherSubject: Subject<int> {
    public:
        void setWeather(int grades);
        bool attach(WeatherObserver* observer);
        bool deattach(WeatherObserver* observer);
        void notify();
    private:
        int _grades = 0;
        std::vector<WeatherObserver*> _observers;
};

#endif // _WEATHERSUBJECT_H
