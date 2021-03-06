void kernel histogram(
  global const char * img,
  global const int* imgSize,
  global int* histOut)
{
  int ID, nThreads, n, ratio, start, stop;

  ID = get_global_id(0);
  n = N[0];

  ratio = n / get_global_size(0);  // number of elements for each thread
  start = ratio * ID;
  stop  = ratio * (ID + 1);

  for (int i = start; i < stop; i++)
histOut[i] = A[i] + B[i];
}