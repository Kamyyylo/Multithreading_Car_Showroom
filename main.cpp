#include <iostream>
#include <stdlib.h>
#include <queue>
#include <thread>
#include <mutex>
#include <chrono>
#include <ctime>
#include <ncurses.h>
#include <string>
#include <iomanip>
#include <condition_variable>
#include <atomic>
#include <sstream>

using namespace std;

// Miejsca dla moich aut w salonach <3
class Car
{
public:
    int id;
    string carName;
    int state;
    string order;
    int carShowroom;
    int progress;
    Car(int i, string m, int s, int p) {
        id = i;
        carName = m;
        state = s;
        progress = p;
    }
};
class Mechanic
{
public:
    int id;
    string MechanicName;
    int state;
    string carName;
    int progress;
    Mechanic(int i,string name, string car, int s, int p)
    {
        id = i;
        MechanicName = name;
        carName = car;
        state = s;
        progress = p;
    }
};
class TowTruck
{
public:
    int id;
    string carName;
    int carId;
    int state;
    int progress;
    TowTruck(int i,int car_id, string name, int s, int p)
    {
        id = i;
        carId = car_id;
        carName = name;
        state = s;
        progress = p;
    }
};
class Space
{
public:
    int id;
    int spaceNumber;
    int saloonNumber;
    string carName;
    int carId;
    int state;
    int progress;
    Space(int i,int space,int saloon, int car_id, string name, int s,int p)
    {
        id =i;
        spaceNumber = space;
        saloonNumber = saloon;
        carId = car_id;
        carName = name;
        state = s;
        progress =p;
    }
};
//zmienne globalne
atomic<bool> force_end{false};
int truckNumber=0;
int washProgress=0;
bool flag = false;
bool tinsmith = false;
bool fitter = false;
bool spraying = false;
bool vulcanizer = false;
bool electrician = false;
bool towTruck_1Bool = false;
bool towTruck_2Bool = false;
bool towTruck_3Bool = false;
bool space_1Bool= false;
bool space_2Bool= false;
bool space_3Bool= false;
bool space_4Bool= false;
bool space_5Bool= false;
bool space_6Bool= false;
bool space_7Bool= false;
bool space_8Bool= false;
bool space_9Bool= false;
bool washBool= false;


//zmienne warunkowe
condition_variable cvTinsmith;
condition_variable cvFitter;
condition_variable cvSpraying;
condition_variable cvVulcanizer;
condition_variable cvElectrician;
condition_variable cvTowTruck_1;
condition_variable cvTowTruck_2;
condition_variable cvTowTruck_3;
condition_variable cvSpace_1;
condition_variable cvSpace_2;
condition_variable cvSpace_3;
condition_variable cvSpace_4;
condition_variable cvSpace_5;
condition_variable cvSpace_6;
condition_variable cvSpace_7;
condition_variable cvSpace_8;
condition_variable cvSpace_9;
//Zasoby
vector <Car> carsVec;
vector <Mechanic> mainMechanicVec;
vector <Mechanic> tinsmithVec;
vector <Mechanic> fitterVec;
vector <Mechanic> sprayingVec;
vector <Mechanic> vulcanizerVec;
vector <Mechanic> electricianVec;
vector <TowTruck> towTruck_1Vec;
vector <TowTruck> towTruck_2Vec;
vector <TowTruck> towTruck_3Vec;
vector <Space> saloon_1Vec;
vector <Space> saloon_2Vec;
vector <Space> saloon_3Vec;
vector <Space> boughtCarsVec;

//Mutex
mutex mxOrders;
mutex mxTinsmith;
mutex mxFitter;
mutex mxSpraying;
mutex mxVulcanizer;
mutex mxElectrician;
mutex mxTowTruck_1;
mutex mxTowTruck_2;
mutex mxTowTruck_3;
mutex mxSpace_1;
mutex mxSpace_2;
mutex mxSpace_3;
mutex mxSpace_4;
mutex mxSpace_5;
mutex mxSpace_6;
mutex mxSpace_7;
mutex mxSpace_8;
mutex mxSpace_9;
mutex mxBlockSaloon;
mutex mxTowTruckMutex;
mutex mxCheckSizeMutex;
mutex mxCheckSizeMutex2;
mutex mxCheckSizeMutex3;
mutex mxCheckSizeMutex4;
mutex tinsmithMutex;
mutex fitterMutex;
mutex sprayerMutex;
mutex vulcanizerMutex;
mutex electricianMutex;

//Zmienne tablicowe
string cars[14] = { "Vectra", "Maluch", "Polonez", "Scigacz", "Golf 4", "Passat B5", "Passat B6", "BMW M3", "Mazda 6", "Fiesta", "Fiat 600", "Audi A5", "Seat Leon", "Yaris" };

//funkcje
void takeOrders();
void Ncurses();
void listenForEscapeKey(atomic<bool>& switch_ref);
void mainMechanicActions();
void tinsmithActions();
void fitterActions();
void sprayingActions();
void vulcanizerActions();
void electricianActions();
void towTruck_1Actions();
void towTruck_2Actions();
void towTruck_3Actions();
void space_1Actions();
void space_2Actions();
void space_3Actions();
void space_4Actions();
void space_5Actions();
void space_6Actions();
void space_7Actions();
void space_8Actions();
void space_9Actions();
void washActions();

int main() {

    //Watki
    thread NCurses(Ncurses);
    thread carOrders(takeOrders);
    thread mainMechanic(mainMechanicActions);
    thread tinsmith(tinsmithActions);
    thread fitter(fitterActions);
    thread spraying(sprayingActions);
    thread vulcanizer(vulcanizerActions);
    thread electrician(electricianActions);
    thread towTruck_1(towTruck_1Actions);
    thread towTruck_2(towTruck_2Actions);
    thread towTruck_3(towTruck_3Actions);
    thread space_1(space_1Actions);
    thread space_2(space_2Actions);
    thread space_3(space_3Actions);
    thread space_4(space_4Actions);
    thread space_5(space_5Actions);
    thread space_6(space_6Actions);
    thread space_7(space_7Actions);
    thread space_8(space_8Actions);
    thread space_9(space_9Actions);
    thread wash(washActions);


    NCurses.join();
    carOrders.join();
    mainMechanic.join();
    tinsmith.join();
    fitter.join();
    spraying.join();
    vulcanizer.join();
    electrician.join();
    towTruck_1.join();
    towTruck_2.join();
    towTruck_3.join();
    space_1.join();
    space_2.join();
    space_3.join();
    space_4.join();
    space_5.join();
    space_6.join();
    space_7.join();
    space_8.join();
    space_9.join();
    wash.join();

    return 0;
}
//Tworzy nowe zamowienia na auta
void takeOrders()
{
    int iterator=0;
    srand ( time(NULL) );
    do{
        if(flag==false){
            if(carsVec.size()>3){
                flag =true;
            }
            else{
                    Car carSpaces (iterator++,cars[(rand() % 14) +0], 1,0);
                    mxOrders.lock();
                    carsVec.push_back(carSpaces);
                    mxOrders.unlock();
                    for(int i=1;i<=10;i++)
                    {
                        this_thread::sleep_for(std::chrono::milliseconds(40));
                        carsVec.back().progress++;
                    }

            }
        }
    } while(!force_end);
}
void mainMechanicActions()
{
    int iterator=0;
    do {
        if(flag==true){


            Mechanic mainMechanic(iterator++, "Main mechanic", carsVec.front().carName, 2,0);
            mxOrders.lock();
            mainMechanicVec.push_back(mainMechanic);
            carsVec.erase(carsVec.begin());

            for(int i=1;i<=10;i++)
            {
                this_thread::sleep_for(std::chrono::milliseconds(50));
                mainMechanicVec.back().progress++;
            }
            mainMechanicVec.back().state=3;
            flag=false;
        if(mainMechanicVec.size() >= 5 ){
            tinsmith = true;
            cvTinsmith.notify_one();
            mxOrders.unlock();
        }
            mxOrders.unlock();
        }
    }while(!force_end);
}
void tinsmithActions()
{ int iterator=0;
    do{

        if(tinsmithVec.size() >= 5){
            fitter = true;
            cvFitter.notify_one();
            tinsmithMutex.unlock();
        }
        tinsmithMutex.lock();
        if(mainMechanicVec.size()>0){
            tinsmithMutex.unlock();
            unique_lock<mutex> locker(mxTinsmith);
            cvTinsmith.wait(locker, [] {return tinsmith;});
            Mechanic tinsmithMech(iterator++,"Tinsmith", mainMechanicVec.front().carName,2,0);
            tinsmithVec.push_back(tinsmithMech);
            mainMechanicVec.erase(mainMechanicVec.begin());
            locker.unlock();
            for(int i=1;i<=10;i++)
            {
                this_thread::sleep_for(std::chrono::milliseconds(90));
                tinsmithVec.back().progress++;
            }

            tinsmithVec.back().state=3;
        }else tinsmithMutex.unlock();

    }while(!force_end);

}
void fitterActions()
{ int iterator=0;
    do{
        if(fitterVec.size() >= 5){
            spraying = true;
            cvSpraying.notify_one();
        }
        fitterMutex.lock();
        if(tinsmithVec.size()>0){
            fitterMutex.unlock();
            unique_lock<mutex> locker(mxFitter);
            cvFitter.wait(locker, [] {return fitter;});
            Mechanic fitterMech(iterator++,"Fitter", tinsmithVec.front().carName,2,0);
            fitterVec.push_back(fitterMech);
            tinsmithVec.erase(tinsmithVec.begin());
            locker.unlock();
            for(int i=1;i<=10;i++)
            {
                this_thread::sleep_for(std::chrono::milliseconds(95));
                fitterVec.back().progress++;
            }

            fitterVec.back().state=3;
        }else fitterMutex.unlock();
    }while(!force_end);
}
void sprayingActions()
{ int iterator=0;
    do{
        if(sprayingVec.size() >= 5){
            vulcanizer = true;
            cvVulcanizer.notify_one();
        }
        sprayerMutex.lock();
        if(fitterVec.size()>0){
            sprayerMutex.unlock();
            unique_lock<mutex> locker(mxSpraying);
            cvSpraying.wait(locker, [] {return spraying;});
            Mechanic sprayingMech(iterator++,"Sprayer", fitterVec.front().carName,2,0);
            sprayingVec.push_back(sprayingMech);
            fitterVec.erase(fitterVec.begin());
            locker.unlock();
            for(int i=1;i<=10;i++)
            {
                this_thread::sleep_for(std::chrono::milliseconds(100));
                sprayingVec.back().progress++;
            }

            sprayingVec.back().state=3;
        }else sprayerMutex.unlock();
    }while(!force_end);
}
void vulcanizerActions()
{ int iterator=0;
    do{
        if(vulcanizerVec.size() >= 5) {
            electrician = true;
            cvElectrician.notify_one();
        }
        vulcanizerMutex.lock();
        if(sprayingVec.size()>0){
            vulcanizerMutex.unlock();
            unique_lock<mutex> locker(mxVulcanizer);
            cvVulcanizer.wait(locker, [] {return vulcanizer;});
            Mechanic vulcanizerMech(iterator++,"vulcanizer", sprayingVec.front().carName,2,0);
            vulcanizerVec.push_back(vulcanizerMech);
            sprayingVec.erase(sprayingVec.begin());
            locker.unlock();
            for(int i=1;i<=10;i++)
            {
                this_thread::sleep_for(std::chrono::milliseconds(105));
                vulcanizerVec.back().progress++;
            }

            vulcanizerVec.back().state=3;
        }else  vulcanizerMutex.unlock();

    }while(!force_end);
}
void electricianActions()
{ int iterator=0;
    do{
            if(electricianVec.size()>=5){
                towTruck_1Bool = true;
                towTruck_2Bool = true;
                towTruck_3Bool = true;
                cvTowTruck_1.notify_all();
                cvTowTruck_2.notify_all();
                cvTowTruck_3.notify_all();
            }
            electricianMutex.lock();
            if(vulcanizerVec.size()>0){
                electricianMutex.unlock();
                unique_lock<mutex> locker(mxElectrician);
                cvElectrician.wait(locker, [] {return electrician;});
                Mechanic electricianMech(iterator++,"electrician", vulcanizerVec.front().carName,2,0);
                electricianVec.push_back(electricianMech);
                vulcanizerVec.erase(vulcanizerVec.begin());
                for(int i=1;i<=10;i++)
                {
                    this_thread::sleep_for(std::chrono::milliseconds(110));
                    electricianVec.back().progress++;
                }

                electricianVec.back().state=3;
            }else   electricianMutex.unlock();


    }while(!force_end);
}
void towTruck_1Actions()
{int iterator =0 ;
do{
    mxCheckSizeMutex.lock();
    if(towTruck_1Vec.size()>=3){
        towTruck_1Bool=false;
        space_1Bool=true;
        space_2Bool = true;
        space_3Bool = true;
        cvSpace_1.notify_all();
        cvSpace_2.notify_all();
        cvSpace_3.notify_all();
        mxCheckSizeMutex.unlock();
    }
    else{
        mxCheckSizeMutex.unlock();
        unique_lock<mutex> locker(mxTowTruck_1);
        cvTowTruck_1.wait(locker, [] {return towTruck_1Bool;});
        mxTowTruckMutex.lock();
        TowTruck towTruck_1(iterator++,electricianVec.front().id, electricianVec.front().carName, 2,0);
        towTruck_1Vec.push_back(towTruck_1);
        electricianVec.erase(electricianVec.begin());
        for(int i=0;i<=10;i++)
        {
            this_thread::sleep_for(std::chrono::milliseconds(70));
            towTruck_1Vec.back().progress++;
        }
        towTruck_1Vec.back().state=3;
        towTruck_1Bool=false;
        mxTowTruckMutex.unlock();
    }

}while(!force_end);
}
void towTruck_2Actions()
{int iterator =0 ;
    do{
        mxCheckSizeMutex.lock();
        if(towTruck_2Vec.size()>=3){
            towTruck_2Bool=false;
            space_4Bool=true;
            space_5Bool = true;
            space_6Bool = true;
            cvSpace_4.notify_all();
            cvSpace_5.notify_all();
            cvSpace_6.notify_all();
            mxCheckSizeMutex.unlock();
        }else{
            mxCheckSizeMutex.unlock();
            unique_lock<mutex> locker(mxTowTruck_2);
            cvTowTruck_2.wait(locker, [] {return towTruck_2Bool;});
            mxTowTruckMutex.lock();
            TowTruck towTruck_2(iterator++,electricianVec.front().id, electricianVec.front().carName, 2,0);
            towTruck_2Vec.push_back(towTruck_2);
            electricianVec.erase(electricianVec.begin());
            for(int i=0;i<=10;i++)
            {
                this_thread::sleep_for(std::chrono::milliseconds(80));
                towTruck_2Vec.back().progress++;
            }
            towTruck_2Vec.back().state=3;
            towTruck_2Bool=false;
            mxTowTruckMutex.unlock();

        }


    }while(!force_end);
}
void towTruck_3Actions()
{int iterator =0 ;
    do{
        mxCheckSizeMutex.lock();
        if(towTruck_3Vec.size()>=3){
            towTruck_3Bool=false;
            space_7Bool=true;
            space_8Bool = true;
            space_9Bool = true;
            cvSpace_7.notify_all();
            cvSpace_8.notify_all();
            cvSpace_9.notify_all();
            mxCheckSizeMutex.unlock();
        }else{
            mxCheckSizeMutex.unlock();
            unique_lock<mutex> locker(mxTowTruck_3);
            cvTowTruck_3.wait(locker, [] {return towTruck_3Bool;});
            mxTowTruckMutex.lock();
            TowTruck towTruck_3(iterator++,electricianVec.front().id, electricianVec.front().carName, 2,0);
            towTruck_3Vec.push_back(towTruck_3);
            electricianVec.erase(electricianVec.begin());
            for(int i=0;i<=10;i++)
            {
                this_thread::sleep_for(std::chrono::milliseconds(95));
                towTruck_3Vec.back().progress++;
            }
            towTruck_3Vec.back().state=3;
            towTruck_3Bool=false;
            mxTowTruckMutex.unlock();
        }

    }while(!force_end);
}

void space_1Actions()
{ int iterator=0;
do{
    mxCheckSizeMutex2.lock();
    if(towTruck_1Vec.size()>0){
        mxCheckSizeMutex2.unlock();
        unique_lock<mutex> locker (mxSpace_1);
        cvSpace_1.wait(locker, [] {return space_1Bool;});
        mxBlockSaloon.lock();
        Space space_1(iterator ++,1,1,towTruck_1Vec.front().carId, towTruck_1Vec.front().carName,2,0 );

        saloon_1Vec.push_back(space_1);
        towTruck_1Vec.erase(towTruck_1Vec.begin());
        for(int i=0;i<=10;i++)
        {
            this_thread::sleep_for(std::chrono::milliseconds(50));
            saloon_1Vec.back().progress++;
        }
        saloon_1Vec.back().state=3;

        saloon_1Vec.back().progress=0;
        for(int i=0;i<=10;i++)
        {
            this_thread::sleep_for(std::chrono::milliseconds(100));
            saloon_1Vec.back().progress++;
        }
        boughtCarsVec.push_back(saloon_1Vec.front());
        saloon_1Vec.erase(saloon_1Vec.begin());

        if(boughtCarsVec.size()>30)
        {
            boughtCarsVec.erase(boughtCarsVec.begin());
        }
        truckNumber=1;
        washBool=true;
        this_thread::sleep_for(std::chrono::milliseconds(1000));
       space_1Bool=false;
        mxBlockSaloon.unlock();
    }mxCheckSizeMutex2.unlock();

    }while(!force_end);
}
void space_2Actions()
{int iterator=0;
    do{
        mxCheckSizeMutex2.lock();
        if(towTruck_1Vec.size()>0){
            mxCheckSizeMutex2.unlock();
            unique_lock<mutex> locker (mxSpace_2);
            cvSpace_2.wait(locker, [] {return space_2Bool;});
            mxBlockSaloon.lock();
            Space space_2(iterator ++,2,1,towTruck_1Vec.front().carId, towTruck_1Vec.front().carName,2,0 );

            saloon_1Vec.push_back(space_2);
            towTruck_1Vec.erase(towTruck_1Vec.begin());

            for(int i=0;i<=10;i++)
            {
                this_thread::sleep_for(std::chrono::milliseconds(55));
                saloon_1Vec.back().progress++;
            }
            saloon_1Vec.back().state=3;
            saloon_1Vec.back().progress=0;
            for(int i=0;i<=10;i++)
            {
                this_thread::sleep_for(std::chrono::milliseconds(110));
                saloon_1Vec.back().progress++;
            }
            boughtCarsVec.push_back(saloon_1Vec.front());
            saloon_1Vec.erase(saloon_1Vec.begin());
            if(boughtCarsVec.size()>30)
            {
                boughtCarsVec.erase(boughtCarsVec.begin());
            }
            truckNumber=1;
            washBool=true;
            this_thread::sleep_for(std::chrono::milliseconds(1000));
            space_2Bool=false;
            mxBlockSaloon.unlock();
        }mxCheckSizeMutex2.unlock();


    }while(!force_end);
}
void space_3Actions()
{
    int iterator=0;
    do{
        mxCheckSizeMutex2.lock();
        if(towTruck_1Vec.size()>0){
            mxCheckSizeMutex2.unlock();
            unique_lock<mutex> locker (mxSpace_3);
            cvSpace_3.wait(locker, [] {return space_3Bool;});
            mxBlockSaloon.lock();
            Space space_3(iterator ++,3,1,towTruck_1Vec.front().carId, towTruck_1Vec.front().carName,2,0 );

            saloon_1Vec.push_back(space_3);
            towTruck_1Vec.erase(towTruck_1Vec.begin());
            for(int i=0;i<=10;i++)
            {
                this_thread::sleep_for(std::chrono::milliseconds(60));
                saloon_1Vec.back().progress++;
            }
            saloon_1Vec.back().state=3;
            saloon_1Vec.back().progress=0;
            for(int i=0;i<=10;i++)
            {
                this_thread::sleep_for(std::chrono::milliseconds(120));
                saloon_1Vec.back().progress++;
            }
            boughtCarsVec.push_back(saloon_1Vec.front());
            saloon_1Vec.erase(saloon_1Vec.begin());
            if(boughtCarsVec.size()>30)
            {
                boughtCarsVec.erase(boughtCarsVec.begin());
            }
            truckNumber=1;
            washBool=true;
            this_thread::sleep_for(std::chrono::milliseconds(1000));
            space_3Bool=false;
            mxBlockSaloon.unlock();
        }mxCheckSizeMutex2.unlock();

    }while(!force_end);
}
void space_4Actions()
{
    int iterator=0;
    do{
        mxCheckSizeMutex3.lock();
        if(towTruck_2Vec.size()>0){
            mxCheckSizeMutex3.unlock();
            unique_lock<mutex> locker (mxSpace_4);
            cvSpace_4.wait(locker, [] {return space_4Bool;});
            mxBlockSaloon.lock();
            Space space_4(iterator ++,4,2,towTruck_2Vec.front().carId, towTruck_2Vec.front().carName,2,0 );

            saloon_2Vec.push_back(space_4);
            towTruck_2Vec.erase(towTruck_2Vec.begin());
            for(int i=0;i<=10;i++)
            {
                this_thread::sleep_for(std::chrono::milliseconds(65));
                saloon_2Vec.back().progress++;
            }
            saloon_2Vec.back().state=3;
            saloon_2Vec.back().progress=0;
            for(int i=0;i<=10;i++)
            {
                this_thread::sleep_for(std::chrono::milliseconds(130));
                saloon_2Vec.back().progress++;
            }
            boughtCarsVec.push_back(saloon_2Vec.front());
            saloon_2Vec.erase(saloon_2Vec.begin());
            if(boughtCarsVec.size()>30)
            {
                boughtCarsVec.erase(boughtCarsVec.begin());
            }
            truckNumber=2;
            washBool=true;
            this_thread::sleep_for(std::chrono::milliseconds(1000));
            space_4Bool=false;
            mxBlockSaloon.unlock();
        } mxCheckSizeMutex3.unlock();

    }while(!force_end);
}
void space_5Actions()
{
    int iterator=0;
    do{
        mxCheckSizeMutex3.lock();
        if(towTruck_2Vec.size()>0){
            mxCheckSizeMutex3.unlock();
            unique_lock<mutex> locker (mxSpace_5);
            cvSpace_5.wait(locker, [] {return space_5Bool;});
            mxBlockSaloon.lock();
            Space space_5(iterator ++,5,2,towTruck_2Vec.front().carId, towTruck_2Vec.front().carName,2,0 );

            saloon_2Vec.push_back(space_5);
            towTruck_2Vec.erase(towTruck_2Vec.begin());
            for(int i=0;i<=10;i++)
            {
                this_thread::sleep_for(std::chrono::milliseconds(70));
                saloon_2Vec.back().progress++;
            }
            saloon_2Vec.back().state=3;
            saloon_2Vec.back().progress=0;
            for(int i=0;i<=10;i++)
            {
                this_thread::sleep_for(std::chrono::milliseconds(140));
                saloon_2Vec.back().progress++;
            }
            boughtCarsVec.push_back(saloon_2Vec.front());
            saloon_2Vec.erase(saloon_2Vec.begin());
            if(boughtCarsVec.size()>30)
            {
                boughtCarsVec.erase(boughtCarsVec.begin());
            }
            truckNumber=2;
            washBool=true;
            this_thread::sleep_for(std::chrono::milliseconds(1000));
            space_5Bool=false;
            mxBlockSaloon.unlock();
        } mxCheckSizeMutex3.unlock();

    }while(!force_end);
}
void space_6Actions()
{
    int iterator=0;
    do{
        mxCheckSizeMutex3.lock();
        if(towTruck_2Vec.size()>0){
            mxCheckSizeMutex3.unlock();

            unique_lock<mutex> locker (mxSpace_6);
            cvSpace_6.wait(locker, [] {return space_6Bool;});
            mxBlockSaloon.lock();
            Space space_6(iterator ++,6,2,towTruck_2Vec.front().carId, towTruck_2Vec.front().carName,2,0 );
            saloon_2Vec.push_back(space_6);
            towTruck_2Vec.erase(towTruck_2Vec.begin());
            for(int i=0;i<=10;i++)
            {
                this_thread::sleep_for(std::chrono::milliseconds(75));
                saloon_2Vec.back().progress++;
            }
            saloon_2Vec.back().state=3;
            saloon_2Vec.back().progress=0;
            for(int i=0;i<=10;i++)
            {
                this_thread::sleep_for(std::chrono::milliseconds(150));
                saloon_2Vec.back().progress++;
            }
            boughtCarsVec.push_back(saloon_2Vec.front());
            saloon_2Vec.erase(saloon_2Vec.begin());
            if(boughtCarsVec.size()>30)
            {
                boughtCarsVec.erase(boughtCarsVec.begin());
            }
            truckNumber=2;
            washBool=true;
            this_thread::sleep_for(std::chrono::milliseconds(1000));
            space_6Bool=false;
            mxBlockSaloon.unlock();
        } mxCheckSizeMutex3.unlock();

    }while(!force_end);
}
void space_7Actions()
{
    int iterator=0;
    do{
        mxCheckSizeMutex4.lock();
        if(towTruck_3Vec.size()>0){
            mxCheckSizeMutex4.unlock();
            unique_lock<mutex> locker (mxSpace_7);
            cvSpace_7.wait(locker, [] {return space_7Bool;});
            mxBlockSaloon.lock();
            Space space_7(iterator ++,7,3,towTruck_3Vec.front().carId, towTruck_3Vec.front().carName,2,0 );
            saloon_3Vec.push_back(space_7);
            towTruck_3Vec.erase(towTruck_3Vec.begin());
            for(int i=0;i<=10;i++)
            {
                this_thread::sleep_for(std::chrono::milliseconds(80));
                saloon_3Vec.back().progress++;
            }
            saloon_3Vec.back().state=3;
            saloon_3Vec.back().progress=0;
            for(int i=0;i<=10;i++)
            {
                this_thread::sleep_for(std::chrono::milliseconds(160));
                saloon_3Vec.back().progress++;
            }
            boughtCarsVec.push_back(saloon_3Vec.front());
            saloon_3Vec.erase(saloon_3Vec.begin());
            if(boughtCarsVec.size()>30)
            {
                boughtCarsVec.erase(boughtCarsVec.begin());
            }
            truckNumber=3;
            washBool=true;
            this_thread::sleep_for(std::chrono::milliseconds(1000));
            space_7Bool=false;
            mxBlockSaloon.unlock();
        }mxCheckSizeMutex4.unlock();

    }while(!force_end);
}
void space_8Actions()
{
    int iterator=0;
    do{
        mxCheckSizeMutex4.lock();
        if(towTruck_3Vec.size()>0){
            mxCheckSizeMutex4.unlock();
            unique_lock<mutex> locker (mxSpace_8);
            cvSpace_8.wait(locker, [] {return space_8Bool;});
            mxBlockSaloon.lock();
            Space space_8(iterator ++,8,3,towTruck_3Vec.front().carId, towTruck_3Vec.front().carName,2,0 );
            saloon_3Vec.push_back(space_8);
            towTruck_3Vec.erase(towTruck_3Vec.begin());
            for(int i=0;i<=10;i++)
            {
                this_thread::sleep_for(std::chrono::milliseconds(85));
                saloon_3Vec.back().progress++;
            }
            saloon_3Vec.back().state=3;
            saloon_3Vec.back().progress=0;
            for(int i=0;i<=10;i++)
            {
                this_thread::sleep_for(std::chrono::milliseconds(170));
                saloon_3Vec.back().progress++;
            }
            boughtCarsVec.push_back(saloon_3Vec.front());
            saloon_3Vec.erase(saloon_3Vec.begin());
            if(boughtCarsVec.size()>30)
            {
                boughtCarsVec.erase(boughtCarsVec.begin());
            }
            truckNumber=3;
            washBool=true;
            this_thread::sleep_for(std::chrono::milliseconds(1000));
            space_8Bool=false;
            mxBlockSaloon.unlock();
        }mxCheckSizeMutex4.unlock();

    }while(!force_end);
}
void space_9Actions()
{
    int iterator=0;
    do{
        mxCheckSizeMutex4.lock();
        if(towTruck_3Vec.size()>0){
            mxCheckSizeMutex4.unlock();
            unique_lock<mutex> locker (mxSpace_9);
            cvSpace_9.wait(locker, [] {return space_9Bool;});
            mxBlockSaloon.lock();
            Space space_9(iterator ++,9,3,towTruck_3Vec.front().carId, towTruck_3Vec.front().carName,2,0 );
            saloon_3Vec.push_back(space_9);
            towTruck_3Vec.erase(towTruck_3Vec.begin());
            for(int i=0;i<=10;i++)
            {
                this_thread::sleep_for(std::chrono::milliseconds(90));
                saloon_3Vec.back().progress++;
            }
            saloon_3Vec.back().state=3;
            saloon_3Vec.back().progress=0;
            for(int i=0;i<=10;i++)
            {
                this_thread::sleep_for(std::chrono::milliseconds(180));
                saloon_3Vec.back().progress++;
            }
            boughtCarsVec.push_back(saloon_3Vec.front());
            saloon_3Vec.erase(saloon_3Vec.begin());
            if(boughtCarsVec.size()>25)
            {
                boughtCarsVec.erase(boughtCarsVec.begin());
            }
            truckNumber=3;
            washBool=true;
            this_thread::sleep_for(std::chrono::milliseconds(1000));
            space_9Bool=false;
            mxBlockSaloon.unlock();
        }mxCheckSizeMutex4.unlock();

    }while(!force_end);
}

void washActions()
{
    do{
        if(washBool==true)
        {
            for(int i=1;i<=10;i++)
            {
                this_thread::sleep_for(std::chrono::milliseconds(100));
                washProgress++;
            }
            washProgress=0;
            washBool=false;
        }
    }while(!force_end);

}

//RYSOWANIE
void printOrders(WINDOW *win)
{   mvwprintw(win,1,1,"Id|Car       |Status");
    wrefresh(win);
    string progress;
    for(int i=0;i<10;i++)
    {
        mvwprintw(win,i+2,1,"                                         ");
    }
    wattron(win,COLOR_PAIR(6));
    for(int i=0;i<(int)carsVec.size();i++){
        if(i==10)
            break;
        else{
            if(carsVec[i].progress==0)
                    progress = "|";
                if(carsVec[i].progress==1)
                    progress = "|||";
                if(carsVec[i].progress==3)
                    progress = "|||||";
                if(carsVec[i].progress==4)
                    progress = "|||||||";
                if(carsVec[i].progress==5)
                    progress = "|||||||||";
                if(carsVec[i].progress==6)
                    progress = "|||||||||||";
                if(carsVec[i].progress==7)
                    progress = "|||||||||||||";
                if(carsVec[i].progress==8)
                    progress = "|||||||||||||||";
                if(carsVec[i].progress==9)
                    progress = "|||||||||||||||||";
                if(carsVec[i].progress==10)
                    progress = "                   ";
            mvwprintw(win,i+2,1,"%2d|%-10s|Ordered %s",carsVec[i].id, carsVec[i].carName.c_str(), progress.c_str());
            wrefresh(win);
        };

    }wattroff(win,COLOR_PAIR(6));

}


string printMechanicProgress(vector<Mechanic> mechanic, int i)
{
    string progress;
    if(mechanic[i].progress==0)
        progress = "|";
    if(mechanic[i].progress==1)
        progress = "|||";
    if(mechanic[i].progress==3)
        progress = "|||||";
    if(mechanic[i].progress==4)
        progress = "|||||||";
    if(mechanic[i].progress==5)
        progress = "|||||||||";
    if(mechanic[i].progress==6)
        progress = "|||||||||||";
    if(mechanic[i].progress==7)
        progress = "|||||||||||||";
    if(mechanic[i].progress==8)
        progress = "|||||||||||||||";
    if(mechanic[i].progress==9)
        progress = "|||||||||||||||||";
    if(mechanic[i].progress==10)
        progress = "                   ";

    return progress;
}
string printTowTruckProgress(vector<TowTruck> towtruck, int i)
{
    string progress;
    if(towtruck[i].progress==0)
        progress = "|";
    if(towtruck[i].progress==1)
        progress = "|||";
    if(towtruck[i].progress==3)
        progress = "|||||";
    if(towtruck[i].progress==4)
        progress = "|||||||";
    if(towtruck[i].progress==5)
        progress = "|||||||||";
    if(towtruck[i].progress==6)
        progress = "|||||||||||";
    if(towtruck[i].progress==7)
        progress = "|||||||||||||";
    if(towtruck[i].progress==8)
        progress = "|||||||||||||||";
    if(towtruck[i].progress==9)
        progress = "|||||||||||||||||";
    if(towtruck[i].progress==10)
        progress = "                   ";

    return progress;
}
string printSaloonProgress(vector<Space> saloon, int i)
{
    string progress;
    if(saloon[i].progress==0)
        progress = "|";
    if(saloon[i].progress==1)
        progress = "|||";
    if(saloon[i].progress==3)
        progress = "|||||";
    if(saloon[i].progress==4)
        progress = "|||||||";
    if(saloon[i].progress==5)
        progress = "|||||||||";
    if(saloon[i].progress==6)
        progress = "|||||||||||";
    if(saloon[i].progress==7)
        progress = "|||||||||||||";
    if(saloon[i].progress==8)
        progress = "|||||||||||||||";
    if(saloon[i].progress==9)
        progress = "|||||||||||||||||";
    if(saloon[i].progress==10)
        progress = "                   ";

    return progress;
}
void printMainMechanicActions(WINDOW *win)
{

    mvwprintw(win,1,1,"Id|Car       |Main Mechanic Status");
    wrefresh(win);
    string stan;
    string progress;
    for(int i=0;i<16;i++)
    {
        mvwprintw(win,i+2,1,"                                               ");
    }

    for (int i = 0; i < (int)mainMechanicVec.size(); i++) {
        if(i==16)
            break;
        else{
            if (mainMechanicVec[i].state == 2) {
                progress= printMechanicProgress(mainMechanicVec, i);
                wattron(win,COLOR_PAIR(4));
                stan = "Got order";
                mvwprintw(win,i+2,1,"%2d|%-10s|%-15s %s",mainMechanicVec[i].id, mainMechanicVec[i].carName.c_str(), stan.c_str(), progress.c_str());
                wrefresh(win);
                wattroff(win,COLOR_PAIR(4));
            }
            else if(mainMechanicVec[i].state == 3){
                wattron(win,COLOR_PAIR(7));
                stan = "Go to tinsmith";
                mvwprintw(win,i+2,1,"%2d|%-10s|%-15s",mainMechanicVec[i].id, mainMechanicVec[i].carName.c_str(), stan.c_str());
                wattroff(win,COLOR_PAIR(7));
                wrefresh(win);
            }
        }

    }

}
void printTinsmith(WINDOW * win)
{
    mvwprintw(win,1,1,"Id|Car       |Tinsmith Status");
    wrefresh(win);
    string stan;
    string progress;
    for(int i=0;i<5;i++)
    {
        mvwprintw(win,i+2,1,"                                                  ");
    }
    for (int i = 0; i < (int)tinsmithVec.size(); i++) {
        if(i==5)
            break;
        progress = printMechanicProgress(tinsmithVec,i);
        if (tinsmithVec[i].state == 2) {
            wattron(win,COLOR_PAIR(4));
            stan = "Get new sheet";
            mvwprintw(win,i+2,1,"%2d|%-10s|%-17s %s",tinsmithVec[i].id, tinsmithVec[i].carName.c_str(), stan.c_str(), progress.c_str());
            wrefresh(win);
            wattroff(win,COLOR_PAIR(4));
        }
        else if(tinsmithVec[i].state == 3){
            wattron(win,COLOR_PAIR(7));
            stan = "Go to fitter" ;
            mvwprintw(win,i+2,1,"%2d|%-10s|%-17s",tinsmithVec[i].id, tinsmithVec[i].carName.c_str(), stan.c_str());
            wrefresh(win);
            wattroff(win,COLOR_PAIR(7));
        }
    }
}
void printFitter(WINDOW *win)
{
    mvwprintw(win,1,1,"Id|Car       |Fitter Status");
    wrefresh(win);
    string stan;
    string progress;
    for(int i=0;i<5;i++)
    {
        mvwprintw(win,i+2,1,"                                                  ");
    }
    for (int i = 0; i < (int)fitterVec.size(); i++) {
        if(i==5)
            break;
        progress = printMechanicProgress(fitterVec,i);
        if (fitterVec[i].state == 2) {
            wattron(win,COLOR_PAIR(4));
            stan = "Engine Mounting ";
            mvwprintw(win,i+2,1,"%2d|%-10s|%-17s %s",fitterVec[i].id, fitterVec[i].carName.c_str(), stan.c_str(),progress.c_str());
            wrefresh(win);
            wattroff(win,COLOR_PAIR(4));
        }
        else if(fitterVec[i].state == 3){
            wattron(win,COLOR_PAIR(7));
            stan = "Go to sprayer" ;
            mvwprintw(win,i+2,1,"%2d|%-10s|%-17s",fitterVec[i].id, fitterVec[i].carName.c_str(), stan.c_str());
            wrefresh(win);
            wattroff(win,COLOR_PAIR(7));
        }
    }
}
void printSprayer(WINDOW *win)
{
    mvwprintw(win,1,1,"Id|Car       |Sprayer Status");
    wrefresh(win);
    string stan;
    string progress;
    for(int i=0;i<5;i++)
    {
        mvwprintw(win,i+2,1,"                                                  ");
    }
    for (int i = 0; i < (int)sprayingVec.size(); i++) {
        if(i==5)
            break;
        progress=printMechanicProgress(sprayingVec,i);
        if (sprayingVec[i].state == 2) {
            wattron(win,COLOR_PAIR(4));
            stan = "Get new color";
            mvwprintw(win,i+2,1,"%2d|%-10s|%-17s %s",sprayingVec[i].id, sprayingVec[i].carName.c_str(), stan.c_str(),progress.c_str());
            wrefresh(win);
            wattroff(win,COLOR_PAIR(4));
        }
        else if(sprayingVec[i].state == 3){
            wattron(win,COLOR_PAIR(7));
            stan = "Go to vulcanizer" ;
            mvwprintw(win,i+2,1,"%2d|%-10s|%-17s",sprayingVec[i].id, sprayingVec[i].carName.c_str(), stan.c_str());
            wrefresh(win);
            wattroff(win,COLOR_PAIR(7));
        }
    }
}
void printVulcanizer(WINDOW *win)
{
    mvwprintw(win,1,1,"Id|Car       |Vulcanizer Status");
    wrefresh(win);
    string stan;
    string progress;
    for(int i=0;i<5;i++)
    {
        mvwprintw(win,i+2,1,"                                                  ");
    }
    for (int i = 0; i < (int)vulcanizerVec.size(); i++) {
        if(i==5)
            break;
        progress=printMechanicProgress(vulcanizerVec,i);
        if (vulcanizerVec[i].state == 2) {
            wattron(win,COLOR_PAIR(4));
            stan = "Get new tires";
            mvwprintw(win,i+2,1,"%2d|%-10s|%-17s %s",vulcanizerVec[i].id, vulcanizerVec[i].carName.c_str(), stan.c_str(), progress.c_str());
            wrefresh(win);
            wattroff(win,COLOR_PAIR(4));
        }
        else if(vulcanizerVec[i].state == 3){
            wattron(win,COLOR_PAIR(7));
            stan = "Go to electric" ;
            mvwprintw(win,i+2,1,"%2d|%-10s|%-17s",vulcanizerVec[i].id, vulcanizerVec[i].carName.c_str(), stan.c_str());
            wrefresh(win);
            wattroff(win,COLOR_PAIR(7));
        }
    }
}
void printElectrician(WINDOW *win)
{
    mvwprintw(win,1,1,"Id|Car       |Electrician Status");
    wrefresh(win);
    string stan;
    string progress;
    for(int i=0;i<5;i++)
    {
        mvwprintw(win,i+2,1,"                                                  ");
    }
    for (int i = 0; i < (int)electricianVec.size(); i++) {
        if(i==5)
            break;
        progress=printMechanicProgress(electricianVec,i);
        if (electricianVec[i].state == 2) {
            wattron(win,COLOR_PAIR(4));
            stan = "Mounting lights";
            mvwprintw(win,i+2,1,"%2d|%-10s|%-17s %s",electricianVec[i].id, electricianVec[i].carName.c_str(), stan.c_str(),progress.c_str());
            wrefresh(win);
            wattroff(win,COLOR_PAIR(4));
        }
        else if(electricianVec[i].state == 3){
            wattron(win,COLOR_PAIR(7));
            stan = "Wait tow-truck" ;
            mvwprintw(win,i+2,1,"%2d|%-10s|%-17s",electricianVec[i].id, electricianVec[i].carName.c_str(), stan.c_str());
            wrefresh(win);
            wattroff(win,COLOR_PAIR(7));
        }
    }
}
void printTowTruck_1(WINDOW *win)
{
    mvwprintw(win,1,1,"Orders Id|Id|Car       |Tow Truck 1 Status");
    wrefresh(win);
    string stan;
    string progress;
    for(int i=0;i<3;i++)
    {
        mvwprintw(win,i+2,1,"                                                           ");
        wrefresh(win);
    }
    for (int i = 0; i < (int)towTruck_1Vec.size(); i++) {
        if (towTruck_1Vec[i].state == 2) {
            progress = printTowTruckProgress(towTruck_1Vec,i);
            wattron(win,COLOR_PAIR(3));
            stan = "loading on truck";
            mvwprintw(win,i+2,1,"Truck_1:%d|%2d|%-10s|%-17s %s",towTruck_1Vec[i].id, towTruck_1Vec[i].carId ,towTruck_1Vec[i].carName.c_str(), stan.c_str(),progress.c_str());
            wrefresh(win);
            wattroff(win,COLOR_PAIR(3));
        }
        else if(towTruck_1Vec[i].state == 3){
            wattron(win,COLOR_PAIR(8));
            stan = "Drive to saloon" ;
            mvwprintw(win,i+2,1,"Truck_1:%d|%2d|%-10s|%-17s",towTruck_1Vec[i].id,towTruck_1Vec[i].carId , towTruck_1Vec[i].carName.c_str(), stan.c_str());
            wrefresh(win);
           wattroff(win,COLOR_PAIR(8));
        }
    }
}
void printTowTruck_2(WINDOW *win)
{
    mvwprintw(win,1,1,"Orders Id|Id|Car       |Tow Truck 2 Status");
    wrefresh(win);
    string stan;
    string progress;
    for(int i=0;i<3;i++)
    {
        mvwprintw(win,i+2,1,"                                                           ");
        wrefresh(win);
    }
    for (int i = 0; i < (int)towTruck_2Vec.size(); i++) {
        progress=printTowTruckProgress(towTruck_2Vec,i);
        if (towTruck_2Vec[i].state == 2) {
            wattron(win,COLOR_PAIR(3));
            stan = "loading on truck";
            mvwprintw(win,i+2,1,"Truck_2:%d|%2d|%-10s|%-17s %s",towTruck_2Vec[i].id, towTruck_2Vec[i].carId ,towTruck_2Vec[i].carName.c_str(), stan.c_str(),progress.c_str());
            wrefresh(win);
            wattroff(win,COLOR_PAIR(3));
        }
        else if(towTruck_2Vec[i].state == 3){
            wattron(win,COLOR_PAIR(8));
            stan = "Drive to saloon" ;
            mvwprintw(win,i+2,1,"Truck_2:%d|%2d|%-10s|%-17s",towTruck_2Vec[i].id,towTruck_2Vec[i].carId , towTruck_2Vec[i].carName.c_str(), stan.c_str());
            wrefresh(win);
            wattroff(win,COLOR_PAIR(8));
        }
    }
}
void printTowTruck_3(WINDOW *win)
{
    mvwprintw(win,1,1,"Orders Id|Id|Car       |Tow Truck 3 Status");
    wrefresh(win);
    string stan;
    string progress;
    for(int i=0;i<3;i++)
    {
        mvwprintw(win,i+2,1,"                                                           ");
        wrefresh(win);
    }
    for (int i = 0; i < (int)towTruck_3Vec.size(); i++) {
        progress=printTowTruckProgress(towTruck_3Vec,i);
        if (towTruck_3Vec[i].state == 2) {
            wattron(win,COLOR_PAIR(3));
            stan = "loading on truck";
            mvwprintw(win,i+2,1,"Truck_3:%d|%2d|%-10s|%-17s %s",towTruck_3Vec[i].id, towTruck_3Vec[i].carId ,towTruck_3Vec[i].carName.c_str(), stan.c_str(),progress.c_str());
            wrefresh(win);
            wattroff(win,COLOR_PAIR(3));
        }
        else if(towTruck_3Vec[i].state == 3){
            wattron(win,COLOR_PAIR(8));
            stan = "Drive to saloon" ;
            mvwprintw(win,i+2,1,"Truck_3:%d|%2d|%-10s|%-17s",towTruck_3Vec[i].id,towTruck_3Vec[i].carId , towTruck_3Vec[i].carName.c_str(), stan.c_str());
            wrefresh(win);
            wattroff(win,COLOR_PAIR(8));
        }
    }
}
void printSaloon_1(WINDOW * win)
{
    mvwprintw(win,1,1,"Space   |Id|Car       |Saloon 1 Status");
    wrefresh(win);
    string stan;
    string progress;
    mvwprintw(win,2,1,"                                                           ");
    wrefresh(win);

    for (int i = 0; i < (int)saloon_1Vec.size(); i++) {
        progress=printSaloonProgress(saloon_1Vec,i);
        if (saloon_1Vec[i].state == 2) {

            wattron(win,COLOR_PAIR(3));
            stan = "Trying to sell";
            mvwprintw(win,i+2,1,"Space: %d|%2d|%-10s|%-17s %s",saloon_1Vec[i].spaceNumber, saloon_1Vec[i].carId ,saloon_1Vec[i].carName.c_str(), stan.c_str(),progress.c_str());
            wrefresh(win);
            wattroff(win,COLOR_PAIR(3));
        }
        else if(saloon_1Vec[i].state == 3){
            wattron(win,COLOR_PAIR(6));
            stan = "Negotiations" ;
            mvwprintw(win,i+2,1,"Space: %d|%2d|%-10s|%-17s %s",saloon_1Vec[i].spaceNumber, saloon_1Vec[i].carId , saloon_1Vec[i].carName.c_str(), stan.c_str(), progress.c_str());
            wrefresh(win);
            wattroff(win,COLOR_PAIR(6));
        }
    }
}
void printSaloon_2(WINDOW * win)
{
    mvwprintw(win,1,1,"Space   |Id|Car       |Saloon 2 Status");
    wrefresh(win);
    string stan;
    string progress;
    mvwprintw(win,2,1,"                                                           ");
    wrefresh(win);
    for (int i = 0; i < (int)saloon_2Vec.size(); i++) {
        progress=printSaloonProgress(saloon_2Vec,i);
        if (saloon_2Vec[i].state == 2) {
            wattron(win,COLOR_PAIR(3));
            stan = "Trying to sell";
            mvwprintw(win,i+2,1,"Space: %d|%2d|%-10s|%-17s %s",saloon_2Vec[i].spaceNumber, saloon_2Vec[i].carId ,saloon_2Vec[i].carName.c_str(), stan.c_str(),progress.c_str());
            wrefresh(win);
            wattroff(win,COLOR_PAIR(3));
        }
        else if(saloon_2Vec[i].state == 3){
            wattron(win,COLOR_PAIR(6));
            stan = "Negotiations" ;
            mvwprintw(win,i+2,1,"Space: %d|%2d|%-10s|%-17s %s",saloon_2Vec[i].spaceNumber, saloon_2Vec[i].carId , saloon_2Vec[i].carName.c_str(), stan.c_str(),progress.c_str());
            wrefresh(win);
            wattroff(win,COLOR_PAIR(6));
        }
    }
}
void printSaloon_3(WINDOW * win)
{
    mvwprintw(win,1,1,"Space   |Id|Car       |Saloon 3 Status");
    wrefresh(win);
    string stan;
    string progress;
    mvwprintw(win,2,1,"                                                           ");
    wrefresh(win);
    for (int i = 0; i < (int)saloon_3Vec.size(); i++) {
        progress=printSaloonProgress(saloon_3Vec,i);
        if (saloon_3Vec[i].state == 2) {
            wattron(win,COLOR_PAIR(3));
            stan = "Trying to sell";
            mvwprintw(win,i+2,1,"Space: %d|%2d|%-10s|%-17s %s",saloon_3Vec[i].spaceNumber, saloon_3Vec[i].carId ,saloon_3Vec[i].carName.c_str(), stan.c_str(),progress.c_str());
            wrefresh(win);
            wattroff(win,COLOR_PAIR(3));
        }
        else if(saloon_3Vec[i].state == 3){
            wattron(win,COLOR_PAIR(6));
            stan = "Negotiations" ;
            mvwprintw(win,i+2,1,"Space: %d|%2d|%-10s|%-17s %s",saloon_3Vec[i].spaceNumber, saloon_3Vec[i].carId , saloon_3Vec[i].carName.c_str(), stan.c_str(),progress.c_str());
            wrefresh(win);
            wattroff(win,COLOR_PAIR(6));
        }
    }
}
void printBought(WINDOW *win)
{
    mvwprintw(win,1,1,"         Truck       |Saloon  |Space  |Id|Car        |Status");
    wrefresh(win);
    for (int i = 0; i < (int)boughtCarsVec.size(); i++) {
        if (boughtCarsVec[i].state == 3) {
            wattron(win,COLOR_PAIR(5));
            mvwprintw(win,i+2,1,"         Truck_%d_ride|Saloon:%d|Space:%d|%2d|%-10s |SOLD",boughtCarsVec[i].saloonNumber,boughtCarsVec[i].saloonNumber,boughtCarsVec[i].spaceNumber, boughtCarsVec[i].carId ,boughtCarsVec[i].carName.c_str());
            wrefresh(win);
            wattroff(win,COLOR_PAIR(5));
        }
    }
}
void printArrow(WINDOW *win)
{
    addch(ACS_DARROW);
    mvwprintw(win,1,1,"                                                                                                                                                                                   |");
    mvwprintw(win,2,1,"                   <----<----<----<----<----<----<----<----<----<----<----<----<----<----<----<----<----<----<----<----<----<----<----<----<----<----<----<----<----<----<----<----");
    mvwprintw(win,3,1,"                   |");
    wrefresh(win);
}
void printWash(WINDOW *win)
{

    mvwprintw(win,2,1,"                                                           ");
    wrefresh(win);
    string progress;
    if(washProgress==0)
        progress = "";
    if(washProgress==1)
        progress = "|||";
    if(washProgress==3)
        progress = "|||||";
    if(washProgress==4)
        progress = "|||||||";
    if(washProgress==5)
        progress = "|||||||||";
    if(washProgress==6)
        progress = "|||||||||||";
    if(washProgress==7)
        progress = "|||||||||||||";
    if(washProgress==8)
        progress = "|||||||||||||||";
    if(washProgress==9)
        progress = "|||||||||||||||||";
    if(washProgress==10)
        progress = "                   ";
    mvwprintw(win,1,1,"                            Truck Wash");
    mvwprintw(win,2,1,"Washing truck number %d %s",truckNumber,progress.c_str());
    wrefresh(win);

}
void Ncurses()
{
    string stan;
    initscr();
    use_default_colors();
    start_color();
    wbkgd(initscr(), COLOR_PAIR(1));
    init_pair(2,COLOR_WHITE,-1);
    init_pair(3,COLOR_GREEN,-1);
    init_pair(4,COLOR_YELLOW,-1);
    init_pair(5,COLOR_BLUE,-1);
    init_pair(6,COLOR_RED,-1);
    init_pair(7,COLOR_CYAN,-1);
    init_pair(8,COLOR_MAGENTA,-1);
    int height , width,start_y, start_x;
    height = 9 ;
    width = 25;
    start_y=start_x=0;
    WINDOW *orderWin = newwin(height+5,width+18,start_y,start_x+1);
    WINDOW *mainMechanicWin =  newwin(height+10,width+26,start_y,start_x+44);
    WINDOW *tinsmithWin = newwin(height,width+29,start_y,start_x+95);
    WINDOW *fitterWin = newwin(height,width+29,start_y,start_x+149);
    WINDOW *sprayerWin = newwin(height,width+29,start_y+10,start_x+95);
    WINDOW *vulcanizerWin = newwin(height,width+29,start_y+10,start_x+149);
    WINDOW *arrowWin = newwin(height-4,width+177,start_y+19,start_x+1);
    WINDOW *electricianWin = newwin(height,width+29,start_y+24,start_x+1);
    WINDOW *towTruck_1Win = newwin(height-3,width+40,start_y+34,start_x+1);
    WINDOW *towTruck_2Win = newwin(height-3,width+40,start_y+41,start_x+68);
    WINDOW *towTruck_3Win = newwin(height-3,width+40,start_y+47,start_x+1);
    WINDOW *saloon_1Win = newwin(height-4,width+40,start_y+40,start_x+1);
    WINDOW *saloon_2Win = newwin(height-4,width+40,start_y+47,start_x+68);
    WINDOW *saloon_3Win = newwin(height-4,width+40,start_y+53,start_x+1);
    WINDOW *boughtWin = newwin(height+25,width+43,start_y+24,start_x+135);
    WINDOW *washWin =  newwin(height-4,width+40,start_y+24,start_x+68);
    box(orderWin,0,0);
    box(mainMechanicWin,0,0);
    box(tinsmithWin,0,0);
    box(fitterWin,0,0);
    box(sprayerWin,0,0);
    box(vulcanizerWin,0,0);
    box(arrowWin,0,0);
    box(electricianWin,0,0);
    box(towTruck_1Win,0,0);
    box(towTruck_2Win,0,0);
    box(towTruck_3Win,0,0);
    box(saloon_1Win,0,0);
    box(saloon_2Win,0,0);
    box(saloon_3Win,0,0);
    box(boughtWin,0,0);
    box(washWin,0,0);
    refresh();
    raw();
    noecho();
    curs_set(false);
    keypad(stdscr, true);
    thread key_listener(listenForEscapeKey, std::ref(force_end));
    key_listener.detach();

    do {
        printOrders(orderWin);
        printMainMechanicActions(mainMechanicWin);
        printTinsmith(tinsmithWin);
        printFitter(fitterWin);
        printSprayer(sprayerWin);
        printVulcanizer(vulcanizerWin);
        printArrow(arrowWin);
        printElectrician(electricianWin);
        printTowTruck_1(towTruck_1Win);
        printTowTruck_2(towTruck_2Win);
        printTowTruck_3(towTruck_3Win);
        printSaloon_1(saloon_1Win);
        printSaloon_2(saloon_2Win);
        printSaloon_3(saloon_3Win);
        printBought(boughtWin);
        printWash(washWin);
        this_thread::sleep_for(std::chrono::milliseconds(80));
    }while(!force_end);
    clear();

    endwin();
    exit(0);
}
void listenForEscapeKey(atomic<bool>& switch_ref) {
    while(wgetch(stdscr) != 27);
    switch_ref = true;
}
