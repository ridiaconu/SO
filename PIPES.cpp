#include <iostream>

using namespace std;

int main()

{

   int i;

   for(i=1;i<=10000;i++)

   {

       int is_prime = 1;

       if(i<2)

	{
           is_prime = 0;
	}

       if(i % 2 == 0 && i > 2)

	{
           is_prime = 0;
	}

       for(int d = 3; d * d <= i && is_prime == 1; d++)

           if(i % d == 0) 
	    { 
               is_prime = 0;  
	    } 

       if(is_prime == 1)

           cout<<i<<" ";
   }
}
