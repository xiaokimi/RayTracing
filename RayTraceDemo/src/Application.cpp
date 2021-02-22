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
#include "AxisAlignedRect.h"
#include "FlipNormals.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void saveToFile(const Renderer& renderer, const char* filePath);

int main()
{
	int width = 400;
	int heigth = 400;

	Point3 lookfrom(278.0f, 278.0f, -800.0f);
	Point3 lookat(278.0f, 278.0f, 0.0f);
	//float focusDistance = (lookfrom - lookat).length();
	float focusDistance = 10.0f;
	float apeture = 0.0f;

	Camera camera(lookfrom, lookat, Vector3f(0.0f, 1.0f, 0.0f), 40.0f, float(width)/float(heigth), apeture, focusDistance, 0.0f, 1.0f);
	Scene scene(width, heigth);
	Renderer renderer(width, heigth);

	Material* red = new Lambertian(new ConstantTexture(Color(0.65f, 0.05f, 0.05f)));
	Material* white = new Lambertian(new ConstantTexture(Color(0.73f)));
	Material* green = new Lambertian(new ConstantTexture(Color(0.12f, 0.45f, 0.15f)));
	Material* light = new DiffuseLight(new ConstantTexture(Color(15.0f)));


	const int nCount = 6;
	Object *objectList[nCount];
	objectList[0] = new FlipNormals(new YZRect(Point3(555.0f, 0.0f, 0.0f), Point3(555.0f, 555.0f, 555.0f), green));
	objectList[1] = new YZRect(Point3(0.0f, 0.0f, 0.0f), Point3(0.0f, 555.0f, 555.0f), red);
	objectList[2] = new XZRect(Point3(213.0f, 554.0f, 227.0f), Point3(343.0f, 554.0f, 332.0f), light);
	objectList[3] = new FlipNormals(new XZRect(Point3(0.0f, 555.0f, 0.0f), Point3(555.0f, 555.0f, 555.0f), white));
	objectList[4] = new XZRect(Point3(0.0f, 0.0f, 0.0f), Point3(555.0f, 0.0f, 555.0f), white);
	objectList[5] = new FlipNormals(new XYRect(Point3(0.0f, 0.0f, 555.0f), Point3(555.0f, 555.0f, 555.0f), white));

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