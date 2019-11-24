//
//  main.cpp
//  HW3
//
//  Created by Ziying Yu on 2/6/19.
//  Copyright © 2019 Ziying Yu. All rights reserved.
//

//Your declarations and implementations would go here
class Landmark
{
public:
    Landmark(string name) {m_name=name;}; //constructor
    string name() const {return m_name;} //non-virtual
    virtual ~Landmark() {} //destructor
    virtual string color() const = 0; //pure-virtual, cannot make a object
    virtual string icon() const =0; //pure-virtual

private:
    string m_name;
};


class Hotel: public Landmark
{
public:
    Hotel(string name): Landmark(name)
    {
       
    }
    
    virtual ~Hotel()
    {
        cout<<"Destroying the hotel "<<name()<<"."<<endl;
        
    }
    
    
    virtual string color() const{
        return "yellow";
    }
    virtual string icon() const{
        return "bed";
    }
private:

};

class Restaurant: public Landmark
{
public:
    Restaurant(string name, int capcity): Landmark(name)
    {
        m_capcity=capcity;
    }
    
    virtual ~Restaurant()
    {
        cout<<"Destroying the restaurant "<<name()<<"."<<endl;
        
    }
    
    virtual string color() const{
        return "yellow";
    }
    virtual string icon() const{
        if(m_capcity<40)
        {
            return "small knife/fork";
        }
        else
        {
            return "large knife/fork";
        }
    }
private:
    int m_capcity;

};

class Hospital: public Landmark
{
public:
    Hospital(string name): Landmark(name)
    {

    }
    
    virtual ~Hospital()
    {
        cout<<"Destroying the hospital "<<name()<<"."<<endl;
        
    }
    
    virtual string color() const{
        return "blue";
    }
    virtual string icon() const{
        return "H";
    }
private:

};

