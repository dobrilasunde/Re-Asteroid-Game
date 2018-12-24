#pragma once
#include <SDL_scancode.h>
#include <SDL_gamecontroller.h>
#include <SDL_mouse.h>
#include "Math.hpp"

enum ButtonState
{
	ENone,
	EPressed,
	EReleased,
	EHeld
};

class KeyboardState
{
public:
	friend class InputSystem;
	bool GetKeyValue(SDL_Scancode keyCode) const;
	ButtonState GetKeyState(SDL_Scancode keyCode) const;
private:
	const Uint8* mCurrState;
	Uint8 mPrevState[SDL_NUM_SCANCODES];
};

class MouseState
{
public:
	friend class InputSystem;
	const Vector2& GetPosition() const { return mMousePos; }
	const Vector2& GetScrollWheel() const { return mScrollWheel; }
	bool IsRelative() const { return mIsRelative; }
	bool GetButtonValue(int button) const;
	ButtonState GetButtonState(int button) const;
private:
	Vector2 mMousePos;
	Vector2 mScrollWheel;
	Uint32 mCurrButtons;
	Uint32 mPrevButtons;
	bool mIsRelative;
};

class ControllerState
{
public:
	friend class InputSystem;
	bool GetButtonValue(SDL_GameControllerButton button) const;
	ButtonState GetButtonState(SDL_GameControllerButton button) const;
	const Vector2& GetLeftStick() const { return mLeftStick; }
	const Vector2& GetRightStick() const { return mRightStick; }
	float GetLeftTrigger() const { return mLeftTrigger; }
	float GetRightTrigger() const { return mRightTrigger; }

	bool GetIsConnected() const { return mIsConnected; }
private:
	Uint8 mCurrButtons[SDL_CONTROLLER_BUTTON_MAX];
	Uint8 mPrevButtons[SDL_CONTROLLER_BUTTON_MAX];
	Vector2 mLeftStick;
	Vector2 mRightStick;
	float mLeftTrigger;
	float mRightTrigger;
	bool mIsConnected;
};

struct InputState
{
	KeyboardState Keyboard;
	MouseState Mouse;
	ControllerState Controller;
};

class InputSystem
{
public:
	bool Initialize();
	void Shutdown();

	void PrepareForUpdate();
	void Update();
	void ProcessEvent(union SDL_Event& event);

	const InputState& GetState() const { return mState; }

	void SetRelativeMouseMode(bool value);
private:
	InputState mState;
	SDL_GameController* mController;
	float Filter1D(int input);
	Vector2 Filter2D(int inputX, int inputY);
};