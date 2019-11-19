#pragma once

class ObserverBase {
public:
	~ObserverBase();
	virtual void Update(int id) = 0;

protected:
	ObserverBase();

};
