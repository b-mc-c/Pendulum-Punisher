//#include "stdafx.h"
//
//#ifdef _DEBUG
//#pragma comment(lib,"sfml-graphics-d.lib")
//#pragma comment(lib,"sfml-audio-d.lib")
//#pragma comment(lib,"sfml-system-d.lib")
//#pragma comment(lib,"sfml-window-d.lib")
//#pragma comment(lib,"sfml-network-d.lib")
//#else
//#pragma comment(lib,"sfml-graphics.lib")
//#pragma comment(lib,"sfml-audio.lib")
//#pragma comment(lib,"sfml-system.lib")
//#pragma comment(lib,"sfml-window.lib")
//#pragma comment(lib,"sfml-network.lib")
//#endif
//#pragma comment(lib,"opengl32.lib")
//#pragma comment(lib,"glu32.lib")
//#include "SFML/Graphics.hpp"
//#include "SFML/OpenGL.hpp"
//
//#pragma comment(lib,"fmodex_vc.lib")
//#include "fmod.hpp"
//#include "fmod_errors.h"
//#include <iostream> 
//#include <stdlib.h>
//#include <time.h>
//#include "SoundManager.h"
//
//using namespace std;
////std::vector<FMOD::Sound *> SoundManager::sounds(0);
////std::vector<FMOD::Channel *> SoundManager::channels(0);//ohhhh made so nicely
//
//
//SoundManager::SoundManager()
//{
//
//}
//void SoundManager::init()
//{
//	result = FMOD::System_Create(&FMODsys);
//	result = FMODsys->init(100, FMOD_INIT_NORMAL, 0);
//}
//void SoundManager::loadSound()
//{
//	FMOD::Sound *sound;
//	FMOD::Sound *sound2;
//	sounds.push_back(sound);
//	sounds.push_back(sound2);
//
//	result = FMODsys->createSound("song.mp3" ,FMOD_DEFAULT, 0, &sounds[0]);
//	result2 = FMODsys->createSound("jump.wav" ,FMOD_DEFAULT, 0, &sounds[1]);
//	if (result != FMOD_OK)
//	{
//		std::cout << "FMOD error! (%d) %s\n" << result;
//		exit(-1);
//	}
//	cout << "sound loading" << endl ;
//	FMOD::Channel *channel;
//	FMOD::Channel *channel2;
//	channels.push_back(channel);
//	channels.push_back(channel2);
//	channels[0]->setVolume(0.5f);// Set the volume while it is paused.
//	channels[1]->setVolume(0.1f);
//	
//}
//void SoundManager::playSound(int i)
//{
//	//for (int i = 0; i < channels.size(); i++)
//	//{
//		//channels[i]->setPaused(false);
//		channels[i]->stop();
//		FMODsys->playSound(FMOD_CHANNEL_FREE, sounds[i], true, &channels[i]);
//		//FMODsys->playSound(FMOD_CHANNEL_FREE, sounds[i], true, &channels[i]);
//				
//		cout << "sound played" << endl ;
//		if ( i == 1)
//		{
//			channels[i]->setVolume(0.9f);
//		}
//		else
//		{
//			channels[i]->setVolume(0.1f);
//		}
//		
//       channels[i]->setPaused(false);
//	   //channels[1]->setPaused(false);
//			//channels[i]->setVolume(0.5f);// Set the volume while it is paused.
//	   
//	//}
//	
//}
//void SoundManager::stopSound(int i)
//{
//	
//	//channels[0]->setPaused(true);
//	channels[0]->stop();
//}
//
