#include <iostream>
#include "Constants.h"
#include "Game.h"

Game::Game()
{
	this->isRunning = false;
}

Game::~Game()
{
}

bool Game::IsRunning() const
{
	return this->isRunning;
}

float projectilePosX = 0.0f;
float projectilePosY = 0.0f;
float projectileVelX = 0.01f;
float projectileVelY = 0.01f;

void Game::Initialize(int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cerr << "Error Initializing SDL\n";
		return;
	}

	this->window = SDL_CreateWindow(
		"My Game",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_BORDERLESS);
	if (!this->window)
	{
		std::cerr << "Error creating SDL window\n";
		return;
	}

	this->renderer = SDL_CreateRenderer(this->window, -1, 0);
	if (!this->renderer)
	{
		std::cerr << "Error creating SDL Renderer\n";
		return;
	}

	isRunning = true;
	return;
}

void Game::ProcessInput()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
			isRunning = false;
		break;
	default:
		break;
	}
}

void Game::Update()
{
	projectilePosX += projectileVelX;
	projectilePosY += projectileVelY;
}

void Game::Render()
{
	SDL_SetRenderDrawColor(
		this->renderer,
		21, 21, 21, 255);

	SDL_RenderClear(this->renderer);

	SDL_Rect projectile{
		(int)projectilePosX,
		(int)projectilePosY,
		10,
		10};
	SDL_SetRenderDrawColor(
		this->renderer,
		255, 255, 255, 255);
	SDL_RenderFillRect(this->renderer, &projectile);

	SDL_RenderPresent(this->renderer);
}

void Game::Destroy()
{
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}