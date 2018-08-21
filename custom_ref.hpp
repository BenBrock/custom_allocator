#pragma once

#include <stdexcept>

template <typename T>
struct custom_ptr;

template <typename T>
struct custom_ref {
  using element_type = T;
  using value_type = typename std::remove_cv<element_type>::type;
  using difference_type = std::ptrdiff_t;
  using pointer = custom_ptr<value_type>;
  using reference = custom_ref<value_type>;
  using iterator_category = std::random_access_iterator_tag;

  custom_ptr<value_type> ptr_;

  custom_ref(custom_ptr<value_type> ptr) : ptr_(ptr) {
    if (ptr_ == nullptr) {
      throw std::runtime_error("AGH! You made a null reference.  How untoward.");
    }
  }

  operator value_type() const {
    return ptr_.load();
  }

  custom_ref& operator=(const value_type& value) {
    ptr_.store(value);
  }

  custom_ptr<value_type> operator&() {
    return ptr_;
  }
};
