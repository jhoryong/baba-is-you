#pragma once

#include "../Game.h"

class CCollision
{
public:
	static bool CollisionRectToRect(class CColliderRect* pSrc,
		class CColliderRect* pDest);
	static bool CollisionRectToRect(Vector2& vIntersect, const RectInfo& tSrc,
		const RectInfo& tDest);

	static bool CollisionSphereToSphere(class CColliderSphere* pSrc,
		class CColliderSphere* pDest);
	static bool CollisionSphereToSphere(Vector2& vIntersect, const SphereInfo& tSrc,
		const SphereInfo& tDest);

	static bool CollisionRectToSphere(class CColliderRect* pSrc,
		class CColliderSphere* pDest);
	static bool CollisionRectToSphere(Vector2& vIntersect, const RectInfo& tSrc,
		const SphereInfo& tDest);

public:
	static bool CollisionRectToPoint(Vector2& vIntersect, const RectInfo& tSrc,
		const Vector2& vDest);
	static bool CollisionSphereToPoint(Vector2& vIntersect, const SphereInfo& tSrc,
		const Vector2& vDest);
};

