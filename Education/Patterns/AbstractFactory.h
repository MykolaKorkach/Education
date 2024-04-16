#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>

class LuggageHolderProduct
{    
public:
    
    int Capacity = 0;
};

class SmallHolder : public LuggageHolderProduct
{
public:
    SmallHolder()
    {
        Capacity = 100;
    }
};

class BigHolder : public LuggageHolderProduct
{
public:
    BigHolder()
    {
        Capacity = 500;
    }
};



class TransportFactoryBase
{
public:
    virtual LuggageHolderProduct* GetHolder() = 0;
};

class LongRage : public TransportFactoryBase
{
public:
    virtual LuggageHolderProduct* GetHolder()
    {
        return new BigHolder();
    }
};

class SmallRange : public TransportFactoryBase
{
public:
    virtual LuggageHolderProduct* GetHolder()
    {
        return new SmallHolder();
    }
};


class TransportProduct
{    
public:
    
    virtual void MoveTo(std::string City) = 0;
    virtual void PutTheBox(int BoxId) = 0;
    virtual void TakeOutTheBox(int BoxId) = 0;

    void PrepareTransport(TransportFactoryBase* Factory)
    {
        Holder = Factory->GetHolder();
    }
    
    virtual ~TransportProduct() = default;

    LuggageHolderProduct* Holder;
};

class Track : public TransportProduct
{    
public:
    
    virtual void MoveTo(std::string City) override {}
    virtual void PutTheBox(int BoxId) override {}
    virtual void TakeOutTheBox(int BoxId) override {}
    
    virtual ~Track() override = default;
};

class Palne : public TransportProduct
{    
public:
    
    virtual void MoveTo(std::string City) override {}
    virtual void PutTheBox(int BoxId) override {}
    virtual void TakeOutTheBox(int BoxId) override {}
    
    virtual ~Palne() override = default;
};



class GarageFactory
{    
public:    

    // Create transport correspond to request
    virtual TransportProduct* CreateTransport() = 0;
};

class Garage_Track : public GarageFactory
{    
public:
    
    virtual TransportProduct* CreateTransport() override
    {
        return new Track();
    }
};

class Garage_Plane : public GarageFactory
{    
public:
    
    virtual TransportProduct* CreateTransport() override
    {
        return new Track();
    }
};


class DeliverSystem
{    
public:

    bool Deliver(const std::string& ToCity, int BoxId)
    {
        GarageFactory* Factory;
        auto Iter = std::find(Connections.begin(), Connections.end(), ToCity);

        if (Iter == Connections.end())
        {
            return false;
        }

        if (Iter->second < 500)
        {
            Factory = new Garage_Track();
        }
        else if (Iter->second < 1500)
        {
            Factory = new Garage_Plane();
        }
        else
        {
            return false;
        }

        if (TransportProduct* CreatedTransport = Factory->CreateTransport())
        {
            TransportFactoryBase* TransportFactory = BoxWeight[BoxId] > 100 ? new LongRage() : new SmallRange();
            
            CreatedTransport->PrepareTransport(TransportFactory);
            
            CreatedTransport->PutTheBox(BoxId);
            CreatedTransport->MoveTo(ToCity);
            CreatedTransport->TakeOutTheBox(BoxId);
            
            delete CreatedTransport;
        }        
        
        return true;
    }
    
private:

    std::map<std::string, int> Connections {{"Lviv", 200}, {"Odessa", 300}, {"Kharkiv", 100}, {"NewYork", 1000}, {"Dublin", 800}, {"Sydney", 1100}};
    std::vector<int> BoxWeight {200, 300, 100};
};


class Customer
{
public:

    void InitDelivering() const
    {
        const std::string DeliveryPoint = PossibleDeliverPoint[rand() % PossibleDeliverPoint.size()];
        std::cout << "Customer want to deliver his box to " << DeliveryPoint << std::endl;

        DeliverSystem DeliveringSystem;

        DeliveringSystem.Deliver(DeliveryPoint, 1);
    }

private:

    std::vector<std::string> PossibleDeliverPoint {"Lviv", "Odessa", "Kharkiv", "NewYork", "Dublin", "Sydney"};
};



