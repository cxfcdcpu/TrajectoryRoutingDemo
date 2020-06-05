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
#ifndef POINT_H
#define POINT_H
#include <iostream>
#include <string>
#include <unordered_set>
#include <math.h>
#include <sstream>
using namespace std;

struct Point
{
  int m_X;
  int m_Y;

};

ostream & operator<<(ostream& os, Point p){
  os<<"("<<p.m_X<<", "<<p.m_Y<<")"<<endl;
  return os;
}

#endif
