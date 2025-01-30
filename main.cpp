#include <iostream>
#include <iomanip> //setw
#include <cmath> //sin, cos
#include <stdlib.h> //atoi
using namespace std;

double deg2rad(double degrees){
    double radians = degrees*(M_PI/180);
    return radians;
}
double haversine(double lat1, double long1, double lat2, double long2, double radius){
    //cout << lat1 << endl << long1 << endl << lat2 << endl << long2 << endl;
    double delta_lat = (lat2 - lat1);
    double delta_long = (long2 - long1);
    double a = pow(sin(delta_lat/2), 2) + cos(lat1)*cos(lat2)*pow(sin(delta_long/2), 2);
    double distance_miles = 2*radius*asin(sqrt(a));
    return distance_miles;
}
double getFlightTime(double lat1, double long1, double lat2, double long2){
    const double EARTH_RADIUS_MILES = 3958.8;
    double flightDistance = haversine(lat1, long1, lat2, long2, EARTH_RADIUS_MILES); // in miles
    const double FLIGHT_SPEED = 500; //miles per hour
    double flightTime = flightDistance / FLIGHT_SPEED;
    return flightTime;
}

int main(){
    //Generate location array
    int amtLocation = 10;
    const int locationIndex[amtLocation] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const string locations[amtLocation] = 
        {"Los Angeles, CA, USA", "New York, NY, USA", "Winston-Salem, NC, USA", "Lansing, MI, USA", "Charlotte, NC, USA",
         "Dayton, OH, USA", "Paris, France", "London, United Kingdom", "Naples, Italy", "Berlin, Germany"};
    const double latitudes[amtLocation] = 
        {34.0549, 40.7128, 36.0999, 42.7325, 35.2271, 
        39.7589, 48.8575, 51.5072, 40.8518, 52.5200};
    const double longitudes[amtLocation] = 
        {-118.2426, -74.0060, -80.2442, -84.5555, -80.8431, 
        -84.1916, 2.3514, 0.1276, 14.3326, 13.4050};
    
    //Output location array to user for first selection.
    cout << left;
    for (size_t i = 0; i < amtLocation; i++){
        cout << setw(2) << locationIndex[i] << ". " << setw(30) << locations[i] << latitudes[i] << ", " << longitudes[i] << "\n";
    }


    //First location
    cout << "Please make a selection. \n";
    string input;
    cin >> input;
    int userSelection1 = atoi(input.c_str()) - 1;
    while (userSelection1 >= 10  || userSelection1 < 0){
        cout << "Please select a number from the list. \n";
        cin >> input;
        userSelection1 = atoi(input.c_str());
    }

    //Output the array table without the user's first selection.
    int index = 0;
    for (size_t i = 0; i < amtLocation; i++){
        if (i != userSelection1){
            cout << setw(2) << locationIndex[index] << ". " << setw(30) << locations[i] << latitudes[i] << ", " << longitudes[i] << "\n";
            index++;
        }
    }

    //Second location
    cout << "Please make a second selection. \n";
    cin >> input;
    int userSelection2 = atoi(input.c_str()) - 1;
    while (userSelection2 >= 9  || userSelection2 < 0){
        cout << "Please select a number from the list. \n";
        cin >> input;
        userSelection2 = atoi(input.c_str());
    }
    if (userSelection2 >= userSelection1)
        userSelection2++;
    

    //Prepare arguments for the haversine function.
    double lat1, lat2, long1, long2;
    lat1 = deg2rad(latitudes[userSelection1]);
    long1 = deg2rad(longitudes[userSelection1]);
    lat2 = deg2rad(latitudes[userSelection2]);
    long2 = deg2rad(longitudes[userSelection2]);
    double flightHours = getFlightTime(lat1, long1, lat2, long2);

    //Output flight time.
    cout << flightHours << " hours between " << locations[userSelection1] << " and " << locations[userSelection2] <<  ". \n";
    system("pause");
    return 0;
}