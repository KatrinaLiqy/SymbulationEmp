#ifndef CPU_STATE_H
#define CPU_STATE_H

#include "../Organism.h"
#include "emp/Evolve/World_structure.hpp"
#include "emp/base/Ptr.hpp"
#include "emp/base/optional.hpp"
#include "emp/base/vector.hpp"
#include "emp/bits/BitSet.hpp"
#include <cstdint>

// Helper that keeps the last `len` inputs and discards the rest
template <const size_t len = 8> struct IORingBuffer {
  uint32_t buffer[len];
  size_t next = 0;

  IORingBuffer() {
    for (size_t i = 0; i < len; i++) {
      buffer[i] = 0;
    }
  }

  void push(uint32_t x) {
    buffer[next] = x;
    next = (next + 1) % len;
  }

  uint32_t operator[](size_t idx) { return buffer[idx % len]; }

  size_t size() { return len; }
};

// CPUState has a pointer to the SGPWorld, but it can't include it
class SGPWorld;

struct CPUState {
  emp::vector<uint32_t> stack;
  emp::vector<uint32_t> stack2;

  IORingBuffer<> input_buf;

  emp::Ptr<emp::BitSet<64>> used_resources = emp::NewPtr<emp::BitSet<64>>();

  emp::Ptr<Organism> host;
  emp::Ptr<SGPWorld> world;

  emp::WorldPosition location;

  CPUState(emp::Ptr<Organism> host, emp::Ptr<SGPWorld> world)
      : host(host), world(world) {}
};

#endif