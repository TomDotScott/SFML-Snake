#pragma once
#include "SFML/Audio.hpp"
#include <unordered_map>

class SoundManager {
public:
	SoundManager();
	
	void PlaySFX(const std::string& _sfxName);

	sf::SoundSource::Status Status() const { return m_sfx.getStatus(); }
	
private:

	void LoadSFX(const std::string& _fileName);
	
	sf::Sound m_music;
	std::unordered_map<std::string, sf::SoundBuffer*> m_musicBuffer;

	
	sf::Sound m_sfx;
	std::unordered_map<std::string, sf::SoundBuffer*> m_sfxBuffer;
};

