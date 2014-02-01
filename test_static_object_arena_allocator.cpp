#include <iostream>

#include <vector>

#include "static_object_arena.hpp"
#include "object_arena_allocator.hpp"

static_object_arena<double,10000> global_arena0;
static_object_arena<int,10000> global_arena1;

object_arena_allocator<static_object_arena<double,10000>> global_allocator0 (global_arena0);
object_arena_allocator<static_object_arena<int,10000>> global_allocator1 (global_arena1);

int
main ()
{
   {
      assert (global_arena0 == global_arena0);
      assert (global_arena1 == global_arena1);
      assert (global_arena0 != global_arena1);
      assert (global_allocator0 == global_allocator0);
      assert (global_allocator1 == global_allocator1);
      assert (global_allocator0 != global_allocator1);
   }

   {
      std::vector<double,object_arena_allocator<static_object_arena<double,10000>>> v { global_allocator0 };

      v.reserve (10000);
      assert (v.capacity () == 10000);

      for (int i = 0; i != v.capacity (); ++i)
      {
         v.push_back (i);
      }

      for (int i = 0; i != v.size (); ++i)
      {
         assert (v [i] == i);
      }
   }

   {
      std::vector<int,object_arena_allocator<static_object_arena<int,10000>>> v { global_allocator1 };

      v.reserve (10000);
      assert (v.capacity () == 10000);

      for (int i = 0; i != v.capacity (); ++i)
      {
         v.push_back (i);
      }

      for (int i = 0; i != v.size (); ++i)
      {
         assert (v [i] == i);
      }
   }

   {
      // an arena on the stack
      static_object_arena<int,10000> arena;
      std::vector<int,object_arena_allocator<static_object_arena<int,10000>>> v { object_arena_allocator<static_object_arena<int,10000>> { arena } };

      v.reserve (10000);
      assert (v.capacity () == 10000);

      for (int i = 0; i != v.capacity (); ++i)
      {
         v.push_back (i);
      }

      for (int i = 0; i != v.size (); ++i)
      {
         assert (v [i] == i);
      }
   }

   {
      static_object_arena<int,100> arena;
      object_arena_allocator<static_object_arena<int,100>> allocator { arena };

      {
         std::vector<int,object_arena_allocator<static_object_arena<int,100>>> v { allocator };

         v.reserve (100);

         v.push_back (0);

         std::cout << &v [0] << "\n";

         // can only use the allocator for one container at a time
      }

      // re-use the allocator after it has been let go by the other
      {
         std::vector<int,object_arena_allocator<static_object_arena<int,100>>> v { allocator };

         v.reserve (100);

         v.push_back (0);

         std::cout << &v [0] << "\n";

      }
   }

   return 0;
}

// Local variables:
// flycheck-clang-language-standard: "c++14"
// End:
