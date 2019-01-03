#pragma once
class IModule;

class IOutputPort
{
public:

	virtual void Write(double value) = 0;

	virtual double Read() const = 0;

	virtual IModule* GetOwnerModule() const = 0;
};

