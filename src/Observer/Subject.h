#pragma once

#include <list>

using namespace std;
class ObserverBase;

class Subject {

public:
	virtual void Attach(ObserverBase* o);
	virtual void Detach(ObserverBase* o);
	virtual void Notify(int id);
	Subject();
	~Subject();

private:
	list<ObserverBase*>* _observers;

};