# Entity-Component-System

## Description
Source code for an Entity Component System Library.

## Classes
### Component Class
An abstract class that creates a blueprint for future components to inherit from.

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