#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Tracer.h"
void Tracer::Initialise()
{
	WorldTexture = new Texture(FilepathWorldTexture);

	SceneCamera = new Camera(Vector3(0.f, 1.0f, -1.f), Vector3(0.0f, 1.0f, 0.0f), Vector3(0, 1, 0), 60, ASPECT_RATIO);

	Shapes.push_back(new Plane(Vector3(0, 0, 8), Vector3(0, 0, -1), &SilverMaterial, nullptr, nullptr));
	Shapes.push_back(new Plane(Vector3(0, 0, 0), Vector3(0, 1, 0), &SilverMaterial, nullptr, nullptr));
	Shapes.push_back(new Plane(Vector3(-8, 0, 0), Vector3(1, 0, 0), &BronzeMaterial, nullptr, nullptr));
	Shapes.push_back(new Plane(Vector3(0, 0, -8), Vector3(0, 0, 1), &LightMaterial, nullptr, nullptr));
	Shapes.push_back(new Plane(Vector3(8, 0, 0), Vector3(-1, 0, 0), &EmeraldMaterial, nullptr, nullptr));
	Shapes.push_back(new Plane(Vector3(0, 8, 0), Vector3(0, -1, 0), &LightMaterial, nullptr, nullptr));

	Shapes.push_back(new Sphere(Vector3(-1.f, 1.0f, 4.0), &ReflectiveMaterial, nullptr, nullptr, 1.0f));
	Shapes.push_back(new Sphere(Vector3(3.f, 1.0f, 5.f), &ReflectiveMaterial, nullptr, nullptr, 1.0f));
	Shapes.push_back(new Box(Vector3(-6.0f, 0.0f, 6.f), Vector3(-4.0f, 4.0f, 8.0f), &LightMaterial, nullptr, nullptr));

	Lights.push_back(new PointLight(Red, Vector3(0.f, 5.0f, 7.5f), 30));
	Lights.push_back(new PointLight(Green, Vector3(0.f, 4.0f, 2.f), 5));
	Lights.push_back(new PointLight(Skyblue, Vector3(-4.f, 1.0f, 2.f), 30));
	Lights.push_back(new PointLight(White, Vector3(0.f, 7.5f, 6.5f), 60));
	Lights.push_back(new PointLight(White, Vector3(2.f, 4.0f, 4.0f), 30));
	


	BoundingVolume = new BVH(Shapes);

	InitialisationCheck = true;
}

int Tracer::Render()
{
	if (!InitialisationCheck) return -1;

	for (unsigned int y = 0; y < SCR_HEIGHT; y++)
	{
		for (unsigned int x = 0; x < SCR_WIDTH; x++)
		{
			const float sx = float(x) / float(SCR_WIDTH) * 2.0f - 1.0f;
			const float sy = float(y) / float(SCR_HEIGHT) * -2.0f + 1.0f;

			Vector2 ScreenPosition = Vector2(sx, sy);
			Ray CameraRay = SceneCamera->ShootCameraRay(&ScreenPosition);
			Color c = Trace(0, CameraRay);
			Pixel ResultPixel = c;
			PixelData[y * SCR_WIDTH + x] = ResultPixel;
		}
	}

	return OutputPicture();
}

Color Tracer::Trace(const unsigned int RecursionDepth, const Ray& RayReference) const
{
	if (RecursionDepth > MAX_BOUNCES)
	{
		return Color(0.0f, 0.0f, 0.0f, 1.0f);
	}
	float OriginalHitDistance = MAX_DEPTH;
	int OriginalHitIndex = CheckBoundaries(RayReference, OriginalHitDistance);
	if (OriginalHitIndex != -1)
	{
		const Vector3 OriginalRayDirection = RayReference.get_Direction();
		const Vector3 OriginalHitLocation = RayReference.ValueAt(OriginalHitDistance);
		const Vector3 OriginalHitNormal = Shapes[OriginalHitIndex]->GetNormal(OriginalHitLocation);

		Color OriginalObjectColor = ObjectColor(OriginalHitIndex, OriginalRayDirection, OriginalHitLocation);
		const unsigned int ThisIntersection = IntersectionType(*Shapes[OriginalHitIndex]);

		if (ThisIntersection == static_cast<int>(RAY_HIT_RESULT::NORMAL))
		{
			return OriginalObjectColor;
		}
		else if (ThisIntersection == static_cast<int>(RAY_HIT_RESULT::REFLECTIVE))
		{
			float ReflectionMultiplier = Shapes[OriginalHitIndex]->GetMaterial()->GetReflectiveness();
			Vector3 ReflectDirection = Vector3::Reflect(OriginalRayDirection, OriginalHitNormal);
			const Ray ReflectionRay(OriginalHitLocation + (0.01f * ReflectDirection), ReflectDirection);
			return OriginalObjectColor * (1 - ReflectionMultiplier) + Trace(RecursionDepth + 1, ReflectionRay) * ReflectionMultiplier;
		}
		else if (ThisIntersection == static_cast<int>(RAY_HIT_RESULT::REFRACTIVE))
		{
			Color RefractivePart(0.0f, 0.0f, 0.0f, 1.0f);
			float RefractionAmount = Shapes[OriginalHitIndex]->GetMaterial()->GetRefractiveIndex();
			float ReflectionMultiplier = Shapes[OriginalHitIndex]->GetMaterial()->GetReflectiveness();
			float FresnelValue = 0;

			bool HitOutside = ((OriginalRayDirection * OriginalHitNormal) < 0);
			Vector3 PositionBias = 0.0001f * OriginalHitNormal;

			Vector3 RefractionDirection = Vector3::Refract(OriginalRayDirection, OriginalHitNormal, RefractionAmount, FresnelValue);

			if (FresnelValue < 1)
			{
				Vector3 RefractionPosition = HitOutside ? (OriginalHitLocation - PositionBias) : (OriginalHitLocation + PositionBias);
				Ray RefractionRay(RefractionPosition, RefractionDirection);
				RefractivePart = Trace(RecursionDepth + 1, RefractionRay);
			}

			Vector3 ReflectDirection = Vector3::Reflect(OriginalRayDirection, OriginalHitNormal);
			const Ray ReflectionRay(OriginalHitLocation + (0.01f * ReflectDirection), ReflectDirection);
			Color ReflectionPart = Trace(RecursionDepth + 1, ReflectionRay);

			return OriginalObjectColor * (1 - ReflectionMultiplier) + (ReflectionPart * FresnelValue) + (RefractivePart * (1 - FresnelValue));
		}
		else
		{
			return BackgroundColor;
		}
	}
	else
	{
		return BackgroundColor;
	}
}
bool Tracer::Shadow(const Vector3& HitLocation, int LightIndex) const
{
	Vector3 LightDirection = Lights[LightIndex]->GetLightDirection(HitLocation).Unit();
	const Ray RayToLight(HitLocation + LightDirection * 0.01f, LightDirection);
	float TDistance = MAX_DEPTH;
	int HitShadowObjectIndex = CheckBoundaries(RayToLight, TDistance);
	if (HitShadowObjectIndex != -1)
	{
		Vector3 T_RayHit = RayToLight.ValueAt(TDistance);
		float LightDistance = Lights[LightIndex]->DistanceToLight(HitLocation);
		float HitDistance = (T_RayHit - HitLocation).Magnitude() * (TDistance > 0);
		if (HitDistance < LightDistance - 0.1f)
		{
			return true;
		}
	}
	return false;
}

const int Tracer::CheckBoundaries(const Ray& RayReference, float& TValue) const
{
	int ObjectIndex = -1;
	float ObjectTValue = MAX_DEPTH;
	Shape* FoundObject = BoundingVolume->GetObjects(RayReference, ObjectTValue);
	if (FoundObject != NULL)
	{
		ObjectIndex = Shapes.find(FoundObject);
	}

	float PlaneTValue = MAX_DEPTH;
	for (unsigned int CurrentShapeIndex = 0; CurrentShapeIndex < Shapes.size(); CurrentShapeIndex++)
	{
		if (Shapes[CurrentShapeIndex]->GetType() == Shape::ShapeType::PLANE)
		{
			if (Shapes[CurrentShapeIndex]->RayIntersect(RayReference, PlaneTValue))
			{
				if (PlaneTValue < ObjectTValue)
				{
					ObjectTValue = PlaneTValue;
					ObjectIndex = CurrentShapeIndex;
				}
			}
		}
	}

	TValue = ObjectTValue;
	return ObjectIndex;
}
const int Tracer::IntersectionType(const Shape& HitObject) const
{
	if (HitObject.GetMaterial()->GetRefractiveIndex() != 0.0f)		return static_cast<int>(RAY_HIT_RESULT::REFRACTIVE);
	else if (HitObject.GetMaterial()->GetReflectiveness() != 0.0f)	return static_cast<int>(RAY_HIT_RESULT::REFLECTIVE);
	else return static_cast<int>(RAY_HIT_RESULT::NORMAL);
}

Color Tracer::ObjectColor(int ShapeIndex, const Vector3& RayDirection, const Vector3& HitLocation) const
{
	Vector3 ObjectNormal = Shapes[ShapeIndex]->GetNormal(HitLocation);
	// AMBIENT
	Color AmbientColor = Shapes[ShapeIndex]->GetMaterial()->GetAmbient() * White * AMBIENT_RATIO;

	Color Result(0.0f, 0.0f, 0.0f, 1.0f);
	for (unsigned int LightIndex = 0; LightIndex < Lights.size(); LightIndex++)
	{
		if (!Shadow(HitLocation, LightIndex))
		{
			Color LightColor = Lights[LightIndex]->GetColor();
			float LightAmount = Lights[LightIndex]->GetLightAmount(HitLocation);
			// LAMBERTIAN (DIFFUSE)
			Color DiffuseBase(Shapes[ShapeIndex]->GetMaterial()->GetDiffuse());

			Vector3 LightDir = Lights[LightIndex]->GetLightDirection(HitLocation);
			LightDir.Normalize();
			float SpecularDot = LightDir.Dot(ObjectNormal);
			SpecularDot = Utilities::ClampValue(1.0f, 0.0f, SpecularDot);

			Color DiffuseColor = DiffuseBase * SpecularDot * LightColor;

			// SPECULAR
			Color SpecularBase(Shapes[ShapeIndex]->GetMaterial()->GetSpecular());
			float SpecularAngle = 0.0f;
			float SpecularValue = 0.0f;
			if (SpecularDot > 0.0f)
			{
				Vector3 ViewDirection = -RayDirection;
				ViewDirection.Normalize();
				Vector3 HalfDirection = (ViewDirection + LightDir).Unit();
				SpecularAngle = HalfDirection * ObjectNormal;
				SpecularAngle = Utilities::ClampValue(1.0f, 0.0f, SpecularAngle);
				SpecularValue = pow(SpecularAngle, Shapes[ShapeIndex]->GetMaterial()->GetShininess());
			}

			Color SpecularColor = SpecularBase * SpecularValue * LightColor;

			SpecularColor = SpecularColor * LightAmount;
			DiffuseColor = DiffuseColor * LightAmount;
			Result = Result + DiffuseColor + SpecularColor;
		}
	}
	// RETURNING THE FINAL COLOR
	return (AmbientColor + Result) * Shapes[ShapeIndex]->GetUVColor(HitLocation);
}

const int Tracer::OutputPicture() const
{
	if (strlen(WriteFilename) + 1 >= MAX_FILENAME_LENGTH) return static_cast<int>(WRITE_RESULT::FILENAME_TOO_LONG);
	auto* path = "Output/";
	auto* command = "start ";

	char buf[64];
	strcpy_s(buf, path);
	strcat_s(buf, WriteFilename);
	char combuf[72];
	strcpy_s(combuf, command);
	strcat_s(combuf, buf);

	switch (WriteFilename[strlen(WriteFilename) - 2])
	{
	case 'n':
		if (stbi_write_png(buf, SCR_WIDTH, SCR_HEIGHT, 4, PixelData, 4 * SCR_WIDTH)) return static_cast<int>(WRITE_RESULT::SUCCESS);
		break;
	case 'p':
		if (stbi_write_jpg(buf, SCR_WIDTH, SCR_HEIGHT, 4, PixelData, 100))
		{
			system(combuf);
			return static_cast<int>(WRITE_RESULT::SUCCESS);
		}
		break;
	default:
		return static_cast<int>(WRITE_RESULT::FILETYPE_NOT_RECOGNISED);
		break;
	}
	return static_cast<int>(WRITE_RESULT::FAILED_TO_WRITE);
}