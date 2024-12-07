#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <array>
#include <bitset>

class Manager;
class Component;



class Entity
{
private:
	Manager& manager;
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;


public:





};