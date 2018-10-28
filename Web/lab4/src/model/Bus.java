package model;

import java.util.ArrayList;
import java.util.List;

public class Bus implements Runnable {

    private final int TIME_FOR_ONE_PASSENGER = 1000;

    /**
     * bus route
     */
    private List<BusStop> route;

    /**
     * passenger list in bus
     */
    private ArrayList<Passenger> passengers = new ArrayList<>(20);


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

    public Bus(List<BusStop> busStops, List<Passenger> passengers, double speed) {
        this.route = busStops;
        this.speed = speed;
        if (passengers.size() > 20)
            throw new IllegalArgumentException("Too many passengers");
        this.passengers.addAll(passengers);
    }

    @Override
    public void run() {
        String currentThreadName = Thread.currentThread().getName();

        for (int i = 0; i < route.size() - 1; i++) {

            BusStop previousBusStop = route.get(i);
            BusStop currentBusStop = route.get(i + 1);

            var busArrayList = currentBusStop.getBusArrayList();
            var currentBusStopExchanger = currentBusStop.getExchanger();
            var semaphore = currentBusStop.getBusesSemaphore();

            double timeNecessaryForRide = previousBusStop.distanceTo(currentBusStop) / speed;

            try {
                System.out.println(currentThreadName + " I am going to " + currentBusStop.getName());
                Thread.sleep((long) timeNecessaryForRide);
                System.out.println(currentThreadName + " I came to " + currentBusStop.getName());

                semaphore.acquire();
                busArrayList.add(this);
                System.out.println(currentBusStop.getName() + " buses " + busArrayList.size());

                System.out.println(currentThreadName + " i am waiting for passengers");


                int count = 0;
                ArrayList<Passenger> stayPassengers = new ArrayList<>();
                for (Passenger passenger : passengers) {
                    if (passenger.getDestinationGoal().getName().equals(currentBusStop.getName().getName())) {
                        count += 1;
                        System.out.println(currentThreadName + " removed " + passenger);
                        continue;
                    }
                    stayPassengers.add(passenger);
                }
                passengers = stayPassengers;
                Thread.sleep(count * TIME_FOR_ONE_PASSENGER);
                System.out.println(currentThreadName + " getting off finished. Passengers go out: " + count);

                count = 0;
                stayPassengers = new ArrayList<>();

                currentBusStop.getPassengersBusStopLock().lock();
                List<Passenger> passengersOnStation = currentBusStop.getPassengers();
                for (Passenger passenger :
                        passengersOnStation) {
                    for (int j = i + 1; j < route.size() - 1; j++) {
                        if (passenger.getDestinationGoal().equals(route.get(j).getName()) && passengers.size() < 20) {
                            passengers.add(passenger);
                            count += 1;
                            System.out.println(currentThreadName + " added " + passenger);
                            continue;
                        }
                        stayPassengers.add(passenger);
                    }
                }
                currentBusStop.getPassengersBusStopLock().unlock();
                currentBusStop.setPassengers(stayPassengers);

                Thread.sleep(count * TIME_FOR_ONE_PASSENGER);
                System.out.println(currentThreadName + " boarding finished. Passengers come in: " + count);

                if (currentBusStop.getBusArrayList().size() > 1) {
                    for (Bus bus : currentBusStop.getBusArrayList()) {
                        List<Passenger> listWhoNeedFasterSpeed = new ArrayList<>();
                        List<Passenger> listWhoCanWait = new ArrayList<>(this.passengers);
                        if (!bus.equals(this)) {
                            for (Passenger passenger : bus.passengers) {
                                if (passenger.isCantWaitAnyMore()) {
                                    listWhoNeedFasterSpeed.add(passenger);
                                }
                            }

                            listWhoCanWait = currentBusStopExchanger.exchange(listWhoCanWait);
                            this.passengers.addAll(listWhoCanWait);
                            bus.passengers.addAll(listWhoNeedFasterSpeed);
                        }
                    }
                }

            } catch (InterruptedException e) {
                System.out.println("Someone interrupted me ");
            }
            System.out.println(currentBusStop.getName() + " leave stop " + currentBusStop.getName());
            busArrayList.remove(this);
            semaphore.release();
        }

        System.out.println(currentThreadName + " I end work ");
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
