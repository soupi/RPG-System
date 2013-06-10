#pragma once

class Attack;
class HeroCharacter;
class Enemy;
class LocalMap;

class AttackAgainst
{
public:
	virtual ~AttackAgainst() {}
	virtual void StepOn(LocalMap& localmap, Attack& attack, Enemy& obj) = 0;
	virtual void StepOn(LocalMap& localmap, Attack& attack, HeroCharacter& obj) = 0;

};

class AttackEnemy : public AttackAgainst
{
public:
	virtual void StepOn(LocalMap& localmap, Attack& attack, Enemy& obj);
	virtual void StepOn(LocalMap& localmap, Attack& attack, HeroCharacter& obj) {}

};

class AttackHero : public AttackAgainst
{
public:
	virtual void StepOn(LocalMap& localmap, Attack& attack, Enemy& obj) {}
	virtual void StepOn(LocalMap& localmap, Attack& attack, HeroCharacter& obj);

};

class AttackAll : public AttackAgainst
{
public:
	virtual void StepOn(LocalMap& localmap, Attack& attack, Enemy& obj);
	virtual void StepOn(LocalMap& localmap, Attack& attack, HeroCharacter& obj);

};