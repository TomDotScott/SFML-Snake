#pragma once
#include "SFML/Audio.hpp"
#include <unordered_map>

/**
 * \brief The SoundManager class controls the audio within the game. All SFX and music are called through it
 */
class SoundManager {
public:
	/**
	 * \brief Constructs a SoundManager object
	 */
	SoundManager();

	/**
	 * \brief Plays a given sound effect
	 * \param _sfxName The file name to play
	 */
	void PlaySFX(const std::string& _sfxName);

	/**
	 * \brief Plays a given music track
	 * \param _musicName The file name to play
	 */
	void PlayMusic(const std::string& _musicName);

	/**
	 * \brief Stops the music that is currently playing
	 */
	void StopMusic();

	/**
	 * \return the status of the SoundManager
	 */
	sf::SoundSource::Status Status() const { return m_sfx.getStatus(); }

private:
	/**
	 * \brief Loads a given sound effect
	 * \param _fileName The file name to load
	 */
	void LoadSFX(const std::string& _fileName);

	/**
	 * \brief Loads a given music track
	 * \param _fileName The file name to load
	 */
	void LoadMusic(const std::string& _fileName);

	sf::Sound m_music;
	std::unordered_map<std::string, sf::SoundBuffer> m_musicBuffer;

	sf::Sound m_sfx;
	std::unordered_map<std::string, sf::SoundBuffer> m_sfxBuffer;
};

