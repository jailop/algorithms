#include "weathersubject.h"

void WeatherSubject::setWeather(int grades) {
    _grades = grades;
    notify();
}

bool WeatherSubject::attach(WeatherObserver* observer) {
    _observers.push_back(observer);
    return true;
}

bool WeatherSubject::deattach(WeatherObserver* observer) {
    bool flag = false;
    for (std::vector<WeatherObserver*>::iterator it = _observers.begin(); it != _observers.end(); it++) {
        if ((*it) == observer) {
            _observers.erase(it);
            flag = true;
            break;
        }
    }
    return flag;
}

void WeatherSubject::notify() {
    for (std::vector<WeatherObserver*>::iterator it = _observers.begin(); it != _observers.end(); it++) {
        (*it)->update(_grades);
    }
}
