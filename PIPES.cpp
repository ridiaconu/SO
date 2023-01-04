#include <iostream>

using namespace std;

int main() {
   for (int i = 1; i <= 10000; i++) {
      bool is_prime = true;

      if (i < 2) {
         is_prime = false;
      }
      else if (i % 2 == 0 && i > 2) {
         is_prime = false;
      }
      else {
         for (int d = 3; d * d <= i && is_prime; d++) {
            if (i % d == 0) { 
               is_prime = false;  
            } 
         }
      }

      if (is_prime) {
         cout << i << " ";
      }
   }

   return 0;
}
