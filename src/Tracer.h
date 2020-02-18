#pragma once

#include "stb_image_write.h"
#include "stb_image.h"
#include "assert.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Sphere.h"
#include "Plane.h"
#include "Camera.h"
#include "Box.h"
#include "Container.h"
#include "..\Include\BVH.h"
#include "..\Include\Node.h"


class Tracer
{
	enum class WRITE_RESULT
	{
		SUCCESS = 1,
		FILENAME_TOO_LONG = -1,
		FAILED_TO_WRITE = -2,
		FILETYPE_NOT_RECOGNISED = -3,
	};
	enum class RAY_HIT_RESULT
	{
		NORMAL = 1,
		REFLECTIVE = 2,
		REFRACTIVE = 3
	};

public:
	Tracer() { }
	~Tracer() { }

	// Initialising the objects on the scene
	void Initialise();
	// Render calculation functions
	const int CheckBoundaries(const Ray& RayReference, float& TValue) const;
	bool Shadow(const Vector3 &HitLocation, int LightIndex) const;

	Color ObjectColor(int ShapeIndex, const Vector3 &RayDirection, const Vector3& HitLocation) const;
	Color Trace(const unsigned int RecursionDepth, const Ray& RayReference) const;
	const int IntersectionType(const Shape& HitObject) const;

	// Main render function
	int Render();

	// Output function for the render function
	const int OutputPicture() const;

	bool InitialisationCheck = false;

private:
	// ================================== CONSTANT INTEGER VALUES
	const unsigned int SCR_WIDTH = 1920;
	const unsigned int SCR_HEIGHT = 1080;
	const unsigned int MAX_FILENAME_LENGTH = 64;
	const unsigned int MAX_BOUNCES = 15;
	const unsigned int NUM_OBJECTS = 10;
	const unsigned int NUM_LIGHTS = 5;


	// ================================== CONSTANT FLOAT VALUES
	const float MAX_DEPTH = 150.f;
	const float AMBIENT_RATIO = 0.1f;
	const float ASPECT_RATIO = static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT);
	// ================================== COLOR DEFINITIONS
	Color Skyblue = Color(0.0f, 0.0f, 0.5f, 1.0f);
	Color Lightblue = Color(0.035294f, 0.64705f, 0.83529411f, 1.0f);
	Color Black = Color(0.0f, 0.0f, 0.0f, 1.0f);
	Color Red = Color(1.0f, 0, 0, 1.0f);
	Color Green = Color(0, 1.0f, 0, 1.0f);
	Color Violet = Color(1.0f, 0, 1.0f, 1.0f);
	Color White = Color(1.0f, 1.0f, 1.0f, 1.0f);
	Color Pink = Color(1.0f, 0.41176f, 0.705882f, 1.0f);
	Color BackgroundColor = Lightblue;
	// ================================== MATERIAL DEFINITIONS
	Material BronzeMaterial = Material::EXAMPLE_BRONZE();
	Material EmeraldMaterial = Material::EXAMPLE_EMERALD();
	Material SilverMaterial = Material::EXAMPLE_SILVER();
	Material ReflectiveMaterial = Material::EXAMPLE_REFLECTIVE_MATERIAL();
	Material LightMaterial = Material::EXAMPLE_FULL_COLOR_MATERIAL();
	Material RefractionMaterial = Material::EXAMPLE_HALF_REFRACTIVE_MATERIAL();

	// ================================== FILE PATHS
	const char* WriteFilename = "TestScene.jpg";
	const char* FilepathWorldTexture = "resources/world.png";
	const char* FilepathWorldNormal = "resources/normals.jpg";
	// ================================== PIXEL ARRAY FOR DRAWING
	Pixel* PixelData = new Pixel[SCR_WIDTH * SCR_HEIGHT];
	// ================================== SHAPES ARRAY FOR HOLDING OBJECTS

	Vector<Shape*> Shapes{ NUM_OBJECTS };
	Vector<Light*> Lights{ NUM_LIGHTS };
	BVH* BoundingVolume = nullptr;


	Camera* SceneCamera = nullptr;
	// ================================== TEXTURES
	Texture* WorldTexture = nullptr;

};