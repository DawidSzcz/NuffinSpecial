#ifndef IOBSERVABLE_HPP
#define IOBSERVABLE_HPP

#include <vector>
#include "Notification.hpp"
#include "IObserver.hpp"

class IObservable {
public:
	virtual void RegisterObserver(IObserver* obs) { observers.push_back(obs); }
	virtual ~IObservable() {}
protected:
	std::vector<IObserver*> observers;
	virtual void NotifyObservers(Notification n) const {
		for(auto obs : observers)
		obs->Notify(n);
	}
};

#endif