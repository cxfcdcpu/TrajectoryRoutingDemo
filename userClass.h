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


#ifndef USERCLASS_H
#define USERCLASS_H

#include<iostream>	//cout
#include<stdio.h>	//printf
#include<string.h>	//strlen
#include<string>	//string
#include<cstring>
#include<sys/socket.h>	//socket
#include<arpa/inet.h>	//inet_addr
#include<netdb.h>	//hostent
#include<stdlib.h>
#include "allConstant.h"
#include <unistd.h>
#include <thread>
#include <chrono> 
#include "quartic.h"
#include <map>
#include <sstream> 
#include <iterator>
#include <unordered_set>
#include <vector>
#include <math.h>
#include <future>
#include <complex>
#include <algorithm>
#include "Point.h"
#include "CycleTrial.h"
#include "HyperTrial.h"
#include "generalFunction.h"
#include "geometryFunction.h"
#include "EllipseTrial.h"


using namespace std;
//!An object that represent an user of the software
/**
A user that has ID, a WSN topology and information, the trajectory area set (TAS).
Use the above information, we can find the encoded trajectory using proposed algorithm in:
https://ieeexplore.ieee.org/abstract/document/8935061

*/
class User
{
  
  private:
    
    string id;
    int nodes;
    int anchor;
    int radioRange;
    int epoch;
    int tSize;
    short xList[nodeSize];
    short yList[nodeSize];
    short tx[strokeSize];
    short ty[strokeSize];
    //int hv[nodeSize][anchorSize];
    bool computingLock;
    int totalStroke;
    
  public:
    ///The Trajectory area set, it is the user defined trajectory.
    unordered_set<string> TAS;
    ///Map request ID and encoded trajecotry ID
    map<string,string> resultMap;
    ///A constructor
    User():xList(),yList()
    {
        id="none";
        nodes=-1;
        anchor=-1;
        radioRange=-1;
        epoch=-1;
        tSize=0;
        computingLock=0;
        for(int i=0;i<strokeSize;i++)
        {
          tx[i]=-1;
          ty[i]=-1;
        }
        for(int i=0;i<nodeSize;i++)
        {
          xList[i]=rand()%width;
          yList[i]=rand()%height;
        }
    
    }
    ///A constructor with ID as input
    /**
		  construct an User instance

		  @param i The ID of the user
		*/
    User(string i):xList(),yList()
    {
        id=i;
        epoch=-1;
        nodes=-1;
        anchor=-1;
        radioRange=-1;
        tSize=0;
        computingLock=0;
        for(int i=0;i<strokeSize;i++)
        {
          tx[i]=-1;
          ty[i]=-1;
        }
        for(int i=0;i<nodeSize;i++)
        {
          xList[i]=rand()%width;
          yList[i]=rand()%height;
        }
    }
    /**
		  set the number of nodes in the Wireless sensor networks (WSNs).

		  @param n The number of sensor nodes
		*/
    void setNodes(int n){nodes=n;}
    /**
		  set the number of anchor nodes in the Wireless sensor networks (WSNs).

		  @param a The number of anchor nodes
		*/
    void setAnchor(int a){anchor=a;}
    /**
		  set the radio range of the Wireless sensor networks (WSNs).

		  @param r The radio range of sensor nodes
		*/
    void setRange(int r){radioRange=r;}
    /**
		  set the epoch (like an ID) of the request of the user

		  @param e The epoch of the request
		*/
    void setEpoch(int e){epoch=e;}
    /**
		  set the x coordinate of the i'th nodes

		  @param v The value of the x coordinate
		*/
    void setX(int i, int v){xList[i]=v;}
    /**
		  set the y coordinate of the i'th nodes

		  @param v The value of the y coordinate
		*/
    void setY(int i, int v){yList[i]=v;}
    /**
		  set the x and y coordinate of the ind'th trajectory points
		  Note: A trajectory can be draw with connected trajectory points.

		  @param x The value of the x coordinate
		  @param y The value of the y coordinate
		  @param ind The index of the ind'th trajectory
		*/
    void setTraj(int x, int y, int ind){tx[ind]=x;ty[ind]=y;}
    /**
		  Returns the number of nodes in the WSNs

		   
		  @return the number of nodes in the WSNs
		*/
    int getNodes(){return nodes;}
    /**
		  Returns the number of anchor nodes in the WSNs

		   
		  @return the number of anchor nodes in the WSNs
		*/
    int getAnchor(){return anchor;}
    /**
		  Returns the radio range of sensors

		   
		  @return the radio range of sensors
		*/
    int getRange(){return radioRange;}
    /**
		  Returns the current epoch

		   
		  @return the current epoch
		*/
    int getEpoch(){return epoch;}
    /**
		  Get the x coordinate of sensor node i

		  @param i The ID of the sensor we want to get X coordinate from 
		  @return x coordinate of sensor node i
		*/
    int getX(int i){return xList[i];}
    /**
		  Get the y coordinate of sensor node i

		  @param i The ID of the sensor we want to get y coordinate from 
		  @return y coordinate of sensor node i
		*/
    int getY(int i){return yList[i];}
    /**
		  Create the TAS from the stroke points

		  @param totalStroke The number of stroke points of a trajectory.
		*/
    void genTAS(int totalStroke);
    /**
		  Add a stroke point and it's current segment's width

		  @param p The stroke points of a trajectory.
		  @param width The width of current segment of trajectory.
		*/
    void addToTAS(Point p, int width);
    /**
		  Add two stroke points and it's current segment's width

		  @param p1 The stroke points of a trajectory.
		  @param p2 The stroke points of a trajectory.
		  @param width The width of current segment of trajectory.
		*/
    void addToTAS(Point p1, Point p2, int width);
    ///Print the TAS area in pixel square 
    void printArea();
    /**
		  find all possible two cycle constraints and calculate the overlapping area

		  @param hv The DV-Hop of all nodes in the WSNs
		  @return all possible two cycle constraints twoCycleTrial
		*/
    vector<twoCycleTrial> findTwoCycleTrial(short hv[][anchorSize]);
    /**
		  find all possible hyperbola and circle constraints and calculate the overlapping area
      using multi thread to speed up the calculation.
      
		  @param hv The DV-Hop of all nodes in the WSNs
		  @return all possible hyperbola and circle constraints hyperTrial
		*/
    vector<hyperTrial> findHyperTrial(short hv[][anchorSize]);
    /**
		  find all hyperbola and circle constraint and calculate the overlapping area given ah and h3
      
		  @param hv The DV-Hop of all nodes in the WSNs
		  @param ah The hop count of 'a' of the hyperbola
		  @param h3 The radius of the circle.
		  @return all possible hyperbola and circle constraints hyperTrial
		*/
    vector<hyperTrial> hyperHelper(short hv[][anchorSize], int ah, int h3);
    /**
		  find all possible ellipse and circle constraints and calculate the overlapping area
      using multi thread to speed up the calculation.
      
		  @param hv The DV-Hop of all nodes in the WSNs
		  @return all possible ellipse and circle constraints ellipseTrial
		*/
    vector<ellipseTrial> findEllipseTrial(short hv[][anchorSize]);
    /**
		  find all ellipse and circle constraint and calculate the overlapping area given ah and h3
      
		  @param hv The DV-Hop of all nodes in the WSNs
		  @param ah The hop count of 'a' of the ellipse
		  @param h3 The radius of the circle.
		  @return all possible ellipse and circle constraints ellipseTrial
		*/
    vector<ellipseTrial>  ellipseHelper(short hv[][anchorSize],int  ah,int  h3);
    /**
		  update the DV hop information to hv
      
      @param hv The DV-Hop of all nodes in the WSNs
    */
    void getHopInfo(short hv[][anchorSize]);
    //void updataHopVector();
};

void User:: printArea()
{
    cout<<"printing TAS"<<endl;
    int counter=0;
    for(string point: TAS)
    {
        counter++;
        cout<<"("<<point<<");";
    }
    cout<<endl;
    cout<<"total: "<<counter<<" points"<<endl;
    


}


vector<ellipseTrial> User::findEllipseTrial(short hv[][anchorSize])
{

    vector<ellipseTrial> trials;
    
    vector<future<vector<ellipseTrial>>> VF;
    for(int i=1;i<=10;i++)
    {
      for(int j=1;j<=10;j++)
      {
        VF.push_back(async(&User::ellipseHelper,this,hv,j,i));
      }
    }
    
    for(auto& V:VF)
    {
      vector<ellipseTrial> curT = V.get();
      //cout<<"Threads results number: "<<curT.size()<<endl;
      for(vector<ellipseTrial>::iterator it = curT.begin();it != curT.end();++it)
      {
        trials.push_back(*it);
      }
    }
    
    return trials;
}




vector<ellipseTrial> User::ellipseHelper(short hv[][anchorSize],int  ah,int  h3)
{
    vector<ellipseTrial> trials;

    for(int i=0;i<anchor;i++)
    {
      for(int j=0;j<anchor;j++)
      {
        
          float avgHopDis1= radioRange;
          float avgHopDis2= radioRange;
          float avgHopDis = radioRange;
          float dis=sqrt(euDis(xList[i],yList[i],xList[j],yList[j]));
          Point p1={xList[i],yList[i]};
          Point p2={xList[j],yList[j]};
          
          for(int z=0;z<anchor;z++)
          {
            //cout<<"Thread is working"<<endl;
            Point p3={xList[z],yList[z]};
            float dis2=sqrt(euDis(xList[z],yList[z],xList[j],yList[j]));
            float dis3=sqrt(euDis(xList[z],yList[z],xList[i],yList[i]));
            if(hv[z][j]!=-1&&hv[z][j]!=0 && hv[z][i]!=-1&&hv[z][i]!=0)
            {
              int hv1 = hv[i][j]>1?hv[i][j]:1;
              int hv2 = hv[z][j]>1?hv[z][j]:1;
              int hv3 = hv[z][i]>1?hv[z][i]:1;
              
	            avgHopDis1=(dis+ dis2 +dis3+radioRange) / (hv1+hv2+hv3);
	            avgHopDis2=(dis2 +dis3+2*radioRange/3) / (hv2+hv3);
	            avgHopDis=avgHopDis1/2+avgHopDis2/2;
	            //cout<<"avgHopDis2: "<<avgHopDis2<<endl;
	            vector<float> yr1;
	            vector<float> yr2;
	            float area1 = findInterEllipseCycle(p1,p2,p3,ah,h3,avgHopDis,avgHopDis,yr1);
	            float area2 = findInterEllipseCycle(p1,p2,p3,(ah-1),h3,avgHopDis,avgHopDis,yr2);
	            
	            //cout<<"area1 is : "<< area1<<endl;
	            //cout<<"area2 is : "<< area2<<endl;
	        
	            if(area1-area2>1000 && area1-area2 < 640000)
	            {
	              float yroot[8]={1.0};
	              int startInd=0;
	              for(float& y1:yr1)
	              {
	                yroot[startInd++]=y1;
	              }
	              startInd=4;
	              for(float& y2:yr2)
	              {
	                yroot[startInd++]=y2;
	              }
	              ellipseTrial tryEntry={i,j,z,static_cast<float>(xList[i]),static_cast<float>(yList[i]),
	                                static_cast<float>(xList[j]),static_cast<float>(yList[j]),static_cast<float>(xList[z]),
	                                static_cast<float>(yList[z]),static_cast<float>(ah),static_cast<float>(h3),
	                                static_cast<float>(avgHopDis),static_cast<float>(avgHopDis),
	                                static_cast<float>(area1-area2),0,0,0};
	              memcpy(&(tryEntry.yroot), &yroot, 32) ;    
	              trials.push_back(tryEntry);
	            }
            }
          }
          
        
      }
    }
    //cout<<"trials size: "<<trials.size()<<endl;
    return trials;
}


vector<hyperTrial> User::findHyperTrial(short hv[][anchorSize])
{

    vector<hyperTrial> trials;
    
    vector<future<vector<hyperTrial>>> VF;
    for(int i=1;i<=12;i++)
    {
      for(int j=1;j<=10;j++)
      {
        VF.push_back(async(&User::hyperHelper,this,hv,j,i));
      }
    }
    
    for(auto& V:VF)
    {
      vector<hyperTrial> curT = V.get();
      //cout<<"Threads results number: "<<curT.size()<<endl;
      for(vector<hyperTrial>::iterator it = curT.begin();it != curT.end();++it)
      {
        trials.push_back(*it);
      }
    }
    
    return trials;
}






void User :: getHopInfo(short hv[][anchorSize])
{
    nodes = nodes < 5000 ? nodes : 5000; 
    nodes = nodes < 0 ? 5000 : nodes;
    vector<vector<int>> neighborsList(nodes);
    
    for(int i=0;i<nodes;i++)
    {
        int curX=xList[i];
        int curY=yList[i];
        
        for(int j=0;j<nodes;j++)
        {
            if(i!=j){
                int neighborX=xList[j];
                int neighborY=yList[j];
                if(euDis(curX,curY,neighborX,neighborY)<radioRange*radioRange)
                {
                    neighborsList[i].push_back(j);
                }
            }
        }
    }
    
    //cout<<radioRange<<endl;
    
    
    for(int i=0;i<nodes;i++)
    {
        for(int j=0;j<anchor;j++)
        {
            hv[i][j]=-1;
        }
    }
    
    for(int i=0;i<anchor;i++)
    {
        unordered_set<int> visited;
        queue<int> nq;
        nq.push(i);
        while(!nq.empty())
        {
            int cur=nq.front();
            nq.pop();
            visited.insert(cur);
            int curHop=hv[cur][i]==-1?0:hv[cur][i];
          if(!neighborsList[cur].empty()){
            for(int neighbor : neighborsList[cur])
            {
                if(visited.find(neighbor)==visited.end())
                {
                    nq.push(neighbor);
                    visited.insert(neighbor); 
                }
                if(hv[neighbor][i]==-1)hv[neighbor][i]=curHop+1;
                else
                {
                    hv[neighbor][i]=hv[neighbor][i]<curHop+1?hv[neighbor][i]:curHop+1;
                }  
            }
          }
      }
    }

}

vector<twoCycleTrial> User::findTwoCycleTrial(short hv[][anchorSize])
{

    vector<twoCycleTrial> trials;

    for(int i=0;i<anchor;i++)
    {
      for(int j=0;j<anchor;j++)
      {
      if(i!=j){
        float avgHopDis= radioRange;
        float dis=sqrt(euDis(xList[i],yList[i],xList[j],yList[j]));
        Point p1={xList[i],yList[i]};
        Point p2={xList[j],yList[j]};
        //cout<<i<<" and "<<j<<" hv: "<<hv[i][j]<<" dis "<<dis<<endl;
        if(hv[i][j]!=-1&&hv[i][j]!=0)avgHopDis=dis / hv[i][j];
      
        //cout<<"avgHopDis: "<<avgHopDis<<endl;
        for(int h1=1;h1<20;h1++)
        {
          for(int h2=1;h2<20;h2++)
          {
            if ( (h1+h2)*avgHopDis>dis)
            {
                float area=findInterTwoCycle(p1,h1,p2,h2,avgHopDis);
                if (area>1000)
                {
                    twoCycleTrial tryEntry={i,j,static_cast<float>(xList[i]),static_cast<float>(yList[i]),
                                        static_cast<float>(xList[j]),static_cast<float>(yList[j]),static_cast<float>(h1),
                                        static_cast<float>(h2),static_cast<float>(avgHopDis),static_cast<float>(area),0,0,0};  
                    trials.push_back(tryEntry);
                }
            }
          
          }
        }
       }
      }
    }
    return trials;
}

vector<hyperTrial> User::hyperHelper(short hv[][anchorSize],int  ah,int  h3)
{
    vector<hyperTrial> trials;

    for(int i=0;i<anchor;i++)
    {
      for(int j=0;j<anchor;j++)
      {
        if(i!=j){
          float avgHopDis1= radioRange;
          float avgHopDis2= radioRange;
          float dis=sqrt(euDis(xList[i],yList[i],xList[j],yList[j]));
          Point p1={xList[i],yList[i]};
          Point p2={xList[j],yList[j]};
          if(hv[i][j]!=-1&&hv[i][j]!=0)avgHopDis1=dis / hv[i][j];
          //avgHopDis2= avgHopDis1;
          if(dis>2*ah*avgHopDis1)
          {
            for(int z=0;z<anchor;z++)
            {
              //cout<<"Thread is working"<<endl;
              Point p3={xList[z],yList[z]};
              float dis2=sqrt(euDis(xList[z],yList[z],xList[j],yList[j]));
              float dis3=sqrt(euDis(xList[z],yList[z],xList[i],yList[i]));
              if(hv[z][j]!=-1&&hv[z][j]!=0 && hv[z][i]!=-1&&hv[z][i]!=0)
              {
                  avgHopDis2=(dis+ dis2 +dis3) / (hv[i][j]+hv[z][j]+hv[z][i]);
                  //cout<<"avgHopDis2: "<<avgHopDis2<<endl;
                  vector<float> yr1;
                  vector<float> yr2;
                  float area1 = findInterHyperCycle(p1,p2,p3,ah,h3,avgHopDis1,avgHopDis2,yr1);
                  float area2 = findInterHyperCycle(p1,p2,p3,(ah-1),h3,avgHopDis1,avgHopDis2,yr2);
                  
                  //cout<<"area1 is : "<< area1<<endl;
                  //cout<<"area2 is : "<< area2<<endl;
                  
                  if(area1-area2>1000 && area1-area2 < 640000){
                    float yroot[8]={0.0};
                    int startInd=0;
                    for(float& y1:yr1)
                    {
                      yroot[startInd++]=y1;
                    }
                    startInd=4;
                    for(float& y2:yr2)
                    {
                      yroot[startInd++]=y2;
                    }
                    hyperTrial tryEntry={i,j,z,static_cast<float>(xList[i]),static_cast<float>(yList[i]),
                                      static_cast<float>(xList[j]),static_cast<float>(yList[j]),static_cast<float>(xList[z]),
                                      static_cast<float>(yList[z]),static_cast<float>(ah),static_cast<float>(h3),
                                      static_cast<float>(avgHopDis1),static_cast<float>(avgHopDis2),
                                      static_cast<float>(area1-area2),0,0,0};
                    memcpy(&(tryEntry.yroot), &yroot, 32) ;    
                    trials.push_back(tryEntry);
                  }
              }
            }
          }
        }
      }
    }
    //cout<<"trials size: "<<trials.size()<<endl;
    return trials;
}

void User:: genTAS(int ts)
{
    TAS.clear();
    totalStroke=ts;
    int width=1;
    for( int i=0;i<ts;i++)
    {
        if(tx[i]<0)
        {
            width=ty[i];
        
        }
        else
        {
            if(tx[i-1]>0)
            {
                Point preP={tx[i-1],ty[i-1]};
                Point curP={tx[i],ty[i]};
                addToTAS(preP,curP,width);
            
            }
            else
            {
                Point curP={tx[i],ty[i]};
                addToTAS(curP,width);
            
            }
        
        }
    
    }

}

void User:: addToTAS(Point p, int width)
{
    int lx= p.m_X-width / 2 < 0? 0 : p.m_X-width / 2;
    int ly= p.m_Y-width / 2 < 0? 0 : p.m_Y-width / 2;
    for( int i=lx; i<p.m_X+width / 2;i++)
    {
        for(int j=ly;j<p.m_Y+width / 2;j++)
        {
            Point curP={i,j};
            if(pDis(curP, p)<width*width / 4)TAS.insert(to_string(curP.m_X)+" "+to_string(curP.m_Y));
        }
    }


}


void User:: addToTAS(Point p1, Point p2,int width)
{
    int lx1= p1.m_X-width / 2<0?0:p1.m_X-width / 2;
    int ly1= p1.m_Y-width / 2<0?0:p1.m_Y-width / 2;
    int lx2= p2.m_X-width / 2<0?0:p2.m_X-width / 2;
    int ly2= p2.m_Y-width / 2<0?0:p2.m_Y-width / 2;
    int rx= p1.m_X+width / 2<p2.m_X+width / 2?p2.m_X+width / 2:p1.m_X+width / 2;
    int ry= p1.m_Y+width / 2<p2.m_Y+width / 2?p2.m_Y+width / 2:p1.m_Y+width / 2;
    int lx=lx1<lx2?lx1:lx2;
    int ly=ly1<ly2?ly1:ly2;
    
    for( int i=lx; i<rx;i++)
    {
        for(int j=ly;j<ry;j++)
        {
            Point curP={i,j};
            if(lDis(curP, p1,p2)<width*width / 4)TAS.insert(to_string(curP.m_X)+" "+to_string(curP.m_Y));
        }
    }
}

#endif
