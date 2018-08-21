#pragma once

#include "custom_ptr.hpp"

template <typename T>
struct custom_allocator {
  using value_type = typename std::remove_cv<T>::type;
  using pointer = custom_ptr<value_type>;
  using reference = custom_ref<value_type>;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;

  custom_allocator() = default;
  custom_allocator(const custom_allocator&) = default;

  pointer allocate(size_type n) {
    return pointer(static_cast<value_type*>(std::malloc(sizeof(value_type)*n)));
  }

  void deallocate(pointer ptr, size_type n) {
    std::free(ptr.ptr_);
  }

  template<typename... Args>
  void construct(pointer ptr, Args&&... args) {
    new(ptr.ptr_) T(std::forward<Args>(args)...);
  }

  void destroy(pointer ptr) {
    ptr.ptr_->~T();
  }

  bool operator==(const custom_allocator&) const {
    return true;
  }

  bool operator!=(const custom_allocator& other) const {
    return !operator==(other);
  }

  template <class U>
  struct rebind {
    using other = custom_allocator<U>;
  };

};
