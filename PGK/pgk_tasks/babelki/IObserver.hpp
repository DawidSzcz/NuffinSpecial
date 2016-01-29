#ifndef IOBSERVER_HPP
#define IOBSERVER_HPP

#include "Notification.hpp"

class IObserver {
public:
	virtual void Notify(Notification n) = 0;
	virtual ~IObserver() {}
};

#endif