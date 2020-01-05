# Car-Ride-Sharing-System
The project focuses on assigning rides to different costumers. Two costumers could be allocated to the same ride so as to optimize fuel costs and decrease overall cost for each costumer.ride-sharing provides socially efficient transport services that help to save energy and to reduce congestion.
The performance of the program is also rather crucial in ride-sharing because the riders will not wait for a long time and we require to compute the driver-rider pairs within minutes.
# Problem-Statement
There are a large number of requests with pickup and drop-off location information, and a large number of available cars with current location information. One of the tasks is to assign requests to the cars, with two requests for one car. The assignment needs to be made socially efficient in the sense that the ride-sharing does not incur much extra traveling distance for the drivers or and extra waiting time for the passengers.

 <b> assumptions</b> 
1. To replicate the real-life scenario, we have considered costumers as well as rides to be uniformally distributed on the x-y plane
2. The program makes ride assignments independently without any initial bias towards closer pickups.
3. It is assumed that the car takes the shortest distance while traveling between any two points, so instead of road network straight line distance between two points has been taken as distance.
# Solution-Approach
1. the solution presented runs in time O(n^3 ) and outputs a solution M with cost(M ) at most 2.5 times the optimal value.
2. Now for every 2 request pair, there are 4 different paths to be considered. Consider Si, Sj as starting point and Ti, Tj as drop location of requests i,j respectively. Then the possible paths followed could be<br />

![alt text](https://github.com/Puneet-Jain-18/Car-Ride-Sharing-System/blob/master/path.png)


3. The algorithm takes a two-phase greedy approach. <br />
  A. In the first phase, it matches the 2n requests into n pairs based on the shortest distance to serve any request pair but on the worse pickup choice.<br />
  B. In the second phase, we assign drivers to the pairs formed in the previous phase, under the assumption that the distance from a driver k to a pair of requests is the distance from d k to the nearer pickup location of the two.<br />
4. Finally, the total distance is calculated and the total waiting time for each driver is calculated using an average assigned speed.
5. We also display the amount of distance traveled if only one ride would be assigned to one car.and the diff if car sharing is opted.

# Running the project
1. The main file of project is "Car Sharing with 2 users assigned One ride (Uniform Data).cpp"
2. compiler and run this file with your favourate c++ compiler. this should gererate the output in a seperate output fine in the same directory. For g++ the command would be
````
g++ "Car Sharing with 2 users assigned One ride (Uniform Data).cpp"
````
3. We also tried assigning 3 riders to single ride but we kept running out of space of big values of rides and assignments
this could be run using command
````
g++ "Algo(3 cars assignment) Without File Handeling final (1).cpp"
````
# Future-Work
1. Currently, it is assumed a straight line distance between two points. We could work on implementing road networks into the program to give a more realistic output.
2. We would need to optimize the program for 3 rider assignemet to support bigger values
3. Currently, the program pre-allocates rides and costumer location. We could integrate code such that new incoming requests could be simultaneously allocated to cars while the ride is currently in progress to make the program real-time compatible. 

# Thank-you-for-visiting
