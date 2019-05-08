#include<iostream>
#include <bits/stdc++.h>
#include<fstream>
#include<conio.h>
#define driverCount 50    //change driver count here
#define requestCount 100  //change request count here
#define average_speed 60  //define average car speed here
using namespace std;
struct coordinate
{
    long double lon;
    long double lat;
};

class reqGraph   //request graph to store data of request from users
{
public:
    reqGraph*next;
    float weight;
    float waiting_time;
    coordinate c;
    int assigned;
    reqGraph()
    {
        assigned=0;
        waiting_time=0;
    }
    bool operator ==(reqGraph g1)           //overloaded == operation to compare lat and long
    {
        if(c.lat==g1.c.lat && c.lon==g1.c.lon)
            return true;
        return false;
    }

};

class driverGraph           //class to store information of drivers and there locations
{
public:
    float weight;
    reqGraph * request;
    driverGraph * next;
};
//initialize coordinates of request and drivers
void initialize(coordinate drivers[driverCount],coordinate requests[requestCount][2]);
//insert data into request graph class object(Utility function)
void insertIntoReqGraph(reqGraph g1[requestCount][requestCount],coordinate c1,coordinate c2,coordinate c3,coordinate c4,int,int);
//pair the most closest two requests
void minimisedRequestGraph(reqGraph g1[requestCount][requestCount], reqGraph minimisedGraph[requestCount/2], long double reqWeights[requestCount][requestCount] );
//assign al request to all drivers for later comparizon
void createDriverGraph( reqGraph minimisedGraph[requestCount/2],driverGraph dGraph[driverCount] ,coordinate drivers[driverCount]);
//finally find the most efficient request to assign to a driver
void finalDriverAssignment(driverGraph dGraph[driverCount],driverGraph finalAssignment[driverCount]);

// utility function for distance function to convert degree to radians
long double toRadians(const long double degree)
{
    long double one_deg = (M_PI) / 180;
    return (one_deg * degree);
}
//function to return distance between lat long pair
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
    // index 0 start location index 1 destination
    coordinate requests[requestCount][2]={ };

    //array to store weights of paired requests
    long double reqWeights[requestCount][requestCount];

    // graph to store all paired request
    reqGraph g1[requestCount][requestCount];

     //storing objects of final minimized paired requests
    reqGraph minimisedRequest[requestCount/2];

    //driver graph to store driver coordiantes and other information
    driverGraph dGraph[driverCount];

    //array cotining driver assigned to particular request pair efficintly
    driverGraph finalAssignment[driverCount];
    coordinate drivers[driverCount]={ };
    float s11,s12,s21,s22;

     //initializing driver and request array with uniformily distributed data
     initialize(drivers,requests);

    //creating graph for requests by pairing all two requests together and calculating weights
    long double total_distance=0;
    for(int i=0;i<requestCount;i++)
    {
        total_distance+=distance( requests[i][0].lat, requests[i][0].lon,    requests[i][1].lat, requests[i][1].lon);
    }
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

            //min of two pairs to find min of weights
            reqWeights[i][j]=max(min(s11,s12),min(s21,s22));

            //assign in order which has minimum weight
            if(reqWeights[i][j]==s11)
            {
                insertIntoReqGraph(g1,requests[i][0],requests[j][0],requests[i][1],requests[j][1],i,j);
            }
            else if(reqWeights[i][j]==s12)
            {
                insertIntoReqGraph(g1,requests[i][0],requests[j][0],requests[j][1],requests[i][1],i,j);

            }

            else if(reqWeights[i][j]==s21)
            {
                insertIntoReqGraph(g1,requests[j][0],requests[i][0],requests[j][1],requests[i][1],i,j);
            }

            else if(reqWeights[i][j]==s22)
            {
                insertIntoReqGraph(g1,requests[j][0],requests[i][0],requests[i][1],requests[j][1],i,j);
            }

        }
        //end of request graph creation
        //made one D minimized graph of paired requests
    }

     minimisedRequestGraph(g1,minimisedRequest,reqWeights);
     cout<<"Done minimizati0n"<<endl;
     //assigning the minimized request pairs to all drivers
     createDriverGraph(minimisedRequest, dGraph,drivers);

     //finfing min cost assignment and assigning them to driver
     finalDriverAssignment(dGraph,finalAssignment);
     long double totalweight=0;
     for(int i=0;i<driverCount;i++)
     {
        double weight1= distance( drivers[i].lat, drivers[i].lon, finalAssignment[i].request->c.lat, finalAssignment[i].request->c.lon);
         double weight2= distance( finalAssignment[i].request->next->c.lat, finalAssignment[i].request->next->c.lon, finalAssignment[i].request->c.lat, finalAssignment[i].request->c.lon);
          totalweight+=weight1;
          totalweight+=weight2;
         cout<<endl<<"Waiting time of first car :"<<(weight1/average_speed)<<"\t & second car : "<<(weight2/average_speed);

     }
     //finalAssignment contain the drivers assigned to requests;

     cout<<endl<<endl<<"Average Waiting time"<<(totalweight/(average_speed*requestCount))<<endl<<endl;
   cout<<"\nTotal distance if only one car taken : "<<total_distance;
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
lon[i]=Lo_st+Lo*i;                         //initiaizing data with uniform distribution
}
    Lo=(Lo_en-Lo_st);
    Lo=Lo/requestCount;
for(int i = driverCount;i< driverCount+requestCount ; i++)
{
lon[i]=Lo_st+Lo*(i-driverCount);          //initiaizing data with uniform distribution
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
lat[i]=La_st+La*i;                      //initiaizing data with uniform distribution
}
    La=(La_en-La_st);
    La=La/requestCount;
for(int i = driverCount;i< driverCount+requestCount ; i++)
{
lat[i]=La_st+La*(i-driverCount);       //initiaizing data with uniform distribution
}

   for(int i=0;i<driverCount;i++)
    {
        drivers[i].lat=lat[i];
        drivers[i].lon=lon[i];
    }
    for(int i=0;i<requestCount;i++)
    {
        requests[i][0].lat=lat[i+driverCount];     //starting LAT
        requests[i][0].lon=lon[i+driverCount];    //starting LON
        requests[i][1].lat=(double)rand()/(RAND_MAX+1)*(La_en-La_st)+La_st;    //Random destination lAT
        requests[i][1].lon=(double)rand()/(RAND_MAX+1)*(Lo_en-Lo_st)+Lo_st;    //Random destination LON
    }

}
//utility function to insert data into graph
void insertIntoReqGraph(reqGraph g1[requestCount][requestCount],coordinate c1,coordinate c2,coordinate c3,coordinate c4,int i,int j)
{
    reqGraph *second=new reqGraph;
    reqGraph *third=new reqGraph;
    reqGraph *fourth=new reqGraph;
    g1[i][j].next=second;
    second ->next=third;
    third ->next=fourth;
    fourth->next=NULL;

    g1[i][j].c=c1;
    second->c=c2;
    third->c=c3;
    fourth->c=c4;

}

void minimisedRequestGraph(reqGraph g1[requestCount][requestCount], reqGraph minimisedGraph[requestCount/2] ,long double reqWeights[requestCount][requestCount])
{
    int assigned[requestCount];  //flag array to store assigned request
    for(int i=0;i<requestCount;i++)
    assigned[i]=0;
    for(int k=0;k<requestCount/2;k++)
    {
         float min=99999999.9;
         int minI=-1;
         int minJ=-1;
        for(int i=0;i<requestCount;i++)
        {
            for(int j=0;j<requestCount;j++)
            {
                if(i<=j  ||assigned[i]==1||assigned[j]==1)
                continue;
                if(reqWeights[i][j]<min)
                {
                    min=reqWeights[i][j];         //finding min weight from the whole graph
                    minI=i;
                    minJ=j;
                }

            }
        }
        minimisedGraph[k]=g1[minI][minJ];//assigning min wheight from the whole graph
        minimisedGraph[k].weight=min;
        cout<<" Paired "<<minI<<"\t"<<minJ<<" with Weight   "<<minimisedGraph[k].weight<<endl;
        assigned[minI]=1;    //setting flag so this request is not assigned again
        assigned[minJ]=1;   //setting flag so this request is not assigned again
    }

}

void createDriverGraph( reqGraph minimisedGraph[requestCount/2],driverGraph dGraph[driverCount], coordinate drivers[driverCount])
{
    for(int i=0;i<driverCount;i++)
    {
        float d1,d2;
        d1=distance( minimisedGraph[0].c.lat,       minimisedGraph[0].c.lon,    drivers[i].lat, drivers[i].lon);
        d2=distance( minimisedGraph[0].next->c.lat, minimisedGraph[0].next->c.lon,    drivers[i].lat, drivers[i].lon);
        float minimised=min(d1,d2);     //setting minimum distance to driver to go first
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
          cout<<"D1  "<<d1<<"  D2  "<<d2<<endl;    // showing all request pairs and weights
        float minimised=min(d1,d2);  //assigning all requests to all drivers
        temp->weight=minimised;
        temp->request=&minimisedGraph[j];
        point->next=temp;
        point=point->next;
        }


    }
}

 //finding min weight request pair to all drivers
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
            long double total_distance=0;
        for(int i=0;i<driverCount;i++)
        {
              float min=999999999999999;
                driverGraph * temp=&dGraph[i];
                while(temp)
                {


                if((temp->weight)<min && temp->request->assigned!=1)
                {
                    driverIndex=i;
                    final=temp;                     //selecting minimum distance to assign request for each driver
                    min=temp->weight;
                }
                temp=temp->next;
                }
                cout<<endl;
            cout<<"DriverId : "<<driverIndex<<"\t"<<"Distance From Request: "<<final->weight<<"\t"<<"Total distance travel to request "<<final->request->weight<<endl;
            total_distance+=final->request->weight;
            finalAssignment[driverIndex].next=NULL;
            finalAssignment[driverIndex].request=final->request;  //assigning that request to the driver
            finalAssignment[driverIndex].weight=final->weight;    //assigning weights of the request pair
            final->request->assigned=1;                           //setting assgined flag

        }

        cout<<"Paired Weights Total : "<<total_distance;

}
//sangeeta.mittal@jiit.ac.in
