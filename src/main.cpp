#include "Engine.cpp"
#include "Graphics.cpp"
#include "UI.cpp"
#include "Transform.cpp"
#include "Controller.cpp"
#include "Physics.cpp"
#include "Time.cpp"
#include "Log.cpp"
#include "Audio.cpp"
#include "Input.cpp"
#include "GameState.cpp"
#include "Debug.cpp"
#include <iostream>

class MyState : public Aspen::GameState::GameState
{
public:
    MyState(Aspen::Object::Object *parent = nullptr, std::string name = "My State")
      : Aspen::GameState::GameState(parent, name)
    {
        // Create a new child
        AddChild(
            // The child is a new rectangle
            new Aspen::Graphics::Rectangle(
                // x = 0, y = 0, width = 32, height = 32
                SDL_Rect({0, 0, 32, 32}),
                // It's black and filled
                Aspen::Graphics::Colors::BLACK, true,
                // this is its parent and its name is "Rectangle" (this can be omitted)
                this, "Rectangle"
                )
            );
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
    int AnimationNumber = 1;
    
    if (Aspen::Input::KeyPressed(SDLK_w))
    {
      y = -30;
    }
    else if (GetTransform()->GetYPosition() > 642)
    {
      GetTransform()->SetYPosition(642);
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
    else if (GetTransform()->GetXPosition() > 1250)
    {
    GetTransform()->SetXPosition(1250);
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

class MainMenu : public GameState
{
  Aspen::Graphics::UI::Text *title;
  Player *player;

public:
    MainMenu(Object *parent = nullptr, std::string name = "MainMenu") : GameState(parent, name)
    {
      //Text/physics
      title = new Aspen::Graphics::UI::Text("Super Smash Bruhs", "default", 64, this, "Title");
      AddChild(title);
      title->GetTransform()->SetPosition(100, 100);
      title->GetTransform()->SetRotation(0.0f);
      title->GetTransform()->SetScale(1, 1);
      title->CreateChild<Aspen::Physics::Rigidbody>();

      //player1 animation
      player = new Player(this, "Player");
      player->GetTransform()->SetPosition(200, 200);
      AddChild(player);
    }
};

int main(int argc, char **argv)
{
  Aspen::Engine::Engine engine(Aspen::Engine::START_FLAGS::ALL ^ (
    Aspen::Engine::START_FLAGS::CREATE_GRAPHICS | 
    Aspen::Engine::START_FLAGS::CREATE_GRAPHICS_DEBUGGER | 
    Aspen::Engine::START_FLAGS::CREATE_GRAPHICS_FONTCACHE
  ));

  engine.FindChildOfType<Aspen::GameState::GameStateManager>()->LoadState<MyState>(true);
  
  engine.FindChildOfType<Aspen::Physics::Physics>()->SetGravityStrength(1);
  engine.FindChildOfType<Aspen::Physics::Physics>()->SetDrag(0.1);
  engine.FindChildOfType<Aspen::Time::Time>()->TargetFramerate(60);
  engine.FindChildOfType<Aspen::Graphics::Graphics>()->FindChildOfType<Aspen::Graphics::FontCache>()->LoadFont("resources/ABeeZee-Regular.ttf", "default");

  engine.FindChildOfType<GameStateManager>()->LoadState<MainMenu>(true);
  while (engine)
    engine();
  return 0;
}
