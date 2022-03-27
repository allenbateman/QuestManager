#include "GuiManager.h"
#include "App.h"
#include "Textures.h"
#include "ModuleFonts.h"
#include "Window.h"
#include "Render.h"
#include "Audio.h"


GuiManager::GuiManager(bool isActive) :Module(isActive)
{
	name.Create("guiManager");
}

GuiManager::~GuiManager() {}

bool GuiManager::Start()
{

	UItexture = app->tex->Load("Assets/Spritesx16/GUI.png");
	UItexture2 = app->tex->Load("Assets/Spritesx16/GUI2.png");

	app->audio->LoadFx("Assets/audio/fx/buttonFocus.wav");
	app->audio->LoadFx("Assets/audio/fx/buttonPressed.wav");
	Debug = false;


	return true;
}


bool GuiManager::Update(float dt)
{	
	if (app->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
		Debug = !Debug;

	accumulatedTime += dt;
	if (accumulatedTime >= updateMsCycle) doLogic = true;


	UpdateAll(dt,doLogic);

	if (doLogic == true)
	{
		accumulatedTime = 0.0f;
		doLogic = false;
	}
	
	return true;
}

bool GuiManager::UpdateAll(float dt, bool doLogic) {

	if (doLogic) {

		ListItem<GuiPanel*>* panel = panels.start;

		while (panel != nullptr && panel->data->Active)
		{
			panel->data->Update(dt,doLogic);
			panel = panel->next;
		}

	}
	return true; 

}

bool GuiManager::PostUpdate() {

	ListItem<GuiPanel*>* panel = panels.start;

	while (panel != nullptr && panel->data->Active)
	{
		panel->data->Draw();
		panel = panel->next;
	}

	return true;

}

bool GuiManager::CleanUp()
{
	ListItem<GuiPanel*>* panel = panels.start;

	while (panel != nullptr)
	{
		panel->data->CleanUp();
		panel = panel->next;
	}

	panels.clear();

	UItexture = nullptr;
	UItexture2 = nullptr;

	return true;
}






