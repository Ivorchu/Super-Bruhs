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
      : Aspen::Graphics::Rectangle(SDL_Rect({0, 0, 64, 64}), Aspen::Graphics::Colors::GREEN, true, parent, name)
    {
      CreateChild<Aspen::Physics::AABBCollider>()->SetSize(64, 64);
    }

    void OnMouseClick()
    {
      Aspen::Log::Debug("I've been clicked");
      if (Aspen::Input::GetMouse().left.pressed)
        Aspen::Engine::Engine::Get()->FindChildOfType<Aspen::GameState::GameStateManager>()->SetCurrentState("L1State");
    }
};


// class MainState : public Aspen::GameState::GameState
// {
//   Aspen::Graphics::Rectangle *rect;
// public:
//     MainState(Aspen::Object::Object *parent = nullptr, std::string name = "Main State")
//       : Aspen::GameState::GameState(parent, name)
//     {
//       rect = 
//             // The child is a new rectangle
//             new Aspen::Graphics::Rectangle(
//                 // x = 0, y = 0, width = 32, height = 32
//                 SDL_Rect({0, 0, 32, 32}),
//                 // It's black and filled
//                 Aspen::Graphics::Colors::BLACK, true,
//                 // this is its parent and its name is "Rectangle" (this can be omitted)
//                 this, "Rectangle"
//                 );

//         rect->CreateChild<Aspen::Physics::AABBCollider>()->SetSize(200,50);
//         // Create a new child
//         AddChild(rect);
        
//     }
// };

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
  int velocity Player::GetVelocity();
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
    int AnimationNumber = 1;

    if (Aspen::Input::KeyPressed(SDLK_w))
    {
      y = -30;
    }
    else if (GetTransform()->GetYPosition() > 975)
    {
      GetTransform()->SetYPosition(975);
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
    else if (GetTransform()->GetXPosition() < 30)
    {
    GetTransform()->SetXPosition(30);
    x = 0;
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
    else if (GetTransform()->GetYPosition() < 30)
    {
    GetTransform()->SetYPosition(30);
    y = 0;
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

public:
    MainMenu(Object *parent = nullptr, std::string name = "MainMenu") : GameState(parent, name)
    {
      //player animation
      // player = new Player(this, "Player");
      // player->GetTransform()->SetPosition(200, 200);
      // AddChild(player);

      //Start Button
      Start = new Button(this, "Button");
      Start->GetTransform()->SetPosition(200, 200);
    }
};

class L1State : public Aspen::GameState::GameState
{
    Aspen::Graphics::Camera *cam;
     *obj;

public:
  L1State(Aspen::Object::Object *parent = nullptr, std::string name = "Level 1 State")
      : Aspen::GameState::GameState(parent, name)
  {
    obj = CreateChild<MyObject>();
    cam = CreateChild<Aspen::Graphics::Camera>();
    cam->SelectCamera();
  }

  void OnUpdate()
  {
    float cx = obj->GetTransform()->GetXPosition() - Aspen::Graphics::DEFAULT_WINDOW_WIDTH / 2.0f;
    float cy = obj->GetTransform()->GetYPosition() - Aspen::Graphics::DEFAULT_WINDOW_HEIGHT / 2.0f;
    cam->GetTransform()->SetPosition(std::max(std::min(cx, 100.0f), -100.0f), cy);
    if (Aspen::Input::KeyHeld(SDLK_w))
      obj->GetTransform()->ModifyYPosition(-1);
    if (Aspen::Input::KeyHeld(SDLK_a))
      obj->GetTransform()->ModifyXPosition(-1);
    if (Aspen::Input::KeyHeld(SDLK_s))
      obj->GetTransform()->ModifyXPosition(1);
    if (Aspen::Input::KeyHeld(SDLK_d))
      obj->GetTransform()->ModifyYPosition(1);
  }
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

  engine.FindChildOfType<Aspen::GameState::GameStateManager>()->LoadState<MainMenu>(true);
  engine.FindChildOfType<Aspen::GameState::GameStateManager>()->LoadState<L1State>(false);

  engine.FindChildOfType<Aspen::Physics::Physics>()->SetGravityStrength(1);
  engine.FindChildOfType<Aspen::Physics::Physics>()->SetDrag(0.1);
  engine.FindChildOfType<Aspen::Time::Time>()->TargetFramerate(60);
  engine.FindChildOfType<Aspen::Graphics::Graphics>()->FindChildOfType<Aspen::Graphics::FontCache>()->LoadFont("resources/ABeeZee-Regular.ttf", "default");

  engine.FindChildOfType<Aspen::GameState::GameStateManager>()->LoadState<L1State>(true);
  engine.FindChildOfType<Aspen::GameState::GameStateManager>()->LoadState<MainMenu>(false);

  while (engine)
    engine();
  return 0;
}
