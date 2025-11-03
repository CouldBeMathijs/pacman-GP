#ifndef PACMAN_SUBJECT_H
#define PACMAN_SUBJECT_H

class Subject {
public:
    virtual ~Subject() = default;
    virtual void update();
};

class EntityModel : public Subject {
};

#endif // PACMAN_SUBJECT_H
