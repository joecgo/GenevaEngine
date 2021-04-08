<img align="left" width="205" height="164" src="http://github.com/joecgo/GenevaEngine/blob/main/Documentation/icons/GenevaLogo_Logo.jpg?raw=true" alt="Geneva Engine Logo">

# Geneva Engine

A custom C++ game engine developed by Joe Goldman

## General info
Geneva Engine was created for my own learning and fun. The goal is to create an engine that leverages [Box2D](https://box2d.org/) physics to create games with unique mechanical constructions at the core of the gameplay. Intially my goal was to recreate my [Unreal Engine Dueling Game](https://www.joecgo.com/ue4-dueling-game) with 2D soft-bodies made from springs and joints. I am also inspired by the Theo Jensen machine from the Box2D testbed.
	
## Technologies
Project is created with:
* [OpenGL](https://www.opengl.org/)
* [Box2D](https://box2d.org/)

## Code Overview
The engine is still a work in progress, but here is an overview of some of the important components I have implemented so far.

#### Table of Contents  
* [Game Loop](#game-loop) 
* [Entity](#entity)
* [Construct](#construct) 
* more to come soon...

### Game Loop
This is the main game loop with a fixed time-step for physics. Based on code from [Fix Your Timestep! by Glenn Fiedler](https://gafferongames.com/post/fix_your_timestep/). 

The basic execution order is: **Input** -> **Physics** -> **Gameplay** -> **Render** 

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

### Entity
The Entity is the core gameplay object. It can be Spawned and Rendered. It also owns a potentially complex composite of Box2D objects that I call a [Construct](#construct).
Incoming input commands are passed along by the Entity to the Construct so that the construct can act upon those commands with it's own unique set of behaviors.

Core/Entity.hpp
```cpp
class Entity
{
public:
	// Attributes
	const int ID;					// unique ID
	std::string Name;				// A recognizable name for debugging

	// Constructor
	Entity(GameSession* gs, std::string name = "none");

	// Public methods
	void Spawn();					// puts this instance into the game
	float FrameTime();				// Dt since last frame was rendered
	void Notify(const Command* command);		// Notify Construct of incoming commands
	void AddConstruct(Construct* Construct);	// Add composite of box2d objects and properties
	Construct* GetConstruct();			// Get construct (box2d composite)
	void SetRenderColor(int colorID);		// Set base color for rendering (from palette ID)
	void SetRenderColor(Color color);		// Set base color for rendering
	Color GetRenderColor() const;			// Get base color for rendering

private:
	// increments on entity construction to create a unique id
	static int m_entityCount;

	// object references
	GameSession* m_gameSession = nullptr;
	Construct* m_construct = nullptr;

	// base color for rendering
	Color m_render_color;

	//  Game loop (only called by GameSession)
	void Start();					// called once before first update
	void FixedUpdate(double alpha);			// called on fixed physics time-steps
	void Update(double dt);				// called on every rendered frame
	void End();					// called once after last update
	friend class GameSession;
};
```

### Construct
This is where the fun starts. This is used as a base class for any type of physical construct - Anything from a wiggly soft-body to a complex Theo Jensen inspired machine. The implementation of the **Create** method gives the Construct its unique form. The **Nofity** method is implemented to allow Player or AI input to change the construct's behavior.

The Construct acts as a component of the [Entity](#entity). All commands come through the Entity's **Notify** method first, and the Entity will call **Create** in it's own **Spawn** method. The **Start**, **End**, **Update**, and **FixedUpdate** methods are all called within the Entity's own methods of the same name.

 Constructs/Construct.hpp
```cpp
class Construct
{
public:
	Construct(b2World* world);
	
	void SetWorld(b2World* world);
	b2World* GetWorld();
	
	// return a list of body render data for rendering all the verts in graphics system
	std::list<BodyRenderData>* GetConstructRenderData();

protected:
	// current state this object is not Created twice
	ExistanceState m_state = ExistanceState::Standby;
	
	// reference to b2World object
	b2World* m_world = nullptr;
	
	// collection of data for graphics to use for rendering
	std::list<BodyRenderData> m_constructRenderData;

	// private methods
	void SafeCreate();					// does a safety check then calls Create()
	virtual void Notify(const Command* command) = 0;
	virtual void Create() = 0;
	virtual void Start() = 0;				// called once before first update
	virtual void FixedUpdate(double alpha) = 0;		// called on fixed physics time-steps
	virtual void Update(double dt) = 0;			// called on every rendered frame
	virtual void End() = 0;					// called once after last update
	friend class Entity;
};
```

more to come...
