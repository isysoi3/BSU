package controller;

import exception.BusWorkException;
import model.Bus;
import model.BusStop;
import model.BusStopNameEnum;
import model.Position;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import util.PassengerListGenerator;

import java.util.ArrayList;

public class Runner {

    private static final Logger logger = LogManager.getLogger();

    public static void main(String[] args) {

        logger.info("Начало маршрута");

        BusStop busStopFirst = new BusStop(new Position(-300, -200), BusStopNameEnum.WARSAW);
        BusStop busStopSecond = new BusStop(new Position(50, 50), BusStopNameEnum.BREST);
        BusStop busStopThird = new BusStop(new Position(450, 500), BusStopNameEnum.MINSK);
        BusStop busStopFourth = new BusStop(new Position(1700, 550), BusStopNameEnum.MOSCOW);


        ArrayList<BusStop> firstRoute = new ArrayList<>();

        firstRoute.add(busStopFirst);
        firstRoute.add(busStopSecond);
        firstRoute.add(busStopThird);
        firstRoute.add(busStopFourth);

        Thread threadFirst = null;
        try {
            threadFirst = new Thread(new Bus(firstRoute, PassengerListGenerator.generatePassangers(), 10));
        } catch (BusWorkException e) {
            logger.warn("Bus can`t work", e);
        }
        Thread threadSecond = null;
        try {
            threadSecond = new Thread(new Bus(firstRoute, PassengerListGenerator.generatePassangers(), 5));
        } catch (BusWorkException e) {
            logger.warn("Bus can`t work", e);
        }
        Thread threadFourth = new Thread(new Bus(firstRoute,30));
        Thread threadThird = new Thread(new Bus(firstRoute,5));


        threadFirst.start();
        threadSecond.start();
        threadThird.start();
        threadFourth.start();

        try {
            threadFirst.join();
        } catch (InterruptedException e) {
            logger.warn(e);
        }
        try {
            threadSecond.join();
        } catch (InterruptedException e) {
            logger.warn(e);
        }
        try {
            threadThird.join();
        } catch (InterruptedException e) {
            logger.warn(e);
        }
        try {
            threadFourth.join();
        } catch (InterruptedException e) {
            logger.warn(e);
        }

        logger.info("Завершение маршрута");
    }
}
