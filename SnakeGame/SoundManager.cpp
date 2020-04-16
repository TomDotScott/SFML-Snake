#include "SoundManager.h"

SoundManager::SoundManager()
{
	LoadSFX("sfx_food_special");
	LoadSFX("sfx_food_standard");
	LoadSFX("sfx_gobble_on");
	LoadSFX("sfx_gobble_off");
	LoadSFX("sfx_menu_move");
	LoadSFX("sfx_menu_pause");
	LoadSFX("sfx_menu_select");
	LoadSFX("sfx_snake_death");
	LoadSFX("sfx_gobble_eat");
	LoadSFX("sfx_game_lose");
	LoadSFX("sfx_game_win");
	LoadMusic("music_game");
}

void SoundManager::PlaySFX(const std::string& _sfxName)
{
	m_sfx.setBuffer(m_sfxBuffer.at(_sfxName));
	m_sfx.play();
}

void SoundManager::PlayMusic(const std::string& _musicName)
{
	m_music.setBuffer(m_musicBuffer.at(_musicName));
	m_music.play();
}

void SoundManager::StopMusic()
{
	m_music.stop();
}

void SoundManager::LoadSFX(const std::string& _fileName)
{
	auto newSound{ sf::SoundBuffer() };
	newSound.loadFromFile("Resources/Sounds/" + _fileName + ".flac");
	m_sfxBuffer.insert(std::pair<std::string, sf::SoundBuffer>(_fileName, newSound));
}

void SoundManager::LoadMusic(const std::string& _fileName)
{
	auto newSound{ sf::SoundBuffer() };
	newSound.loadFromFile("Resources/Sounds/" + _fileName + ".flac");
	m_musicBuffer.insert(std::pair<std::string, sf::SoundBuffer>(_fileName, newSound));
}
