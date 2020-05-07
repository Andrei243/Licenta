#pragma once
class CollisionExecutor {
public:
	virtual void OnCollisionEnter() {};
	virtual void OnCollisionContinuing() {};
	virtual void OnCollisionExit() {};

};