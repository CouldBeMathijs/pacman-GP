#ifndef PACMAN_CONCRETEENTITYFACTORY_H
#define PACMAN_CONCRETEENTITYFACTORY_H
#include "AbstractEntityFactory.h"

#include <memory>

class ConcreteEntityFactory final : public AbstractEntityFactory {
public:
    std::shared_ptr<EntityModel> createPacman(const Rectangle& p) override;
    std::shared_ptr<EntityModel> createWall(const Rectangle& p) override;
    std::shared_ptr<EntityModel> createCoin(const Rectangle& p) override;
    std::shared_ptr<EntityModel> createFruit(const Rectangle& p) override;

    std::shared_ptr<EntityModel> createOrangeGhost(const Rectangle& p) override;
    std::shared_ptr<EntityModel> createRedGhost(const Rectangle& p) override;
    std::shared_ptr<EntityModel> createBlueGhost(const Rectangle& p) override;
    std::shared_ptr<EntityModel> createPinkGhost(const Rectangle& p) override;

private:
    /**
     * @brief Template helper function to create an Entity Model and attach its View Observer.
     * * @tparam Model The specific EntityModel subclass (e.g., Pacman, RedGhost).
     * @tparam View The specific View class that observes the Model.
     * @param p The position for the new entity.
     * @return A shared_ptr to the newly created Model, cast up to the base EntityModel.
     */
    template <typename Model, typename View>
    std::shared_ptr<EntityModel> createEntityWithView(Rectangle p) {
        auto model = std::make_shared<Model>(p);
        auto view = std::make_shared<View>(model);
        model->addObserver(view);
        return model;
    }
};
#endif // PACMAN_CONCRETEENTITYFACTORY_H
