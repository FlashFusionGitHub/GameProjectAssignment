#pragma once
#include "Matrix3.h"
#include <vector>
#include "Application2D.h"
#include "Renderer2D.h"

class SceneObject
{
public:
	SceneObject() : m_parent(nullptr) {}

	virtual  ~SceneObject() {
		for (auto child : m_children)
			delete child;
	}

	void addChild(SceneObject* child) {
		if (child->m_parent == nullptr) {
			child->m_parent = this;
			m_children.push_back(child);
		}
	}

	Matrix3 getLocalTransform()
	{
		return m_localTransform;
	}

	Matrix3 getGlobalTransform()
	{
		return m_globalTransform;
	}


	//Rotate Function
	void rotate(float angle)
	{
		//creating an identity matrix
		Matrix3 mR;
		//modifying the identity martix with setRotateZ and parsing is the rotation amount
		mR.setRotateZ(angle);
		//multiplying the tranks localtransform with the rotated matrix
		m_localTransform = m_localTransform * mR;
		//updating the tanks global transform to apply the rotation
		updateGlobalTransform();
	}

	//setting a scene objects spawn point
	void setSceneObjectPosition(float x, float y)
	{
		Matrix3 t = getLocalTransform();
		t[2][0] = x, t[2][1] = y;
		setLocalTransform(t);
	}

	void setLocalTransform(Matrix3 lt)
	{
		m_localTransform = lt;
		updateGlobalTransform();
	}

	void setGlobalTransform(Matrix3 gt)
	{
		m_globalTransform = gt;
		updateGlobalTransform();
	}

	//reverse a 2D objects direction, by rotating it
	void reverse()
	{
		Matrix3 m3a;
		m3a.setRotateZ(3.14f * 90);
		setLocalTransform(getLocalTransform() * m3a);
	}

	void updateGlobalTransform()
	{
		if (m_parent != nullptr)
			m_globalTransform = m_parent->m_globalTransform * m_localTransform;
		else
			m_globalTransform = m_localTransform;
		for (auto child : m_children)
			child->updateGlobalTransform();
	}

	virtual void update(float deltaTime) {
		for (auto child : m_children)
			child->update(deltaTime);
	}

	virtual void draw(aie::Renderer2D* renderer) {
		for (auto child : m_children)
			child->draw(renderer);
	}

protected:

	Matrix3 m_globalTransform;
	Matrix3 m_localTransform;

	SceneObject* m_parent;
	std::vector<SceneObject*> m_children;
};

