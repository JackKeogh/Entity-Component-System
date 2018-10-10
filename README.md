# Entity-Component-System

## Description
Source code for an Entity Component System Library.

## Classes
### Component Class
An abstract class that creates a blueprint for future components to inherit from.

## Catagories
### Groups
- Player
- Enemy
- NPC
- Item
- Door
- Player Bullet
- Enemy Bullet
- Breakable
- Tile

### Layers
- Background
- Middleground
- Foreground

## Functions
### Component Class
#### Initialiser
virtual void Init()<br />
A virtual function that will be used by child classes to initialise them.

#### Update
virtual void Update()<br />
A virtual function that will be used by child classes to update the component.

#### Render
virtual void Render()<br />
A virtual function that will be used by child classes to render the component.

### Entity Class
#### Constructor
Entity(EntityManager& Manager)<br />
The default constructor class for an Entity. Requires a reference to an entity manager.

#### Update
void Update()<br />
This method will be used to call the update function for all the entity's components.

#### Render
void Render()<br />
This method will be used to call the render function for all the entity's components.

#### isActive
bool isActive()<br />
This method returns a bool value that determines if the entity is active or not.

#### setActive
void setActive(bool set)<br />
This method sets the entity's active bool variable to the parameter that's passed in.