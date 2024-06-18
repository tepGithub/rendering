#include "Image/Image.h"
#include "BVH.h"
#include "Util.h"

#include "Math/Intersect.h"
using namespace Math;

#include <iostream>

static constexpr uint32_t kTriCount = 64;
Tri tris[kTriCount];

static void initScene()
{
    for (Tri& tri : tris)
    {
        float3 r0( RandomFloat(), RandomFloat(), RandomFloat() );
        float3 r1( RandomFloat(), RandomFloat(), RandomFloat() );
        float3 r2( RandomFloat(), RandomFloat(), RandomFloat() );
        tri.vertex0 = r0 * 9.0f - float3( 5.0f );
        tri.vertex1 = tri.vertex0 + r1;
        tri.vertex2 = tri.vertex0 + r2;
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
    BVH bvh(tris, kTriCount);

    Image img(640, 640);

    float3 camPos( 0, 0, -18 );
    float3 p0( -1, 1, -15 ), p1( 1, 1, -15 ), p2( -1, -1, -15 );
    Ray ray;
    
    Timer timer;

    for (uint32_t y = 0; y < img.height; y++)
    {
        for (uint32_t x = 0; x < img.width; x++)
        {
            float3 pixelPos = p0 + (p1 - p0) * (x / 640.0f) + (p2 - p0) * (y / 640.0f);
            ray.O = camPos;
            ray.D = normalize( pixelPos - ray.O );
            ray.t = Ray::kInf;

        #if 1
            bvh.intersect(ray);
        #else
            for( int i = 0; i < kTriCount; i++ )
                intersectRayTri( ray, tris[i] );
        #endif

            if (ray.t < Ray::kInf)
            {
                img(x, y) = colors::white();
            }
            else
            {
                img(x, y) = colors::black();
            }
        }
    }

    int64_t durationMs = timer.duration();
    std::cout << "elapsed in " << durationMs << " ms.\n";

    printRayPerSecond(img.width * img.height, durationMs);

    img.save("output.png");

    return 0;
}