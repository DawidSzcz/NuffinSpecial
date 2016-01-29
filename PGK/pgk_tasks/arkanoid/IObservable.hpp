#ifndef IOBSERVABLE_HPP
#define IOBSERVABLE_HPP

#include <list>
#include "Notification.hpp"
#include "IObserver.hpp"

class IObservable {
public:
	virtual void RegisterObserver(IObserver* obs) { observers.push_back(obs); }
	virtual ~IObservable() { observers.clear(); }
protected:
	virtual void NotifyObservers(Notification n) const;
	std::list<IObserver*> observers;
};

#endif