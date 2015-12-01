#include "IObservable.hpp"

void IObservable::NotifyObservers(Notification n) const {
	for(auto it=observers.begin() ; it != observers.end() ; it++)
		(*it)->Notify(n);
}