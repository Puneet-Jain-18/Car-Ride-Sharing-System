#include<iostream>
#include <bits/stdc++.h>
#include<fstream>
#include<conio.h>
#define driverCount 4
#define requestCount 12
using namespace std;
struct coordinate
{
    long double lon;
    long double lat;
};

class reqGraph
{
public:
    reqGraph*next;
    float weight;
    coordinate c;
    int assigned;
    reqGraph()
    {
        assigned=0;
    }
    bool operator ==(reqGraph g1)
    {
        if(c.lat==g1.c.lat && c.lon==g1.c.lon)
            return true;
        return false;
    }

};

class driverGraph
{
public:
    float weight;
    reqGraph * request;
    driverGraph * next;
};
void finalDriverAssignment(driverGraph dGraph[driverCount],driverGraph finalAssignment[driverCount]);
void initialize(coordinate drivers[driverCount],coordinate requests[requestCount][2]);
void insertIntoReqGraph(reqGraph g1[requestCount][requestCount][requestCount],coordinate c1,coordinate c2,coordinate c3,coordinate c4,coordinate c5,coordinate c6,int,int,int);
void minimisedRequestGraph(reqGraph g1[requestCount][requestCount][requestCount], reqGraph minimisedGraph[requestCount/2], long double reqWeights[requestCount][requestCount][requestCount] );
void createDriverGraph( reqGraph minimisedGraph[requestCount/2],driverGraph dGraph[driverCount] ,coordinate drivers[driverCount]);
long double toRadians(const long double degree)
{
    long double one_deg = (M_PI) / 180;
    return (one_deg * degree);
}

long double distance(long double lat1, long double long1,
                     long double lat2, long double long2)
{
    // Convert the latitudes
    // and longitudes
    // from degree to radians.
    lat1 = toRadians(lat1);
    long1 = toRadians(long1);
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);

    // Haversine Formula
    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1;

    long double ans = pow(sin(dlat / 2), 2) +
                          cos(lat1) * cos(lat2) *
                          pow(sin(dlong / 2), 2);

    ans = 2 * asin(sqrt(ans));

    // Radius of Earth in
    // Kilometers, R = 6371
    // Use R = 3956 for miles
    long double R = 6371;

    // Calculate the result
    ans = ans * R;

    return ans;
}
int main()
{
    cout<<"Hello";
    coordinate requests[requestCount][2]={ };            // index 0 start location index 1 destination

    long double reqWeights[requestCount][requestCount][requestCount];
    reqGraph g1[requestCount][requestCount][requestCount];

    reqGraph minimisedRequest[requestCount/2];

    driverGraph dGraph[driverCount];
    driverGraph finalAssignment[driverCount];
    coordinate drivers[driverCount]={ };
    float s11,s12,s21,s22;
    cout<<"Declared variables";
     initialize(drivers,requests);
     cout<<"Completed initialization";
    //creating graph for requests
    for(int i=0;i<requestCount;i++)
    {

        for(int j=0;j<requestCount;j++)
        {
            if (i==j)
                continue;
            s11=     distance( requests[i][0].lat, requests[i][0].lon,    requests[j][0].lat, requests[j][0].lon)+   //pick i first and drop i first
                     distance( requests[j][0].lat, requests[j][0].lon,    requests[i][1].lat, requests[i][1].lon)+
                     distance(  requests[i][1].lat, requests[i][1].lon,   requests[j][1].lat, requests[j][1].lon);

            s12=     distance( requests[i][0].lat, requests[i][0].lon,    requests[j][0].lat, requests[j][0].lon)+   //pick i first and drop j first
                     distance( requests[j][0].lat, requests[j][0].lon,    requests[j][1].lat, requests[j][1].lon)+
                     distance( requests[j][1].lat, requests[j][1].lon,    requests[i][1].lat, requests[i][1].lon);

            s21=     distance( requests[j][0].lat, requests[j][0].lon,    requests[i][0].lat, requests[i][0].lon)+  //pick j first and drop j first
                     distance( requests[i][0].lat, requests[i][0].lon,    requests[j][1].lat, requests[j][1].lon)+
                     distance( requests[j][1].lat, requests[j][1].lon,    requests[i][1].lat, requests[i][1].lon);

            s22=     distance( requests[j][0].lat, requests[j][0].lon,    requests[i][0].lat, requests[i][0].lon)+  // pick j first and drop i first
                     distance( requests[i][0].lat, requests[i][0].lon,    requests[i][1].lat, requests[i][1].lon)+
                     distance( requests[i][1].lat, requests[i][1].lon,    requests[j][1].lat, requests[j][1].lon);

            for(int k=0;k<requestCount;k++)
            {

                reqWeights[i][j][k]=max(min(s11,s12),min(s21,s22));
                if(reqWeights[i][j][k]==s11)
                {
                    insertIntoReqGraph(g1,requests[i][0],requests[j][0],requests[i][1],requests[j][1],requests[k][0],requests[k][1],i,j,k);
                }
                else if(reqWeights[i][j][k]==s12)
                {
                    insertIntoReqGraph(g1,requests[i][0],requests[j][0],requests[j][1],requests[i][1],requests[k][0],requests[k][1],i,j,k);

                }

                else if(reqWeights[i][j][k]==s21)
                {
                    insertIntoReqGraph(g1,requests[j][0],requests[i][0],requests[j][1],requests[i][1],requests[k][0],requests[k][1],i,j,k);
                }

                else if(reqWeights[i][j][k]==s22)
                {
                    insertIntoReqGraph(g1,requests[j][0],requests[i][0],requests[i][1],requests[j][1],requests[k][0],requests[k][1],i,j,k);
                }

            }
        }
        //end of request graph creation
        //made one D minimized graph of paired requests
    }
     minimisedRequestGraph(g1,minimisedRequest,reqWeights);
     cout<<"Done minimizati0n"<<endl;
     createDriverGraph(minimisedRequest, dGraph,drivers);
     finalDriverAssignment(dGraph,finalAssignment);
     //finalAssignment contain the drivers assigned to requests;


}

void initialize(coordinate drivers[driverCount],coordinate requests[requestCount][2])
{
     double lat[driverCount+requestCount];
    double lon[driverCount+requestCount];
double Lo;
double La;
    double Lo_st;
    double Lo_en;
    cout<<"\nLongitude Starting\t";
    cin>>Lo_st;
    cout<<"\nLongitude Ending\t";
    cin>>Lo_en;
    Lo=(Lo_en-Lo_st);
    Lo=Lo/driverCount;
    cout<<Lo;
for(int i = 0;i< driverCount ; i++)
{
lon[i]=Lo_st+Lo*i;
}
    Lo=(Lo_en-Lo_st);
    Lo=Lo/requestCount;
for(int i = driverCount;i< driverCount+requestCount ; i++)
{
lon[i]=Lo_st+Lo*(i-driverCount);
}
    double La_st;
    double La_en;
    cout<<"\n\nLatitude Starting\t";
    cin>>La_st;
    cout<<"\nLatitude Ending\t\t";
    cin>>La_en;
        La=(La_en-La_st);
        La=La/driverCount;
for(int i = 0;i< driverCount ; i++)
{
lat[i]=La_st+La*i;
}
    La=(La_en-La_st);
    La=La/requestCount;
for(int i = driverCount;i< driverCount+requestCount ; i++)
{
lat[i]=La_st+La*(i-driverCount);
}

   for(int i=0;i<driverCount;i++)
    {
        drivers[i].lat=lat[i];
        drivers[i].lon=lon[i];
        cout<<drivers[i].lat<<" "<<drivers[i].lon<<endl;
    }
    for(int i=0;i<requestCount;i++)
    {
        requests[i][0].lat=lat[i+driverCount];     //starting LAT
        requests[i][0].lon=lon[i+driverCount];    //starting LON
        requests[i][1].lat=(double)rand()/(RAND_MAX+1)*(La_en-La_st)+La_st;    //Random destination lAT
        requests[i][1].lon=(double)rand()/(RAND_MAX+1)*(Lo_en-Lo_st)+Lo_st;    //Random destination LON
        cout<<requests[i][0].lat<<" "<<requests[i][0].lon<<" "<<requests[i][1].lat<<" "<<requests[i][1].lon<<endl;
    }

}

void insertIntoReqGraph(reqGraph g1[requestCount][requestCount][requestCount],coordinate c1,coordinate c2,coordinate c3,coordinate c4,coordinate c5,coordinate c6,int i,int j,int k)
{
    reqGraph *second=new reqGraph;
    reqGraph *third=new reqGraph;
    reqGraph *fourth=new reqGraph;
    reqGraph *fifth=new reqGraph;
    reqGraph *sixth=new reqGraph;
    g1[i][j][k].next=second;
    second ->next=third;
    third ->next=fourth;
    fourth->next=fifth;
    fifth->next=sixth;
    sixth->next=NULL;


    g1[i][j][k].c=c5;
    second->c=c1;
    third->c=c2;
    fourth->c=c3;
    fifth->c=c4;
    sixth->c=c6;

}

void minimisedRequestGraph(reqGraph g1[requestCount][requestCount][requestCount], reqGraph minimisedGraph[requestCount/2] ,long double reqWeights[requestCount][requestCount][requestCount])
{
    int assigned[requestCount];
    for(int i=0;i<requestCount;i++)
    assigned[i]=0;
    for(int p=0;p<(int)requestCount/3;p++)
    {
         float min=99999999.9;
         int minI=-1;
         int minJ=-1;
         int minK=-1;
        for(int i=0;i<requestCount;i++)
        {
            for(int j=0;j<requestCount;j++)
            {
                for(int k=0;k<requestCount;k++)
                {


                    if(i<=j ||i<=k ||assigned[i]==1||assigned[j]==1||assigned[k]==1)//to be confirmed
                    continue;
                    if(reqWeights[i][j][k]<min)
                    {
                        min=reqWeights[i][j][k];
                        minI=i;
                        minJ=j;
                        minK=k;
                    }

                }
            }
        }
        minimisedGraph[p]=g1[minI][minJ][minK];
        minimisedGraph[p].weight=min;
        cout<<" Paired "<<minI<<"\t"<<minJ<<"\t"<<minK<<" with Weight   "<<minimisedGraph[p].weight<<endl;
        assigned[minI]=1;
        assigned[minJ]=1;
        assigned[minK]=1;
    }

}





void createDriverGraph( reqGraph minimisedGraph[requestCount/2],driverGraph dGraph[driverCount], coordinate drivers[driverCount])
{
    for(int i=0;i<driverCount;i++)
    {
        cout<<"00000000000000000000000000000000000000000";
        float d1,d2,d3;
        d1=distance( minimisedGraph[0].c.lat,       minimisedGraph[0].c.lon,    drivers[i].lat, drivers[i].lon);
        d2=distance( minimisedGraph[0].next->c.lat, minimisedGraph[0].next->c.lon,    drivers[i].lat, drivers[i].lon);
        d3=distance(minimisedGraph[0].next->next->c.lat, minimisedGraph[0].next->next->c.lon,    drivers[i].lat, drivers[i].lon);
        cout<<"D1  "<<d1<<"  D2  "<<d2<<"D3"<<d3<<endl;
        float minimised2=min(d1,d2);
        float minimised=min(minimised2,d3);
        dGraph[i].weight=minimised;
        dGraph[i].request=&minimisedGraph[0];
        dGraph[i].next=NULL;
        driverGraph * point=&dGraph[i];
        for(int j=1;j<driverCount;j++)
        {
            driverGraph *temp=new driverGraph ;
            temp->next=NULL;

        d1=distance( minimisedGraph[j].c.lat,       minimisedGraph[j].c.lon,          drivers[i].lat, drivers[i].lon);
        d2=distance( minimisedGraph[j].next->c.lat, minimisedGraph[j].next->c.lon,    drivers[i].lat, drivers[i].lon);
        d3=distance(minimisedGraph[j].next->next->c.lat, minimisedGraph[j].next->next->c.lon,    drivers[i].lat, drivers[i].lon);
        cout<<"D1  "<<d1<<"  D2  "<<d2<<"D3"<<d3<<endl;
        float minimised2=min(d1,d2);
        float minimised=min(minimised2,d3);
        temp->weight=minimised;
        temp->request=&minimisedGraph[j];
        point->next=temp;
        point=point->next;
        }


    }
}

void finalDriverAssignment(driverGraph dGraph[driverCount],driverGraph finalAssignment[driverCount])
{
    cout<<"Inside Assignment function";

      for(int i=0;i<driverCount;i++)
     {
         driverGraph * d=&dGraph[i];
     }

                int driverIndex=-1;
             driverGraph * final;
             float min=999999999999999;
        for(int i=0;i<driverCount;i++)
        {
              float min=999999999999999;
                driverGraph * temp=&dGraph[i];
                while(temp)
                {


                if((temp->weight)<min && temp->request->assigned!=1)
                {
                    driverIndex=i;
                    final=temp;
                    min=temp->weight;
                }
                temp=temp->next;
                }
                cout<<endl;
            cout<<"DriverId: "<<driverIndex<<"\t"<<"Distance From Request: "<<final->weight<<"\t"<<"Total distance travel to request "<<final->request->weight<<endl;
            finalAssignment[driverIndex].next=NULL;
            finalAssignment[driverIndex].request=final->request;
            finalAssignment[driverIndex].weight=final->weight;
            final->request->assigned=1;

        }

}
