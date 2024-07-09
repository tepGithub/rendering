#include "Image/Image.h"
#include "BVH.h"
#include "Util.h"

#include "Math/Intersect.h"
using namespace Math;

#include <cstdio>
#include <iostream>

#define USE_BVH

//#define SCENE_USE_RANDOMIZED_TRIANGLE
#define SCENE_USE_UNITY_ROBOLAB

std::vector<Tri> tris;

static void initScene()
{
#ifdef SCENE_USE_RANDOMIZED_TRIANGLE
    tris.resize(1024);
    for (Tri& tri : tris)
    {
        float3 r0( RandomFloat(), RandomFloat(), RandomFloat() );
        float3 r1( RandomFloat(), RandomFloat(), RandomFloat() );
        float3 r2( RandomFloat(), RandomFloat(), RandomFloat() );
        tri.vertex0 = r0 * 9.0f - float3( 5.0f );
        tri.vertex1 = tri.vertex0 + r1;
        tri.vertex2 = tri.vertex0 + r2;
    }
#endif

#ifdef SCENE_USE_UNITY_ROBOLAB
    tris.resize(12582);
    FILE* file = fopen("../../assets/unity.tri", "r");
    float a, b, c, d, e, f, g, h, i;
    for (Tri& tri : tris)
    {
        fscanf(file, "%f %f %f %f %f %f %f %f %f\n", &a, &b, &c, &d, &e, &f, &g, &h, &i);
        tri.vertex0 = float3( a, b, c );
        tri.vertex1 = float3( d, e, f );
        tri.vertex2 = float3( g, h, i );
    }
    fclose(file);
#endif

    // compute centroid
    for (Tri& tri : tris)
    {
        tri.centroid = (tri.vertex0 + tri.vertex1 + tri.vertex2) / 3.0f;
    }
}

void printRayPerSecond(uint32_t rayCount, int64_t durationMs)
{
    double rps = double(rayCount) * 1000.0 / double(durationMs);    
    if (rps < 1e3)
    {
        std::cout << rps << " rays/sec\n";
    }
    else if (rps < 1e6)
    {
        std::cout << rps / 1e3 << " Krays/sec\n";
    }
    else if (rps < 1e9)
    {
        std::cout << rps / 1e6 << " Mrays/sec\n";
    }
    else
    {
        std::cout << rps / 1e9 << " Grays/sec\n";
    }
}

int main()
{    
    initScene();

    // construct BVH
    BVH bvh(tris.data(), uint32_t(tris.size()));

    Image img(640, 640);
    img.clear(colors::black());

#ifdef SCENE_USE_RANDOMIZED_TRIANGLE    
    float3 camPos( 0, 0, -18 );
    float3 p0( -1, 1, -15 );
    float3 p1( 1, 1, -15 );
    float3 p2( -1, -1, -15 );
#endif
#ifdef SCENE_USE_UNITY_ROBOLAB
    float3 camPos( -1.5f, -0.2f, -2.5f );
    float3 p0( -2.5f, 0.8f, -0.5f );
    float3 p1( -0.5f, 0.8f, -0.5f );
    float3 p2( -2.5f, -1.2f, -0.5f );
#endif

    Ray ray;
    
    Timer timer;

    for (uint32_t y = 0; y < img.height; y++)
    {
        for (uint32_t x = 0; x < img.width; x++)
        {
            float3 pixelPos = p0 + (p1 - p0) * (x / float(img.width)) + (p2 - p0) * (y / float(img.height));
            ray.O = camPos;
            ray.D = normalize( pixelPos - ray.O );
            ray.t = Ray::kInf;

        #ifdef USE_BVH
            bvh.intersect(ray);
        #else
            for (const Tri& tri : tris)
                intersectRayTri(ray, tri);
        #endif

            if (ray.t < Ray::kInf)
            {
                // depth as color
                uint8_t d = uint8_t(saturate(1.0f - ray.t / 4.0f) * 255.0f);
                img(x, y) = color3b(d);

                //img(x, y) = colors::white();
            }
        }
    }

    int64_t durationMs = timer.duration();
    std::cout << "elapsed in " << durationMs << " ms.\n";

    printRayPerSecond(img.width * img.height, durationMs);

    img.save("output.png");

    return 0;
}