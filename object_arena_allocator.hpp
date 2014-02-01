#ifndef object_arena_allocator_hpp_
#define object_arena_allocator_hpp_

#include <cstddef>

/// Uses an object arena to perform allocations.
template<class ObjectArena>
class object_arena_allocator
{
public:
   typedef ObjectArena object_arena_type;

   typedef typename object_arena_type::value_type value_type;

public:
   explicit
   object_arena_allocator (object_arena_type & arena) noexcept :
      arena_ (arena)
   {
   }

   explicit
   object_arena_allocator (const object_arena_allocator & rhs) noexcept = default;

   object_arena_allocator &
   operator= (const object_arena_allocator & rhs) noexcept = delete;

   explicit
   object_arena_allocator (object_arena_allocator && rhs) noexcept = default;

   object_arena_allocator &
   operator= (object_arena_allocator && rhs) noexcept = delete;

public:
   template <class A1, class A2>
   friend
   bool
   operator== (const object_arena_allocator<A1> & lhs,
               const object_arena_allocator<A2> & rhs) noexcept
   {
      return lhs.arena_ == rhs.arena_;
   }

   template <class A1, class A2>
   friend
   bool
   operator!= (const object_arena_allocator<A1> & lhs,
               const object_arena_allocator<A2> & rhs) noexcept
   {
      return !(lhs == rhs);
   }

public:
   value_type *
   allocate (std::size_t n)
   {
      return static_cast<value_type *> (arena_.allocate (n));
   }

   void
   deallocate (value_type * p, std::size_t n)
   {
      arena_.deallocate (p,n);
   }

private:
   object_arena_type & arena_;
};

// Local variables:
// flycheck-clang-language-standard: "c++14"
// End:

#endif
