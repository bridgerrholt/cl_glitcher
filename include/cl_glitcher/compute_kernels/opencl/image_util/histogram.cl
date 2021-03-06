void kernel histogram(
  global unsigned char const * img,
  global int const * imgSize,
  global unsigned int * histOut)
{
  int ID, Nthreads, n, ratio, start, stop;

  ID = get_global_id(0);
  Nthreads = get_global_size(0);
  n = imgSize[0];

  ratio = (n / Nthreads);  // number of elements for each thread
  start = ratio * ID;
  stop  = ratio * (ID + 1);

  for (int i = start; i < stop; i++) {
    unsigned int t = img[i];
    atomic_add(histOut + t, 1);
  }
}