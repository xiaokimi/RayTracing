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
#include "Mat.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void saveToFile(const Renderer& renderer, const char* filePath);
BVHNode* createCornellBox();
Cuboid* createOneCuoid(const Vector3f& scaled, const Mat3& rotated, const Vector3f& translated, Material* material);

int main()
{
	int width = 400;
	int heigth = 400;

	Point3 lookfrom(278.0f, 278.0f, -800.0f);
	Point3 lookat(278.0f, 278.0f, 0.0f);
	Vector3f vup(0.0f, 1.0f, 0.0f);
	float vFov = 40.0f;
	float aspect = float(width) / float(heigth);
	float apeture = 0.0f;
	float focusDistance = 10.0f;

	Camera camera(lookfrom, lookat, vup, vFov, aspect, apeture, focusDistance, 0.0f, 1.0f);
	Scene scene(width, heigth);
	Renderer renderer(width, heigth);

	BVHNode* root = createCornellBox();
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
	errno_t err = fopen_s(&fp, filePath, "wb");
	fprintf(fp, "P3\n%d %d\n255", renderer.getWidth(), renderer.getHeight());
	for (auto& buffer : renderer.getFrameBuffer())
	{
		int R = lerp<float>(0.0f, 1.0f, std::powf(buffer.x(), gamma)) * 255.0f;
		int G = lerp<float>(0.0f, 1.0f, std::powf(buffer.y(), gamma)) * 255.0f;
		int B = lerp<float>(0.0f, 1.0f, std::powf(buffer.z(), gamma)) * 255.0f;
		fprintf(fp, "\n%d %d %d", R, G, B);
	}
	fclose(fp);
}

BVHNode* createCornellBox()
{
	Material* red = new Lambertian(new ConstantTexture(Color(0.65f, 0.05f, 0.05f)));
	Material* white = new Lambertian(new ConstantTexture(Color(0.73f)));
	Material* green = new Lambertian(new ConstantTexture(Color(0.12f, 0.45f, 0.15f)));
	Material* light = new DiffuseLight(new ConstantTexture(Color(15.0f)));

	int i = 0;
	Object** objectList = new Object* [8];
	objectList[i++] = new FlipNormals(new YZRect(Point3(555.0f, 0.0f, 0.0f), Point3(555.0f, 555.0f, 555.0f), green));
	objectList[i++] = new YZRect(Point3(0.0f, 0.0f, 0.0f), Point3(0.0f, 555.0f, 555.0f), red);
	objectList[i++] = new XZRect(Point3(213.0f, 554.0f, 227.0f), Point3(343.0f, 554.0f, 332.0f), light);
	objectList[i++] = new FlipNormals(new XZRect(Point3(0.0f, 555.0f, 0.0f), Point3(555.0f, 555.0f, 555.0f), white));
	objectList[i++] = new XZRect(Point3(0.0f, 0.0f, 0.0f), Point3(555.0f, 0.0f, 555.0f), white);
	objectList[i++] = new FlipNormals(new XYRect(Point3(0.0f, 0.0f, 555.0f), Point3(555.0f, 555.0f, 555.0f), white));

	objectList[i++] = createOneCuoid(Vector3f(165.0f), rotate(Mat3(1.0f), Vector3f(0.0f, 1.0f, 0.0f), -18.0f), Vector3f(130.0f, 0.0f, 65.0f), white);
	objectList[i++] = createOneCuoid(Vector3f(165.0f, 330.0f, 165.0f), rotate(Mat3(1.0f), Vector3f(0.0f, 1.0f, 0.0f), 15.0f), Vector3f(265.0f, 0.0f, 295.0f), white);

	return new BVHNode(objectList, i, 0.0f, 1.0f);
}

Cuboid* createOneCuoid(const Vector3f& scaled, const Mat3& rotated, const Vector3f& translated, Material* material)
{
	Point3 vertex[8] = {
		Point3(0.0f, 0.0f, 0.0f),
		Point3(1.0f, 0.0f, 0.0f),
		Point3(0.0f, 1.0f, 0.0f),
		Point3(1.0f, 1.0f, 0.0f),
		Point3(0.0f, 0.0f, 1.0f),
		Point3(1.0f, 0.0f, 1.0f),
		Point3(0.0f, 1.0f, 1.0f),
		Point3(1.0f, 1.0f, 1.0f)
	};

	for (int i = 0; i < 8; i++)
	{
		vertex[i] = vertex[i] * scaled;
		vertex[i] = rotated * vertex[i];
		vertex[i] += translated;
	}

	int indices[36] = {
		0, 1, 2,
		1, 3, 2,

		4, 5, 6,
		5, 7, 6,

		5, 1, 7,
		1, 3, 7,

		0, 4, 2,
		4, 6, 2,

		6, 7, 2,
		7, 3, 2,

		4, 5, 0,
		5, 1, 0
	};

	Vector3f normal[6] = {
		Vector3f(0.0f, 0.0f, -1.0f),
		Vector3f(0.0f, 0.0f, 1.0f),
		Vector3f(1.0f, 0.0f, 0.0f),
		Vector3f(-1.0f, 0.0f, 0.0f),
		Vector3f(0.0f, 1.0f, 0.0f),
		Vector3f(0.0f, -1.0f, 0.0f)
	};

	for (int i = 0; i < 6; i++)
	{
		normal[i] = rotated * normal[i];
	}

	int nCount = 12;
	Object** objectList = new Object* [nCount];
	for (int i = 0; i < nCount; i++)
	{
		Point3 v[3];
		Vector3f n[3];
		Point2 c[3];
		for (int j = 0; j < 3; j++)
		{
			v[j] = vertex[indices[i * 3 + j]];
			n[j] = normal[i / 2];
			c[j] = Point2(0.0f, 0.0f);
		}

		objectList[i] = new Triangle(v, n, c, material);
	}

	return new Cuboid(objectList, nCount);
}