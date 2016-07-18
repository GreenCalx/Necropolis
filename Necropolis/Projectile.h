#pragma once

// Projectiles are small entities defining a 'small' actor that is the 'physical reality' of a given spell/arrow/whatever.
//-----

/**------------**/
class Projectile /* : public TE::Actor */
{


public:
	Projectile();
	~Projectile();

private:
	// Existence
	/* coordinates*/


	// Physics
	double		weight = 0.;
	double		impulse = 0.;
	double		angularMomentum = 0.;

	double		randomizerCoefficient = 1. ; // fuzzy projectile trajectory

	// Behaviour
	

};

