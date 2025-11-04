#include "Subject.h"
Subject::~Subject() = default;
void Subject::update() {}
void Subject::addObserver(std::unique_ptr<Observer> n) { observers.push_back(std::move(n)); }