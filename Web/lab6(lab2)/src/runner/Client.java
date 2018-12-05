package runner;

import model.medicine.Medicine;
import model.pharmacy.RemotePharmacy;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.List;

/**
 * Client class which work with rmi methods of pharmacy
 * @author Ilya Sysoi
 * @version 1.0.0
 */

public class Client {

    /**
     * logging via log4j
     */
    private static final Logger logger = LogManager.getLogger();

    /**
     * The Client method
     * @param args command line parameters
     */
    public static void main(String[] args) {
        Registry reg;
        RemotePharmacy stub;
        try {
            reg = LocateRegistry.getRegistry(9001);
            stub = (RemotePharmacy) reg.lookup("Pharmacy");
        } catch (RemoteException | NotBoundException e) {
            logger.warn(e);
            return;
        }

        try {
            printMedicineList("", stub.getMedicines());
        } catch (RemoteException e) {
            logger.warn(e);
        }

//        List<Person> p = Controller.getPersonList();
//        System.out.println("All members");
//        System.out.println(Controller.getPeoples(p));
//        stub.addPeoples(p);
//        System.out.println(Controller.numberOfMembers(stub) + "\n");
//        Controller.createAllPerformances(stub);
//        for (ActBase ab : stub.getAllPerformances())
//            System.out.println("Created new performance(" + ab.getClass() + "):\n"
//                    + Controller.getMemberList(ab) +
//                    "\n_______________________________");
//
//        List<Person> age = Controller.selectWithAge(stub, 15, 20);
//        System.out.println("Members between 15-20");
//        System.out.println(Controller.getPeoples(age));
//        List<Person> gendor = Controller.selectWithGender(stub, Person.Gender.MAN);
//        System.out.println("\n\nBoys in the collective");
//        System.out.println(Controller.getPeoples(gendor));
//
//        System.out.println("\n\nNon-sorting performances:\n" + Controller.getPerformances(stub.getAllPerformances()));
//        System.out.println("\n\nSorting performances:\n" + Controller.getPerformances(
//                Controller.sortByPerfomance(stub)));
//
//        System.out.println(Controller.performance(stub));
    }

    public static void printMedicineList(String textBefore, List<Medicine> list) {
        System.out.println("-----------" + textBefore + "---------");
        if (list.size() > 0) {
            for (Medicine medicine : list) {
                System.out.println(medicine);
            }
        } else {
            System.out.println("No items");
        }
        System.out.println();
    }

}
