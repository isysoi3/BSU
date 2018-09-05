package Controller;

import Model.Point;
import Model.Quadrilateral;

/**
 * Basic class demonstrates functions of Quadrilateral and Point classes
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class Controller {

    /**
     * Method to demonstrate work with Quadrilateral and Point classes
     */
    public static void startWork() {
        Quadrilateral tmp = new Quadrilateral(
                new Point(0,0),
                new Point(0,1),
                new Point(1,0),
                new Point(1,1));
        System.out.println( tmp);

    }

}
