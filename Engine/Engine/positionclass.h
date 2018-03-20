#ifndef _POSITIONCLASS_H_
#define _POSITIONCLASS_H_
#endif
class PositionClass
{
public:
	PositionClass();
	PositionClass(const PositionClass &other);
	~PositionClass();

	void SetFrameTime(float frameTime);
	void GetRotation(float &rotation);
	void TurnLeft(bool keydown);
	void TurnRight(bool keydown);
private:
	float m_frameTime;
	float m_rotationY;
	float m_leftTurnSpeed;
	float m_rightTurnSpeed;
};

