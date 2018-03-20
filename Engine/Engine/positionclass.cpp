#include "positionclass.h"


PositionClass::PositionClass()
{
	m_frameTime = 0.0f;
	m_rotationY = 0.0f;
	m_leftTurnSpeed = 0.0f;
	m_rightTurnSpeed = 0.0f;
}


PositionClass::~PositionClass()
{
}

void PositionClass::SetFrameTime(float frameTime)
{
	m_frameTime = frameTime;
}

void PositionClass::GetRotation(float &rotation)
{
	rotation = m_rotationY;
}

void PositionClass::TurnLeft(bool keydown)
{
	if (keydown)
	{
		m_leftTurnSpeed += m_frameTime * 0.01f;
		if (m_leftTurnSpeed > (m_frameTime * 0.15))
		{
			m_leftTurnSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_leftTurnSpeed -= m_frameTime * 0.005f;
		if (m_leftTurnSpeed < 0.0f)
		{
			m_leftTurnSpeed = 0.0f;
		}
	}
	m_rotationY -= m_leftTurnSpeed;
	if (m_rotationY < 0.0f)
	{
		m_rotationY += 360.0f;
	}
}

void PositionClass::TurnRight(bool keydown)
{
	if (keydown)
	{
		m_rightTurnSpeed += m_frameTime * 0.01f;
		if (m_rightTurnSpeed > (m_frameTime * 0.15))
		{
			m_rightTurnSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_rightTurnSpeed -= m_frameTime * 0.005f;
		if (m_rightTurnSpeed < 0.0f)
		{
			m_rightTurnSpeed = 0.0f;
		}
	}
	m_rotationY += m_rightTurnSpeed;
	if (m_rotationY > 360.0f)
	{
		m_rotationY -= 360.0f;
	}
}
