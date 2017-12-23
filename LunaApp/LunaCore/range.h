#ifndef RANGE_H
#define RANGE_H

template<typename T>
class RangeIterable {
private:
    class Iterator {
    public:
        Iterator(T value) :
            mValue(value)
        {}

        Iterator & operator++() {
            ++mValue;
            return *this;
        }

        bool operator==(const Iterator & other) const {
            return mValue == other.mValue;
        }

        bool operator!=(const Iterator & other) const {
            return !(*this == other);
        }

        T operator*() const {
            return mValue;
        }
    private:
        T mValue;
    };

public:
    constexpr RangeIterable(T from, T to) :
        mFrom(from),
        mTo(to)
    {}

    Iterator begin() {
        return Iterator(mFrom);
    }

    Iterator end() {
        return Iterator(mTo);
    }

private:
    const T mFrom;
    const T mTo;
};

template<typename T>
RangeIterable<T> range(T from, T to) {
    return  RangeIterable<T>(from, to);
}


template<typename T>
RangeIterable<T> range(T to) {
    return  RangeIterable<T>(0, to);
}

#endif // RANGE_H
