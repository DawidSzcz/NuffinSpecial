#ifndef NOTIFICATION_HPP
#define NOTIFICATION_HPP

class Notification {
public:
	enum Type {
		BRICK_HIT,
		BALL_ESCAPE
	} type;

	Notification(Type notif_type) : type(notif_type) {}
};
#endif