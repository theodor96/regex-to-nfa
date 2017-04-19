#ifndef UTILS_H
#define UTILS_H

#include <memory>

#define NO_COPY(CLASS) \
    CLASS(const CLASS&) = delete; \
    CLASS& operator=(const CLASS&) = delete;

#define NO_MOVE(CLASS) \
    CLASS(CLASS&&) = delete; \
    CLASS& operator=(CLASS&&) = delete;

#define NO_COPY_NO_MOVE(CLASS) \
    NO_COPY(CLASS) \
    NO_MOVE(CLASS)

namespace Utils
{
    /*template<class SmartT, typename... Args>
    typename SmartT::Ptr NewPtr(Args&&... args)
    {
        return SmartT::Ptr(new SmartT(std::forward<Args>(args)...));
    }*/

    template<class T>
    using Ptr = std::unique_ptr<T>;

    template<class T>
    using SharedPtr = std::shared_ptr<T>;

    template<class SmartT>
    class NewPtr
    {
        template <typename... Args>
        typename SmartT::Ptr operator()(Args&&... args)
        {
            return SmartT::Ptr(new SmartT(std::forward<Args>(args)...));
        }
    };
}

#endif // UTILS_H
