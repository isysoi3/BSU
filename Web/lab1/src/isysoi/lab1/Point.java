package isysoi.lab1;

import java.util.Arrays;

public class Point {

    private final int x;
    private final int y;

    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    static double distance(Point p1, Point p2) {
        return Math.sqrt(Math.pow(p1.x - p2.x, 2) + Math.pow(p1.y - p2.y, 2));
    }

    /**
     * Distance from this point to the supplied point.
     *
     * @param that the that
     * @return the double
     */
    public double distance(Point that) {
        return distance(this, that);
    }

    @Override
    public String toString() {
        return "(" + x + "," + y + ")";
    }

}


