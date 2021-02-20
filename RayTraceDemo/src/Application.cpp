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
#include "BVHNode.h"
#include "TimeCounter.h"
#include "NoiseTexture.h"

void saveToFile(const Renderer& renderer, const char* filePath);

int main()
{
	int width = 200;
	int heigth = 100;

	Point3 lookfrom(13.0f, 2.0f, 3.0f);
	Point3 lookat(0.0f, 0.0f, 0.0f);
	//float focusDistance = (lookfrom - lookat).length();
	float focusDistance = 10.0f;
	float apeture = 0.0f;

	Camera camera(lookfrom, lookat, Vector3f(0.0f, 1.0f, 0.0f), 20.0f, float(width)/float(heigth), apeture, focusDistance, 0.0f, 1.0f);
	Scene scene(width, heigth);
	Renderer renderer(width, heigth);

	NoiseTexture* texture = new NoiseTexture();

	const int nCount = 2;
	Object *objectList[nCount];
	objectList[0] = new Sphere(Point3(0.0f, -1000.0f, 0.0f), 1000.0f, new Lambertian(texture));
	objectList[1] = new Sphere(Point3(0.0f, 2.0f, 0.0f), 2.0f, new Lambertian(texture));

	scene.setObjectList(objectList, nCount);

	BVHNode* root = new BVHNode(objectList, nCount, 0.0f, 1.0f);
	scene.setBVHNode(root);

	{
		TimeCounter timer;
		renderer.render(scene, camera);
	}
	saveToFile(renderer, "BVH.ppm");

	std::cin.get();
}

void saveToFile(const Renderer& renderer, const char* filePath)
{
	float gamma = 1.0f / 2.2f;

	FILE* fp;
	fopen_s(&fp, filePath, "wb");
	fprintf(fp, "P3\n%d %d\n255", renderer.getWidth(), renderer.getHeight());
	for (auto& buffer : renderer.getFrameBuffer())
	{
		int R = std::powf(buffer.x(), gamma) * 255.0f;
		int G = std::powf(buffer.y(), gamma) * 255.0f;
		int B = std::powf(buffer.z(), gamma) * 255.0f;
		fprintf(fp, "\n%d %d %d", R, G, B);
	}
	fclose(fp);
}