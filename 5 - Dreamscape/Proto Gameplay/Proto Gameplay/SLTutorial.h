#ifndef SLTUTORIAL_H
#define SLTUTORIAL_H

#include "Common.h"
#include "SLPlayer.h"
#include "SLBoss.h"
#include "SLMap.h"
#include "SLSounds.h"
#include "Camera.h"
#include "Easing.h"
#include "Video.h"

class SLTutorial
{
public:
	SLTutorial(Camera* _camera, SLPlayer* _player, SLMap* _map, SLBoss* _boss, std::string _mapString);

	void Update(float _dt, Config _config);

	void Display(sf::RenderWindow& _window);
	void DisplayPopUps(sf::RenderWindow& _window);

	const bool IsInBossFight() { return m_isInBossFight; }
	const bool GetCinematicMode() { return m_isInCinematicMode; }
	const bool GetPause() { return m_pause || m_isInCinematicMode; }
	const sf::Vector2f GetSpiritPosition() { return m_spirit.onScreenPos; };
	const sf::Vector2f GetGemPos() { return m_gemSprite.getPosition(); };

	const bool HasWon() { return m_currentEvent == NUMBER_OF_EVENTS; }

	const std::vector<sf::Vector2f> GetActiveTargets() { return m_activeTargets; };

private:
	enum SpiritStates
	{
		WAITING,
		FOLLOWING
	};

	struct Spirit
	{
		sf::Sprite sprite;

		sf::Vector2f pos;
		sf::Vector2f onScreenPos;

		sf::Vector2f velocity;
		sf::Vector2f target;

		float speed;
		float amplitude;
		float movementSpeed;

		SpiritStates state;
	};

	enum RonceSpriteType
	{
		START,
		MIDDLE,
		END
	};

	struct RonceSprite
	{
		sf::Sprite sprite;
		RonceSpriteType type;
		sf::Vector2f pos;
	};

	struct Ronce
	{
		std::vector<sf::Vector2i> tileList;
		std::vector<RonceSprite> sprites;
		bool dir;
		bool active = true;
		AnimationManager anim;
	};

	enum EventList
	{
		INITIAL_ANIM,
		NORMAL_ATTACK,
		DODGE,
		HUD,
		SPECIAL_ATTACK,
		LOCK,
		SWITCH_TARGET,
		SHROOMS,
		BOSS_CORRIDOR,
		BOSS_END,
		NUMBER_OF_EVENTS
	};

	Config m_currentConfig;

	sf::Sprite m_popUp[NUMBER_OF_EVENTS][2];
	Video m_previewVideos[NUMBER_OF_EVENTS];

	sf::Vector2f m_tileList[NUMBER_OF_EVENTS];
	sf::Vector2f m_champiTiles[3];
	sf::Sprite m_champiSprite[3];
	std::vector<sf::Vector2f> m_activeTargets;

	EventList m_currentEvent;
	Spirit m_spirit;
	sf::Sprite m_evilSpirit;
	Ronce m_ronces[3];
	int m_ronceToRetract = -1;

	sf::Sprite m_bossSprite;
	AnimationManager m_bossAnimation;
	sf::Sprite m_pieux[5];
	AnimationManager m_pieuxAnimation;
	sf::Sprite m_gemSprite;

	sf::Shader m_shader;
	SLSounds m_sounds;

	sf::Clock m_easingsClock;
	sf::Texture m_windowContent;
	sf::Sprite m_windowSprite;

	sf::Shader m_desatShader;

	Camera* m_camera;
	SLPlayer* m_player;
	SLBoss* m_boss;
	SLMap* m_map;

	sf::Music m_currentTheme;
	float m_musicVolume;

	bool m_isInCinematicMode = false;
	bool m_pause = true;
	bool m_skippable = false;
	bool m_isInBossFight = false;
	int m_door;
	float m_timer;

	void InitRonces(std::string _mapString);
	void InitVideoPreviews(int _ID);

	void ToggleNextEvent();
	void UpdateSpiritMovement(float _dt);
	void PlayCinematic(float _dt);

	void UpdateShroomStates();

	void DisplayTutorialPopUp(sf::RenderWindow& _window);

	bool IsCollidingTriggerTile();
	void OverWriteTrigger();
};

#endif