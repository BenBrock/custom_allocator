#pragma once

#include "custom_ref.hpp"

template <typename T>
struct custom_ptr {
  using element_type = T;
  using value_type = typename std::remove_cv<element_type>::type;
  using difference_type = std::ptrdiff_t;
  using pointer = custom_ptr<value_type>;
  using reference = custom_ref<value_type>;
  using iterator_category = std::random_access_iterator_tag;

  value_type* ptr_ = nullptr;

  custom_ptr() = default;
  custom_ptr(const custom_ptr& ptr) = default;

  custom_ptr(value_type* ptr) : ptr_(ptr) {}

  value_type load() const {
    return *ptr_;
  }

  void set(const value_type& value) {
    *ptr_ = value;
  }

  reference operator*() {
    return reference(*this);
  }

  custom_ptr operator+(difference_type diff) {
    custom_ptr ptr = *this;
    ptr += diff;
    return ptr;
  }

  custom_ptr operator-(difference_type diff) {
    custom_ptr ptr = *this;
    ptr -= diff;
    return ptr;
  }

  difference_type operator-(custom_ptr ptr) {
    return ptr_ - ptr.ptr_;
  }

  custom_ptr& operator++() {
    ptr_++;
    return *this;
  }

  custom_ptr& operator++(int) {
    ptr_++;
    return *this;
  }

  custom_ptr& operator--() {
    ptr_--;
    return *this;
  }

  custom_ptr& operator--(int) {
    ptr_--;
    return *this;
  }

  custom_ptr& operator+=(difference_type diff) {
    ptr_ += diff;
    return *this;
  }

  custom_ptr& operator-=(difference_type diff) {
    ptr_ -= diff;
    return *this;
  }

  bool operator==(const custom_ptr<value_type>& ptr) const {
    return ptr_ == ptr.ptr_;
  }

  bool operator!=(const custom_ptr<value_type>& ptr) const {
    return !(*this == ptr);
  }
};
