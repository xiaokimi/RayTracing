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
#include "ImageTexture.h"
#include "DiffuseLight.h"
#include "XYRect.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void saveToFile(const Renderer& renderer, const char* filePath);

int main()
{
	int width = 400;
	int heigth = 400;

	Point3 lookfrom(13.0f, 0.0f, 3.0f);
	Point3 lookat(0.0f, 0.0f, 0.0f);
	//float focusDistance = (lookfrom - lookat).length();
	float focusDistance = 10.0f;
	float apeture = 0.0f;

	Camera camera(lookfrom, lookat, Vector3f(0.0f, 1.0f, 0.0f), 20.0f, float(width)/float(heigth), apeture, focusDistance, 0.0f, 1.0f);
	Scene scene(width, heigth);
	Renderer renderer(width, heigth);

	int textureWidth, textureHeight, channel;
	unsigned char* textureData = stbi_load("res/sky.jpg", &textureWidth, &textureHeight, &channel, 0);

	ImageTexture* imageTexture = new ImageTexture(textureWidth, textureHeight, textureData);

	NoiseTexture* texture = new NoiseTexture();

	const int nCount = 2;
	Object *objectList[nCount];
	objectList[0] = new Sphere(Point3(0.0f, 0.0f, 0.0f), 1.0f, new Lambertian(imageTexture));
	objectList[1] = new XYRect(Point3(-0.5f, -0.5f, -1.5f), Point3(0.5f, 0.5f, -2.5f), new DiffuseLight(new ConstantTexture(Color(4.0f))));

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
		int R = lerp(0.0f, 1.0f, std::powf(buffer.x(), gamma)) * 255.0f;
		int G = lerp(0.0f, 1.0f, std::powf(buffer.y(), gamma)) * 255.0f;
		int B = lerp(0.0f, 1.0f, std::powf(buffer.z(), gamma)) * 255.0f;
		fprintf(fp, "\n%d %d %d", R, G, B);
	}
	fclose(fp);
}