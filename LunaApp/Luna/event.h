#ifndef EVENT_H
#define EVENT_H

#include <algorithm>
#include <vector>

#include "delegate.h"

template<typename F>
class Event;

template<typename R, typename... Args>
class Event<R(Args...)> {
private:
    using DelT = Delegate<R(Args...)>;

    std::vector<DelT> mDelegates;
public:
    template<typename T, R(T::*method)(Args...)>
    void subscribe(T * p) {
        mDelegates.emplace_back();
        mDelegates.back().bind<T, method>(p);
    }

    template<R(*function)(Args...)>
    void subscribe() {
        mDelegates.emplace_back();
        mDelegates.back().bind<function>(p);
    }

    bool unsubscribe(const DelT & delegate) {
        auto it = std::find(mDelegates.begin(), mDelegates.end(), delegate);
        if (it == mDelegates.end()) {
            return false;
        } else {
            *it = std::move(mDelegates.back());
            mDelegates.pop_back();
            return true;
        }
    }

    template<typename T, R(T::*method)(Args...)>
    bool unsubscribe(T * p) {
        DelT delegate;
        delegate.bind<T, method>(p);
        return unsubscribe(delegate);
    }

    template<typename T, R(*function)(Args...)>
    bool unsubscribe(T * p) {
        DelT delegate;
        delegate.bind<function>(p);
        return unsubscribe(delegate);
    }

    void operator()(Args... args) {
        for (auto & delegate : mDelegates) {
            delegate(Args(args)...);
        }
    }

    size_t size() { return mDelegates.size(); }
    void unsubscribeAll() { mDelegates.clear(); }
};

#endif // EVENT_H
