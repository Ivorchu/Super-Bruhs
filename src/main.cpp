#include "Engine.hpp"
#include "Graphics.hpp"
#include "UI.hpp"
#include "Transform.hpp"
#include "Controller.hpp"
#include "Physics.hpp"
#include "Time.hpp"
#include "Log.hpp"
#include "Audio.hpp"
#include "Input.hpp"
#include "GameState.hpp"
#include "Debug.hpp"
#include <iostream>
#include <algorithm>

class Button : public Aspen::Graphics::Rectangle
{
public:
    Button(Aspen::Object::Object *parent = nullptr, std::string name = "Button")
      : Aspen::Graphics::Rectangle(SDL_Rect({0, 0, 512, 64}), Aspen::Graphics::Colors::WHITE, true, parent, name)
    {
      CreateChild<Aspen::Physics::AABBCollider>()->SetSize(512, 64);
    }

    void OnMouseClick()
    {
      Aspen::Log::Debug("I've been clicked");
      if (Aspen::Input::GetMouse().left.pressed)
        Aspen::Engine::Engine::Get()->FindChildOfType<Aspen::GameState::GameStateManager>()->SetCurrentState("Level 1 State");
    }
};

class Grass : public Aspen::Graphics::Sprite
{
  public:
  Grass(Aspen::Object::Object *parent = nullptr, std::string name = "Grass") : Aspen::Graphics::Sprite ("./resources/Grass.png" ,parent, name)
  {
    GetTransform()->SetPosition(500,500);
  }
};

class Player : public Aspen::Object::Object
{
  Aspen::Graphics::Animation *animation1;
  Aspen::Graphics::Animation *animation2;
  Aspen::Graphics::Animation *animation3;
  Aspen::Graphics::Animation *animation4;
  Aspen::Graphics::Animation *animation5;
  Aspen::Graphics::Animation *animation6;
  int AnimationNumber = 1;

public:
  Player(Object *parent = nullptr, std::string name = "Player") : Aspen::Object::Object(parent, name)
  {
    //int Health = 100;
    //int Attack = 10;
    animation1 = new Aspen::Graphics::Animation(
      new Aspen::Graphics::UniformSpritesheet("./resources/Fortnite.png", 128, 128, 2, nullptr, "FortniteSpiritsheet"), 
      1.0f / 2.0f, parent, name);
    animation2 = new Aspen::Graphics::Animation(
      new Aspen::Graphics::UniformSpritesheet("./resources/Fortnite left.png", 128, 128, 2, nullptr, "FortniteSpiritsheet"), 
      1.0f / 2.0f, parent, name);
    animation3 = new Aspen::Graphics::Animation(
      new Aspen::Graphics::UniformSpritesheet("./resources/Fortnite crouch.png", 128, 128, 1, nullptr, "FortniteSpiritsheet"), 
      1.0f / 1.0f, parent, name);
    animation4 = new Aspen::Graphics::Animation(
      new Aspen::Graphics::UniformSpritesheet("./resources/Fortnite left crouch.png", 128, 128, 1, nullptr, "FortniteSpiritsheet"), 
      1.0f / 1.0f, parent, name);
    animation5 = new Aspen::Graphics::Animation(
      new Aspen::Graphics::UniformSpritesheet("./resources/Fortnite punch.png", 128, 128, 1, nullptr, "FortniteSpiritsheet"), 
      1.0f / 1.0f, parent, name);
    animation6 = new Aspen::Graphics::Animation(
      new Aspen::Graphics::UniformSpritesheet("./resources/Fortnite left punch.png", 128, 128, 1, nullptr, "FortniteSpiritsheet"), 
      1.0f / 1.0f, parent, name);
    AddChild(animation1);
    AddChild(animation2);
    AddChild(animation3);
    AddChild(animation4);
    AddChild(animation5);
    AddChild(animation6);
    CreateChild<Aspen::Transform::Transform>();
    CreateChild<Aspen::Physics::AABBCollider>()->SetSize(64, 64);
    CreateChild<Aspen::Physics::Rigidbody>();
    GetTransform()->SetPosition(100, 100);
    animation2->Deactivate();
    animation3->Deactivate();
    animation4->Deactivate();
    animation5->Deactivate();
    animation6->Deactivate();
  }

  void OnCollision(Aspen::Physics::Collision c)
  {
    // Aspen::Log::Debug("I have been collided!");
  }

  void OnUpdate()
  {
    double x = GetRigidbody()->GetVelocityX();
    double y = GetRigidbody()->GetVelocityY();

    if (Aspen::Input::KeyPressed(SDLK_w))
    {
      y = -30;
    }
    else if (GetTransform()->GetYPosition() > 928)
    {
      GetTransform()->SetYPosition(928);
      y = 0;
    }
    if (Aspen::Input::KeyHeld(SDLK_a))
    {
      AnimationNumber = 2;
      animation1->Deactivate();
      animation2->Activate();
      animation3->Deactivate();
      animation4->Deactivate();
      animation5->Deactivate();
      animation6->Deactivate();
      x = -5;
    }
    else if (GetTransform()->GetXPosition() > 1900)
    {
    GetTransform()->SetXPosition(1900);
    x = 0;
    }
    if (Aspen::Input::KeyPressed(SDLK_s) && (AnimationNumber == 1 || AnimationNumber == 5))
    {
      AnimationNumber = 3;
      animation1->Deactivate();
      animation2->Deactivate();
      animation3->Activate();
      animation4->Deactivate();
      animation5->Deactivate();
      animation6->Deactivate();
      y = 5;
    }
    else if (Aspen::Input::KeyPressed(SDLK_s) && (AnimationNumber == 2 || AnimationNumber == 6))
    {
      AnimationNumber = 4;
      animation1->Deactivate();
      animation2->Deactivate();
      animation3->Deactivate();
      animation4->Activate();
      animation5->Deactivate();
      animation6->Deactivate();
      y = 5;
    }
    else if (Aspen::Input::KeyReleased(SDLK_s) && (AnimationNumber == 3 || AnimationNumber == 5))
    {
      AnimationNumber = 1;
      animation1->Activate();
      animation2->Deactivate();
      animation3->Deactivate();
      animation4->Deactivate();
      animation5->Deactivate();
      animation6->Deactivate();
    }
    else if (Aspen::Input::KeyReleased(SDLK_s) && (AnimationNumber == 4 || AnimationNumber == 6))
    {
      AnimationNumber = 2;
      animation1->Deactivate();
      animation2->Activate();
      animation3->Deactivate();
      animation4->Deactivate();
      animation5->Deactivate();
      animation6->Deactivate();
    }
    
    if (Aspen::Input::KeyHeld(SDLK_d))
    {
      AnimationNumber = 1;
      animation1->Activate();
      animation2->Deactivate();
      animation3->Deactivate();
      animation4->Deactivate();
      animation5->Deactivate();
      animation6->Deactivate();
      x = 5;
    }
    
    if (Aspen::Input::KeyHeld(SDLK_LCTRL) && (AnimationNumber == 1 || AnimationNumber == 3 ))
    {
      AnimationNumber = 5;
      animation1->Deactivate();
      animation2->Deactivate();
      animation3->Deactivate();
      animation4->Deactivate();
      animation5->Activate();
      animation6->Deactivate();
    }
    else if (Aspen::Input::KeyHeld(SDLK_LCTRL) && (AnimationNumber == 2 || AnimationNumber == 4 ))
    {
      AnimationNumber = 6;
      animation1->Deactivate();
      animation2->Deactivate();
      animation3->Deactivate();
      animation4->Deactivate();
      animation5->Deactivate();
      animation6->Activate();
    }
    else if (Aspen::Input::KeyReleased(SDLK_LCTRL) && (AnimationNumber == 3 || AnimationNumber == 5))
    {
      AnimationNumber = 1;
      animation1->Activate();
      animation2->Deactivate();
      animation3->Deactivate();
      animation4->Deactivate();
      animation5->Deactivate();
      animation6->Deactivate();
    }
    else if (Aspen::Input::KeyReleased(SDLK_LCTRL) && (AnimationNumber == 4 || AnimationNumber == 6))
    {
      AnimationNumber = 2;
      animation1->Deactivate();
      animation2->Activate();
      animation3->Deactivate();
      animation4->Deactivate();
      animation5->Deactivate();
      animation6->Deactivate();
    }
    GetRigidbody()->SetCartesianVelocity(x, y);
  }
};

class MainMenu : public Aspen::GameState::GameState
{
  Player *player;
  Button *Start;
  Aspen::Graphics::UI::Text *startText;

public:
    MainMenu(Object *parent = nullptr, std::string name = "MainMenu") : GameState(parent, name)
    {
      Aspen::Graphics::Sprite *bg = new Aspen::Graphics::Sprite("resources/title screen background.png");
      bg->GetTransform()->SetPosition(1920 / 2, 1080 / 2);
      bg->GetTransform()->SetPosition(1920 / 2, 1080 / 2);
      AddChild(bg);
      //Start Button
      Start = new Button();
      Start->GetTransform()->SetPosition(960, 540);
      AddChild(Start);
      startText = new Aspen::Graphics::UI::Text("Start", "default", 64, this, "Start Text");
      AddChild(startText);
      startText->GetTransform()->SetPosition(960, 540);
    }
};

class L1State : public Aspen::GameState::GameState
{
  //  Aspen::Graphics::Camera *cam;
    Player *player;
    Grass *grass1;
    Grass *grass2;
    Grass *grass3;
    Grass *grass4;
    Grass *grass5;
    Grass *grass6;
    Grass *grass7;
    Grass *grass8;
    Grass *grass9;
    Grass *grass10;
    Grass *grass11;
    Grass *grass12;
    Grass *grass13;
    Grass *grass14;
    Grass *grass15;
    Grass *grass16;
    Grass *grass17;
    Grass *grass18;
    Grass *grass19;
    Grass *grass20;
    Grass *grass21;
public:
  L1State(Aspen::Object::Object *parent = nullptr, std::string name = "Level 1 State")
      : Aspen::GameState::GameState(parent, name)
  {

  grass1 = new Grass();  
  grass2 = new Grass();  
  grass3 = new Grass();  
  grass4 = new Grass();  
  grass5 = new Grass();  
  grass6 = new Grass();  
  grass7 = new Grass();  
  grass8 = new Grass();  
  grass9 = new Grass();  
  grass10 = new Grass();  
  grass11 = new Grass();  
  grass12 = new Grass();
  grass13 = new Grass();
  grass14 = new Grass();
  grass15 = new Grass();
  grass16 = new Grass();
  grass17 = new Grass();
  grass18 = new Grass();
  grass19 = new Grass();
  grass20 = new Grass();
  grass21 = new Grass();
  player = new Player();
  //   cam = CreateChild<Aspen::Graphics::Camera>();
  //   cam->SelectCamera();
     AddChild(player);

  grass1->GetTransform()->SetPosition(45, 1040);
  grass2->GetTransform()->SetPosition(141, 1040);
  grass3->GetTransform()->SetPosition(237, 1040);
  grass4->GetTransform()->SetPosition(333, 1040);
  grass5->GetTransform()->SetPosition(429, 1040);
  grass6->GetTransform()->SetPosition(525, 1040);
  grass7->GetTransform()->SetPosition(621, 1040);
  grass8->GetTransform()->SetPosition(717, 1040);
  grass9->GetTransform()->SetPosition(813, 1040);
  grass10->GetTransform()->SetPosition(909, 1040);
  grass11->GetTransform()->SetPosition(1005, 1040);
  grass12->GetTransform()->SetPosition(1101, 1040);
  grass13->GetTransform()->SetPosition(1197, 1040);
  grass14->GetTransform()->SetPosition(1293, 1040);
  grass15->GetTransform()->SetPosition(1389, 1040);
  grass16->GetTransform()->SetPosition(1485, 1040);
  grass17->GetTransform()->SetPosition(1581, 1040);
  grass18->GetTransform()->SetPosition(1677, 1040);
  grass19->GetTransform()->SetPosition(1773, 1040);
  grass20->GetTransform()->SetPosition(1869, 1040);
  grass21->GetTransform()->SetPosition(1965, 1040);
  
  
  AddChild(grass1);
  AddChild(grass2);
  AddChild(grass3);
  AddChild(grass4);
  AddChild(grass5);
  AddChild(grass6);
  AddChild(grass7);
  AddChild(grass8);
  AddChild(grass9);
  AddChild(grass10);
  AddChild(grass11);
  AddChild(grass12);
  AddChild(grass13);
  AddChild(grass14);
  AddChild(grass15);
  AddChild(grass16);
  AddChild(grass17);
  AddChild(grass18);
  AddChild(grass19);
  AddChild(grass20);
  AddChild(grass21);
  }

  // void OnUpdate()
  // {
  //   float cx = player->GetTransform()->GetXPosition() - Aspen::Graphics::DEFAULT_WINDOW_WIDTH / 2.0f;
  //   float cy = player->GetTransform()->GetYPosition() - Aspen::Graphics::DEFAULT_WINDOW_HEIGHT / 2.0f;
  //   cam->GetTransform()->SetPosition(std::max(std::min(cx, 100.0f), -100.0f), cy);
  // }
};

int main(int argc, char **argv)
{
  Aspen::Engine::Engine engine(Aspen::Engine::START_FLAGS::ALL ^ (
    Aspen::Engine::START_FLAGS::CREATE_GRAPHICS | 
    Aspen::Engine::START_FLAGS::CREATE_GRAPHICS_DEBUGGER | 
    Aspen::Engine::START_FLAGS::CREATE_GRAPHICS_FONTCACHE
  ));

  Aspen::Graphics::Graphics *gfx = new Aspen::Graphics::Graphics(1920, 1080);
  gfx->CreateChild<Aspen::Debug::Debug>();
  gfx->CreateChild<Aspen::Graphics::FontCache>();
  engine.AddChild(gfx);

  engine.FindChildOfType<Aspen::Physics::Physics>()->SetGravityStrength(1);
  engine.FindChildOfType<Aspen::Physics::Physics>()->SetDrag(0.1);
  engine.FindChildOfType<Aspen::Time::Time>()->TargetFramerate(60);
  engine.FindChildOfType<Aspen::Graphics::Graphics>()->FindChildOfType<Aspen::Graphics::FontCache>()->LoadFont("resources/ABeeZee-Regular.ttf", "default");

  engine.FindChildOfType<Aspen::GameState::GameStateManager>()->LoadState<MainMenu>(true);
  engine.FindChildOfType<Aspen::GameState::GameStateManager>()->LoadState<L1State>(false);

  while (engine)
    engine();
  return 0;
}
