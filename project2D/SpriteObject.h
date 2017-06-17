#pragma once
#include "SceneObject.h"
#include "Texture.h"


class SpriteObject : public SceneObject
{
public:
	SpriteObject(aie::Texture* texture) 
		: m_texture(texture) {
	}

	virtual ~SpriteObject() {}

	virtual void draw(aie::Renderer2D* renderer) {

		renderer->drawSpriteTransformed3x3(m_texture, (float*)&m_globalTransform);

		//call base draw
		SceneObject::draw(renderer);
	}

protected:

	aie::Texture* m_texture;
};

