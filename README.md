# Car-Ride-Sharing-System
The project focuses on assigning rides to different costumers.Two costumers could be alloted to same ride so as to optimize fuel costs and decrease overall cost for each costumer.ride-sharing provides socially efficient transport services that help to save energy and to reduce congestion.
The performance of program is also rather crucial in ride sharing because the riders will not wait for long time and we require to compute the driver-rider pairs within minutes.
# Problem-Statement
There are a large number of requests with pickup and drop-off location information, and a large number of available cars with current location information. One of the tasks is to assign the requests to the cars, with two requests for one car. The assignment needs to be made socially efficient in the sense that the ride sharing does not incur much extra traveling distance for the drivers or and extra waiting time for the passengers.

<h4> assumptions</h4>
1. To replicate real life scenerio, we have considered costumers as well as rides to be normally distributed on x-y plane
2. The program make ride assignment independently without any initial bias towards closer pickups.
3. It is assumed that the car takes shortest distance while travelling between any two points, so insted of road network straight line distance between two points has been taken as distance.
# Solution-Approach
1. the solution presented runs in time O(n^3 ) and outputs a solution M with cost(M ) at most 2.5 times the optimal value.
2. Now for every 2 request pair there are 4 different paths to be cosidred.consider Si,Sj as starting point and Ti,Tj as drop location of requesets i,j respectively. Then the possible paths followed could be<br />

![alt text](https://github.com/Puneet-Jain-18/Car-Ride-Sharing-System/blob/master/path.png)


3. The algorithm takes a two-phase greedy approach. <br>
  A.In the first phase, it matches the 2n requests into n pairs based on the shortest distance to serve any request pair but on the worse pickup choice.
  B. In the second phase, we assign drivers to the pairs formed in the previous phase, under the assumption that the distance from a driver k to a pair of requests isdistance from d k to the nearer pickup location of the two.
4. Finally the total distance is calculated and total waiting time for each driver is calculated using an average assigned speed.
5. We also display the amount of distance travelled if only one ride would be assigned to one car.and the diff if car sharing is opted.

# Future-Work
1. Currently it is assumed straight line distance between two points. We could work on implementing road networks into the program to give more realistic output.
2. Currently program preallocaes rides and costumer location. We could integrate code such that new incoming requests could be simultaniously allocated to cars while the ride is currently in progress to make the program real-time compatible. 
