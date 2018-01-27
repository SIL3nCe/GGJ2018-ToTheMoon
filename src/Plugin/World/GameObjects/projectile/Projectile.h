#pragma once

#include "ShSDK/ShSDK.h"
#include "ShEngineExt/ShEngineExt.h"

#include "../GameObject.h"

class Projectile : public GameObject
{
public:

	explicit								Projectile			(ShEntity2 * pEntity, const CShVector2 & vPosition);
	virtual									~Projectile			(void);

	void									Initialize			(void);
	void									Release				(void);

	void									Start				(const CShVector2 & vPosition, const CShVector2 & vDestination, const CShVector2 & vSpeed);

	virtual void							Update				(float dt) = 0;

	virtual void							OnHit				(GameObject* pObject) = 0;
	virtual GameObject::EType				GetType				(void) = 0;

protected:
	CShVector2								m_vSpeed;

};