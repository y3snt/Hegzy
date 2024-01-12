#include "EventHandler.h"

template<class... Args>
EventHandler<Args...>::EventHandler(const std::function<void (Args...)> &Func) : HandlerFunc(Func) {}

template<class... Args>
void EventHandler<Args...>::operator()(Args... params) const  // EventHandler(...) operator overloading
{
    if (HandlerFunc)
    {
        HandlerFunc(params...);
    }
}
