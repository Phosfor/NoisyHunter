#include "State.hpp"

#include <boost/foreach.hpp>

namespace Engine{

    State::State() {}
    State::~State() {}

    void State::Update(const float time_delta){
        UpdateAllEntities(time_delta);
    }

    void State::UpdateAllEntities(const float time_delta){
        BOOST_FOREACH(Entity& entity, mEntities){
            entity.Update(time_delta);
        }

        if (mEntityListNeedsSorting) {
            //mEntities.sort();
            mEntityListNeedsSorting = false;
        }
    }


    void State::Draw(sf::RenderTarget* const target) const {
        BOOST_FOREACH(const Entity& entity, mEntities){
            entity.Draw(target);
        }
    }


    void State::AddEntity(Entity* entity){
        mEntities.push_back( entity );
        mEntityListNeedsSorting = true;
    }




}
