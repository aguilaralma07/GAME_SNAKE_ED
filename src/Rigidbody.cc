#include "Rigidbody.hh"

#include<iostream>
Rigidbody::Rigidbody(b2World*& world, b2BodyType bodyType, b2Vec2* position, 
float boxWidth, float boxHeight, float density, float friction, float restitution)
{
    this->world = world;
    bodyDef = new b2BodyDef();
    bodyDef->type = bodyType;
    bodyDef->position = *position;

    body = world->CreateBody(bodyDef);
    polygonShape = new b2PolygonShape();
    polygonShape->SetAsBox(boxWidth, boxHeight); 

    fixtureDef = new b2FixtureDef();
    fixtureDef->shape = polygonShape;
    fixtureDef->density = density; 
    fixtureDef->friction = friction;
    fixtureDef->restitution = restitution; 

    fixture = body->CreateFixture(fixtureDef);
}

Rigidbody::~Rigidbody()
{
    fixture->SetSensor(true);
    body->SetUserData(nullptr);
}

void Rigidbody::SetSensor(bool status)
{
    fixture->SetSensor(status);
}

b2Body* Rigidbody::GetBody() const
{
    return body;
}

void Rigidbody::SetUserData(void* userData)
{
    body->SetUserData(userData);
}

