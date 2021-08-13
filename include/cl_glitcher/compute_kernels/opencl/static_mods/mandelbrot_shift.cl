float2 f(float2 c, float2 z)
{
  return (float2)(
    z.x * z.x - z.y * z.y + c.x,
    2 * z.x * z.y + c.y
  );
}


// v: vector on [0, 1]^2
float2 normalizeToBulb(float2 v)
{
  // adjust to [-1, 1]^2
  v.x = -1.0f + 2.0f * v.x;
  v.y = -1.0f + 2.0f * v.y;

  // initial length
  float l1 = length(v);

  // new length
  float l2 = 0.25f;

  if (l1 != 0.0f) {
    v.x = v.x * l2 / l1;
    v.y = v.y * l2 / l1;
  }

  v.x += 1;

  return v;
}


float shift(
  global unsigned char * colorX,
  global unsigned char * colorY,
  float incFactor,
  int steps)
{
  float2 posStart = normalizeToBulb(
    (float2)(
      (float)*colorX / 255.0f,
      (float)*colorY / 255.0f
    )
  );
  //posStart.x = -2.0f + 3.0f * ((float)*colorX / 255.0f);
  //posStart.y = -1.0f + 2.0f * ((float)*colorY / 255.0f);
  float2 pos = (float2)(0);
  int j;
  for (j = 0; j < steps; j++) {
    pos = f(posStart, pos);
    if (length(pos) > 2.0f)
      break;
  }
  float incF = 1.0f - (float)j / (float)steps;
  incF = incFactor * incF * 255.f;
  return incF;
}


uchar roundFToUC(float value)
{
  return (uchar)round(value);
}



void kernel mandelbrotShift(
  global unsigned char * imgCurrent,
  global int const * imgSizeBytes,
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

  if (start % 3 == 0) {
    for (int i = start; i < stop; i += 3) {
      global unsigned char * r = imgCurrent + i;
      global unsigned char * g = imgCurrent + i + 1;
      global unsigned char * b = imgCurrent + i + 2;

      int steps = 100;
      float rg = shift(r, g, *incFactor, steps);
      float rb = shift(r, b, *incFactor, steps);
      float gb = shift(g, b, *incFactor, steps);
      *r = *r + roundFToUC(rg + rb);
      *g = *g + roundFToUC(rg + gb);
      *b = *b + roundFToUC(rb + gb);
      /*float2 posStart;
      posStart.x = -2.0f + 3.0f * ((float)*r / 255.0f);
      posStart.y = -1.0f + 2.0f * ((float)*g / 255.0f);
      float2 pos = (float2)(0);
      int steps = 100;
      int j;
      for (j = 0; j < steps; j++) {
        pos = f(posStart, pos);
        if (length(pos) > 2.0f)
          break;
      }
      float incF = 1.0f - (float)j / (float)steps;
      incF = *incFactor * incF * 255.f;
      unsigned char inc = (unsigned char)(round(incF));
      *r = *r + inc;
      *g = *g + inc;*/
    }
  }
}