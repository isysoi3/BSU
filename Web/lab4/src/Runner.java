import model.Bus;
import model.BusStop;
import model.BusStopNameEnum;
import model.Position;

import java.util.ArrayList;

public class Runner {

    public static void main(String[] args) {

        BusStop busStopFirst = new BusStop(new Position(-300, -200), BusStopNameEnum.WARSAW);
        BusStop busStopSecond = new BusStop(new Position(50, 50), BusStopNameEnum.BREST);
        BusStop busStopThird = new BusStop(new Position(450, 500), BusStopNameEnum.MINSK);
        BusStop busStopFourth = new BusStop(new Position(1700, 550), BusStopNameEnum.MOSCOW);


        ArrayList<BusStop> firstRoute = new ArrayList<>();

        firstRoute.add(busStopFirst);
        firstRoute.add(busStopSecond);
        firstRoute.add(busStopThird);
        firstRoute.add(busStopFourth);

        Thread threadFirst = new Thread(new Bus(firstRoute,30));
        Thread threadSecond = new Thread(new Bus(firstRoute,30));
        Thread threadFourth = new Thread(new Bus(firstRoute,30));
        Thread threadThird = new Thread(new Bus(firstRoute,30));


        threadFirst.start();
        threadSecond.start();
        threadFourth.start();
        threadThird.start();


    }
}
