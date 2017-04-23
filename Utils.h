#ifndef UTILS_H
#define UTILS_H

#include <memory>

#define NO_COPY(CLASS) \
    CLASS(const CLASS&) = delete; \
    CLASS& operator=(const CLASS&) = delete

#define NO_MOVE(CLASS) \
    CLASS(CLASS&&) = delete; \
    CLASS& operator=(CLASS&&) = delete

#define NO_COPY_NO_MOVE(CLASS) \
    NO_COPY(CLASS); \
    NO_MOVE(CLASS)

namespace Utils
{
    template<class T>
    using Ptr = std::unique_ptr<T>;

    template<class T>
    using SharedPtr = std::shared_ptr<T>;
    
    template<class SmartT, typename... Args>
    typename SmartT::Ptr NewPtr(Args&&... args)
    {
        return SmartT::Ptr(new SmartT(std::forward<Args>(args)...));
    }

    template<typename IntT>
    IntT getRandomBetween(IntT lo, IntT hi)
    {
        return qrand() % (hi - lo + 1) + lo;
    }

    template<class PointT>
    double DistanceBetweenPoints(const PointT& lhs, const PointT& rhs)
    {
        return qSqrt(qPow(lhs.x() - rhs.x(), 2) + qPow(lhs.y() - rhs.y(), 2));
    }
}

#endif // UTILS_H
