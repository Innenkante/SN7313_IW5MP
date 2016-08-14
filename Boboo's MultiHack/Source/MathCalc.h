#pragma once
class Math_
{
public:
	float GetDistance(Vector3D source, Vector3D destination);
	float GetDistance(Vector2D source, Vector2D destination);
	float GetMagnitude(Vector3D vec);
	Vector3D SubtractVec(Vector3D src, Vector3D dest);
	Vector3D NormalizeVec(Vector3D vec);
	Vector3D MultiplyVec(Vector3D src, Vector3D dest);
	Vector2D CalcAngles(Vector3D src, Vector3D dest, Vector3D ViewAxis[3]);
private:

};

