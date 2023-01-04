#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <cstring>
#include <cstdlib>
#include <string>

namespace bip = boost::interprocess;

int main(int argc, char *argv[])
{
   // Remove shared memory on construction and destruction
   struct shm_remove
   {
      shm_remove() { bip::shared_memory_object::remove("MySharedMemory"); }
      ~shm_remove() { bip::shared_memory_object::remove("MySharedMemory"); }
   } remover;

   if (argc == 1) {  // Parent process
      // Create a shared memory object.
      bip::shared_memory_object shm(bip::create_only, "MySharedMemory", bip::read_write);

      // Set size
      shm.truncate(1000);

      // Map the whole shared memory in this process
      bip::mapped_region region(shm, bip::read_write);

      // Write all the memory to 1
      std::memset(region.get_address(), 1, region.get_size());

      // Launch child process
      std::string s(argv[0]);
      s += " child ";
      if (std::system(s.c_str()) != 0) {
         return 1;
      }
   }
   else {  // Child process
      // Open already created shared memory object.
      bip::shared_memory_object shm(bip::open_only, "MySharedMemory", bip::read_only);

      // Map the whole shared memory in this process
      bip::mapped_region region(shm, bip::read_only);

      // Check that memory was initialized to 1
      char *mem = static_cast<char*>(region.get_address());
      for (std::size_t i = 0; i < region.get_size(); ++i) {
         if (*mem++ != 1) {
            return 1;   // Error checking memory
         }
      }
   }

   return 0;
}
