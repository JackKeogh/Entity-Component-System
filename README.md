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

#### hasGroup
bool hasGroup(Group group)<br />
This method checks if the entity is apart of a specific group.

#### hasLayer
bool hasLayer(Layer layer)<br />
This method checks if the entity is apart of a specific layer.

#### addGroup
void addGroup(Group group)<br />
This method assigns the entity a particular group to be apart of.

#### addLayer
void addLayer(Layer layer)<br />
This method assigns the entity a particular layer to be apart of.

#### delGroup
void delGroup(Group group)<br />
This method removes the entity from a particular group.

#### delLayer
void delLayer(Layer layer)<br />
This method removes the entity from a particular layer.