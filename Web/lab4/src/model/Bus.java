package model;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Exchanger;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Bus implements Runnable {

    private static final int MAGIC_NUMBER_FOR_DEBUG = 20;

    /**
     * passenger to exchange
     */
    private Exchanger<List<Passenger>> exchanger;

    /**
     * bus route
     */
    private List<BusStop> route;

    /**
     * passenger list in bus
     */
    private ArrayList<Passenger> passengers = new ArrayList<>(20);

    /**
     * previous bus stop
     */
    private BusStop previousBusStop;

    /**
     * current bus stop
     */
    private BusStop currentBusStop;

    /**
     * lock
     */
    private Lock lock = new ReentrantLock();

    /**
     * speed of bus
     */
    private double speed;

    /**
     * constructor of bus
     *
     * @param busStops list of bus stops
     * @param speed    speed of bus
     */
    public Bus(List<BusStop> busStops, double speed) {
        this.route = busStops;
        this.speed = speed;
    }

    @Override
    public void run() {
        String currentThreadName = Thread.currentThread().getName();


        for (int i = 0; i < route.size() - 1; i++) {
            previousBusStop = route.get(i);
            currentBusStop = route.get(i + 1);

            List<Passenger> passengersOnStation = currentBusStop.getPassengers();

            //required for exchange between two buses
            exchanger = currentBusStop.getExchanger();
            //get semaphore form each aim station
            Semaphore semaphore = currentBusStop.getSemaphore();

            try {
                System.out.println(currentThreadName + " I am going to the station " + currentBusStop.getName());

                //get number  that we need sleep (imitating of riding)
                double timeNecessaryForRide = getDistance(route, i, i + 1) / speed;
                Thread.sleep((long) timeNecessaryForRide * MAGIC_NUMBER_FOR_DEBUG);
                System.out.println(currentThreadName + " I came to stantion " + currentBusStop.getName());

                semaphore.acquire();

                //parking places for buses
                ArrayList<Bus> busArrayList = currentBusStop.getBusArrayList();
                lock.lock();
                if (busArrayList.size() < 2) {
                    busArrayList.add(this);
                    System.out.println(busArrayList.size());
                }
                lock.unlock();
                System.out.println(currentThreadName + " i am waiting for passengers");

                Thread.sleep(5000);

                // let passenger to take their sits in the bus
                for (int k = 0; k < passengersOnStation.size(); k++) {
                    // for each passanger
                    Passenger passenger = passengersOnStation.get(k);

                    //we check if he can use this bus (routes should be equals)
                    for (int j = i + 1; j < route.size() - 1; j++) {
                        if (passenger.getDestinationGoal().equals(route.get(j).getName()) && passengers.size() < 20) {
                            lock.lock();
                            passengers.add(passenger); // TODO ask why it doesn't remove (it works with buses)
                            passengersOnStation.remove(passenger);
                            lock.unlock();
                        }
                        System.out.println(currentThreadName + " i just added " + passenger);
                    }
                }
                Thread.sleep(3000);


                if (busArrayList.size() > 1) {

                    for (Bus bus : busArrayList) {
                        List<Passenger> listWhoCanWait = new ArrayList<>();
                        List<Passenger> listWhoNeedFasterSpeed = new ArrayList<>();
                        for (Passenger passenger : this.passengers) {
                            listWhoCanWait.add(passenger);
                        }

                        if (!bus.equals(this)) {
                            // if passenger need to move faster let him
                            //todo check what bus is faster and add passengers who need here
                            for (Passenger passenger : bus.passengers) {
                                if (passenger.isCantWaitAnyMore()) {

                                    listWhoNeedFasterSpeed.add(passenger);
                                }
                            }

                            listWhoCanWait = exchanger.exchange(listWhoCanWait);
                            this.passengers.addAll(listWhoCanWait);
                            bus.passengers.addAll(listWhoNeedFasterSpeed);
                        }


                    }
                }
                busArrayList.remove(this);
            } catch (InterruptedException e) {
                System.out.println("Someone interrupted me ");
            }
            semaphore.release();
        }
        System.out.println(currentThreadName + " I end my work ");
    }


    /**
     * distance between two stations
     *
     * @param route route with bus stops
     * @param prev  previous bus stop
     * @param next  next bus stop
     * @return distance
     */
    private static double getDistance(List<BusStop> route, int prev, int next) {
        BusStop prevBusStop = route.get(prev);
        BusStop nextBusStop = route.get(next);

        return prevBusStop.distanceTo(nextBusStop);
    }
}
