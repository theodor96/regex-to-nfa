#ifndef UTILS_H
#define UTILS_H

#include <memory>
#include <cmath>

#define SMART_ALIASES(CLASS)                                                  \
    using Self        = CLASS;                                                \
    using Ptr         = Utils::Ptr<Self>;                                     \
    using Weak        = Utils::WeakPtr<Self>;                                 \
    using Shared      = Utils::SharedPtr<Self>;                               \
                                                                              \
    template<typename... Args>                                                \
    static Ptr MakePtr(Args&&... args)                                     \
    {                                                                         \
        return Utils::MakePtr<Self, Args...>(std::forward<Args>(args)...); \
    }                                                                         \
                                                                              \
    template<typename... Args>                                                \
    static Ptr MakeShared(Args&&... args)                                     \
    {                                                                         \
        return Utils::MakeShared<Self, Args...>(std::forward<Args>(args)...); \
    }                                                                         \
                                                                              \
    using ConstPtr    = Utils::Ptr<const Self>;                               \
    using ConstWeak   = Utils::WeakPtr<const Self>;                           \
    using ConstShared = Utils::SharedPtr<const Self>


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
    namespace detail
    {
        template<class SmartT, typename TypeOfSmartT, typename... Args>
        typename std::enable_if
        <
            std::is_same<TypeOfSmartT, typename SmartT::Ptr>::value ||
                 std::is_same<TypeOfSmartT, typename SmartT::Shared>::value,
            TypeOfSmartT
        >::type MakeSmart(Args&&... args)
        {
            return TypeOfSmartT(new SmartT(std::forward<Args>(args)...));
        }
    }

    template<class T>
    using Ptr = std::unique_ptr<T>;

    template<class T>
    using SharedPtr = std::shared_ptr<T>;

    template<class T>
    using WeakPtr = std::weak_ptr<T>;
    
    template<class SmartT, typename... Args>
    typename SmartT::Ptr MakePtr(Args&&... args)
    {
        return detail::MakeSmart<SmartT, typename SmartT::Ptr, Args...>(std::forward<Args>(args)...);
    }

    template<class SmartT, typename... Args>
    typename SmartT::Ptr MakeShared(Args&&... args)
    {
        return detail::MakeSmart<SmartT, typename SmartT::Shared, Args...>(std::forward<Args>(args)...);
    }

    template<typename IntT>
    IntT getRandomBetween(IntT lo, IntT hi)
    {
        return qrand() % (hi - lo + 1) + lo;
    }

    template<typename PointT>
    PointT getRandomPointBetween(PointT lo, PointT hi)
    {
        return PointT(getRandomBetween(lo.x(), hi.x()), getRandomBetween(lo.y(), hi.y()));
    }

    template<typename PointT>
    PointT getMiddlePointBetween(PointT lhs, PointT rhs)
    {
        return PointT((lhs.x() + rhs.x()) / 2, (lhs.y() + rhs.y()) / 2);
    }

    template<class PointT>
    double DistanceBetweenPoints(const PointT& lhs, const PointT& rhs)
    {
        return std::hypot(lhs.x() - rhs.x(), lhs.y() - rhs.y());
    }
}

#endif // UTILS_H
