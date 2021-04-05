#pragma once

#include <memory>

template<typename T>
struct EnableSharedFromThisVirtual;

class EnableSharedFromThisVirtualBase : public std::enable_shared_from_this<EnableSharedFromThisVirtualBase>
{
    typedef std::enable_shared_from_this<EnableSharedFromThisVirtualBase> base_type;
    template<typename T>
    friend struct EnableSharedFromThisVirtual;

    std::shared_ptr<EnableSharedFromThisVirtualBase> shared_from_this()
    {
        return base_type::shared_from_this();
    }
    std::shared_ptr<EnableSharedFromThisVirtualBase const> shared_from_this() const
    {
        return base_type::shared_from_this();
    }
};

template<typename T>
struct EnableSharedFromThisVirtual: virtual EnableSharedFromThisVirtualBase
{
    typedef EnableSharedFromThisVirtualBase base_type;

 public:
    std::shared_ptr<T> shared_from_this()
    {
        std::shared_ptr<T> result(base_type::shared_from_this(), static_cast<T*>(this));
        return result;
    }

    std::shared_ptr<T const> shared_from_this() const
    {
        std::shared_ptr<T const> result(base_type::shared_from_this(), static_cast<T const*>(this));
        return result;
    }
};