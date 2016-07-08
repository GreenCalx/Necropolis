#pragma once
template <class T> class SkillPrototype
{
public:
	virtual T* Clone() const = 0;
	virtual ~SkillPrototype();
};

template<class T>
inline SkillPrototype<T>::~SkillPrototype()
{
}
