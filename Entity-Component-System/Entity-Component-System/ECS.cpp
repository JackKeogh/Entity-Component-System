#include "ECS.h"

void jk::Entity::addGroup(Group group)
{
	m_groupBitSet[group] = true;
	m_manager.addToGroup(this, group);
}

void jk::Entity::addLayer(Layer layer)
{
	m_layerBitSet[layer] = true;
	m_manager.addToLayer(this, layer);
}
