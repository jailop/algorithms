#include "weathersubject.h"
#include "weatherobserver.h"

int main() {
    WeatherSubject ws = WeatherSubject();
    WeatherObserver wo1 = WeatherObserver();
    WeatherObserver wo2 = WeatherObserver();
    ws.attach(&wo1);
    ws.attach(&wo2);
    ws.setWeather(35);
}
