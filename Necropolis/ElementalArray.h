#pragma once

struct ElementalArray {

	ElementalArray() {
		_EARTH	= 0;
		_WATER	= 0;
		_AIR	= 0;
		_FIRE	= 0;
		_DARK	= 0;
		_LIGHT	= 0;
	}

	ElementalArray(int earth, int water, int air, int fire, int dark, int light) 
	{
		_EARTH	= earth;
		_WATER	= water;
		_AIR	= air;
		_FIRE	= fire;
		_DARK	= dark;
		_LIGHT	= light;
	}

	int getEarth()	{ return _EARTH; }
	int getWater()	{ return _WATER; }
	int getAir()	{ return _AIR; }
	int getFire()	{ return _FIRE; }
	int getDark()	{ return _DARK; }
	int getLight()	{ return _LIGHT; }

	void setEarth(const int earth)	{ _EARTH = earth; }
	void setWater(const int water)	{ _WATER = water; }
	void setAir(const int air)		{ _AIR = air; }
	void setFire(const int fire)	{ _FIRE = fire; }
	void setDark(const int dark)	{ _DARK = dark; }
	void setLight(const int light)	{ _LIGHT = light; }

private:
	int _EARTH, _WATER, _AIR, _FIRE, _DARK, _LIGHT;

};