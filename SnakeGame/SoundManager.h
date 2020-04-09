#pragma once
#include "SFML/Audio.hpp"
#include <unordered_map>

class SoundManager {
public:
	SoundManager();
	~SoundManager();

	void PlaySFX(const std::string& _sfxName);

	void PlayMusic(const std::string& _musicName);

	void StopMusic();

	sf::SoundSource::Status Status() const { return m_sfx.getStatus(); }

private:
	void LoadSFX(const std::string& _fileName);
	void LoadMusic(const std::string& _fileName);

	sf::Sound m_music;
	std::unordered_map<std::string, sf::SoundBuffer*> m_musicBuffer;


	sf::Sound m_sfx;
	std::unordered_map<std::string, sf::SoundBuffer*> m_sfxBuffer;
};

