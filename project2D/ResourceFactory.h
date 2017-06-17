#pragma once
#include <memory>
#include "DynamicArray.h"
#include <vector>
#include "Bullet.h"

class ResourceFactory
{
public:
	ResourceFactory() {}
	~ResourceFactory() {}

	void addPrototype(std::shared_ptr<IPrototype> prototype) {
		m_prototypes.push_back(prototype);
	}

	std::shared_ptr<IPrototype> create(const char* name) {
		for (std::shared_ptr<IPrototype> proto : m_prototypes)
		{
			if (proto->getName().compare(name) == 0)
			{
				return proto->clone();
			}
		}
		return nullptr;
	}

private:
	DynamicArray<std::shared_ptr<IPrototype>> m_prototypes;
};

