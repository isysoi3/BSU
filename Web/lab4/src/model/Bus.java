package model;

import exception.BusWorkException;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import java.util.ArrayList;
import java.util.List;

public class Bus implements Runnable {

    private static final Logger logger = LogManager.getLogger();

    /**
     * time in milisec to board or get of passenger
     */
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
     * speed of bus
     */
    private int positionAtBusStop;

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

    /**
     * constructor of bus
     *
     * @param busStops   list of bus stops
     * @param passengers inittial passengers
     * @param speed      speed of bus
     */
    public Bus(List<BusStop> busStops, List<Passenger> passengers, double speed) throws BusWorkException {
        this.route = busStops;
        this.speed = speed;
        if (passengers.size() > 20)
            throw new BusWorkException("Too many passengers");
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
            var passengersOnStation = currentBusStop.getPassengers();

            double timeNecessaryForRide = previousBusStop.distanceTo(currentBusStop) / speed;

            try {
                logger.info(currentThreadName + " I am going to " + currentBusStop.getName());
                Thread.sleep((long) timeNecessaryForRide);
                logger.info(currentThreadName + " I came to " + currentBusStop.getName());
            } catch (InterruptedException e) {
                logger.warn("I`m can`t go to bus stop", e);
                continue;
            }

            try {
                positionAtBusStop = currentBusStop.arriveToBusStop(this);
                logger.info(currentBusStop.getName() + " buses " + busArrayList.size());
                logger.info(currentThreadName + " i am waiting for passengers");
            } catch (InterruptedException e) {
                logger.warn("Someone interrupted me, go to next bus stop", e);
                continue;
            }

            int count = 0;
            ArrayList<Passenger> stayPassengers = new ArrayList<>();
            for (Passenger passenger : passengers) {
                if (passenger.getDestinationGoal().getName().equals(currentBusStop.getName().getName())) {
                    count += 1;
                    logger.info(currentThreadName + " removed " + passenger);
                    continue;
                }
                stayPassengers.add(passenger);
            }
            passengers = stayPassengers;
            try {
                Thread.sleep(count * TIME_FOR_ONE_PASSENGER);
                logger.info(currentThreadName + " getting off finished. Passengers go out: " + count);
            } catch (InterruptedException e) {
                logger.warn("Someone interrupted me ", e);
            }
            count = 0;
            stayPassengers = new ArrayList<>();

            try {
                currentBusStop.getPassengersBusStopLock().lock();
                for (Passenger passenger :
                        passengersOnStation) {
                    for (int j = i + 1; j < route.size() - 1; j++) {
                        if (passenger.getDestinationGoal().equals(route.get(j).getName()) && passengers.size() < 20) {
                            passengers.add(passenger);
                            count += 1;
                            logger.info(currentThreadName + " added " + passenger);
                            continue;
                        }
                        stayPassengers.add(passenger);
                    }
                }
                currentBusStop.setPassengers(stayPassengers);
            } finally {
                currentBusStop.getPassengersBusStopLock().unlock();
            }

            try {
                Thread.sleep(count * TIME_FOR_ONE_PASSENGER);
                logger.info(currentThreadName + " boarding finished. Passengers come in: " + count);
            } catch (InterruptedException e) {
                logger.warn("Boarding canceled", e);
            }

            try {
                if (currentBusStop.getBusArrayList().size() > 1) {
                    List<Passenger> passengerExchangeList = new ArrayList<>();
                    stayPassengers = new ArrayList<>();
                    for (Passenger passenger : passengers) {
                        if (positionAtBusStop != 1) {
                            if (passenger.isCantWaitAnyMore()) {
                                passengerExchangeList.add(passenger);
                            } else {
                                stayPassengers.add(passenger);
                            }
                        } else {
                            if (!passenger.isCantWaitAnyMore()) {
                                passengerExchangeList.add(passenger);
                            } else {
                                stayPassengers.add(passenger);
                            }
                        }
                    }
                    passengers = stayPassengers;
                    passengerExchangeList = currentBusStopExchanger.exchange(passengerExchangeList);
                    count = 0;
                    if (passengers.size() + passengerExchangeList.size() > 20) {
                        logger.info("Can`t exchange passengers, some of them will stay at bus stop");
                        for (Passenger passenger : passengerExchangeList) {
                            if (passengers.size() > 20) {
                                currentBusStop.getPassengersBusStopLock().lock();
                                currentBusStop.getPassengers().add(passenger);
                                currentBusStop.getPassengersBusStopLock().unlock();
                            } else {
                                passengers.add(passenger);
                                count++;
                            }
                        }
                    } else {
                        count = passengerExchangeList.size();
                        passengers.addAll(passengerExchangeList);
                    }
                    logger.info("Total exchanged passengers: " + count);
                }
            } catch (InterruptedException e) {
                logger.warn("Someone interrupted me ", e);
            }

            currentBusStop.leaveBusStop(this);
            logger.info(currentThreadName + " leave stop " + currentBusStop.getName());

        }

        logger.info(currentThreadName + " end work ");
    }

}
