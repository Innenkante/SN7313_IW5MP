#pragma once
static class Math
{
public:
	static float GetDistance(Vector3D source, Vector3D destination);
	static float GetDistance(Vector2D source, Vector2D destination);
	static float GetMagnitude(Vector3D vec);
	static Vector3D SubtractVec(Vector3D src, Vector3D dest);
	static Vector3D NormalizeVec(Vector3D vec);
	static Vector3D MultiplyVec(Vector3D src, Vector3D dest);
	static Vector2D CalcAngles(Vector3D src, Vector3D dest, Vector3D ViewAxis[3]);
private:

};

