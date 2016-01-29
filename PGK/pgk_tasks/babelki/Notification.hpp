#ifndef NOTIFICATION_HPP
#define NOTIFICATION_HPP

class Notification {
public:
	enum Type {
		TARGET_HIT,
		BUBBLE_HIT,
		SHINY_BUBBLE_HIT,
	} type;

	Notification(Type notif_type) : type(notif_type) {}
};
#endif