#ifndef __TRAITS_HPP
#define __TRAITS_HPP

#include <type_traits>

#if __cplusplus < 202002L
#error "This code requires C++20 or later. Please use a C++20 compatible compiler."
#endif

namespace traits {

class __TraitBase {
};

template<typename T>
concept IsTrait = std::is_base_of_v<__TraitBase, T>;

#define TRAIT : public traits::__TraitBase

template<IsTrait... Ts>
class impl_checker : public Ts... {};

#define IMPL(...) : public traits::impl_checker<__VA_ARGS__>

} // namespace traits

#endif // __TRAITS_HPP
