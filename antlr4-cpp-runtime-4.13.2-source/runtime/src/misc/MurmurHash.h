﻿/* Copyright (c) 2012-2017 The ANTLR Project. All rights reserved.
 * Use of this file is governed by the BSD 3-clause license that
 * can be found in the LICENSE.txt file in the project root.
 */

#pragma once

#include <vector>
#include <cstddef>
#include <cstdint>
#include <type_traits>

#include "antlr4-common.h"

namespace antlr4 {
namespace misc {

  class ANTLR4CPP_PUBLIC MurmurHash final {
  private:
    static constexpr size_t DEFAULT_SEED = 0;

    /// Initialize the hash using the default seed value.
    /// Returns the intermediate hash value.
  public:
    static size_t initialize() { return initialize(DEFAULT_SEED); }

    /// Initialize the hash using the specified seed.
    static size_t initialize(size_t seed) { return seed; }

    /// Update the intermediate hash value for the next input {@code value}.
    /// <param name="hash"> the intermediate hash value </param>
    /// <param name="value"> the value to add to the current hash </param>
    /// Returns the updated intermediate hash value.
    static size_t update(size_t hash, size_t value);

    /**
     * Update the intermediate hash value for the next input {@code value}.
     *
     * @param hash the intermediate hash value
     * @param value the value to add to the current hash
     * @return the updated intermediate hash value
     */
    template <class T>
    static size_t update(size_t hash, Ref<T> const& value) {
      return update(hash, value != nullptr ? value->hashCode() : 0);
    }

    template <class T>
    static size_t update(size_t hash, T *value) {
      return update(hash, value != nullptr ? value->hashCode() : 0);
    }

    static size_t update(size_t hash, const void *data, size_t size);

    template <typename T>
    static size_t update(size_t hash, const T *data, size_t size) {
      return update(hash, static_cast<const void*>(data), size * sizeof(std::remove_reference_t<T>));
    }

    /// <summary>
    /// Apply the final computation steps to the intermediate value {@code hash}
    /// to form the final result of the MurmurHash 3 hash function.
    /// </summary>
    /// <param name="hash"> the intermediate hash value </param>
    /// <param name="entryCount"> the number of calls to update() before calling finish() </param>
    /// <returns> the final hash result </returns>
    static size_t finish(size_t hash, size_t entryCount);

    /// Utility function to compute the hash code of an array using the MurmurHash3 algorithm.
    ///
    /// @param <T> the array element type </param>
    /// <param name="data"> the array data </param>
    /// <param name="seed"> the seed for the MurmurHash algorithm </param>
    /// <returns> the hash code of the data </returns>
    template<typename T> // where T is C array type
    static size_t hashCode(const std::vector<Ref<T>> &data, size_t seed = DEFAULT_SEED) {
      size_t hash = initialize(seed);
      for (auto &entry : data) {
        hash = update(hash, entry);
      }
      return finish(hash, data.size());
    }

    static size_t hashCode(const void *data, size_t size, size_t seed = DEFAULT_SEED) {
      size_t hash = initialize(seed);
      hash = update(hash, data, size);
      return finish(hash, size);
    }

    template <typename T>
    static size_t hashCode(const T *data, size_t size, size_t seed = DEFAULT_SEED) {
      return hashCode(static_cast<const void*>(data), size * sizeof(std::remove_reference_t<T>), seed);
    }

  private:
    MurmurHash() = delete;

    MurmurHash(const MurmurHash&) = delete;

    MurmurHash& operator=(const MurmurHash&) = delete;
  };

} // namespace atn
} // namespace antlr4
