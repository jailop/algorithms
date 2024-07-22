#include <iostream>
#include "weatherobserver.h"

void WeatherObserver::update(int& value) {
    std::cout << value << std::endl;    
}
