package isysoi.lab1;

public class Quadrilateral {

    private final double square;
    private final double perimeter;
    private final Point [] points;
    private final QuadrilateralType type;

    public Quadrilateral(Point[] points) {
        this.points = points;
        perimeter = 4;
        square = 5;
        type = QuadrilateralType.arbitrary;
    }

    public QuadrilateralType getType() {
        return type;
    }

    public double getPerimeter() {
        return perimeter;
    }

    public double getSquare() {
        return square;
    }

    public Point[] getPoints() {
        return points;
    }

    //TODO: write in caps
    private enum QuadrilateralType {
        SQUARE,
        rectangle,
        rhombus,
        arbitrary
    }

}
