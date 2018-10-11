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
		static ComponentID typeID = getComponentTypeID();
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

		/// <summary>
		/// addComponent
		/// 
		/// Adds a component to the Entity accepting multiple arguments.
		/// </summary>
		template <typename T, typename... TARGS>
		T& addComponent(TARGS&&... args)
		{
			T* c(new T(std::forward<TARGS>(args)...));
			c->m_entity = this;

			std::unique_ptr<Component> Uptr{ c };
			m_components.emplace_back(std::move(Uptr));

			m_componentArray[getComponentTypeID<T>()] = c;
			m_componentBitSet[getComponentTypeID<T>()] = true;

			c->Init();
			return *c;
		}

		/// <summary>
		/// Returns a reference to a particular component.
		/// </summary>
		template <typename T>
		T& getComponent()
		{
			auto ptr(m_componentArray[getComponentTypeID<T>()]);
			return *static_cast<T*>(ptr);
		}

		/// <summary>
		/// Checks if an entity has a paticular component.
		/// </summary>
		template <typename T>
		bool hasComponent() const
		{
			return m_componentBitSet[getComponentTypeID<T>()];
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

	/// <summary>
	/// The Entity Manager class will keep track of all entities. It
	/// will group entities together based on groups or layers.
	/// </summary>
	class EntityManager
	{
	public:

		// Constructor
		EntityManager()
		{
			m_entities = std::vector<std::unique_ptr<Entity>>();
		}

		/// <summary>
		/// Used to call the entities update method.
		/// </summary>
		void Update()
		{
			for (auto& e : m_entities)
			{
				e->Update();
			}
		}

		/// <summary>
		/// Used to call the entities render method.
		/// </summary>
		void Render()
		{
			for (auto& e : m_entities)
			{
				e->Render();
			}
		}

		/// <summary>
		/// Used to refresh the entity manager. Removes entities
		/// from the entity list if they are inactive as well as 
		/// removing them from the groups and layers array.
		/// </summary>
		void Refresh()
		{
			for (auto i(0u); i < maxGroups; i++)
			{
				auto& v(m_groupedEntities[i]);

				v.erase(std::remove_if(std::begin(v), std::end(v), [i](Entity * entity)
				{
					return !entity->isActive() || !entity->hasGroup(i);
				}),
					std::end(v));
			}

			for (auto i(0u); i < maxLayers; i++)
			{
				auto& v(m_layeredEntities[i]);

				v.erase(std::remove_if(std::begin(v), std::end(v), [i](Entity * entity)
				{
					return !entity->isActive() || !entity->hasLayer(i);
				}),
					std::end(v));
			}

			m_entities.erase(std::remove_if(std::begin(m_entities), std::end(m_entities),
				[](const std::unique_ptr<Entity>& entity)
			{
				return !entity->isActive();
			}),
				std::end(m_entities));
		}

		/// <summary>
		/// addToGroup
		/// 
		/// Adds entities to a particular group.
		/// </summary>
		/// <param name="entity">The entity to add.</param>
		/// <param name="group">The group to add to.</param>
		void addToGroup(Entity * entity, Group group)
		{
			m_groupedEntities[group].emplace_back(entity);
		}

		/// <summary>
		/// addToLayer
		/// 
		/// Adds entities to a particular layer.
		/// </summary>
		/// <param name="entity">The entity to add.</param>
		/// <param name="layer">The layer to add to.</param>
		void addToLayer(Entity * entity, Layer layer)
		{
			m_layeredEntities[layer].emplace_back(entity);
		}

		/// <summary>
		/// getGroup
		/// 
		/// Gets a particular group of entities.
		/// </summary>
		/// <param name="group">The group to get entities from.</param>
		/// <returns>A vector of entities.</returns>
		std::vector<Entity *>& getGroup(Group group)
		{
			return m_groupedEntities[group];
		}

		/// <summary>
		/// getLayer
		/// 
		/// Gets a particular layer of entities.
		/// </summary>
		/// <param name="layer">The layer to get entities from.</param>
		/// <returns>A vector of entities.</returns>
		std::vector<Entity *>& getLayer(Layer layer)
		{
			return m_layeredEntities[layer];
		}

		/// <summary>
		/// addEntity
		/// 
		/// Creates a new entity and adds it to the Entity Manager's
		/// entity vector.
		/// </summary>
		/// <returns>A reference to the new entity.</returns>
		Entity& addEntity()
		{
			Entity * entity = new Entity(*this);
			std::unique_ptr<Entity> Uptr{ entity };
			m_entities.emplace_back(std::move(Uptr));

			return *entity;
		}

		/// <summary>
		/// getEntities
		/// 
		/// Gets the entity manager's vector of entities.
		/// </summary>
		/// <returns>The vector of entities.</returns>
		std::vector<std::unique_ptr<Entity>> const& getEntities() const
		{
			return m_entities;
		}

	private:
		std::vector<std::unique_ptr<Entity>> m_entities;
		std::array<std::vector<Entity*>, maxGroups> m_groupedEntities;
		std::array<std::vector<Entity*>, maxLayers> m_layeredEntities;
	};
}