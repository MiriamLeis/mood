#include "DestroyAfterSecsEC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Scene.h"

#include <ctime>
#include <iostream>
#include <value.h>

void DestroyAfterSecsEC::checkEvent() {
    if (firstTime_) {
        firstTime_ = false;
        creationTime_ = clock() / static_cast<float>(CLOCKS_PER_SEC);
    }

    float seconds = clock() / static_cast<float>(CLOCKS_PER_SEC);
    if (seconds - creationTime_ >= lifeTime_) {
        scene_->deleteEntity(father_);
    }
}

void DestroyAfterSecsEC::setLifeTime(int n) { lifeTime_ = n; }

// FACTORY INFRASTRUCTURE
DestroyAfterSecsECFactory::DestroyAfterSecsECFactory() = default;

Component* DestroyAfterSecsECFactory::create(Entity* _father,
                                             Json::Value& _data,
                                             Scene* _scene) {
    DestroyAfterSecsEC* destroyAfterSecsEC = new DestroyAfterSecsEC();

    destroyAfterSecsEC->setFather(_father);
    destroyAfterSecsEC->setScene(_scene);
    _scene->getComponentsManager()->addEC(destroyAfterSecsEC);

    if (!_data["lifeTime"].isDouble())
        throw std::exception("DestroyAfterSecsEC: lifeTime is not a double");
    destroyAfterSecsEC->setLifeTime(_data["lifeTime"].asDouble());

    destroyAfterSecsEC->setActive(true);

    return destroyAfterSecsEC;
};

DEFINE_FACTORY(DestroyAfterSecsEC);