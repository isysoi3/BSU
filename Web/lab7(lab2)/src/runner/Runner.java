package runner;

import controller.Controller;
import controller.ParsingModeEnum;
import exception.ParserException;
import model.medicine.Medicine;
import model.pharmacy.Pharmacy;
import model.pharmacy.PharmacyManager;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import javax.swing.text.html.parser.Parser;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

/**
 * Runner class which contains pharmacy
 * * @author Ilya Sysoi
 * * @version 1.0.0
 */
public class Runner {

    /**
     * logging via log4j
     */
    private static final Logger logger = LogManager.getLogger();

    public static final String FILE_XML = "medicines.xml";
    public static final String FILE_XSD = "xsd_schema.xsd";

    /**
     * The Client method
     *
     * @param args command line parameters
     */
    public static void main(String[] args) {
        logger.info("Start work");

        var controller = new Controller(new Pharmacy(new PharmacyManager()));

        controller.validate(FILE_XML, FILE_XSD);

        logger.info("Create pharmacy");

        if (args.length < 1) {
            logger.warn("No parsing mode argument");
        }
        ParsingModeEnum mode = null;
        switch (args[0]) {
            case "-d":
                mode = ParsingModeEnum.DOM;
                break;
            case "-s":
                mode = ParsingModeEnum.SAX;
                break;
            case "-st":
                mode = ParsingModeEnum.StAX;
                break;
        }

        List<Medicine> medicines = null;
        try {
            medicines = controller.parseMedicinesList(FILE_XML, mode);
        } catch (ParserException e) {
            logger.warn(e);
        }
        for (Medicine medicine : Objects.requireNonNull(medicines)) {
            controller.addMedicine(medicine);
        }

        printMedicineList("Just list of medicine in pharmacy", controller.getPharmacyMedicines());

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
