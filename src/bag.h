#pragma once
#include <algorithm>
#include <concepts>
#include <cstddef>
#include <cstdlib>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

template<typename T>
class Bag {
private:
  std::unique_ptr<T[]> items;
  std::size_t capacity = 0;
  std::size_t size = 0;

  void reserve(std::size_t needed)
  {
    if (needed <= capacity)
      return;

    std::size_t new_capacity = capacity == 0 ? 8 : capacity * 2;
    while (new_capacity < needed) {
      new_capacity *= 2;
    }

    auto new_items = std::make_unique<T[]>(new_capacity);

    for (std::size_t i = 0; i < size; i++) {
      new_items[i] = std::move(items[i]);
    }

    items = std::move(new_items);
    capacity = new_capacity;
  }

public:
  Bag(): capacity(10), size(0)
  {
    items = std::make_unique<T[]>(capacity);
  }
  ~Bag() = default;

  // copy
  Bag(const Bag& bag): capacity(bag.capacity), size(bag.size)
  {
    items = std::make_unique<T[]>(capacity);
    for (std::size_t i = 0; i < size; i++) {
      items[i] = bag.items[i];
    }
  }

  // assignment
  Bag& operator=(const Bag& bag)
  {
    auto new_items = std::make_unique<T[]>(bag.capacity);
    for (std::size_t i = 0; i < bag.size; i++) {
      new_items[i] = bag.items[i];
    }

    items = std::move(new_items);
    size = bag.size;
    capacity = bag.capacity;

    return *this;
  }

  void add_item(const T& item)
  {
    reserve(size + 1);
    items[size] = item;
    size++;
  }

  bool remove_item(const T& item)
  {
    for (std::size_t i = 0; i < size; i++) {
      if (items[i] == item) {
        if (i != size - 1) {
          items[i] = items[size - 1];
        }
        size--;
        return true;
      }
    }

    return false;
  }

  void remove_all_of(const T& item)
  {
    for (std::size_t i = 0; i < size;) {
      if (items[i] == item) {
        items[i] = items[size - 1];
        size--;
      } else {
        i++;
      }
    }
  }

  T pick_random()
  {
    if (size == 0) {
      throw std::runtime_error("can't call `pick_random` on an empty Bag...");
    }

    std::size_t i = std::rand() % size;

    auto pick = items[i];

    items[i] = items[size - 1];
    size--;

    return pick;
  }

  void dump()
  {
    size = 0;
  }

  void dump_into(Bag<T>& new_bag)
  {
    for (std::size_t i = 0; i < size; i++) {
      new_bag.add_item(items[i]);
    }

    this->dump();
  }

  std::size_t count(const T& item) const
  {
    std::size_t count = 0;
    for (std::size_t i = 0; i < size; i++) {
      if (items[i] == item) {
        count++;
      }
    }

    return count;
  }

  int number_of(const T& item) const
  {
    int count = 0;
    for (std::size_t i = 0; i < size; i++) {
      if (items[i] == item) {
        count++;
      }
    }
    return count;
  }

  bool contains(const T& item)
  {
    for (std::size_t i = 0; i < size; i++) {
      if (items[i] == item)
        return true;
    }
    return false;
  }

  std::string to_string()
  {
    if (size == 0)
      return "{}";

    std::ostringstream out_stream;

    out_stream << '{';

    for (std::size_t i = 0; i < size; i++) {
      out_stream << items[i];
      if (i < size - 1)
        out_stream << ", ";
    }

    out_stream << '}';

    return out_stream.str();
  }

  std::size_t get_size()
  {
    return size;
  }

  bool is_empty()
  {
    return size == 0;
  }
};
