#include "Ship.h"

#include "NetworkHelper.h"

#include <string.h> // memcpy
#include <math.h>

namespace Network
{

/**
 * @brief Default constructor
 */
Ship::Ship(void) : m_position(0.0f, 0.0f), m_target(0.0f, 0.0f), m_speed(0.0f), m_team(0), m_eShipType(0), m_life(0), m_bNeedSync(false)
{
#if __gnu_linux__
	uuid_clear(m_uuid);
#else
	memset(&m_uuid, 0, sizeof(uuid_t));
#endif // __gnu_linux__
}

/**
 * @brief Constructor
 * @param id
 */
Ship::Ship(const uuid_t & id, unsigned int team, unsigned int life, unsigned int eShipType) : m_position(0.0f, 0.0f), m_target(0.0f, 0.0f), m_speed(0.0f), m_team(team), m_life(life), m_eShipType(eShipType), m_bNeedSync(false)
{
#if __gnu_linux__
	uuid_copy(m_uuid, id);
#else
	memcpy(&m_uuid, (void*)&id, sizeof(uuid_t));
#endif // __gnu_linux__
}

/**
 * @brief Constructor
 * @param id
 * @param x
 * @param y
 */
Ship::Ship(const uuid_t & id, unsigned int team, unsigned int life, unsigned int eShipType, float x, float y) : m_position(x, y), m_target(x, y), m_speed(0.0f), m_team(team), m_life(life), m_eShipType(eShipType), m_bNeedSync(false)
{
#if __gnu_linux__
	uuid_copy(m_uuid, id);
#else
	memcpy(&m_uuid, (void*)&id, sizeof(uuid_t));
#endif // __gnu_linux__
}

/**
 * @brief Destructor
 */
Ship::~Ship(void)
{
	// ..
}

/**
 * @brief update
 * @param delta time in seconds
 */
void Ship::update(float dt, NetworkHelper & network)
{
	vec2 direction;
	direction.x = m_target.x - m_position.x;
	direction.y = m_target.y - m_position.y;

	float norm = sqrt((direction.x*direction.x) + (direction.y*direction.y));

	if (norm > 0.0001f)
	{
		direction.x /= norm;
		direction.y /= norm;

		m_position.x += direction.x * m_speed * dt;
		m_position.y += direction.y * m_speed * dt;
	}
	else
	{
		m_position.x = m_target.x;
		m_position.y = m_target.y;
	}

	if (m_bNeedSync)
	{
		SyncShipStateMessage message;
#if __gnu_linux__
		uuid_copy(message.shipId, m_uuid);
#else
		memcpy(&message.shipId, (void*)&m_uuid, sizeof(uuid_t));
#endif // __gnu_linux__
		message.position = m_position;
		message.target = m_target;
		message.speed = m_speed;
		message.life = m_life;
		message.team = m_team;
		message.shipType = m_eShipType;

		network.SendMessageToAllClients(message);

		m_bNeedSync = false;
	}
}

/**
 * @brief Clamp position
 * @param halfSize
 */
void Ship::clampPosition(const vec2 & halfSize)
{
	//
	// Clamp X
	if (m_position.x > halfSize.x)
	{
		m_position.x = halfSize.x;
	}
	else if (m_position.x < -halfSize.x)
	{
		m_position.x = -halfSize.x;
	}

	//
	// Clamp Y
	if (m_position.y > halfSize.y)
	{
		m_position.y = halfSize.y;
	}
	else if (m_position.y < -halfSize.y)
	{
		m_position.y = -halfSize.y;
	}
}

}
