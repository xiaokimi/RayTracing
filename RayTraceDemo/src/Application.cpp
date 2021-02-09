#include "rtpch.h"
#include "HitableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material.h"
#include "Lambertian.h"
#include "Metal.h"

Color getColor(const Ray& ray, const Hitable* world, int depth)
{
	HitRecord record;
	if (world->hit(ray, 0.001f, MAXFLOAT, record))
	{
		Ray scattered;
		Vector3f attenuation;
		if (depth < 50 && record.material->scatter(ray, record, attenuation, scattered))
		{
			return attenuation * getColor(scattered, world, depth + 1);
		}
		else
		{
			return Vector3f(0.0f, 0.0f, 0.0f);
		}
	}
		
	Vector3f dir = ray.getDirection().normalize();
	float t = 0.5f * (dir.y() + 1.0);
	return (1.0f - t) * Vector3f(1.0f, 1.0f, 1.0f) + t * Vector3f(0.5f, 0.7f, 1.0f);
}

int main()
{
	//
	Camera camera;

	Hitable *list[4];
	list[0] = new Sphere(Point3(0.0f, 0.0f, -1.0f), 0.5f, new Lambertian(Vector3f(0.8f, 0.3f, 0.3f)));
	list[1] = new Sphere(Point3(0.0f, -100.5f, -1.0f), 100.0f, new Lambertian(Vector3f(0.8f, 0.8f, 0.0f)));
	list[2] = new Sphere(Point3(1.0f, 0.0f, -1.0f), 0.5f, new Metal(Vector3f(0.8f, 0.6f, 0.2f)));
	list[3] = new Sphere(Point3(-1.0f, 0.0f, -1.0f), 0.5f, new Metal(Vector3f(0.8f, 0.8f, 0.8f)));

	Hitable* world = new HitableList(list, 4);

	//
	int width = 200, height = 100;
	int sampleCount = 100;
	
	FILE* fp;
	errno_t err = fopen_s(&fp, "test.ppm", "wb");

	fprintf(fp, "P3\n%d %d\n255", width, height);
	for (int j = height - 1; j >= 0; j--)
	{
		for (int i = 0; i < width; i++)
		{
			Color color(0.0f, 0.0f, 0.0f);
			for (int s = 0; s < sampleCount; s++)
			{
				float u = (i * 1.0f + dis(gen)) / width;
				float v = (j * 1.0f + dis(gen))/ height;

				Ray ray = camera.getRay(u, v);
				color += getColor(ray, world, 0);
			}
			color /= sampleCount;

			int ir = int(255 * std::sqrt(color.x()));
			int ig = int(255 * std::sqrt(color.y()));
			int ib = int(255 * std::sqrt(color.z()));

			fprintf(fp, "\n%d %d %d", ir, ig, ib);
		}
	}
	fclose(fp);

	std::cin.get();
}