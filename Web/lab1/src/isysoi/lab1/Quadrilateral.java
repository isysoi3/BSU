package isysoi.lab1;

import java.util.Arrays;

public class Quadrilateral {

    private final double square;
    private final double perimeter;
    private final QuadrilateralType type;
    private final Point a;
    private final Point b;
    private final Point c;
    private final Point d;

    public Quadrilateral(Point a, Point b, Point c, Point d) {

        validatePoints(a, b, c, d);

        this.a = a;
        this.b = b;
        this.c = c;
        this.d = d;

        perimeter = countPerimeter();
        square = countSquare();
        type = QuadrilateralType.ARBITRARY;
    }

    static void validatePoints(Point a, Point b, Point c, Point d) {

        // throw exceptions if we can't construct a quadrilateral (duplicate points, etc)

        // Duplicate points check
        Point[] points = { a, b, c, d };
        if (Arrays.stream(points)
                .distinct()
                .count() != 4) {
            throw new DuplicatePoints(points);
        }

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

    private double countSquare() {
        return Math.sqrt(perimeter
                * (perimeter - Point.distance(a,b))
                * (perimeter - Point.distance(b,c))
                * (perimeter - Point.distance(c,d))
                * (perimeter - Point.distance(d,a))
        );
    }

    private double countPerimeter() {

        double tmpPerimeter = 0;
        tmpPerimeter += Point.distance(a,b);
        tmpPerimeter += Point.distance(b,c);
        tmpPerimeter += Point.distance(c,d);
        tmpPerimeter += Point.distance(d,a);

        return tmpPerimeter;
    }

    //TODO: write in caps
    private enum QuadrilateralType {
        SQUARE,
        RECTANGLE,
        RHOMBUS,
        ARBITRARY
    }

    public static class UserQuit extends RuntimeException {
        public UserQuit() {
            super("User quit.");
        }
    }

    public static class DuplicatePoints extends RuntimeException {
        public DuplicatePoints(Point... points) {
            super("Cannot create quadrilaterl with duplicate points: " + Arrays.toString(points));
        }
    }

}
