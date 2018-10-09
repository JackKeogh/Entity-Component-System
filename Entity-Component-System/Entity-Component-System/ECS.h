/// <summary>
/// An Entity Component System library to use
/// in future game development projects. Entities 
/// will be able to be grouped in two separate
/// categories.
/// </summary>
/// <date>
/// 09/10/2018
/// </date>
/// <author>
/// Jack Keogh
/// </author>

#pragma once

namespace jk
{
	// Forward declarations
	class Component;
	class Entity;
	class EntityManager;

	/// <summary>
	/// Abstract class for future components to
	/// inherit from.
	/// </summary>
	class Component
	{
	public:
		virtual void Init() {};
		virtual void Update() {};
		virtual void Render() {};

		Entity * m_entity;
	};
}