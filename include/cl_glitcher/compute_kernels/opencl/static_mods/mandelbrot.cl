float2 f(float2 c, float2 z)
{
  return (float2)(
    z.x * z.x - z.y * z.y + c.x,
    2 * z.x * z.y + c.y
  );
}

float3 f3(float3 c, float3 z, float n)
{
  float rn = length(z);
  float3 v = rn * (float3)(
    sin(n * z.z) * cos(n * z.y),
    sin(n * z.z) * sin(n * z.y),
    cos(n * z.z)
    );
  return v + c;
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

float3 normalizeToSphere(float3 v, float rTo, float3 sphereOffset)
{
  v -= 0.5f;
  v *= 2 * rTo;
  // TODO: Make other version
  //v += sphereOffset;
  return v;
}

float3 denormalizeFromSphere(float3 v, float rFrom, float3 sphereOffset)
{
  v -= sphereOffset;
  v /= 2 * rFrom;
  v += 0.5f;
  return v;
}


float2 shift(
  global unsigned char * colorX,
  global unsigned char * colorY,
  float incFactor,
  int steps)
{
  //float2 posStart = normalizeToBulb(
  //  (float2)(
  //    (float)*colorX / 255.0f,
  //    (float)*colorY / 255.0f
  //  )
  //);
  float2 posStart;
  posStart.x = -2.0f + 3.0f * ((float)*colorX / 255.0f);
  posStart.y = -1.0f + 2.0f * ((float)*colorY / 255.0f);
  float2 pos = (float2)(0);
  int j;
  for (j = 0; j < steps; j++) {
    pos = f(posStart, pos);
    //if (length(pos) > 2.0f)
    //  break;
  }
  pos.x = (pos.x + 2.0f) * 255.0f / 3.0f ;
  pos.y = (pos.y + 1.0f) * 255.0f / 2.0f ;
  //float incF = 1.0f - (float)j / (float)steps;
  //incF = incFactor * incF * 255.f;
  return (float2)(pos.x, pos.y);
}


float3 shift3(
  global unsigned char * colorX,
  global unsigned char * colorY,
  global unsigned char * colorZ,
  float steps,
  float n,
  float r,
  float3 sphereOffset)
{
  float3 posStartXYZ;
  posStartXYZ.x = (float)*colorX / 255.0f;
  posStartXYZ.y = (float)*colorY / 255.0f;
  posStartXYZ.z = (float)*colorZ / 255.0f;
  posStartXYZ = normalizeToSphere(posStartXYZ, r, sphereOffset);
  float3 posStart;
  float3 pos;
  pos.x = length(posStartXYZ);
  pos.y = atan2(posStartXYZ.y, posStartXYZ.x);
  pos.z = acos(posStartXYZ.z / pos.x);
  posStart = pos;
  float stepsFloor = floor(steps);
  float stepsRem = steps - stepsFloor;
  int j;
  for (j = 0; j < (int)stepsFloor; j++) {
    pos = f3(posStart, pos, n);
    //if (length(pos) > 2.0f)
    //  break;
  }
  if (stepsRem > 0.0f) {
    float3 pos2 = f3(posStart, pos, n);
    float3 d = pos2 - pos;
    d *= stepsRem;
    pos += d;
  }
  pos.x = pos.x * cos(pos.y) * sin(pos.z);
  pos.y = pos.x * sin(pos.y) * sin(pos.z);
  pos.z = pos.x * cos(pos.z);
  // TODO: Implement into a bool or other version
  pos.x = (pos.x + 1.0f) * 255.0f / 2.0f;
  pos.y = (pos.y + 1.0f) * 255.0f / 2.0f;
  pos.z = (pos.z + 1.0f) * 255.0f / 2.0f;
  //pos = denormalizeFromSphere(pos, r, sphereOffset);
  //pos *= 255.0f;

  //float incF = 1.0f - (float)j / (float)steps;
  //incF = incFactor * incF * 255.f;
  return pos;
}


uchar roundFToUC(float value)
{
  return (uchar)round(value);
}



void kernel mandelbrot(
  global unsigned char * imgIn,
  global unsigned char * imgCurrent,
  global int const * imgSizeBytes,
  global float const * steps,
  global float const * n,
  global float const * radius,
  global bool const * imageFeedback,
  global float3 const * sphereOffset)
{
  int id = get_global_id(0);
  int nThreads = get_global_size(0);
  int N = imgSizeBytes[0];

  int ratio = (N / nThreads);  // number of elements for each thread
  int start = ratio * id;
  int stop  = ratio * (id + 1);

  if (id == nThreads - 1) {
    stop = N;
  }

  if (start % 3 == 0) {
    for (int i = start; i < stop; i += 3) {
      global unsigned char * r, * g, * b;
      global unsigned char * rW, * gW, * bW;
      if (*imageFeedback)
      {
        r = imgCurrent + i;
        g = imgCurrent + i + 1;
        b = imgCurrent + i + 2;
        rW = r;
        gW = g;
        bW = b;
      }
      else
      {
        r = imgIn + i;
        g = imgIn + i + 1;
        b = imgIn + i + 2;
        rW = imgCurrent + i;
        gW = imgCurrent + i + 1;
        bW = imgCurrent + i + 2;
      }
      //global unsigned char * r = imgCurrent + i;
      //global unsigned char * g = imgCurrent + i + 1;
      //global unsigned char * b = imgCurrent + i + 2;

      //int stepsI = round(*steps);
      float3 rgb = shift3(r, g, b, *steps, *n, *radius, *sphereOffset);
      //float rb = shift(r, b, *incFactor, steps);
      //float gb = shift(g, b, *incFactor, steps);
      //*r = roundFToUC(rg.x);//*r + roundFToUC(rg.x);
      //*g = roundFToUC(rg.y);//*g + roundFToUC(rg.y);
      *rW = convert_uchar(rgb.x);//*r + roundFToUC(rg.x);
      *gW = convert_uchar(rgb.y);//*g + roundFToUC(rg.y);
      *bW = convert_uchar(rgb.z);//*g + roundFToUC(rg.y);
      //*b = *b + roundFToUC(rb + gb);
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