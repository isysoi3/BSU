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
import java.util.Random;

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

        Random rand = new Random();
        var mode = rand.nextInt(5);
        try {
            logger.info("I`m come into the pharmacy");
            stub.comeIn();
            var medecines = stub.getMedicines();
            printMedicineList("All medicines at pharmacy", medecines);
            List<Medicine> sortedMedecines;
            switch (mode) {
                case 0:
                    sortedMedecines = stub.sortMedicinesByPrice(false);
                    printMedicineList("Sorted medicines by price at pharmacy", sortedMedecines);
                    break;
                case 1:
                    sortedMedecines = stub.sortMedicinesByName(false);
                    printMedicineList("Sorted medicines by price at pharmacy", sortedMedecines);
                    break;
                case 2:
                    sortedMedecines = stub.sortMedicinesByExpirationDate(false);
                    printMedicineList("Sorted medicines by price at pharmacy", sortedMedecines);
                    break;
                case 3:
                    sortedMedecines = stub.sortMedicinesByManufactureDate(false);
                    printMedicineList("Sorted medicines by price at pharmacy", sortedMedecines);
                    break;
                case 4:
                    var totalPrice = stub.countTotalPrice();
                    logger.info("I am check price of medicines " + totalPrice);
                    return;
                default:
                    sortedMedecines = medecines;
            }

            for(Medicine medicine : sortedMedecines) {
                logger.info("Try to buy medicine\n" + medicine);
                if (stub.buyMedicine(medicine)) {
                    logger.info("Successful bought");
                    logger.info(medicine.makeEffect());
                    break;
                }
                logger.info("Fail to buy, let`s try another one");
            }
        } catch (RemoteException e) {
            logger.warn(e);
        }
        finally {
            try {
                stub.goOut();
            } catch (RemoteException e) {
                logger.warn(e);
            }
            logger.info("I`m go out from the pharmacy");
        }
    }

    public static void printMedicineList(String textBefore, List<Medicine> list) {
        logger.info("\n" + "-----------" + textBefore + "---------");
        if (list.size() > 0) {
            for (Medicine medicine : list) {
                logger.info("\n" + medicine);
            }
        } else {
            logger.info("No items");
        }
    }

}
