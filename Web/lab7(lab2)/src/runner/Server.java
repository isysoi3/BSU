package runner;

import util.pharmacy.builder.MedicineBuilder;
import util.pharmacy.director.MedicineDirector;
import model.medicine.internal.ColorEnum;
import model.pharmacy.Pharmacy;
import model.pharmacy.PharmacyManager;
import model.pharmacy.RemotePharmacy;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.rmi.AlreadyBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

/**
 *  Server class which contains pharmacy
 *   * @author Ilya Sysoi
 *  * @version 1.0.0
 */
public class Server {

    /**
     * logging via log4j
     */
    private static final Logger logger = LogManager.getLogger();

    /**
     * The Client method
     * @param args command line parameters
     */
    public static void main(String[] args) {
        var pharmacy = new Pharmacy(new PharmacyManager());
        MedicineDirector director = new MedicineDirector();
        MedicineBuilder builder = new MedicineBuilder();
        pharmacy.addMedicine(director.manufactureAntibiotic(builder, "Antibiotic4", 5.5, false));
        builder.reset();

        pharmacy.addMedicine(director.manufactureGell(builder, "gel1", 12.4, true));
        builder.reset();

        pharmacy.addMedicine(director.manufactureGell(builder, "gel2", 32.4, false));
        builder.reset();

        pharmacy.addMedicine(director.manufactureOintment(builder, "Ointment1", 50.5, true));
        builder.reset();

        pharmacy.addMedicine(director.manufactureAntibiotic(builder, "Antibiotic2", 50.5, true));
        builder.reset();

        pharmacy.addMedicine(director.manufacturePill(builder, "Pill43", 5.4, 2));
        builder.reset();

        pharmacy.addMedicine(director.manufactureSyrup(builder, "Syrup32", 42.5, ColorEnum.RED));
        builder.reset();

        pharmacy.addMedicine(director.manufacturePill(builder, "Pill753", 5.4, 2));
        builder.reset();

        pharmacy.addMedicine(director.manufactureGell(builder, "Gel5", 42.5, false));
        builder.reset();

        pharmacy.addMedicine(director.manufactureOintment(builder, "Ointment2", 2.4, false));
        builder.reset();

        pharmacy.addMedicine(director.manufacturePill(builder, "Pill23", 2.4, 1));
        builder.reset();

        pharmacy.addMedicine(director.manufactureAntibiotic(builder, "Antibiotic5", 54.5, false));
        builder.reset();

        logger.info("Create pharmacy");

        try {
            RemotePharmacy stub = (RemotePharmacy) UnicastRemoteObject.exportObject(pharmacy, 0);
            Registry reg = LocateRegistry.createRegistry(9001);
            reg.bind("Pharmacy", stub);
            logger.info("Register pharmacy");
        } catch (RemoteException | AlreadyBoundException e) {
            logger.warn(e);
        }
    }

}
