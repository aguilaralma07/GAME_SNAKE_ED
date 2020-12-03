#include "ContactListener.hh"
#include "GameObject.hh"
#include "Tile.hh"
#include<iostream>
#include<cstring>
#include<algorithm>


ContactListener::ContactListener(Score*& score, std::vector<GameObject*>*& covid)
{
    this->score = score;
    this->covid = covid;
}

ContactListener::~ContactListener()
{
}

int ContactListener::GetSceneIndex() const
{
    return sceneIndex;
}

void ContactListener::BeginContact(b2Contact* contact)
{
    GameObject* bodyDataA = (GameObject*) contact->GetFixtureA()->GetBody()->GetUserData();
    GameObject* bodyDataB = (GameObject*) contact->GetFixtureB()->GetBody()->GetUserData();

    if(bodyDataA && bodyDataB)
    {
        if(std::strcmp(bodyDataA->GetTagName(), "gel") == 0 && std::strcmp(bodyDataB->GetTagName(), "virus") == 0)
        {
            std::cout << "eliminated" << std::endl;
            score->AddPoints(5);
            covid->erase(std::remove(covid->begin(), covid->end(), bodyDataB), covid->end());
            bodyDataB->~GameObject();
        }
    }
}

void ContactListener::EndContact(b2Contact* contact)
{
    
}