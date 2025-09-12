//
// Created by mossy on 9/12/2025.
//

#ifndef ACTOR_H
#define ACTOR_H



class Actor {
public:
    enum State {
        EActive,
        EPaused,
        EDead
    };
    Actor(class Game* game);
    virtual ~Actor();

    void Update(float deltaTime);
    void UpdateComponents(float deltaTime);
    virtual void UpdateActor(float deltaTime);


    void AddComponent(class Component* component);
    void RemoveComponent(class Component* component);

private:
    State mState;
    Vector2 mPosition;
    float mScale;
    flaot mROtation;
    std::vector<class Component*> mComponents;
    class Game* mGame;

};



#endif //ACTOR_H
