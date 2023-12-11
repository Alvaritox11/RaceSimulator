#pragma once
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class GameState {
public:
	float dt;
	bool up;
	bool down;
	bool right;
	bool left;

	GameState(float deltaTime = 0.0f, bool up = false, bool down = false,
		bool right = false, bool left = false)
		: dt(deltaTime), up(up), down(down), right(right), left(left) {
	}
private:
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& dt& up& down& right& left;
	}
};