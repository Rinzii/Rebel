#pragma once
#include <memory>

namespace rebel
{
    template <typename Type>
    requires(std::is_array_v<Type>)
    auto make_unique_for_overwrite(std::size_t element_count)
{
#if defined(REBEL_MUFO)
    return std::make_unique_for_overwrite<Type>(element_count);
#else
    return std::make_unique<Type>(element_count);
#endif
}
} // namespace rebel
