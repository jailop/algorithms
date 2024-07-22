#ifndef _WEATHEROBSERVER_H
#define _WEATHEROBSERVER_H 0

#include "observer.h"

class WeatherObserver: Observer<int> {
    void update(int& value);
};

#endif // _WEATHEROBSERVER_H
