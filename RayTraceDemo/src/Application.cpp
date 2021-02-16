#include "rtpch.h"
#include "Scene.h"
#include "Renderer.h"
#include "Camera.h"
#include "Sphere.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"

int main()
{
	int width = 200;
	int heigth = 100;

	Point3 lookfrom(3.0f, 3.0f, 2.0f);
	Point3 lookat(0.0f, 0.0f, -1.0f);
	float focusDistance = (lookfrom - lookat).length();
	float apeture = 2.0f;

	Camera camera(lookfrom, lookat, Vector3f(0.0f, 1.0f, 0.0f), 20.0f, float(width)/float(heigth), apeture, focusDistance);
	Scene scene(width, heigth);
	Renderer renderer(width, heigth);

	scene.addObject(std::make_unique<Sphere>(Point3(0.0f, 0.0f, -1.0f), 0.5f, new Lambertian(Vector3f(0.1f, 0.2f, 0.5f))));
	scene.addObject(std::make_unique<Sphere>(Point3(0.0f, -100.5f, -1.0f), 100.0f, new Lambertian(Vector3f(0.8f, 0.8f, 0.0f))));
	scene.addObject(std::make_unique<Sphere>(Point3(1.0f, 0.0f, -1.0f), 0.5f, new Metal(Vector3f(0.8f, 0.6f, 0.2f))));
	scene.addObject(std::make_unique<Sphere>(Point3(-1.0f, 0.0f, -1.0f), 0.5f, new Dielectric(1.5f)));
	scene.addObject(std::make_unique<Sphere>(Point3(-1.0f, 0.0f, -1.0f), -0.45f, new Dielectric(1.5f)));


	renderer.render(scene, camera);

	//
	float gamma = 1.0f / 2.2f;

	FILE* fp;
	fopen_s(&fp, "test.ppm", "wb");
	fprintf(fp, "P3\n%d %d\n255", width, heigth);
	for (auto& buffer : renderer.getFrameBuffer())
	{
		int R = std::powf(buffer.x(), gamma) * 255.0f;
		int G = std::powf(buffer.y(), gamma) * 255.0f;
		int B = std::powf(buffer.z(), gamma) * 255.0f;
		fprintf(fp, "\n%d %d %d", R, G, B);
	}
	fclose(fp);

	std::cin.get();
}