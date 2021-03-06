#pragma once

/**
 * @brief Game::get
 * @param state
 * @return
 */
inline GameState * Game::get(EState state)
{
	switch (state)
	{
		case MAIN_MENU:
		{
			return(&m_stateMainMenu);
		}
		break;

		case SHIP_SELECTION:
		{
			return(&m_stateShipSelection);
		}
		break;

		case GAME_LEVEL:
		{
			return(&m_stateGame);
		}
		break;

		default:
		{
			SH_ASSERT_ALWAYS();
			return((GameState*)0); // this should never happen
		}
	}
}

/**
 * @brief Game::GetPersistentData
 * @return
 */
inline PersistentData & Game::GetPersistentData(void)
{
	return(m_PersistentData);
}

/**
 * @brief Game::GetInputManager
 * @return
 */
inline Inputs & Game::GetInputManager(void)
{
	return(m_Inputs);
}
