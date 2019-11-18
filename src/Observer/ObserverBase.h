#pragma once

class ObserverBase {
public:
	~ObserverBase();
	virtual void Update() = 0;

protected:
	ObserverBase();

};
