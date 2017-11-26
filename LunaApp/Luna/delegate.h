#ifndef DELEGATE_H
#define DELEGATE_H

#include <cstddef>

template<typename F>
class Delegate;

template<typename R, typename... Args>
class Delegate<R(Args...)> {
private:
    void * mTarget;
    R(*mFunctionPointer)(void *, Args...);

    template<R(*function)(Args...)>
    static R functionProxy(void * self, Args... args) {
        function(std::forward<Args>(args)...);
    }

    template<typename T, R(T::*method)(Args...)>
    static R methodProxy(void * self, Args...  args) {
        T * p = static_cast<T *>(self);
        (p->*method)(std::forward<Args>(args)...);
    }
public:
    Delegate() :
        mTarget(nullptr),
        mFunctionPointer(nullptr)
    {}

    template<typename T, R(T::*method)(Args...)>
    void bind(T * self) {
        mTarget = static_cast<void *>(self);
        mFunctionPointer = methodProxy<T, method>;
    }

    template<R(*function)(Args...)>
    void bind() {
        mTarget = nullptr;
        mFunctionPointer = functionProxy<function>;
    }

    void unbind() {
        mTarget = nullptr;
        mFunctionPointer = nullptr;
    }

    void operator()(Args... args) const {
        mFunctionPointer(mTarget, std::forward<Args>(args)...);
    }

    bool operator==(const Delegate & other) const {
        return (mTarget == other.mTarget) && (mFunctionPointer == other.mFunctionPointer);
    }

    bool operator!=(const Delegate & other) const {
        return !(*this == other);
    }

    operator bool() const {
        return mFunctionPointer != nullptr;
    }

    bool operator==(const std::nullptr_t) const {
        return (*this);
    }

    bool operator!=(const std::nullptr_t) const {
        return !(*this);
    }
};

#endif // DELEGATE_H
