#ifndef _OBSERVER_H
#define _OBSERVER_H 0

template<typename StateType>
class Observer {
    public:
        virtual void update(StateType& value);
};

#endif // _OBSERVER_H
