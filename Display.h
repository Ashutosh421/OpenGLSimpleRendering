#pragma once
#include <iostream>
#include <sdl2\SDL.h>
#include <glew\glew.h>

class Display
{
public:
	Display(int width, int height, const std::string title);
	void Clear(float r ,float b ,float g ,float a);
	void Update();
	virtual ~Display();	
	bool IsClosed();

private:
	SDL_Window* m_window;
	SDL_GLContext m_glContext;	

	bool isClosed;
};

