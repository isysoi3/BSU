package model;

/**
 * name of bus stops
 *
 * @author Ilya Sysoi
 */
public enum BusStopNameEnum {

    MINSK("Minsk"),
    BREST("Brest") ,
    WARSAW("Warsaw"),
    MOSCOW("Moscow");

    private String name;

    BusStopNameEnum(String name) {
        this.name = name;
    }

    public String getName() {
        return "station " + name;
    }

}
