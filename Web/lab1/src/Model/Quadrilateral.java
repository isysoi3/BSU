package Model;

/**
 * This is the class of Quadrilateral with some functions to work with it
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class Quadrilateral {

    /**
     * a point of quadrilateral
     */
    private final Point a;

    public Point getAPoint() {
        return a;
    }

    /**
     * b point of quadrilateral
     */
    private final Point b;

    public Point getBPoint() {
        return b;
    }

    /**
     * c point of quadrilateral
     */
    private final Point c;

    public Point getCPoint() {
        return c;
    }

    /**
     * d point of quadrilateral
     */
    private final Point d;

    public Point getDPoint() {
        return d;
    }


    /**
     * square of quadrilateral
     */
    private final double square;

    public double getSquare() {
        return square;
    }

    /**
     * perimeter of quadrilateral
     */
    private final double perimeter;

    public double getPerimeter() {
        return perimeter;
    }

    /**
     * geometric type of quadrilateral
     */
    private final QuadrilateralType type;

    /**
     * all types of quadrilateral
     */
    private enum QuadrilateralType {
        SQUARE,
        RECTANGLE,
        RHOMBUS,
        ARBITRARY
    }

    /**
     * geometric type of quadrilateral
     *
     * @return geometric type of quadrilateral as string based on enum
     */
    public String getGeometricType() {
        switch (type) {
            case RECTANGLE:
                return "rectangle";
            case RHOMBUS:
                return "rhombus";
            case ARBITRARY:
                return "arbitrary";
            case SQUARE:
                return "square";
        }
        return "arbitrary";
    }


    /**
     * Constructor of quadrilateral with validating points and count square and perimeter, recognize type
     *
     * @param a a point of quadrilateral
     * @param b b point of quadrilateral
     * @param c c point of quadrilateral
     * @param d d point of quadrilateral
     */
    public Quadrilateral(Point a, Point b, Point c, Point d) {

        validatePoints(a, b, c, d);

        this.a = a;
        this.b = b;
        this.c = c;
        this.d = d;

        perimeter = countPerimeter();
        square = countSquare();
        type = recognizeQuadrilateralType();
    }

    /**
     * validating points by checking lines between its
     */
    private void validatePoints(Point a, Point b, Point c, Point d) {
        checkLine(a, b, c);
        checkLine(b, c, d);
        checkLine(c, d, a);
        checkLine(a, b, d);
    }

    /**
     * ff
     * @throws IllegalArgumentException ff
     */
    private void checkLine(Point t, Point m, Point k) {
        if ((t.getX() == m.getX() && t.getX() == k.getX())
                || (t.getY() == m.getY() && t.getY() == k.getY())) {
            throw new IllegalArgumentException();
        }
    }

    /**
     * count perimeter of quadrilateral based on distance between points
     */
    private double countPerimeter() {

        double tmpPerimeter = 0;
        tmpPerimeter += a.distanceTo(b);
        tmpPerimeter += b.distanceTo(c);
        tmpPerimeter += c.distanceTo(d);
        tmpPerimeter += d.distanceTo(a);

        return tmpPerimeter;
    }

    /**
     * count square of quadrilateral by common Brahmagupta's formula
     */
    private double countSquare() {
        double halfOfPerimeter = perimeter / 2;
        double abSide = a.distanceTo(b),
                bcSide = b.distanceTo(c),
                cdSide = c.distanceTo(d),
                daSide = d.distanceTo(a),
                abAndcdSides = abSide * cdSide,
                bsAnddaSides = bcSide * daSide,
                diagonals = b.distanceTo(d) * c.distanceTo(a);

        return Math.sqrt((halfOfPerimeter - abSide)
                * (halfOfPerimeter - bcSide)
                * (halfOfPerimeter - cdSide)
                * (halfOfPerimeter - daSide)
                - 0.25 * (abAndcdSides + bsAnddaSides + diagonals) * (abAndcdSides + bsAnddaSides - diagonals)
        );
    }

    /**
     * recognizing quadrilateral type
     */
    private QuadrilateralType recognizeQuadrilateralType() {
        if (checkRhombus()) {
            return QuadrilateralType.RHOMBUS;
        } else if (checkSquare()) {
            return QuadrilateralType.SQUARE;
        } else if (checkRectangle()) {
            return QuadrilateralType.RECTANGLE;
        }
        return QuadrilateralType.ARBITRARY;
    }

    /**
     * checking is it square by compare two sides, and angles for 90 degrees
     *
     * @return true if angel is 90 degree, false in other
     */
    private boolean checkRightAngle(Point a, Point b, Point c) {
        Point aB = new Point(b.getX() - a.getX(),
                b.getY() - a.getY());
        Point bC = new Point(c.getX() - b.getX(),
                c.getY() - b.getY());

        return (aB.getX() * bC.getX() + aB.getY() * bC.getY()) == 0;
    }

    /**
     * checking is it square by compare two sides, and angles for 90 degrees
     * @return true if it is square, false in other way
     */
    private boolean checkSquare() {
        return (a.distanceTo(b) == a.distanceTo(d))
                && checkRightAngle(a, b, c)
                && checkRightAngle(a, d, c);
    }

    /**
     * checking is it rectangle by compare two sides, and angles for 90 degrees
     * @return true if it is rectangle, false in other way
     */
    private boolean checkRectangle() {
        return (a.distanceTo(b) != a.distanceTo(d))
                && checkRightAngle(a, b, c)
                && checkRightAngle(a, d, c);
    }

    /**
     * checking is it rhombus by compare four sides, and angles for not 90 degrees
     * @return true if it is rhombus, false in other way
     */
    private boolean checkRhombus() {
        return ((a.distanceTo(b) == b.distanceTo(c))
                && (c.distanceTo(d) == b.distanceTo(c)))
                && !checkRightAngle(a, b, c)
                && !checkRightAngle(a, d, c);
    }

    /**
     * Converts quadrilateral to string
     *
     * @return the quadrilateral info as string
     */
    @Override
    public String toString() {
        return String.format("a - '%s'\nb - '%s'\nc - '%s'\nd - '%s'\nperimeter is %.2f\nsquare is %.2f\nType is '%s'",
                a.toString(),
                b.toString(),
                c.toString(),
                d.toString(),
                perimeter,
                square,
                getGeometricType());
    }

}
