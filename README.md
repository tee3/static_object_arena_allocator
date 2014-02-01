# An arena allocator with a statically allocated arena

This repository contains two experimental classes to enable use of
std::vector<T,A> that allocates its elements from statically allocated
memory (either global or on the stack) and fails hard if reallocation
is attempted.  This is useful for real-time systems that cannot
utilize dynamically allocated memory, but do not want to implement a
special dynamically sized vector class.

- An arena allocator that creates an allocator from an arena with a
  specific interface

- An arena of statically allocated memory suitable for use by the
  above arena allocator.
