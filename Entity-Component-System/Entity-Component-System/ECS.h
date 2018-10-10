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
#include <bitset>
#include <array>
#include <vector>

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

	// Defining max limits
	constexpr size_t maxComponents = 32;
	constexpr size_t maxGroups = 32;
	constexpr size_t maxLayers = 32;

	// Bitsets and arrays
	using GroupBitSet = std::bitset<maxGroups>;
	using LayerBitSet = std::bitset<maxLayers>;
	using ComponentBitSet = std::bitset<maxComponents>;
	using ComponentArray = std::array<Component*, maxComponents>;

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

	/// <summary>
	/// An Entity Object that will be able be grouped into
	/// predefined groups and layers. An entity will be made
	/// up of components.
	/// </summary>
	class Entity
	{
	public:
		// Constructors
		Entity(EntityManager & Manager) :
			m_manager(Manager), m_active(true) {};

		// Destructors
		~Entity() {};

		/// <summary>
		/// Used to call the update method for each of
		/// the entity's component.
		/// </summary>
		void Update()
		{
			for (auto& c : m_components)
			{
				c->Update();
			}
		}

		/// <summary>
		/// Used to call the render method for each of
		/// the entity's component.
		/// </summary>
		void Render()
		{
			for (auto& c : m_components)
			{
				c->Render();
			}
		}

		/// <summary>
		/// Returns a bool variable checking if the Entity is active or not.
		/// </summary>
		bool isActive() { return m_active; };

		/// <summary>
		/// Set if the Entity is active or not.
		/// </summary>
		/// <param name="set">A bool variable to set active to.</param>
		void setActive(bool set) { m_active = set; };

		/// <summary>
		/// hasGroup
		/// 
		/// Checks if the entity is apart of a specific group.
		/// </summary>
		/// <param name="group">The group to check.</param>
		/// <returns>A bool value.</returns>
		bool hasGroup(Group group)
		{
			return m_groupBitSet[group];
		}

		/// <summary>
		/// hasLayer
		/// 
		/// Check if the entity is apart of a specific layer.
		/// </summary>
		/// <param name="layer">The layer to check.</param>
		/// <returns>A bool value.</returns>
		bool hasLayer(Layer layer)
		{
			return m_layerBitSet[layer];
		}

		/// <summary>
		/// addGroup
		/// 
		/// Assigns the entity a group to be apart of.
		/// </summary>
		/// <param name="group">The group to be apart of.</param>
		void addGroup(Group group);

		/// <summary>
		/// addLayer
		/// 
		/// Assigns the entity a layer to be apart of.
		/// </summary>
		/// <param name="layer">The layer to be apart of.</param>
		void addLayer(Layer layer);


		/// <summary>
		/// delGroup
		/// 
		/// Removes the entity from a group.
		/// </summary>
		/// <param name="group">The group to be removed from.</param>
		void delGroup(Group group)
		{
			m_groupBitSet[group] = false;
		}

		/// <summary>
		/// delLayer
		/// 
		/// Removes the entity from a layer.
		/// </summary>
		/// <param name="layer">The layer to be removed from.</param>
		void delLayer(Layer layer)
		{
			m_layerBitSet[layer] = false;
		}

	private:
		EntityManager & m_manager;
		bool m_active;
		std::vector<std::unique_ptr<Component>> m_components;
		
		ComponentArray m_componentArray;
		ComponentBitSet m_componentBitSet;
		GroupBitSet m_groupBitSet;
		LayerBitSet m_layerBitSet;
	};
}