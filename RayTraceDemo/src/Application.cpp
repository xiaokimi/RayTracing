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

	Texture* checker = new CheckerTexture(new ConstantTexture(Color(0.2f, 0.3f, 0.1f)), new ConstantTexture(Color(0.9f, 0.9f, 0.9f)));

	Object *objectList[2];
	objectList[0] = new Sphere(Point3(0.0f, -10.0f, 0.0f), 10.0f, new Lambertian(checker));
	objectList[1] = new Sphere(Point3(0.0f, 10.0f, 0.0f), 10.0f, new Lambertian(checker));

	BVHNode* root = new BVHNode(objectList, 2, 0.0f, 1.0f);
	scene.setBVHNode(root);

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