package model;

/**
 * This is the class of 2D point with some functions to work with points
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class Point {
    /**
     * x component of point
     */
    private final double x;

    /**
     * x component getter
     * @return x component of point
     */
    public double getX() {
        return x;
    }


    /**
     * y component of point
     */
    private final double y;

    /**
     * y component getter
     * @return y component of point
     */
    public double getY() {
        return y;
    }

    /**
     * Constructor of point with given (x, y) coordinates
     * @param x x component of 2D point
     * @param y y component of 2D point
     */
    public Point(double x, double y) {
        this.x = x;
        this.y = y;
    }

    /**
     * Default constructor to create (0, 0) point
     */
    public Point(){
        this.x = 0;
        this.y = 0;
    }

    /**
     * Returns distance to another point
     * @param that target point
     * @return distance between two points
     * @throws NullPointerException if second summand is null
     */
    public double distanceTo(Point that) {
        return distance(this, that);
    }

    /**
     * Returns distance from one point to another point
     * @param p1 first point
     * @param p2 second point
     * @return distance between two points
     * @throws NullPointerException if second summand is null
     */
    private double distance(Point p1, Point p2) {
        return Math.sqrt(Math.pow(p1.x - p2.x, 2)
                + Math.pow(p1.y - p2.y, 2));
    }

    /**
     * Converts 2D point to string
     * @return the point as string
     */
    @Override
    public String toString() {
        return "( " + x + " , " + y + " )";
    }

}


