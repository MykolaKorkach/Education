#pragma once
#include <iostream>
#include <string>
#include <vector>


class TransportProduct
{
    
public:
    
    virtual void MoveTo(std::string City) = 0;
    virtual void PutTheBox(int BoxId) = 0;
    virtual void TakeOutTheBox(int BoxId) = 0;

    virtual ~TransportProduct() = default;
};

class Track : public TransportProduct
{
    
public:
    
    virtual void MoveTo(std::string City) override {}
    virtual void PutTheBox(int BoxId) override {}
    virtual void TakeOutTheBox(int BoxId) override {}
    
    virtual ~Track() override = default;
};

class Plane : public TransportProduct
{
    
public:
    
    virtual void MoveTo(std::string City) override {}
    virtual void PutTheBox(int BoxId) override {}
    virtual void TakeOutTheBox(int BoxId) override {}
    
    virtual ~Plane() override = default;
};



class GarageFactory
{
    
public:    

    // Create transport correspond to request
    virtual TransportProduct* CreateTransport(float Distance, float BoxWeight) = 0;
};

class Garage_Track : public GarageFactory
{
    
public:
    
    virtual TransportProduct* CreateTransport(float Distance, float BoxWeight) override
    {
        return new Track();
    }
};

class Garage_Plane : public GarageFactory
{
    
public:

    virtual TransportProduct* CreateTransport(float Distance, float BoxWeight) override
    {
        return new Plane();
    }
};


class DeliverSystem
{
    
public:

    bool Deliver(const std::string& ToCity, int BoxId)
    {
        GarageFactory* Factory;

        if (std::find(RoadConnections.begin(), RoadConnections.end(), ToCity) != RoadConnections.end())
        {
            Factory = new Garage_Track();
        }
        else if (std::find(AirConnections.begin(), AirConnections.end(), ToCity) != AirConnections.end())
        {
            Factory = new Garage_Plane();
        }
        else
        {
            return false;
        }

        if (TransportProduct* CreatedTransport = Factory->CreateTransport(100.f, 100.f))
        {
            CreatedTransport->PutTheBox(BoxId);
            CreatedTransport->MoveTo(ToCity);
            CreatedTransport->TakeOutTheBox(BoxId);
            
            delete CreatedTransport;
        }        
        
        return true;
    }
    
private:

    std::vector<std::string> RoadConnections {"Lviv", "Odessa", "Kharkiv"};
    std::vector<std::string> AirConnections {"NewYork", "Dublin", "Sydney"};
};


class Customer
{
public:

    void InitDelivering() const
    {
        const std::string DeliveryPoint = PossibleDeliverPoint[rand() % PossibleDeliverPoint.size()];
        std::cout << "Customer want to deliver his box to " << DeliveryPoint << std::endl;

        DeliverSystem DeliveringSystem;

        DeliveringSystem.Deliver(DeliveryPoint, 5);
    }

private:

    std::vector<std::string> PossibleDeliverPoint {"Lviv", "Odessa", "Kharkiv", "NewYork", "Dublin", "Sydney"};
};
