#include "rtpch.h"
#include "Scene.h"
#include "Renderer.h"
#include "Camera.h"
#include "Sphere.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"
#include "MovingSphere.h"
#include "ConstantTexture.h"
#include "CheckerTexture.h"

int main()
{
	int width = 800;
	int heigth = 600;

	Point3 lookfrom(0.0f, 2.0f, 2.0f);
	Point3 lookat(0.0f, 0.0f, -1.0f);
	//float focusDistance = (lookfrom - lookat).length();
	float focusDistance = 1.0f;
	float apeture = 0.0f;

	Camera camera(lookfrom, lookat, Vector3f(0.0f, 1.0f, 0.0f), 90.0f, float(width)/float(heigth), apeture, focusDistance, 0.0f, 1.0f);
	Scene scene(width, heigth);
	Renderer renderer(width, heigth);

	Texture* checker = new CheckerTexture(new ConstantTexture(Color(0.2f, 0.3f, 0.1f)), new ConstantTexture(Color(0.9f, 0.9f, 0.9f)));

	scene.addObject(std::make_unique<Sphere>(Point3(0.0f, 1.0f, -1.0f), 1.5f, new Dielectric(1.5f)));

	//scene.addObject(std::make_unique<Sphere>(Point3(0.0f, 0.0f, -1.0f), 0.5f, new Lambertian(new ConstantTexture(Color(0.1f, 0.2f, 0.5f)))));
	scene.addObject(std::make_unique<Sphere>(Point3(0.0f, -100.5f, -1.0f), 100.0f, new Lambertian(checker)));
	//scene.addObject(std::make_unique<Sphere>(Point3(1.0f, 0.0f, -1.0f), 0.5f, new Metal(Vector3f(0.8f, 0.6f, 0.2f))));
	//scene.addObject(std::make_unique<Sphere>(Point3(-1.0f, 0.0f, -1.0f), 0.5f, new Dielectric(1.5f)));
	//scene.addObject(std::make_unique<Sphere>(Point3(-1.0f, 0.0f, -1.0f), -0.45f, new Dielectric(1.5f)));

	Vector3f center0(-2.0f, 0.0f, -1.0f);
	Vector3f center1 = center0 + Vector3f(0.0f, 0.5f * dis(gen), 0.0f);
	//scene.addObject(std::make_unique<MovingSphere>(center0, center1, 0.0f, 1.0f, 0.5f, new Lambertian(new ConstantTexture(Color(0.1f, 0.2f, 0.5f)))));


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