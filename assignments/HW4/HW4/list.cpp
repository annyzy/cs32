//
//  list.cpp
//  HW4
//
//  Created by Ziying Yu on 3/4/19.
//  Copyright © 2019 Ziying Yu. All rights reserved.
//

void listAll(const MenuItem* m, string path) // two-parameter overload
{
    if(m==nullptr)
        return;

    if(m->name()!="")
    {
        path+=m->name();
        cout<<path<<endl;
        path+="/";
    }

    const vector<MenuItem*>* pathName = m->menuItems();

    if (pathName==nullptr)
        return;

    for(vector<MenuItem*>::const_iterator it = pathName->begin(); it!=pathName->end(); it++)
    {
        listAll((*it), path);
    }

}
