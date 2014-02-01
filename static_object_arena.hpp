#ifndef static_object_arena_hpp_
#define static_object_arena_hpp_

#include <cstddef>

#include <cassert>

/// Allocates objects from an arena of static size.
///
/// This assumes that the allocation is only done once and is less
/// than or equal to N.
///
/// This needs a much better explanation.
template<class T, std::size_t N>
class static_object_arena
{
public:
   typedef std::size_t size_type;
   static const std::size_t size = N;

public:
   typedef T value_type;

public:
   static_object_arena () noexcept :
      allocated_ (0)
   {
   }

   explicit
   static_object_arena (const static_object_arena & rhs) noexcept = delete;

   static_object_arena &
   operator= (const static_object_arena & rhs) noexcept = delete;

   explicit
   static_object_arena (static_object_arena && rhs) noexcept = delete;

   static_object_arena &
   operator= (static_object_arena && rhs) noexcept = delete;

public:
   template <class T1, std::size_t N1, class T2, std::size_t N2>
   friend
   bool
   operator== (const static_object_arena<T1,N1> & lhs,
               const static_object_arena<T2,N2> & rhs) noexcept
   {
      return (N1 == N2) && (lhs.allocated_ == rhs.allocated_) && (lhs.storage_ == rhs.storage_);
   }

   template <class T1, std::size_t N1, class T2, std::size_t N2>
   friend
   bool
   operator!= (const static_object_arena<T1,N1> & lhs,
               const static_object_arena<T2,N2> & rhs) noexcept
   {
      return !(lhs == rhs);
   }

public:
   void *
   allocate (std::size_t n)
   {
      assert (allocated_ == 0);
      assert (n <= N);

      allocated_ = n;

      return storage_;
   }

   void
   deallocate (void * p, std::size_t n)
   {
      assert (p == storage_);
      assert (allocated_ == n);

      allocated_ = false;
   }

private:
   /// The number of allocated elements.
   std::size_t allocated_;

   /// Aligned storage for N elements of type T.
   alignas (alignof (T))
   unsigned char storage_ [N * sizeof (T)];
};

// Local variables:
// flycheck-clang-language-standard: "c++14"
// End:

#endif
