void kernel histogramShift(
  global unsigned char * img,
  global int const * imgSizeBytes,
  global unsigned int const * hist,
  global unsigned const * incMin,
  global unsigned const * incMax,
  global float const * incFactor)
{
  int id = get_global_id(0);
  int nThreads = get_global_size(0);
  int n = imgSizeBytes[0];

  int ratio = (n / nThreads);  // number of elements for each thread
  int start = ratio * id;
  int stop  = ratio * (id + 1);

  if (id == nThreads - 1) {
    stop = n;
  }

  for (int i = start; i < stop; i++) {
    int * v = img + i;
    int h = hist[*v]
    if (*incMin <= h && h <= *incMax) {
      *v = *v + (unsigned char)(round(*incFactor * 255.f));
    }
  }
}