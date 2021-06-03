#include <string>
namespace test{
std::string const vectorAdditionStr {
"void kernel simple_add(global const unsigned int* A, global const unsigned int* B, global unsigned int* C,\n"
"                      global const int* N) {\n"
"   int ID, Nthreads, n, ratio, start, stop;\n"
"\n"
"   ID = get_global_id(0);\n"
"   Nthreads = get_global_size(0);\n"
"   n = N[0];\n"
"\n"
"   ratio = (n / Nthreads);  // number of elements for each thread\n"
"   start = ratio * ID;\n"
"   stop  = ratio * (ID + 1);\n"
"\n"
"   for (int i=start; i<stop; i++)\n"
"       C[i] = A[i] + B[i];\n"
"}\n"
"\n"
"/*void kernel simple_add(global const int* A, global const int* B, global int* C,\n"
"                      global const int* N) {\n"
"   int ID, Nthreads, n, ratio, start, stop;\n"
"\n"
"   ID = get_global_id(0);\n"
"   Nthreads = get_global_size(0);\n"
"   n = N[0];\n"
"\n"
"   ratio = (n / Nthreads);  // number of elements for each thread\n"
"   start = ratio * ID;\n"
"   stop  = ratio * (ID + 1);\n"
"\n"
"   for (int i=start; i<stop; i++) {\n"
"    atomic_add(&C[i], 1);\n"
"    atomic_add(&C[i+1], 1);\n"
"   }\n"
"       //C[i] = A[i] + B[i];\n"
"}*/\n"
"\n"
};
}