# Entity-Component-System

## Description
Source code for an Entity Component System Library.

## Classes
### Component Class
An abstract class that creates a blueprint for future components to inherit from.

### Entity Class
A class that is built to manage individual component objects. Components are able to be added,
removed, updated and rendered using this class. Entities can be grouped by layers and by groups.

### Entity Manager
A class to handle multiple entities. Entities are able to be updated, rendered, added and removed.
A vector of entities can be accessed as well as the specific groups and layers they are in.

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

#### addComponent
T& addComponent(TARGS&&... args)<br />
This method adds a component to the Entity, it takes in multiple parameters to create
the component and then returns a reference to the new component.

#### getComponent
T& getComponent()<br />
This method returns a reference to a particular component.

#### hasComponent
bool hasComponent() const<br />
This method checks that an Entity has a particular component and returns a bool statement.

### Entity Manager Class
#### Constructor
EntityManager()<br />
The default constructor for the Entity Manager class. It initialises a vector of entities.

#### Update
void Update()<br />
This method is used to update each entity in the vector of entities.

#### Render
void Render()<br />
This method is used to render each entity in the vector of entities.

#### Refresh
void Refresh() <br />
This method is used to refresh the Entity Manager. It removes inactive entities from the layer and group
groups as well as the vector of entities.