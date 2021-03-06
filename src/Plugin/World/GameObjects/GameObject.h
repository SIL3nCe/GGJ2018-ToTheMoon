#pragma once

#include "ShSDK/ShSDK.h"

class GameObject
{

public:

	enum EType
	{
		e_type_void,
		e_type_ship,
		e_type_transmitter,
		e_type_bullet,
		e_type_explosion,
		e_type_planet,
	};

	explicit		GameObject			(ShEntity2* pEntity, const CShVector2 & vPosition);
	virtual			~GameObject			(void);

	virtual void	Initialize			(void);
	virtual void	Release				(void);

	virtual void	Update				(float dt);

	virtual void	OnHit				(GameObject* pObject) = 0;
	virtual EType	GetType				(void) = 0;

	void			SetState			(int iState);

	void			SetShow				(bool bShow);

	ShEntity2 *		GetSprite			(void);

	void			SetPosition2		(const CShVector2 & vPosition);
	CShVector2 &	GetPosition2		(void);

protected:
	EType					m_eType;
	int						m_iState;
	float					m_fStateTime;
	ShEntity2 *				m_pEntity;
	CShVector2				m_vPosition;

private:

};
