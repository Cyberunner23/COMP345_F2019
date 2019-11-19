#include "Subject.h"
#include "ObserverBase.h"

Subject::Subject() {
	_observers = new list<ObserverBase*>;
}

Subject::~Subject() {
	//delete _observers;
}

void Subject::Attach(ObserverBase* o) {
	_observers->push_back(o);
};

void Subject::Detach(ObserverBase* o) {
	_observers->remove(o);
};

void Subject::Notify(int id) {
	list<ObserverBase*>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i)
		(*i)->Update(id);
};

void Subject::Notify()
{
    list<ObserverBase*>::iterator i = _observers->begin();
    for (; i != _observers->end(); ++i)
        (*i)->Update();
}