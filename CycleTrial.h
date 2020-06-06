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

#ifndef CIRCLETRIAL_H
#define CIRCLETRIAL_H
#include <iostream>
#include <string>
#include <unordered_set>
#include <math.h>
#include <sstream>
#include "Point.h"
using namespace std;

//!A two cycle constraints. 
/**
  
  It contains two cycle information including the overlapping area.
  Detail about two cycle constraints can be seen in:
  https://ieeexplore.ieee.org/abstract/document/8935061
*/
struct twoCycleTrial
{
  ///Center one's ID
  int c1ID;
  ///Center two's ID
  int c2ID; 
  ///X coordinate of center one
  float c1X;
  ///Y coordinate of center one
  float c1Y;
  ///X coordinate of center two
  float c2X;
  ///Y coordinate of center two
  float c2Y;
  ///circle one's radius in hops
  float h1;
  ///circle two's radius in hops
  float h2;
  ///average distance of each hop
  float d;
  ///mathematic calculated overlapping area of two circles
  float tArea;
  /// rate3 * acAr
  float grAr;
  /// (acAr / tArea)^3
  float rate3;
  ///tested overlapping area of two circles and TAS
  float acAr;
};




ostream& operator<<(ostream& os,twoCycleTrial &rhs)
{
  os<<"best two cycle:"<<endl;
  os<<"c1ID: "<<rhs.c1ID<<" coor: ("<<rhs.c1X<<", "<<rhs.c1Y<<")"<<endl;
  os<<"c2ID: "<<rhs.c2ID<<" coor: ("<<rhs.c2X<<", "<<rhs.c2Y<<")"<<endl;
  os<<"r1 and r2 and d: "<<rhs.h1<<"  "<<rhs.h2<<"  "<< rhs.d<< endl;
  os<<"grAr and acAr: "<<rhs.grAr<<"  "<<rhs.acAr<<endl;
  os<<"tArea and rate3: "<<rhs.tArea<< "   "<<rhs.rate3<<endl;
  return os;
}



bool sortCycleTrial(twoCycleTrial ct1, twoCycleTrial ct2)
{
  return ct1.grAr * ct1 . rate3 > ct2 . grAr * ct2 . rate3;

}







#endif
