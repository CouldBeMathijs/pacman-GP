#include "Subject.h"
Subject::~Subject() = default;
void Subject::update() {}
void Subject::addObserver(std::unique_ptr<Observer> n) { observer = std::move(n); }