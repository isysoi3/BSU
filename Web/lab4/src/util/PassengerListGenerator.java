package util;

import model.BusStopNameEnum;
import model.Passenger;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

/**
 * util class that helps generate random passangers on bus stations
 *
 * @author Ilya Sysoi
 */
public class PassengerListGenerator {

    /**
     * generate list of passenger
     *
     * @return random list of passengers
     */
    public static List<Passenger> generatePassangers() {
        List<Passenger> list = new ArrayList<>();
        Random random = new Random();

        int amount = random.nextInt(10) + 1;
        for (int i = 0; i < amount; i++) {
            int randomInt = random.nextInt(4);
            BusStopNameEnum direction = null;

            switch (randomInt) {
                case 0:
                    direction = BusStopNameEnum.MINSK;
                    break;
                case 1:
                    direction = BusStopNameEnum.BREST;
                    break;
                case 2:
                    direction = BusStopNameEnum.WARSAW;
                    break;
                case 3:
                    direction = BusStopNameEnum.MOSCOW;
                    break;
            }

            String firstName = "Passenger " + (random.nextInt(100) + 1);
            list.add(new Passenger(firstName, direction));
        }
        return list;
    }

}
