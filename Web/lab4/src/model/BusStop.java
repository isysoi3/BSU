package model;

import util.PassengerListGenerator;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Exchanger;
import java.util.concurrent.Semaphore;

/**
 * common resource for buses
 *
 * @author Ilya Sysoi
 */
public class BusStop {

    /**
     * passengers list waiting on bus stop
     */
    private List<Passenger> passengers;


    /**
     * getter of passengers
     */
    public List<Passenger> getPassengers() {
        return passengers;
    }

    /**
     * exchanger passengers list going to next bus
     */
    private Exchanger<List<Passenger>> exchanger = new Exchanger<>();

    /**
     * getter of exchanger passengers
     */
    public Exchanger<List<Passenger>> getExchanger() {
        return exchanger;
    }

    /**
     * bus stop position
     */
    private Position position;

    /**
     * getter of bus stop position
     */
    public Position getPosition() {
        return position;
    }

    /**
     * bus stop name
     */
    private BusStopNameEnum name;

    /**
     * getter of bus stop name
     */
    public BusStopNameEnum getName() {
        return name;
    }

    /**
     * max buses can take place on bus stop at one time
     */
    private final int maxBusesAmount = 2;

    /**
     * synchronize semaphore buses on bus stop
     */
    private Semaphore semaphore = new Semaphore(maxBusesAmount, true);

    /**
     * getter of synchronize semaphore
     */
    public Semaphore getSemaphore() {
        return semaphore;
    }

    /**
     * list of buses, which occupied station
     */
    private ArrayList<Bus> busArrayList = new ArrayList<>(2);

    /**
     * getter of occupied station buses
     */
    public ArrayList<Bus> getBusArrayList() {
        return busArrayList;
    }


    /**
     * constructor of bus stop
     *
     * @param position        position of bus stop
     * @param busStopNameEnum name of bus stop
     */
    public BusStop(Position position, BusStopNameEnum busStopNameEnum) {
        passengers = PassengerListGenerator.generatePassangers();
        this.position = position;
        this.name = busStopNameEnum;
    }

    /**
     * calcilate distance between two bus stops
     *
     * @param next next bus stop
     * @return distance between two bus stops
     */
    public double distanceTo(BusStop next) {
        return position.distanceTo(next.position);
    }

    @Override
    public String toString() {
        return "BusStop{" +
                ", position=" + position +
                ", name='" + name + '\'' +
                '}';
    }
}
