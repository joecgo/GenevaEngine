<img align="left" height="80" src="https://raw.githubusercontent.com/joecgo/GenevaEngine/main/Assets/Logo/GenevaEngineLogo_LargeCropped.jpg?raw=true" alt="Geneva Engine Logo">

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
* [A Simple Construct](#a-simple-construct)


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
	
	// return a vector of body render data for rendering all the verts in graphics system
	std::vector<BodyRenderData>* GetConstructRenderData();

protected:
	// existance state prevents construct from being created twice
	ExistanceState m_state = ExistanceState::Standby;
	
	// reference to b2World object
	b2World* m_world = nullptr;
	
	// collection of data for graphics to use for rendering
	std::vector<BodyRenderData> m_constructRenderData;

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

### A Simple Construct
This is a simple implementation of the [Construct](#construct) base class. The **SingleShape** class is designed to be general enough for any single-bodied Construct. For example, a SingleShape, during its instantiation, can be defined as a circle, a box, or any type of polygon. If you desire multiple bodies as part of a single Construct, a different class of Construct will need to be used.

**SingleShape::Notify** is derived from the base Construct class, and, in this case, implements a finite state machine specific to the SingleShape class.

**SingleShape::Create** is also derived from Construct. FixtureDef, Shape, BodyDef are Box2D objects used to define the parameters of the physical object before it is created. The render data then needs to be organized for the Graphics system to use.

**SingleShape::GetBody** This method provides the Box2D body of the SingleShape. It is used to implement behaviors like movement and jumping. In a more complex Construct, a call like this may not neccessarily make sense because a construct could be made up of many bodies.

 Constructs/SingleShape.cpp
```cpp
void SingleShape::Notify(const Command* command)
{
	if (m_state == nullptr) return;

	State<SingleShape>* next_state = m_state->Notify(this, command);
	if (next_state != nullptr)
	{
		m_state->Exit(this);
		delete m_state;
		next_state->Enter(this);
		m_state = next_state;
	}
}

void SingleShape::Create()
{
	// create body
	m_body = m_world->CreateBody(&BodyDef);
	FixtureDef.shape = &Shape;
	m_body->CreateFixture(&FixtureDef);

	// add body and shape to render data
	BodyRenderData brData;
	brData.Body = m_body;
	brData.Shape = Shape;
	m_constructRenderData.push_back(brData);
}

b2Body* SingleShape::GetBody()
{
	return m_body;
}
```
