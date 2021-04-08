# GenevaEngine
A custom C++ game engine developed by Joe Goldman

## General info
GenevaEngine was created for my own learning and fun. The goal is to create an engine that leverages [Box2D](https://box2d.org/) physics to create games with unique mechanical constructions at the core of the gameplay. Intially my goal was to recreate my [Unreal4 Dueling Game](https://www.joecgo.com/ue4-dueling-game) with 2D soft-bodies made from springs and joints. I am also inspired by the Theo Jensen machine from the Box2D testbed.
	
## Technologies
Project is created with:
* [OpenGL](https://www.opengl.org/)
* [Box2D](https://box2d.org/)

## Code Overview
The engine is still a work in progress, but here is an overview of what I have implemented so far.

#### Table of Contents  
[Game Loop](#game-loop)  

### Game Loop
This is the main game loop with a fixed time-step for physics.
The basic execution order is: Input -> Physics -> Gameplay -> Render 

Core/GameSession.cpp
```cpp
void GameSession::GameLoop()
{
	// initialize time variables
	float dt = 0.01f;
	double currentTime = Time();
	double accumulator = 0.0;

	while (!WindowIsClosed())
	{
		// time calculations
		double newTime = Time();
		FrameTime = newTime - currentTime;
		if (FrameTime > 0.25)
			FrameTime = 0.25;
		currentTime = newTime;
		accumulator += FrameTime;

		//// -----------------------------------------------------
		/// Game Loop Execution
		// -------------------------------------------------------

		m_input->Update(FrameTime); 			// Input

		// fixed update loop
		while (accumulator >= dt)
		{
			m_physics->Update(dt);			// Physics (fixed update)
			for (Entity* entity : m_entities)	// Gameplay Entities
				entity->FixedUpdate(dt);

			accumulator -= dt;
		}

		const double alpha = accumulator / dt;
		for (Entity* entity : m_entities)		// Gameplay Entities
			entity->Update(FrameTime);
		m_graphics->Update(FrameTime); 			// Render
		while (Paused) { newTime = Time(); };		// Pausing

		//// -----------------------------------------------------
		/// Game Loop Execution
		// -------------------------------------------------------

		currentTime = newTime;
	}

	End();
}
```
