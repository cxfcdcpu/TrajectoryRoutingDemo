/***************************************************************************
 *   Copyright (C) 2020 by Xiaofei Cao                                     *
 *   xiaofeicao0@gmail.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *   ( http://www.gnu.org/licenses/gpl-3.0.en.html )                       *
 *									   *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef ELLIPSETRIAL_H
#define ELLIPSETRIAL_H
#include <iostream>
#include <string>
#include <unordered_set>
#include <math.h>
#include <sstream>
#include "Point.h"
using namespace std;


struct ellipseTrial
{
  int c1ID;
  int c2ID;
  int c3ID; 
  float c1X;
  float c1Y;
  float c2X;
  float c2Y;
  float c3X;
  float c3Y;  
  float ah;
  float h3;
  float avgD1;
  float avgD2;
  float tArea;
  float grAr;
  float rate3;
  float acAr;
  float yroot[8];
};


ostream& operator<<(ostream& os,ellipseTrial &rhs)
{
  os<<"best ellipse and cycle:"<<endl;
  os<<"c1ID: "<<rhs.c1ID<<" coor: ("<<rhs.c1X<<", "<<rhs.c1Y<<")"<<endl;
  os<<"c2ID: "<<rhs.c2ID<<" coor: ("<<rhs.c2X<<", "<<rhs.c2Y<<")"<<endl;
  os<<"c3ID: "<<rhs.c3ID<<" coor: ("<<rhs.c3X<<", "<<rhs.c3Y<<")"<<endl;
  os<<"ah and h3 and avgD1 and avgD2: "<<rhs.ah<<"  "<<rhs.h3<<"  "<< rhs.avgD1<<" "<< rhs.avgD2<< endl;
  os<<"grAr and acAr: "<<rhs.grAr<<"  "<<rhs.acAr<<endl;
  os<<"tArea and rate3: "<<rhs.tArea<< "   "<<rhs.rate3<<endl;
  os<<"roots are: ";
  for(int kk=0;kk<8;kk++)
  {
    os<< rhs.yroot[kk]<< " ";
  }
  os<<endl;
  return os;
}

bool sortEllipseTrial(ellipseTrial ct1, ellipseTrial ct2)
{
  return  ct1.grAr * ct1 . rate3 > ct2 . grAr * ct2 . rate3;

}


#endif

