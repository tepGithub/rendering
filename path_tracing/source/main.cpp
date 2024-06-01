// https://jacco.ompf2.com/2022/04/13/how-to-build-a-bvh-part-1-basics/
#include "Image/Image.h"
#include "Util.h"

#include "Math/Vector.h"
using namespace Math;

struct Tri
{
    float3 vertex0;
    float3 vertex1;
    float3 vertex2;
    float3 centroi;
};

struct Ray
{
    float3 O;
    float3 D;
    float t = 1e30f;
};

static constexpr uint32_t kTriCount = 64;
Tri tris[kTriCount];

static void init()
{
    for (Tri& tri : tris)
    {
        float3 r0( RandomFloat(), RandomFloat(), RandomFloat() );
        float3 r1( RandomFloat(), RandomFloat(), RandomFloat() );
        float3 r2( RandomFloat(), RandomFloat(), RandomFloat() );
        tri.vertex0 = r0 * 9.0f - float3( 5.0f );
        tri.vertex1 = tri.vertex0 + r1;
        tri.vertex2 = tri.vertex0 + r2;
    }
}

// https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
void IntersectTri( Ray& ray, const Tri& tri, const float kEpsilon = 0.0001f)
{
    const float3 edge1 = tri.vertex1 - tri.vertex0;
    const float3 edge2 = tri.vertex2 - tri.vertex0;
    const float3 h = cross( ray.D, edge2 );
    const float a = dot( edge1, h );
    if (a > -kEpsilon && a < kEpsilon) return; // ray parallel to triangle
    const float f = 1 / a;
    const float3 s = ray.O - tri.vertex0;
    const float u = f * dot( s, h );
    if (u < 0 || u > 1) return;
    const float3 q = cross( s, edge1 );
    const float v = f * dot( ray.D, q );
    if (v < 0 || u + v > 1) return;
    const float t = f * dot( edge2, q );
    if (t > kEpsilon) ray.t = min( ray.t, t );
}

int main()
{
    init();

    Image img(640, 640);

    float3 camPos( 0, 0, -18 );
    float3 p0( -1, 1, -15 ), p1( 1, 1, -15 ), p2( -1, -1, -15 );
    Ray ray;
    
    for (uint32_t y = 0; y < img.height; y++)
    {
        for (uint32_t x = 0; x < img.width; x++)
        {
            float3 pixelPos = p0 + (p1 - p0) * (x / 640.0f) + (p2 - p0) * (y / 640.0f);
            ray.O = camPos;
            ray.D = normalize( pixelPos - ray.O );
            ray.t = 1e30f;

            for( int i = 0; i < kTriCount; i++ )
                IntersectTri( ray, tris[i] );

            if (ray.t < 1e30f)
            {
                img(x, y) = colors::white();
            }
            else
            {
                img(x, y) = colors::black();
            }
        }
    }

    img.save("output.png");

    return 0;
}