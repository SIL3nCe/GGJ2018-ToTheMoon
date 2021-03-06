#pragma once

#include "ShSDK/ShSDK.h"
#include "ShEngineExt/ShEngineExt.h"

#include "../GameObject.h"

class Projectile : public GameObject
{
public:

	enum EProjectileState
	{
		OFF,
		ON
	};

	explicit								Projectile			(ShEntity2 * pEntity, const CShVector2 & vPosition);
	virtual									~Projectile			(void);

	void									Initialize			(void);
	void									Release				(void);

	void									Start				(const CShVector2 & vPosition, const CShVector2 & vDestination, float fSpeed, float fAngle);
	void									Stop				(void);

	void									Update				(float dt);

	virtual void							OnHit				(GameObject* pObject) = 0;
	virtual GameObject::EType				GetType				(void) = 0;

protected:
	CShVector2								m_vStartPosition;
	CShVector2								m_vDestination;
	float									m_fSpeed;
	float									m_fCompletion;
};
