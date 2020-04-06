#include "SoundManager.h"

SoundManager::SoundManager()
{
	LoadSFX("sfx_gobble_on");
}

void SoundManager::PlaySFX(const std::string& _sfxName)
{
	m_sfx.setBuffer(*m_sfxBuffer.at(_sfxName));
	m_sfx.play();
}

void SoundManager::LoadSFX(const std::string& _fileName)
{
	auto* newSound = new sf::SoundBuffer();
	newSound->loadFromFile("Resources/Sounds/" + _fileName + ".wav");
	m_sfxBuffer.insert(std::pair<std::string, sf::SoundBuffer*>(_fileName, newSound));
}
