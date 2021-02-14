#include "rtpch.h"
#include "HitableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"

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

Hitable* randomScene()
{
	int n = 500;
	Hitable** list = new Hitable*[n + 1];
	list[0] = new Sphere(Point3(0.0f, -1000.0f, 0.0f), 1000, new Lambertian(Vector3f(0.5f, 0.5f, 0.5f)));

	int i = 1;
	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			float chooseMat = dis(gen);
			Vector3f center(a + 0.9 * dis(gen), 0.2f, b + 0.9f * dis(gen));
			if ((center - Vector3f(4.0f, 0.2f, 0.0f)).length() > 0.9f)
			{
				if (chooseMat < 0.8f)
				{
					list[i++] = new Sphere(center, 0.2f, new Lambertian(Vector3f(dis(gen) * dis(gen), dis(gen) * dis(gen), dis(gen) * dis(gen))));
				}
				else if (chooseMat < 0.95f)
				{
					list[i++] = new Sphere(center, 0.2f, new Metal(Vector3f(0.5f * (1.0f + dis(gen)), 0.5f * (1.0f + dis(gen)), 0.5f * (1.0f + dis(gen))), 0.5 * dis(gen)));
				}
				else
				{
					list[i++] = new Sphere(center, 0.2f, new Dielectric(1.5f));
				}
			}
		}
	}

	list[i++] = new Sphere(Point3(0.0f, 1.0f, 0.0f), 1.0f, new Dielectric(1.5f));
	list[i++] = new Sphere(Point3(-4.0f, 1.0f, 0.0f), 1.0f, new Lambertian(Vector3f(0.4f, 0.2f, 0.1f)));
	list[i++] = new Sphere(Point3(4.0f, 1.0f, 0.0f), 1.0f, new Metal(Vector3f(0.7f, 0.6f, 0.5f), 0.0f));

	return new HitableList(list, i);
}

int main()
{
	int width = 1200, height = 800;

	//
	Point3 lookfrom(13.0f, 2.0f, 3.0f);
	Point3 lookat(0.0f, 0.0f, 0.0f);
	float distToFocus = 10.0f;
	float aperture = 0.1f;

	Camera camera(lookfrom, lookat, Vector3f(0.0f, 1.0f, 0.0f), 20.0f, float(width) / float(height), aperture, distToFocus);

	Hitable* world = randomScene();

	//
	int sampleCount = 10;
	
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

		updateProgress(1.0f - j / (float)height);
	}
	updateProgress(1.0f);
	fclose(fp);

	std::cin.get();
}