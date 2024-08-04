#include <iostream>
#include <vector>

class WeatherObserver {
    public:
        void update(int& value);
};

class WeatherSubject {
    public:
        void setWeather(int grades);
        bool attach(WeatherObserver* observer);
        bool deattach(WeatherObserver* observer);
        void notify();
    private:
        int _grades = 0;
        std::vector<WeatherObserver*> _observers;
};

void WeatherObserver::update(int& value) {
    std::cout << value << std::endl;    
}

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

int main() {
    WeatherSubject ws = WeatherSubject();
    WeatherObserver wo1 = WeatherObserver();
    WeatherObserver wo2 = WeatherObserver();
    ws.attach(&wo1);
    ws.attach(&wo2);
    ws.setWeather(35);
}
