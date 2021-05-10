#pragma once

typedef struct _tagAnimationFrameInfo
{
	Vector2		vStart;
	Vector2		vEnd;
}AnimationFrameInfo, * PAnimationFrameInfo;


typedef struct _tagRectInfo
{
	float	fL;
	float	fT;
	float	fR;
	float	fB;
}RectInfo, * PRectInfo;


typedef struct _tagSphereInfo
{
	Vector2	vCenter;
	float	fRadius = 0.f;
}SphereInfo, * PSphereInfo;