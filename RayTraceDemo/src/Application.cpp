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
#include "Cuboid.h"
#include "Triangle.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void saveToFile(const Renderer& renderer, const char* filePath);

int main()
{
	int width = 400;
	int heigth = 400;

	//Point3 lookfrom(278.0f, 278.0f, -800.0f);
	//Point3 lookat(278.0f, 278.0f, 0.0f);

	Point3 lookfrom(0.0f, 0.0, 3.0f);
	Point3 lookat(0.0, 0.0, 0.0f);
	Vector3f vup(0.0f, 1.0f, 0.0f);
	float vFov = 90.0f;
	float aspect = float(width) / float(heigth);
	float apeture = 0.0f;
	//float focusDistance = (lookfrom - lookat).length();
	float focusDistance = 10.0f;
	

	Camera camera(lookfrom, lookat, vup, vFov, aspect, apeture, focusDistance, 0.0f, 1.0f);
	Scene scene(width, heigth);
	Renderer renderer(width, heigth);

	Material* red = new Lambertian(new ConstantTexture(Color(0.65f, 0.05f, 0.05f)));
	Material* white = new Lambertian(new ConstantTexture(Color(0.73f)));
	Material* green = new Lambertian(new ConstantTexture(Color(0.12f, 0.45f, 0.15f)));
	Material* light = new DiffuseLight(new ConstantTexture(Color(15.0f)));


	/*const int nCount = 8;
	Object *objectList[nCount];
	objectList[0] = new FlipNormals(new YZRect(Point3(555.0f, 0.0f, 0.0f), Point3(555.0f, 555.0f, 555.0f), green));
	objectList[1] = new YZRect(Point3(0.0f, 0.0f, 0.0f), Point3(0.0f, 555.0f, 555.0f), red);
	objectList[2] = new XZRect(Point3(213.0f, 554.0f, 227.0f), Point3(343.0f, 554.0f, 332.0f), light);
	objectList[3] = new FlipNormals(new XZRect(Point3(0.0f, 555.0f, 0.0f), Point3(555.0f, 555.0f, 555.0f), white));
	objectList[4] = new XZRect(Point3(0.0f, 0.0f, 0.0f), Point3(555.0f, 0.0f, 555.0f), white);
	objectList[5] = new FlipNormals(new XYRect(Point3(0.0f, 0.0f, 555.0f), Point3(555.0f, 555.0f, 555.0f), white));
	objectList[6] = new Cuboid(Point3(130.0f, 0.0f, 65.0f), Point3(295.0f, 165.0f, 230.0f), white);
	objectList[7] = new Cuboid(Point3(265.0f, 0.0f, 295.0f), Point3(430.0f, 330.0f, 460.0f), white);*/

	Point3 vertex[6] = {
		Point3(-1.0f, -1.0f, 0.0f),
		Point3(1.0f, -1.0f, -2.0f),
		Point3(-1.0f, 1.0f, 0.0f),
		Point3(1.0f, -1.0f, -2.0f),
		Point3(-1.0f, 1.0f, 0.0f),
		Point3(1.0f, 1.0f, -2.0f)
	};

	Vector3f normal[6] = {
		Vector3f(0.0f, 0.0f, 1.0f),
		Vector3f(0.0f, 0.0f, 1.0f),
		Vector3f(0.0f, 0.0f, 1.0f),
		Vector3f(0.0f, 0.0f, 1.0f),
		Vector3f(0.0f, 0.0f, 1.0f),
		Vector3f(0.0f, 0.0f, 1.0f)
	};

	Point2 texCoord[6] = {
		Point2(0.0f, 0.0f),
		Point2(1.0f, 0.0f),
		Point2(0.0f, 1.0f),
		Point2(1.0f, 0.0f),
		Point2(0.0f, 1.0f),
		Point2(1.0f, 1.0f)
	};

	int textureWidth, textureHeight, channel;
	unsigned char* textureData = stbi_load("res/test.png", &textureWidth, &textureHeight, &channel, 0);
	float* srgb = convertToSRGB(textureWidth, textureHeight, textureData);

	Lambertian* material = new Lambertian(new ImageTexture(textureWidth, textureHeight, srgb));

	const int nCount = 2;
	Object *objectList[nCount];
	objectList[0] = new Triangle(vertex, normal, texCoord, material);
	objectList[1] = new Triangle(vertex + 3, normal + 3, texCoord + 3, material);

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
	float gamma = 1.0f / M_GAMMA;

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