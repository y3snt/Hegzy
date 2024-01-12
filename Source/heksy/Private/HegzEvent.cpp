#include "HegzEvent.h"
#include "EventHandler.h"

template <typename... Args> 
void HegzEvent<Args...>::operator()(Args... params) const
{
    for (const auto& handler : Handlers)
    {
        handler(params...);
    }
}

template <typename... Args> 
/*inline*/ HegzEvent<Args...>& HegzEvent<Args...>::operator+=(const std::function<void(Args...)>& handler)  // ew. check if same handler is not added twice... but ==
{
    Add(handler);
    return *this;
}

template <typename... Args> 
/*inline*/ HegzEvent<Args...>& HegzEvent<Args...>::operator+=(const EventHandler<Args...>& handler)
{
    AddHandler(handler);
    return *this;
}

template <typename... Args> 
/*inline*/ bool HegzEvent<Args...>::operator-=(const EventHandler<Args...>& handler)
{
    return RemoveHandler(handler);
}

template <typename... Args> 
/*inline*/ void HegzEvent<Args...>::Add(const std::function<void(Args...)>& handler)  // ? remove explicit
{
    AddHandler(EventHandler<Args...>(handler));
}

template <typename... Args> 
void HegzEvent<Args...>::AddHandler(const EventHandler<Args...>& handler)
{
    Handlers.push_back(handler);
}

template <typename... Args> 
bool HegzEvent<Args...>::RemoveHandler(const EventHandler<Args...>& handler)
{
    auto it = std::find(Handlers.begin(), Handlers.end(), handler);
    if (it != Handlers.end())
    {
        Handlers.erase(it);
        return true;
    }

    return false;
}


