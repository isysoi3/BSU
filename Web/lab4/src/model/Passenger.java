package model;

import java.util.Random;

/**
 * entity class , instances randomly appear at the busStop ,
 * it can change bus (if passenger chose another aim to stop(another busStop))
 */
public class Passenger {

    /**
     * passenger name
     */
    private String name;

    /**
     * passenger destination goal
     */
    private String destinationGoal;

    /**
     * passenger destination goal getter
     *
     * @return passenger destination goal
     */
    public String getDestinationGoal() {
        return destinationGoal;
    }

    /**
     * passenger destination goal setter
     *
     * @param destinationGoal passenger destination goal
     */
    public void setDestinationGoal(String destinationGoal) {
        //require to create shuffle method
        this.destinationGoal = destinationGoal;
    }

    /**
     * passenger can wait
     */
    private boolean cantWaitAnyMore;

    /**
     * passenger can wait getter
     *
     * @return passenger can wait
     */
    public boolean isCantWaitAnyMore() {
        return cantWaitAnyMore;
    }

    /**
     * passenger can wait setter
     *
     * @param cantWaitAnyMore passenger can wait
     */
    public void setCantWaitAnyMore(boolean cantWaitAnyMore) {
        this.cantWaitAnyMore = cantWaitAnyMore;
    }

    /**
     * constructor of passenger
     *
     * @param name            passenger name
     * @param destinationGoal passenger destination goal
     */
    public Passenger(String name, String destinationGoal) {

        Random random = new Random();

        cantWaitAnyMore = random.nextInt(100) % 2 == 0;
        this.name = name;
        this.destinationGoal = destinationGoal;
    }

    @Override
    public String toString() {
        return "Passenger{" +
                "name='" + name + '\'' +
                '}';
    }

}
