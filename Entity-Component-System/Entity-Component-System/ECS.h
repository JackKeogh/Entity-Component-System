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

	// Groups
	enum Groups : size_t
	{
		PlayerGroup,
		EnemyGroup,
		NPCGroup,
		ItemGroup,
		DoorGroup,
		PlayerBulletGroup,
		EnemyBulletGroup,
		BreakableGroup,
		TileGroup
	};

	// Layers
	enum Layers : size_t
	{
		Background,
		Middleground,
		Foreground
	};

	// Type Aliases
	using ComponentID = size_t;
	using Group = size_t;
	using Layer = size_t;

	/// <summary>
	/// Assigns a component an ID.
	/// </summary>
	/// <returns>A size_t value.</returns>
	inline ComponentID getComponentTypeID()
	{
		static ComponentID lastID = 0;
		return lastID++;
	}

	/// <summary>
	/// Assigns a type ID.
	/// </summary>
	/// <returns>A size_t value.</returns>
	template <typename T>
	inline ComponentID getComponentTypeID() noexcept
	{
		static typeID = getComponentTypeID();
		return typeID;
	}

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