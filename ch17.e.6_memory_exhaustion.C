// g++ -Wall -std=c++11 ch17.e.6_memory_exhaustion.C -o ch17.e.6_memory_exhaustion.exe 2>&1 | tee tmp.txt
/* EX6 Memory exhaustion - running out of available memory when allocating using new. Find out what happens.
 * Write a program with an infinite loop that allocates, but never deallocates.
 *
 * EX5 Write a function char* findx (const char*s, const char*x), that finds the first occurrence of the C-style string x in s.
 *
 * EX4: Write a function, char* strdup(const char*), that copies a C-style string into memory it allocates on the free store.
 * Do not use any standard library functions
 *
 * Ex3: Write a function, void to_lower(char* s), that replaces all uppercase characters
 * in the C-style string s with their lowercase equivalents. For Example, Hello, World!, becomes hello, world!
 * Do not use any standard library functions. A C-style string is a zero-terminated array of characters,
 * so if you find a char with the value of 0 you are at the end.
 */


#include <iostream>
#include <vector>

using namespace std;

char* findx (const char* s, const char* x){
  int len_s=0;
  while(s[len_s++]); // gives the length of s, including \0 termination character
  int len_x=0;
  while(x[len_x++]); // gives the length of x, including \o termination character
  if (len_x>len_s || len_x == 1)  // guarantees no match (as the x is too long, or empty length=1)
    return (char*) &s[len_s]; // return pointer to the termination symbol of s
  for (int i=0; i< len_s-len_x + 1; i++) { // pick a starting location of s to try
    int j=0; // index into j
    while (s[i+j]==x[j] && j < len_x - 1) // we do not want to compare the terminating symbol('\0') of x
      j++;
    if (j==len_x-1)  // we do not want to compare the terminating symbol ('\0') of x
      return (char*) &s[i];  // match found;
  }

  // searched everything, did not find the match
  return (char*) &s[len_s]; // return pointer to the termination symbol of s
}

char* strdup(const char* s) {
  int n=0;
  while(s[n++]); // count the characters // even if the line is empty, it will return 1 (accounting for \0 symbol)
  char* result = new char[n]; // allocate the new string
  cout << "reserving " << n << " bytes" << endl;
  // copy full string (including \0 termination symbol
  for (int i=0; i<n; i++)
    result[i]=s[i];
  return result;
}

void to_lower(char* s) {
  while (*s) {
    if (*s >= 'A' &&  *s <= 'Z')
      *s = char(*s -'A' + 'a');
    s++; // advance to next symbol
  }
}

void allocation_demo (int loop_limit) {
  // allocation_demo(1); // Expect to consume 0x20 + 0x20 +0x30 +0x20 = 0x90
  // new double
  // new double[3]
  // new double[4]
  // new char

  // p = 0x2061230
  // p = 0x2061250
  cout << endl;
  cout << "Allocating single doubles: double* p = new double; // 8 bytes, consume 0x20 " << endl;
  for (int i=0; i<loop_limit; i++) {
    double* p = new double;
    cout << "p = " << (void*) p << endl;
  }


  // p = 0x1165430
  // p = 0x1165450
  cout << endl;
  cout << "Allocating 3 doubles:double* p = new double[3]; // 0x18 bytes, but consume 0x20 " << endl;
  for (int i=0; i<loop_limit; i++) {
    double* p = new double[3]; // 8*3 = 24 bytes = 0x18
    cout << "p = " << (void*) p << endl;
  }

  // p = 0x24d6630
  // p = 0x24d6660
  cout << endl;
  cout << "Allocating 4 doubles:double* p = new double[4]; // 0x20 bytes, but consume 0x30 " << endl;
  for (int i=0; i<loop_limit; i++) {
    double* p = new double[4]; // 8*4 = 32 bytes = 0x20
    cout << "p = " << (void*) p << endl;
  }

  // This code will try a couple more examples with allocations:
  // p = 0xd37030
  // p = 0xd37050
  // p = 0xd37070
  cout << endl;
  cout << "Allocating single chars: char* p = new char; // 1 byte, consume 0x20" << endl;
  for (int i=0; i<loop_limit; i++) {
    char* p = new char;
    cout << "p = " << (void*) p << endl;
  }
}

int main()
{
  /*
  p = 0x7fa5ac1c9700
  p = 0x7fa5ac1cb710
  p = 0x7fa5ac1cd720
  p = 0x7fa5ac1cf730
  p = 0x7fa5ac1d1740Killed
  Note:
  it appears that we allocated the requested size +0x10 bytes
  cout << "This program will try to demonstrate memory exhaustion"<< endl;
  while(1) { // infinite loop
    double* p = new double[1024]; // 1024*8 = 8k chunk requested = 2^13 = 2*2^12 = 0x2000
    cout << "p = " << p << endl;
    // do not deallocate here on purpose
  }
  */

  // This code will try a couple more examples with allocations:
  // p = 0xd37030
  // p = 0xd37050
  // p = 0xd37070
  cout << endl;
  cout << "Allocating single chars: char* p = new char;" << endl;
  for (int i=0; i<16; i++) {
    char* p = new char;
    cout << "p = " << (void*) p << endl;
  }

  // p = 0x2061230
  // p = 0x2061250
  cout << endl;
  cout << "Allocating single doubles: double* p = new double;" << endl;
  for (int i=0; i<16; i++) {
    double* p = new double;
    cout << "p = " << (void*) p << endl;
  }


  // p = 0x1165430
  // p = 0x1165450
  cout << endl;
  cout << "Allocating 3 doubles:double* p = new double[3]; // 0x18 bytes " << endl;
  for (int i=0; i<16; i++) {
    double* p = new double[3]; // 8*3 = 24 bytes = 0x18
    cout << "p = " << (void*) p << endl;
  }

  // p = 0x24d6630
  // p = 0x24d6660
  cout << endl;
  cout << "Allocating 4 doubles:double* p = new double[4]; // 0x20 bytes " << endl;
  for (int i=0; i<16; i++) {
    double* p = new double[4]; // 8*4 = 32 bytes = 0x20
    cout << "p = " << (void*) p << endl;
  }

  cout << endl;
  cout << "Allocating multiple chars: char* p = new char;" << endl;
  for (int i=0; i<33; i++) {
    char* p = new char[i];
    cout << "allocated "<< i << "chars, p = " << (void*) p << endl;
  }



  cout << endl;
  cout << endl;
  cout << "*************************************************"<<endl;
  cout << endl;
  char* p = new char[24]; // payload 24=0x16, consumed 0x20 or 4 uint64_t pointers
  cout << "char* p = new char[24], p = " << (void*) p << endl;cout << "char* p = new char[24], p = " << (void*) p << endl;

  // after this point we will consume through allocation 22 uint64_t elements (uint64_t = long long int )
  // so starting with p, we can sample 22+4 = 26 pointers
  const int num_8byte_ptrs_extra = 22;
  const int num_8byte_ptrs_total = num_8byte_ptrs_extra + 4;
  cout << "clobbering the area starting p "<< endl;
  char* p_cl = p+0x20;
  for (int i=0; i<num_8byte_ptrs_extra*8; i++) // we have 8 bytes per uint64_t pointer
    *(p_cl++) = 'a';

  cout << "Pointer p = " << (void*) p << endl;
  cout << "Pointer p_cl = " << (void*) p_cl << endl;

// moved down after clobbering
//  char* p_next = new char[24];
//  cout << "char* p_next = new char[24], p_next = " << (void*) p_next << endl;

  // int* x = static_cast<int*> ( (void*) p);
  const long long int* x = reinterpret_cast<long long int*> ( p);
  cout << "int* x = reinterpret_cast<int*> ( p); x = " << x << endl;
  //for (int i=0; i<4; i++) {

  long long int* loc = (long long int*) x;
  for (int i=0; i<num_8byte_ptrs_total; i++) {
    cout << "loc = " << loc << ", *loc = 0x" << hex << *loc << endl;
    loc++;
  }

  char* p_next = new char[24];
  cout << "char* p_next = new char[24], p_next = " << (void*) p_next << endl;

  allocation_demo(1); // should allocate 0x90 or 18 uint64_t pointers
  // 4 +4 + 18= 26 uint64_t pointers we can look at
  // char[24]
  // char[24]
  // new double
  // new double[3]
  // new double[4]
  // new char


  cout << "Reprinting locations after the demo"<< endl;
  loc = (long long int*) x;
  for (int i=0; i<num_8byte_ptrs_total; i++) {
    cout << "loc = " << loc << ", *loc = 0x" << hex << *loc << endl;
    loc++;
  }

  cout << endl;
  cout << "Conclusion:"<<endl;
  cout << "1. We allocate at least 0x20 bytes of free space with new."<<endl;
  cout << "2. We allocate in 0x10 byte increments."<<endl;
  cout << "3. We allocate an extra 8 bytes past the size required."<< endl;
  cout << "   new double[3] will consume 0x20 = 32 bytes, whereas the payload is only 0x18 = 24 (overhead: 8 bytes)" << endl;
  cout << "   new double[4] will consume 0x30 = 48 bytes, whereas the payload is only 0x20 = 32 (overhead: 16 bytes)" << endl;
}
