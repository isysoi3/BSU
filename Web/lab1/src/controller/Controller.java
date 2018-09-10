package controller;

import model.Point;
import model.Quadrilateral;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * Basic class demonstrates functions of Quadrilateral and Point classes
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class Controller {

    /**
     * Method to demonstrate work with Quadrilateral and Point classes
     */
    public static String startWork() {
        List<Quadrilateral> quadrilaterals = new ArrayList<>();
        List<Double> squarePerimeters = new ArrayList<>();
        List<Double> arbitraryPerimeters = new ArrayList<>();
        List<Double> rhombusPerimeters = new ArrayList<>();
        List<Double> rectanglePerimeters = new ArrayList<>();

        quadrilaterals.add(new Quadrilateral(new Point(4, 5), new Point(7, 3), new Point(4, 1), new Point(1, 3)));
        quadrilaterals.add(new Quadrilateral(new Point(5, 4), new Point(8, 4), new Point(8, 1), new Point(5, 1)));
        quadrilaterals.add(new Quadrilateral(new Point(4, 10), new Point(11, 2), new Point(9, 7), new Point(2, 2)));
        quadrilaterals.add(new Quadrilateral(new Point(5, 4), new Point(10, 4), new Point(10, 1), new Point(5, 1)));
        quadrilaterals.add(new Quadrilateral(new Point(1, 1), new Point(5, 5), new Point(1, 5), new Point(5, 1)));
        quadrilaterals.add(new Quadrilateral(new Point(1, 3), new Point(4, 4), new Point(3, 1), new Point(1, 1)));
        quadrilaterals.add(new Quadrilateral(new Point(5, 5), new Point(1, 3), new Point(4, 1), new Point(1, 3)));
        quadrilaterals.add(new Quadrilateral(new Point(2, 0), new Point(0, 2), new Point(4, 2), new Point(2, 4)));
        quadrilaterals.add(new Quadrilateral(new Point(0, 1), new Point(0, 5), new Point(5, 3), new Point(-5, 3)));
        quadrilaterals.add(new Quadrilateral(new Point(0, 0), new Point(0, 3), new Point(-5, 3), new Point(-5, 0)));

        int squareCounter = 0,
                arbitraryCounter = 0,
                rhombusCounter = 0,
                rectangleCounter = 0;

        String outputString = "";

        for (Quadrilateral quadrangle :
                quadrilaterals) {
            outputString += quadrangle.toString() + "\n\n";
            switch (quadrangle.getGeometricType()) {
                case SQUARE:
                    squareCounter++;
                    squarePerimeters.add(quadrangle.getPerimeter());
                    break;
                case ARBITRARY:
                    arbitraryCounter++;
                    arbitraryPerimeters.add(quadrangle.getPerimeter());
                    break;
                case RHOMBUS:
                    rhombusCounter++;
                    rhombusPerimeters.add(quadrangle.getPerimeter());
                    break;
                case RECTANGLE:
                    rectangleCounter++;
                    rectanglePerimeters.add(quadrangle.getPerimeter());
                    break;
            }
        }



        outputString += String.format("The total of squares is %d, with max - %.2f and min - %.2f perimeters\n",
                            squareCounter, Collections.max(squarePerimeters), Collections.min(squarePerimeters));
        outputString += String.format("The total of arbitraries is %d, with max - %.2f and min - %.2f perimeters\n",
                            arbitraryCounter, Collections.max(arbitraryPerimeters), Collections.min(arbitraryPerimeters));
        outputString += String.format("The total of rhombuses is %d, with max - %.2f and min - %.2f perimeters\n",
                            rhombusCounter, Collections.max(rhombusPerimeters), Collections.min(rhombusPerimeters));
        outputString += String.format(("The total of rectangles is %d, with max - %.2f and min - %.2f perimeters\n"),
                        rectangleCounter, Collections.max(rectanglePerimeters), Collections.min(rectanglePerimeters));

        return outputString;

    }

}
