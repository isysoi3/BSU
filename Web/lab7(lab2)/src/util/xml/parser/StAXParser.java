package util.xml.parser;

import exception.ParserException;
import model.medicine.Medicine;
import model.medicine.internal.ColorEnum;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import util.pharmacy.builder.MedicineBuilder;
import util.pharmacy.director.MedicineDirector;

import javax.xml.stream.XMLEventReader;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamConstants;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.events.EndElement;
import javax.xml.stream.events.StartElement;
import javax.xml.stream.events.XMLEvent;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Locale;

/**
 * StAX parser of XML
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */

public class StAXParser implements MedicinesParser {

    private static final Logger logger = LogManager.getLogger("Parser");


    /**
     * Parse XML file to collective using DOM parser
     *
     * @param fileName name of the file that contains medicines stored in XML format
     * @return parsed medicines list
     * @throws ParserException if some error occurred while parsing XML file
     */
    @Override
    public List<Medicine> parse(String fileName) throws ParserException {
        logger.info("Starting DOM parsing");
        List<Medicine> medicines = new ArrayList<>();
        MedicineDirector director = new MedicineDirector();
        MedicineBuilder builder = new MedicineBuilder();

        XMLInputFactory factory = XMLInputFactory.newInstance();
        XMLEventReader eventReader;
        try {
            eventReader = factory.createXMLEventReader(new FileReader(fileName));
        } catch (XMLStreamException | FileNotFoundException e) {
            throw new ParserException("Configuration StAX parser error", e);
        }
        String currentElement = "";
        boolean parsed;
        parsed = true;
        String name = "";
        double price = 0;
        Date manufactureDate = null;
        Date expirationDate = null;
        boolean isWarming = false;
        double fluidityPercent = 0;
        double maxDailyDoseInMg = 0;
        boolean isRecipeRequired = false;
        boolean isCooling = false;
        int doseInMg = 0;
        ColorEnum color = null;


        while (eventReader.hasNext()) {
            XMLEvent event = null;
            try {
                event = eventReader.nextEvent();
            } catch (XMLStreamException e) {
                throw new ParserException("Fail to get eventReader", e);
            }
            String qName = "";

            switch (event.getEventType()) {
                case XMLStreamConstants.START_ELEMENT:
                    StartElement startElement = event.asStartElement();
                    qName = startElement.getName().getLocalPart();
                    currentElement = qName;
                    if (qName.equals("name") ||
                            qName.equals("price") ||
                            qName.equals("manufactureDate") ||
                            qName.equals("expirationDate") ||
                            qName.equals("fluidityPercent") ||
                            qName.equals("isWarming") ||
                            qName.equals("maxDailyDoseInMg") ||
                            qName.equals("isRecipeRequired") ||
                            qName.equals("isCooling") ||
                            qName.equals("doseInMg") ||
                            qName.equals("color")) {
                        parsed = false;
                    }
                    break;
                case XMLStreamConstants.CHARACTERS:
                    String value = event.asCharacters().getData();
                    if (!parsed) {
                        switch (currentElement) {
                            case "name":
                                name = value;
                                break;
                            case "price":
                                price = Double.parseDouble(value);
                                break;
                            case "manufactureDate":
                                try {
                                    manufactureDate = new SimpleDateFormat("yyyy-MM-dd", Locale.US).parse(value);
                                } catch (ParseException e) {
                                    e.printStackTrace();
                                }
                                break;
                            case "expirationDate":
                                try {
                                    expirationDate = new SimpleDateFormat("yyyy-MM-dd", Locale.US).parse(value);
                                } catch (ParseException e) {
                                    e.printStackTrace();
                                }
                                break;
                            case "isCooling":
                                isCooling = Boolean.parseBoolean(value);
                                break;
                            case "fluidityPercent":
                                fluidityPercent = Double.parseDouble(value);
                                break;
                            case "doseInMg":
                                doseInMg = Integer.parseInt(value);
                                break;
                            case "maxDailyDoseInMg":
                                maxDailyDoseInMg = Double.parseDouble(value);
                                break;
                            case "color":
                                color = ColorEnum.valueOf(value.toUpperCase());
                                break;
                            case "isWarming":
                                isWarming = Boolean.parseBoolean(value);
                                break;
                            case "isRecipeRequired":
                                isRecipeRequired = Boolean.parseBoolean(value);
                                break;
                        }

                        parsed = true;
                    }
                    break;
                case XMLStreamConstants.END_ELEMENT:
                    EndElement endElement = event.asEndElement();
                    qName = endElement.getName().getLocalPart();
                    switch (qName) {
                        case "pill":
                            medicines.add(director.manufacturePill(builder,
                                    name,
                                    price,
                                    manufactureDate,
                                    expirationDate,
                                    maxDailyDoseInMg,
                                    doseInMg));
                            break;
                        case "syrup":
                            medicines.add(director.manufactureSyrup(builder,
                                    name,
                                    price,
                                    manufactureDate,
                                    expirationDate,
                                    maxDailyDoseInMg,
                                    color));
                            break;
                        case "ointment":
                            medicines.add(director.manufactureOintment(builder,
                                    name,
                                    price,
                                    manufactureDate,
                                    expirationDate,
                                    fluidityPercent,
                                    isWarming));
                            break;
                        case "antibiotic":
                            medicines.add(director.manufactureAntibiotic(builder,
                                    name,
                                    price,
                                    manufactureDate,
                                    expirationDate,
                                    maxDailyDoseInMg,
                                    isRecipeRequired));
                            break;
                        case "gell":
                            medicines.add(director.manufactureGell(builder,
                                    name,
                                    price,
                                    manufactureDate,
                                    expirationDate,
                                    fluidityPercent,
                                    isCooling));
                            break;
                    }
                    builder.reset();
                    break;
            }
        }


        return medicines;
    }
}
