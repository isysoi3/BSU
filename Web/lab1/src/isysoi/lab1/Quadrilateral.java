package isysoi.lab1;

public class Quadrilateral {

    private Point [] points = new Point[4];

    public Quadrilateral(Point[] points) {
        this.points = points;
    }

    public Quadrilateral() {

    }

    public Point[] getPoints() {
        return points;
    }

    public void setPoints(Point[] points) {
        this.points = points;
    }

}
