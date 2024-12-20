#pragma once

#include <vector>

#include "Transform.h"
#include "components/Component.h"

class RenderingEngine;

class Node {

public:

	Node();
	virtual ~Node() {};

	void addChild(Node* child);
	void addComponent(Component* component);

	void input(float delta);
	void update(float delta);
	void render(RenderingEngine* renderingEngine);

	void addToRenderingEngine(RenderingEngine* renderingEngine);

	Transform& getTransform();
	Node* getParent();
	std::vector<Node*> getChildren();

	void setParent(Node* parent);

    //Get Component by type
    template <typename T>
    T* getComponent()
    {
        for (auto component : m_components)
        {
            if (T* t = dynamic_cast<T*>(component))
            {
                return t;
            }
        }
        return nullptr;
    }

private:
	Node* m_parent;
	std::vector<Node*> m_children;
	std::vector<Component*> m_components;
	Transform m_transform;

};