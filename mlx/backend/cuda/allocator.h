// Copyright © 2025 Apple Inc.

#pragma once

#include "mlx/allocator.h"
#include "mlx/backend/common/buffer_cache.h"

#include <mutex>
#include <set>
#include <thread>
#include <utility>

namespace mlx::core::cu {

class Worker;

using allocator::Buffer;

// Stores cuda-managed unified memory.
struct CudaBuffer {
  void* data;
  size_t size;
};

class SmallSizePool {
 private:
  struct Block {
    Block* next;
  };

  void* buffer_{nullptr};
  Block* next_free_{nullptr};
  void* end_{nullptr};

 public:
  SmallSizePool();
  ~SmallSizePool();

  SmallSizePool(const SmallSizePool&) = delete;
  SmallSizePool& operator=(const SmallSizePool&) = delete;

  void* malloc();
  void free(void* p);
  bool in_pool(void* p);
};

class CudaAllocator : public allocator::Allocator {
 public:
  Buffer malloc(size_t size) override;
  void free(Buffer buffer) override;
  size_t size(Buffer buffer) const override;

  // Register current thread as safe to free buffers.
  // In cuda freeing a buffer implicitly synchronizes stream, and for threads
  // that may be waited by gpu stream (for example cpu stream threads), freeing
  // buffers there would result in dead lock.
  void register_this_thread();

  // Call cudaFree in the safe thread.
  void cuda_free(void* buf);

  size_t get_active_memory() const;
  size_t get_peak_memory() const;
  void reset_peak_memory();
  size_t get_memory_limit();
  size_t set_memory_limit(size_t limit);
  size_t get_cache_memory() const;
  size_t set_cache_limit(size_t limit);
  void clear_cache();

 private:
  CudaAllocator();
  friend CudaAllocator& allocator();

  std::mutex worker_mutex_;
  std::unique_ptr<Worker> worker_;
  std::set<std::thread::id> allowed_threads_;

  std::mutex mutex_;
  size_t memory_limit_;
  size_t max_pool_size_;
  BufferCache<CudaBuffer> buffer_cache_;
  size_t active_memory_{0};
  size_t peak_memory_{0};
  SmallSizePool scalar_pool_;
};

CudaAllocator& allocator();

} // namespace mlx::core::cu
